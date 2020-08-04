#ifndef GAMEINTRODUCE_H
#define GAMEINTRODUCE_H

#include <QWidget>
#include "sourse.h"

class GameIntroduce : public QWidget
{
    Q_OBJECT
public:
    explicit GameIntroduce(QWidget *parent = 0);

signals:

public slots:
    void paintEvent(QPaintEvent *event);

private:

};

#endif // GAMEINTRODUCE_H
