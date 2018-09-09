#ifndef SCENESELECT_H
#define SCENESELECT_H
#include "Scene.h"

class SceneSelect : public Scene
{

public:
    SceneSelect();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESELECT_H
