#include "gameIntroduce.h"

GameIntroduce::GameIntroduce(QWidget *parent) : QWidget(parent)
{

}
void GameIntroduce::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(rect(),QPixmap(":/image/introduce.png"));
    this->resize(2000,1000);
    this->move(0,0);
}
