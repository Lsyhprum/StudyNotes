# ANNG

KNNG 作为海量数据检索的常用方法，其构建索引算法相当耗时，同时不连通的图导致查询的准确度降低。基于 KNNG 的以上缺点，ANNG 通过逐渐增加结点来保证图的连通性，并通过部分索引进行 k 近邻搜索。

### Range Search

```cpp
// Algorithm 1 NearestNeighborSearch(G, q, s) 
p ← s 
P ← N(G, p)
c ← argmin
d(x, q)
if d(c, q) < d(p, q) then
x∈P
p ← NearestNeighborSearch(G, q, c)
end if return p
```

### 构建 ANNG 索引

```cpp
//Create(G, P, k)   // P 结点集合
for all q ∈ P do 
    if G = ∅ then   // 图为空，将结点直接加入 
        G ←{q}
    else 
        s ← Random(G) // 选取随机入口点
        s ← NearestNeighborSearch(G, q, s)  // 贪心选取候选集 
        r ← ∞         // 初始搜索范围为 无穷
        R ←∅ 
        C ←∅
        KnnSearch(G, q, s, r, k, R, C)      // ANNG 范围搜索
        G ← G ∪ {q} 
        N(G, q) ← R 
        for all p ∈ R do 
            N(G, p) ← N(G, p) ∪ {q}
    end for 
    end if 
end for
```

### 裁边

ANNG 存在的一个缺点是，部分结点存在过多的边，尤其是越早插入的节点，普遍其相连的边越多。因此需要删除过剩节点，但若单纯删除过剩节点，有可能导致图不连通，进而导致搜索的精确度下降。所以需要在保持图的连通性的情况下，进行边的裁减。

裁边主要分为三种情况 ： 

* 删除边后，图依然连通
* 删除边后，图不连通，且存在源点的近邻，同时也为删除点的近邻，则连接源点近邻与删除点
* 删除边后，图不连通，且不存在源点的近邻，同时为删除点的近邻，那么这个边不应当删除

```cpp
//Algorithm 1 Optimize(G, kd, ks) 
for all p ∈ G do 
    // 获取待删除结点列表
    Nd ← ∅                  // 待删除结点列表
    T ← N(G, p)             // 获取搜索节点 p 的近邻
    while |T| > kd do       // 若 p 的近邻个数大于边数阈值
        s ← argmax d(x, p) x∈T      // 获取距离 p 最远的近邻点 s
        if |N(G, s)| > kd then       // 若 s 的近邻大于边数阈值，删除 s 和 p 的连接边
            N(G, p) ← N(G, p) − {s} 
            N(G, s) ← N(G, s) − {p}
            Nd ← Nd ∪ {s}
        end if
        T ← T − {s}
    end while

    for all q ∈ Nd do 
        r ← ∞
        C ← ∅ 
        R ← ∅
        KnnSearchUsingGraph(G, q, p, r, ks, R, C)   // 获取待删除结点 q 的近邻
        
        s ← argmin d(q, x) x∈R                  
        if s != q then                              // 不连通
            N(G, q) ← N(G, q) ∪ {s}
            N(G, s) ← N(G, s) ∪ {q}
        end if
    end for 
end for
```

```cpp
//Algorithm 2 KnnSearchUsingGraph(G, q, s, r, ks, R, C)
// 输入 ： 图索引 G，搜索点 q, 入口点 s, 搜索半径 r, 路径搜索结果数 ks，搜索节点集合 R， 已搜索节点集合 C
for all p ∈ N(G, s) do 
    if p /∈ C then 
        C ← C ∪ {p}
        if d(p, q) ≤ r then
            R ← R ∪ {p}
            if |R| > ks then 
                R ← R− {argmax d(x, q)} x∈R
            end if

            if |R| = ks then
                r ← maxx∈R d(x, q)
            end if
        end if 
        rs ← (1 + ϵ)r
        if d(p, q) ≤ rs then  
            KnnSearchUsingGraph(G, q, p, r, ks, R, C)
        end if 
    end if 
end for
```


### Tree-based 查找



### NGT 源码

