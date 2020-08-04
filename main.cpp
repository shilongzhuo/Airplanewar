#include "loginWidget.h"
#include <QApplication>
#include "myWindow.h"
#include "gameWidget.h"
#include "levelSelection.h"
#include "gameintroduce.h"
#include "gameOverWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow w;
//    GameWidget w;
//    LevelSelection w;
//    GameIntroduce w;
//    GameOverWidget w(1111,"星空大战");
    w.show();

    return a.exec();
}
