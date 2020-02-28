# CPP 小知识
<!-- TOC -->

- [CPP 小知识](#cpp-%e5%b0%8f%e7%9f%a5%e8%af%86)
  - [Hacktosh](#hacktosh)
  - [define](#define)
  - [VS 格式化代码](#vs-%e6%a0%bc%e5%bc%8f%e5%8c%96%e4%bb%a3%e7%a0%81)
  - [constexpr](#constexpr)
  - [const_cast来去除const限定](#constcast%e6%9d%a5%e5%8e%bb%e9%99%a4const%e9%99%90%e5%ae%9a)
  - [explicit 关键字](#explicit-%e5%85%b3%e9%94%ae%e5%ad%97)
  - [快速编译Qt程序](#%e5%bf%ab%e9%80%9f%e7%bc%96%e8%af%91qt%e7%a8%8b%e5%ba%8f)

<!-- /TOC -->


## Hacktosh
https://mirrors.dtops.cc/iso/MacOS/daliansky_macos/macOS%20Catalina%2010.15.3%2819D76%29%20Installer%20for%20Clover%205103%20and%20WEPE.dmg
迅雷下载

## define
- 作用
  - 预处理命令，定义常量、简单表达式，防止头文件重复包含
- # define 和 #ifndef
  - 一般用作防止头文件重复包含，配合使用
    - 在理论上来说可以是自由命名的，但每个头文件的这个“标识”都应该是唯一的。标识的命名规则一般是头文件名全大写，前后加下划线，并把文件名中的“.”也变成下划线，如：stdio.h   
    #ifndef   _STDIO_H_   
    #define   _STDIO_H_   
    ......   
    #endif  


## VS 格式化代码
- c-k c-d

## constexpr

- constexpr是C++11中新增的关键字，其语义是“常量表达式”，也就是在编译期可求值的表达式。最基础的常量表达式就是字面值或全局变量/函数的地址或sizeof等关键字返回的结果，而其它常量表达式都是由基础表达式通过各种确定的运算得到的。constexpr值可用于enum、switch、数组长度等场合。

constexpr所修饰的变量一定是编译期可求值的，所修饰的函数在其所有参数都是constexpr时，一定会返回constexpr。

```
constexpr int Inc(int i) {
    return i + 1;
}
 
constexpr int a = Inc(1); // ok
constexpr int b = Inc(cin.get()); // !error
constexpr int c = a * 2 + 1; // ok
```
constexpr还能用于修饰类的构造函数，即保证如果提供给该构造函数的参数都是constexpr，那么产生的对象中的所有成员都会是constexpr，该对象也就是constexpr对象了，可用于各种只能使用constexpr的场合。注意，constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中。

``` 
struct A {
    constexpr A(int xx, int yy): x(xx), y(yy) {}
    int x, y;
};
 
constexpr A a(1, 2);
enum {SIZE_X = a.x, SIZE_Y = a.y};

```
constexpr的好处：

是一种很强的约束，更好地保证程序的正确语义不被破坏。
编译器可以在编译期对constexpr的代码进行非常大的优化，比如将用到的constexpr表达式都直接替换成最终结果等。
相比宏来说，没有额外的开销，但更安全可靠。


## const_cast来去除const限定
对于const变量，我们不能修改它的值，这是这个限定符最直接的表现。但是我们就是想违背它的限定希望修改其内容怎么办呢？

下边的代码显然是达不到目的的： const int constant = 10;
int modifier = constant;

因为对modifier的修改并不会影响到constant，这暗示了一点:const_cast转换符也不该用在对象数据上，因为这样的转换得到的两个变量/对象并没有相关性。

只有用指针或者引用，让变量指向同一个地址才是解决方案，可惜下边的代码在C++中也是编译不过的： const int constant = 21;
int* modifier = &constant 
// Error: invalid conversion from 'const int*' to 'int*'

（上边的代码在C中是可以编译的，最多会得到一个warning，所在在C中上一步就可以开始对constant里面的数据胡作非为了）

把constant交给非const的引用也是不行的。 const int constant = 21;
int& modifier = constant;
// Error: invalid initialization of reference of type 'int&' from expression of type 'const int'

于是const_cast就出来消灭const，以求引起程序世界的混乱。

下边的代码就顺利编译功过了： const int constant = 21;
const int* const_p = &constant;
int* modifier = const_cast<int*>(const_p);
*modifier = 7;

## explicit 关键字
- 定义：
  -  C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).
  -  explicit关键字的作用就是防止类构造函数的隐式自动转换.
  -   explicit关键字只对有一个参数的类构造函数有效, 如果类构造函数参数大于或等于两个时, 是不会产生隐式转换的, 所以explicit关键字也就无效了. 例如: 
  -    explicit关键字只对有一个参数的类构造函数有效, 如果类构造函数参数大于或等于两个时, 是不会产生隐式转换的, 所以explicit关键字也就无效了. 例如: 

- 总结
   - explicit关键字只需用于类内的单参数构造函数前面。由于无参数的构造函数和多参数的构造函数总是显示调用，这种情况在构造函数前加explicit无意义。
   - google的c++规范中提到explicit的优点是可以避免不合时宜的类型变换，缺点无。所以google约定所有单参数的构造函数都必须是显示的，只有极少数情况下拷贝构造函数可以不声明称explicit。例如作为其他类的透明包装器的类。
   - effective c++中说：被声明为explicit的构造函数通常比其non-explicit兄弟更受欢迎。因为它们禁止编译器执行非预期（往往也不被期望）的类型转换。除非我有一个好理由允许构造函数被用于隐式类型转换，否则我会把它声明为explicit，鼓励大家遵循相同的政策。

- 出处：https://www.cnblogs.com/rednodel/p/9299251.html
- 原文 [原文](https://www.cnblogs.com/rednodel/p/9299251.html)


## 快速编译Qt程序
- 解决Qt Creator在编译应用程序时耗时较长的优化方法：

    - 首先，Qt creator只是一个IDE，不是编译器，编译快慢与Qt Creator无关，要看具体使用的是什么编译器。一般来说Windows下就是MinGW的gcc和Visual Studio的nmake，在Windows下推荐使用VS编译器，能够加快编译速度。



  - 其次，可以配置PRECOMPILED_HEADER，添加预编译头文件(PCH,PreCompiled Headers)支持：

    CONFIG+=precompile_header  
    PRECOMPILED_HEADER=stable.h  
   -    最后，可以采用并行编译方式，在.pro里加入下面一行：<br>
    QMAKE_CXXFLAGS += /MP<br>
    同时起多个编译进程并行编译不同的cpp。


    ## 编译QT 的Mysql 驱动
-   1.下载MySQL Connector C 6.1并安装
-   2.打开 VS 2017的开发人员命令提示符 
-   3.进入  C:\Qt\Qt5.14.1\5.14.1\Src\qtbase\src\plugins\sqldrivers\mysql\
    -   即进入 QT安装目录\版本号\Src\qtbase\src\plugins\sqldrivers\mysql\ 目录，实为QT mysql 驱动的源代码目录
-   4.修改 C:\Qt\Qt5.14.1\5.14.1\Src\qtbase\src\plugins\sqldrivers\mysql\mysql.pro 文件 
    - 增加 ``` LIBS += -LC:\Qt\Qt5.14.1\5.14.1\Src\qtbase\src\plugins\sqldrivers\mysql -lmysql
INCLUDEPATH +="C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/include"
QMAKE_LIBDIR +="C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/lib"```
    - 即 增加 MySQL Connector C 6.1 安装目录下的include路径  和MySQL Connector C 6.1 安装目录下的lib路径  ,同时 增加MySQL Connector C 6.1 安装目录下的lib路径下的libmysql.dll(.lib)库
-   5. 输入 ```C:\Qt\Qt5.14.1\5.14.1\msvc2017\bin\qmake -- MYSQL_INCDIR="C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\include" MYSQL_LIBDIR="C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\lib" ```
    -   即 qmake -- -- MYSQL_INCDIR=MySQL Connector C 6.1 安装目录下的include路径 MYSQL_LIBDIR=MySQL Connector C 6.1 安装目录下的lib路径 
- 6.命令行输入 nmake
- 7.命令行输入 nmake install
- 8. 出错处理：
  - 1. 找不到 mysql 库 ： 
    - qtsqldrivers-config.pri 文件找不到，在  C:\Qt\Qt5.14.1\5.14.1\Src\qtbase\src\plugins\sqldrivers\ 下有这个文件，提示在哪里找不到就复制到哪里去。我的是在文件生产目录找不到，那就把这个复制过去
    - MySQL Connector C 6.1 未安装正确
    - 增加MySQL Connector C 6.1 安装目录下的lib路径下的libmysql.dll(.lib)库 的操作不正确。（mysql.pro 文件没写对）
    - qmake -- -- MYSQL_INCDIR=MySQL Connector C 6.1 安装目录下的include路径 MYSQL_LIBDIR=MySQL Connector C 6.1 安装目录下的lib路径 命令写错C Connector 的路径了

