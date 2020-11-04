# FANNG 算法

```
@inproceedings{DBLP:conf/cvpr/HarwoodD16,
  author    = {Ben Harwood and
               Tom Drummond},
  title     = {{FANNG:} Fast Approximate Nearest Neighbour Graphs},
  booktitle = {2016 {IEEE} Conference on Computer Vision and Pattern Recognition,
               {CVPR} 2016, Las Vegas, NV, USA, June 27-30, 2016},
  pages     = {5713--5722},
  publisher = {{IEEE} Computer Society},
  year      = {2016},
  url       = {https://doi.org/10.1109/CVPR.2016.616},
  doi       = {10.1109/CVPR.2016.616},
  timestamp = {Wed, 16 Oct 2019 14:14:50 +0200},
  biburl    = {https://dblp.org/rec/conf/cvpr/HarwoodD16.bib},
  bibsource = {dblp computer science bibliography, https://dblp.org}
}
```

## Introduction

## Algorithms

### 图索引构建

FANNG 首先在传统的贪心路由算法进行改进，通过删除 occludes edge (三角形短边)来达到减少出度的目的。

```cpp
Algorithm 2: Naive ideal graph construction 

Input: graph vertices P // 输入 ： 向量结点 P
Output: directed graph edges E  // 输出 ： 有向图边集 E

for each vertex Pi do
  e ← empty sorted list of edges  // 清空边集
  for each vertex Pj != Pi do 
    add edge e(Pi,Pj) sorted by distance(Pi,Pj) // 计算 Pi 与其他结点的距离并排序
  for each edge ej do
    u ← index of end vertex of ej // u 有向边中点 u 
    L ← length of ej 
    occluded ← false
    for each edge Ek with start vertex Pi do  // 遍历已经加入 Pi 边集的边
      v ← index of end vertex of Ek
      if distance(Pu,Pv) < L then // 判断是否为 occludes edge
        occluded ← true
    if not occluded then
      add edge ej to E
return E
```

事实上，以上算法的时间复杂度非常高，因此 FANNG 基于以上算法进行了改进。

* 修改 occludes rule

```cpp
Algorithm 4: Traverse-add 

Input: graph vertices P, directed graph edges E, search start index v1, search end index v2
Output: directed graph edges E

u ← NaiveDownhillSearch(P, E, Pv2 , v1)
if u != v2 then
  add edge e(Pu,Pv2 ) to E // keep E sorted
  for each edge Ei with start vertex Pu do
    if e(Pu,Pv2) occludes Ei then
      remove edge Ei from E
      v ← index of end vertex of Ei
      E ← TraverseAdd(P, E, u, v)
  E ← TraverseAdd(P, E, v2, u) // test reverse
return E
```



### 搜索策略

```cpp
Algorithm 3: Backtrack search 

Input: graph vertices P, directed graph edges E, query point Q, search start index v, maximum distance calculations M
Output: nearest neighbour index n

X ← empty priority queue // closest to Q first 
add edge e0 with start vertex Pv to X
  m ← 1  // count distance computed to Q
  n ← v

  while m < M do
    ei ← remove top of X
    u ← = index of end vertex of ei
    if Pu has not been visited yet then
      add edge e0 with start vertex Pu to X
      m ← m+1 // add 1 to compute count
      if distance(Q,Pu) < distance(Q,Pn) then
        n ← u
    v ← = index of start vertex of ei
    if i< number ofedges with start vertex Pv then
      add edge ei+1 with start vertex Pv to X
return n
```

FANNG 主要的创新点在于提出了一种新的图结构提升查找的效率，

通过剪枝保证贪心算法始终保持下降

occludes edge

