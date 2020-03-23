# 神经网络入门

## 神经元

![神经元](https://github.com/Lsyhprum/StudyNotes/blob/master/%E6%B7%B1%E5%BA%A6%E5%AD%A6%E4%B9%A0%E4%B9%8B%E7%A5%9E%E7%BB%8F%E7%BD%91%E7%BB%9C%E7%AE%97%E6%B3%95%E5%8E%9F%E7%90%86/img/nn.png)

<img src="https://latex.codecogs.com/gif.latex?h_{W,b}(x)=f(\sum^3_{i=1}W_ix_i+b)">

W: 权重，表示该特征的重要程度

x: 特征

f: 激活函数，增加神经网络的表达能力

将 b 看作一项权重，特征增加一个额外项 1，公式则为

<img src="https://latex.codecogs.com/gif.latex?$h_{W,b}(x)=f(W^Tx)$">

## 逻辑回归模型

### 激活函数 sigmoid

![Sigmoid](https://github.com/Lsyhprum/StudyNotes/blob/master/%E6%B7%B1%E5%BA%A6%E5%AD%A6%E4%B9%A0%E4%B9%8B%E7%A5%9E%E7%BB%8F%E7%BD%91%E7%BB%9C%E7%AE%97%E6%B3%95%E5%8E%9F%E7%90%86/img/sigmoid.png)

### 二分类逻辑回归模型

定义概率，相当于做归一化

Y = 0

<img src="https://latex.codecogs.com/gif.latex?P(Y=0|x)=\frac{1}{1+e^{-w^Tx}}">

Y=1

<img src="https://latex.codecogs.com/gif.latex?P(Y=1|x)=\frac{e^{-w^Tx}}{1+e^{-w^Tx}}">

### 多分类逻辑回归模型

* W 从向量扩展成矩阵

* 输出 W*x 变成向量

<img src="https://latex.codecogs.com/gif.latex?P(Y=k|x)=\frac{e^{-w_k^Tx}}{1+\sum^{k-1}_1e^{-w_k^Tx}}%20k=1,2,..K-1">

<img src="https://latex.codecogs.com/gif.latex?P(Y=k|x)=\frac{1}{1+\sum^{k-1}_1e^{-w_k^Tx}} k=K">



## 神经网络训练







## 神经元->多输出




## 目标函数

衡量对数据的拟合程度 loss

多类：
类别值——one-hot 编码， 类别值作为索引，只有一个值为1

### 常用损失函数

* 平方差损失

* 交叉熵损失:衡量两个分布差距，适合多分类

神经网络训练的目的：使损失函数最小


## 梯度下降算法

<img src="https://latex.codecogs.com/gif.latex?\theta=\theta-\alpha\frac{\partial{L(x,y)}}{\partial{\theta}}">

theta: 参数（w,b)

alpha: 学习率

# loss 和 acc 区别