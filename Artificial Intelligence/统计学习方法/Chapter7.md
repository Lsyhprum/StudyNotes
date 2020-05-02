
SVM 有三宝：间隔、对偶、核技巧

SVM: hard-margin SVM   soft-margin SVM  kernel SVM

hard-margin SVM 最大间隔分类器










支持向量机(support vector machines)是一种二分类模型，基本模型是定义在特征空间上的 **间隔最大的** 线性分类器。

<div align="center"> <img src="./pic/v2-0d6eb1459f72940dc932795f345bae06_b.jpg" width="300"/> </div><br>

支持向量机还包括**核技巧**， 这使它称为实质上的**非线性分类器**。

支持向量机包含由简至繁的模型，线性可分支持向量机、线性支持向量机、非线性支持向量机。

训练数据集样本点中与分离超平面距离最近的样本点称为支持向量。

# 线性可分支持向量机

## 模型

决策函数
$$
f(x)=sign(w^*\cdot x+b^*)
$$

## 策略

#### 函数间隔

对于给定数据集$T$和超平面$(w,b)$，定义超平面$(w,b)$关于样本点$(x_i,y_i)$的函数间隔为
$$
\hat \gamma_i=y_i(w\cdot x_i+b)
$$
定义超平面$(w,b)$关于训练数据集$T$的函数间隔为超平面$(w,b)$关于$T$中所有样本点$(x_i,y_i)$的函数间隔之最小值，即
$$
\hat \gamma=\min_{i=1,\cdots,N}\hat\gamma_i
$$

函数间隔可以表示分类预测的**正确性**及**确信度**。

但如果成比例的改变 w 和 b, 分离超平面没有改变，函数间隔却改变。因此需要对超平面 w 加入某些约束，如规范化，使得间隔确定，此时函数间隔成为几何间隔。

#### 几何间隔

对于给定数据集$T$和超平面$(w,b)$，定义超平面$(w,b)$关于样本点$(x_i,y_i)$的几何间隔为
$$
\hat \gamma_i=y_i(\frac{w}{||w||}\cdot x_i+ \frac{b}{||w||})
$$

#### 间隔最大化

支持向量机学习的基本想法是求解能够正确划分训练数据集并且几何间隔最大的分离超平面。

对线性可分分离超平面有无穷个（等价于感知机），几何间隔最大的分离超平面唯一。

对训练数据集找到几何间隔最大的超平面意味着以充分大的确信度对训练数据进行分类。也就是说，不仅将正负实例点分开，而且对最难分的实例点（离超平面最近的点）也有足够大的确信度将它们分开。这样的超平面应该对未知的新实例有很好的分类预测能力。

<div align="center"> <img src="./pic/6cbb8645gw1ewo3pjicrfj207105vjrd.jpg" width="300"/> </div><br>

在上图中，有A、B、 C三个点，表示3个实例，均在分离超平面的正类一侧，预测它们的类。点A距分离超平面较远，若预测该点为正类，就比较确信预测是正确的；点C距分离超平面较近，若预测该点为正类就不那么确信；点B介于点A与C之间，预测其为正类的确信度也在A与C之间。

求解几何间隔最大的分离超平面，可表示为：

$$\max_{w, b} \gamma$$

$$y_i \{ \frac{w}{||w||} \cdot x_i + \frac{b}{||w||} \} \geq \gamma$$

即

$$\max_{w, b} \frac{\hat\gamma}{||w||}$$

$$y_i \{ \frac{w}{||w||} \cdot x_i + \frac{b}{||w||} \} \geq \frac{\hat\gamma}{||w||}$$

函数间隔 $\hat\gamma$ 作为常数约去，且由于最大化 $\frac{1}{||w||}$ 和最小化 $\frac{1}{2}||w||^2$ 等价，于是得到线性可分支持向量机最优化问题：

$$\min_{w, b} \frac{1}{2}||w||^2$$

$$y_i \{ w \cdot x_i + b \} - 1 \geq 0$$


## 算法

#### 最大间隔法






#### 对偶算法

通过求解对偶问题得到原始问题的最优解，即对偶算法：

* 对偶问题往往更容易求解
* 自然引入核函数，进而推广到非线性分类问题

针对每个不等式约束，定义拉格朗日乘子$\alpha_i\ge0​$，定义拉格朗日函数

$$
L(w,b,\alpha)=\frac{1}{2}||w||^2-\sum_{i=1}^N\alpha_i y_i(w\cdot x_i+b)+\sum_{i=1}^N\alpha_i
$$

