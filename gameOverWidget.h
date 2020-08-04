#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>
#include "sourse.h"

class GameOverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverWidget(int credit,QString mode,int people,QWidget *parent = 0);

signals:
    gameagain(int people,QString mode);
    gameover();

public slots:
    void showCredit();//显示分数
    void showMode();//显示模式
    void paintEvent(QPaintEvent *event);
    void toGameAgain();
    void toCancel();

private:
    QLabel* creditshow;//分数
    QLabel* modeshow;//模式
    QString mode;
    int credit;
    int people;//双人还是单人模式
    QPushButton* gameAgain;//再来一局
    QPushButton* cancel;//结束战斗，返回主菜单
};

#endif // GAMEOVERWIDGET_H
