#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene/SceneManager.h"
#include "Constant.h"
#include "scene/Scene.h"
#include "object/ObjectManager.h"
#include "component/ComponentPaint.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeScene(Scene* newScene)
      {
        if (currScene != nullptr)
          currScene->unload();
        newScene->load();
        currScene = newScene;
      }
    //TODO 确定场景切换方式 自动机orswitch
    void chooseNewScene(SCENE_NUMBER old_scene, int/*TODO information*/ );//选择新场景,场景切换利用SWITCH大概就够了
     void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    friend class SceneManager;
    Scene* currScene;
    ObjectManager *objManager;
    ComponentPaint *paintComponent;

};

#endif // MAINWINDOW_H
