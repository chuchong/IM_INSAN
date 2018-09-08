#ifndef SCENESTORY_H
#define SCENESTORY_H
#include <QSettings>
#include <QDebug>
#include "Scene.h"

class SceneStory : public Scene
{
public:
    SceneStory(QString url);
    virtual void parseFromFile(QString url);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
};

#endif // SCENESTORY_H
