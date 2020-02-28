# QT学习


<!-- TOC -->

- [QT学习](#qt%e5%ad%a6%e4%b9%a0)
  - [基础](#%e5%9f%ba%e7%a1%80)
    - [坐标系统](#%e5%9d%90%e6%a0%87%e7%b3%bb%e7%bb%9f)
    - [layouts](#layouts)
    - [控件](#%e6%8e%a7%e4%bb%b6)
    - [消息基础](#%e6%b6%88%e6%81%af%e5%9f%ba%e7%a1%80)
    - [QT 消息中级](#qt-%e6%b6%88%e6%81%af%e4%b8%ad%e7%ba%a7)
      - [eventFilter 截取消息](#eventfilter-%e6%88%aa%e5%8f%96%e6%b6%88%e6%81%af)
      - [notify 通知消息](#notify-%e9%80%9a%e7%9f%a5%e6%b6%88%e6%81%af)
      - [postEvent 和 sendEvent](#postevent-%e5%92%8c-sendevent)
    - [QPainter 和重写自定义控件](#qpainter-%e5%92%8c%e9%87%8d%e5%86%99%e8%87%aa%e5%ae%9a%e4%b9%89%e6%8e%a7%e4%bb%b6)
      - [QPainter 的绘图效率(引用)](#qpainter-%e7%9a%84%e7%bb%98%e5%9b%be%e6%95%88%e7%8e%87%e5%bc%95%e7%94%a8)
      - [QPainter 实现自己的控件](#qpainter-%e5%ae%9e%e7%8e%b0%e8%87%aa%e5%b7%b1%e7%9a%84%e6%8e%a7%e4%bb%b6)
    - [信号和槽](#%e4%bf%a1%e5%8f%b7%e5%92%8c%e6%a7%bd)
      - [定义](#%e5%ae%9a%e4%b9%89)
      - [需要注意的事项](#%e9%9c%80%e8%a6%81%e6%b3%a8%e6%84%8f%e7%9a%84%e4%ba%8b%e9%a1%b9)
      - [总结：](#%e6%80%bb%e7%bb%93)
    - [高级Painter](#%e9%ab%98%e7%ba%a7painter)
    - [QDialog](#qdialog)
      - [代码展示](#%e4%bb%a3%e7%a0%81%e5%b1%95%e7%a4%ba)
    - [MainWindow](#mainwindow)
    - [QFile-QBuffer-QXXXXStream-Mapping](#qfile-qbuffer-qxxxxstream-mapping)
      - [QFile](#qfile)
      - [QBuffer //内存 文件](#qbuffer-%e5%86%85%e5%ad%98-%e6%96%87%e4%bb%b6)
      - [QDataStream QTextStream](#qdatastream-qtextstream)
    - [Socket-TCP-UDP-BOARDCAST-MULI-CAST](#socket-tcp-udp-boardcast-muli-cast)
    - [关于在new 生成控件的时候this 的解释 和 deleteLater](#%e5%85%b3%e4%ba%8e%e5%9c%a8new-%e7%94%9f%e6%88%90%e6%8e%a7%e4%bb%b6%e7%9a%84%e6%97%b6%e5%80%99this-%e7%9a%84%e8%a7%a3%e9%87%8a-%e5%92%8c-deletelater)
      - [关于在new 生成控件的时候this](#%e5%85%b3%e4%ba%8e%e5%9c%a8new-%e7%94%9f%e6%88%90%e6%8e%a7%e4%bb%b6%e7%9a%84%e6%97%b6%e5%80%99this)
      - [deleteLater](#deletelater)
    - [QT动态库](#qt%e5%8a%a8%e6%80%81%e5%ba%93)
    - [QT静态库](#qt%e9%9d%99%e6%80%81%e5%ba%93)
    - [QT JSON](#qt-json)
    - [QT 加密](#qt-%e5%8a%a0%e5%af%86)
    - [QSQLDatabase 的使用](#qsqldatabase-%e7%9a%84%e4%bd%bf%e7%94%a8)
      - [编译Mysql 驱动](#%e7%bc%96%e8%af%91mysql-%e9%a9%b1%e5%8a%a8)
    - [QSQLDatabase 的使用](#qsqldatabase-%e7%9a%84%e4%bd%bf%e7%94%a8-1)
      - [原生执行SQL语句](#%e5%8e%9f%e7%94%9f%e6%89%a7%e8%a1%8csql%e8%af%ad%e5%8f%a5)
      - [QSQLModel 方式 执行](#qsqlmodel-%e6%96%b9%e5%bc%8f-%e6%89%a7%e8%a1%8c)
      - [QTableView 特别方便](#qtableview-%e7%89%b9%e5%88%ab%e6%96%b9%e4%be%bf)
    - [Qprocess 的使用](#qprocess-%e7%9a%84%e4%bd%bf%e7%94%a8)

<!-- /TOC -->


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



### 信号和槽

#### 定义
- 信号（Signal) 函数必须放在signals 保留字下，并且不需要实现
- 槽 必须放在slots 保留字下，切必须实现
- 信号和槽通过QObject::connect()函数连接
- 当信号被触发时，槽函数执行
- 触发信号用emit 关键字
  

#### 需要注意的事项
-   信号和槽，时QT的扩展，所以实现信号和槽的类，必须是QObject的子类
-   实现信号和槽的类，必须以 Q_OBJECT 开始
- 连接信号和槽，需要用到 SIGNAL 和 SLOT 宏转换为字符串
- 一个信号可以和多个槽连接，槽函数调用的顺序是不确定的
- 多个信号可以同时连接一个槽
- 信号可以连接信号，形成传递
- 信号和槽的参数参数应该一样多，类型必须一样。
- 信号可以重载
- 槽可以重载
- 信号和槽都可以有默认参数
- 槽函数可以向普通函数一样调用（Widget::close())
- 在槽函数中，调用sender可以获得信号调用者
- .....

#### 总结：
- 一个类 QObject
- 三个宏 Q_OBJECT SIGNAL SLOT
- 三个保留字 signals slots  emit


### 高级Painter
-  QGraphicSence 和 QGraphicsItem 头文件使用



### QDialog
- 模块对话框和普通对话框：
  - 通过exec() 运行的是模块对话框，模块对话框有自己的消息循环，且把APP 的消息循环接管了（就是模块对话框出来以后，主窗口就点不动了
  - 通过show（） 运行的是普通对话框，普通对话框可以有多个，且互不干扰
  - 如果Dialog 是通过exec() 来来显示，可以通过 accept() 和 Reject() 来关闭窗口。show() 显示则通过 close() 来关闭，和 Qwidget 一样。

- 有很多特殊的 Dialog 如打印（预览） ，文件选择，MessageBox，颜色选择，字体选择

#### 代码展示

- Dialog.h
```
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QFontDialog>

#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:s
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:


public slots:

    void _clicked()
    {
#if 0
        QDialog* qd=new QDialog();
//        qd->setParent(this); //不能设置Parent。。。
         qDebug()<<"Clicked";

         QPushButton* qpp=new QPushButton("Accept",qd);
         connect(qpp,SIGNAL(clicked(bool)),qd,SLOT(accept()));
         int rect;
        if(rect=qd->exec() == QDialog::Accepted) //exec() 显示是个模块对话框 只能有一个
            {

            qDebug()<<"Accept";
            }

        if(rect==QDialog::Rejected)
        {
            qDebug()<<"Rejected";
        }
//         qd->show(); //show（） 显示，是正常对话框 可以有无数个

#endif
#if 0


        QString Filename =
        QFileDialog::getSaveFileName(NULL,"Slect File for save",_str,"PNG File(*.png)"); //QFIleDialog 一般直接直接使用静态函数 getOpenFileName 指定打开文件
        qDebug()<<Filename;
        QFileInfo FileInfo(Filename);
        _str=FileInfo.path();


        QFontDialog* font=new QFontDialog(this);
        font->exec();
         qDebug()<<font->selectedFont();
 #endif

         QMessageBox::warning(this,"警告","警告@！！！！");

    }

private:
    Ui::Dialog *ui;
    QString _str;
};

#endif // DIALOG_H


```

- Dialog.cpp

```
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QPushButton* pb=new QPushButton("new one");
    pb->setParent(this);
    ui->setupUi(this);
    connect(pb,SIGNAL(clicked(bool)),this,SLOT(_clicked()));
}

Dialog::~Dialog()
{
    delete ui;
}

```
- main.cpp

```
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}

```

- dialog.ui

```
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>Dialog</class>
 <widget class="QDialog" name="Dialog">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>946</width>
    <height>560</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>Dialog</string>
  </property>
 </widget>
 <layoutdefault spacing="6" margin="11"/>
 <resources/>
 <connections/>
</ui>

```
  
### MainWindow

- 主窗口
- 菜单栏 ： Qmenu 菜单类 QMenuBar 菜单栏 QAction 菜带项目
- Status Bar 
- Tool Bar 
- QSystemTrayIcon 系统托盘类

- 示例代码如下：
  - mw.h  
```
#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QList>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QSystemTrayIcon>  //系统托盘类
#include "mview.h"

class mw : public QMainWindow
{
    Q_OBJECT

public:
    mw(QWidget *parent = 0);
    ~mw();

private:
QString _str;
mview* _view;
QMenu* _menu;
QSystemTrayIcon* _icon;

public slots:
    void open_file()
    {
        _str=QFileDialog::getOpenFileName(this,"",_str,"TXT File (*.txt)");

        qDebug()<<"Opened File :"<<_str;



    }

    void open_dir()
    {
        _str=QFileDialog::getExistingDirectory(this,"",_str);

        qDebug()<<"Opened Directory :"<<_str;



    }

//    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);

signals:
    void clicked();
};



#endif // MW_H


```

- mw.cpp

```
#include "mw.h"

mw::mw(QWidget *parent)
    : QMainWindow(parent)
{
    //加菜单
    QMenuBar* menubar=this->menuBar(); //获取mainWindow 里面的MenuBar
    QMenu* menu=menubar->addMenu("&Open"); //通过MenuBar 添加菜单，每个菜单对弈一个菜单项
    QAction* open_file=new QAction("Open File");
    QAction* open_Directory=new QAction("Open Directory");
    QAction* exit_this=new QAction("Exit");
//    QAction* blank=new QAction("Exit");

    exit_this->setShortcut(QKeySequence::Quit);
    open_file->setShortcut(QKeySequence::Open);
    connect(exit_this,SIGNAL(triggered(bool)),this,SLOT(close()));  //绑定槽函数，信号使用trggered()
    connect(open_file,SIGNAL(triggered(bool)),this,SLOT(open_file()));
     connect(open_Directory,SIGNAL(triggered(bool)),this,SLOT(open_dir()));
    QList<QAction*> ql={
        open_file,
        open_Directory,
        exit_this
    };
    menu->addActions(ql);
    _menu =menu;

    // ToolBar

    QToolBar* tb1= this->addToolBar("TollBar");
    tb1->addActions(ql);


    //Status Bar

    QStatusBar* stb=this->statusBar();
    stb->addWidget(new QLabel("OK"));
    stb->addActions(ql);



    _view = new mview;

    this->setCentralWidget(_view);

    this->setWindowOpacity(0.9); //设置 窗口透明度 小数

    //创建托盘类
    _icon=new QSystemTrayIcon(this);
    _icon->setIcon(QIcon("E:/code/universal/QT/MW/1.ico"));
    _icon->setToolTip("我是Elliot 的小程序的哦");
    _icon->show();

}


//void mw::paintEvent(QPaintEvent *event)
//{


//}


  void mw::mousePressEvent(QMouseEvent *event)
  {
      if(event->button()==Qt::RightButton)
    _menu->exec(QCursor::pos());
  }

  bool mw::event(QEvent *event)
  {
        if(event->type()==QEvent::Close)
        {
            return true;
        }

        return QMainWindow::event(event);
  }


mw::~mw()
{

}

```

- mview.h

```
#ifndef MVIEW_H
#define MVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

class mview : public QWidget
{
    Q_OBJECT
public:
    explicit mview(QWidget *parent = nullptr){}

    void paintEvent(QPaintEvent *event)
    {
        QPainter* panter=new QPainter(this);
        panter->fillRect(rect(),Qt::black);
        panter->drawArc(50,50,30,30,10,50);
        panter->drawPixmap(QPoint(0,0),QPixmap("E:/code/universal/QT/MW/11.png"));
    }

signals:

public slots:
};

#endif // MVIEW_H

```
- mview.cpp
```
#include "mview.h"

mview::mview(QWidget *parent) : QWidget(parent)
{


}


```

- main.cpp

```
#include "mw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mw w;
    w.show();

    return a.exec();

}

```

### QFile-QBuffer-QXXXXStream-Mapping
- QIODevice 是所有IO 类的父类
  - QFile
  - QBuffer //Memery File
  - QTCPSocket
  - QUDPSocket

#### QFile
- 头文件 QFile
- 函数  open write 
- QString  是多字节字符串 QByteArray 是字节数

#### QBuffer //内存 文件
- 头文件 QBuffer
- 函数  open write 


#### QDataStream QTextStream

  
- 代码展示
  - mw.h

```
#ifndef MW_H
#define MW_H

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QBuffer>
#include <QTextBrowser>
#include <QPixmap>
#include <QLabel>
#include <QTextStream>
#include <QDataStream>


class mw : public QWidget
{
    Q_OBJECT
public:
    explicit mw(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MW_H

```

- mw.cpp

```
#include "mw.h"

mw::mw(QWidget *parent) : QWidget(parent)
{
    QTextBrowser* qbb=new QTextBrowser(this);
    QFile file("devil.txt");
    file.open(QFile::ReadWrite);

    file.write("jaingnan");


    file.close();


    QBuffer buffer;

    buffer.open(QBuffer::ReadWrite);
#if 0
    buffer.write("aa");
//    QString aa('江南的风');
    buffer.write("Nothing to read");

#endif

    QPixmap* map=new QPixmap("11.png");

    map->save(&buffer,"png");


    qbb->setText(buffer.buffer());
    QString str=tr("%1").arg(buffer.size());
    qbb->append(str);
    buffer.close();


    QPixmap* png=new QPixmap;
    png->loadFromData(buffer.buffer(),"PNG");
    const QPixmap png1=*png;
    QLabel* label=new QLabel(this);
    label->setPixmap(png1);


    //Text Stream
    QFile file1("stream.txt");
    file1.open(QFile::ReadWrite);

   QTextStream qs(&file1);

   qs<<"nimeide"<<1.2<<22;


   file.close();


   //虚拟内存 Virtual Memory

}


int main  (int argc,char ** argv)
{
    QApplication app(argc,argv);


    mw* mw1=new mw();
    mw1->show();
    return app.exec();

}

```

### Socket-TCP-UDP-BOARDCAST-MULI-CAST
- QT socket 需要在 .pro 文件中添加 QT += newwork
- TCPServer 头文件

### 关于在new 生成控件的时候this 的解释 和 deleteLater

#### 关于在new 生成控件的时候this
- 可以再生成控件的时候指定父对象this.此时，子对象的内存管理由父对象控制。
  - 当父对象销毁的时候，子对象也被父对象销毁。避免了内存泄漏
  - 窗口类可指定父子关系，避免了多一步的绑定
  - 指定了父对象后也可以使用delete 释放，此时子对象的析构函数会通知父对象接触父子关系

#### deleteLater 
- 定义 延时删除，只是发送标记，不是立即删除


### QT动态库

- QT 使用LIBRARYSHARED_EXPORT （Q_DECL_EXPORT） 声明类来跨平台宏
- 使用动态库是，需要在使用动态库的程序内包含源动态库的头文件，同时，包含库文件
  - 1.包含库头文件
  - 2.包含库位置：
    - 在QT 的 .pro 文件中添加
    - ``` LIBS += LE:\code\universal\QT\build-Library-Desktop_Qt_5_14_1_MSVC2017_32bit-Debug\debug -lLibrary```
    - ```LIBS += L库的目录 -l库的名称```
    - 不需要后缀 .dll


### QT静态库
- ....


### QT JSON
- 头文件 <QJsonDocument> <QJsonDocument> 
- 

### QT 加密
- 头文件 #include <QCryptographicHash> 
  - 有MD5 SHA 等加密

### QSQLDatabase 的使用

#### 编译Mysql 驱动
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

### QSQLDatabase 的使用
#### 原生执行SQL语句

#### QSQLModel 方式 执行

#### QTableView 特别方便
- 用来显示QTable 类型的数据 



### Qprocess 的使用
- 头文件
  - Qprocess
  - 