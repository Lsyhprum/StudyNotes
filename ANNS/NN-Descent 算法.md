# NN-Descent 算法 —— Efficient K-Nearest Neighbor Graph Construction for Generic Similarity Measures

**NN-Descent 算法** 是一种构建 **近似 K 近邻图** 的算法。主要用于解决之前基于 K 近邻图的几种方法所存在的问题，以下是论文中提到的几个缺点：

* 数据规模小: Brute-force 时间复杂度为 O(n^2), 不适合大数据集
* 适用特定相似度度量标准
* 不支持并行计算：构建全局索引难以进行并行计算
* 计算成本高：LSH 为了获得精确结果需要付出较高计算成本，且对于不同相似度度量标准需设计不同散列函数

NN-Descent 算法主要思想十分简单：**邻居的邻居更可能是邻居**。

即在初始 K-NN 图中，通过探索每个点的邻居的邻居来提升结果的召回率。

## 理论推导

K = c^3

对于数据集 V，构建初始近似 K-NN 图 B。对于其中一个数据点 v，B[v] 表示 v 的 K 个最近邻，B'[v] 表示 v 的邻居的邻居的集合。

在此证明通过 NN-descent 算法将 v 的 K 近邻最大距离减半的可能性：

对于 $B_{r/2}(v)$ 中的一点 u, 假设从 B'[v] 中找到至少一点 v' 满足 $v' \in B_{r/2}(v)$ 可得:

* $v' \in B_r(v), P{v' \in B[v]} \ge K/|B_r(v)|$
  * 若 v 的 K 个邻居都在 $B_r(v)$ 中取的话，则共有 $\sum^K_{|B_r(v)|}$ 种情况，而 $B_r(v)$ 中存在一点不是 v 的邻居的情况有 $\sum^K_{|B_r(v)|-1}$ 种情况。$B_r(v)$ 中存在一点不是 v 的邻居的概率为 $\frac{\sum^K_{|B_r(v)|-1}}{\sum^K_{|B_r(v)|}}$，即 $\frac{|B_r(v)|-K}{|B_r(v)|}$
  * $B_r(v)$ 中一点是 v 的邻居的概率为 $1-\frac{|B_r(v)|-K}{|B_r(v)|}$，即 $\frac{K}{|B_r(v)|}$
  * 故 v' 是 v 的邻居的概率大于等于 $K/|B_r(v)|$
* $d(u,v') \le d(u,v) + d(v, v') \le r, P{u \in B[v']} \ge \frac{K}{B_r(v')}$
  * $B_r(v')$ 中一点是 v' 的邻居的概率为 $\frac{K}{|B_r(v')|}$
  * u 与 v' 的距离小于 r, 故 u 是 v' 的邻居的概率大于等于 $\frac{K}{|B_r(v')|}$
* $|B_r(v)| \le c|B_{\frac{r}{2}}(v)|, |B_r(v')| \le c|B_{\frac{r}{2}}(v')| \le c|B_r(v)| \le c^2|B_{r/2}(v)|$
  

由以上 3 个不等式和各事件的独立性可得：

$P{v' \in B[v] ^ u \in B[v']} \ge K/|B_{r/2}(v)|^2$

即对于 v' , 它既是 v 的邻居又是 u 的方向邻居的概率大于等于 K/|B_r/2(v)|^2

...

只要取足够大的 K，就可以通过探索每个对象邻居的邻居来达到构建高质量近似 K 近邻图的作用。




### 局部连接

### 增量搜索

### 采样

### 提前终止

## Map-Reduce 实现


*参考*：

[NN-Descent构建K近邻图——论文超详细注解](https://blog.csdn.net/whenever5225/article/details/105598694)


