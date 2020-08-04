#include "suply.h"

Suply::Suply(QWidget *parent) : QWidget(parent)
{
    value = 2;
    x = 400;
    y = 400;
    width = 30;
    height = 30;
    suplyPath.load(":/image/suply001.png");
}
int Suply::getValue()
{
    return value;
}

void Suply::setValue(int value)
{
    this->value = value;
}
void Suply::getSuplyPath(QPixmap p)
{
    this->suplyPath = p;
}

QPixmap Suply::getSuplyPath()
{
    return suplyPath;
}
void Suply::setX(int x)
{
    this->x = x;
}

void Suply::setY(int y)
{
    this->y = y;
}

int Suply::getX()
{
    return x;
}

int Suply::getY()
{
    return y;
}
void Suply::setWidth(int width)
{
    this->width = width;
}

void Suply::setHeight(int height)
{
    this->height = height;
}

int  Suply::getWidth()
{
    return width;
}

int Suply::getHeight()
{
    return height;
}
