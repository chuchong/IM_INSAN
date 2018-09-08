#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDate>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


//    QPixmap pixmap(":/BG_DEBUG");      //绑定一个图片
//    QSplashScreen *splash=new QSplashScreen;
//    splash->setPixmap(pixmap);
//    splash->show();

//    QDateTime n=QDateTime::currentDateTime();
//    QDateTime now;
//    do{
//    now=QDateTime::currentDateTime();
//    } while (n.secsTo(now)<=6);

    w.show();
//    splash->finish(&w);
//    delete splash;

    return a.exec();
}
