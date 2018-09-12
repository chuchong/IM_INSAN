#ifndef SCENESELECT_H
#define SCENESELECT_H
#include "Scene.h"

class SceneSelect : public Scene
{
private:

public:
    ~SceneSelect(){ qDebug() << "delete select";}
    SceneSelect();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual void getIn();
    virtual SCENE_TYPE getSceneType(){
        return SELECT;
    }
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESELECT_H
