#include "glorySort.h"

GlorySort::GlorySort(QWidget *parent) : QWidget(parent)
{
    QSqlQuery query(Sourse::db);
    bool success=query.exec("select * from gameInformation order by credit desc");
    if(!success)
    {
        qDebug()<<QObject::tr("排序失败！");
    }
//    query.exec(QString("select count(*) from gameInformation;"));
    query.next();
    name1 = new QLabel(this);
    credit1 = new QLabel(this);
    name2 = new QLabel(this);
    credit2 = new QLabel(this);
    name3 = new QLabel(this);
    credit3 = new QLabel(this);
    name1->resize(200,200);
    credit1->resize(200,200);
    name2->resize(200,200);
    credit2->resize(200,200);
    name3->resize(200,200);
    credit3->resize(200,200);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    name1->setFont(QFont("华文行楷",30,100));
    name1->setPalette(pe);
    credit1->setFont(QFont("华文行楷",30,100));
    credit1->setPalette(pe);

    name2->setFont(QFont("华文行楷",30,100));
    name2->setPalette(pe);
    credit2->setFont(QFont("华文行楷",30,100));
    credit2->setPalette(pe);
    name3->setFont(QFont("华文行楷",30,100));
    name3->setPalette(pe);
    credit3->setFont(QFont("华文行楷",30,100));
    credit3->setPalette(pe);


    name1->setText(query.value(1).toString());
    credit1->setText(query.value(3).toString()+"分");

    name1->setGeometry(150,500,200,200);
    credit1->setGeometry(350,500,200,200);
    query.next();
    qDebug()<<query.value(1).toString()<<query.value(3).toString();
    name2->setText(query.value(1).toString());
    credit2->setText(query.value(3).toString()+"分");
    name2->setGeometry(900,500,200,200);
    credit2->setGeometry(1100,500,200,200);
    query.next();
    name3->setText(query.value(1).toString());
    credit3->setText(query.value(3).toString()+"分");
    name3->setGeometry(1600,550,200,200);
    credit3->setGeometry(1800,550,200,200);



}
void GlorySort::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(rect(),QPixmap(":/image/sort.png"));
    this->resize(2000,1000);
    this->move(0,0);
}
