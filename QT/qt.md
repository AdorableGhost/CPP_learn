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

####  eventFilter 截取消息
  - 首先需要安装EventFilter .经过这个控件的消息都必须经过这个过滤器
  -  pb->installEventFilter(this);
  -  安装处理特定消息后必须将 消息返回 QWidget 。

- 代码示例：
  - dWidget.h
 ```
 #ifndef DWIDGET_H
#define DWIDGET_H

#include <QWidget>

class dWidget : public QWidget
{
    Q_OBJECT
public:
    explicit dWidget(QWidget *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event);

    QObject* _ob;
signals:

public slots:
};

#endif // DWIDGET_H

 ```

  - dWidget.cpp
  
  ```
  #include <QApplication>
#include <QEvent>
#include <QPushButton>
#include <QDebug>
#include "dwidget.h"

dWidget::dWidget(QWidget *parent) : QWidget(parent)
{

    QPushButton* pb=new QPushButton("lalal");
    pb->setParent(this);
    connect(pb,SIGNAL(clicked(bool)),this,SLOT(close()));

    _ob=pb;
    pb->installEventFilter(this);
}

bool dWidget::eventFilter(QObject *watched, QEvent *event){

    if( watched== (QObject*)_ob  && (event->type()==QEvent::MouseButtonPress
                                     || event->type()==QEvent::MouseButtonDblClick))
    {
        qDebug()<<"Msg have been catched!\n an Never exit!!......";
        return true;

    }

    return QWidget::eventFilter(watched,event);  //必须返回给Qwidget
}

int main (int argc,char ** argv)
{
    QApplication ap(argc,argv);
    dWidget* dd=new dWidget();
    dd->show();
    return ap.exec();

}

  ```

####  notify 通知消息

- notify 函数属于 QApplication .需要重载QApplciation 实现自己的通知消息
- 示例代码见最后

#### postEvent 和 sendEvent 
- ap.postEvent(dd,new QEvent(QEvent::User)); //postEvent 加入消息队里等待处理
- ap.sendEvent(dd,new QEvent(QEvent::User)); //发送给消息队列并立即处理
- 示例代码见最后

- qApp 是全局指针。可以全局调用
   - app.h 

```
#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QDebug>
class APP : public QApplication
{
    Q_OBJECT
public:
    APP(int argc,char** argv):QApplication(argc,argv)
    {

    }

     QWidget* topW;
    bool notify(QObject *, QEvent *);
};

#endif // APP_H

```

  - app.cpp
  
  ```
  #include "app.h"

bool APP::notify(QObject *ob, QEvent *ev)
{
    if(this->topLevelWidgets().count()>0)
    {
        topW=this->topLevelWidgets().at(0);
        if(ob==(QObject*)topW && ev->type() ==QEvent::MouseButtonPress)
        {

        qDebug()<<"main window is clicked";
        }
    }


    return QApplication::notify(ob,ev);
}

  ```

-   dwidget.h
```
#ifndef DWIDGET_H
#define DWIDGET_H

#include <QWidget>

class dWidget : public QWidget
{
    Q_OBJECT
public:
    explicit dWidget(QWidget *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event);

    QObject* _ob;

bool  event(QEvent *event);
signals:

public slots:
};

#endif // DWIDGET_H

```
- dwidget.cpp
  
```
//#include <QApplication>
#include <QEvent>
#include <QPushButton>
#include <QDebug>
#include "dwidget.h"
#include "app.cpp"

dWidget::dWidget(QWidget *parent) : QWidget(parent)
{

    QPushButton* pb=new QPushButton("lalal");
    pb->setParent(this);
    connect(pb,SIGNAL(clicked(bool)),this,SLOT(close()));

    _ob=pb;
    pb->installEventFilter(this);
}

bool dWidget::eventFilter(QObject *watched, QEvent *event){

    if( watched== (QObject*)_ob  && (event->type()==QEvent::MouseButtonPress
                                     || event->type()==QEvent::MouseButtonDblClick))
    {
        qDebug()<<"Msg have been catched!\n an Never exit!!......";
        return true;

    }


    return QWidget::eventFilter(watched,event);
}


bool dWidget::event(QEvent *event)
{
    if(event->type()==QEvent::User)
    {
        qDebug()<<"User Event is comming";
    }

    return QWidget::event(event);
}
int main (int argc,char ** argv)
{
    APP ap(argc,argv);
    dWidget* dd=new dWidget();
    dd->show();
    //发送一个Event 给 dWidget
    ap.postEvent(dd,new QEvent(QEvent::User)); //postEvent 加入消息队里等待处理
    ap.sendEvent(dd,new QEvent(QEvent::User)); //发送给消息队列并立即处理

    return ap.exec();

}

```
### QPainter 和重写自定义控件
- 头文件 <QPainter>
- 常用功能： drawLine drawRect drawText 等 ，可通过translate transform 变换

