# PANNG 算法

>@inproceedings{DBLP:conf/sisap/Iwasaki16,
>  author    = {Masajiro Iwasaki},
>  editor    = {Laurent Amsaleg and
>               Michael E. Houle and
>               Erich Schubert},
>  title     = {Pruned Bi-directed K-nearest Neighbor Graph for Proximity >Search},
>  booktitle = {Similarity Search and Applications - 9th International >Conference,
>               {SISAP} 2016, Tokyo, Japan, October 24-26, 2016. >Proceedings},
>  series    = {Lecture Notes in Computer Science},
>  volume    = {9939},
>  pages     = {20--33},
>  year      = {2016},
>  url       = {https://doi.org/10.1007/978-3-319-46759-7\_2},
>  doi       = {10.1007/978-3-319-46759-7\_2},
>  timestamp = {Tue, 14 May 2019 10:00:53 +0200},
>  biburl    = {https://dblp.org/rec/conf/sisap/Iwasaki16.bib},
>  bibsource = {dblp computer science bibliography, https://dblp.org}
>}


### Introduction

在基于图的 ANNS 算法中，通常提升性能常伴随着占据内存的增加。PANNG 旨在 **提升 ANNS 搜索性能的同时而不增加边的数量**。

论文主要提出基于 KNNG 改进的 PBKNNG 算法。由于 PBKNNG 构建初始图耗时较长，之后提出了由 ANNG 改进的 PANNG 算法。

### Algorithms

#### 搜索算法

```cpp
Input: G, q, ks, ε           // 输入：图索引 G，查询点 q, 结果集数量 ks, 距离阈值 ε
Output: R 

S ← Seed(G), r ← ∞, R ← ∅
while S != ∅ do 
    s ← argmin d(x, q), S ← S − {s} (x∈S)   // 从候选集中选取距离查询点最近的点 s
    if d(s, q) > r(1 + ε) then               // 最近点 s 大于阈值，返回 
        return R
    end if
    for all o ∈ N(G, s) do                   // 若 s 到查询点 q 的距离小于阈值，遍历 s 近邻
        if o /∈ C then                       // 若 o 未访问
            C ← C ∪{o}                       // 添加到已访问集 C
            if d(o, q) ≤ r(1 + ?) then        // 若合法，添加该点 o 到候选集中
                S ← S ∪{o}
            end if
            if d(o, q) ≤ r then               // 若距离小于结果集最大距离，将该点加入结果集
                R ← R ∪{o}
                if |R| > ks then               // 若结果集数量过多，剔除最大距离点
                    R ← R−{argmax d(x, q)}  (x∈R)
                end if
                if |R| = ks then
                    r ← max d(x, q)  (x∈R)
                end if
            end if
        end if
    end for
end while
return R
```

#### 裁边算法

PBKNNG 裁边算法主要有如下几步：

* 对初始图所有的边增加反向边。其好处是增加反向边可能增加一些到达入度较少的点的路径，从而增加准确度，并减少长边的生成。

* 削减不必要的长边。

* 削减具有可代替路径的边

```cpp
Input: G, kp, kr, p              // 输入：图索引 G，削减长边阈值 kp, 削减可替代路径阈值 kr, 最大替代边个数阈值 p
Output: G 
for all o ∈ V do                // 对于图索引中所有结点 o
    for all n ∈ N(G, o) do      // 添加反向边
        if N(G,n) ∩ {o} = ∅ then    
            N(G,n) ← N(G,n) ∪{o}
            if |N(G,n)| > kp then   // 若结点边数量大于阈值，删除长边
                N(G,n) ← N(G,n) − {argmax d(x, n)} x∈N(G,n)
            end if
        end if
    end for
end for 

RemoveEdgesSelectively(G, kr, p)    // 削减可替代路径
return G
```


```cpp
//RemoveEdgesSelectively

Input: G, kr, p 
Output: G 
for all o ∈ V do
    for all n ∈ N(G, o) do 
        if Rank(N(G, o),n) > kr then
            if PathExists(G, o, n, p) = true then
                N(G, o) ← N(G, o) − n
            end if
        end if
    end for 
end for
return G
```


PANNG 裁边算法

```cpp
Input: O, kc,kp,kr,εc,p 
Output: G 
for all o ∈ O do
    N(G, o) ← KnnSearch(G, o, kc, εc)
    for all n ∈ N(G, o) do
        N(G,n) ←N(G,n) ∪{o}
        if |N(G,n)| > kp then
            N(G,n) ← N(G,n) − {argmax d(x, n)} (x∈N(G,n))
        end if
    end for 
end for
RemoveEdgesSelectively(G, kr,p) 
return G
```