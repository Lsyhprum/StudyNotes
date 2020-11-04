# NGT 源码分析

### 结点管理

NGT 源码中通过 ObjectDistance 保存单个结点，其主要保存 **结点id** 以及 **距离**。

```cpp
class ObjectDistance {
public:

    ... 

    uint32_t id;
    float distance;
};
```

NGT 将 Repository 作为最基础的管理结点的容器。Repository 通过覆写 vecotr 实现。主要包括 **分配新结点内存**、**增删改查**、**序列化** 等功能

```cpp
template <class TYPE> class Repository : public std::vector<TYPE *> {
    ...
};
```

```cpp
class ObjectRepository : public Repository<Object> {
public:
    typedef Repository<Object>	Parent;
#endif
    ObjectRepository(size_t dim, const std::type_info &ot):dimension(dim), type(ot), sparse(false) { }

    void initialize() {
      deleteAll();
      Parent::push_back((PersistentObject*)0);
    }

    virtual PersistentObject *allocateNormalizedPersistentObject(const std::vector<double> &obj) {
      std::cerr << "ObjectRepository::allocateNormalizedPersistentObject(double): Fatal error! Something wrong!" << std::endl;
      abort();
    }

    virtual PersistentObject *allocateNormalizedPersistentObject(const std::vector<float> &obj) {
      std::cerr << "ObjectRepository::allocateNormalizedPersistentObject(float): Fatal error! Something wrong!" << std::endl;
      abort();
    }

    virtual PersistentObject *allocateNormalizedPersistentObject(const std::vector<uint8_t> &obj) {
      std::cerr << "ObjectRepository::allocateNormalizedPersistentObject(uint8_t): Fatal error! Something wrong!" << std::endl;
      abort();
    }

    virtual PersistentObject *allocateNormalizedPersistentObject(const float *obj, size_t size) {
      std::cerr << "ObjectRepository::allocateNormalizedPersistentObject: Fatal error! Something wrong!" << std::endl;
      abort();
    }


    template <typename T>
    void append(T *data, size_t objectCount) {
      if (dimension == 0) {
	NGTThrowException("ObjectSpace::readText: Dimension is not specified.");
      }
      if (size() == 0) {
	// First entry should be always a dummy entry.
	// If it is empty, the dummy entry should be inserted.
	push_back((PersistentObject*)0);
      }
      if (objectCount > 0) {
	reserve(size() + objectCount);
      }
      for (size_t idx = 0; idx < objectCount; idx++, data += dimension) {
	std::vector<double> object;
	object.reserve(dimension);
	for (size_t dataidx = 0; dataidx < dimension; dataidx++) {
	  object.push_back(data[dataidx]);
	}
	try {
	  PersistentObject *obj = 0;
	  try {
	    obj = allocateNormalizedPersistentObject(object);
	  } catch (Exception &err) {
	    std::cerr << err.what() << " continue..." << std::endl;
	    obj = allocatePersistentObject(object);
	  }
	  push_back(obj);

	} catch (Exception &err) {
	  std::cerr << "ObjectSpace::readText: Warning! Invalid data. Skip the data no. " << idx << " and continue." << std::endl;
	}
      }
    }

    void setLength(size_t l) { byteSize = l; }
    void setPaddedLength(size_t l) { paddedByteSize = l; }
    void setSparse() { sparse = true; }
    size_t getByteSize() { return byteSize; }
    size_t insert(PersistentObject *obj) { return Parent::insert(obj); }
    const size_t dimension;
    const std::type_info &type;

protected:
    size_t byteSize;		// the length of all of elements.
    size_t paddedByteSize;
    bool sparse;		// sparse data format
};
```


