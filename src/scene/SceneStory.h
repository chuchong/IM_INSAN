#ifndef SCENESTORY_H
#define SCENESTORY_H
#include <QSettings>
#include <QDebug>
#include "Scene.h"
class SceneStory : public Scene
{
private:
    BlockObject *background;
    ObjectScript *script;
    QString script_url;

public:
    ~SceneStory(){ qDebug() << "delete story";}
    SceneStory();
    virtual void parseFromFile(QString url);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual void getIn();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual SCENE_TYPE getSceneType(){
        return STORY;
    }

//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENESTORY_H
