#ifndef AIRPLANE_H
#define AIRPLANE_H
#include <QPixmap>
#include "sourse.h"


class AirPlane
{
public:
    AirPlane(int k,bool is_blue_plane);
    AirPlane();
    ~AirPlane();

private:
    double xpos;
    double ypos;//飞机x,y坐标
    QPixmap planePath;
    double speed;
    int life;//飞机生命值
    bool is_alive;//飞机是否存活
    int fight;//飞机撞击力
    int power;//飞机能量值，放技能用
    int height;//飞机尺寸设定
    int width;

public :
    int exploreTime;//爆炸显示时间(微秒）
    bool is_boom_sound;//是否放映过爆炸音乐
public:
    void setXpos(double x);
    void setYpos(double y);
    void setSpeed(double speed);
    void setPlanePath(QPixmap planePath);
    void setFight(int fight);
    void setLife(int life);
    void move(int x,int y);
    void setHeight(int high);
    void setWidth(int width);
    int getXpos();
    int getYpos();
    int getSpeed();
    int getLife();
    int getFight();
    int getPower();
    int getHeight();
    int getWidth();
    void setPower(int power);
    QPixmap getPlanePath();
    void explode();
    void heroMove(int x,int y);
    void addLife(int i);//加血
    void subLife(int i);//减血 

};


#endif // AIRPLANE_H
