#include "gameWidget.h"

#include <QPainter>
#include "airplane.h"
#include <iostream>
#include <QDebug>
using namespace std;

GameWidget::GameWidget(int people,QString mode,QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    this->setFocus();
//初始化运动状态
    right = false;
    left = false;
    up = false;
    down = false;
    zero = false;
    w = false;
    s = false;
    a = false;
    d = false;
    kongge = false;
    jineng1 = false;
    jineng2 = false;
    wushuang1 = false;
    wushuang2 = false;
    pause = false;//页面不静止

    music = true;
    numberOfMyBullet = 0;
    numberOfEnemyBullet = 0;
    numberOfEnemyPlane = 0;
    numberOfSuply = 0;
    this->people = people;
    this->mode = mode;
    anotherPlane = NULL;
    myPlane = NULL;
    //界面设计开始
    credits = 0;
    creditShow = new QLabel(this);
    creditShow->setFocusPolicy(Qt::NoFocus);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    creditShow->setPalette(pe);
    creditShow->setFont(QFont("FangSong",30,100));//字体设置
    creditShow->setGeometry(0,0,300,40);
    howToShowCredit();
    resize(GAME_WIDTH,GAME_HEIGHT);
    musicButton= new QPushButton(QIcon("musicPress.icon"),"音乐",this);
    musicButton->setFocusPolicy(Qt::NoFocus);
    stopButton = new QPushButton(QIcon("begin.icon"),"暂停",this);
    stopButton->setFocusPolicy(Qt::NoFocus);
    beginButton = new QPushButton(QIcon("Main.icon"),"主页面",this);
    beginButton->setFocusPolicy(Qt::NoFocus);
    musicButton->setGeometry(500,0,80,40);
    stopButton->setGeometry(600,0,80,40);
    beginButton->setGeometry(700,0,80,40);
    QLabel* showLife = new QLabel(this);
    showLife->setText("p1生命值");
    showLife->setPalette(pe);
    showLife->setFont(QFont("FangSong",20,100));
    showLife->setGeometry(0,50,150,80);
    QLabel* showPower = new QLabel(this);
    showPower->setText("p1能量值");
    showPower->setPalette(pe);
    showPower->setFont(QFont("FangSong",20,100));
    showPower->setGeometry(0,130,150,80);
    if(people == 2)
    {
        QLabel* showLife2 = new QLabel(this);
        showLife2->setText("p2生命值");
        showLife2->setPalette(pe);
        showLife2->setFont(QFont("FangSong",20,100));
        showLife2->setGeometry(0,210,150,80);
        QLabel* showPower2 = new QLabel(this);
        showPower2->setText("p2能量值");
        showPower2->setPalette(pe);
        showPower2->setFont(QFont("FangSong",20,100));
        showPower2->setGeometry(0,290,150,80);
    }

    //界面设置结束

    //爆炸声音设置开始
    myPlaneBoom = new QSound(":/image/MyPlaneBoom.wav");
    enemyPlaneBoom = new QSound(":/image/enemyPlaneBoom.wav");
    //声音设置结束
    timer = new QTimer(this);
    timer->start(UPDATE_TIME);
    connect(timer, &QTimer::timeout, this, &GameWidget::timerUpdate);//刷新页面
    connect(musicButton,&QPushButton::pressed,this,&GameWidget::musicButtonPressed);
    connect(stopButton,&QPushButton::pressed,this,GameWidget::stopButtonPressed);
    connect(beginButton,&QPushButton::pressed,this,&GameWidget::beginButtonPressed);
//    connect(gameoverWidget,&GameOverWidget::gameagain,this,&GameWidget::creatnewgame);


    time1=startTimer(TIME1);
    time2=startTimer(TIME2);
    time3=startTimer(TIME3);

    createMyPlane();
}

