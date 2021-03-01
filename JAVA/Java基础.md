# Java 基础

## 语言基础

### Java 语言特点

* 简单性（剔除 C++ 中头文件、指针、操作符重载、虚基类等语法）；
* 面向对象（封装，继承，多态）；
* 平台无关性（Java 虚拟机实现平台无关性）；
* 健壮性（Java 采用的指针模型可以消除重写内存和损坏数据的可能性）；
* 安全性；
* 支持多线程（ C++ 语言没有内置的多线程机制，因此必须调用操作系统的多线程功能来进行多线程程序设计，而 Java 语言却提供了多线程支持）；
* 支持网络编程并且很方便（ Java 语言诞生本身就是为简化网络编程设计的，因此 Java 语言不仅支持网络编程而且很方便）；
  编译与解释并存；

### JDK 与 JRE

JDK 是 Java Development Kit 缩写，它是功能齐全的 Java SDK。它拥有 JRE 所拥有的一切，还有编译器（javac）和工具（如 javadoc 和 jdb）。它能够创建和编译程序。

JRE 是 Java 运行时环境。它是运行已编译 Java 程序所需的所有内容的集合，包括 Java 虚拟机（JVM），Java 类库，java 命令和其他的一些基础构件。但是，它不能用于创建新程序。

如果你只是为了运行一下 Java 程序的话，那么你只需要安装 JRE 就可以了。如果你需要进行一些 Java 编程方面的工作，那么你就需要安装 JDK 了。但是，这不是绝对的。有时，即使您不打算在计算机上进行任何 Java 开发，仍然需要安装 JDK。例如，如果要使用 JSP 部署 Web 应用程序，那么从技术上讲，您只是在应用程序服务器中运行 Java 程序。那你为什么需要 JDK 呢？因为应用程序服务器会将 JSP 转换为 Java servlet，并且需要使用 JDK 来编译 servlet。

### Java 和 C++的区别?

我知道很多人没学过 C++，但是面试官就是没事喜欢拿咱们 Java 和 C++ 比呀！没办法！！！就算没学过 C++，也要记下来！

* 都是面向对象的语言，都支持封装、继承和多态
* Java 不提供指针来直接访问内存，程序内存更加安全
* Java 的类是单继承的，C++ 支持多重继承；虽然 Java 的类不可以多继承，但是接口可以多继承。
* Java 有自动内存管理垃圾回收机制(GC)，不需要程序员手动释放无用内存
* 在 C 语言中，字符串或字符数组最后都会有一个额外的字符'\0'来表示结束。但是，Java 语言中没有结束符这一概念。 这是一个值得深度思考的问题，具体原因推荐看这篇文章： https://blog.csdn.net/sszgg2006/article/details/49148189

### 1.1.6. 为什么说 Java 语言“编译与解释并存”？

高级编程语言按照程序的执行方式分为编译型和解释型两种。简单来说，编译型语言是指编译器针对特定的操作系统将源代码一次性翻译成可被该平台执行的机器码；解释型语言是指解释器对源程序逐行解释成特定平台的机器码并立即执行。比如，你想阅读一本英文名著，你可以找一个英文翻译人员帮助你阅读， 有两种选择方式，你可以先等翻译人员将全本的英文名著（也就是源码）都翻译成汉语，再去阅读，也可以让翻译人员翻译一段，你在旁边阅读一段，慢慢把书读完。

Java 语言既具有编译型语言的特征，也具有解释型语言的特征，因为 Java 程序要经过先编译，后解释两个步骤，由 Java 编写的程序需要先经过编译步骤，生成字节码（*.class 文件），这种字节码必须由 Java 解释器来解释执行。因此，我们可以认为 Java 语言编译与解释并存。

### 源文件

* 源文件是一个包含 Java 代码的文本文件，以 .java 作为文件后缀名。源文件通过编译产生可执行的字节代码文件，即类文件，以 .class 作为文件后缀名。编译并运行一个源文件的示例如下：

> javac SourceFileName.java  // generate SourceFileName.class
> java SourceFileName  // do not add .class

* 一个源文件最多只能包含一个顶层的 public 类定义。
* 若源文件中存在一个顶层 public 类定义，则该源文件名必须与顶层的 public 类名一致。
  * jvm 为了提高查找类的速度，将类名与文件名一一对应。
* java.lang 包由系统自动引入，不需要明确引入就可使用其中的类。

### 关键字和标识符

* goto 和 const 是保留字，Java 中目前未被使用，但不能作为标识符。
* 标识符只能以字母、$ 或 _ 开头，随后的字符只能是字母、$ 和数字。

