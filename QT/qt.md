# QT学习

## 基础
- .pro文件为工程文件
- .pro.user 特定环境的编译的工程文件

- hello World 代码
  
```
#include <QApplication>
//应用程序抽象类
#include <QWidget>
//窗口类

#include <QPushButton>
//按钮

int main (int argc,char** argv)
{

    QApplication app(argc,argv);
    QWidget w;
//    w为窗口对象
    QPushButton bt;
    bt.setText("点击我啊啊啊啊");
//    按钮也是个窗口 ，控件都是窗口
    bt.setParent(&w);
//    窗口对象的父子关系影响着显示位置
//    没有父窗口的窗口称之为主窗口
    QObject::connect(&bt,SIGNAL(clicked()),&w,SLOT(close()));
//    QT 对C++的扩展 ，和C++ std::bind 和 std::function 有相似之处
    w.show();
//    bt.show();
//    显示窗口
    w.setWindowTitle("Hello ,My first QT Program!");

    return  app.exec();

}
```
- LineEdit 示例
```
#include <QApplication>
//应用程序抽象类
#include <QWidget>
//窗口类
#include <QLineEdit>
#include <QPushButton>
//按钮

int main(int argc,char** argv)
{

    QApplication app(argc,argv);
    QWidget w;
    QLineEdit ql;
    ql.setEchoMode(QLineEdit::Password);
    ql.setParent(&w);
    ql.setPlaceholderText("请输入密码！");
//    QCompleter cp1(QStringList()<<"aaa"<<"bbb"<<"2333");
//    ql.setCompleter(&cp1);
    w.show();
//    显示窗口
    w.setWindowTitle("Hello ,My first QT Program!");

    return  app.exec();
}

```

###  坐标系统
- setGeometry(const &rect) 函数 或者 setGeometry(x,y,w,h);

### layouts

- QVBoxlayout
- QHBoxlayout
- GridLayout
- 代码示例

```
#include <QApplication>
//应用程序抽象类
#include <QWidget>
//窗口类
#include <QLineEdit>
#include <QPushButton>
//按钮
//#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

int main(int argc,char** argv)
{

    QApplication app(argc,argv);
    QWidget w;
    QLineEdit ql;
    ql.setEchoMode(QLineEdit::Password);
    ql.setParent(&w);
    ql.setPlaceholderText("请输入密码！");
//    ql.setGeometry(100,100,100,50);

    QPushButton qp;
    qp.setText("nimei");
    qp.setParent(&w);

#if 0
    QVBoxLayout qbb;
//    QHBoxLayout qbb;
    qbb.stretch(1);
    qbb.addWidget(&ql);
    qbb.addSpacing(50);
    qbb.addWidget(&qp);
    qbb.stretch(1);

#endif

    QGridLayout qbb;
    qbb.addWidget(&ql,1,1);
    qbb.addWidget(&qp,1,2);
    qbb.addWidget(new QPushButton,2,1);
    qbb.addWidget(new QPushButton,2,2);
    qbb.addWidget(new QPushButton,3,1);
    qbb.addWidget(new QPushButton,3,2);

    qbb.setColumnStretch(0,1);
    qbb.setColumnStretch(3,1);
    qbb.setRowStretch(0,1);
    qbb.setRowStretch(4,1);

//    QCompleter cp1(QStringList()<<"aaa"<<"bbb"<<"2333");
//    ql.setCompleter(&cp1);
    w.setLayout(&qbb);
//    设置layout
    w.show();
//    显示窗口
    w.setWindowTitle("Hello ,My first QT Program!");


    return  app.exec();
}


```

### 控件
