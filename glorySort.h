#ifndef GLORYSORT_H
#define GLORYSORT_H

#include <QWidget>
#include "sourse.h"

class GlorySort : public QWidget
{
    Q_OBJECT
public:
    explicit GlorySort(QWidget *parent = 0);

signals:

public slots:
    void paintEvent(QPaintEvent *event);
private:
    QLabel* name1;
    QLabel* credit1;
    QLabel* name2;
    QLabel* credit2;
    QLabel* name3;
    QLabel* credit3;

};

#endif // GLORYSORT_H
