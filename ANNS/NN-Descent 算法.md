# NN-Descent 算法

```
@inproceedings{DBLP:conf/www/DongCL11,
  author    = {Wei Dong and
               Moses Charikar and
               Kai Li},
  editor    = {Sadagopan Srinivasan and
               Krithi Ramamritham and
               Arun Kumar and
               M. P. Ravindra and
               Elisa Bertino and
               Ravi Kumar},
  title     = {Efficient k-nearest neighbor graph construction for generic imilarity
               measures},
  booktitle = {Proceedings of the 20th International Conference on World ide Web,
               {WWW} 2011, Hyderabad, India, March 28 - April 1, 2011},
  pages     = {577--586},
  publisher = {{ACM}},
  year      = {2011},
  url       = {https://doi.org/10.1145/1963405.1963487},
  doi       = {10.1145/1963405.1963487},
  timestamp = {Tue, 06 Nov 2018 16:57:07 +0100},
  biburl    = {https://dblp.org/rec/conf/www/DongCL11.bib},
  bibsource = {dblp computer science bibliography, https://dblp.org}
}
```



### Introduction

**NN-Descent 算法** 是一种构建 **近似 K 近邻图** 的算法。主要用于解决之前基于 K 近邻图算法的几个缺陷：

* 时间复杂度高: Brute-force 时间复杂度为 $O(n^2)$, 不适合大数据集; NN-Descent 时间复杂度为 $O(n^{1.11})$ 到 $O(n^{1.14})$ 之间。
* 标准适用情形少：很多近邻搜索算法只适用特定相似度度量标准；NN-Descent 适用于任意度量标准。
* 不支持并行计算：构建全局索引难以进行并行计算; NN-Descent 通过局部搜索避免依赖全局索引。
* 计算成本高：LSH 为了获得精确结果需要付出较高计算成本，且对于不同相似度度量标准需设计不同散列函数。

NN-Descent 主要思想十分简单：**邻居的邻居很可能是邻居**。即在初始 K-NN 图中，通过探索每个点的 **邻居的邻居** 来提升结果的召回率。

### Algorithm

#### 基础算法——我的邻居的邻居可能是我的邻居

NN-Descent 算法在离线构建阶段首先对每个点 **随机选取** K近邻，之后迭代筛选出更优的邻居的邻居，来替代 KNN 和 反向 KNN 的候选集。当没有明显提高时终止迭代。

