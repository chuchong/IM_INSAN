#ifndef SCENESTORY_H
#define SCENESTORY_H
#include "Scene.h"

class SceneStory : public Scene
{
public:
    SceneStory();
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
};

#endif // SCENESTORY_H
