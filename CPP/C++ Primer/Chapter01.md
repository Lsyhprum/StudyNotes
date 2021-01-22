### 编译过程

g++ 是 GNU 组织推出的 C++ 编译器，其在执行编译时需要经过 **预处理**、**编译**、**汇编** 和 **链接** 四步。

![](./pic/856214-20170831203214640-1792176674.png)

* 预处理：编译器对各种预处理命令进行处理，包括头文件包含、宏定义的扩展、条件编译的选择等 `g++ -E prog.cpp -o prog.i`
* 编译：将预处理得到的源代码文件，翻译成机器语言的目标程序，得到汇编文件 `g++ -S prog.i`
* 汇编：将汇编代码翻译成机器码 `g++ -c prog.s`
* 链接：处理可重定位文件，把各种符号引用和符号定义转换成为可执行文件中
的合适信息，通常是虚拟地址 `g++ prog.o`

g++ 编译常用命令

* 编译：`g++ prog.cpp -o prog`
* 编译多个文件：`g++ prog1.cpp prog2.cpp -o prog`
* 运行：`./prog`
* 查看运行状态：`echo $?`

```
用法：/usr/bin/ld [选项] 文件...
选项：
  -I 程序, --dynamic-linker 程序
                              将“程序”设为要使用的动态链接器
  -l 库名, --library 库名 搜索库“库名”
  -L 目录, --library-path 目录
                              将“目录”添加到库搜索路径中
  -o 文件, --output 文件  设置输出文件名
  -O                          优化输出文件
```

### 类

#### 类的成员函数

* \*this
  * 每个成员函数都有一个额外的，隐含的形参 this，this 总是指向当前对象。
  * 形参表后面的 const，改变了隐含的 this 形参的类型，如 bool same_isbn(const Sales_item &rhs) const，这种函数称为“常量成员函数”（this指向的当前对象是常量）。
  * 普通的非const成员函数：this是指向类类型的const指针（可以改变this所指向的值，不能改变this保存的地址）。
  * const成员函数：this是指向const类类型的const指针（既不能改变this所指向的值，也不能改变this保存的地址）。
  * `return *this;` 可以让成员函数连续调用。

#### 类的构造函数

* 默认构造函数：=default要求编译器合成默认的构造函数。(C++11)
* 初始化列表：冒号和花括号之间的代码： Sales_item(): units_sold(0), revenue(0.0) { }

#### 访问控制

* 使用 class或者 struct：都可以被用于定义一个类。唯一的却别在于访问权限。
  * 使用 class：在第一个访问说明符之前的成员是 priavte的。
  * 使用 struct：在第一个访问说明符之前的成员是 public的。

*TODO*

* 常亮成员函数

*参考*

* [gcc 编译过程](https://www.cnblogs.com/wjchao/p/7460375.html)