void GameWidget::paintEvent(QPaintEvent *event)
{

    myPlaneMove();
    painter = new QPainter(this);
    if(mode == "星空大战")
    {
        painter->drawPixmap(rect(),QPixmap(":/image/background.jpg"));
    }
    else if(mode == "漫日天堡")
    {
        painter->drawPixmap(rect(),QPixmap(":/image/background001.jpg"));
    }
    else if(mode == "海底鬼穴")
    {
        painter->drawPixmap(rect(),QPixmap(":/image/background003.jpg"));
    }
    else
    {
        painter->drawPixmap(rect(),QPixmap(":/image/background004.jpg"));
    }
    paintEnemyPlane();
    paintMyPlane();
    paintMyBullet();
    paintEnemyBullet();
    painterLife();
    paintPower();
    paintBloodSuply();



}
void GameWidget::creatBloodSuply()//创建加血包
{
    bloodSuply[numberOfSuply] = new Suply();
    bloodSuply[numberOfSuply]->setX(qrand()%GAME_WIDTH);
    bloodSuply[numberOfSuply]->setY(qrand()%GAME_HEIGHT);
    numberOfSuply++;
}
void GameWidget::paintBloodSuply()//绘制血包
{
    for(int i = 0; i < numberOfSuply;i++)
    {

        if(bloodSuply[i])
        {
            QPainter paint(this);
            paint.drawPixmap(bloodSuply[i]->getX(),bloodSuply[i]->getY(),
            bloodSuply[i]->getWidth(), bloodSuply[i]->getHeight(),bloodSuply[i]->getSuplyPath());
        }
    }
}

void GameWidget::createMyPlane()//创建己方飞机
{
    if(people == 1)
    {
        myPlane = new AirPlane(1,true);
        myPlane->setLife(10);
    }
    if(people == 2)
    {
        myPlane = new AirPlane(1,true);
        myPlane->setLife(10);
        if(mode == "漫日天堡")
        {
           myPlane->setPlanePath(QPixmap(":/image/hero1.png"));
        }
        if(mode == "海底鬼穴")
        {
            myPlane->setPlanePath(QPixmap(":/image/hero1.png"));
        }
        if(mode == "无尽冲刺")
        {

        }
        anotherPlane = new AirPlane(1,true);
        anotherPlane->setLife(10);
        anotherPlane->setPlanePath(QPixmap(":/image/myplane.png"));
        if(mode == "海底鬼穴")
        {
            anotherPlane->setPlanePath(QPixmap(":/image/hero2.png"));
        }
        if(mode == "海底鬼穴")
        {
             anotherPlane->setPlanePath(QPixmap(":/image/hero2.png"));
        }
        if(mode == "无尽冲刺")
        {

        }
    }
}

