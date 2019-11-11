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

