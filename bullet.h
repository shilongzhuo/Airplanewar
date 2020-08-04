#ifndef BULLET_H
#define BULLET_H

#include <QPixmap>
#include "sourse.h"


class Bullet
{
public:
    Bullet(int x,int y,int power,bool is_blue_bullet);//子弹坐标及能量和派别
    ~Bullet();
    void move (double x,double y);
    QPixmap getBulletPath();
    void setX(int x);
    void setY(int y);
    void setSpeed(int speed);
    void setPower(int power);
    void setBulletPath(QPixmap x);
    int getX();
    int getY();
    int getSpeed();
    int getPower();
    int getWidth();
    int getHeight();
    void setWidth(int width);
    void setHeight(int heigth);

private:
    double x,y;//子弹坐标位置
    QPixmap bulletPath;
    int speed;
    int power;//子弹的伤害
    bool is_blue_bullet = true;//判断子弹是哪方的
    int width;//子弹尺寸
    int height;
};

#endif // BULLET_H
