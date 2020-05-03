# Android 消息机制
Android 消息机制主要指 **Handler** 的运行机制，Handler 的运行需要底层的 **MessageQueue** 以及 **Looper** 的支持。Handler 创建线程时会通过 **ThreadLocal** 获取当前线程的 **Looper** 来构造消息循环系统。子线程默认没有 Looper，主线程——ActivityThread 被创建时会初始化 Looper。

## 概述
Android 的 UI 控件不是线程安全的（在 UI 控件加上锁机制不仅会使逻辑变复杂，并且会降低 UI 访问的效率），因此 Android 规定只能在 主线程访问 UI，因此需要 Handler   机制切换线程。
Handler 采用当前线程 Looper 构建内部的消息系统，若当前的线程没有 Looper，则会报错：
> java.lang.RuntimeException: Can't create handler inside thread that has not called Looper.prepare()

通过 Handler 的 send 或 post 再子线程发送消息后，此消息将会被置入创建 Handler 的线程中的 MessageQueue 中，最终被 Looper 处理。
![](http://oh1zr9i3e.bkt.clouddn.com/17-5-1/93960763-file_1493632763982_153de.jpg)

## MessageQueue
**MessageQueue** 内部通过**单链表**维护消息列表，主要包含两个操作——**插入（enqueueMessage）**以及**读取（next）**
### enqueueMessage
主要为单链表的插入
```java
synchronized (this) {
	msg.markInUse();
	msg.when = when;
	Message p = mMessages;
	boolean needWake;
	//新链表
	if (p == null || when == 0 || when < p.when) {
	    msg.next = p;
	    mMessages = msg;
	    needWake = mBlocked;
	} else {
	    needWake = mBlocked && p.target == null && msg.isAsynchronous();
	    Message prev;
	    for (;;) {
	        prev = p;
	        p = p.next;
	        if (p == null || when < p.when) {
	            break;
	        }
	        if (needWake && p.isAsynchronous()) {
	            needWake = false;
	        }
	    }
	    msg.next = p;
	    prev.next = msg;
	}
	
	if (needWake) {
	    nativeWake(mPtr);
	}
}
```
### next
无限循环，当有新消息时，返回并删除。
```java
int pendingIdleHandlerCount = -1; // -1 only during first iteration
int nextPollTimeoutMillis = 0;
//无限循环
for (;;) {
    if (nextPollTimeoutMillis != 0) {
        Binder.flushPendingCommands();
    }

    nativePollOnce(ptr, nextPollTimeoutMillis);

    synchronized (this) {
        // Try to retrieve the next message.  Return if found.
        final long now = SystemClock.uptimeMillis();
        Message prevMsg = null;
        Message msg = mMessages;
        if (msg != null && msg.target == null) {
            // Stalled by a barrier.  Find the next asynchronous message in the queue.
            do {
                prevMsg = msg;
                msg = msg.next;
            } while (msg != null && !msg.isAsynchronous());
        }
        if (msg != null) {
            if (now < msg.when) {
                // Next message is not ready.  Set a timeout to wake up when it is ready.
                nextPollTimeoutMillis = (int) Math.min(msg.when - now, Integer.MAX_VALUE);
            } else {
                // Got a message.
                mBlocked = false;
                if (prevMsg != null) {
                    prevMsg.next = msg.next;
                } else {
                    mMessages = msg.next;
                }
                msg.next = null;
                if (DEBUG) Log.v(TAG, "Returning message: " + msg);
                msg.markInUse();
                return msg;
            }
        } else {
            // No more messages.
            nextPollTimeoutMillis = -1;
        }
}
```
## Looper
*   **创建 Looper：**prepare()
*   **获取主线程 Looper：**getMainLooper()
*  **直接退出：**quit()
*  **安全退出（处理完消息队列中的消息再退出）：**quitSafely()
*   **开始循环：**loop()
同样是一个死循环，唯一跳出方法是 MessageQueue 的 next() 返回了 null。如果 Looper 不退出，将会一直阻塞在那里。
当获取到新消息，将交给 Handler 的**dispatchMessage** 处理，切换到指定的线程中。
```java
 public static void loop() {
 final Looper me = myLooper();
    if (me == null) {
        throw new RuntimeException("No Looper; Looper.prepare() wasn't called on this thread.");
    }
    final MessageQueue queue = me.mQueue;

    // Make sure the identity of this thread is that of the local process,
    // and keep track of what that identity token actually is.
    Binder.clearCallingIdentity();
    final long ident = Binder.clearCallingIdentity();

    for (;;) {
        Message msg = queue.next(); // might block
        if (msg == null) {
            // No message indicates that the message queue is quitting.
            return;
        }

        // This must be in a local variable, in case a UI event sets the logger
        final Printer logging = me.mLogging;
        if (logging != null) {
            logging.println(">>>>> Dispatching to " + msg.target + " " +
                    msg.callback + ": " + msg.what);
        }

        final long traceTag = me.mTraceTag;
        if (traceTag != 0 && Trace.isTagEnabled(traceTag)) {
            Trace.traceBegin(traceTag, msg.target.getTraceName(msg));
        }
        try {
            msg.target.dispatchMessage(msg);
        } finally {
            if (traceTag != 0) {
                Trace.traceEnd(traceTag);
            }
        }

        if (logging != null) {
            logging.println("<<<<< Finished to " + msg.target + " " + msg.callback);
        }

        // Make sure that during the course of dispatching the
        // identity of the thread wasn't corrupted.
        final long newIdent = Binder.clearCallingIdentity();
        if (ident != newIdent) {
            Log.wtf(TAG, "Thread identity changed from 0x"
                    + Long.toHexString(ident) + " to 0x"
                    + Long.toHexString(newIdent) + " while dispatching to "
                    + msg.target.getClass().getName() + " "
                    + msg.callback + " what=" + msg.what);
        }

        msg.recycleUnchecked();
    }
}
```
## 主线程
Android 的入口方法为 ActivityThread 中的 main，其中通过 **Looper.prepareMainLooper()** 创建主线程的 Looper 及 MessageQueue。
```java
public static void main(String[] args) {  
    SamplingProfilerIntegration.start();  
    CloseGuard.setEnabled(false);  
    Environment.initForCurrentUser();  
    EventLogger.setReporter(new EventLoggingReporter());  
    Process.setArgV0("<pre-initialized>");  
    
    //创建主线程 Looper
    Looper.prepareMainLooper();  
    // 创建ActivityThread实例  
    ActivityThread thread = new ActivityThread();  
    thread.attach(false);  

    if (sMainThreadHandler == null) {  
        sMainThreadHandler = thread.getHandler();  
    }  

    AsyncTask.init();  

    if (false) {  
        Looper.myLooper().setMessageLogging(new  
                LogPrinter(Log.DEBUG, "ActivityThread"));  
    }  

    Looper.loop(); //开启循环 

    throw new RuntimeException("Main thread loop unexpectedly exited");  
}  
```
*END ~*


# Android 异步消息处理机制

Android 异步消息处理主要由 4 部分组成：Message、Handler、MessageQueue、Looper

## Message

在线程间传递消息

## Handler

用于发送和处理消息

## MessageQueue

存放 Handler 发送的消息，每个线程中都有一个 MessageQueue

## Looper

Looper 是 MessageQueue 的管家，调用 loop() 后，进入死循环中，将新 Message 传递到 Handler 中。
