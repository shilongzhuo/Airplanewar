#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include "sourse.h"
#include "airplane.h"
#include "bullet.h"
#include "suply.h"
#include "gameOverWidget.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(int people,QString mode,QWidget *parent = 0);
    ~GameWidget();
private:
    QPainter* painter;
    AirPlane* myPlane;
    AirPlane* anotherPlane;//二号玩家
    Bullet* MyBullet[NUMBER_OF_MYBULLET];
    Bullet* EnemyBullet[NUMBER_OF_ENEMYBULLET];
    AirPlane* enemyPlane[ENEMY_NUMBER];
//    AirPlane* friendPlane[2000];
    Suply* bloodSuply[2000];//加血包
    QTimer* timer;
    QLabel* creditShow;
    QLabel* blood;//血条
    QPushButton* musicButton;//音乐键
    QPushButton* stopButton;//暂停键
    QPushButton* beginButton;//开始界面
    QSound* myPlaneBoom;//敌军爆炸声音
    QSound* enemyPlaneBoom;//我军爆炸声音

    int numberOfMyBullet;
    int numberOfEnemyBullet;
    int numberOfEnemyPlane;
    int numberOfSuply;
    int time1;
    int time2;
    int time3;//计时器ID
    bool up;
    bool down;
    bool left;
    bool right;//p1操纵方式
    bool zero;
    bool w;
    bool s;
    bool a;
    bool d;
    bool kongge;//p2操纵方式
    bool jineng1;
    bool jineng2;
    bool wushuang1;
    bool wushuang2;
    int rand;//飞机类型
    int credits;//获得积分
    bool pause;//决定页面是否静止
    bool music;//声音是否放映
    GameOverWidget* gameoverWidget;//游戏结束画面
    int people;//双人或单人
    QString mode;//模式

signals:
    gameOver();
    newGame(int people,QString mode);
    tokaishi();//去主页面
public slots:
    void paintEvent(QPaintEvent *event);
    void createMyPlane();//创建己方飞机
    void createEnemyPlane();//创建敌方飞机
    void createMyBullet(AirPlane* plane);
    void createEnemyBullet(AirPlane* plane);
    void paintMyBullet();
    void paintEnemyBullet();
    void paintEnemyPlane();
    void paintMyPlane();
    void clearEnemyPlane(int i);//清除敌军飞机
    void clearMyPlane();//清除我军飞机
    void clearEnemyBullet(int i);//清除敌军子弹
    void clearMyBullet(int i);//清除我军子弹
    void clearanotherPlane();//清除我军飞机p2
    void timerUpdate();//计时器溢出处理
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void myPlaneMove();
    void howToShowCredit();
    void musicButtonPressed();//按键处理
    void stopButtonPressed();
    void beginButtonPressed();
    void painterLife();
    void paintPower();
    void paintBloodSuply();
    void creatnewgame(int people,QString mode);
    void showCreditWidget();//游戏结束后显示分数
    void creatBloodSuply();
    void clearBloodSuply(int i);

//    void setBackSounds();//设置背景音乐
//    void setBoomSounds();//设置爆炸音乐

    bool myBulletHitJudge(int i);//判断玩家子弹是否击中敌机
    bool enemyBulletHitJudge(int i);//判断子弹是否击中玩家p1
    bool enemyBulletHitAnotherJudge(int i);//判断子弹是否击中玩家p2
    bool anotherTwoAiplaneMeetJudge(int i);//判断玩家飞机p2与敌机是否相遇
    bool myPlaneGetBloodSuply(int i);//我机p1得到血包
    bool anotherPlaneGetBloodSuply(int i);//我机p2得到血包
    bool twoAiplaneMeetJudge(int i);//判断玩家飞机p1与敌机是否相遇
    void myAiplaneExplodeTimeOutWhether();//玩家飞机p1爆炸云消失倒计时
    void anotherAiplaneExplodeTimeOutWhether();//玩家飞机p2爆炸云消失倒计时
    void enemyAirplaneExplodeTimeOutWhether(int i);//敌机爆炸云消失倒计时

};

#endif // GAMEWIDGET_H
