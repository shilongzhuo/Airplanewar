#include "loginWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QString>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    QLabel* nameLabel = new QLabel("用户名:");
    QLabel* passwordLabel = new QLabel("密码:");
    nameLine = new QLineEdit;
    password = new QLineEdit;
    this->resize(400,300);//设置页面大小
    QPixmap pixmap = QPixmap(":/image/background.jpg").scaled(this->size());
    QGridLayout* mainLayout = new QGridLayout;
    registered = new QPushButton(tr("&注册"));
    login = new QPushButton(tr("&登录"));
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(passwordLabel,1,0);
    mainLayout->addWidget(nameLine,0,1,1,3);
    mainLayout->addWidget(password,1,1,1,3);
    mainLayout->addWidget(registered,2,1);
    mainLayout->addWidget(login,2,2);
    this->setLayout(mainLayout);
    connect(registered,SIGNAL(clicked()), this, SLOT(registerLine()));
    connect(login,&QPushButton::clicked, this, &LoginWidget::loginBtn);
}
void LoginWidget::registeredBtn()
{
//     close();
//    QMessageBox* box = new QMessageBox;
//    box->setText("是否确定进入注册页面");
//    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
//    int result=box->exec();
//    switch (result)
//    {
//    case QMessageBox::Yes:
//        close();
//        registerLine();
//        break;
//    case QMessageBox::No:
//        break;
//    }
//     box->show();
}
void LoginWidget::loginBtn()
{
    QString name = nameLine->text();
    QString pass = password->text();
    if(name == ""||pass=="")
    {
        QMessageBox* box = new QMessageBox;
        box->setText("Error,Please enter your name and password");
        box->show();
        return;
    }
    QSqlQuery query(Sourse::db);
    query.exec(QString("select count(*) from gameInformation where username ='%1' and password = '%2';").arg(name,pass));
    query.next();
    qDebug()<<query.value(1).toString();
    if(query.value(0).toInt())
    {
        level = new LevelSelection;
        level->show();
        this->close();
//        connect(levelwidget,&LevelSelection::toMainWidget,this,&MyWindow::toMain);
    }
    else
    {
        QMessageBox* box = new QMessageBox;
        box->setText("用户名或密码错误，请重新输入正确的用户名密码");
        box->show();
        return;
    }

}
void LoginWidget::registerLine()
{
    QString name = nameLine->text();
    QString pass = password->text();
    if(name == ""||pass=="")
    {
        QMessageBox* box = new QMessageBox;
        box->setText("Error,Please enter your name and password");
        box->show();
        return;
    }
    else
    {
         QSqlQuery query(Sourse::db);
         query.exec(QString("insert into gameInformation (username , password ,"
                     "credit ) values ( '%1','%2','0')").arg(name,pass));
    }
    QMessageBox* box = new QMessageBox;
    box->setText("恭喜您注册成功");
    box->show();
}
LoginWidget::~LoginWidget()
{
//    delete box;
//    delete w;
//    delete label;
//    delete nameLabel;
//    delete passwordLabel;
//    delete mainLayout;
//    delete login;
//    delete registered;
}
