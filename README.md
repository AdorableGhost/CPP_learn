# CPP 学习笔记
### 文件操作已经学完，今天看下多线程  2019.11.11 15:06
#### 知识点１
<li> Linux 下编译 带&ltthread&gt 的CPP需要加上 -pthread 编译选项。例如：
```
g++ -std=c++11 -pthread a.cpp

```
<li>QT Creator 编译带&ltthread&gt的CPP有ＢＵＧ，暂时不知道怎么去除！

#### 代码1

```#include <iostream>
#include <stdlib.h>v
#include <thread>

using namespace std;
void run(char* p)
{
    int i=0;
    i=system(p);
}

int main()
{
    char p[5][20]={
        "ls",
        "echo nihao",
        "gnome-terminal",
        "terminator",
        "ps -aux"

    };

    while("nimei")
    {
       static  int i(0);
        if(i<5){
            thread  *pt=new  thread(run,p[i]);
            i+=1;
            cout<<"I now is :\t"<<i<<endl;
        }
        else{
            break;
        }

        cout<<"Breaking...."<<endl;
    }




    cin.get();
    return 0;
}
```
#### 知识点２

<li> 关于thread类的内部成

| 关键字                       | 详细解释                                             |
| ---------------------------- | ---------------------------------------------------- |
| id                           | Thread的iｄ                                          |
| native_handle_type           | native_handle_type                                   |
| operator=                    | Move massive Thread                                  |
| get_id                       | get Thread ID                                        |
| joinable                     | get if joinable                                      |
| join                         | join thread                                          |
| detach                       | detach thread                                        |
| swap                         | swap thread                                          |
| native_handle                | get native handle                                    |
| hardware_concurrency[static] | Detect hardware concurrency (public static function) |

![](1.jpg)

<li> 线程 detach 脱离主线程的绑定，主线程挂了，子线程不报错，子线程执行完自动退出。

<li> 线程 detach以后，子线程会成为孤儿线程，线程之间将无法通信。

### 知识点３

<li>线程中变量的竞争控制是通过 mutex automic 来实现的

<li>mutex : 互斥量。需要包含头文件　&ltmutex> 来使用　-->速度慢

<li>atomic 原子变量。需要包含头文件&ltatomic>来实现　-->速度快，线程安全。

#### 代码３

```
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <atomic>

using namespace std;
int count(0);

void run()
{
    for(int i(0);i<1000000;i++)
    {
        count++;
        cout<<"\t"<<i<<"\t"<<count<<"\t";
    }
}

int main()
{
    auto n=thread::hardware_concurrency();

    thread* pt[n];
    for(int z=0;z<n;z++)
    {
        pt[z]=new thread(run);
        pt[z]->detach();

    }

    cout<<"Finally count is \t"<<count<<endl;
    cout<<"Used "<<n <<"threads"<<endl;




    cin.get();
    return 0;
}
```

<em>运行结果不是1000000×２．

```#include <iostream>
#include <stdlib.h>
#include <thread>
#include <atomic>

using namespace std;
int count(0);

void run()
{
    for(int i(0);i<1000000;i++)
    {
        count++;
        cout<<"\t"<<i<<"\t"<<count<<"\t";
    }
}

int main()
{
    auto n=thread::hardware_concurrency();

    thread* pt[n];
    for(int z=0;z<n;z++)
    {
        pt[z]=new thread(run);
        pt[z]->detach();

    }

    cout<<"Finally count is \t"<<count<<endl;
    cout<<"Used "<<n <<"threads"<<endl;




    cin.get();
    return 0;
}
```
<em>运行结果是1000000×２．正确

<li><em>atomic 声明方式为　atomic&ltint> a(100); 等号初始化会报错

<li><em>vim 按ＣＴＲＬ+S 后假死按　ＣＴＲＬ＋q 退出


### STL 学习，没有带笔记本回来。。。我日 2019.11.11 23:21

#### STL的概念

<li> Iterator  (迭代器)
<li> Container (容器) array
<li> Alogrithm (算法)
<li> Adapters (配接器) 用来实现容器之间的转接<br>
 面向过程--》面向对象-》基于对象-》泛型

#### 代码

```
#include <iostream>
#include <vector> //容器
#include <algorithm> //算法

using namespace std;

//专么实现一个类模板，实现打印
//类模板实现了方法
template <class T>
class vector_s {
public:
void operator()(const T &t1) //重载了小括号 实现访问小括号就直接打印
	{
		cout << t1 << endl;
	}
};

int main(void)
{
	vector<int> myv;
	myv.push_back(13);
	myv.push_back(23);
	myv.push_back(33);
	myv.push_back(113);
	myv.push_back(1995);
	myv.push_back(1996);

	vector_s<int> print; // 对打印实现实例化

    //myv.begin(), myv.end() 是迭代器 本质是指针
    // for_each 本质是一个算法
	for_each(myv.begin(), myv.end(), print);

	cin.get();



	return 0;
}
```