```
Data: dataset V, similarity oracle σ, K 
Result: K-NN list B                        // 候选集
begin 
  B[v] ←− Sample(V,K) × {∞}, ∀v ∈ V 	  // 随机抽选 k 个入口点
  loop 
    R ←− Reverse(B) 					   // 更新反向集，即更新无向图 
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

#### 局部连接——介绍我的邻居了解彼此

探索邻居的邻居可以通过局部连接来优化替代，以避免 **冗余计算**，提高效率。局部连接对邻居集内每一对不同的邻居进行相似度计算，并更新每对邻居各自的邻居集。

举个栗子：

在 基础算法 中，基础关系为 a -> b -> c，b∈B(a)，c∈B(b)，当探索到 a 时，我们需要比较 a 与 c，当探索到 c 时，我们也需要比较 a 与 c。同样地，a与c之间的比较可通过对B[b]进行局部连接来实现，即 b <- a -> c。

局部连接实现起来很简单，那么它有什么好处呢？

* **减少算法复杂度**。如果每一个对象的邻居的个数平均为 K，基础算法每次迭代探索每一个对象的邻居的邻居时将接触到 K^2 个点，而局部连接只需要接触 K 个点。

* **提升 Cache 命中率/减少数据复制**。单机部署时，运用 Cache 访问的局部性原理，从而加速了 K 近邻图的构建。分布式实施时，能减少机器之间数据的复制。


#### 增量搜索——见过面的邻居记下他的名字

随着算法的执行，每一个对象的K近邻更新的幅度逐渐减小。而且，在某次迭代中参与比较的两个点，就更可能在之前的迭代中已经比较过了。这就造成冗余计算，而增量搜索就是要解决这个问题的。

给每一个点的K近邻列表中的每一个对象附加一个布尔标记，当一个新对象插入到该列表中的某个条目时，它的标记初始化为true。
只有当两个对象至少一个的标记为 true，它们才进行局部连接。一个对象参与局部连接后，它被标记为 false。


#### 采样——抽选部分邻居了解彼此

采样是为了解决以下两个问题：

* 局部连接的高成本。一次迭代，就算只考虑K近邻，时间复杂度为K^2N，如果再考虑反向近邻，时间复杂度更高。
* 冗余计算。两个点同时连接到多个不同对象，这两个点将比较多次。

选取部分未标记的邻居进行局部连接。只根据取样对象和标记为false的对象来构建反向邻居列表。对构建得的反向邻居列表再次取样。
因此，我们就可以通过取样率 ρ 来进行精度和速度的 trade-off。


#### 提前终止——DONE IS BETTER THAN PERFECT

基础算法中，K近邻图不再被改善则算法终止。实际上，开始迭代时，K近邻图能充分的更新，而随着迭代的进行，需要更多次迭代才能获得略微的提升，此时的迭代就显得意义不大了，考虑到迭代的计算成本，这些迭代其实没必要执行。为了解决这个问题，本文采取的方案是：在每次迭代中，统计所有对象K近邻列表更新的次数 count，当 count < δKN 时终止程序继续执行。

其中 δ是精度参数，它粗略反应了由于提前终止允许错过的真正的K近邻的比例。

#### 完整算法

```
Data: dataset V, similarity oracle σ, K, ρ, δ // ρ 取样率、δ 精度参数
Result: K-NN list B 
begin 
  B[v] ←− Sample(V,K) × {<∞, true>} ∀v ∈ V 
  loop 
    parallel for v ∈ V do 						// 并行计算

      // 优化后的算法将候选池根据是否访问过分为两部分
      old[v] ←− all items in B[v] with a false flag // 增量搜索
      new[v] ←− ρK items in B[v] with a true flag   // 采样
      Mark sampled items in B[v] as false;

    old′ ← Reverse(old), new′ ← Reverse(new) 		// 更新反向集
    c ←− 0 //update counter 
    
    parallel for v ∈ V do 
      old[v] ←− old[v] ∪ Sample(old′[v], ρK) 		// 更新增量搜索列表
      new[v] ←− new[v] ∪ Sample(new′[v], ρK) 
      for u1, u2 ∈ new[v], u1 < u2 or u1 ∈ new[v], u2 ∈ old[v] do 		// 局部连接
      	l ←− σ(u1, u2) // c and B[.] are synchronized.
      	c ←− c+UpdateNN(B[u1], <u2, l, true>)
      	c ←− c+UpdateNN(B[u2], <u1, l, true>)
    return B if c < δNK								// 提前终止
```

#### 源码解析

构建索引阶段
```cpp
void IndexGraph::Build(size_t n, const float *data, const Parameters &parameters) {
  ...

  // 入口点策略 -> 随机入口点
  InitializeGraph(parameters);

  // NN-Descent 核心代码
  NNDescent(parameters);

  final_graph_.reserve(nd_);
  unsigned K = parameters.Get<unsigned>("K");
  for (unsigned i = 0; i < nd_; i++) {
    std::vector<unsigned> tmp;

    // 裁边策略 -> 选取前 K 个近邻
    std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
    for (unsigned j = 0; j < K; j++) {
      tmp.push_back(graph_[i].pool[j].id);
    }
    tmp.reserve(K);
    final_graph_.push_back(tmp);
    ...
  }
  ...
}

