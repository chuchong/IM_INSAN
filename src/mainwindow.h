//包含主窗口以及多线程类,两个放在一起因为都要负责场景的切换
//TODO: 还不确定是否结束次线程!!
//Q: 为什么将currScene传入子线程中
//A: 因为若currScene自己转入自己时,其先unload后load顺序不能改变!
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
#include "scene/SceneStart.h"
#include "scene/SceneBattle.h"
#include "scene/SceneSelect.h"
#include "scene/SceneMachine.h"
#include "component/ComponentPaint.h"
namespace Ui {
class MainWindow;
}
//这是为实现多线程准备的类
class LoadingThread : public QThread
{
    Q_OBJECT
private:
    bool changed = 0;
    Scene *sceneFromMain;
    S_CONDITIONS conditions;
    SceneMachine *machine;
public:
    explicit LoadingThread(QObject *parent = 0);
    void setCondition(S_CONDITIONS);
    void setMachine(SceneMachine * m);
    void setScene(Scene *);
    ~LoadingThread();
signals:
    void sendFinishedScreen(Scene *);
protected:
    virtual void run() Q_DECL_OVERRIDE;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void receiveLoadScreen(Scene *);
    void handleConditions(S_CONDITIONS conditions);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeScene(Scene* newScene);

    //TODO 确定场景切换方式 自动机orswitch
     void chooseNewScene(SCENE_ID old_scene, int/*TODO information*/ );//选择新场景,场景切换利用SWITCH大概就够了
     void paintEvent(QPaintEvent *event);
     void start();
private:
    static SceneStory* loadingScene;
    Ui::MainWindow *ui;
    friend class SceneManager;
    SceneMachine *machine;
    Scene* currScene = nullptr;
    ComponentPaint *paintComponent;

    LoadingThread* loadThread = nullptr;
};




#endif // MAINWINDOW_H
