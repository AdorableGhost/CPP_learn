# Boost 学习笔记
> 书籍：Beyond the C++ Standard Library : An Introduction to Boost 
    > > 注记（笔记）

<!-- TOC -->

- [Boost 学习笔记](#boost-%e5%ad%a6%e4%b9%a0%e7%ac%94%e8%ae%b0)
  - [有用的](#%e6%9c%89%e7%94%a8%e7%9a%84)
    - [boost string_algo库](#boost-stringalgo%e5%ba%93)
  - [Smart Pointer](#smart-pointer)
    - [智能指针 ：shared_ptr weak_ptr scoped_ptr  scoped_array  intrusive_ptr,](#%e6%99%ba%e8%83%bd%e6%8c%87%e9%92%88-sharedptr-weakptr-scopedptr-scopedarray-intrusiveptr)
      - [Smart_ptr 库如何改进你的程序？](#smartptr-%e5%ba%93%e5%a6%82%e4%bd%95%e6%94%b9%e8%bf%9b%e4%bd%a0%e7%9a%84%e7%a8%8b%e5%ba%8f)
      - [有三种典型的情况适合使用智能指针：](#%e6%9c%89%e4%b8%89%e7%a7%8d%e5%85%b8%e5%9e%8b%e7%9a%84%e6%83%85%e5%86%b5%e9%80%82%e5%90%88%e4%bd%bf%e7%94%a8%e6%99%ba%e8%83%bd%e6%8c%87%e9%92%88)
      - [boost智能指针的优势](#boost%e6%99%ba%e8%83%bd%e6%8c%87%e9%92%88%e7%9a%84%e4%bc%98%e5%8a%bf)
    - [scoped_ptr](#scopedptr)
      - [scoped_ptr 的用法](#scopedptr-%e7%9a%84%e7%94%a8%e6%b3%95)
      - [scoped_ptr 和 Pimpl 用法](#scopedptr-%e5%92%8c-pimpl-%e7%94%a8%e6%b3%95)
      - [scoped_ptr 与 const auto_ptr 的区别](#scopedptr-%e4%b8%8e-const-autoptr-%e7%9a%84%e5%8c%ba%e5%88%ab)
      - [总结](#%e6%80%bb%e7%bb%93)
    - [scoped_array](#scopedarray)
    - [shared_ptr](#sharedptr)

<!-- /TOC -->

## 有用的
  ###  boost string_algo库 
- 头文件 boost/algorithm/string.hpp
- 这是一组与字符串相关的算法。包括很多有用的算法，用于大小写转换，空格清除，字符串分割，查找及替换，等
等。这组算法是目前C++标准库里已有功能的扩展。

## Smart Pointer


###  智能指针 ：shared_ptr weak_ptr scoped_ptr  scoped_array  intrusive_ptr,
#### Smart_ptr 库如何改进你的程序？
  - 使用 shared_ptr 进行对象的生存期自动管理，使得分享资源所有权变得有效且安全。
  - 使用 weak_ptr 可以安全地观测共享资源，避免了悬挂的指针。
  -  使用 scoped_ptr 和 scoped_array 限制资源的使用范围，使得代码更易于编写和维护，并有助于写出异常安全的代码。

#### 有三种典型的情况适合使用智能指针：
- 资源所有权的共享
-  要写异常安全的代码时
- 避免常见的错误，如资源泄漏

#### boost智能指针的优势
虽然 C++ 标准库中提供了 std::auto_ptr, 但是它不能
完全满足我们对智能指针的需求。例如，auto_ptr 不能用作 STL 容器的元素。Boost 的智能指针类填充了标准所留下来的缺口。

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

#### scoped_ptr 和 Pimpl 用法
- Tips:
  - 如果 pimpl 实例可以安全地被多个封装类(在这里是 pimpl_sample)的实例所共享，那
么用 boost::shared_ptr 来管理 pimpl 的生存期才是正确的选择。用 shared_ptr 比用 scoped_ptr 的优势
Beyond the C++ Standard Library : An Introduction to Boost
40
在于，不需要手工去定义复制构造函数和赋值操作符，而且可以定义空的析构函数，shared_ptr 被设计为可以正
确地用于未完成的类

#### scoped_ptr 与 const auto_ptr 的区别
-     scoped_ptr 可以被 reset, 在需要时可以删除并替换被指物。
-     而对于 const auto_ptr 这是不可能的


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


### scoped_array
- 头文件: "boost/scoped_array.hpp"
-作用：
  - 防止错误调用 delete 操作符而不是 delete[] 操作符。
  - scoped_array 为数组做了 scoped_ptr 为单个对象的指针所做的事情：它负责释放内存。区
别只在于 scoped_array 是用 delete[] 操作符来做这件事的。

### shared_ptr
- 头文件: "boost/shared_ptr.hpp"
- 