void GameWidget::createEnemyPlane()//创建敌方飞机
{
    enemyPlane[numberOfEnemyPlane] = new AirPlane(1,true);
    if(qrand()%3 == 0)
    {
        enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(ENEMY_AIRPLANE5_PATH ));
        enemyPlane[numberOfEnemyPlane]->setLife(3);
        enemyPlane[numberOfEnemyPlane]->setWidth(ENEMY_AIRPLANE_WIDTH * 3);
        enemyPlane[numberOfEnemyPlane]->setHeight(ENEMY_AIRPLANE_HEIGHT);


        if(mode == "漫日天堡")
        {
              enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/Boos1.png"));
              enemyPlane[numberOfEnemyPlane]->setWidth(ENEMY_AIRPLANE_WIDTH * 3);
              enemyPlane[numberOfEnemyPlane]->setHeight(ENEMY_AIRPLANE_HEIGHT*2);
        }
        if(mode == "海底鬼穴")
        {
            enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/Boos2 .png"));
            enemyPlane[numberOfEnemyPlane]->setWidth(ENEMY_AIRPLANE_WIDTH * 3);
            enemyPlane[numberOfEnemyPlane]->setHeight(ENEMY_AIRPLANE_HEIGHT*3);

        }
        if(mode == "无尽冲刺")
        {
            enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/enemy007.png"));
        }
        enemyPlane[numberOfEnemyPlane]->setXpos(qrand() % (GAME_WIDTH - enemyPlane[numberOfEnemyPlane]->getWidth()));

    }
    else
    {
        enemyPlane[numberOfEnemyPlane]->setXpos(qrand() % (GAME_WIDTH - enemyPlane[numberOfEnemyPlane]->getWidth()));
        enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(ENEMY_AIRPLANE1_PATH));
        enemyPlane[numberOfEnemyPlane]->setLife(1);

        if(mode == "漫日天堡")
        {
            enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/enemy006.png"));
        }
        if(mode == "海底鬼穴")
        {
            enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/enemy003.png"));
        }
        if(mode == "无尽冲刺")
        {
            enemyPlane[numberOfEnemyPlane]->setPlanePath(QPixmap(":/image/enemy005.png"));
        }
    }
    enemyPlane[numberOfEnemyPlane]->setYpos(0);
    enemyPlane[numberOfEnemyPlane]->setSpeed(qrand() % 4 + 1);
    numberOfEnemyPlane++;
}
void GameWidget::paintEnemyPlane()//绘制敌方飞机
{
    for(int i =0;i < numberOfEnemyPlane;i++)
    {
        if(enemyPlane[i])
        {
            if(enemyPlane[i]->getLife()>0)
            {
                enemyPlane[i]->setPlanePath(enemyPlane[i]->getPlanePath());
            }
            painter->drawPixmap(enemyPlane[i]->getXpos(),enemyPlane[i]->getYpos(),
            enemyPlane[i]->getWidth(), enemyPlane[i]->getHeight(),enemyPlane[i]->getPlanePath());
            enemyPlane[i]->move(0,enemyPlane[i]->getSpeed());
            if(twoAiplaneMeetJudge(i))
            {
                myPlane->subLife(enemyPlane[i]->getLife());
                enemyPlane[i]->subLife(enemyPlane[i]->getLife());
            }
            if(anotherTwoAiplaneMeetJudge(i))
            {
                anotherPlane->subLife(enemyPlane[i]->getLife());
                enemyPlane[i]->subLife(enemyPlane[i]->getLife());
            }
            if(enemyPlane[i]->getLife() <= 0)
            {
                if(!enemyPlane[i]->is_boom_sound&&music)
                {
                    enemyPlaneBoom->play();
                    enemyPlane[i]->is_boom_sound = true;
                }
                enemyPlane[i]->setSpeed(0);//设置爆炸图案静止
                enemyAirplaneExplodeTimeOutWhether(i);//爆炸时间结束，清理图案
            }
        }

    }

}
void GameWidget::paintMyPlane()//绘制我方飞机
{
    if(people == 1)
    {
        if(myPlane)
        {
            painter->drawPixmap(myPlane->getXpos(),myPlane->getYpos(),
            myPlane->getWidth(),myPlane->getHeight(),myPlane->getPlanePath());
            if(myPlane->getLife() <= 0)
            {
                myPlane->setSpeed(0);
                myAiplaneExplodeTimeOutWhether();
                if(myPlane)
                {
                    if(!myPlane->is_boom_sound&&music)
                    {
                        myPlaneBoom->play();
                        myPlane->is_boom_sound = true;
                    }
                }
            }
            for(int i = 0;i<numberOfSuply;i++)
            {
                if(myPlaneGetBloodSuply(i))
                {
                    if(myPlane->getLife()+BLOOD_SUPLY >= MyPlane_Life)
                    {
                        myPlane->setLife(MyPlane_Life);
                    }
                    else
                    {
                         myPlane->addLife(BLOOD_SUPLY);
                    }
                }
            }
        }
    }
    if(people == 2)
    {
        if(myPlane)
        {
            painter->drawPixmap(myPlane->getXpos(),myPlane->getYpos(),
            myPlane->getWidth(),myPlane->getHeight(),myPlane->getPlanePath());
            if(myPlane->getLife() <= 0)
            {
                myPlane->setSpeed(0);
                myAiplaneExplodeTimeOutWhether();
                if(myPlane)
                {
                    if(!myPlane->is_boom_sound&&music)
                    {
                        myPlaneBoom->play();
                        myPlane->is_boom_sound = true;
                    }
                }
            }
            for(int i = 0;i<numberOfSuply;i++)
            {
                if(myPlaneGetBloodSuply(i))
                {
                    if(myPlane->getLife()+BLOOD_SUPLY >= MyPlane_Life)
                    {
                        myPlane->setLife(MyPlane_Life);
                    }
                    else
                    {
                         myPlane->addLife(BLOOD_SUPLY);
                    }
                }
            }
        }
        if(anotherPlane)
        {
            painter->drawPixmap(anotherPlane->getXpos(),anotherPlane->getYpos(),
            anotherPlane->getWidth(),anotherPlane->getHeight(),anotherPlane->getPlanePath());
            if(anotherPlane->getLife() <= 0)
            {
                anotherPlane->setSpeed(0);
                anotherAiplaneExplodeTimeOutWhether();
                if(anotherPlane)
                {
                    if(!anotherPlane->is_boom_sound&&music)
                    {
                        myPlaneBoom->play();
                        myPlane->is_boom_sound = true;
                    }
                }
            }
            for(int i = 0;i<numberOfSuply;i++)
            {
                if(anotherPlaneGetBloodSuply(i))
                {
                    if(anotherPlane->getLife()+BLOOD_SUPLY >= MyPlane_Life)
                    {
                        anotherPlane->setLife(MyPlane_Life);
                    }
                    else
                    {
                         anotherPlane->addLife(BLOOD_SUPLY);
                    }
                }
            }
        }
    }

}

