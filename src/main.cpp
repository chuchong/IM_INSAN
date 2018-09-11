#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDate>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //调皮一下
    QPixmap pixmap(":/BG_WELCOME");      //绑定一个图片
    QSplashScreen splash;
    splash.setPixmap(pixmap);
    splash.show();

    MainWindow *w = new MainWindow;
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
    now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=1);

    w->show();
    splash.finish(w);

    return a.exec();
}