```cpp
class GraphRepository : public Repository<GRAPH_NODE> {
#endif

  public:
#ifdef NGT_SHARED_MEMORY_ALLOCATOR
    typedef PersistentRepository<GRAPH_NODE> VECTOR;
#else
    typedef Repository<GRAPH_NODE> VECTOR;

    GraphRepository() { prevsize = new vector<unsigned short>; }
    virtual ~GraphRepository() {
        deleteAll();
        if (prevsize != 0) {
            delete prevsize;
        }
    }
#endif

    void insert(ObjectID id, ObjectDistances &objects) {
        GRAPH_NODE *r = allocate();
#if defined(NGT_SHARED_MEMORY_ALLOCATOR)
        (*r).copy(objects, VECTOR::getAllocator());
#else
        *r = objects;
#endif
        try {
            put(id, r);
        } catch (Exception &exp) {
            delete r;
            throw exp;
        }
        if (id >= prevsize->size()) {
#if defined(NGT_SHARED_MEMORY_ALLOCATOR)
            prevsize->resize(id + 1, VECTOR::getAllocator(), 0);
#else
            prevsize->resize(id + 1, 0);
#endif
        } else {
#if defined(NGT_SHARED_MEMORY_ALLOCATOR)
            (*prevsize).at(id, VECTOR::getAllocator()) = 0;
#else
            (*prevsize)[id] = 0;
#endif
        }
        return;
    }

    inline GRAPH_NODE *get(ObjectID fid, size_t &minsize) {
        GRAPH_NODE *rs = VECTOR::get(fid);
#if defined(NGT_SHARED_MEMORY_ALLOCATOR)
        minsize = (*prevsize).at(fid, VECTOR::getAllocator());
#else
        minsize = (*prevsize)[fid];
#endif
        return rs;
    }
    void serialize(std::ofstream &os) {
        VECTOR::serialize(os);
        Serializer::write(os, *prevsize);
    }
    void deserialize(std::ifstream &is) {
        VECTOR::deserialize(is);
        Serializer::read(is, *prevsize);
    }
    void show() {
        for (size_t i = 0; i < this->size(); i++) {
            std::cout << "Show graph " << i << " ";
            if ((*this)[i] == 0) {
                std::cout << std::endl;
                continue;
            }
            for (size_t j = 0; j < (*this)[i]->size(); j++) {
#if defined(NGT_SHARED_MEMORY_ALLOCATOR)
                std::cout << (*this)[i]->at(j, VECTOR::getAllocator()).id << ":"
                          << (*this)[i]->at(j, VECTOR::getAllocator()).distance
                          << " ";
#else
                std::cout << (*this)[i]->at(j).id << ":"
                          << (*this)[i]->at(j).distance << " ";
#endif
            }
            std::cout << std::endl;
        }
    }

  public:
#ifdef NGT_SHARED_MEMORY_ALLOCATOR
    Vector<unsigned short> *prevsize;
#else
    std::vector<unsigned short> *prevsize;
#endif
}; // namespace NGT


```




### 构建索引

```cpp
NGT::Property property;                    // 构建索引相关参数
    ...
NGT::Index::create(indexPath, property);   // 初始化索引结构，具体逻辑位于 createGraphAndTree
NGT::Index index(indexPath);               // 加载索引文件，并将数据保存入 DVPTree

// 读取数据点
...
while (getline(is, line)) {
    ...

    // 将数据点插入索引
    obj.resize(property.dimension); // cut off additional data in the file.
    index.append(obj);
}

// 构建索引主代码
index.createIndex(16);
    ...
```

初始化索引结构

```cpp
void NGT::Index::createGraphAndTree(const string &database, NGT::Property &prop,
                                    const string &dataFile, size_t dataSize,
                                    bool redirect) {
    ...
    prop.indexType = NGT::Index::Property::IndexType::GraphAndTree; // 构建索引类型
    Index *idx = 0;
    ...
    idx = new NGT::GraphAndTreeIndex(prop);              // 载入构建索引相关参数
    ...
    loadAndCreateIndex(*idx, database, dataFile, prop.threadPoolSize,
                           dataSize);                    // 加载数据后创建索引，并保存索引文件
    
    delete idx;
}
```

构建索引