void GameWidget::paintMyBullet()//绘制我方子弹
{
    for(int i=0;i < numberOfMyBullet;i++)
    {
        if(MyBullet[i]!=NULL)
         {
            painter->drawPixmap(MyBullet[i]->getX(),MyBullet[i]->getY(),
            MyBullet[i]->getWidth(),MyBullet[i]->getHeight(),MyBullet[i]->getBulletPath());
            MyBullet[i]->move(0,-MyBullet[i]->getSpeed());

            if(myBulletHitJudge(i)||MyBullet[i]->getY() < -MyBullet[i]->getHeight())
            {
                clearMyBullet(i);
            }
         }
     }
}
void GameWidget::paintEnemyBullet()//绘制敌方子弹
{
    for(int i = 0;i < numberOfEnemyBullet;i++)
    {
        if(EnemyBullet[i]!=NULL)
        {
            painter->drawPixmap(EnemyBullet[i]->getX(),EnemyBullet[i]->getY(),
            EnemyBullet[i]->getWidth(),EnemyBullet[i]->getHeight(),EnemyBullet[i]->getBulletPath());

            EnemyBullet[i]->move(0,EnemyBullet[i]->getSpeed());
            if(enemyBulletHitJudge(i)||EnemyBullet[i]->getY() > GAME_HEIGHT||enemyBulletHitAnotherJudge(i))
            {
                clearEnemyBullet(i);
            }

        }
    }
}

