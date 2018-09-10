#ifndef SCENESTART_H
#define SCENESTART_H

#include <QList>
#include "Scene.h"
#include "../object/GameObject.h"
#include "../object/BlockObject.h"
class SceneStart : public Scene
{
private:
   QList<BlockObject *>buttons;
   BlockObject *background;

public:
   ~SceneStart(){ this->unload();}
    SceneStart();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESTART_H
