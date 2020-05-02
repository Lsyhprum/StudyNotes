# pytorch 和 tensorflow 区别

tensorflow 把 计算 和 运算图 分开处理

|      |     pytorch |   tensorflow   |
| :--------: | :--------:| :------: |
| 计算图分类    |   动态计算图 |  静态计算图  |
| 计算图定义    |   运行时定义 |  提前定义  |
| 调试    |   python开发工具  |  Tensorflow 开发工具  |
| 开发公司    |   Facebook |  Google  |

# Math Background

向量：一列数

矩阵：二维向量

张量：三维向量

神经网络的核心是向量、矩阵、张量的运算

# 神经网络

* 输入层、隐藏层、输出层

* 正向传递  

* 反向传递-> 梯度运算

# 神经网络训练过程

* 定义神经网络

* 迭代输入数据

* 神经网络计算输出

* 计算损失

* 反向传递梯度到网络的参数

* 更新网络权重

# 神经网络损失函数

L1 mean absolute loss

MSE mean squared loss

cross entropy loss

KL

# 知识要点

数据加载与归一

* 把训练数据导入到神经网络中并对神经网络训练

* 图像训练数据一般较大，无法加载所有数据

    * mini-batch 加载训练

        * mini-batch 加载训练数据集中一部分

        * mini-batch 数据不重叠

        * 所有训练数据集中数据都加载并训练完一次称为一个epoch

* 图像数据像素一般在 【0-255】
* 训练神经网络时，经常把输入数据值变成【0，1】或【-1,1】间

* torchvision.dataset 加载公共数据集、私人数据集

* 数据归一 torchvision.transforms

定义神经网络

定义损失函数

训练、测试神经网络

神经网络存储与读取