void GameWidget::createEnemyBullet(AirPlane* plane)
{
    if(plane->getLife() == 3)
    {
         EnemyBullet[numberOfEnemyBullet]=new Bullet(plane->getXpos()+ plane->getWidth()/2,plane->getYpos()+ plane->getHeight()/2,1,true);
//        EnemyBullet[numberOfEnemyBullet]->setSpeed( EnemyBullet[numberOfEnemyBullet]->getSpeed());
         EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(ENEMY_BULLET2_PATH ));
         EnemyBullet[numberOfEnemyBullet]->setWidth(5);
         EnemyBullet[numberOfEnemyBullet]->setHeight(50);
          if(mode == "漫日天堡")
          {
             EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
          }
          if(mode == "海底鬼穴")
          {
             EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
          }
          if(mode == "无尽冲刺")
          {
            EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
          }
    }
    else
    {
        EnemyBullet[numberOfEnemyBullet]=new Bullet(plane->getXpos()+ plane->getWidth()/2,plane->getYpos()+ plane->getHeight()/2,1,true);
//        EnemyBullet[numberOfEnemyBullet]->setSpeed( EnemyBullet[numberOfEnemyBullet]->getSpeed());
                 if(mode == "漫日天堡")
                 {
                    EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
                 }
                 if(mode == "海底鬼穴")
                 {
                    EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
                 }
                 if(mode == "无尽冲刺")
                 {
                   EnemyBullet[numberOfEnemyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
                 }
    }
    numberOfEnemyBullet++;//计数
}
void GameWidget::createMyBullet(AirPlane* plane)
{
    MyBullet[numberOfMyBullet]=new Bullet(plane->getXpos()+plane->getWidth()/2,plane->getYpos(),1,true);
    MyBullet[numberOfMyBullet]->setSpeed(20);
    MyBullet[numberOfMyBullet]->setBulletPath(QPixmap(MY_BULLET4_PATH));
    if(mode == "漫日天堡")
    {
        MyBullet[numberOfMyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
         MyBullet[numberOfMyBullet]->setWidth(10);
         MyBullet[numberOfMyBullet]->setHeight(40);
    }
    if(mode == "海底鬼穴")
    {
        MyBullet[numberOfMyBullet]->setBulletPath(QPixmap(":/image/Mybullet006.png"));
        MyBullet[numberOfMyBullet]->setWidth(10);
        MyBullet[numberOfMyBullet]->setHeight(40);
    }
    if(mode == "无尽冲刺")
    {
      MyBullet[numberOfMyBullet]->setBulletPath(QPixmap(":/image/mybullet.png"));
      MyBullet[numberOfMyBullet]->setWidth(10);
      MyBullet[numberOfMyBullet]->setHeight(30);
    }
    numberOfMyBullet++;
}

void GameWidget::clearEnemyPlane(int i)//清除敌军飞机
{
    enemyPlane[i]->~AirPlane();
//    delete enemyPlane[i];
    enemyPlane[i]=NULL;
}

void GameWidget::clearMyPlane()//清除我军飞机p1
{
    myPlane->~AirPlane();
//    delete myPlane;
    myPlane = NULL;
}

void  GameWidget::clearanotherPlane()//清除我军飞机p2
{
    anotherPlane->~AirPlane();
//    delete anotherPlane;
    anotherPlane = NULL;
}

void GameWidget::clearEnemyBullet(int i)//清除敌军子弹
{
    EnemyBullet[i]->~Bullet();
//    delete EnemyBullet[i];
    EnemyBullet[i] = NULL;
}

void GameWidget::clearMyBullet(int i)//清除我军子弹
{
    MyBullet[i]->~Bullet();
//    delete MyBullet[i];
    MyBullet[i]=NULL;
}
void  GameWidget::clearBloodSuply(int i)//清除回血包
{
//    delete bloodSuply[i];
    bloodSuply[i] = NULL;
}

void GameWidget::timerUpdate()
{


//    for(int i =0;i < numberOfMyBullet;i++)
//    {
//        if(MyBullet[i])
//        MyBullet[i]->move(0,-2);
//    }
//    for(int i =0;i < numberOfEnemyBullet;i++)
//    {
//        if(EnemyBullet[i])
//        EnemyBullet[i]->move(0,2);
//    }
    if(!pause)
    update();
}
void GameWidget::timerEvent(QTimerEvent* event)//创建敌机和敌机子弹和加血包
{
    if(!pause&&event->timerId()==time1)
    {
        createEnemyPlane();
    }
    if(!pause&&event->timerId()==time2)
    {
        for(int i = 0;i < numberOfEnemyPlane;i++)
        if(enemyPlane[i]&&enemyPlane[i]->getLife()>0)
        {
            createEnemyBullet(enemyPlane[i]);
        }
    }
    if(!pause&&event->timerId()==time3)
    {
        creatBloodSuply();
        if(numberOfSuply > 1);
        clearBloodSuply(numberOfSuply-2);
    }
    if(time1>100&&time2>100)
    {
        time1 = time1 - credits/2;
        time2 = time2 - credits/2;
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)//英雄飞机移动问题
{
    if(pause)
    {
        return;
    }
    if(event->key()==Qt::Key_Left)
    {
       left = true;
    }
    if(event->key()==Qt::Key_Right)
    {
       right = true;
    }
    if(event->key()==Qt::Key_Up)
    {
       up = true;
    }
    if(event->key()==Qt::Key_Down)
    {
       down = true;
    }
    if(event->key()==Qt::Key_1)
    {
        zero = true;
    }
    if(event->key()==Qt::Key_5)
    {
        jineng1 = true;
    }
    if(event->key()==Qt::Key_0)
    {
        wushuang1 = true;
    }
    if(event->key()==Qt::Key_A)
    {
       a = true;
    }
    if(event->key()==Qt::Key_D)
    {
       d = true;
    }
    if(event->key()==Qt::Key_W)
    {
       w = true;
    }
    if(event->key()==Qt::Key_S)
    {
       s = true;
    }
    if(event->key()==Qt::Key_J)
    {
        kongge = true;
    }
    if(event->key()==Qt::Key_O)
    {
        jineng2 = true;
    }
    if(event->key()==Qt::Key_Space)
    {
        wushuang2 = true;
    }

}
void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left)
    {
       left = false;
    }
    if(event->key()==Qt::Key_Right)
    {
       right = false;
    }
    if(event->key()==Qt::Key_Up)
    {
       up = false;
    }
    if(event->key()==Qt::Key_Down)
    {
       down = false;
    }
    if(event->key()==Qt::Key_1)
    {
        zero = false; //发射子弹
    }
    if(event->key()==Qt::Key_5)
    {
        jineng1 = false;
    }
    if(event->key()==Qt::Key_0)
    {
        wushuang1 = false;
    }
    if(event->key()==Qt::Key_A)
    {
       a = false;
    }
    if(event->key()==Qt::Key_D)
    {
       d = false;
    }
    if(event->key()==Qt::Key_W)
    {
       w = false;
    }
    if(event->key()==Qt::Key_S)
    {
       s = false;
    }
    if(event->key()==Qt::Key_J)
    {
        kongge = false;
    }
    if(event->key()==Qt::Key_O)
    {
        jineng2 = false;
    }
    if(event->key()==Qt::Key_Space)
    {
        wushuang2 = false;
    }
}