```cpp
void GraphAndTreeIndex::createIndex(size_t threadPoolSize,
                                    size_t sizeOfRepository) {
    ...

    // 初始化进程
    CreateIndexThreadPool threads(threadPoolSize);
    CreateIndexSharedData sd(*this);
    threads.setSharedData(&sd);
    threads.create();
    // 进程输出结果接口
    CreateIndexThreadPool::OutputJobQueue &output = threads.getOutputJobQueue();

    CreateIndexJob job;
    // 结点编号从 1 开始
    NGT::ObjectID id = 1;
    for (;;) {
        size_t cnt = searchMultipleQueryForCreation(*this, id, job, threads, sizeOfRepository);     // 确定同时执行的进程任务

        ...

        insertMultipleSearchResults(*this, output, cnt);      // 插入结点

        for (size_t i = 0; i < cnt; i++) {
            CreateIndexJob &job = output[i];
            if (((job.results->size() > 0) &&
                    ((*job.results)[0].distance != 0.0)) ||
                (job.results->size() == 0)) {
                DVPTree::InsertContainer tiobj(*job.object, job.id);
                try {
                    DVPTree::insert(tiobj);
                } catch (Exception &err) {
                    cerr << "NGT::createIndex: Fatal error. ID=" << job.id
                            << ":";
                    if (NeighborhoodGraph::property.graphType ==
                        NeighborhoodGraph::GraphTypeKNNG) {
                        cerr << err.what() << " continue.." << endl;
                    } else {
                        throw err;
                    }
                }
            }
        } // for

        while (!output.empty()) {
            delete output.front().results;
            output.pop_front();
        }

        count += cnt;
        if (timerCount <= count) {
            timer.stop();
            cerr << "Processed " << timerCount
                    << " objects. time= " << timer << endl;
            timerCount += timerInterval;
            timer.start();
        }
        buildTimeController.adjustEdgeSize(count);
        if (pathAdjustCount > 0 && pathAdjustCount <= count) {
            GraphReconstructor::adjustPathsEffectively(
                static_cast<GraphIndex &>(*this));
            pathAdjustCount += property.pathAdjustmentInterval;
        }
    }
}
```

insertMultipleSearchResults
```cpp
static void
insertMultipleSearchResults(GraphIndex &neighborhoodGraph,
                            CreateIndexThreadPool::OutputJobQueue &output,
                            size_t dataSize) {
    // compute distances among all of the resultant objects
    // This processing occupies about 30% of total indexing time when batch
    // size is 200. Only initial batch objects should be connected for each
    // other. The number of nodes in the graph is checked to know whether
    // the batch is initial.
    size_t size = neighborhoodGraph.NeighborhoodGraph::property.edgeSizeForCreation;
    // add distances from a current object to subsequence objects to imitate of sequential insertion.
    
    sort(output.begin(), output.end()); // sort by batchIdx

    // 遍历所有结点
    for (size_t idxi = 0; idxi < dataSize; idxi++) {
        // add distances
        ObjectDistances &objs = *output[idxi].results;
        // 遍历计算与之前节点（提前插入图的节点）的距离
        for (size_t idxj = 0; idxj < idxi; idxj++) {
            ObjectDistance r;
            r.distance = neighborhoodGraph.objectSpace->getComparator()(
                *output[idxi].object, *output[idxj].object);
            r.id = output[idxj].id;
            objs.push_back(r);
        }
        // sort and cut excess edges
        std::sort(objs.begin(), objs.end());
        if (objs.size() > size) {
            objs.resize(size);
        }
    } // for (size_t idxi ....

    // insert resultant objects into the graph as edges
    for (size_t i = 0; i < dataSize; i++) {
        CreateIndexJob &gr = output[i];
        
        ...

        // 逐个将结点插入图
        neighborhoodGraph.insertNode(gr.id, *gr.results);
    }
}
```

