#include "airplane.h"

AirPlane::AirPlane(int power,bool is_blue_plane)
{ 
    planePath.load(":/image/myplane1.png");
    xpos = GAME_WIDTH*0.5 - MY_AIRPLANE_WIDTH*0.5;
    ypos = GAME_HEIGHT - MY_AIRPLANE_HEIGHT;
    speed = 10;
    life = 1;
    is_alive = true;
    life = true;
    fight = 2;
    exploreTime = SECOND/2;//500毫秒
    is_boom_sound = false;
    this->power = 10;
    width = MY_AIRPLANE_WIDTH;
    height = MY_AIRPLANE_HEIGHT;
}
AirPlane::AirPlane()
{

}

void AirPlane::setXpos(double x)
{
    xpos = x;
}

void AirPlane::setYpos(double y)
{
    ypos = y;
}

void AirPlane::setSpeed(double speed)
{
    this->speed = speed;
}

void AirPlane::setPlanePath(QPixmap planePath)
{
    this->planePath = planePath;
}

void AirPlane::move(int x, int y)
{
    xpos = xpos + x;
    ypos = ypos + y;
}

int AirPlane::getXpos()
{
    return xpos;
}

int AirPlane::getYpos()
{
    return ypos;
}

int AirPlane::getSpeed()
{
    return speed;
}

QPixmap AirPlane::getPlanePath()
{
    return planePath;
}

void AirPlane::explode()
{
    setPlanePath(QPixmap(PLANE_EXPLODE));
}
void AirPlane::heroMove(int x, int y)//英雄飞机框内移动
{
    if(getXpos()+x<=GAME_WIDTH-MY_AIRPLANE_WIDTH&&
            getXpos()+x>=0&&
            getYpos()+y<=GAME_HEIGHT-MY_AIRPLANE_HEIGHT&&getYpos()+y>=0)
        move(x,y);
    else
        move(0,0);
}
void AirPlane::setLife(int life)
{
    this->life = life;
}
int AirPlane::getLife()
{
    return life;
}
void AirPlane::addLife(int i)
{
    life = life + i;
}

void AirPlane::subLife(int i)
{
    life = life - i;
    if(life <= 0 )
    {
        explode();
    }
}
int AirPlane::getFight()
{
    return fight;
}

void AirPlane::setFight(int fight)
{
    this->fight = fight;
}
void AirPlane::setPower(int power)
{
    this->power = power;
}
int AirPlane::getPower()
{
    return power;
}
void AirPlane::setHeight(int height)
{
    this->height = height;
}

void AirPlane::setWidth(int width)
{
    this->width = width;
}

int AirPlane::getHeight()
{
    return height;
}

int AirPlane::getWidth()
{
    return width;
}

AirPlane::~AirPlane()
{

}
