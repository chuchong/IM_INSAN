#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDate>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //调皮一下
    QPixmap pixmap(":/BG_WELCOME");      //绑定一个图片
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(pixmap);
    splash->show();

    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
    now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=2);

    w.show();
    splash->finish(&w);
    delete splash;

    return a.exec();
}
