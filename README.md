# CPP 学习笔记
### 文件操作已经学完，今天看下多线程  2019.11.11 15:06
#### 知识点１
<li> Linux 下编译 带&ltthread&gt 的CPP需要加上 -pthread 编译选项。例如：
```
g++ -std=c++11 -pthread a.cpp

```
<li>QT Creator 编译带&ltthread&gt的CPP有ＢＵＧ，暂时不知道怎么去除！
#### 代码1

```
#include <iostream>
#include <stdlib.h>
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
<li> 关于thread类的内部成员

|关键字|详细解释|
|--|--|
|id|Thread的iｄ|  
|native_handle_type | native_handle_type|
|operator=|Move massive Thread|
|get_id|get Thread ID|
|joinable|get if joinable|
|join|join thread|
|detach|detach thread|
|swap |swap thread|
|native_handle|get native handle|
|hardware_concurrency[static]|Detect hardware concurrency (public static function)

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