### 基本数据类型

Java 共有 8 种基本类型，其中 4 种整型，2 种浮点类型，1 种字符类型和 1 种真值类型。

|  类型   | 存储需求 |
| :-----: | :------: |
|  byte   |   8bit   |
|  short  |  16bit   |
|   int   |  32bit   |
|  long   |  64bit   |
|  float  |  32bit   |
| double  |  64bit   |
| boolean |   1bit   |
|  char   |  16bit   |

## 字符类型

* char 属于无符号整数型
* 由于 Unicode 字符超过了 65536 个，16 位 char 类型无法满足描述所有 Unicode 字符的需要，因此从 JDK 5.0 开始，采用代码点表示字符。代码点是指编码字符集中，字符所对应的数字。有效范围从U+0000到U+10FFFF。其中U+0000到U+FFFF为基本字符，U+10000到U+10FFFF为增补字符。代码单元是指对代码点进行编码得到的1或2个16位序列（UTF-16）。其中基本字符的代码点直接用一个相同值的代码单元表示，增补字符的代码点用两个代码单元进行编码，编码值来自U+D800到U+DFFF，这个范围内没有数字用于表示字符，因此程序可以识别出当前字符是单单元的基本字符，还是双单元的增补字符。
* 程序中尽量少使用 char 类型

#### 真值类型

与 c++ 不同的是，整数值和布尔值之间不能相互转换


#### 常量

Java 中利用关键字 final 声明常量。一旦被赋值以后，就不能再更改。一般使用大写。
在 Java 中若希望某个常量在类中多个方法中使用，称为类常量。可以使用关键字 static final 设置一个类常量。

> const 是 Java 保留的关键字

#### 数值类型转换

无信息丢失：byte->short, short->int, char->int, int->long, int->double

存在信息丢失：long->float, int->float

不可转换：float<->double

#### 不可变字符串

* Java 中 String 类对象不可改变，但编译器可以让字符串**共享**。

* Java 使用 equals 方法检测两个字符串是否内容相等。不能使用 == 判别内容是否相等，其作用是判别两字符串地址是否相同。

* 获取字符串中代码单元数量

> int n = string.length();

* 获取字符串中代码点数量

> int n = string.codePointCount(0, string.length());

* 获取指定位置代码单元

> char first = string.charAt(1);

* 获取第 i 个代码点

> int index = string.offsetByCodePoints(0, i);
> int cp = string.codePointAt(index);

#### 构建字符串

* StringBuilder : 不支持并发访问
* StringBuffer : 运行并发访问


### 参数传递

首先回顾一下在程序设计语言中有关将参数传递给方法（或函数）的一些专业术语。**按值调用(call by value)表示方法接收的是调用者提供的值，而按引用调用（call by reference)表示方法接收的是调用者提供的变量地址**。一个方法可以修改传递引用所对应的变量值，而不能修改传递值调用所对应的变量值。 它用来描述各种程序设计语言（不只是 Java)中方法参数传递方式。

Java 程序设计语言总是采用 **按值调用**。也就是说，方法得到的是所有**参数值的一个拷贝**，也就是说，方法不能修改传递给它的任何参数变量的内容。

*TODO*


























## 面向过程与面向对象区别

## JDK 和 JRE

JDK：Java Development Kit 的简称，java 开发工具包，提供了 java 的开发环境和运行环境。

JRE：Java Runtime Environment 的简称，java 运行环境，为 java 的运行提供了所需环境。

具体来说 JDK 其实包含了 JRE，同时还包含了编译 java 源码的编译器 javac，还包含了很多 java 程序调试和分析的工具。简单来说：如果你需要运行 java 程序，只需安装 JRE 就可以了，如果你需要编写 java 程序，需要安装 JDK。

## == 和 equals 区别

equals 本质上就是 ==，只不过 String 和 Integer 等重写了 equals 方法，改为了值比较。

未重写 equals 代码：
```java
public boolean equals(Object obj) {
    return (this == obj);
}
```

String equals 代码：
```java
public boolean equals(Object anObject) {
    if (this == anObject) {
        return true;
    }
    if (anObject instanceof String) {
        String anotherString = (String)anObject;
        int n = value.length;
        if (n == anotherString.value.length) {
            char v1[] = value;
            char v2[] = anotherString.value;
            int i = 0;
            while (n-- != 0) {
                if (v1[i] != v2[i])
                    return false;
                i++;
            }
            return true;
        }
    }
    return false;
}
```

## 两个对象的 hashCode() 相同， equals() 是否也为 true?

placeholder

## final 在 java 中有什么作用？

##