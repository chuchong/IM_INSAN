#ifndef SCENESTART_H
#define SCENESTART_H

#include <QList>
#include "Scene.h"
#include "../object/GameObject.h"
#include "../object/BlockObject.h"
class SceneStart : public Scene
{
private:
   BlockObject *background;
public:
    SceneStart();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
};

#endif // SCENESTART_H
