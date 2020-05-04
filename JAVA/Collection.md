List、Set、Map, Map 没有继承Collection

# List

## ArrayList

* ArrayList 插入删除一定慢吗？
* ArrayList 和 LinkedList 遍历性能比较如何？
* ArrayList 如何扩容？
* ArrayList 数据结构？
* ArrayList 默认大小？
* 线程安全？
* 数组队列？

## LinkedList

## Vector

# Set

# Map


 
### fail fast
**fail-fast** 机制是 Collection 中的一种错误机制。当多个线程对同一个集合的内容进行操作时，就可能会产生 fail-fast 事件。
例如：当某一个线程 A 通过 iterator 去遍历某集合的过程中，若该集合的内容被其他线程所改变了；那么线程 A 访问集合时，就会抛出 **ConcurrentModificationException** 异常，产生 fail-fast 事件。
由于迭代器的 fail-fast 无法得到保证，所以 Iterator 在工作的时候是不允许被迭代的对象被改变的。但可以使用 Iterator 本身的方法 remove() 来删除对象，**Iterator.remove()** 方法会在删除当前迭代对象的同时维护索引的一致性。


浅拷贝