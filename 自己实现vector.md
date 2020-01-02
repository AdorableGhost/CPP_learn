### 一个自己实现的Vector(只能处理基本类型数据)

- string 类型不行
- bool char* int double float long long  等基本类型可用
- 使用模板类实现。底层为数组实现。


- dvector.h
```
#ifndef DVECTOR_H
#define DVECTOR_H
#pragma once
#include <iostream>
template <class T>
class dvector
{
public:
    dvector();
    ~dvector();
    bool push_back(T);
    void show();

public:
    T* p;
    int len;
    int real_len;

};

#endif // DVECTOR_H
```
- dvector.cpp
```
#include "dvector.h"

template <class T>
dvector<T>::dvector()
{
    len=real_len =0;
    p=nullptr;
}


template<class T>
dvector<T>::~dvector()
{
    if(p!=nullptr)
    {
        delete []p;
        p=nullptr;
    }
}

template <class T>
void dvector<T>::show()
{
    if(p!=nullptr)
    {
        for(int i=0;i<real_len;i++){
            std::cout<<i<<"\t"<<*(p+i)<<std::endl;
        }

        std::cout<<"length="<<real_len<<std::endl;
    }else {

        std::cout<<"NNNNNNNNNNNNNNNNNNNNNNNNNNo thing"<<std::endl;
}
}


template<class T>
bool dvector<T>::push_back(T t){

    if(p==nullptr)
    {
        //第一个为空说明只有一个元素
        p=new T;
        *p=t;
        real_len=len=1;
    }else {

        //第一个不为空说明有多个元素，这时候链表就必须重新分配内存
        //分配为数组形式
        T *ptemp = new T[real_len+1];
        for(int i=0;i<real_len;i++)
        {
            *(ptemp+i)=*(p+i);

        }
        *(ptemp+real_len)=t;
        delete []p;
        p=ptemp;
        real_len+=1;
        len+=1;
    }

    return  true;

}


int main()
{
    //测试基本类型
    //string 会出错，因为string 不是基本类型，是一种类似 vector 的类模板，其内部的内存操作与基本类型不一样。
    //1. int
    dvector<int>* dv1=new dvector<int>;
    dv1->push_back(12);
    dv1->push_back(15);
    dv1->push_back(1995);
    dv1->push_back(200);
    dv1->push_back(2);
    dv1->push_back(1);

    dv1->show();

    //2. double
    dvector<double>* dv2=new dvector<double>;
    dv2->push_back(12.2);
    dv2->push_back(15.3);
    dv2->push_back(1995.0220);
    dv2->push_back(200.1);
    dv2->push_back(2.3);
    dv2->push_back(1.9);

    dv2->show();

    //3. char*
    dvector<char*>* dv3=new dvector<char*>;
    dv3->push_back("nimei");
    dv3->push_back("de");
    dv3->push_back("垃圾");
    dv3->push_back("95");
    dv3->push_back("lalala");
    dv3->push_back("45");

dv3->show();
    return 0;
}

```