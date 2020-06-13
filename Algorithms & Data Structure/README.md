# 数据结构

## 数组

## 链表

### 单链表

### 双向链表

### 循环链表

### 双向循环链表

## 栈

## 队列

### 普通队列

### 阻塞队列

### 并发队列

### 双端队列

## 树

### 堆

### 并查集

### 字典树

## 图

## 哈希表



# 算法

## 双指针

## 二分

leetcode 4. Median of Two Sorted Arrays

## 分治算法

https://www.cnblogs.com/oldby/p/11646402.html

hanio tower 2^n-1

汉诺塔II

## 回溯算法

全排列

N 皇后

## 贪心算法

### 普通贪心

### 区间贪心

## 动态规划




























# 数组

由于数组查找时间复杂度为 O(1)，常使用数组作为简易 **哈希表**，即**整数散列**，适用于数据规模小于 **10^5** 的情况。其 key-value 一一对应的特点常作为解题的关键：

[剑指OFFER: 03.数组中重复的数字 题目一](https://github.com/Lsyhprum/StudyNotes/tree/master/Algorithms%20%26%20Data%20Structure/%E5%89%91%E6%8C%87OFFER/03.%E6%95%B0%E7%BB%84%E4%B8%AD%E9%87%8D%E5%A4%8D%E7%9A%84%E6%95%B0%E5%AD%97)

同时数组常与 **折半查找** 一起使用：

[剑指OFFER: 03.数组中重复的数字 题目二](https://github.com/Lsyhprum/StudyNotes/tree/master/Algorithms%20%26%20Data%20Structure/%E5%89%91%E6%8C%87OFFER/3.%E6%95%B0%E7%BB%84%E4%B8%AD%E9%87%8D%E5%A4%8D%E7%9A%84%E6%95%B0%E5%AD%97)

单纯考察一维数组的题目并不很多，大多结合其他算法使用。

除一维数组外，二维数组也是一种考察方向：

[剑指OFFER: 04.二维数组中的查找](https://github.com/Lsyhprum/StudyNotes/tree/master/Algorithms%20%26%20Data%20Structure/%E5%89%91%E6%8C%87OFFER/04.%E4%BA%8C%E7%BB%B4%E6%95%B0%E7%BB%84%E4%B8%AD%E7%9A%84%E6%9F%A5%E6%89%BE)


[LeetCode: 48.Rotate Image]()





## 剑指 OFFER

* 动态数组 vector , 避免频繁扩充数组容量

* 二维数组

## LeetCode





# 字符串

## 剑指 OFFER

* 字符数组 以 '\0' 结尾，声明字符数组时，常为字符串长度 + 1
* 声明为 字符串常量 const char *
* 频繁移动数组时，从后向前移动

# 链表

* 删除链表结点
  * 保存前结点
  * copy 下一节点的值，删除下一个结点

## 剑指 OFFER

# 树

## 剑指 OFFER

BST 堆 红黑树

# 栈和队列

# 递归和循环

## 分治

## 递归





# 查找和排序

顺序查找、二分查找、哈希表、二叉排序树查找

快排--> 荷兰国旗问题，双指针

```cpp
void Swap(int &a, int &b){
    int c = b;
    b = a;
    a = c;
}

int partition(int data[], int length, int start, int end){
    if(data == NULL || length <= 0 || start < 0 || end >= length)
        return -1;

    int pivot = data[start];
    int left = start;
    int right = end;

    while(left < right){
        while(data[right] >= pivot && left < right){
            right --;
        }

        //cout << data[right] << endl;

        while(data[left] <= pivot && left < right){
            left ++;
        }

        //cout << data[left] << endl;

        if(left < right){
            Swap(data[left], data[right]);
        }
    }

    Swap(data[left], data[start]);
    //cout << left << endl;

    return left;
}

void QuickSort(int data[], int length, int start, int end){
    if(start == end) return ;

    int index = partition(data, length, start, end);
    //cout << index << endl;
    if(start < index)
        QuickSort(data, length, start, index - 1);

    if(index < end)
        QuickSort(data, length, index + 1, end);
}
```



