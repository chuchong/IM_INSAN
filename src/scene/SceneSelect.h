#ifndef SCENESELECT_H
#define SCENESELECT_H
#include "Scene.h"

class SceneSelect : public Scene
{
public:
    SceneSelect();
    virtual void parseFromJason(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
};

#endif // SCENESELECT_H