<br>
<li>注意：算法需要包含头文件 &ltalgorithm&gt <br>
<li>这个遍历的函数为 for_each 不是foreach<br>
<li>算法可以适用于任何容器<br>

#### STL抽象的是什么

-有些算法并不依赖于数据结构的特定实现，而只依赖于该结构的几个基本语义属性

-STL 抽象出的这些基本属性（concept）成功的将算法和数据结构相分离，在没有效率损失的前提下，获得了极大的弹性！

### 六大组件
-容器 （container)

-算法Algorithm

-迭代器 （iterator）

-仿函数 （Function Object)

-适配器 （Adaptor）

-空间制配器 （allocator)


获取远程代码修改后,想要push到远端与原来不同的新分支，可以使用下面的命令实现：
git push origin 本地分支:远端希望创建的分支


例如git下来的分支为master

git branch master
git push origin master:my_remote_new_branch
#远端即可创建新的分支my_remote_new_branch,提交本地修改

### 2019.11.13 9:32

``` std::for_each(arr.begin(), arr.end(), func);```

 比较有用的for_each 用法

 ```for (auto n:Original)```

 C++ 11 新的for

 ## Missing lastnight

#### array
``` array <int ,5>={1,2,3,4,5};```
-静态数组，栈上
#### vector 动态数组 堆上
  ```vector <int> mv;
   mv.push_back()
   ```
   -不需要变长，容量较小，array 需要变长，容量较大，用vector

#### tuple 可以存储不同的数据类型

#### list 适合经常插入，经常删除的情况
- 35.20

#### list 容器

-list容器是无序容器

-list 容器只能通过迭代器访问。通过++ -- 遍历

-list容器可以使用remove（）方法删除元素，

-可以同时正向和反向查找

-可以使用sort()函数排序

-可以使用merge 合并，但是合并之前必须排序

-可以使用unique()函数删除重复项，删除前必须排序。

--merge (使)合并，结合，并入;相融;融入;渐渐消失在某物中

#### set 容器 （红黑树容器）

-set容器不能有重复项，重复的会被舍弃
-set容器会自动排序
-set 用insert插入元素
-set可以用find（）函数查找位置

循环加栈


### algorithm 算法

find（）函数可以查找数组、容器中的元素。

for_each(); 遍历每一个元素。

multiset和set差不多，但是允许重复元素。

迭代器本质是智能指针。

### Iterator
![](iterator.jpg)
#### 仿函数

```auto ifind=find_if(mylist.bengin(),mylisy.end(),bindlst(greater<int>(),3));```

bindlst 需要头文件 funtional   ```#include <functional>```

```bindlst(greater<int>(),3);```  绑定一个函数。 ```greater<int>() ```  是一个仿函数（functional)  是一个重载了（）的类/结构 体 ，可以用来实现一定的算法策略。

仿函数例子：
``` #include <iostream>
#include <list>
#include <functional>
#include <array>
#include <algorithm>

using namespace std;


class shuchu {
  public:

  void operator()(int x)
  {
    std::cout<<x<<endl;
  }
};



 int main(int argc, char const *argv[]) {
  /* code */

  // array<int,5>array1({1,2,3,4,5});
  list <int>ls1;
  ls1.push_back(1);
   ls1.push_back(3);
    ls1.push_back(5);
     ls1.push_back(7);
      ls1.push_back(9);
  auto ib=ls1.begin();
  auto ie=ls1.end();
  for_each(ib,ie,shuchu());
  cin.get();
  return 0;
}

```

### 2019.11.15  6.wmv STL Bug 迭代器

-智能指针有一个_Ptr属性，可以打印里面的指针。

-STL 有bug 先访问迭代器的_Ptr属性，再访问迭代器指针正常，但是反过来会出错。

-分行打印就没有问题。


### 2019.11.15  7.wmv 栈队列双端队列优先队列

#### stack 关键字可以构建栈
-用法

```stack <mystack>;  //声明一个栈```
```mystack.push(num); //压栈```
```mystack.pop(); //出栈```
```mystack.top(); //获取第一个元素```

#### queue  队列

-queue 英 [kjuː]   美 [kjuː]  

n.(人、汽车等的)队，行列;(储存的数据)队列
v.(人、车等)排队等候;(使)排队;列队等待