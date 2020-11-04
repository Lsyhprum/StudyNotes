# SPTAG 算法

```

```

## Scalable k-NN graph construction for visual descriptors

递归划分

邻域传播

## Query-Driven Iterated Neighborhood Graph Search
for Large Scale Indexing

搜索策略 - 基于查询历史， 添加扰动

## Trinary-Projection Trees for Approximate
Nearest Neighbor Search

初始化策略 - TP 树 / KD 树

## SPTAG 源码分析

### 构建索引

```cpp
// 测试代码

// algo 初始化算法: KDT/BKT 
// distCalcMethod 距离计算方法
// vec 向量
// meta
// out 索引保存文件
template <typename T>
void Build(SPTAG::IndexAlgoType algo, std::string distCalcMethod, std::shared_ptr<SPTAG::VectorSet>& vec, std::shared_ptr<SPTAG::MetadataSet>& meta, const std::string out)
{
    // 初始化 KDT / BKT 索引
    std::shared_ptr<SPTAG::VectorIndex> vecIndex = SPTAG::VectorIndex::CreateInstance(algo, SPTAG::GetEnumValueType<T>());
    ...

    vecIndex->SetParameter("DistCalcMethod", distCalcMethod);
    vecIndex->SetParameter("NumberOfThreads", "16");

    BOOST_CHECK(SPTAG::ErrorCode::Success == vecIndex->BuildIndex(vec, meta));
    ...
} 

// 初始化索引
std::shared_ptr<VectorIndex>
VectorIndex::CreateInstance(IndexAlgoType p_algo, VectorValueType p_valuetype)
{
    ...

    if (p_algo == IndexAlgoType::BKT) {
        ...
        return std::shared_ptr<VectorIndex>(new BKT::Index<Type>); 
        ...
    }
    else if (p_algo == IndexAlgoType::KDT) {
        ...
        return std::shared_ptr<VectorIndex>(new KDT::Index<Type>);
        ...
    }
}
  
// 构建索引
ErrorCode
VectorIndex::BuildIndex(std::shared_ptr<VectorSet> p_vectorSet,
    std::shared_ptr<MetadataSet> p_metadataSet, bool p_withMetaIndex)
{
    ...
    
    // 将数据转移至内部数据结构
    m_pMetadata = std::move(p_metadataSet);
    if (p_withMetaIndex && m_pMetadata != nullptr)
    {
        BuildMetaMapping(false);
    }

    // 转至 KDT/BKT 重写 BuildIndex 方法
    BuildIndex(p_vectorSet->GetData(), p_vectorSet->Count(), p_vectorSet->Dimension());
    return ErrorCode::Success;
}
```

