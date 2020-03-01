<a id="markdown-boost-学习笔记" name="boost-学习笔记"></a>
# Boost 学习笔记
> 书籍：Beyond the C++ Standard Library : An Introduction to Boost 
    > > 注记（笔记）

<!-- TOC -->

- [Boost 学习笔记](#boost-学习笔记)
    - [有用的](#有用的)
    - [Smart Pointer](#smart-pointer)
        - [智能指针 ：shared_ptr weak_ptr scoped_ptr  scoped_array  intrusive_ptr,](#智能指针-shared_ptr-weak_ptr-scoped_ptr--scoped_array--intrusive_ptr)
            - [Smart_ptr 库如何改进你的程序？](#smart_ptr-库如何改进你的程序)
            - [有三种典型的情况适合使用智能指针：](#有三种典型的情况适合使用智能指针)
            - [boost智能指针的优势](#boost智能指针的优势)
        - [scoped_ptr](#scoped_ptr)
            - [scoped_ptr 的用法](#scoped_ptr-的用法)
            - [scoped_ptr 和 Pimpl 用法](#scoped_ptr-和-pimpl-用法)
            - [scoped_ptr 与 const auto_ptr 的区别](#scoped_ptr-与-const-auto_ptr-的区别)
            - [总结](#总结)
        - [scoped_array](#scoped_array)
        - [shared_ptr](#shared_ptr)
            - [作用](#作用)
        - [Shared_ptr 定义](#shared_ptr-定义)
        - [Shared_ptr 内部构造](#shared_ptr-内部构造)
    - [代码示例](#代码示例)

<!-- /TOC -->

<a id="markdown-有用的" name="有用的"></a>
## 有用的
  ###  boost string_algo库 
- 头文件 boost/algorithm/string.hpp
- 这是一组与字符串相关的算法。包括很多有用的算法，用于大小写转换，空格清除，字符串分割，查找及替换，等
等。这组算法是目前C++标准库里已有功能的扩展。

<a id="markdown-smart-pointer" name="smart-pointer"></a>
## Smart Pointer


<a id="markdown-智能指针-shared_ptr-weak_ptr-scoped_ptr--scoped_array--intrusive_ptr" name="智能指针-shared_ptr-weak_ptr-scoped_ptr--scoped_array--intrusive_ptr"></a>
###  智能指针 ：shared_ptr weak_ptr scoped_ptr  scoped_array  intrusive_ptr,
<a id="markdown-smart_ptr-库如何改进你的程序" name="smart_ptr-库如何改进你的程序"></a>
#### Smart_ptr 库如何改进你的程序？
  - 使用 shared_ptr 进行对象的生存期自动管理，使得分享资源所有权变得有效且安全。
  - 使用 weak_ptr 可以安全地观测共享资源，避免了悬挂的指针。
  -  使用 scoped_ptr 和 scoped_array 限制资源的使用范围，使得代码更易于编写和维护，并有助于写出异常安全的代码。

<a id="markdown-有三种典型的情况适合使用智能指针" name="有三种典型的情况适合使用智能指针"></a>
#### 有三种典型的情况适合使用智能指针：
- 资源所有权的共享
-  要写异常安全的代码时
- 避免常见的错误，如资源泄漏

<a id="markdown-boost智能指针的优势" name="boost智能指针的优势"></a>
#### boost智能指针的优势
虽然 C++ 标准库中提供了 std::auto_ptr, 但是它不能
完全满足我们对智能指针的需求。例如，auto_ptr 不能用作 STL 容器的元素。Boost 的智能指针类填充了标准所留下来的缺口。

<a id="markdown-scoped_ptr" name="scoped_ptr"></a>
### scoped_ptr 
- 它不能转让所有权，scoped_ptr 永远不能被复制或被赋值，scoped_ptr 拥有它所指向的资源的所有权，并永远不会放弃这个所有权

- 成员函数：
  - explicit scoped_ptr(T* p=0) 构造函数，存储 p的一份拷贝。
  - ~scoped_ptr() 删除被指物。
  - void reset(T* p=0); 重置一个 scoped_ptr 就是删除它已保存的指针，如果它有的话，并重新保存 p
  - T* get() const; 返回保存的指针。应该小心地使用get，因为它可以直接操作裸指针。 get通常用于调用那些需要裸指针的函数。
  - operator unspecified_bool_type() const 返回 scoped_ptr 是否为非空。返回值的类型是未指明的，但这个类型可被用于 Boolean 的上下文中。在 if 语
句中最好使用这个类型转换函数，而不要用 get 去测试 scoped_ptr 的有效性
    - void swap(scoped_ptr& b) 交换两个 scoped_ptr 的内容。这个函数不会抛出异常。
    - template<typename T> void swap(scoped_ptr<T>& a,scoped_ptr<T>& b)<br>这个函数提供了交换两个scoped pointer的内容的更好的方法。之所以说它更好，是因为 swap(scoped1,
scoped2) 可以更广泛地用于很多指针类型，包括裸指针和第三方的智能指针。[2] scoped1.swap(scoped2) 则
只能用于它的定义所在的智能指针，而不能用于裸指针

<a id="markdown-scoped_ptr-的用法" name="scoped_ptr-的用法"></a>
#### scoped_ptr 的用法
- scoped_ptr 的用法与普通的指针没什么区别；最大的差别在于你不必再记得在指针上调用 delete，还有复制是不允许的。典型的指针操作(operator* 和 operator->)都被重载了，并提供了和裸指针一样的语法。用scoped_ptr 和用裸指针一样快，也没有大小上的增加，因此它们可以广泛使用。使用 boost::scoped_ptr时，包含头文件 "boost/scoped_ptr.hpp". 在声明一个scoped_ptr 时，用被指物的类型来指定类模板的参数。
- 代码展示：

```
#include <iostream>
#include "boost/scoped_ptr.hpp"
#include <string>


using namespace std;
using namespace boost;

using namespace std;

int main(int argc, char ** argv)
{

	scoped_ptr<string> st(new string("Scoped ptr  Inner Text"));

	//错误的做法，scoped_ptr 不能复制
	//st = new scoped_ptr<string>; 


	cout << *st <<endl<<"Is "<<st->size()<<" length"<<endl;

	*st = "文本已经改变！";	//但是scoped指针指向的内容是可以改变的，scoped_ptr 使用与普通指针没有区别！
	
	cout << endl << *st;




 cin.get();

// 此处 st 指针自动删除！不需要delete
	return 0;
}
```

- Tips:
  - 永远不要把 auto_ptr 放入标准库的容器里。如果你试一下，通常你会得到一个编译错误；如
果你没有得到错误，你就麻烦了。
    -   auto_ptr 转让所有权后（= 赋值）会变成一个空指针。
    -   由于 scoped_ptr::get 会返回一个裸指针，所以就有可能对 scoped_ptr 做一些有害的事情，其中有两件是你
尤其要避免的。
        - 不要删除这个裸指针。因为它会在 scoped_ptr 被销毁时再一次被删除。
        - 不要把这个裸指针保存到另一个 scoped_ptr (或其它任何的智能指针)里。因为这样也会两次删除这个指针，每个scoped_ptr 一次。简单地说，尽量少用 get, 除非你要使用那些要求你传送裸指针的遗留代码！
        - 如果你使用 scoped_ptr 作为一个类的成员，你就必须手工定义这个类的复制构造函数和赋值操作符。原因是 scoped_ptr 是不能复制的，因此聚集了它的类也变得不能复制了。

<a id="markdown-scoped_ptr-和-pimpl-用法" name="scoped_ptr-和-pimpl-用法"></a>
#### scoped_ptr 和 Pimpl 用法
- Tips:
  - 如果 pimpl 实例可以安全地被多个封装类(在这里是 pimpl_sample)的实例所共享，那
么用 boost::shared_ptr 来管理 pimpl 的生存期才是正确的选择。用 shared_ptr 比用 scoped_ptr 的优势
Beyond the C++ Standard Library : An Introduction to Boost
40
在于，不需要手工去定义复制构造函数和赋值操作符，而且可以定义空的析构函数，shared_ptr 被设计为可以正
确地用于未完成的类

<a id="markdown-scoped_ptr-与-const-auto_ptr-的区别" name="scoped_ptr-与-const-auto_ptr-的区别"></a>
#### scoped_ptr 与 const auto_ptr 的区别
-     scoped_ptr 可以被 reset, 在需要时可以删除并替换被指物。
-     而对于 const auto_ptr 这是不可能的


<a id="markdown-总结" name="总结"></a>
#### 总结
- 使用裸指针来写异常安全和无错误的代码是很复杂的。使用智能指针来自动地把动态分配对象的生存期限制在一个
明确的范围之内，是解决这种问题的一个有效的方法，并且提高了代码的可读性、可维护性和质量。scoped_ptr
明确地表示被指物不能被共享和转移。正如你所看到的，std::auto_ptr 可以从另一个 auto_ptr 那里窃取被指
物，那怕是无意的，这被认为是 auto_ptr 的最大的缺点。正是这个缺点使得 scoped_ptr 成为 auto_ptr 最
好的补充。当一个动态分配的对象被传送给 scoped_ptr, 它就成为了这个对象的唯一的拥有者。因为
scoped_ptr 几乎总是以自动变量或数据成员来分配的，因此它可以在离开作用域时正确地销毁，从而在执行流由
于返回语句或异常抛出而离开作用域时，总能释放它所管理的内存。
- 在以下情况时使用 scoped_ptr ：
  - 在可能有异常抛出的作用域里使用指针
  - 函数里有几条控制路径
  - 动态分配对象的生存期应被限制于特定的作用域内
  - 异常安全非常重要时(始终如此!)


<a id="markdown-scoped_array" name="scoped_array"></a>
### scoped_array
- 头文件: "boost/scoped_array.hpp"
-作用：
  - 防止错误调用 delete 操作符而不是 delete[] 操作符。
  - scoped_array 为数组做了 scoped_ptr 为单个对象的指针所做的事情：它负责释放内存。区
别只在于 scoped_array 是用 delete[] 操作符来做这件事的。

<a id="markdown-shared_ptr" name="shared_ptr"></a>
### shared_ptr
- 头文件: "boost/shared_ptr.hpp"
- 分类
  - 插入式(intrusive)
  - 非插入式(non-intrusive)

<a id="markdown-作用" name="作用"></a>
#### 作用
- 被管理的类可能拥有一些特性使得它更应该与引用计数智能指针一起使用。例如，它的复制操作很昂贵，或 者它所
代表的有些东西必须被多个实例共享，这些特性都值得去共享所有权。还有一种情形是共享的资源没有一个明确的拥
有者。使用引用计数智能指针可以在需要 访问共享资源的对象之间共享资源的所有权。引用计数智能指针还让你可
以把对象指针存入标准库的容器中而不会有泄漏的风险，特别是在面对异常或要从容器中删 除元素的时候。如果你
把指针放入容器，你就可以获得多态的好处，可以提高性能(如果复制的代价很高的话)，还可以通过把相同的对象放
入多个辅助容器来进行 特定的查找。

<a id="markdown-shared_ptr-定义" name="shared_ptr-定义"></a>
### Shared_ptr 定义
- 可以从一个裸指针、另一个 shared_ptr、一个 std::auto_ptr、或者一个 boost::weak_ptr 构
造。
- 还可以传递第二个参数给 shared_ptr 的构造函数，它被称为删除器(deleter)。删除器稍后会被调用，来处理
共享资源的释放。这对于管理那些不是用 new 分配也不是用 delete 释放的资源时非常有用
- shared_ptr 被创建后，它就可象普通指针一样使用了，除了一点，它不能被显式地删除。

<a id="markdown-shared_ptr-内部构造" name="shared_ptr-内部构造"></a>
### Shared_ptr 内部构造
>>> 定义
  ```
     namespace boost {
template<typename T> class shared_ptr {
public:
template <class Y> explicit shared_ptr(Y* p);
template <class Y,class D> shared_ptr(Y* p, D d);
shared_ptr(const shared_ptr & r);
template <class Y> explicit
shared_ptr(const weak_ptr<Y>& r);
template <class Y> explicit shared_ptr(std::auto_ptr<Y>& r);
shared_ptr& operator=(const shared_ptr& r);
void reset();
T& operator*() const;
T* operator->() const;
T* get() const;
bool unique() const;
long use_count() const;
operator unspecified_bool_type() const; //译注：原文是unspecified-bool-type()，有误
void swap(shared_ptr<T>& b);
};
template <class T,class U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& r);
}
```
#### 成员函数
- ` template <class Y> explicit shared_ptr(Y* p); `
  - 这个构造函数获得给定指针 p 的所有权。参数 p 必须是指向 Y 的有效指针。构造后引用计数设为1。唯一从这个构
造函数抛出的异常是 std::bad_alloc (仅在一种很罕见的情况下发生，即不能获得引用计数器所需的自由空间)。
- `template <class Y, class D> shared_ptr(Y* p, D d); `
  - 这个构造函数带有两个参数。第一个是 shared_ptr 将要获得所有权的那个资源，第二个是 shared_ptr 被销毁时
  负责释放资源的一个对象，被保存的资源将以 d(p) 的形式传给那个对象。因此 p 的值是否有效取决于 d。如果引
  用计数器不能分配成功， shared_ptr 抛出一个类型为 std::bad_alloc 的异常。

- `shared_ptr(const shared_ptr& r);`
  - r 中保存的资源被新构造的 shared_ptr 所共享，引用计数加一。这个构造函数不会抛出异常。

 - `template <class Y> explicit shared_ptr(const weak_ptr<Y>& r);`
   - 从一个 weak_ptr (本章稍后会介绍)构造 shared_ptr。这使得 weak_ptr 的使用具有线程安全性，因为指向
weak_ptr 参数的共享资源的引用计数将会自增(weak_ptr 不影响共享资源的引用计数)。如果 weak_ptr 为空 (r.
use_count()==0), shared_ptr 抛出一个类型为 bad_weak_ptr 的异常

- `template <typename Y> shared_ptr(std::auto_ptr<Y>& r);`
  - 这个构造函数从一个 auto_ptr 获取 r 中保存的指针的所有权，方法是保存指针的一份拷贝并对 auto_ptr 调用
release 。构造后的引用计数为1。而 r 当然就变为空的。如果引用计数器不能分配成功，则抛出 std::
bad_alloc 。

- `~shared_ptr();`
  -  shared_ptr 析构函数对引用计数减一。如果计数为零，则保存的指针被删除。删除指针的方法是调用 operator
delete 或者，如果给定了一个执行删除操作的客户化删除器对象，就把保存的指针作为唯一参数调用这个对象。析
构函数不会抛出异常。

- `shared_ptr& operator=(const shared_ptr& r);`
  - 赋值操作共享 r 中的资源，并停止对原有资源的共享。赋值操作不会抛出异常。

- `void reset();`
  - reset 函数用于停止对保存指针的所有权的共享。共享资源的引用计数减一。

- `T& operator*() const;`
  - 这个操作符返回对已存指针所指向的对象的一个引用。如果指针为空，调用 operator* 会导致未定义行为。这个操
作符不会抛出异常

- `T* operator->() const;`
  - 这个操作符返回保存的指针。这个操作符与 operator* 一起使得智能指针看起来象普通指针。这个操作符不会抛出
异常

- `T* get() const; `
  - get 函数是当保存的指针有可能为空时(这时 operator* 和 operator-> 都会导致未定义行为)获取它的最好办法。
  注意，你也可以使用隐式布尔类型转换来测试 shared_ptr 是否包含有效指针。这个函数不会抛出异常。

- `bool unique() const;`
  - 这个函数在 shared_ptr 是它所保存指针的唯一拥有者时返回 true；否则返回 false。 unique 不会抛出异常。

- `long use_count() const;`
   -  use_count 函数返回指针的引用计数。它在调试的时候特别有用，因为它可以在程序执行的关键点获得引用计数的
快照。小心地使用它，因为在某些可能的 shared_ptr 实现中，计算引用计数可能是昂贵的，甚至是不行的。这个
函数不会抛出异常。

- `operator unspecified_bool_type() const;`
  - 这是个到 unspecified_bool_type 类型的隐式转换函数，它可以在Boolean上下文中测试一个智能指针。如果
shared_ptr 保存着一个有效的指针，返回值为 True；否则为 false。

- `void swap(shared_ptr<T>& b);`
  - 这可以很方便地交换两个 shared_ptr。 swap 函数交换保存的指针(以及它们的引用计数)。这个函数不会抛出异
常

### 普通函数
- `template <typename T,typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& r);`
  - 要对保存在 shared_ptr 里的指针执行 static_cast，我们可以取出指针然后强制转换它，但我们不能把它存到另
一个 shared_ptr 里；新的 shared_ptr 会认为它是第一个管理这些资源的。解决的方法是用
static_pointer_cast. 使用这个函数可以确保被指物的引用计数保持正确。 static_pointer_cast 不会抛出异
常。


### 使用方法
-  详见最后的代码展示：

### shared_ptr 与其它资源
- 有时你会发现你要把 shared_ptr 用于某个特别的类型，它需要其它清除操作而不是简单的 delete.
shared_ptr 可以通过客户化删除器来支持这种需要。那些处理象 FILE* 这样的操作系统句柄的资源通常要使用
象 fclose 这样的操作来释放。要在 shared_ptr 里使用 FILE* ，我们要定义一个类来负责释放相应的资源。

- 注意
  - 在访问资源时，我们需要对 shared_ptr 使用 &* 用法, get, 或 get_pointer 。 (请注意最好使用 &*. 另两
个选择不太清晰) 

### 从this创建shared_ptr
- 有时候，需要从 this 获得 shared_ptr ，即是说，你希望你的类被 shared_ptr 所管理，你需要把“自身”转换
为 shared_ptr 的方法。看起来不可能？好的，解决方案来自于我们即将讨论的另一个智能指针 boost::
weak_ptr. weak_ptr 是 shared_ptr 的一个观察者；它只是安静地坐着并看着它们，但不会影响引用计数。通过存
储一个指向 this 的 weak_ptr 作为类的成员，就可以在需要的时候获得一个指向 this 的 shared_ptr 。为了你
可以不必编写代码来保存一个指向 this 的 weak_ptr ，接着又从 weak_ptr 获 shared_ptr 得， Boost.
Smart_ptr 为这个任务提供了一个助手类，称为 enable_shared_from_this. 只要简单地让你的类公有地派生自
enable_shared_from_this ，然后在需要访问管理 this 的 shared_ptr 时，使用函数 shared_from_this 就
行了。

### 总结
- 引用计数智能指针是非常重要的工具。 Boost 的 shared_ptr 提供了坚固而灵活的解决方案，它已被广泛用于多种
环境下。需要在使用者之间共享对象是常见的，而且通常没有办法通知使用者何时删除对象是安全的。
shared_ptr 让使用者无需知道也在使用共享对象的其它对象，并让它们 无需担心在没有对象引用时的资源释放。
这对于Boost的智能指针类而言是最重要的。你会看到 Boost.Smart_ptr 中还有其它的智能指针，但这 一个肯定
是你最想要的。通过使用定制删除器，几乎所有资源类型都可以存入 shared_ptr 。这使得 shared_ptr 成为处理
资源管理的通用类，而不仅仅是处理动态分配对象。与裸指针相比， shared_ptr 会有一点点额外的空间代价。我
还没有发现由于这些代价太大而需要另外寻找一个解决方案的情形。不要去创建你自己的引用计数智能指针类。没有
比使用 shared_ptr 智能指针更好的了。

### 使用shared_ptr 的时机
- 当有多个使用者使用同一个对象，而没有一个明显的拥有者时
- 当要把指针存入标准库容器时
- 当要传送对象到库或从库获取对象，而没有明确的所有权时
- 当管理一些需要特殊清除方式的资源时
  -  通过定制删除器的帮助。


## shared_array
- 头文件: "boost/shared_array.hpp"
- >> ared_array 用于共享数组所有权的智能指针。它与 shared_ptr 的关系就如 scoped_array 与
scoped_ptr 的关系。 shared_array 与 shared_ptr 的不同之处主要在于它是用于数组的而不是用于单个对象
的。在我们讨论 scoped_array时，我提到过通常 std::vector 是一个更好的选择。但 shared_array 比
vector 更有价值，因为它提供了对数组所有权的共享。 shared_array 的接口与 shared_ptr 非常相似，差别
仅在于增加了一个下标操作符，以及不支持定制删除器。

## instrusive_ptr
-   头文件: "boost/intrusive_ptr.hpp"
>> - intrusive_ptr 是 shared_ptr 的插入式版本。有时我们必须使用插入式的引用计数智能指针。典型的情况是对
于那些已经写好了内部引用计数器的代码，而我们又没有时间去重写它(或者已经不能获得那些代码了)。另一种情
况是要求智能指针的大小必须与裸指针大小严格相等，或者 shared_ptr 的引用计数器分配严重影响了程序的性
能(我可以肯定这是非常罕见的情况！ )。从功能的观点来看，唯一需要插入式智能指针的情况是，被指类的某个成
员函数需要返回 this ，以便它可以用于另一个智能指针(事实上，也有办法使用非插入式智能指针来解决这个问
题，正如我们在本章前面看到的)。 intrusive_ptr 不同于其它智能指针，因为它要求你来提供它所要的引用计
数器。
>> 当 intrusive_ptr 递增或递减一个非空指针上的引用计数时，它是通过分别调用函数 intrusive_ptr_add_ref
和 intrusive_ptr_release 来完成的。这两个函数负责确保引用计数的正确性，并且负责在引用计数降为零时
删除指针。因此，你必须为你的类重载这两个函数，正如我们后面将看到的。

- 部分代码
 ``` namespace boost {
template<class T> class intrusive_ptr {
public:
intrusive_ptr(T* p,bool add_ref=true);
intrusive_ptr(const intrusive_ptr& r);
~intrusive_ptr();
T& operator*() const;
T* operator->() const;
T* get() const;
operator unspecified-bool-type() const;
};
template <class T> T* get_pointer(const intrusive_ptr<T>& p);
template <class T,class U> intrusive_ptr<T>
static_pointer_cast(const intrusive_ptr<U>& r);
}
```

<a id="markdown-代码示例" name="代码示例"></a>
## 代码示例
```
////#include "bst.h"
#include <iostream>
#include "boost/scoped_ptr.hpp"
#include <string>
#include "boost/algorithm/string.hpp" //String_algo 算法
#include "boost/shared_ptr.hpp"
//#include "boost/container/vector.hpp"
#include <vector>
#include <fstream>

#define  SCOPED_PTR 0
#define SHARED_SIMPLE 0
#define SHARED_FILE 1

using namespace boost;
using std::cin;
using std::cout;
using std::endl;


class filecloser
{
public:
	filecloser();
	~filecloser();

	void operator()(std::fstream *fs)
	{
		cout << "Now starting to close the file resourse" << endl;
		if (fs)
		{
			fs->close();
			cout << "File Closed" << endl;
		}
		
	}

private:

};

filecloser::filecloser()
{
}

filecloser::~filecloser()
{
}

//#define  shared_ptr boost::shared_ptr;

class A {

public:
	virtual void sing() = 0;
protected:

	virtual ~A()
	{

	}	   
};


class B : public A
{
public:
	void sing()
	{
		cout << "A B C D E \n\n" << endl;
	};

	


};


static boost::shared_ptr<A>  createA()
{
	boost::shared_ptr<B> p(new B());

	return p;

}

typedef std::vector<boost::shared_ptr<A>> sv;
typedef boost::shared_ptr<B> SB;
typedef sv::iterator sbi;


//using namespace std;
using namespace boost;

using namespace std;

int main(int argc, char ** argv)
{

#if SCOPED_PTR


	scoped_ptr<string> st(new string("Scoped ptr  Inner Text"));

	//错误的做法，scoped_ptr 不能复制
	//st = new scoped_ptr<string>; 


	cout << *st <<endl<<"Is "<<st->size()<<" length"<<endl;

	*st = "文本已经改变！";	//但是scoped指针指向的内容是可以改变的，scoped_ptr 使用与普通指针没有区别！
	
	cout << endl << *st;

#endif // SCOPED_PTR



#if SHARED_SIMPLE

	sv shared_v;

	for (int i = 0; i < 100; i++)
	{

		shared_v.push_back(createA());
	}

	cout << "下面取出并打印:\n";							

	for (auto a: shared_v)
	{

		a->sing();
	}

#endif


#if SHARED_FILE

	fstream fs("1.txt",ios::out|ios::out);
	if (!fs.bad())
	{
		boost::shared_ptr<std::fstream> file(&fs,filecloser());
		file->write("文件内读写！\n",60);	  
	}
	

	

#endif


	cin.get();

	return 0;
}```