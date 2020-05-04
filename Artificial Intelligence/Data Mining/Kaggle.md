# Kaggle 流程、方法和技巧总结

## 探索性数据分析

* 统计基本信息：最大最小值，中位数，均值..，使用 **DataFrame.describe**

* 单个特征可视化：对单个特征进行可视化，使用 **DataFrame.count**
  * 直观地获取数据特征是否与先验吻合
  * 缺少先验的特征可以知道该变量的重要性
    * 存在数据缺失时，是否取某些值的样本经常有缺失值


* 多个特征比较：对多个变量进行相关性分析，可视化相关性矩阵

## 预处理

主要是对 异常值和缺失值 的处理

### 异常值

### 缺失值

* 删除样本：缺失值随机，且去除后仍有足够数据
* 删除特征：特征缺失率超过 50%，丢弃
* 均值、中值、众数填补：数据波动不大，且变量对目标变量影响不大时
* 预测值填补

## 模型和特征工程

### 处理定性特征

* 将定量变量转化为定性变量
* 对类别进行编码
* 平均数编码
* 类别出现次数较少，或每个类出现一次：丢弃、合并..
* 有序/无序

### 处理定量特征

* 标准化
* 归一化
* 非线性变换


**标准化和归一化区别：标准化作用于每个特征列，归一化作用于每一行**

### 构建新特征

* 交叉特征：多个特征进行组合




## 模型选择和评价


* 结果提交型：XGBoost, lightGBM, 进行模型 Ensemble
* 线性模型：SVM,神经网络和决策树模型
* 交叉验证，调参，Evaluation Metrics，Validation Curve and Learning Curve。
工程中做ensemble的方法。









* 机器学习常用算法

* 常用工具

* 建模与问题解决流程

    * 了解场景和目标
    * 了解评估准则
    * 认识数据
    * 数据预处理、清洗、调权
    * 特征工程
    * 模型选择
    * 寻找最佳超参数：交叉验证
    * 模型分析与模型融合

    * 拿到数据怎么了解数据（可视化）
    * 选择贴切的机器学习方法
    * 过/欠拟合 解决方法
    * 损失函数优缺点及选择

数据（特征）最重要 70%   -> 模型

* Kaggle wiki

* 简单案例


分类：

线性方法

决策树  分治的思想       非黑盒、去除无关特征     只能线性分割数据、贪婪算法（弱分类器）

Ensemble(集成) 算法框架 ： Bagging   Random Forest   Boosting

组合  ---> mini batch




神经网络




# 预处理信息

1. NaN
2. 英文单词  数字化
3. index 等无意义数据（噪音）

crosstab