* 变量的作用域

    修改全局作用域 global


* 字符串
  
```python
s3 = """

hello 
world
"""

s1 = '\131\142'   # \ 跟八进制 、 16 进制 表示字符， \u Unicode 字符编码

s1 = r'\'hello, world!\''  # 不希望转义

# * 重复字符串
# + 拼接
```

* 切片

简单切片 

a[start:stop]

扩展切片

a[start:stop:step]

  * 当step为负数时，切片将其解释为从start出发以步长|step|逆序索引序列

```python

fruits[::-1] # 反向切片
```

[Python]切片完全指南(语法篇) - AyiStar的文章 - 知乎
https://zhuanlan.zhihu.com/p/79541418

* 生成器

```python
# 用这种语法创建列表之后元素已经准备就绪所以需要耗费较多的内存空间
f = [x ** 2 for x in range(1, 1000)]

# 每次需要数据的时候就通过内部的运算得到数据(需要花费额外的时间)
f = (x ** 2 for x in range(1, 1000))
```