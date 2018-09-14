#ifndef SCENESTART_H
#define SCENESTART_H

#include <QList>
#include "Scene.h"
#include "../object/ObjectGame.h"
#include "../object/ObjectBlock.h"
class SceneStart : public Scene
{
private:
   int timerNum;
   QList<BlockObject *>buttons;
   BlockObject *background;
//   QString bg_url = ":/BG_STARTMENU";
public:
   ~SceneStart(){ qDebug() << "delete start";}
    SceneStart();
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual void getIn();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual SCENE_TYPE getSceneType(){
        return START;
    }
    void timerEvent(QTimerEvent *event);
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESTART_H
