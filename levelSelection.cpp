#include "levelSelection.h"
#include "gameWidget.h"

LevelSelection::LevelSelection(QWidget *parent): QWidget(parent)
{
    level1 = new QPushButton("",this);
    level2 = new QPushButton("",this);
    level3 = new QPushButton("",this);
    level4 = new QPushButton("",this);
    this->resize(800,800);//设置页面大小
    level1->setGeometry(0,0,399,399);//设置按钮位置
    level2->setGeometry(400,0,399,399);
    level3->setGeometry(0,400,399,399);
    level4->setGeometry(400,400,399,399);
    this->setWindowTitle("游戏关卡选择");


    level1->setStyleSheet("QPushButton{border-image:url(:/image/level1.png)}");
    level2->setStyleSheet("QPushButton{border-image:url(:/image/level2.png)}");
    level3->setStyleSheet("QPushButton{border-image:url(:/image/level3.png)}");
    level4->setStyleSheet("QPushButton{border-image:url(:/image/level4.png)}");
    connect(level1,&QPushButton::pressed,this,&LevelSelection::toLevel1);
    connect(level2,&QPushButton::pressed,this,&LevelSelection::toLevel2);
    connect(level3,&QPushButton::pressed,this,&LevelSelection::toLevel3);
    connect(level4,&QPushButton::pressed,this,&LevelSelection::toLevel4);


}
void LevelSelection::paintEvent(QPaintEvent *event)
{

}

void LevelSelection::toLevel1()
{
    QMessageBox* box = new QMessageBox;
    box->setText("请选择游戏模式");
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setButtonText (QMessageBox::Yes,QString("单人模式"));
    box->setButtonText (QMessageBox::No,QString("双人模式"));
    int result=box->exec();
    switch (result)
    {
    case QMessageBox::Yes:
        close();
        people = 1;
        break;
    case QMessageBox::No:
        close();
        people = 2;
        break;
    }
    mode = "漫日天堡";
    game1 = new GameWidget(people,mode);//游戏界面初始化
    connect(game1,&GameWidget::gameOver,
    [=]()
    {
        emit toMainWidget();
    }
    );
    connect(game1,&GameWidget::newGame,this,&LevelSelection::newgame);
    connect(game1,&GameWidget::tokaishi,[=]()
    {
        emit toMainWidget();
    }
    );
    game1->show();
    this->close();
}

void LevelSelection::toLevel2()
{
    QMessageBox* box = new QMessageBox;
    box->setText("请选择游戏模式");
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setButtonText (QMessageBox::Yes,QString("单人模式"));
    box->setButtonText (QMessageBox::No,QString("双人模式"));
    int result=box->exec();
    switch (result)
    {
    case QMessageBox::Yes:
        close();
        people = 1;
        break;
    case QMessageBox::No:
        close();
        people = 2;
        break;
    }
    mode = "星空大战";
    game1 = new GameWidget(people,mode);//游戏界面初始化
    connect(game1,&GameWidget::gameOver,
    [=]()
    {
        emit toMainWidget();
    }
    );
    connect(game1,&GameWidget::newGame,this,&LevelSelection::newgame);
    connect(game1,&GameWidget::tokaishi,[=]()
    {
        emit toMainWidget();
    }
    );
    game1->show();
    this->close();
}

void LevelSelection::toLevel3()
{
    QMessageBox* box = new QMessageBox;
    box->setText("请选择游戏模式");
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setButtonText (QMessageBox::Yes,QString("单人模式"));
    box->setButtonText (QMessageBox::No,QString("双人模式"));
    int result=box->exec();
    switch (result)
    {
    case QMessageBox::Yes:
        close();
        people = 1;
        break;
    case QMessageBox::No:
        close();
        people = 2;
        break;
    }
    mode = "海底鬼穴";
    game1 = new GameWidget(people,mode);//游戏界面初始化
    connect(game1,&GameWidget::gameOver,
    [=]()
    {
        emit toMainWidget();
    }
    );
    connect(game1,&GameWidget::newGame,this,&LevelSelection::newgame);
    connect(game1,&GameWidget::tokaishi,[=]()
    {
        emit toMainWidget();
    }
    );
    game1->show();
    this->close();
}

void LevelSelection::toLevel4()
{
    QMessageBox* box = new QMessageBox;
    box->setText("请选择游戏模式");
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setButtonText (QMessageBox::Yes,QString("单人模式"));
    box->setButtonText (QMessageBox::No,QString("双人模式"));
    int result=box->exec();
    switch (result)
    {
    case QMessageBox::Yes:
        close();
        people = 1;
        break;
    case QMessageBox::No:
        close();
        people = 2;
        break;
    }
    mode = "无尽冲刺";
    game1 = new GameWidget(people,mode);//游戏界面初始化
    connect(game1,&GameWidget::gameOver,
    [=]()
    {
        emit toMainWidget();
    }
    );
    connect(game1,&GameWidget::newGame,this,&LevelSelection::newgame);
    connect(game1,&GameWidget::tokaishi,[=]()
    {
        emit toMainWidget();
    }
    );

    game1->show();
    this->close();
}

void LevelSelection::newgame(int people,QString mode)
{
    game1 = new GameWidget(people,mode);
    connect(game1,&GameWidget::gameOver,
    [=]()
    {
        emit toMainWidget();
    }
    );
    connect(game1,&GameWidget::newGame,this,&LevelSelection::newgame);
    connect(game1,&GameWidget::tokaishi,[=]()
    {
        emit toMainWidget();
    }
    );
    game1->show();

}

LevelSelection::~LevelSelection()
{
//    delete level1;
//    delete level2;
//    delete level3;
//    delete level4;
//    delete level5;
//    delete level6;
}