void GameWidget::myPlaneMove()
{
    if(myPlane)
    {
        if(zero)
        {
            createMyBullet(myPlane);
    //      paintMyBullet();
        }
        if(jineng1)
        {
            if(myPlane->getPower()>=2)
            {
                for(int i=0; i<numberOfEnemyBullet;i++)
                {
                    if(EnemyBullet[i])
                    clearEnemyBullet(i);
                }
                myPlane->setPower(myPlane->getPower()-2);
            }
        }
        if(wushuang1)
        {

        }
        if((up&&down&&left&&!right)||(!up&&!down&&left&&!right))//向左移动
        {
            myPlane->heroMove(-myPlane->getSpeed(),0);
        }
        else if((up&&down&&!left&&right)||(!up&&!down&&!left&&right))//向右移动
        {
             myPlane->heroMove(myPlane->getSpeed(),0);
        }
        else if((up&&!down&&left&&right)||(up&&!down&&!left&&!right))//向上移动
        {
            myPlane->heroMove(0,-myPlane->getSpeed());
        }
        else if(up&&!down&&left&&!right)//向左上移动
        {
            myPlane->heroMove(-0.5*myPlane->getSpeed(),-0.5*myPlane->getSpeed());
        }
        else if(up&&!down&&!left&&right)//向右上移动
        {
            myPlane->heroMove(0.5*myPlane->getSpeed(),-0.5*myPlane->getSpeed());
        }
        else if ((!up&&down&&left&&right)||(!up&&down&&!left&&!right))//向下移动
        {
            myPlane->heroMove(0,myPlane->getSpeed());
        }
        else if(!up&&down&&left&&!right)//向左下移动
        {
            myPlane->heroMove(-myPlane->getSpeed(),myPlane->getSpeed());
        }
        else if(!up&&down&&!left&&right)//向右下移动
        {
            myPlane->heroMove(myPlane->getSpeed(),myPlane->getSpeed());
        }
    }
    if(anotherPlane)
    {
        if(kongge)
        {
            createMyBullet(anotherPlane);
    //      paintMyBullet();
        }
        if(jineng2)
        {
            if(anotherPlane->getPower()>=2)
            {
                for(int i=0; i<numberOfEnemyBullet;i++)
                {
                    if(EnemyBullet[i])
                    clearEnemyBullet(i);
                }
                anotherPlane->setPower(anotherPlane->getPower()-2);
            }
        }
        if(wushuang2)
        {

        }
        if((w&&s&&a&&!d)||(!w&&!s&&a&&!d))//向左移动
        {
            anotherPlane->heroMove(-anotherPlane->getSpeed(),0);
        }
        else if((w&&s&&!a&&d)||(!w&&!s&&!a&&d))//向右移动
        {
             anotherPlane->heroMove(anotherPlane->getSpeed(),0);
        }
        else if((w&&!s&&a&&d)||(w&&!s&&!a&&!d))//向上移动
        {
            anotherPlane->heroMove(0,-myPlane->getSpeed());
        }
        else if(w&&!s&&a&&!d)//向左上移动
        {
            anotherPlane->heroMove(-0.5*anotherPlane->getSpeed(),-0.5*anotherPlane->getSpeed());
        }
        else if(w&&!s&&!a&&d)//向右上移动
        {
            anotherPlane->heroMove(0.5*anotherPlane->getSpeed(),-0.5*anotherPlane->getSpeed());
        }
        else if ((!w&&s&&a&&d)||(!w&&s&&!a&&!d))//向下移动
        {
            anotherPlane->heroMove(0,anotherPlane->getSpeed());
        }
        else if(!w&&s&&a&&!d)//向左下移动
        {
            anotherPlane->heroMove(-anotherPlane->getSpeed(),anotherPlane->getSpeed());
        }
        else if(!w&&s&&!a&&d)//向右下移动
        {
            anotherPlane->heroMove(anotherPlane->getSpeed(),anotherPlane->getSpeed());
        }
    }
}

bool GameWidget::myBulletHitJudge(int i)//处在矩形框内，子弹命中敌机
{
    for(int j=0;j < numberOfEnemyPlane;j++)
    {
        if(enemyPlane[j]!=NULL&&enemyPlane[j]->getLife()>0
        &&MyBullet[i]->getX()<=enemyPlane[j]->getXpos()+enemyPlane[j]->getWidth()
        &&MyBullet[i]->getX()+MyBullet[i]->getWidth()>enemyPlane[j]->getXpos()
        &&MyBullet[i]->getY()<=enemyPlane[j]->getYpos()+enemyPlane[j]->getHeight()
        &&MyBullet[i]->getY()+MyBullet[i]->getHeight()>=enemyPlane[j]->getYpos())
        {
            if(enemyPlane[j]->getLife()<=1)
            {
                credits+=10;
                howToShowCredit();
            }
            enemyPlane[j]->subLife(1);
            return true;
        }
    }
    return false;
}

