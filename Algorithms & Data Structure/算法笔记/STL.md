<!-- GFM-TOC -->
* [vector](#vector)
* [set](#set)
* [string](#string)
* [map](#map)
* [queue](#queue)
* [priority_queue](#priority_queue)
* [stack](#stack)
* [pair](#pair)
<!-- GFM-TOC -->


# vector

变长数组

## vector 定义

```cpp
vector<typename> name;
```

**易错：如果 typename 也是一个 STL 容器，定义时记得要在 >> 符号间加上空格**

## vector 访问

* 通过下标访问

* 通过迭代器访问

vi[i] 和 *(vi.begin() + i) 等价

**注意：除开 vector 和 string 之外的 STL 容器都不支持 *(it + i)**

begin() 作用是取 vi 的首元素地址，end() 取尾元素地址的**下一个地址**（左闭右开）

## vector 添加

* push_back()

* emplace_back()

比 push_back() 快

* insert(it, x)

向 vector 的任意迭代器 it 处插入一个元素 x

## vector 删除

* pop_back()

* clear()

* erase(it)

* erase(fist, last)


# set

内部自动排序且不含重复元素的容器

## set 访问

**set 只能通过迭代器访问**

## set 添加

* insert()

insert(x) 可将 x 插入 set 容器中，并自动递增和去重，时间复杂度为 logN

## set 删除

* erase(it)

* erase(val)

* erase(first, last)

* clear()

## set 查询

* find()

返回 set 中对应值的迭代器

## set 其他常用方法

unordered_set，可以用来处理只去重但不排序的需求


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

* 删除区间 [fist, last) 内元素

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


# map

**map 内部以红黑树实现，在建立映射的过程中自动实现从小到大的排序**

## map 定义

单独定义一个map:

map<type1, type2> mp;

**易错：**若是字符串到整形的映射，必须使用 string 不能使用 char 数组。

## map 访问

* 通过下标访问

```cpp
map<char, int> mp;
mp['c'] = 20;
cout << mp['c'];
```

* 通过迭代器访问

```cpp
for(map<char, int>::iterator it = mp.begin(); it != mp.end(); it ++){
    cout << it->first << it->second;
}
```

## map 添加

* insert

```cpp
map.insert(pair<string, int>("test", 1));
```

* 数组方式

**易错：** insert 方式键值重复时，无法插入。数组方式则会覆盖该键值对应值。

## map 删除

* 删除单个元素

map.erase(iterator it)，时间复杂度 O(1)

* 删除区间内元素

map.erase(iterator first, iterator last), 左闭右开

* 通过关键字删除

map.erase(key)，时间复杂度 O(logN)

* 删除全部元素

map.clear()

## map 查询

* find

mp.find(key), 返回迭代器，时间复杂度为 O(logN)

* count

mp.count(key), 判断关键字是否出现，但无法定位数据出现位置

## map 其他常用方法

* str.size()

map 映射对数，时间复杂度 O(1)

## unordered_map

unordered_map 以散列代替红黑树实现，可以用来处理只映射而不排序的需求，速度比 map 快得多

# queue

## queue 访问

* front()

访问队首元素

* back()

访问队尾元素

## queue 添加

push()

## queue 删除

pop()

# priority_queue

优先队列，底层使用堆实现，队首元素是当前队列中优先级最高的

需要头文件 queue

## priority_queue 访问

**只能通过 top() 访问队首元素**

## 优先级

### 基本数据类型

默认数字越大优先级越高

```cpp
priority_queue<int, vector<int>, less<int>> q;
```

vector<int> 承载底层数据结构堆的容器

less<int> 表示数字越大优先级越高

greater<int> 表示数字越小优先级越高

### 结构体

```cpp
struct fruit{
    int price;
    ...

    friend bool operator < (fruit f1, fruit f2){
        return f1.price < f2.price;
    }
}
```

**重载大于号会编译错误**

**优先队列与 sort 中 cmp 的效果相反**

如果结构体内数据庞大（出现了字符串或数组），建议使用引用来提高效率

```cpp
friend bool operator < (const fruit &f1, const fruit &f2){

}
```

# stack

## stack 访问

top()

## stack 添加

push()

## stack 删除

pop()

# pair 

## pair 定义

需要引用 utility / map 头文件

## pair 访问

pair 中只有两个元素，分别是 first 和 second，按照正常结构体方式访问即可

## pair 比较

先以 first 的大小作为标准，只有当 first 相等才去判别 second

# algorithm

## max() / min() / abs()

**注意：浮点数的绝对值使用 math 头文件下的 fabs**

## swap()

## reverse()

reverse(it, it2)

## fill()

把数组或容器中某一段区间赋为某个相同的值

fill(it1, it2, val)

## sort()

STL 中， 只有 vector、string、dequeu 可以 sort

默认从小到大

## lower_bound() / upper_bound()

lower_bound 左闭

upper_bound 右开

若没有寻找的元素，返回可以插入该元素的位置的迭代器
