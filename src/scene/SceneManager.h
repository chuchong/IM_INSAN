//写到一半我发现这个manager单例没啥用处,可以全权让mainwindow代替他.
//#ifndef SCENEMANAGER_H
//#define SCENEMANAGER_H

//#include <QObject>
//#include "../Constant.h"
//#include "Scene.h"
//#include "../object/ObjectManager.h"
//#include "../component/ComponentPaint.h"
//class SceneManager
//{
//private:
//    static SceneManager *instance;
//    Scene* currScene;
//    ObjectManager *objManager;
//    ComponentPaint *paintComponent;


//    SceneManager();
//    ~SceneManager();
//public:
//    static SceneManager *getInstance()
//    {
//      if (instance == nullptr)
//          instance = new SceneManager();
//      return instance;
//    }

//    static void changeScene(Scene* newScene)
//      {
//        if (instance->currScene != nullptr)
//            instance->currScene->unload();
//        newScene->load();
//        instance->currScene = newScene;
//      }
//    //TODO 确定场景切换方式 自动机orswitch
//    static void chooseNewScene(SCENE_NUMBER old_scene, int/*TODO information*/ );//选择新场景,场景切换利用SWITCH大概就够了
//    static void handleInput();
//};

//#endif // SCENEMANAGER_H