bool GameWidget::enemyBulletHitJudge(int i)//敌机子弹击中我p1机
{
    if(myPlane)
    {
        if(EnemyBullet[i]!=NULL && myPlane->getXpos()<EnemyBullet[i]->getX()+EnemyBullet[i]->getWidth()
        &&myPlane->getXpos()+myPlane->getWidth()>=EnemyBullet[i]->getX()
        &&EnemyBullet[i]->getY() + EnemyBullet[i]->getHeight()>myPlane->getYpos()
        &&EnemyBullet[i]->getY() < myPlane->getYpos()+myPlane->getHeight()&&myPlane->getLife()>0)
        {

            myPlane->subLife(EnemyBullet[i]->getPower());
            return true;
        } 
    }
    return false;
}
bool GameWidget::enemyBulletHitAnotherJudge(int i)//判断子弹是否击中玩家p2
{
    if(anotherPlane)
    {

        if(EnemyBullet[i]!=NULL && anotherPlane->getXpos()<EnemyBullet[i]->getX()+EnemyBullet[i]->getWidth()
        &&anotherPlane->getXpos()+anotherPlane->getWidth()>=EnemyBullet[i]->getX()
        &&EnemyBullet[i]->getY() + EnemyBullet[i]->getHeight()>anotherPlane->getYpos()
        &&EnemyBullet[i]->getY() < anotherPlane->getYpos()+anotherPlane->getHeight()&&anotherPlane->getLife()>0)
        {
            anotherPlane->subLife(EnemyBullet[i]->getPower());
            return true;
        }

    }
    return false;
}

bool GameWidget::anotherTwoAiplaneMeetJudge(int i)//判断玩家飞机p2与敌机是否相遇
{
    if(anotherPlane&&enemyPlane[i])
    {
        if(anotherPlane->getXpos() < enemyPlane[i]->getXpos()+enemyPlane[i]->getWidth()
           &&anotherPlane->getXpos()+anotherPlane->getWidth() > enemyPlane[i]->getXpos()
           &&anotherPlane->getYpos() < enemyPlane[i]->getYpos()+enemyPlane[i]->getHeight()
           &&anotherPlane->getYpos()+anotherPlane->getHeight() > enemyPlane[i]->getYpos()
                &&anotherPlane->getLife()>0&&enemyPlane[i]->getLife()>0)
        {
            return true;

        }

    }
    return false;
}