void IndexGraph::InitializeGraph(const Parameters &parameters) {

  const unsigned L = parameters.Get<unsigned>("L");
  const unsigned S = parameters.Get<unsigned>("S");

  graph_.reserve(nd_);
  std::mt19937 rng(rand());
  for (unsigned i = 0; i < nd_; i++) {
    graph_.push_back(nhood(L, S, rng, (unsigned) nd_));
  }
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; i++) {
    const float *query = data_ + i * dimension_;
    std::vector<unsigned> tmp(S + 1);
    initializer_->Search(query, data_, S + 1, parameters, tmp.data());

    for (unsigned j = 0; j < S; j++) {
      unsigned id = tmp[j];
      if (id == i)continue;
      float dist = distance_->compare(data_ + i * dimension_, data_ + id * dimension_, (unsigned) dimension_);

      graph_[i].pool.push_back(Neighbor(id, dist, true));
    }
    std::make_heap(graph_[i].pool.begin(), graph_[i].pool.end());
    graph_[i].pool.reserve(L);
  }
}

void IndexGraph::join() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
  for (unsigned n = 0; n < nd_; n++) {
    graph_[n].join([&](unsigned i, unsigned j) {
      if(i != j){
        float dist = distance_->compare(data_ + i * dimension_, data_ + j * dimension_, dimension_);
        graph_[i].insert(j, dist);
        graph_[j].insert(i, dist);
      }
    });
  }
}
void IndexGraph::update(const Parameters &parameters) {
  unsigned S = parameters.Get<unsigned>("S");
  unsigned R = parameters.Get<unsigned>("R");
  unsigned L = parameters.Get<unsigned>("L");
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; i++) {
    std::vector<unsigned>().swap(graph_[i].nn_new);
    std::vector<unsigned>().swap(graph_[i].nn_old);
    //std::vector<unsigned>().swap(graph_[i].rnn_new);
    //std::vector<unsigned>().swap(graph_[i].rnn_old);
    //graph_[i].nn_new.clear();
    //graph_[i].nn_old.clear();
    //graph_[i].rnn_new.clear();
    //graph_[i].rnn_old.clear();
  }
#pragma omp parallel for
  for (unsigned n = 0; n < nd_; ++n) {
    auto &nn = graph_[n];
    std::sort(nn.pool.begin(), nn.pool.end());
    if(nn.pool.size()>L)nn.pool.resize(L);
    nn.pool.reserve(L);
    unsigned maxl = std::min(nn.M + S, (unsigned) nn.pool.size());
    unsigned c = 0;
    unsigned l = 0;
    //std::sort(nn.pool.begin(), nn.pool.end());
    //if(n==0)std::cout << nn.pool[0].distance<<","<< nn.pool[1].distance<<","<< nn.pool[2].distance<< std::endl;
    while ((l < maxl) && (c < S)) {
      if (nn.pool[l].flag) ++c;
      ++l;
    }
    nn.M = l;
  }
#pragma omp parallel for
  for (unsigned n = 0; n < nd_; ++n) {
    auto &nnhd = graph_[n];
    auto &nn_new = nnhd.nn_new;
    auto &nn_old = nnhd.nn_old;
    for (unsigned l = 0; l < nnhd.M; ++l) {
      auto &nn = nnhd.pool[l];
      auto &nhood_o = graph_[nn.id];  // nn on the other side of the edge

      if (nn.flag) {
        nn_new.push_back(nn.id);
        if (nn.distance > nhood_o.pool.back().distance) {
          LockGuard guard(nhood_o.lock);
          if(nhood_o.rnn_new.size() < R)nhood_o.rnn_new.push_back(n);
          else{
            unsigned int pos = rand() % R;
            nhood_o.rnn_new[pos] = n;
          }
        }
        nn.flag = false;
      } else {
        nn_old.push_back(nn.id);
        if (nn.distance > nhood_o.pool.back().distance) {
          LockGuard guard(nhood_o.lock);
          if(nhood_o.rnn_old.size() < R)nhood_o.rnn_old.push_back(n);
          else{
            unsigned int pos = rand() % R;
            nhood_o.rnn_old[pos] = n;
          }
        }
      }
    }
    std::make_heap(nnhd.pool.begin(), nnhd.pool.end());
  }
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; ++i) {
    auto &nn_new = graph_[i].nn_new;
    auto &nn_old = graph_[i].nn_old;
    auto &rnn_new = graph_[i].rnn_new;
    auto &rnn_old = graph_[i].rnn_old;
    if (R && rnn_new.size() > R) {
      std::random_shuffle(rnn_new.begin(), rnn_new.end());
      rnn_new.resize(R);
    }
    nn_new.insert(nn_new.end(), rnn_new.begin(), rnn_new.end());
    if (R && rnn_old.size() > R) {
      std::random_shuffle(rnn_old.begin(), rnn_old.end());
      rnn_old.resize(R);
    }
    nn_old.insert(nn_old.end(), rnn_old.begin(), rnn_old.end());
    if(nn_old.size() > R * 2){nn_old.resize(R * 2);nn_old.reserve(R*2);}
    std::vector<unsigned>().swap(graph_[i].rnn_new);
    std::vector<unsigned>().swap(graph_[i].rnn_old);
  }
}

