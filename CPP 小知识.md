# CPP 小知识

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