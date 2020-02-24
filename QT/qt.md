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
- QIODevice