KDT
```cpp
// KDT 构建索引方法
template <typename T>
ErrorCode Index<T>::BuildIndex(const void* p_data, SizeType p_vectorNum, DimensionType p_dimension)
{
    ...

    // m_pSamples 保存数据的数据结构
    m_pSamples.Initialize(p_vectorNum, p_dimension, (T*)p_data, false);
    m_deletedID.Initialize(p_vectorNum);

    // 多线程相关初始化代码
    ...

    // 构建 KDT 
    m_pTrees.BuildTrees<T>(m_pSamples, m_iNumberOfThreads);
    
    // 构建 SPTAG 图
    m_pGraph.BuildGraph<T>(this);

    ...
}

// 构建树索引
template <typename T>
void BuildTrees(const Dataset<T>& data, int numOfThreads, std::vector<SizeType>* indices = nullptr)
{
    std::vector<SizeType> localindices;
    if (indices == nullptr) {
        // KDT 树根数量 -> 维度个数
        localindices.resize(data.R());
        for (SizeType i = 0; i < localindices.size(); i++) localindices[i] = i;
    }

    // 初始化树数据结构
    // m_iTreeNumber 默认为 2， m_iSamples 1000
    m_pTreeRoots.resize(m_iTreeNumber * localindices.size());
    m_pTreeStart.resize(m_iTreeNumber, 0);
#pragma omp parallel for num_threads(numOfThreads)
    for (int i = 0; i < m_iTreeNumber; i++)
    {
        Sleep(i * 100); std::srand(clock());

        std::vector<SizeType> pindices(localindices.begin(), localindices.end());
        std::random_shuffle(pindices.begin(), pindices.end());

        m_pTreeStart[i] = i * (SizeType)pindices.size();
        LOG(Helper::LogLevel::LL_Info, "Start to build KDTree %d\n", i + 1);
        SizeType iTreeSize = m_pTreeStart[i];
        DivideTree<T>(data, pindices, 0, (SizeType)pindices.size() - 1, m_pTreeStart[i], iTreeSize);
        LOG(Helper::LogLevel::LL_Info, "%d KDTree built, %d %zu\n", i + 1, iTreeSize - m_pTreeStart[i], pindices.size());
    }
}

// 分治构建树
template <typename T>
void DivideTree(const Dataset<T>& data, std::vector<SizeType>& indices, SizeType first, SizeType last, SizeType index, SizeType &iTreeSize) {
    ChooseDivision<T>(data, m_pTreeRoots[index], indices, first, last);
    SizeType i = Subdivide<T>(data, m_pTreeRoots[index], indices, first, last);
    if (i - 1 <= first)
    {
        m_pTreeRoots[index].left = -indices[first] - 1;
    }
    else
    {
        iTreeSize++;
        m_pTreeRoots[index].left = iTreeSize;
        DivideTree<T>(data, indices, first, i - 1, iTreeSize, iTreeSize);
    }
    if (last == i)
    {
        m_pTreeRoots[index].right = -indices[last] - 1;
    }
    else
    {
        iTreeSize++;
        m_pTreeRoots[index].right = iTreeSize;
        DivideTree<T>(data, indices, i, last, iTreeSize, iTreeSize);
    }
}

// 选取分治结点
template <typename T>
SizeType Subdivide(const Dataset<T>& data, const KDTNode& node, std::vector<SizeType>& indices, const SizeType first, const SizeType last) const
{
    SizeType i = first;
    SizeType j = last;
    // decide which child one point belongs
    while (i <= j)
    {
        SizeType ind = indices[i];
        const T* v = (const T*)data[ind];
        float val = v[node.split_dim];
        if (val < node.split_value)
        {
            i++;
        }
        else
        {
            std::swap(indices[i], indices[j]);
            j--;
        }
    }
    // if all the points in the node are equal,equally split the node into 2
    if ((i == first) || (i == last + 1))
    {
        i = (first + last + 1) / 2;
    }
    return i;
}

// 构建图索引 RNG
template <typename T>
void BuildGraph(VectorIndex* index, const std::unordered_map<SizeType, SizeType>* idmap = nullptr)
{
    LOG(Helper::LogLevel::LL_Info, "build RNG graph!\n");

    // 初始化图索引
    m_iGraphSize = index->GetNumSamples();
    m_iNeighborhoodSize = m_iNeighborhoodSize * m_iNeighborhoodScale;
    m_pNeighborhoodGraph.Initialize(m_iGraphSize, m_iNeighborhoodSize);

    ...

    BuildInitKNNGraph<T>(index, idmap);
    LOG(Helper::LogLevel::LL_Info, "BuildInitKNNGraph time (s): %lld\n", std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count());

    RefineGraph<T>(index, idmap);

    if (idmap != nullptr) {
        for (auto iter = idmap->begin(); iter != idmap->end(); iter++)
            if (iter->first < 0)
            {
                m_pNeighborhoodGraph[-1 - iter->first][m_iNeighborhoodSize - 1] = -2 - iter->second;
            }
    }

    LOG(Helper::LogLevel::LL_Info, "BuildGraph time (s): %lld\n", std::chrono::duration_cast<std::chrono::seconds>(t3 - t1).count());
}

template <typename T>
void BuildInitKNNGraph(VectorIndex* index, const std::unordered_map<SizeType, SizeType>* idmap)
{
    COMMON::Dataset<float> NeighborhoodDists(m_iGraphSize, m_iNeighborhoodSize);
    std::vector<std::vector<SizeType>> TptreeDataIndices(m_iTPTNumber, std::vector<SizeType>(m_iGraphSize));
    std::vector<std::vector<std::pair<SizeType, SizeType>>> TptreeLeafNodes(m_iTPTNumber, std::vector<std::pair<SizeType, SizeType>>());

    for (SizeType i = 0; i < m_iGraphSize; i++)
        for (DimensionType j = 0; j < m_iNeighborhoodSize; j++)
            (NeighborhoodDists)[i][j] = MaxDist;

    auto t1 = std::chrono::high_resolution_clock::now();
    LOG(Helper::LogLevel::LL_Info, "Parallel TpTree Partition begin\n");
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < m_iTPTNumber; i++)
    {
        Sleep(i * 100); std::srand(clock());
        for (SizeType j = 0; j < m_iGraphSize; j++) TptreeDataIndices[i][j] = j;
        std::random_shuffle(TptreeDataIndices[i].begin(), TptreeDataIndices[i].end());
        PartitionByTptree<T>(index, TptreeDataIndices[i], 0, m_iGraphSize - 1, TptreeLeafNodes[i]);
        LOG(Helper::LogLevel::LL_Info, "Finish Getting Leaves for Tree %d\n", i);
    }
    LOG(Helper::LogLevel::LL_Info, "Parallel TpTree Partition done\n");
    auto t2 = std::chrono::high_resolution_clock::now();
    LOG(Helper::LogLevel::LL_Info, "Build TPTree time (s): %lld\n", std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count());

    for (int i = 0; i < m_iTPTNumber; i++)
    {
#pragma omp parallel for schedule(dynamic)
        for (SizeType j = 0; j < (SizeType)TptreeLeafNodes[i].size(); j++)
        {
            SizeType start_index = TptreeLeafNodes[i][j].first;
            SizeType end_index = TptreeLeafNodes[i][j].second;
            if ((j * 5) % TptreeLeafNodes[i].size() == 0) LOG(Helper::LogLevel::LL_Info, "Processing Tree %d %d%%\n", i, static_cast<int>(j * 1.0 / TptreeLeafNodes[i].size() * 100));
            for (SizeType x = start_index; x < end_index; x++)
            {
                for (SizeType y = x + 1; y <= end_index; y++)
                {
                    SizeType p1 = TptreeDataIndices[i][x];
                    SizeType p2 = TptreeDataIndices[i][y];
                    float dist = index->ComputeDistance(index->GetSample(p1), index->GetSample(p2));
                    if (idmap != nullptr) {
                        p1 = (idmap->find(p1) == idmap->end()) ? p1 : idmap->at(p1);
                        p2 = (idmap->find(p2) == idmap->end()) ? p2 : idmap->at(p2);
                    }
                    COMMON::Utils::AddNeighbor(p2, dist, (m_pNeighborhoodGraph)[p1], (NeighborhoodDists)[p1], m_iNeighborhoodSize);
                    COMMON::Utils::AddNeighbor(p1, dist, (m_pNeighborhoodGraph)[p2], (NeighborhoodDists)[p2], m_iNeighborhoodSize);
                }
            }
        }
        TptreeDataIndices[i].clear();
        TptreeLeafNodes[i].clear();
    }
    TptreeDataIndices.clear();
    TptreeLeafNodes.clear();

    auto t3 = std::chrono::high_resolution_clock::now();
    LOG(Helper::LogLevel::LL_Info, "Process TPTree time (s): %lld\n", std::chrono::duration_cast<std::chrono::seconds>(t3 - t2).count());
}
```

第一个实现
init : KDT

prune : KANNG

第二个实现
init : BKM 

prune : RNG