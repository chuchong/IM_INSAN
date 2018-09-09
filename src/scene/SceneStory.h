#ifndef SCENESTORY_H
#define SCENESTORY_H
#include <QSettings>
#include <QDebug>
#include "Scene.h"

class SceneStory : public Scene
{
    BlockObject *background;
public:
    SceneStory();
    virtual void parseFromFile(QString url);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESTORY_H