插入具体逻辑
```cpp
void insertNode(ObjectID id, ObjectDistances &objects) {
    switch (property.graphType) {
    case GraphTypeANNG:
        insertANNGNode(id, objects);
        break;
        ...
    }
}

void insertANNGNode(ObjectID id, ObjectDistances &results) {
    repository.insert(id, results);
    std::queue<ObjectID> truncateQueue;
    for (ObjectDistances::iterator ri = results.begin(); ri != results.end(); ri++) {
        assert(id != (*ri).id);
        if (addEdge((*ri).id, id, (*ri).distance)) {    // 添加反向边，并确定是否需要裁边
            truncateQueue.push((*ri).id);
        }
    }
    while (!truncateQueue.empty()) {
        ObjectID tid = truncateQueue.front();
        truncateEdges(tid);         // 调整边
        truncateQueue.pop();
    }
    return;
}

int truncateEdges(ObjectID id) {
    GraphNode &results = *getNode(id);

    size_t truncationSize = NGT_TRUNCATION_THRESHOLD;
    if (truncationSize < (size_t)property.edgeSizeForCreation) {
        truncationSize = property.edgeSizeForCreation;
    }
    return truncateEdgesOptimally(id, results, truncationSize);
}

int NeighborhoodGraph::truncateEdgesOptimally(ObjectID id, GraphNode &results, size_t truncationSize) {
    ObjectDistances delNodes;

    size_t osize = results.size();

    ...

    // 将多余结点加入待删候选池
    for (size_t i = truncationSize; i < results.size(); i++) {
        if (id == results[i].id) {
            continue;
        }
        delNodes.push_back(results[i]);
    }

    // 将多余结点从结构集中删除
    GraphNode::iterator ri = results.begin();
    ri += truncationSize;
    results.erase(ri, results.end());

    // 遍历待删除结点，删除 delNode -> id 的单向边
    for (size_t i = 0; i < delNodes.size(); i++) {
        GraphNode::iterator j;
        GraphNode &res = *getNode(delNodes[i].id);
        for (j = res.begin(); j != res.end(); j++) {
            if ((*j).id == id) {
                res.erase(j);
                break;
            }
        }
    }

    bool retry = true;
    size_t maxResSize = osize * 2;
    size_t batchSize = 20;
    TruncationSearchThreadPool::OutputJobQueue &output = threads.getOutputJobQueue();
    TruncationSearchJob job;

    for (; retry == true; resSize = maxResSize) {
        retry = false;
        sd.resultSize = resSize;        // 设置结果集尺寸
        size_t nodeidx = 0;
        for (;;) {

            // 将待删除结点信息封装到 job 中
            for (; nodeidx < delNodes.size(); nodeidx++) {
                ...
                nodeSize++;
                // 目标结点
                job.object =
                    getObjectRepository().get(delNodes[nodeidx].id);
                job.idx = nodeidx;
                // 查询开始结点
                job.start.id = id;
                job.start.distance = delNodes[nodeidx].distance;
                job.radius = FLT_MAX;
                threads.pushInputQueue(job);
            }

            // 范围搜索 -> Search
            threads.waitForFinish();

            size_t cannotMoveCnt = 0;
            // 遍历查询结果
            for (size_t i = 0; i < nodeSize; i++) {
                TruncationSearchJob &ojob = output.front();
                // 获取 id 到 delNodes 的最近邻
                ObjectID nearestID = ojob.nearest.id;
                // 获取待删除结点 idx
                size_t idx = ojob.idx;
                // 查询点可到达查询点，彻底删除与该 delNode 的边
                if (nearestID == delNodes[idx].id) {
                    delNodes[idx].id = 0;   // 设置 id 为不可达
                    output.pop_front();
                    continue;

                // 待删除结点近邻即为查询结点，图不连通
                } else if (nearestID == id) {
                    cannotMoveCnt++;

                    // 重新进行判断 ？ 
                    if ((resSize < maxResSize) && (cannotMoveCnt > 1)) {
                        retry = true;
                        output.pop_front();
                        continue;
                    }

                // 待删除结点与查询近邻不连通
                } else {
                }

                // 重新插入结点
                ObjectID tid = delNodes[idx].id;
                delNodes[idx].id = 0;

                // 将 查找近邻插入 待删除结点 tid 近邻                
                GraphNode &delres = *getNode(tid);
                {
                    GraphNode::iterator ei = std::lower_bound(
                        delres.begin(), delres.end(), ojob.nearest);
                    if ((*ei).id != ojob.nearest.id) {
                        delres.insert(ei, ojob.nearest);
                    } else {
                        output.pop_front();
                        continue;
                    }
                }

                // 插入结果集
                ObjectDistance r;
                r.distance = ojob.nearest.distance;
                r.id = tid;
                if (nearestID != id) {
                    GraphNode &rs = *getNode(nearestID);
                    rs.push_back(r);
                    std::sort(rs.begin(), rs.end());
                } else {
                    results.push_back(r);
                    std::sort(results.begin(), results.end());
                }
                // 查询任务完成
                output.pop_front();
            }
        }
    }

    // 返回删除边的个数
    size_t delsize = osize - results.size();

    return delsize;
}
```


