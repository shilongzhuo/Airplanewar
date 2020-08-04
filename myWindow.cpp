#include "myWindow.h"
#include "loginWidget.h"
#include "gameWidget.h"
#include "levelSelection.h"
#include "gameIntroduce.h"

#include <QSqlDatabase>


MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    button1 = new QPushButton("账号登录",this);
//    button1->setStyleSheet(BUTTON_STYLE_2);
//    button1->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    button2 = new QPushButton("游客登录",this);
//    button2->setStyleSheet(BUTTON_STYLE_2);
//    button2->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    button3 = new QPushButton("关于游戏",this);
//    button3->setStyleSheet(BUTTON_STYLE_2);
//    button3->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    button4 = new QPushButton("荣耀殿堂",this);
//    button4->setStyleSheet(BUTTON_STYLE_2);
//    button4->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    button5 = new QPushButton("退出游戏",this);
//    button5->setStyleSheet(BUTTON_STYLE_2);
//    button5->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    this->resize(700,600);
    button1->setGeometry(500,100,100,40);
    button2->setGeometry(500,200,100,40);
    button3->setGeometry(500,300,100,40);
    button4->setGeometry(500,400,100,40);
    button5->setGeometry(500,500,100,40);



    //connect实现按钮
    connect(button1,&QPushButton::pressed,this,&MyWindow::toUserLogin);
    connect(button2,&QPushButton::pressed,this,&MyWindow::toTurister);
    connect(button3,&QPushButton::pressed,this,&MyWindow::toIntroduce);
    connect(button4,&QPushButton::pressed,this,&MyWindow::toSet);
    connect(button5,&QPushButton::pressed,this,&MyWindow::toQuit);
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("gameInformation.db");
    //创建数据库表
//    QSqlQuery query;
//    bool success=query.exec("create table gameInformationd(id int primary key,username varchar,password varchar,credit int,numberOfGame int)");
//    if(success)
//        qDebug()<<QObject::tr("数据库表创建成功！\n");
//    else
//        qDebug()<<QObject::tr("数据库表创建失败！\n");
//        qDebug()<<query.lastError();

    if (!Sourse::createConnection())
    {

    }
//    Sourse::db.setDatabaseName("gameInformation.db");
//    db.open();
    QSqlQuery query(Sourse::db);
    if(IsTableExist(query,"gameInformation"))
    {
        //do nothing;
    }
    else
    {
        bool success = query.exec("create table gameInformation (id int primary key,username varchar,password varchar,credit int)");
        if(success)
            qDebug()<<"数据库表创建成功！\n";
        else
        {
            qDebug()<<"数据库表创建失败！\n";
            qDebug()<<query.lastError();
        }
        query.prepare("insert into gameInformation values(?,?,?,?)");
        query.bindValue(0,0);
        query.bindValue(1,"小张");
        query.bindValue(2,"123456");
        query.bindValue(3,120);
        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        query.bindValue(0,1);
        query.bindValue(1,"小王");
        query.bindValue(2,"123456");
        query.bindValue(3,130);
        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        query.bindValue(0,2);
        query.bindValue(1,"小李");
        query.bindValue(2,"123456");
        query.bindValue(3,140);
        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        query.bindValue(0,3);
        query.bindValue(1,"小明");
        query.bindValue(2,"123456");
        query.bindValue(3,150);

        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        query.bindValue(0,4);
        query.bindValue(1,"小刘");
        query.bindValue(2,"123456");
        query.bindValue(3,150);

        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        query.bindValue(0,5);
        query.bindValue(1,"小6");
        query.bindValue(2,"123456");
        query.bindValue(3,150);

        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
        //排序
        success=query.exec("select * from gameInformation order by credit");
        if(!success)
        {
            qDebug()<<QObject::tr("排序失败！");
        }
        query.prepare("insert into gameInformation values(?,?,?,?)");
        query.bindValue(0,6);
        query.bindValue(1,"小7");
        query.bindValue(2,"123456");
        query.bindValue(3,150);

        success=query.exec();
    }



}
//槽函数实现
bool MyWindow::IsTableExist(QSqlQuery &query , QString table)
{
    QString sql = QString("select count(*) from sqlite_master where type = 'table' name='%1'").arg(table);
    return query.exec(sql);
}
void MyWindow::toUserLogin()
{
    loginwidget = new LoginWidget;
    loginwidget->show();
//    levelwidget = new LevelSelection;
//    connect(levelwidget,&LevelSelection::toMainWidget,this,&MyWindow::toMain);
//    levelwidget->show();
//    this->close();
}

void MyWindow::toTurister()
{
    levelwidget = new LevelSelection;
    connect(levelwidget,&LevelSelection::toMainWidget,this,&MyWindow::toMain);
    levelwidget->show();
    this->close();
}

void MyWindow::toIntroduce()
{
    introduce = new GameIntroduce;
    introduce->show();
}

void MyWindow::toSet()
{
    sort = new GlorySort;
    sort->show();
}

void MyWindow::toQuit()
{
    close();
}

void  MyWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/image/background4.jpg"));
    p.drawPixmap(0,500,100,100,QPixmap(":/image/myplane.png"));
    p.drawPixmap(300,500,100,100,QPixmap(":/image/myplane1.png"));
    p.drawPixmap(300,100,100,100,QPixmap(":/image/enemy005.png"));
    p.drawPixmap(0,100,100,100,QPixmap(":/image/enemy006.png"));
    p.drawPixmap(150,300,100,100,QPixmap(":/image/enemyplane001.png"));
}
void MyWindow::toMain()
{
    this->show();
}

MyWindow::~MyWindow()
{
//    delete button1;
//    delete button2;
//    delete button3;
//    delete button4;
//    delete button5;
}
