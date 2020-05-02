# 数组

## 剑指 OFFER

* 数组在算法中常作为简单的哈希表使用

* 动态数组 vector , 避免频繁扩充数组容量

* 二维数组

# 字符串

## 剑指 OFFER

* 字符数组 以 '\0' 结尾，声明字符数组时，常为字符串长度 + 1
* 声明为 字符串常量 const char *
* 频繁移动数组时，从后向前移动

# 链表

## 剑指 OFFER

# 树

## 剑指 OFFER

BST 堆 红黑树

# 栈和队列

# 递归和循环

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

# 回溯法



