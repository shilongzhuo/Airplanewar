#include "bullet.h"

Bullet::Bullet(int x,int y,int power,bool is_blue_bullet)
{   
    this->power = power;
    this->is_blue_bullet = is_blue_bullet;
    this->x = x;
    this->y = y;
    bulletPath.load(ENEMY_BULLET1_PATH);
    speed = 20;
    width = ENEMY_BULLET_WIDTH;
    height = ENEMY_BULLET_HEIGHT;

}
void Bullet::move (double x,double y)
{
    this->x += x;
    this->y += y;
}
QPixmap Bullet::getBulletPath()
{
    return bulletPath;
}
void Bullet::setBulletPath(QPixmap x)
{
    this->bulletPath = x;
}

void Bullet::setX(int x)
{
    this->x = x;
}

void Bullet::setY(int y)
{
    this->y = y;
}
void Bullet::setSpeed(int speed)
{
    this->speed = speed;
}

int Bullet::getSpeed()
{
    return speed;
}

int Bullet:: getX()
{
    return x;
}

int Bullet::getY()
{
    return y;
}
void Bullet::setPower(int power)
{
    this->power = power;
}
int Bullet::getPower()
{
    return power;
}
int Bullet::getWidth()
{
    return width;
}

int Bullet::getHeight()
{
    return height;
}

void Bullet::setWidth(int width)
{
    this->width = width;
}

void Bullet::setHeight(int height)
{
    this->height = height;
}

Bullet::~Bullet()
{

}
