
### 拷贝控制

拷贝控制操作（copy control）:
* 拷贝构造函数
* 拷贝赋值运算符
* 移动构造函数
* 移动赋值函数
* 析构函数

#### 拷贝构造函数

* 如果一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数。
* `class Foo { public: Foo(const Foo&); }`
* 如果没有自定义拷贝构造函数，即使我们定义了其他构造函数，编译器也会合成一个拷贝构造函数。
* 合成的拷贝构造函数会将其参数的成员逐个拷贝到正在创建的对象中。
* 拷贝初始化
  * 将右侧运算对象拷贝到正在创建的对象中，如果需要，还需进行类型转换。
  * 通常使用拷贝构造函数完成。
* 出现场景：
  * 用=定义变量时。
  * 将一个对象作为实参传递给一个非引用类型的形参。
  * 从一个返回类型为非引用类型的函数返回一个对象。
  * 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员。
  * 某些类类型会对分配对象使用拷贝初始胡，如标准库容器或调用 insert 或 push 成员，emplace 成员创建的元素都进行直接初始化。


#### 拷贝赋值运算符

* `class Foo { public: Foo& operator=(const Foo&); }`
* 返回指向其左侧运算对象的引用
* 合成拷贝赋值运算符：将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员。

#### 析构函数

* 析构函数执行与构造函数相反，构造函数初始化对象的非 static 数据成员，析构函数释放对象使用的资源，并销毁对象的非 static 数据成员。
* `class Foo { public: ~Foo(); }`
* 析构函数不接受参数，因此无法被重载。
* 调用时机：
    * 变量在离开其作用域时。
    * 当一个对象被销毁时，其成员被销毁。
    * 容器被销毁时，其元素被销毁。
    * 动态分配的对象，当对指向它的指针应用delete运算符时。
    * 对于临时对象，当创建它的完整表达式结束时。
    * 智能指针是类类型，具有析构函数，因此与普通指针不同，在析构阶段会被自动销毁。（当指向一个对象的引用或指针离开作用域时，析构函数不会执行）

#### 三/五法则
* 需要析构函数的类也需要拷贝和赋值操作。
* 需要拷贝操作的类也需要赋值操作，反之亦然。

```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    ~HasPtr() { delete ps; }
}

HasPtr f(HasPtr hp) {
    HasPtr ret = hp;    // 拷贝给定的 HasPtr
    return ret;         // ret 和 hp 都被销毁
}

HasPtr p("some values");
f(p);   // f 结束时，p.ps 指向内存被释放
HasPtr q(p);    // p 和 q 都指向无效内存
```

#### 阻止拷贝

* 大多数类应该定义默认构造函数、拷贝构造函数和拷贝赋值运算符，无论是隐式地还是显式地。
* 定义删除的函数：=delete。
* 与 =default 不同的是，可以对任何函数指定 =delete，=default 只能对编译器可以合成的默认构造函数或拷贝控制成员使用。
* 析构函数不能是删除的成员。

#### 拷贝控制和资源管理

类的行为可以像一个值，也可以像一个指针。
* 行为像值：对象有自己的状态，副本和原对象是完全独立的。
* 行为像指针：共享状态，拷贝一个这种类的对象时，副本和原对象使用相同的底层数据。

### 对象移动

* 很多拷贝操作后，原对象会被销毁，因此引入移动操作可以大幅度提升性能。
* 在新标准中，我们可以用容器保存不可拷贝的类型，只要它们可以被移动即可。
* 标准库容器、string和shared_ptr类既可以支持移动也支持拷贝。IO类和unique_ptr类可以移动但不能拷贝。

#### 右值引用

* 新标准引入右值引用以支持移动操作。
* 通过&&获得右值引用。
* 只能绑定到一个将要销毁的对象。
* 常规引用可以称之为左值引用。
* 左值持久，右值短暂。

```cpp
int i = 42; 
int &&rr = i; // 错误，不能将右值引用绑定到左值上
int &r2 = i * 42; // 错误，i*42 是右值
const int &r3 = i * 42;  // 正确，将 const 引用绑定到右值上
int &&rr2 = i * 42; // 正确
```

#### move 函数

* `int &&rr2 = std::move(rr1);`
* move告诉编译器，我们有一个左值，但我希望像右值一样处理它。
* 调用move意味着：除了对rr1赋值或者销毁它外，我们将不再使用它。
* 使用 move 的代码应该使用 std::move 而不是 move，避免潜在的命名冲突。


*TODO*

* 动态内存不会回收？