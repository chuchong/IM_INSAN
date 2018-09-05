#ifndef SCENEBATTLE_H
#define SCENEBATTLE_H
#include "Scene.h"

class SceneBattle : public Scene
{
public:
    SceneBattle();
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
};

#endif // SCENEBATTLE_H
