#ifndef SUPLY_H
#define SUPLY_H

#include <QWidget>
#include "sourse.h"

class Suply : public QWidget
{
    Q_OBJECT
public:
    explicit Suply(QWidget *parent = 0);

signals:

public slots:
    int getValue();
    void setValue(int value);
    void getSuplyPath(QPixmap p);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void setWidth(int width);
    void setHeight(int height);
    int  getWidth();
    int getHeight();
    QPixmap getSuplyPath();
private:
    int value;
    int x;
    int y;
    int width;
    int height;
    QPixmap suplyPath;

};

#endif // SUPLY_H
