#ifndef SCENESTART_H
#define SCENESTART_H

#include <QList>
#include "Scene.h"
#include "../object/ObjectGame.h"
#include "../object/ObjectBlock.h"
class SceneStart : public Scene
{
private:
   QList<BlockObject *>buttons;
   BlockObject *background;
public:
   ~SceneStart(){ qDebug() << "delete start";}
    SceneStart();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual SCENE_TYPE getSceneType(){
        return START;
    }
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESTART_H