void IndexGraph::NNDescent(const Parameters &parameters) {
  unsigned iter = parameters.Get<unsigned>("iter");
  std::mt19937 rng(rand());
  std::vector<unsigned> control_points(_CONTROL_NUM);
  std::vector<std::vector<unsigned> > acc_eval_set(_CONTROL_NUM);
  GenRandom(rng, &control_points[0], control_points.size(), nd_);
  generate_control_set(control_points, acc_eval_set, nd_);
  for (unsigned it = 0; it < iter; it++) {
    join();
    update(parameters);
    //checkDup();
    eval_recall(control_points, acc_eval_set);
    std::cout << "iter: " << it << std::endl;
  }
}


```

搜索阶段
```cpp

void IndexGraph::Search(
    const float *query,
    const float *x,
    size_t K,
    const Parameters &parameter,
    unsigned *indices) {
  const unsigned L = parameter.Get<unsigned>("L_search");

  std::vector<Neighbor> retset(L+1);
  std::vector<unsigned> init_ids(L);
  std::mt19937 rng(rand());
  GenRandom(rng, init_ids.data(), L, (unsigned)nd_);

  std::vector<char> flags(nd_);
  memset(flags.data(), 0, nd_ * sizeof(char));
  for(unsigned i=0; i<L; i++){
    unsigned id = init_ids[i];
    float dist = distance_->compare(data_ + dimension_*id, query, (unsigned)dimension_);
    retset[i]=Neighbor(id, dist, true);
  }

  std::sort(retset.begin(), retset.begin()+L);
  int k=0;
  while(k < (int)L) {
    int nk = L;

    if (retset[k].flag) {
      retset[k].flag = false;
      unsigned n = retset[k].id;

      for (unsigned m = 0; m < final_graph_[n].size(); ++m) {
        unsigned id = final_graph_[n][m];
        if(flags[id])continue;
        flags[id] = 1;
        float dist = distance_->compare(query, data_ + dimension_ * id, (unsigned)dimension_);
        if(dist >= retset[L-1].distance)continue;
        Neighbor nn(id, dist, true);
        int r = InsertIntoPool(retset.data(), L, nn);

        //if(L+1 < retset.size()) ++L;
        if(r < nk)nk=r;
      }
      //lock to here
    }
    if(nk <= k)k = nk;
    else ++k;
  }
  for(size_t i=0; i < K; i++){
    indices[i] = retset[i].id;
  }
}
```

### Experimental 

本文提出了几个实验中具体考量的问题，可以作为论文实验部分架构的思考方向：

* 本算法的具体表现

* 本算法与其他算法的比较

* 精确度和查询花费与数据集规模的关系

* 如何选取适合的参数

* 本征维度如何影响算法的性能


### Conclusions

* 优点：时间复杂度较低, 在大多数数据集上为 O(n^1.14)，且易于并行化实现。
* 缺点：NN-Descent 在 本征维度较高 的数据集上表现较差，其适用于本征维度较低**(20) 的数据集。事实上真实数据集的本征维度大多都具有较低的本征维度。



*参考*：

[efanna_graph](https://github.com/ZJULearning/efanna_graph)

[NN-Descent构建K近邻图——论文超详细注解](https://blog.csdn.net/whenever5225/article/details/105598694)



