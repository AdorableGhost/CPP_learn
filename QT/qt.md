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


### 消息基础
- 代码
- dwin.hpp
```
    #ifndef DWIN_H
#define DWIN_H

#include <QWidget>
#include  <QPushButton>

class DWin : public QWidget
{
    Q_OBJECT
public:
    explicit DWin(QWidget *parent = nullptr);
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    QPushButton *pb;
signals:

public slots:
};

#endif // DWIN_H
```
- dwin.cpp

```
#include "dwin.h"
#include <iostream>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>

DWin::DWin(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    pb=new QPushButton("OK",this);
    pb->setDefault(true);
    //Lamda 表达式。。。。
    connect(pb,&QPushButton::clicked,[](){
        qDebug()<<"OK Pushed ............";
    });

}
/*
 * QAppkication 先得到消息 -》具体负责每个窗口的event（）获取-》具体负责每项消息处理的虚函数
 *我们可以做的：
 * 1》可以重载具体的虚函数来实现自己的功能
 * 2》可以重载event() 函数用来处理或者截取消息
 */

// event 管理所有的消息，用来截断所有消息 return ture ; 就能截取消息

bool DWin::event(QEvent *event)
{

return QWidget::event(event);
}

void DWin::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Your mouse have been release!";
}



void DWin::mousePressEvent(QMouseEvent *event)
{
    QPoint pt=event->pos();
    qDebug()<<pt;
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<"Left button have been pressed!";
    }

   if(event->modifiers() == Qt::ShiftModifier)
   {
       qDebug()<<"Shift Pressed LOL...";
   }
}


void  DWin::keyPressEvent(QKeyEvent *event)
{
    //返回大写的字母ASCII代码！
    auto mod=event->modifiers();
    auto key=event->key();
    qDebug()<<(char)key<<"   "<<mod;
}
void  DWin::keyReleaseEvent(QKeyEvent *event)
{

}
void  DWin::mouseMoveEvent(QMouseEvent *event)
{
    static long i;

    //默认的是鼠标按下后移动
    //设置窗口类 setMouseTracking(true) 后可实现鼠标不按下就接受移动消息！
    qDebug()<<"mouse Moved"<<i++;
}

void DWin::closeEvent(QCloseEvent *event)
{
    qDebug()<<"Closed Window";
}
void DWin::showEvent(QShowEvent *event)
{
 qDebug()<<"showing Window";
}
void DWin::hideEvent(QHideEvent *event)
{
    qDebug()<<"hidding Window";

}

int main (int argc ,char ** argv)
{
    QApplication app(argc,argv);

    DWin w;
    w.show();

    return app.exec();
}

```

### QT 消息中级

- eventFilter 截取消息