```cpp
void GraphAndTreeIndex::createIndex(size_t threadPoolSize,
                                    size_t sizeOfRepository) {
   
    ...

    CreateIndexJob job;
    NGT::ObjectID id = 1;
    for (;;) {
        size_t cnt = searchMultipleQueryForCreation(*this, id, job, threads, sizeOfRepository);     //将多个点的查询工作包装成一个作业，cnt 为作业数

        if (cnt == 0) {
            break;
        }
        threads.waitForFinish();

        if (output.size() != cnt) {
            cerr << "NNTGIndex::insertGraphIndexByThread: Warning!! Thread "
                    "response size is wrong."
                    << endl;
            cnt = output.size();
        }

        insertMultipleSearchResults(*this, output, cnt);        // 将新节点插入索引
    
        for (size_t i = 0; i < cnt; i++) {                      // 
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

```cpp
static void
insertMultipleSearchResults(GraphIndex &neighborhoodGraph,
                            CreateIndexThreadPool::OutputJobQueue &output,
                            size_t dataSize) {
    // compute distances among all of the resultant objects
    if (neighborhoodGraph.NeighborhoodGraph::property.graphType ==
            NeighborhoodGraph::GraphTypeANNG ||
        neighborhoodGraph.NeighborhoodGraph::property.graphType ==
            NeighborhoodGraph::GraphTypeIANNG ||
        neighborhoodGraph.NeighborhoodGraph::property.graphType ==
            NeighborhoodGraph::GraphTypeONNG ||
        neighborhoodGraph.NeighborhoodGraph::property.graphType ==
            NeighborhoodGraph::GraphTypeDNNG) {
        // This processing occupies about 30% of total indexing time when batch
        // size is 200. Only initial batch objects should be connected for each
        // other. The number of nodes in the graph is checked to know whether
        // the batch is initial.
        // size_t size = NeighborhoodGraph::property.edgeSizeForCreation;
        size_t size =
            neighborhoodGraph.NeighborhoodGraph::property.edgeSizeForCreation;
        // add distances from a current object to subsequence objects to imitate
        // of sequential insertion.

        sort(output.begin(), output.end()); // sort by batchIdx

        for (size_t idxi = 0; idxi < dataSize; idxi++) {
            // add distances
            ObjectDistances &objs = *output[idxi].results;
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
    } // if (neighborhoodGraph.graphType == NeighborhoodGraph::GraphTypeUDNNG)
    // insert resultant objects into the graph as edges
    for (size_t i = 0; i < dataSize; i++) {
        CreateIndexJob &gr = output[i];
        if ((*gr.results).size() == 0) {
        }
        if (static_cast<int>(gr.id) >
                neighborhoodGraph.NeighborhoodGraph::property
                    .edgeSizeForCreation &&
            static_cast<int>(gr.results->size()) <
                neighborhoodGraph.NeighborhoodGraph::property
                    .edgeSizeForCreation) {
            cerr << "createIndex: Warning. The specified number of edges could "
                    "not be acquired, because the pruned parameter [-S] might "
                    "be set."
                 << endl;
            cerr << "  The node id=" << gr.id << endl;
            cerr << "  The number of edges for the node=" << gr.results->size()
                 << endl;
            cerr << "  The pruned parameter (edgeSizeForSearch [-S])="
                 << neighborhoodGraph.NeighborhoodGraph::property
                        .edgeSizeForSearch
                 << endl;
        }
        neighborhoodGraph.insertNode(gr.id, *gr.results);
    }
}
```

```cpp
void insertNode(ObjectID id, ObjectDistances &objects) {
    switch (property.graphType) {
    case GraphTypeANNG:
        insertANNGNode(id, objects);
        break;
    case GraphTypeIANNG:
        insertIANNGNode(id, objects);
        break;
    case GraphTypeONNG:
        insertONNGNode(id, objects);
        break;
    case GraphTypeKNNG:
        insertKNNGNode(id, objects);
        break;
    case GraphTypeBKNNG:
        insertBKNNGNode(id, objects);
        break;
    case GraphTypeNone:
        NGTThrowException("NGT::insertNode: GraphType is not specified.");
        break;
    default:
        NGTThrowException("NGT::insertNode: GraphType is invalid.");
        break;
    }
}

int truncateEdges(ObjectID id) {
    GraphNode &results = *getNode(id);
    if (results.size() == 0) {
        return -1;
    }

    size_t truncationSize = NGT_TRUNCATION_THRESHOLD;
    if (truncationSize < (size_t)property.edgeSizeForCreation) {
        truncationSize = property.edgeSizeForCreation;
    }
    return truncateEdgesOptimally(id, results, truncationSize);
}

void insertANNGNode(ObjectID id, ObjectDistances &results) {
    repository.insert(id, results);
    std::queue<ObjectID> truncateQueue;
    for (ObjectDistances::iterator ri = results.begin();
            ri != results.end(); ri++) {
        assert(id != (*ri).id);
        if (addEdge((*ri).id, id, (*ri).distance)) {
            truncateQueue.push((*ri).id);
        }
    }
    while (!truncateQueue.empty()) {
        ObjectID tid = truncateQueue.front();
        truncateEdges(tid);
        truncateQueue.pop();
    }
    return;
}

void insertONNGNode(ObjectID id, ObjectDistances &results) {
    if (property.truncationThreshold != 0) {
        std::stringstream msg;
        msg << "NGT::insertONNGNode: truncation should be disabled!"
            << std::endl;
        NGTThrowException(msg);
    }
    int count = 0;
    for (ObjectDistances::iterator ri = results.begin();
            ri != results.end(); ri++, count++) {
        assert(id != (*ri).id);
        if (count >= property.incomingEdge) {
            break;
        }
        addEdge((*ri).id, id, (*ri).distance);
    }
    if (static_cast<int>(results.size()) > property.outgoingEdge) {
        results.resize(property.outgoingEdge);
    }
    repository.insert(id, results);
}
```

```cpp
int NeighborhoodGraph::truncateEdgesOptimally(ObjectID id, GraphNode &results, size_t truncationSize) {

    ObjectDistances delNodes;

    size_t osize = results.size();

    size_t resSize = 2;
    TruncationSearchThreadPool threads(property.truncationThreadPoolSize);
    TruncationSearchSharedData sd(*this, id, resSize, 1.1);
    threads.setSharedData(&sd);
    threads.create();

    try {
        for (size_t i = truncationSize; i < results.size(); i++) {
            if (id == results[i].id) {
                continue;
            }
            delNodes.push_back(results[i]);
        }

        GraphNode::iterator ri = results.begin();
        ri += truncationSize;
        results.erase(ri, results.end());

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
        TruncationSearchThreadPool::OutputJobQueue &output =
            threads.getOutputJobQueue();
        TruncationSearchJob job;

        for (; retry == true; resSize = maxResSize) {
            retry = false;
            sd.resultSize = resSize;
            size_t nodeidx = 0;
            for (;;) {
                size_t nodeSize = 0;
                for (; nodeidx < delNodes.size(); nodeidx++) {
                    if (delNodes[nodeidx].id == 0) {
                        continue;
                    }
                    nodeSize++;
                    job.object =
                        getObjectRepository().get(delNodes[nodeidx].id);
                    job.idx = nodeidx;
                    job.start.id = id;
                    job.start.distance = delNodes[nodeidx].distance;
                    job.radius = FLT_MAX;
                    threads.pushInputQueue(job);
                    if (nodeSize >= batchSize) {
                        break;
                    }
                }
                if (nodeSize == 0) {
                    break;
                }
                threads.waitForFinish();

                if (output.size() != nodeSize) {
                    nodeSize = output.size();
                }
                size_t cannotMoveCnt = 0;
                for (size_t i = 0; i < nodeSize; i++) {
                    TruncationSearchJob &ojob = output.front();
                    ObjectID nearestID = ojob.nearest.id;
                    size_t idx = ojob.idx;
                    if (nearestID == delNodes[idx].id) {
                        delNodes[idx].id = 0;
                        output.pop_front();
                        continue;
                    } else if (nearestID == id) {
                        cannotMoveCnt++;
                        if ((resSize < maxResSize) && (cannotMoveCnt > 1)) {
                            retry = true;
                            output.pop_front();
                            continue;
                        }
                    } else {
                    }

                    ObjectID tid = delNodes[idx].id;
                    delNodes[idx].id = 0;

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
                    output.pop_front();
                }
            }
        }

        int cnt = 0;
        for (size_t i = 0; i < delNodes.size(); i++) {
            if (delNodes[i].id != 0) {
                cnt++;
            }
        }
        if (cnt != 0) {
            for (size_t i = 0; i < delNodes.size(); i++) {
                if (delNodes[i].id != 0) {
                }
            }
        }
        threads.terminate();
    } catch (Exception &err) {
        threads.terminate();
        Exception e(err);
        throw e;
    }

    size_t delsize = osize - results.size();

    return delsize;
}
```




*参考：*

[Neighborhood Graph and Tree for Indexing High-dimensional Data](https://github.com/yahoojapan/NGT)