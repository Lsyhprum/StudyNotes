# 2018 杭电计算机复试笔试题

## 第一题

> 给出 n 个人的名字，各抽取一个数字，自己用一种数据结构存取人的名字和抽取数字信息（票数）。eg: Bob 9 Alice 12 Tom 5 Wisten 7

> 1 定义丑数，其因子除 1 外 只用 2 3 5 的倍数，输出所有抽到丑数人的名字
>
> 2 根据个人所抽数字大小排序，输出排序后的名字
>
> 3 将一个新名字加入所有名字的中间（n / 2）。并输出排序后所有人的名字。

**Note**:
1. 结构体

2. [map]()

## 第二题

> 给出两张 bmp 图像（两个矩阵），将第一张图上的某个部分截取下来放入第二张某个位置

> 1 (程序填空题)根据题目函数的定义填出整个拷贝图像过程

> 2 写出 copybmp 的整个具体函数

```cpp
// pOldbuf、pNewbuf 两张图像首地址
// OldW、NewW 两图像宽度
// BlockW、BlockH 待截取部分的宽和高
void copybmp(unsigned char *pOldbuf, unsigned char *pNewbuf, int OldW, int NewW, int BlockH, int Block)
```


# 第三题

>瓜农王大爷去年种西瓜赚了不少钱。看到收入不错，今年他又重新开辟了n个西瓜地。
为了能给他的n个西瓜地顺利的浇上水，对于每个西瓜地他可以选择在本地打井，也可以修管道从另一个瓜地（这个瓜地可能打了井；也可能没打井，他的水也是从其他瓜地引来的）将水引过来。
当然打井和修管道的费用有差别。已知在第i个西瓜地打井需要耗费wi元，在第i、j个西瓜地之间修管道需要耗费pi,j元。
现在的问题是：王大爷要想使所有瓜地都被浇上水，至少需要花费多少钱（打井与修管道的费用和）？
由于瓜地较多，王大爷无法选择在哪些（个）瓜地打井，哪些西瓜地之间修管道。
请你编程帮王大爷做出决策，求出最小费用。
>
>输入格式:
>
>第1行，一个正整数n，代表西瓜地的数量。
以下n行，依次给出整数w1…wn（每块西瓜地的打井费用）。
紧接着是一个n*n的整数矩阵，矩阵的第i行第j列的数代表pi,j（两块西瓜地之间建立管道的费用）。每行的两个数之间有一个空格隔开。


**Note**:

应用贪婪算法，先在打井费用最便宜的地打井，用已有水源的地更新没有水源的地（判断两者之间是否适合挖管道），若所有地都有水源，算法结束，否则，打下一口井