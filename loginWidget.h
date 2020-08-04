#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "sourse.h"
#include "levelSelection.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

signals:

private:
    QLineEdit *nameLine;
    QLineEdit *password;
    QPushButton* registered;
    QPushButton* login;
    QMap<QString, QString> contacts;
    LevelSelection* level;

public slots:

    void registeredBtn();
    void loginBtn();
    void registerLine();

};

#endif // LOGINWIDGET_H
