#ifndef SCENEBATTLE_H
#define SCENEBATTLE_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "Scene.h"
//BreedFactury factury;
//SCENE_ID sceneId;
//QList<GameObject *> allList;
//BlockObject *background;

//QString background_url;
//virtual ~Scene(){}//只允许在栈上使用
//friend class GVariantKeeper;//负责让他帮忙析构
//virtual SCENE_ID getSceneId();
//virtual bool equal(Scene *newScene);
//virtual void sortAndPaintPhase();
//virtual void DeletePhase();
//virtual void setBG(QString image, int x, int y, qreal px, qreal py);
//virtual void resetBG(QString image, int x, int y, qreal px, qreal py);


class SceneBattle : public Scene
{
private:
    SCENE_ID next;//
    QList<SpriteObject *> baits;
    int timerId = 0;
    QPointF position;
public:
    SceneBattle();
    ~SceneBattle(){ qDebug() << "delete battle";/*this->unload();*/}
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual SCENE_TYPE getSceneType(){
        return BATTLE;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void timerEvent(QTimerEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENEBATTLE_H
