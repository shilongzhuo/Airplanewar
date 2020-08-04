#ifndef SOURSE_H
#define SOURSE_H
#define GAME_WIDTH 1000
#define GAME_HEIGHT 800
#define MY_AIRPLANE_WIDTH 80
#define MY_AIRPLANE_HEIGHT 80
#define ENEMY_AIRPLANE_WIDTH 50
#define ENEMY_AIRPLANE_HEIGHT 50
#define MY_BULLET_WIDTH 10
#define MY_BULLET_HEIGHT 10
#define ENEMY_BULLET_WIDTH 10
#define ENEMY_BULLET_HEIGHT 10
#define ENEMY_NUMBER 1000
#define BLOOD_SUPLY 2 //回血值
#define UPDATE_TIME 50
#define NUMBER_OF_MYBULLET 20000
#define NUMBER_OF_ENEMYBULLET 20000
#define ENEMY_AIRPLANE_SPEED 4  //敌机速度
#define ENEMY_BULLET_SPEED 10 //敌机子弹速度
#define TIME1 1500
#define TIME2 1500
#define TIME3 20000
#define SECOND 1000
#define MyPlane_Life 10  //定义飞机生命值
#define MyPlane_Power 10 //定义飞机能量值
#define MY_AIRPLANE1_PATH ":/image/myplane.png"
#define MY_AIRPLANE2_PATH ":/image/myplane1.png"
#define ENEMY_AIRPLANE1_PATH ":/image/enemyplane001.png"
#define ENEMY_AIRPLANE2_PATH ":/image/enemy002.png"
#define ENEMY_AIRPLANE3_PATH ":/image/enemy003.png"
#define ENEMY_AIRPLANE4_PATH ":/image/enemy004 .png"
#define ENEMY_AIRPLANE5_PATH ":/image/enemyplane003.png"
#define ENEMY_BULLET1_PATH ":/image/bullet002.png"
#define ENEMY_BULLET2_PATH ":/image/enemybullet006.png"
#define MY_BULLET2_PATH ":/image/bossbullet.png"
#define MY_BULLET4_PATH ":/image/bullet004.png"
#define ENEMY_BULLET5_PATH ":/image/enemybullet005.png"
#define PLANE_EXPLODE ":/image/BOOM1.jpg"


#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QPen>
#include <QSound>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QMediaPlayer>
#include <QLayout>
#include <QLineEdit>
#include <QTimer>
#include <QTimerEvent>
#include <QKeyEvent>
#include <iostream>
#include <QPalette>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace std;



class Sourse
{
public:
   static QSqlDatabase db ;
   static bool createConnection();//打开数据库并连接

};

#endif // SOURSE_H
