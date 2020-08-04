#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "sourse.h"
#include <QLineEdit>
#include "gameintroduce.h"
#include "levelSelection.h"
#include "gameWidget.h"
#include "loginWidget.h"
#include "glorySort.h"


class MyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

signals:

public slots:
    void toUserLogin();//账号登陆
    void toTurister();//游客登录
    void toIntroduce();//关于游戏
    void toSet();//游戏设置
    void toQuit();//退出游戏
    void paintEvent(QPaintEvent *event);
    void toMain();//主页面显示
    bool IsTableExist(QSqlQuery &query,QString table);//判断表是否存在

private:
    QPushButton* button1;//账号登陆
    QPushButton* button2;//游客登录
    QPushButton* button3;//关于游戏
    QPushButton* button4;//游戏设置
    QPushButton* button5;//退出游戏
    QVBoxLayout* layout;//垂直页面布局
    LoginWidget* loginwidget;//登录页面
    LevelSelection* levelwidget;//模式选择页面
    GameIntroduce* introduce;//游戏介绍页面
    GameWidget * w;//游戏界面
    GlorySort* sort;//排行榜界面


};

#endif // MYWINDOW_H
