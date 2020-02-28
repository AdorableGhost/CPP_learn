
<!-- TOC -->

- [一个自己实现的Vector(只能处理基本类型数据)](#%e4%b8%80%e4%b8%aa%e8%87%aa%e5%b7%b1%e5%ae%9e%e7%8e%b0%e7%9a%84vector%e5%8f%aa%e8%83%bd%e5%a4%84%e7%90%86%e5%9f%ba%e6%9c%ac%e7%b1%bb%e5%9e%8b%e6%95%b0%e6%8d%ae)
- [晚上完善 增加了 删 改 查](#%e6%99%9a%e4%b8%8a%e5%ae%8c%e5%96%84-%e5%a2%9e%e5%8a%a0%e4%ba%86-%e5%88%a0-%e6%94%b9-%e6%9f%a5)

<!-- /TOC -->
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

### 晚上完善 增加了 删 改 查
    - 和尹成老师视频里面写的不一样。。自己写的。反正就是不规范就是了
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
	bool del(T);
	bool modify(T, T);
	int  search(T t);
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

using namespace std;

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

//遍历输出
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

//增
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

//查	  返回查找到的序号
template <class T>
int dvector<T>::search(T t)
{
	if (p ==nullptr)
	{
		std::cout << "The dvector is empty ,abort!" << std::endl;
		return false;
	}
	else
	{
		for (size_t i = 0; i < real_len; i++)
		{
			if (*(p+i) == t)
			{
				cout << "FIND	" << t << "at the position of  " << i<<"  " << endl;
				return i;
			   
			}
		}

		cout << "no such a thing" << endl; 
		return -1;

	}


	return -1;


}

//删
 template <class T>
 bool dvector<T>::del(T t)
 {

	 if (p == nullptr)
	 {
		 std::cout << "The dvector is alreafy empty ,abort!" << std::endl;
		 return false;
	 }
	 else
	 {
		 for (size_t i = 0; i < real_len; i++)
		 {
			 if (*(p + i) == t)
			 {
				 cout << "Deleting" << endl;
				 cout << "FIND	" << t << "at the position of  " << i << "  " << endl;
				 
				 //如果是在第一个的情况
				 if (i == 0)
				 {
					 for (size_t i = 0; i < real_len; i++)
					 {
						 if (real_len == 1)		 //如果是只剩一个而且刚好第一个是要删除的
						 { 
							 delete p;
							 p == nullptr;
							 real_len -= 1;
							 return true;
							
						 }
						 else
						 {			//还有多个且第一个是要删除的
							 T* tmp = new T[real_len - 1];
							 for (size_t k = 0; k < real_len-1; k++)
							 {
								 *(tmp + k) = *(p + k + 1);
							 }

							
							 delete[]p;
							 p = tmp;
							 real_len -= 1;
							 return true;
						 }
						 
					 }

				 }
				 else if (i== real_len-1)			   //最后一个匹配要删除的时候
				 {
					 p + i == nullptr;
					 real_len -= 1;
				 }
				 else		  //在中间的情况
				 {

					 T* tmp = new T[real_len - 1];
					 for (size_t k = 0; k < i ; k++)
					 {
						 *(tmp + k) = *(p + k);
					 }
					 // 利用两个循环刚好跳过下标为i 的值 k 为原来的p 中的值，tmp+k-i 为新数组中的下标
					 for (size_t k = i+1; k < real_len; k++)
					 {
						 *(tmp + k - 1) = *(p + k);

					 }

					
					 delete[]p;
					 p = tmp;
					 real_len -= 1;
					 return true;

				 }


			 }
		 }

		 cout << "no such a thing,Delete failed!" << endl;
		 return false;

	 }	   	

 }

 //改
 template <class T>
 bool dvector<T>::modify(T origin, T mo)
 {

	 if (p == nullptr)
	 {
		 std::cout << "The dvector is empty ,abort!" << std::endl;
		 return false;
	 }
	 else
	 {
		 for (size_t i = 0; i < real_len; i++)
		 {
			 if (*(p + i) == origin)
			 {
				 cout << "Modifying" << endl;
				 cout << "FIND	" << origin << "at the position of  " << i << "  " << endl;
				 
				 *(p + i) = mo;

			 }
		 }

		 cout << "no such a thing ,Modify failed!" << endl;
		 return false;

	 }


	 return -1;

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

	//dv1->search(200);
	//dv1->search(1000);
	dv1->del(12);
	dv1->show();
	dv1->del(1995);
	dv1->show();
	dv1->del(1);
	dv1->show();

	dv1->modify(15, 33);
	dv1->modify(200, 1);
	dv1->modify(100, 1);
	dv1->show();

//	cout<<"next............"<<endl<<endl;
//    //2. double
//    dvector<double>* dv2=new dvector<double>;
//    dv2->push_back(12.2);
//    dv2->push_back(15.3);
//    dv2->push_back(1995.0220);
//    dv2->push_back(200.1);
//    dv2->push_back(2.3);
//    dv2->push_back(1.9);
//
//    dv2->show();
//
//	dv2->search(1.9);
//
//	cout << "next............" << endl << endl;
//
//    //3. char*
//    dvector<const char*>* dv3=new dvector<const char*>;
//    dv3->push_back("nimei");
//    dv3->push_back("de");
//    dv3->push_back("垃圾");
//    dv3->push_back("95");
//    dv3->push_back("lalala");
//    dv3->push_back("45");
//
//dv3->show();
//dv3->search("nimei");
//cout << "next............" << endl << endl;

std::cin.get();
    return 0;
}
```