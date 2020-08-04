#include "gameOverWidget.h"
#include "QString"

GameOverWidget::GameOverWidget(int credit,QString mode,int people,QWidget *parent) : QWidget(parent)
{
    this->resize(GAME_WIDTH,GAME_HEIGHT);
    creditshow = new QLabel(this);
    modeshow = new QLabel(this);
    this->credit = credit;
    this->mode = mode;
    this->people = people;
    showMode();
    showCredit();

    gameAgain = new QPushButton("再来一局",this);
    gameAgain->setGeometry(100,600,200,50);
    cancel = new QPushButton("返回菜单",this);
    cancel->setGeometry(500,600,200,50);

    connect(gameAgain,&QPushButton::pressed,this,&GameOverWidget::toGameAgain);
    connect(cancel,&QPushButton::pressed,this,&GameOverWidget::toCancel);
}
void GameOverWidget::paintEvent(QPaintEvent *event)
{
    QPainter background(this);
    if(mode == "星空大战")
    background.drawPixmap(rect(),QPixmap(":/image/background3.jpg"));
    if(mode == "漫日天堡")
    background.drawPixmap(rect(),QPixmap(":/image/background001.jpg"));
    if(mode == "海底鬼穴")
    background.drawPixmap(rect(),QPixmap(":/image/background003.jpg"));
    if(mode == "无尽冲刺")
    background.drawPixmap(rect(),QPixmap(":/image/image2.jpg"));
}

void GameOverWidget::showCredit()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
    QString str=QString::number(credit,10);
    creditshow->setText(str+"分");
    creditshow->setFont(QFont("华文行楷",30,100));
    creditshow->setGeometry(300,400,600,100);
    creditshow->setPalette(pe);
}

void GameOverWidget::showMode()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
    modeshow->setText("恭喜您在"+mode+"模式\n             获得");
    modeshow->setFont(QFont("华文行楷",30,100));
    modeshow->setGeometry(100,100,600,300);
    modeshow->setPalette(pe);
}

void GameOverWidget::toGameAgain()
{
    emit gameagain(people,mode);
    this->close();
}

void GameOverWidget::toCancel()
{
    emit gameover();//发送信号到gameWidget
    this->close();
}
