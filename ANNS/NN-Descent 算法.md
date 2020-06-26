# NN-Descent 算法

相关论文：[Efficient K-Nearest Neighbor Graph Construction for Generic Similarity Measures]()

**NN-Descent 算法** 是一种构建 **近似 K 近邻图** 的算法。主要用于解决之前基于 K 近邻图的几种算法所存在的问题，以下是论文中提到的 4 个缺点：

* 时间复杂度高: Brute-force 时间复杂度为 $O(n^2)$, 不适合大数据集
* 标准适用情形少：只适用特定相似度度量标准
* 不支持并行计算：构建全局索引难以进行并行计算
* 计算成本高：LSH 为了获得精确结果需要付出较高计算成本，且对于不同相似度度量标准需设计不同散列函数

NN-Descent 致力于达成通用、可拓展、节省空间、快速、简单的算法。该算法主要思想十分简单：**邻居的邻居更可能是邻居**。即在初始 K-NN 图中，通过探索每个点的 **邻居的邻居** 来提升结果的召回率。

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

## 算法

### 基础算法

```
Data: dataset V, similarity oracle σ, K 
Result: K-NN list B                        // 候选集
begin 
  B[v] ←− Sample(V,K) × {∞}, ∀v ∈ V 
  loop 
    R ←− Reverse(B) 
    B1[v] ←− B[v] ∪ R[v], ∀v ∈ V;        // 将 v 候选集和 包含 v 的反向集混合
    c ←− 0                                 // update counter 
    for v ∈ V do 
      for u1 ∈ B1[v], u2 ∈ B1[u1] do     // 向 v 候选集中加入邻居的邻居
        l ←− σ(v, u2) 
        c ←− c +UpdateNN(B[v], <u2, l>)
    return B if c = 0                      // 未进行更新操作，返回结果集

function Sample(S, n)                      // 从数据集 S 中随机抽样 n 个点
  return Sample n items from set S

function Reverse(B)                        // 计算反向近邻集
begin 
  R[v] ←− {u | <v, · · ·> ∈ B[u]} ∀v ∈ V 
  returnR

function UpdateNN(H, <u, l, . . .>)        // 更新候选集
  Update K-NN heap H; 
  return 1 if changed, or 0 if not.
```

### 算法改进

#### 局部连接

让每一个对象探索它邻居的邻居的操作也可通过局部连接等价实现。局部连接可这样理解：给定一点v，它的邻居集为B¯¯¯¯[v]，在B¯¯¯¯[v]上的局部连接是计算每一对不同的p和q之间的相似性（p，q∈B¯¯¯¯[v]），并且根据此相似性更新B[p]与B[q]。通俗的将，局部连接就是每一个点介绍它的邻居去了解彼此。

局部连接能代替一个对象探索它邻居的邻居的操作吗？看下面的示例：

[]()

如图2所示，b∈BK(a)，c∈BK(b)。在算法1中，当探索到a时，我们需要比较a与c，当探索到c时，我们也需要比较a与c，这是 **冗余计算** 的一种情况，可通过索引编号的顺序来解决。同样地，a与c之间的比较可通过对B¯¯¯¯[b]进行局部连接来实现。

局部连接实现起来很简单，那么它有什么好处呢？

增强了数据的局部性，使执行更有效。如果每一个对象的邻居的个数平均为K¯¯¯¯¯，算法1每次迭代探索每一个对象的邻居的邻居时将接触到K¯¯¯¯¯2个点，而局部连接只需要接触K¯¯¯¯¯个点。
单机实施时，提升了cache的命中率，从而加速了K近邻图的构建。分布式实施时，能减少机器之间数据的复制。


#### 增量搜索

随着算法的执行，每一个对象的K近邻更新的幅度逐渐减小。而且，在某次迭代中参与比较的两个点，就更可能在之前的迭代中已经比较过了。这就造成冗余计算，而增量搜索就是要解决这个问题的。

给每一个点的K近邻列表中的每一个对象附加一个布尔标记，当一个新对象插入到该列表中的某个条目时，它的标记初始化为true。
只有当两个对象至少一个的标记为true，它们才进行局部连接。一个对象参与局部连接之后，它被标记为false（true变false，false还是false）。

#### 采样

采样是为了解决以下两个问题：

局部连接的高成本。一次迭代，就算只考虑K近邻，时间复杂度为K2N，如果再考虑反向近邻，时间复杂度更高。
冗余计算。两个点同时连接到多个不同对象，这两个点将比较多次。
使用采样来缓解这两个问题的具体方案如下：

邻居取样。局部连接之前，对用于局部连接的每一个对象，从标记为true的K近邻中取样ρK个对象（ρ∈(0,1]）。每一次迭代，仅仅这些被取出的数据被标记为false。
反向邻居。只根据取样对象和标记为false的对象来构建反向邻居列表。对构建得的反向邻居列表再次取样。
在标记为true对象之间进行局部连接，以及在标记为true对象与标记为false对象之间进行局部连接。
因此，我们就可以通过取样率ρ来进行精度和速度的trade-off。


#### 提前终止

一个很自然的终止标准是：某次迭代中，K近邻图不再被改善。实际上，开始迭代时，K近邻图能充分的更新，而随着迭代的进行，K近邻图更新的次数快速收缩，此时的迭代就显得意义不大了，考虑到迭代的计算成本，这些迭代其实没必要执行。为了解决这个问题，本文采取的方案是：在每次迭代中，统计所有对象K近邻列表更新的次数count，当count<δKN时终止发生，其中δ是精度参数，它粗略反应了由于提前终止允许错过的真正的K近邻的比例。

### 完整算法

```
Data: dataset V, similarity oracle σ, K, ρ, δ 
Result: K-NN list B 
begin 
  B[v] ←− Sample(V,K) × {<∞, true>} ∀v ∈ V 
  loop 
    parallel for v ∈ V do 
      old[v] ←− all items in B[v] with a false flag 
      new[v] ←− ρK items in B[v] with a true flag 
      Mark sampled items in B[v] as false;

    old′ ← Reverse(old), new′ ← Reverse(new) 
    c ←− 0 //update counter 
    
    parallel for v ∈ V do 
      old[v] ←− old[v] ∪ Sample(old′[v], ρK) 
      new[v] ←− new[v] ∪ Sample(new′[v], ρK) 
      for u1, u2 ∈ new[v], u1 < u2 or u1 ∈ new[v], u2 ∈ old[v] do 
      l ←− σ(u1, u2) // c and B[.] are synchronized.
      c ←− c+UpdateNN(B[u1], <u2, l, true>)
      c ←− c+UpdateNN(B[u2], <u1, l, true>)
    return B if c < δNK
```

## Map-Reduce 实现

## 总结



*参考*：

[NN-Descent构建K近邻图——论文超详细注解](https://blog.csdn.net/whenever5225/article/details/105598694)


