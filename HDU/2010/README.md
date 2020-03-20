# 2010 杭电计算机复试笔试题

## 第一题

> 随机产生一个3位的正整数，让你进行猜数字，如果猜小了，输出：“猜小了，请继续”。  如果猜大了，输出：“猜大了，请继续”。如果猜对了。输出：“恭喜你，猜对了”。不过最多只能猜10次，如果猜了10次还没有猜对，就退出程序，输出：“Bye Bye”。

[题解](https://github.com/Lsyhprum/StudyNotes/blob/master/%E6%9D%AD%E7%94%B5%E7%AC%94%E8%AF%95/2010/Pro.ID1.cpp)

**Note**:

* srand() : 设置 rand() 产生随机数时的随机数种子。利用系统时钟，可以产生不同的随机数（需引入 ctime 头文件）。

```cpp
srand((unsigned int)time(NULL));
```

* rand() : 返回 0 - RAND_MAX 之间的随机数，RAND_MAX 与 int 位数有关，最小为 32767，其结果与随机数种子有关，种子不变，生成随机数不变。

	* 随机数范围 [0,x)：rand() % x
	* 随机数范围 [a,b)：rand() % (b-a) + a
	* 随机数范围 [a,b]： rand() % (b-a+1) + a 
	* 随机数范围 (a,b]：rand() % (b-a) + a + 1 

## 第二题

>编写函数 FindAndSum，输入一个字符串，把字符串中的数字作为整数进行求和，并输出结果。
>
>Sample ： 
>
>输入：There are some apple. 
>
>输出：0
>
>输入：124and 1524 
>
>输出：1648 。

[题解](https://github.com/Lsyhprum/StudyNotes/blob/master/%E6%9D%AD%E7%94%B5%E7%AC%94%E8%AF%95/2010/Pro.ID2.cpp)

**Note**:

string/字符数组 的应用

## 第三题

>处理一个文件 student.txt。从这个文件当中读入学生的信息，然后按照总成绩从高到低进行排序并输出学生信息。
>文件当中包括一组学生的信息，包括名字、学号、英语成绩、语文成绩、数学成绩、科学成绩，如下： 

| 姓名      |     学号 |   英语   |   语文   |   数学   |   科学    |
| :--------: | :--------:| :------: | :--------: | :--------:| :------: |
|张三 |20100601| 78 |89| 62| 75| 
|李四 |20100602 |78 |54 |98 |86 |
|王五| 20100603| 78 |69 |85 |75 |

[题解](https://github.com/Lsyhprum/StudyNotes/blob/master/%E6%9D%AD%E7%94%B5%E7%AC%94%E8%AF%95/2010/Pro.ID3.cpp)

**Note**:

cpp 文件操作：

* 打开文件：

```cpp
ofstream out("filename", ios::out);
ifstream out("filename", ios::in);
fstream out("filename", ios::in|ios::out);
```

* 写文件：

```cpp
ofstream out("filename");
out << "test";
out.close();
```

* 读文件：

```cpp
ifstream in("filename");
in >> buffer >> a >> b;
out.close();
```



