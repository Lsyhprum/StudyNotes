# ONNG

>@article{DBLP:journals/corr/abs-1810-07355,
>  author    = {Masajiro Iwasaki and
>               Daisuke Miyazaki},
>  title     = {Optimization of Indexing Based on k-Nearest >Neighbor Graph for Proximity
>               Search in High-dimensional Data},
>  journal   = {CoRR},
>  volume    = {abs/1810.07355},
>  year      = {2018},
>  url       = {http://arxiv.org/abs/1810.07355},
>  archivePrefix = {arXiv},
>  eprint    = {1810.07355},
> timestamp = {Tue, 30 Oct 2018 20:39:56 +0100},
>  biburl    = {https://dblp.org/rec/journals/corr/abs-1810-07355.>bib},
>  bibsource = {dblp computer science bibliography, https://dblp.>org}
>}

### Introduction

在 ANNS 的多种算法中，基于图的算法更有利于在高维数据集上进行快速查询。为了进一步提高基于图的算法的查询性能，ONNG 试图通过控制图中点的 **入度** 和 **出度** 来达成以上目的。

该论文认为，**入度的增加有利于提升查询的准确率，出度的增加则会降低查询的效率**。
因此，ONNG 主要提出了三种调整度的算法：

* 静态度调整

* 动态度调整

* 路径调整减少出度

同时，改论文认为算法的具体实现会对查询效率产生较大影响，特别是在查询过程中对点是否已访问的管理工作占据了较大一部分的时间。因此本文提出了更好的节点管理算法来缩短查询时间。



### Algorithm

#### 搜索阶段

ONNG 搜索阶段首先通过 vp-tree 获取初始入口点，之后根据贪心算法更新近邻集。其贪心算法主要有两个特点：

* 根据结果集动态更新阈值，依据阈值作为是否加入候选集或结果集的判断依据，减少了一定的距离比较次数

* 候选池中的结点的获取依据是与候选点的距离而非与查询点的距离

```cpp
Input: G, q, k, ǫ, ep   // 输入：图索引 G， 查询向量 q, 结果近邻数量 k, 搜索范围调整值 ǫ， 动态调整值 ep
Output: R               // 输出：搜索近邻结果集

S ← Seed(G), r ←∞, R ← S    // Seed —— 入口点生成函数，本论文中通过 vp-tree 生成入口点; r —— 用于筛选近邻，在算法中根据结果集最大距离进行更新
C ← ∅                       // b ← {empty, · · · }, L ← {∅, · · · } 已访问结点集

while S != ∅ do                              // 候选池非空
    s ← argmin d(x, q), S ← S \ {s} (x∈S)   // 从候选池中选出距离查询点最近的结点，将该点从候选池中删除

    if d(s, q) > r(1 + ǫ) then              // 最近结点到查询点距离仍大于r的阈值，退出循环
        return R
    end if

    p ← 1
    M ← N(G, s)                             // 获取最近结点 s 的近邻
    while M != ∅ and p ≤ ep do
        n ← argmin d(x, s) x∈M             // 获取距离 s 的最近点 n
        M ← M \ {n}
        if n not in C then                  // 结点 n 未访问
            C ← C ∪ {n}                    // 标记为已访问
            if d(n, q) ≤ r(1 + ǫ) then      // 距离小于r的阈值，加入候选集
                S ← S ∪ {n}                
            end if
            if d(n, q) ≤ r then             // 距离小于距离 r, 直接加入结果集
                R ← R ∪ {n}
                if |R| > k then             // 结果集数量过多，筛选最小的 k 个
                    R ← R \ {argmax d(x, q)} x∈R
                end if
                if |R| = k then             // 结果集达到 k, 更新 r
                    r ← max x∈R d(x, q)
                end if
            end if
        end if
        p ← p + 1                           // 更新迭代次数
    end while
end while

return R
```

#### 调整索引阶段

ONNG 对于基于不同的出度入度构建了三张不同的图：

* KNNG : 出度 40 的近邻图
* TKNNG (transposed KNNG ): 翻转 KNNG 所有边的方向，即入度为 40
* BKNNG (bi-directed KNNG) : 出度为 20 的近邻图，但边的方向为双向，其边的总数与 KNNG 和 TKNNG 相同

ONNG 对于同一算法构建的初始图根据度的区别分别构建了三张不同的图 ：

* KNNG : 初始图，不作改变

* TKNNG : transposed KNNG 翻转初始图

* BKNNG : bi-directed KNNG 双向初始图

<div align="center"> <img src="./pic/ONNG precision.png" width="300"/> </div><br>

实验证明，TKNNG 查询时间小于 KNNG, BKNNG 查询时间小于 TKNNG。  

论文中针对 KNNG、TKNNG 和 BKNNG 的入度出度的数量进行了分析：

<div align="center"> <img src="./pic/ONNG degree.png" width="300"/> </div><br>

KNNG 中部分的点入度为 0，从而导致很多点无法到达，且大量的点入度小于 10， 到达这些点的可能性较低。较低的平均入度，导致 KNNG 准确率较低。

TKNNG 中的入度恒定为 40， 准确率优于 KNNG。然而由于其存在大量的点的出度为数百，对于这些点，计算近邻将花费大量时间。

BKNNG 入度均大于 20，出度大多小于 TKNNG。

基于以上实验，提升搜索性能主要有两个方面：

* **削减过高的出度**

* **提高过低的入度**

* 静态度调整

限制图出度入度, 并构建双向边：

```cpp
ConstructAdjustedGraph

Input: G(V, E), eo, ei  // 输入 ： 图索引 G， eo 期望出度， ei 期望入度
Output: Ge(Ve, Ee)      // 输出 :  调整后的图索引

Ve ← V, Ee ← ∅, Ge ← (Ve, Ee)   // 调整图：只添加结点，不添加边
for all o ∈ V do 
    S ← N(G, o)         // 将结点 o 的邻居加入候选集 S
    p ← 1
    while S != ∅ and p ≤ eo and p ≤ ei do   // 保证每个结点出度入度小于规定值
        n ← argmin d(x, o) (x∈S)
        S ← S \ {n}

        if p ≤ eo and N(Ge, o) ∩ {n} = ∅ then   // 增加 o 的出度
            N(Ge, o) ← N(Ge, o) ∪ {n}
        end if
        if p ≤ ei and N(Ge, n) ∩ {o} = ∅ then   // 增加 o 的入度
            N(Ge, n) ←N(Ge, n) ∪ {o}
        end if
        p ← p + 1
    end while
end for

return Ge
```

```cpp
Input: G(V, E), eo, ei 
Output: Ge(Ve, Ee) 

Gt(Vt, Et) ← ConstructAdjustedGraph(G, 0, ei)       // 将 KNNG 转化为 TKNNG Gt
Ve ← V, Ee ← ∅, Ge ← (Ve, Ee)                       // Ge 仅保留 KNNG 结点和出度信息
Vi ← V, Ei ← ∅, Gi ← (Vi, Ei)                       // Gi 仅用于保存 KNNG 结点和入度信息
M ← V 
while M != ∅ do
    o ← argmin|N(Gt, x)| (x∈M)                     // 从 Gt 中获取到 x 最近的点 o （o->x）
    M ← M \ {o}                                     // 从点集中删除 
    S ← N(Gt, o)                                    // 将 o 的近邻加入候选池 S
    
    while S != ∅ do
        n ← argmin d(x, o) (x∈S)                    // 获取候选池中距离 o 的最近点 n
        S ← S \ {n}
        if N(Gi, n) = ∅ or {|N(Gi, n)| < ei and |N(Ge, o)| < eo} then       // n 无近邻 或 n 的近邻小于 ei 或 o 的近邻小于 eo
            N(Ge, o) ← N(Ge, o) ∪ {n}                                      // n 加入 o 的近邻                                                           
            N(Gi, n) ← N(Gi, n) ∪ {o}                                      // o 加入 n 的近邻
        end if
    end while
end while 

for all o ∈ V do 
    S ← N(G, o)                                 // 获取结点 o 的近邻集 S
    while S != ∅ and N(Ge, o) < eo do           // 调整图 Ge 中结点 o 出度小于 eo
        n ← argmin d(x, o) (x∈S)                // 获取距离 o 最近的结点 n
        S ← S \ {n}
        if N(Ge, o) ∩ {n} = ∅ then               // n -> o 不存在路径
            N(Ge, o) ← N(Ge, o) ∪ {n}           // n 增加出度
        end if
    end while
end for 
return Ge
```


* 路径调整

静态度调整只考虑了由边相连的两点的度的问题。而路径调整通过裁边达到减少搜索时间的问题：

```cpp
//HasPath 
Input: G, ns, nd    // 输入：图索引 G，路径起始点 ns, 路径结束点 nd
Output: Whether there is an alternative path: true or false 

for all n ∈ N(G, ns) do     // 获取 ns 的所有近邻 n
    if N(G, n) ∩ {nd} != ∅ and d(n, nd) < d(ns, nd) then        // ns 到 nd 为三角形最长边 ： ns 存在近邻 n 能到达 nd 并且 近邻 n 到 nd 的距离小于 ns 到 nd 的距离。
        return true                                             // ns nd 存在代替边
    end if
end for
return false                                                    // ns nd 不存在代替边
```

```cpp
Input: G(V, E) 
Output: Gp(Vp, Ep) 

Vp ← V, Ep ← ∅ 
Gt(Vt, Et) ← G(V, E) 

while Vt != ∅ do
    for all n ∈ Vt do
        nd ← argmin d(n, x) (x∈N(Gt,n))
        if HasPath(Gp, n, nd) = false then
            N(Gp, n) ← N(Gp, n) ∪ {nd}
        end if
        N(Gt, n) ← N(Gt, n) \ {nd}
        if N(Gt, n) = ∅ then
            Vt ← Vt \ {n}
        end if
    end for
end while 
return Gp
```


* 动态度调整

* 结点管理

ONNG 论文中认为， 在基于图的算法实现中，结点是否访问占据了较大一部分的搜索时间。目前主要有如下几种实现：

* 通过数组保存结点是否访问的信息，其缺点是初始化时间较长。

* 通过 hash table 进行保存，其优点是数据规模对其影响较小，缺点是访问结点的比例较小，然而这种方法仍需要对所有结点进行比较。

* Bloom 过滤器由于它使用了多个 hash table 同样速度不够快

* 


## ONNG 所做优化

* static degree adjustment method
    * 调整出度入度
    * 缺点 ： 高出度，影响查询时间
    * 改进 ： 限制出度入度

* dynamic degree-adjustment method for
    * 适应用户要求准确度

* path-adjustment method
    * 考虑点和边

* 对于基于图的方法，查询时间很大程度上取决于具体实现
    * 管理节点是否访问占据了较多查询时间，ONNG 对其进行了优化


    #### 

    搜索阶段 ： 候选点距离而非查询点距离


### ONNG 源码分析

```cpp                                                        
#include        "NGT/Index.h"
#include        "NGT/GraphOptimizer.h"

using namespace std;
int main(int argc, char **argv)
{
  NGT::GraphOptimizer   graphOptimizer(false);
  int numOfOutgoingEdges = 10;
  int numOfIncomingEdges = 100;
  int numOfQueries = 200;
  int numOfResultantObjects = 20; // k                                                                 

  // 设置 ONNG 相关参数       
  graphOptimizer.set(numOfOutgoingEdges, numOfIncomingEdges, numOfQueries, numOfResultantObjects);  
  graphOptimizer.execute("fasttext.anng-100", "fasttext.onng");
  return 0;
}  

void execute(const std::string inIndexPath, const std::string outIndexPath){
    
    ...

    {
        NGT::GraphIndex graphIndex(outIndexPath, false);
        if (numOfOutgoingEdges > 0 || numOfIncomingEdges > 0) {
            ...
            std::vector<NGT::ObjectDistances> graph;
            
            std::cerr << "Optimizer::execute: Extract the graph data." << std::endl;
            // extract only edges from the index to reduce the memory usage.
            NGT::GraphReconstructor::extractGraph(graph, graphIndex);
            // 设置构建 ONNG 相关参数
            NeighborhoodGraph::Property &prop = graphIndex.getGraphProperty();
            // 初始图必须为 ANNG
            if (prop.graphType != NGT::NeighborhoodGraph::GraphTypeANNG) {
                NGT::GraphReconstructor::convertToANNG(graph);
            }
            NGT::GraphReconstructor::reconstructGraph(graph, graphIndex, numOfOutgoingEdges, numOfIncomingEdges);
            
            ...
        }

        if (shortcutReduction) {
            ...

            NGT::GraphReconstructor::adjustPathsEffectively(graphIndex);
            
            ...
        }
        ...
    }

    optimizeSearchParameters(outIndexPath);
}

// 提取图中结点
static void extractGraph(std::vector<NGT::ObjectDistances> &graph, NGT::GraphIndex &graphIndex) {
    graph.reserve(graphIndex.repository.size());
    for (size_t id = 1; id < graphIndex.repository.size(); id++) {
        ...
        NGT::GraphNode &node = *graphIndex.getNode(id);
        graph.push_back(node);
        ...
    }
}

// graph 初始图索引，outGraph 输出图索引（初始状态下只存在图结点），originalEdgeSize 出度，reverseEdgeSize 入度
static void reconstructGraph(std::vector<NGT::ObjectDistances> &graph, NGT::GraphIndex &outGraph, size_t originalEdgeSize, size_t reverseEdgeSize) {
    ...

    // 初始化 outGraph 结点
    for (size_t id = 1; id < outGraph.repository.size(); id++) {
        ...

        NGT::GraphNode &node = *outGraph.getNode(id);
        if (originalEdgeSize == 0) {
            NGT::GraphNode empty;
            node.swap(empty);
        } else {
            NGT::ObjectDistances n = graph[id - 1];
            if (n.size() < originalEdgeSize) {
                std::cerr << "GraphReconstructor: Warning. The edges "
                                "are too few. "
                            << n.size() << ":" << originalEdgeSize
                            << " for " << id << std::endl;
                continue;
            }
            n.resize(originalEdgeSize);
            node.swap(n);
        }
        ...
    }
    
    // 构建反向图
    int insufficientNodeCount = 0;
    for (size_t id = 1; id <= graph.size(); ++id) {
        ...

        NGT::ObjectDistances &node = graph[id - 1];
        size_t rsize = reverseEdgeSize;
        if (rsize > node.size()) {
            insufficientNodeCount++;
            rsize = node.size();
        }
        for (size_t i = 0; i < rsize; ++i) {
            NGT::Distance distance = node[i].distance;
            size_t nodeID = node[i].id;
            try {
                NGT::GraphNode &n = *outGraph.getNode(nodeID);
                n.push_back(NGT::ObjectDistance(id, distance));
            } catch (...) {
            }
        }
        ...
    }
    if (insufficientNodeCount != 0) {
        std::cerr << "# of the nodes edges of which are in short = "
                    << insufficientNodeCount << std::endl;
    }

    ...
    for (size_t id = 1; id < outGraph.repository.size(); id++) {
        ...
        NGT::GraphNode &n = *outGraph.getNode(id);
        ...
        std::sort(n.begin(), n.end());
#endif
        NGT::ObjectID prev = 0;
        for (auto it = n.begin(); it != n.end();) {
            if (prev == (*it).id) {
                it = n.erase(it);
                continue;
            }
            prev = (*it).id;
            it++;
        }
#if !defined(NGT_SHARED_MEMORY_ALLOCATOR)
        NGT::GraphNode tmp = n;
        n.swap(tmp);
#endif
        ...
    }
    
    ...
}
```

```cpp
static void adjustPathsEffectively(NGT::GraphIndex &outGraph) {
    ...
    std::vector<NGT::GraphNode> tmpGraph;
    for (size_t id = 1; id < outGraph.repository.size(); id++) {
        ...
        NGT::GraphNode &node = *outGraph.getNode(id);
        tmpGraph.push_back(node);
        node.clear();
        ...
    }
    ...

    // 待删除结点候选集
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> removeCandidates(tmpGraph.size());
    int removeCandidateCount = 0;
    // 并行遍历图索引
#pragma omp parallel for
    for (size_t idx = 0; idx < tmpGraph.size(); ++idx) {
        auto it = tmpGraph.begin() + idx;
        size_t id = idx + 1;

        // 获取结点近邻
        NGT::GraphNode &srcNode = *it;
        // 保存结点 id 和 近邻 id 及距离的关系
        std::unordered_map<uint32_t, std::pair<size_t, double>> neighbors;
        for (size_t sni = 0; sni < srcNode.size(); ++sni) {
            neighbors[srcNode[sni].id] = std::pair<size_t, double>(sni, srcNode[sni].distance);
        }

        // 当前结点待删除结点
        std::vector<std::pair<int, std::pair<uint32_t, uint32_t>>> candidates;
        // 遍历近邻
        for (size_t sni = 0; sni < srcNode.size(); sni++) {
            NGT::GraphNode &pathNode = tmpGraph[srcNode[sni].id - 1];
            // 遍历近邻的近邻，寻找可删除结点（三角形）
            for (size_t pni = 0; pni < pathNode.size(); pni++) {
                auto dstNodeID = pathNode[pni].id;
                auto dstNode = neighbors.find(dstNodeID);
                if (dstNode != neighbors.end() &&
                    srcNode[sni].distance < (*dstNode).second.second &&
                    pathNode[pni].distance < (*dstNode).second.second) {
                    candidates.push_back(
                        std::pair<int, std::pair<uint32_t, uint32_t>>(
                            (*dstNode).second.first,
                            std::pair<uint32_t, uint32_t>(
                                srcNode[sni].id, dstNodeID)));
                    removeCandidateCount++;
                }
            }
        }
        // 推入总删除结点
        sort(candidates.begin(), candidates.end(), std::greater<std::pair<int, std::pair<uint32_t, uint32_t>>>());
        removeCandidates[id - 1].reserve(candidates.size());
        for (size_t i = 0; i < candidates.size(); i++) {
            removeCandidates[id - 1].push_back(candidates[i].second);
        }
    }
    ...

    std::list<size_t> ids;
    for (size_t idx = 0; idx < tmpGraph.size(); ++idx) {
        ids.push_back(idx + 1);
    }

    int removeCount = 0;
    removeCandidateCount = 0;
    for (size_t rank = 0; ids.size() != 0; rank++) {
        for (auto it = ids.begin(); it != ids.end();) {
            size_t id = *it;
            size_t idx = id - 1;
            // 获取当前结点近邻 srcNode
            NGT::GraphNode &srcNode = tmpGraph[idx];
            // ?
            if (rank >= srcNode.size()) {
                if (!removeCandidates[idx].empty()) {
                    std::cerr << "Something wrong! ID=" << id
                                << " # of remaining candidates="
                                << removeCandidates[idx].size()
                                << std::endl;
                    abort();
                }
                NGT::GraphNode empty;
                tmpGraph[idx] = empty;
                it = ids.erase(it);
                continue;
            }
            if (removeCandidates[idx].size() > 0) {
                removeCandidateCount++;
                bool pathExist = false;
                while (!removeCandidates[idx].empty() &&
                        (removeCandidates[idx].back().second ==
                        srcNode[rank].id)) {
                    size_t path = removeCandidates[idx].back().first;
                    size_t dst = removeCandidates[idx].back().second;
                    removeCandidates[idx].pop_back();
                    if (removeCandidates[idx].empty()) {
                        std::vector<std::pair<uint32_t, uint32_t>> empty;
                        removeCandidates[idx] = empty;
                    }
                    if ((hasEdge(outGraph, id, path)) && (hasEdge(outGraph, path, dst))) {
                        pathExist = true;
                        while (!removeCandidates[idx].empty() &&
                                (removeCandidates[idx].back().second ==
                                srcNode[rank].id)) {
                            removeCandidates[idx].pop_back();
                            if (removeCandidates[idx].empty()) {
                                std::vector<std::pair<uint32_t, uint32_t>> empty;
                                removeCandidates[idx] = empty;
                            }
                        }
                        break;
                    }
                }
                if (pathExist) {
                    removeCount++;
                    it++;
                    continue;
                }
            }
            NGT::GraphNode &outSrcNode = *outGraph.getNode(id);
            insert(outSrcNode, srcNode[rank].id, srcNode[rank].distance);
            it++;
        }
    }

    // 后续处理 ： 排序
    for (size_t id = 1; id < outGraph.repository.size(); id++) {
        try {
            NGT::GraphNode &node = *outGraph.getNode(id);
            std::sort(node.begin(), node.end());
        } catch (...) {
        }
    }
}

static bool hasEdge(NGT::GraphIndex &graph, size_t srcNodeID, size_t dstNodeID) {
    NGT::GraphNode &srcNode = *graph.getNode(srcNodeID);
    GraphNode::iterator ni =
        std::lower_bound(srcNode.begin(), srcNode.end(),
                            ObjectDistance(dstNodeID, 0.0), edgeComp);
    return (ni != srcNode.end()) && ((*ni).id == dstNodeID);
}
```