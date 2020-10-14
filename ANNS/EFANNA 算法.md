# EFANNA 算法

>@article{DBLP:journals/corr/FuC16,
>  author    = {Cong Fu and
>               Deng Cai},
>  title     = {{EFANNA} : An Extremely Fast Approximate Nearest Neighbor Search Algorithm
>               Based on kNN Graph},
>  journal   = {CoRR},
>  volume    = {abs/1609.07228},
>  year      = {2016},
>  url       = {http://arxiv.org/abs/1609.07228},
>  archivePrefix = {arXiv},
>  eprint    = {1609.07228},
>  timestamp = {Mon, 13 Aug 2018 16:47:30 +0200},
>  biburl    = {https://dblp.org/rec/journals/corr/FuC16.bib},
>  bibsource = {dblp computer science bibliography, https://dblp.org}
>}



### Introduction

NN-Expansion 算法作为基于图的 ANNS 的主要构建方法，存在两点问题 ：

* 容易陷于局部最优

* 离线阶段构建 K-NNG 耗时

论文中认为 NN-Expansion 十分依赖于其初始化阶段的效果，并试图通过提供更好的初始图来尽量避免陷于局部最优。同时 EFANNA 使用基于层次结构的算法，在生成更好初始图的同时，减少距离的计算次数。

总体上本文主要针对 NN-Expansion **初始化阶段** 进行了改进。


### NN-Descent VS NN-Expansion

论文中在实验分析中证明，NN-Descent 和 NN-Expansion 在原理和性能上有较大区别。

NN-Expansion 原理是：我邻居的邻居很可能是我的邻居。

NN-Descent 原理是：我邻居很可能是我邻居的邻居。

具体来说 NN-Expansion + Local Join = NN-Descent。实验结果证明，NN-Descent 比 NN-Expansion 效率更高。


### Algorithm

#### 索引构建阶段

EFANNA 构建索引算法主要分为两部分：构建多随机层次结构 和 构建近邻 K-NNG。

EFANNA 首先通过构建层次结构将数据集多次分成多个小数据集，之后自底向上构建近似近邻图。最后使用 NN-Expansion 对初始图进行优化。

**分** —— 构建多棵随机截断树
```cpp
Input: the data set D, the number of trees T, the number of points in a leaf node K.  
Output: the randomized truncated KD-tree set S.     // 保存每棵随机截断树的树根

function BUILDTREE(Node,PointSet)
    //若剩余数据点的个数小于叶子节点中所需数据点数返回
    if size of PointSet < K then
		return
	else
        Randomly choose dimension d. //随机选择一个维度d
		Calculate the mean mid over PointSet on dimension d.    //计算数据集在该维的平均值mid
		Divide PointSet evenly into two subsets, LeftHalf and RightHalf, according to mid. //根据平均值把数据集平分为两个子集LeftHalf和RightHalf
        BUILDTREE(Node.LeftChild, LeftHalf) //递归建立左子树
		BUILDTREE(Node.RightChild,RightHalf) //递归建立右子树
	end if
	return
end function

//迭代T次，建立T棵随机截断树
for all i = 1 to T do
	BUILDTREE(Rooti,D)
    
	Add Rooti to S.  //添加第i棵树根到树集S
end for
```

**治** —— 根据随机截断树自下而上构建初始图
```cpp
Input:
the data set D, the k in approximate kNN graph , the randomized truncated KD-tree set S, the conquer-to depth Dep.   //数据集D;近似kNN图的k;树构建算法构建的随机截断KD树集S;处理的最小深度Dep(从叶子向上处理)
Output:
approximate kNN graph G.

//使用树构建算法建立多个随机截断KD树，得到树集S
%%Division step
Using Algorithm 1 to build tree, which leads to the input S

%% Conquer step
G = ∅  //近似kNN图G初始化为空
for all point i in D do
	Candidate pool C = ∅
	for all binary tree t in S do
		search in tree t with point i to the leaf node.  //用数据点i在树t上进行搜索直到叶子结点
		add all the point in the leaf node to C.         //添加叶子结点中的所有数据点到候选集C
		d = depth of the leaf node
		
		while d > Dep do                                 //当d大于给定的处理到的最小深度Dep执行下面的循环
			d = d − 1
            //用数据点i在树t上执行深度优先搜索直到深度d，在深度为d的那层搜索到的非叶结点标记为N，它的还没被访问过的孩子结点标记为Sib
			Depth-first-search in the tree t with point i to depth d. Suppose N is the non-leaf node on the search path with depth d. Suppose Sib is the child node of N. And Sib is not on the search path of point i.
            //在以Sib为根的子树上用数据点i执行深度优先搜索，直到叶子结点，添加叶子结点中所有的数据点到候选集C
			Depth-first-search to the leaf node in the subtree of Sib with point i . Add all the points in the leaf node to C.
		end while
	end for
    //保留候选集C中离数据点i最近的K个数据点
	Reserve K closest points to i in C.
	//添加候选集C中的点到近邻图，作为数据点i的初始化邻居
	Add C to G.
end for
```

#### 搜索阶段

在搜索阶段，EFANNA 通过层次结构搜索候选近邻，并通过 NN-Expansion 进行优化。

```cpp
Input:
data set D, query vector q, the number K of required nearest neighbors, EFANNA index (including tree set Stree and kNN graph G), the candidate pool size P, the expansion factor E, the iteration number I.   //侯选池尺寸P;扩展因子(贪婪搜索时每次迭代保留的最大候选邻居数)E;迭代次数I.
Output:
approximate nearest neighbor set ANNS of the query
iter = 0
NodeList = ∅
candidate set C = ∅
//每个叶子结点包含的数据点的最大个数记为Sleaf
suppose the maximal number of points of leaf node is Sleaf
//树的数量记为Ntree
suppose the number of trees is Ntree
//每棵树需要返回的最大叶子结点个数Nnode
then the maximal node check number is Nnode = P ÷ Sleaf ÷Ntree + 1
//遍历Stree中的树，对每一个树执行深度优先搜索，返回其中离查询最近的Nnode个叶子结点
//并添加到NodeList表中
for all tree i in Stree do
    Depth-first search i for top Nnode closest leaf nodes according to respective tree search criteria, add to NodeList
end for
//把NodeList中的叶子结点中的数据点添加到候选集C中
add the points belonging to the nodes in NodeList to C
//保留候选集C中离查询点最近的E个数据点
keep E points in C which are closest to q. 
//迭代I次贪婪搜索
while iter < I do
    candidate set CC = ∅
    //遍历候选集C中的数据点
    for all point n in C do
        //对于点n,它在kNN图中的邻居集为Sn
        Sn is the neighbors of point n based on G.
        //遍历Sn中的数据点
        for all point nn in Sn do
            //如果nn还没被检查
            if nn hasn’t been checked then
                //把nn添加到CC中
                put nn into CC.
            end if
        end for
    end for
    //把CC集中的点添加到候选集C中并保留离查询点最近的P个数据点
    move all the points in CC to C and keep P points in C which are closest to q.
    iter = iter + 1
end while
return ANNS as the closet K points to q in C.
```

*参考*：

[极度快速的近似最近邻搜索算法(EFANNA)学习笔记](https://mzwang.top/2019/09/21/efanna1/)