bool GameWidget::twoAiplaneMeetJudge(int i)//我机p1与敌机相撞
{
    if(myPlane&&enemyPlane[i])
    {
        if(myPlane->getXpos() < enemyPlane[i]->getXpos()+enemyPlane[i]->getWidth()
           &&myPlane->getXpos()+myPlane->getWidth() > enemyPlane[i]->getXpos()
           &&myPlane->getYpos() < enemyPlane[i]->getYpos()+enemyPlane[i]->getHeight()
           &&myPlane->getYpos()+myPlane->getHeight() > enemyPlane[i]->getYpos()
                &&myPlane->getLife()>0&&enemyPlane[i]->getLife()>0)
        {
            return true;
        }
    }
    return false;
}
bool GameWidget::myPlaneGetBloodSuply(int i)//p1得到血包
{
    if(myPlane&&bloodSuply[i])
    {
        if(myPlane->getXpos() < bloodSuply[i]->getX()+bloodSuply[i]->getWidth()
           &&myPlane->getXpos()+myPlane->getWidth() >bloodSuply[i]->getX()
           &&myPlane->getYpos() <bloodSuply[i]->getY() +bloodSuply[i]->getHeight()
           &&myPlane->getYpos() + myPlane->getHeight() > bloodSuply[i]->getY()
                &&myPlane->getLife()>0)
        {
            clearBloodSuply(i);
            return true;
        }

    }
    return false;
}
bool GameWidget::anotherPlaneGetBloodSuply(int i)//p2得到血包
{
    if(anotherPlane&&bloodSuply[i])
    {
        if(anotherPlane->getXpos() < bloodSuply[i]->getX()+bloodSuply[i]->getWidth()
           &&anotherPlane->getXpos()+anotherPlane->getWidth() >bloodSuply[i]->getX()
           &&anotherPlane->getYpos() <bloodSuply[i]->getY() +bloodSuply[i]->getHeight()
           &&anotherPlane->getYpos() + anotherPlane->getHeight() > bloodSuply[i]->getY()
                &&anotherPlane->getLife()>0)
        {
            clearBloodSuply(i);
            return true;
        }
    }
    return false;
}
void GameWidget::myAiplaneExplodeTimeOutWhether()//玩家p1飞机战死
{

    myPlane->exploreTime = myPlane->exploreTime - UPDATE_TIME;
    if(myPlane->exploreTime <= 0)
    {
        clearMyPlane();
        if(!myPlane&&!anotherPlane)
           showCreditWidget();
    }
}
void GameWidget::anotherAiplaneExplodeTimeOutWhether()//玩家p2飞机战死
{

    anotherPlane->exploreTime = anotherPlane->exploreTime - UPDATE_TIME;
    if(anotherPlane->exploreTime <= 0)
    {
        clearanotherPlane();
        if(!myPlane&&!anotherPlane)
           showCreditWidget();
    }
}
void GameWidget::painterLife()//血条绘制
{
    if(myPlane)
    {
        QPainter painter(this);
        QPen pen(Qt::red,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QBrush brush(Qt::red,Qt::SolidPattern);


        painter.setPen(pen);
        painter.drawRect(QRect(160,80,MyPlane_Life*20,20));
        painter.setBrush(brush);
        painter.drawRect(QRect(160,80,myPlane->getLife()*20,20));
    }
    if(anotherPlane)
    {
        QPainter painter(this);
        QPen pen(Qt::red,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QBrush brush(Qt::red,Qt::SolidPattern);


        painter.setPen(pen);
        painter.drawRect(QRect(160,240,MyPlane_Life*20,20));
        painter.setBrush(brush);
        painter.drawRect(QRect(160,240,anotherPlane->getLife()*20,20));
    }
}
void  GameWidget::paintPower()//能量条绘制
{
    if(people == 1)
    {
        if(myPlane)
         {
            QPainter painter(this);
            QPen pen(Qt::green,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
            QBrush brush(Qt::green,Qt::SolidPattern);


            painter.setPen(pen);
            painter.drawRect(QRect(160,160,MyPlane_Power*20,20));
            painter.setBrush(brush);
            painter.drawRect(QRect(160,160,myPlane->getPower()*20,20));
        }
    }
    if(people == 2)
     {
        if(myPlane)
         {
            QPainter painter(this);
            QPen pen(Qt::green,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
            QBrush brush(Qt::green,Qt::SolidPattern);


            painter.setPen(pen);
            painter.drawRect(QRect(160,160,MyPlane_Power*20,20));
            painter.setBrush(brush);
            painter.drawRect(QRect(160,160,myPlane->getPower()*20,20));
        }
        if(anotherPlane)
        {
            QPainter painter(this);
            QPen pen(Qt::green,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
            QBrush brush(Qt::green,Qt::SolidPattern);


            painter.setPen(pen);
            painter.drawRect(QRect(160,320,MyPlane_Power*20,20));
            painter.setBrush(brush);
            painter.drawRect(QRect(160,320,anotherPlane->getPower()*20,20));
        }
    }
}

void GameWidget::enemyAirplaneExplodeTimeOutWhether(int i)//敌机爆炸图案显示时间到
{
    enemyPlane[i]->exploreTime = enemyPlane[i]->exploreTime - UPDATE_TIME;
    if(enemyPlane[i]->exploreTime <= 0)
    {
        clearEnemyPlane(i);
    }
}
void GameWidget::howToShowCredit()//显示分数
{
    QString str=QString::number(credits,10);
    creditShow->setText(str);
}
//按键处理开始
void GameWidget::musicButtonPressed()//音乐键被按下
{
    if(music)
        {
            music=false;
            musicButton->setIcon(QIcon(":/Images/stopMusic.png"));
            musicButton->setText(tr("静音"));
//            groundBack->pause();
        }
        else
        {
            music=true;
            musicButton->setIcon(QIcon(":/Images/music.png"));
            musicButton->setText(tr("音乐"));
            myPlaneBoom->stop();
            enemyPlaneBoom->stop();
//            groundBack->play();
        }

}

void GameWidget::stopButtonPressed()//暂停键被按下
{
    if(pause)
    {
        pause = false;
    }
    else
    {
        pause = true;
    }
}

void GameWidget::beginButtonPressed()//开始键被按下
{
    emit tokaishi();
    pause = true;
    this->close();
}

//按键处理结束
void GameWidget::showCreditWidget()
{
    gameoverWidget = new GameOverWidget(credits,mode,people);
    gameoverWidget->show();
    connect(gameoverWidget,&GameOverWidget::gameover,[=]()
    {
       emit gameOver();//发送信号到levelSelection
    }
    );
    connect(gameoverWidget,&GameOverWidget::gameagain,this,&GameWidget::creatnewgame);
    pause = true;
    this->close();
}

void GameWidget::creatnewgame(int people,QString mode)
{
   emit newGame(people,mode);
}

GameWidget::~GameWidget()
{

}