```cpp
// 当前入口点即为 start 一个节点
void NeighborhoodGraph::search(NGT::SearchContainer &sc,ObjectDistances &seeds) {
    // 设置查询半径扩展因子
    if (sc.explorationCoefficient == 0.0) {
        sc.explorationCoefficient = NGT_EXPLORATION_COEFFICIENT;
    }

    // setup edgeSize
    size_t edgeSize = getEdgeSize(sc);

    UncheckedSet unchecked;
    // 确定是否计算距离
    DistanceCheckedSet distanceChecked;

    ResultSet results;
    // 计算入口点与目标点的距离
    setupDistances(sc, seeds);
    // 将 start 加入 unchecked 和 distanceChecked 
    setupSeeds(sc, seeds, results, unchecked, distanceChecked);
    Distance explorationRadius = sc.explorationCoefficient * sc.radius;
    NGT::ObjectSpace::Comparator &comparator = objectSpace->getComparator();
    ObjectRepository &objectRepository = getObjectRepository();
    ObjectDistance result;
    ObjectDistance target;
    ObjectDistance *neighborptr;
    ObjectDistance *neighborendptr;

    // 候选点非空
    while (!unchecked.empty()) {
        target = unchecked.top();
        unchecked.pop();

        // target 距离小于阈值
        if (target.distance > explorationRadius) {
            break;
        }

        // 获取 target 近邻
        GraphNode *neighbors = getNode(target.id);
        
        if (neighbors->size() == 0) {
            continue;
        }
        neighborptr = &(*neighbors)[0];
        neighborendptr = neighborptr;
        size_t neighborSize =
            neighbors->size() < edgeSize ? neighbors->size() : edgeSize;
        neighborendptr += neighborSize;

        for (; neighborptr < neighborendptr; ++neighborptr) {
            sc.visitCount++;
            ObjectDistance &neighbor = *neighborptr;
            // 若已经计算过，则跳过
            if (distanceChecked[neighbor.id]) {
                continue;
            }
            distanceChecked.insert(neighbor.id);

            // 获取目标点到当前结点的距离
            Distance distance =
                comparator(sc.object, *objectRepository.get(neighbor.id));
            sc.distanceComputationCount++;
            // 距离小于阈值
            if (distance <= explorationRadius) {
                // 加入候选池
                result.set(neighbor.id, distance);
                unchecked.push(result);
                // 距离小于半径阈值，则直接加入结果集，并更新半径
                if (distance <= sc.radius) {
                    results.push(result);
                    if (results.size() >= sc.size) {
                        if (results.top().distance >= distance) {
                            if (results.size() > sc.size) {
                                results.pop();
                            }
                            sc.radius = results.top().distance;
                            explorationRadius =
                                sc.explorationCoefficient * sc.radius;
                        }
                    }
                }
            }
        }
    }
    if (sc.resultIsAvailable()) {
        ObjectDistances &qresults = sc.getResult();
        qresults.clear();
        qresults.moveFrom(results);
    } else {
        sc.workingResult = std::move(results);
    }
}
```


**：

* 三角形裁边法有利于：在保持图的连通性的情况下，减少边的个数