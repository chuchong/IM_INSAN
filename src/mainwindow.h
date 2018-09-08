//包含主窗口以及多线程类,两个放在一起因为都要负责场景的切换
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplashScreen>
#include <QDate>
#include <QThread>
#include "scene/SceneManager.h"
#include "Constant.h"
#include "scene/Scene.h"
#include "scene/SceneStory.h"
#include "object/ObjectManager.h"
#include "component/ComponentPaint.h"
namespace Ui {
class MainWindow;
}
//这是为实现多线程准备的类
class LoadingThread : public QThread
{
    Q_OBJECT
public:
    explicit LoadingThread(QObject *parent = 0);
    ~LoadingThread();
signals:
    void sendFinishedScreen(ObjectManager *);
protected:
    virtual void run() Q_DECL_OVERRIDE;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void receiveLoadScreen(ObjectManager *);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeScene(Scene* newScene);

    //TODO 确定场景切换方式 自动机orswitch
    void chooseNewScene(SCENE_NUMBER old_scene, int/*TODO information*/ );//选择新场景,场景切换利用SWITCH大概就够了
     void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    friend class SceneManager;
    Scene* currScene;
    ObjectManager *objManager;
    ComponentPaint *paintComponent;

    LoadingThread loadThread;
};




#endif // MAINWINDOW_H
