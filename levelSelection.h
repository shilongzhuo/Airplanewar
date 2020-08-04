#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H
#include "sourse.h"
#include "gameWidget.h"

class LevelSelection : public QWidget
{
    Q_OBJECT
public:
    explicit LevelSelection(QWidget *parent = 0);
    ~LevelSelection();

private:
    QPushButton* level1;//游戏等级设定
    QPushButton* level2;
    QPushButton* level3;
    QPushButton* level4;
    GameWidget* game1;//
    QMessageBox* box;//弹出框
    int people; //单人游戏或双人游戏
    QString mode;//模式选择

public slots:
    void toLevel1();
    void toLevel2();
    void toLevel3();
    void toLevel4();
    void paintEvent(QPaintEvent *event);
    void newgame(int people,QString mode);

    signals:
    toMainWidget();//返回主页面信号


};

#endif // LEVELSELECTION_H