#### QPainter 的绘图效率(引用)
- 通过定义 PaintDevice 然后在 PainDevice 中画，然后再显示
- 可以通过 Qpainter 实现 一个自定义的画图工具
- 代码如下：
  
  - ww.h
```

#ifndef WW_H
#define WW_H
#include <QApplication>
#include <QPainter>
#include <QEvent>
#include <QWidget>
#include <QMouseEvent>

class ww : public QWidget
{
    Q_OBJECT
public:
    explicit ww(QWidget *parent = nullptr);


//    void Pain()
//    {
//        p->drawLine(QPoint(0,0),QPoint(0,100));
//        p->drawRect(QRect(QPoint(50,50),QPoint(200,100)));
//    }

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

   QVector<QVector<QPoint>>_lines;   //用Qvector 记录连起来的点是line ,——lines 则是这些线的集合

    void paintEvent(QPaintEvent*);
signals:

public slots:
};

#endif // WW_H

```

- ww.cpp

```
#include "ww.h"

ww::ww(QWidget *parent) : QWidget(parent)
{
//    QPaintDevice* qd=new QPaintDevice();


}

void ww::paintEvent(QPaintEvent* e)
{
     QPixmap* map=new QPixmap(size());
     map->fill(Qt::gray);
     //QPainter* p=new QPainter(this);
     QPainter* p=new QPainter(map);
     p->setBackground(QBrush(QColor(Qt::gray)));
     p->setBrush(Qt::red);
     p->setPen(QPen(Qt::green));
     p->translate(50,50);
     QTransform* trans=new QTransform;
     trans->rotate(30);
     trans->scale(0.3,0.3);
     p->setTransform(*trans);

    p->drawLine(QPoint(0,0),QPoint(100,100));
    p->drawRect(QRect(QPoint(50,50),QPoint(200,100)));
    p->drawText(QPoint(100,100),"Hello 你好");
    p->drawPixmap(QPoint(200,200),QPixmap("11.png"));

    p->end(); //在 PixMAp 绘画结束


    p->begin(this); //重新开始在屏幕上画
    p->drawPixmap(QPoint(0,0),*map); //重新在窗口中显示图片

    p->setBrush(Qt::black);
    p->setPen(QPen(Qt::black));

    // 下面为定义 划线的函数

    for(int x=0;x<_lines.size();x++)
    {
       const  QVector<QPoint>& line = _lines.at(x);
        for (int i=0;i<line.size()-1;i++)
        {
            p->drawLine(line.at(i),line.at(i+1));
        }


    }


}



void ww::mouseMoveEvent(QMouseEvent *event)
{
    QVector<QPoint>& lastLine=_lines.last();
    lastLine.append(event->pos());
    update(); //重绘窗口，隐含调用PaintEvent
}
void ww::mousePressEvent(QMouseEvent *event)
{

    QVector<QPoint> line;
    _lines.append(line);

    QVector<QPoint>& lastLine=_lines.last();
    lastLine.append(event->pos());
}


void ww::mouseReleaseEvent(QMouseEvent *event)
{
    QVector<QPoint>& lastLine=_lines.last();
    lastLine.append(event->pos());
}


int main (int argc,char** argv)
{
    QApplication app(argc,argv );

    ww* window=new ww();
//    window->Pain();
    window->show();

    return app.exec();
}

```

#### QPainter 实现自己的控件



