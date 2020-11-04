### Lambda 表达式

一个 Lambda 表达式表示一个可调用的代码单元，其形式为 ：

```
[capture list](parameter list) -> return type { function body }
```

其中参数列表和返回类型可忽略，但必须包含捕获列表和函数体。与普通函数不同，Lambda 必须使用尾置返回。


#### 捕获列表

一个 Lambda 只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在 Lambda 函数体中使用该变量。

* 值捕获

* 引用捕获

* 隐式捕获

    * [&, identifier_list] 隐式值捕获

    * [=, identifier_list] 显式值捕获


    

