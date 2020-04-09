# 背景

## Class 文件 和 Dex 文件

JVM -> *.class -> *.java / *.kt

Dalvik VM / ART VM -> *.dex -> *.class -> *.java / *.kt

Dex 由多个 Class 文件生成压缩文件，体积更小，适合移动端

## 方法数超限问题和解决方案

apk -> zip 解压

AndroidManifest.xml
assets/
res/
META-INF/
resources.arsc
classes.dex 

"Conversion to Dalvik format failed: Unable to execute dex:method ID not in [0,0xffff]: 65536"

方法数量超过 65536


.dex file

constant pool : 方法数超过 65535 （自己编写、引用第三方库）

* 方法数减少

* 混淆去除无用代码

* MultiDex

# 基本用法

* 5.0 以上

gradle

minSdkVersion 21
multiDexEnabled true

* 5.0 以下

* 编译后 APK 结构分析

classesDex1
classesDex2
...

# 原理解析

## 编译期原理

*java ->javac -> *.class -> dx 工具 -> classes.dex

--multi-dex:
    allows to generate several dex files if needed

*.class -> dx 工具 （--multi-dex) -> classes.dex / classes2.dex

## 运行期原理

### 分析入口

MultiDex.install()

### 整体流程

* 判读虚拟机是否支持 MultiDex
    * Dalvik 与 ART 虚拟机区别

        * Dalvik JIT 即时编译：java.vm.version < 2.0.0
            APK -> INSTALL -> *.Dex -> 启动 -> JIT -> 原生指令 -> 运行

            启动慢、运行慢，每次执行都会重新编译

        * ART AOT 提前编译：> 2.0.0

            ARK -> INSTALL(AOT) -> 原生指令 -> 启动 -> 执行

* Dex 解压

* Dex 安装

    *.class -> 类加载器 -> 运行

    dex 文件存储在 PathClassLoader 中 pathList 数组中

    通过反射 获取 PathClassLoader 中数组，将 Dex 添加进去

## 小结

java.vm.version > 2.0.0 -> ART -> 编译器支持

java.vm.version < 2.0.0 -> JIT 不支持 MultiDex -> APK 解压，二级文件列表注入 ClassLoader (通过反射获取数组，并添加)

# 热修复

## 代码热修复简介

APK 存在 bug 

* 重新发布 APK：重新上架发布、用户有感知

* 热修复：

修改 A.java -> 编译补丁包 -> 新的补丁包 -> 远程下发 -> 后台静默下载安装补丁包 -> 重新启动应用程序 -> 完成修复

无需重新发布应用

用户无感知

## 代码热修复原理

### 生成代码补丁包

ToBeFixed.java -> javac -> *.class -> dx -> patch.dex

### 注入补丁

patch.dex 插入到 dex 数组最前面

## 实现热修复

## 小结

# ANR 问题

多 dex 解压，注入，占用主线程执行，超过 5 秒未响应，ANR （Application Not Responding)问题

## 优化方案