其中$\alpha=(\alpha_1,\alpha_2,\dots,\alpha_N)^T​$为拉格朗日乘子向量

根据**拉格朗日对偶性**，原始问题的**对偶问题是极大极小问题**:
$$
\max\limits_\alpha\min\limits_{w,b}L(w,b,\alpha)
$$

关于对偶问题，引用Wikipedia中的描述

> [Duality (optimization)](https://en.wikipedia.org/wiki/Duality_(optimization))
>
> In [mathematical optimization](https://en.wikipedia.org/wiki/Mathematical_optimization) theory, **duality** or the **duality principle** is the principle that [optimization problems](https://en.wikipedia.org/wiki/Optimization_problem) may be viewed from either of two perspectives, the **primal problem** or the **dual problem**. The solution to the dual problem provides a lower bound to the solution of the primal (minimization) problem.[[1\]](https://en.wikipedia.org/wiki/Duality_(optimization)#cite_note-Boyd-1) However in general the optimal values of the primal and dual problems need not be equal. Their difference is called the [duality gap](https://en.wikipedia.org/wiki/Duality_gap). For [convex optimization](https://en.wikipedia.org/wiki/Convex_optimization) problems, the duality gap is zero under a [constraint qualification](https://en.wikipedia.org/wiki/Constraint_qualification) condition.

**$\min\limits_{w,b}L(w,b,\alpha)$**

$$\nabla_wL(w,b,\alpha)=w-\sum_{i=1}^N \alpha_i y_i x_i = 0$$

$$\nabla_bL(w,b,\alpha)=-\sum_{i=1}^N \alpha_i y_i = 0$$

得

$$w=\sum_{i=1}^N \alpha_i y_i x_i$$

$$\sum_{i=1}^N \alpha_i y_i = 0$$

**$\max\limits_\alpha L(w,b,\alpha)$**

$$
\min\limits_\alpha \frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_j(x_i\cdot x_j)-\sum_{i=1}^N\alpha_i\\
s.t. \ \ \ \sum_{i=1}^N\alpha_iy_i=0\\
\alpha_i\geqslant0, i=1,2,\dots,N
$$


对于任意线性可分的两组点，他们在分类超平面上的投影都是线性不可分的。

$\alpha$不为零的点对应的实例为支持向量，通过支持向量可以求得$b$值

核心公式两个
$$
\begin{align}
w^*&=\sum_{i=1}^{N}\alpha_i^*y_ix_i\\
b^*&=\color{red}y_j\color{black}-\sum_{i=1}^{N}\alpha_i^*y_i(x_i\cdot \color{red}x_j\color{black})
\end{align}
$$
这里面比较重要的是$b^*$的公式的理解，通过$\arg\max \alpha^*$实现，因为支持向量共线，所以通过任意支持向量求解都可以。






















## [2] 线性支持向量机

### 问题描述

$$
\begin{align}
\min_{w,b,\xi} &\frac{1}{2}\left\|w\right\|^2+C\sum_{i=1}^N\xi_i\\
s.t. \ \ \ &y_i(w\cdot x_i+b)\geqslant1-\xi_i, i=1,2,\dots,N\\
&\xi_i\geqslant0,i=1,2,\dots,N
\end{align}
$$

### 对偶问题描述

原始问题里面有两部分约束，涉及到两个拉格朗日乘子向量
$$
\begin{align}
\min_\alpha\ &\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_j(x_i\cdot x_j)-\sum_{i=1}^N\alpha_i\\
s.t.\ \ \ &\sum_{i=1}^N\alpha_iy_i=0\\
&0\leqslant \alpha_i \leqslant C,i=1,2,\dots,N
\end{align}
$$
通过求解对偶问题， 得到$\alpha$，然后求解$w,b$的过程和之前一样

注意， 书后总结部分，有这样一句描述：**线性支持向量机的解$w^*$唯一但$b^*$不一定唯一**

线性支持向量机是线性可分支持向量机的超集。

### 算法

#### 软间隔最大化

>对于线性支持向量机学习来说
>模型为分离超平面$w^*\cdot x+b^*=0$
>
>决策函数为$f(x)=sign(w^*\cdot x+b^*)$
>
>学习策略为软间隔最大化
>
>学习算法为凸二次规划



#### 合页损失

另一种解释，最小化目标函数

$$\min\limits_{w,b} \sum\limits_{i=1}^N\left[1-y_i(w\cdot x+b)\right]_++\lambda\left\|w\right\|^2$$

其中

- 第一项是经验损失或经验风险，函数$L(y(w\cdot x+b))=[1-y(w\cdot x+b)]_+$称为合页损失，可以表示成$L = \max(1-y(w\cdot x+b), 0)$
- 第二项是**系数为$\lambda$的$w$的$L_2$范数的平方**，是正则化项

书中这里通过定理7.4说明了用合页损失表达的最优化问题和线性支持向量机原始最优化问题的关系。
$$
\begin{align}
\min_{w,b,\xi} &\frac{1}{2}\left\|w\right\|^2+C\sum_{i=1}^N\xi_i\\
s.t. \ \ \ &y_i(w\cdot x_i+b)\geqslant1-\xi_i, i=1,2,\dots,N\\
&\xi_i\geqslant0,i=1,2,\dots,N
\end{align}
$$
等价于
$$
\min\limits_{w,b} \sum\limits_{i=1}^N\left[1-y_i(w\cdot x+b)\right]_++\lambda\left\|w\right\|^2
$$
证明：

令合页损失$\left[1-y_i(w\cdot x+b)\right]_+=\xi_i$，合页损失非负，所以有$\xi_i\ge0$，这个对应了原始最优化问题中的**一个约束【1】**。

还是根据合页损失非负，当$1-y_i(w\cdot x+b)\leq\color{red}0​$的时候，有$\left[1-y_i(w\cdot x+b)\right]_+=\color{red}\xi_i=0​$，所以有

$1-y_i(w\cdot x+b)\leq\color{red}0=\xi_i$，这对应了原始最优化问题中的**另一个约束【2】**。

所以，在满足这**两个约束【1】【2】**的情况下，有
$$
\begin{aligned}
\min\limits_{w,b} &\sum\limits_{i=1}^N\left[1-y_i(w\cdot x+b)\right]_++\lambda\left\|w\right\|^2\\
\min\limits_{w,b} &\sum\limits_{i=1}^N\xi_i+\lambda\left\|w\right\|^2\\
\min\limits_{w,b} &\frac{1}{C}\left(\frac{1}{2}\left\|w\right\|^2+C\sum\limits_{i=1}^N\xi_i\right), with \  \lambda=\frac{1}{2C}\\
\end{aligned}
$$
看下下面这个图，其中合页损失和感知机损失函数之间的关系，合页损失要求函数间隔大于1的时候才没有损失（loss=0），而感知机只要函数间隔大于0就认为没有损失，所以说合页损失对学习有更高的要求。

再解释下，对于线性支持向量机大于一的意思是符号为正，且值要大于1；对于感知机大于零的意思是符号为正，就可以了。

![test](assets/fig76.png)



```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-3,3,601)
# perceptron loss
y1 = list(map(lambda x: max(0, -x), x))
# hinge loss
y2 = list(map(lambda x: max(0,1-x), x))
# 0-1 loss
y3 = list(map(lambda x:1 if x <= 0 else 0, x))
# lr loss
y4 = list(map(lambda x:np.log2(1+np.exp(-x)), x))
# adaboost
y5 = list(map(lambda x:np.exp(-x), x))
plt.plot(x,y1,'--', label='perceptron loss')
plt.plot(x,y2, '-', label='hinge loss' )
plt.plot(x,y3, '-', label='0-1 loss')
plt.plot(x,y4, '-', label='lr')
plt.plot(x,y5, '-', label='adaboost')

plt.legend()
plt.xlim(-3,3)
plt.ylim(0,3)
plt.xlabel("functional margin")
plt.ylabel("loss")
plt.savefig("test.png")
plt.show()
```



以上：

- 0-1损失函数不是连续可导
- 合页损失认为是0-1损失函数的上界，在[AdaBoost](../CH08/README.md)中也有说明，指数损失也是0-1损失函数的上界，在[感知机](../CH02/README.md)中有提到`损失函数的自然选择是误分类点的个数`，这句在最开始见到的时候，可能不一定有上面图片的直觉。注意在本书[CH12](../CH12/README.md)中也有这个图，可以对比理解下。
- 感知机误分类驱动， 选择函数间隔作为损失考虑分类的正确性，合页损失不仅要考虑分类正确， 还要考虑确信度足够高时损失才是0.

## [3]非线性支持向量机
核技巧的想法是在学习和预测中只定义核函数$K(x,z)$，而不是显式的定义映射函数$\phi$

通常，直接计算$K(x,z)$比较容易， 而通过$\phi(x)$和$\phi(z)$计算$K(x,z)$并不容易。
$$
\begin{align}
W(\alpha)=\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_jK(x_i,x_j)-\sum_{i=1}^N\alpha_i\\
f(x)=sign\left(\sum_{i=1}^{N_s}\alpha_i^*y_i\phi(x_i)\cdot \phi(x)+b^*\right)=sign\left(\sum_{i=1}^{N_s}\alpha_i^*y_iK(x_i,x)+b^*\right) 
\end{align}
$$
学习是隐式地在特征空间进行的，不需要显式的定义特征空间和映射函数。这样的技巧称为核技巧，核技巧不仅引用于支持向量机，而且应用于其他统计学习问题。

TODO：字符串核函数
### 核函数

例7.3 主要是为了说明

> 对于给定的核$K(x,z)$，特征空间$\mathcal H$和映射函数$\phi(x)$的取法并不唯一，可以取不同的特征空间，即便是同一特征空间里也可以取不同的映射

注意这个例子里面$\phi(x)$实现了从低维空间到高维空间的映射。
$$
K(x,z)=(x\cdot z)^2\\
\cal{X}=\R^2, x=(x^{(1)},x^{(2)})^T\\
\cal{H}=\R^3, \phi(x)=((x^{(1)})^2, \sqrt2x^{(1)}x^{(2)}, (x^{(2)})^2)^T\\
\cal{H}=\R^4, \phi(x)=((x^{(1)})^2, x^{(1)}x^{(2)}, x^{(1)}x^{(2)}, (x^{(2)})^2)^T\\
$$

这里看下：

- 理解下$\R^n$
- 理解下计算$K$要比通过$\phi$计算$K$要容易
- 核函数的定义相当于给出了$\phi(x)\cdot\phi(z)$的结果，而没有显式的给出$\phi$的定义，$\phi$实现了从输入空间到特征空间的变换，所以说，学习是隐式的从特征空间中进行的，不需要显式的定义特征空间和映射函数，这样的技巧称为核技巧，通过线性分类学习方法和核函数解决非线性问题。

核具有再生性即满足
$$
K(\cdot,x)\cdot f=f(x)\\
K(\cdot,x)\cdot K(\cdot, z)=K(x,z)
$$
称为再生核


### 问题描述

~~和线性支持向量机的问题描述一样~~，注意，这里是有差异的，将向量内积替换成了核函数，而后续SMO算法求解的问题是该问题。

构建最优化问题：
$$
\begin{align}
\min_\alpha\ &\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_jK(x_i,x_j)-\sum_{i=1}^N\alpha_i\\
s.t.\ \ \ &\sum_{i=1}^N\alpha_iy_i=0\\
&0\leqslant \alpha_i \leqslant C,i=1,2,\dots,N
\end{align}
$$


求解得到$\alpha^*=(\alpha_1^*,\alpha_2^*,\cdots,\alpha_N^*)^T$

选择$\alpha^*$的一个正分量计算
$$
b^*=y_j-\sum_{i=1}^N\alpha_i^*y_iK(x_i,x_j)
$$
构造决策函数
$$
f(x)=sign\left(\sum_{i=1}^N\alpha_i^*y_iK(x,x_i)+b^*\right)
$$







## 学习算法：序列最小最优化

支持向量机的学习问题可以形式化为求解凸二次规划问题，这部分主要参考文献是文献5[^1]

### 问题描述

$$
\begin{aligned}
\min_\alpha\ &\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_jK(x_i,x_j)-\sum_{i=1}^N\alpha_i\\
s.t.\ \ \ &\sum_{i=1}^N\alpha_iy_i=0\\
&0\leqslant \alpha_i \leqslant C,i=1,2,\dots,N
\end{aligned}
$$

这个问题中，变量是$\alpha$，一个变量$\alpha_i$对应一个样本点$(x_i,y_i)$，变量总数等于$N$



### KKT 条件

KKT条件是该最优化问题的充分必要条件。这个参考[附录C](../APP/README.md)



### SMO算法

整个SMO算法包括两~~步骤~~**部分**：

1. 求解两个变量二次规划的解析方法
1. 选择变量的启发式方法

$$
\begin{aligned}
\min_\alpha\ &\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\alpha_i\alpha_jy_iy_j(x_i\cdot x_j)-\sum_{i=1}^N\alpha_i\\
s.t.\ \ \ &\sum_{i=1}^N\alpha_iy_i=0\\
&0\leqslant \alpha_i \leqslant C,i=1,2,\dots,N
\end{aligned}
$$

注意，这里是**两个部分**，而不是先后的两个步骤。

#### Part I

两变量二次规划求解

选择两个变量$\alpha_1,\alpha_2​$

由等式约束可以得到

$\alpha_1=-y_1\sum\limits_{i=2}^N\alpha_iy_i​$

所以这个问题实质上是单变量优化问题。
$$
\begin{align}
\min_{\alpha_1,\alpha_2} W(\alpha_1,\alpha_2)=&\frac{1}{2}K_{11}\alpha_1^2+\frac{1}{2}K_{22}\alpha_2^2+y_1y_2K_{12}\alpha_1\alpha_2\nonumber\\
&-(\alpha_1+\alpha_2)+y_1\alpha_1\sum_{i=3}^Ny_i\alpha_iK_{il}+y_2\alpha_2\sum_{i=3}^Ny_i\alpha_iK_{i2}\\
s.t. \ \ \ &\alpha_1y_1+\alpha_2y_2=-\sum_{i=3}^Ny_i\alpha_i=\varsigma\\
&0\leqslant\alpha_i\leqslant C, i=1,2
\end{align}
$$

上面存在两个约束：

1. **线性**等式约束
1. 边界约束

这里有个$\color{red}配图$，其中这样一段描述**等式约束使得$(\alpha_1,\alpha_2)$在平行于盒子$[0,C]\times [0,C]$的对角线的直线上**

这句怎么理解？

$y_i\in \mathcal Y=\{+1,-1\}$所以又等式约束导出的关系式中两个变量的系数相等，所以平行于对角线。

要时刻记得，支持向量机是个二类分类模型。后面有研究者对这个问题做多分类扩展，应该不是简单的OvO或者OvR吧，不然能专门发文章写一下？

书中**剪辑**的概念对应了文献[^1]中的**clipped**，剪辑的操作对应的是clipping，也叫truncation或者shortening。

#### Part II

变量的选择方法

1. 第一个变量$\alpha_1$
   外层循环
   违反KKT条件**最严重**的样本点
1. 第二个变量$\alpha_2$
   内层循环
   希望能使$\alpha_2$有足够大的变化
1. 计算阈值$b$和差值$E_i$

### 算法7.5

> 输入：训练数据集$T={(x_1,y_1),(x_2,y_2),\dots, (x_N,y_N)}$，其中$x_i\in\mathcal X=\bf R^n, y_i\in\mathcal Y=\{-1,+1\}, i=1,2,\dots,N$,精度$\epsilon$
>
> 输出：近似解$\hat\alpha$
>
> 1. 取初值$\alpha_0=0$，令$k=0$
>
> 1. **选取**优化变量$\alpha_1^{(k)},\alpha_2^{(k)}$，解析求解两个变量的最优化问题，求得最优解$\alpha_1^{(k+1)},\alpha_2^{(k+1)}$，更新$\alpha$为$\alpha^{k+1}$
>
> 1. 若在精度$\epsilon$范围内满足停机条件
>    $$
>    \sum_{i=1}^{N}\alpha_iy_i=0\\
>    0\leqslant\alpha_i\leqslant C,i=1,2,\dots,N\\
>    y_i\cdot g(x_i)=
>    \begin{cases}
>    \geqslant1,\{x_i|\alpha_i=0\}\\
>    =1,\{x_i|0<\alpha_i<C\}\\
>    \leqslant1,\{x_i|\alpha_i=C\}
>    \end{cases}\\
>    g(x_i)=\sum_{j=1}^{N}\alpha_jy_jK(x_j,x_i)+b
>    $$
>    则转4,否则，$k=k+1$转2
>
> 1. 取$\hat\alpha=\alpha^{(k+1)}$

TODO:

其实这里支持向量机的几个核心的思想是不难理解的，这里涉及到的主要是求解二次规划问题么？

## 扩展

### 对比支持向量机和提升方法

参考下[CH08](../CH08/README.md)



### 对比二次规划求解工具和SMO

## 习题

### 7.3

线性支持向量机还可以定义成以下形式：
$$
\begin{aligned}
\min_{w,b,\xi}\ &\frac{1}{2}||w||^2+C\sum_{i=1}^{N}\xi_i^2\\
s.t.\ &y_i(w\cdot x_i+b)\ge1-\xi_i, i=1,2,\cdots,N\\
&\xi_i\ge 0, i=1,2,\cdots,N
\end{aligned}
$$

求其对偶形式。