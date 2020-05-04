# ArrayList

**本文章基于 JDK 1.8**

ArrayList 是一个 **可变长**、**线程不安全** 的数组。

ArrayList 对象本身并不存储元素，而是通过内部持有的数组 **Object[] elementData** 存储元素。根据 Cache 的局部性原理，连续的地址可大幅降低读取内存的性能开销。

因此其符合顺序表的特性，size、isEmpty、get、set 操作为 **O(1)**，add、remove 操作时间复杂度为 **O(n)**。

ArrayList 适合 **查询操作较多** 的环境，若涉及频繁增删，建议使用 **LinkedList**。若需要线程安全建议使用 **Vector**。

本文将从 ArrayList 的动态扩充机制、序列化对源码进行解析：


## 动态扩充

ArrayList 需要设置容量（capacity），并可随着元素的增加自动扩容。其初始容量默认为 **10**，也可设置初始容量。

### 初始化

```java
//默认容量
private static final int DEFAULT_CAPACITY = 10;

//空数组，如指定容量为 0 ，返回此空数组
//ArrayList 的空实例都指向同一个数组，可优化性能，减少空实例个数
private static final Object[] EMPTY_ELEMENTDATA = {};

//JDK 1.8 新增，空数组，默认容量为 10
private static final Object[] DEFAULTCAPACITY_EMPTY_ELEMENTDATA = {};

//真正存储数组
transient Object[] elementData;

//可设置容量大小的构造器
public ArrayList(int initialCapacity) {
    if (initialCapacity > 0) {
        this.elementData = new Object[initialCapacity];
    } else if (initialCapacity == 0) {
	    //指定容量为 0，返回 EMPTY_ELEMENTDATA
        this.elementData = EMPTY_ELEMENTDATA;
    } else {
        throw new IllegalArgumentException("Illegal Capacity: "+
                initialCapacity);
    }
}

//无参构造器，默认容量为10
public ArrayList() {
    this.elementData = DEFAULTCAPACITY_EMPTY_ELEMENTDATA;
}

//传入集合
public ArrayList(Collection<? extends E> c) {
    elementData = c.toArray();
    if ((size = elementData.length) != 0) {
        // c.toArray might (incorrectly) not return Object[] (see 6260652)
        if (elementData.getClass() != Object[].class)
            elementData = Arrays.copyOf(elementData, size, Object[].class);
    } else {
        // replace with empty array.
        this.elementData = EMPTY_ELEMENTDATA;
    }
}
```

值得注意的是：不要将 **内部持有的数组的容量** 和 **ArrayList的大小** 混为一谈。构造器内仅对内部持有的数组容量进行扩充，ArrayList 大小并未改变。ArrayList 的大小需要根据 size 判断。

```cpp
ArrayList<Integer> list = new ArrayList<>(20);
System.out.println(list.size());
```

> 0


### 增长规则

Java 中数组扩容无法像 C/C++ 中 realloc() 原地扩容。而是创建新对象，并将原数组元素拷贝至新元素。

在校验长度后，扩充新容量 = 旧容量的 1.5 倍（位运算提升效率）。

```java
// 避免 overflow
private static final int MAX_ARRAY_SIZE = Integer.MAX_VALUE - 8;

private void grow(int minCapacity) {
 // overflow-conscious code
    int oldCapacity = elementData.length;
    int newCapacity = oldCapacity + (oldCapacity >> 1);
    if (newCapacity - minCapacity < 0)
        newCapacity = minCapacity;
    if (newCapacity - MAX_ARRAY_SIZE > 0)
        newCapacity = hugeCapacity(minCapacity);
    elementData = Arrays.copyOf(elementData, newCapacity);
}

private static int hugeCapacity(int minCapacity) {
    if (minCapacity < 0) // overflow
        throw new OutOfMemoryError();
    return (minCapacity > MAX_ARRAY_SIZE) ?
        Integer.MAX_VALUE :
        MAX_ARRAY_SIZE;
}
```

由于扩容时需要进行数组拷贝，相当费时，因此应当尽力避免扩容。

**小结**：

* ArrayList 构造器总共有三种：无参，传入容量大小，传入Collection。构造器通过判断 capacity 的情况初始化数组。
* 区分内部持有数组容量和ArrayList大小
* 当原数组空间不足时，将会直接开辟新空间，并对旧数组进行拷贝，新容量 = 旧容量 * 1.5





## 元素操作

ArrayList 元素操作中大量使用了 **System.arraycopy()**，其最终调用了 C 的 **memmove()** 函数。
```java
public static native void arraycopy(Object src,  int  srcPos, Object dest, int destPos, int length);
```

**典型方法：**
```java
public void add(int index, E element) {
	//范围检查
    rangeCheckForAdd(index);
	//1.确保数组容量
	//2.增加modCount，用于判断是否进行过结构性修改
    ensureCapacityInternal(size + 1);  
    //index元素以及所有后续元素右移一个位置。  
    System.arraycopy(elementData, index, elementData, index + 1, size - index);
    elementData[index] = element;
    size++;
}
    
public E remove(int index) {
    rangeCheck(index);

    modCount++;
    E oldValue = elementData(index);

    int numMoved = size - index - 1;
    if (numMoved > 0)
	    //所有"index + 1"及之后的元素向前移一位
        System.arraycopy(elementData, index+1, elementData, index,
                         numMoved);
    elementData[--size] = null; // clear to let GC do its work

    return oldValue;
}

//简易版 remove 方法，跳过范围检测及返回值
private void fastRemove(int index) {
    modCount++;
    int numMoved = size - index - 1;
    if (numMoved > 0)
        System.arraycopy(elementData, index+1, elementData, index,
                         numMoved);
    elementData[--size] = null; // clear to let GC do its work
}
```




## 非线程安全

ArrayList 是非线程安全的。如果多个线程访问同一个ArrayList的实例，并修改了结构（structural modification）如增加或删除一个元素（修改元素值不属于改变结构），需使用线程安全的容器。
如需使用线程安全的 ArrayList，可使用 **Collections.synchronizedList**

> List list = Collections.synchronizedList(new ArrayList(...));




## 序列化

ArrayList 中 elementData 使用 transient 修饰，该对象不直接进行序列化。而是通过调用 writeObject，直接将 size 和 element 写入 ObjectOutputStream。

通过以上方法，可剔除 elementData 中的预留空间，节省空间和时间。


*END ~*


* fail fast