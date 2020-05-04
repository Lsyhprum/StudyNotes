# Java 基础

## 语言基础

## 运算符

## 修饰符

## 类型转换和造型

## 程序控制

## 面向对象

## 线程

## 输入/输出流

## 基础包

## 




























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