# string

使用 string 需要添加 string 头文件

## string 定义

**与其他 STL 容器相同**，只需要在 string 后跟变量名即可，也可以声明变量时赋值。

## string 与 字符数组 转化

* string 转 字符数组：

str.c_str()

**易错: printf 只能输出字符数组，输出 string 时需要使用 c_str() 转为字符数组。**

* 字符数组 与 string 转化

```cpp
char buf[64] = {0};
s1.copy(buf, 7);
```

## string 访问

* 通过下标访问

* 通过迭代器访问

```cpp
for(string::iterator it = str.begin(); it != str.end(); it ++){
    printf("%c", *it);
}
```

## string 添加

* 字符串连接

operator+= / str.append(s)

* 添加字符

str.push_back(c)

* 插入固定位置

str.insert(pos, s)

```cpp
string str = "abcxyz", str2 = "opq";
str.insert(3, str2);
cout << str << endl;  // abcopqxyz
```

## string 删除

* 删除单个元素

str.erase(it)

```cpp
string str = "abcdefg";
str.erase(str.begin() + 4);
cout << str << endl;   // abcdfg
```

* 删除区间内元素

str.erase(first, last)

```cpp
string str = "abcdefg";
str.erase(str.begin() + 2, str.end() - 1);
cout << str << endl;   // abg
```

* 删除全部元素

str.clear()

## string 修改

* str.replace(pos, len, s)

把 str 从 pos 号开始，长度为 len 的子串替换为 s

## string 查询

* 查询子串

str.substr(pos, len)

* 查询元素

string::npos 是一个常数，本身值为 -1，用以作为 find() 函数失配时的返回值

str.find(s)，当 s 为 str 的子串时，返回其在 str 中第一次出现的位置，若为子串，返回 string::npos

## string 其他常用方法

* compare operator

两个 string 类型比较大小，比较规则为字典序

* str.length() / str.size()

string 长度

* to_string(val)

将数值转化为字符串

[PAT A1060]()