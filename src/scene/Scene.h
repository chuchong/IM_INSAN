//Scene是指一个场景
//Scene在游戏中一旦在栈上创立好,就必须等系统来回收
//而Scene真正的初始化在load()函数中
//同理,其析构在unload()中
//通过SceneMachine可以设立一套切换Scene的逻辑
#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "../Constant.h"
#include "../object/BlockObject.h"
#include "../object/SpriteObject.h"
#include "../object/BreedFactury.h"
class SceneStart;
class SceneBattle;
class SceneSelect;
class SceneStory;
class GVariantKeeper;
class Scene:public QGraphicsScene
{
    Q_OBJECT
protected:
    BreedFactury factury;
    SCENE_ID sceneId;
    QList<GameObject *> allList;
    BlockObject *background;
    virtual ~Scene(){}//只允许在栈上使用
    friend class GVariantKeeper;//负责让他帮忙析构
signals:
    virtual void sendCondition(S_CONDITIONS conditions);
public:
    Scene(QObject *parent = nullptr);
    //接口 从本地文档中读取配置文件,大体上包含json ini
    virtual void parseFromFile(QString j) = 0;
    virtual void update() = 0;//逻辑
    virtual void redraw() = 0;//绘制
    virtual void load() = 0;
    virtual void unload() = 0;
//    virtual Scene *duplicateScene(Scene *) = 0;

    //送给子类的类函数
    virtual SCENE_ID getSceneId();
    virtual bool equal(Scene *newScene);
    virtual void sortAndPaintPhase();
    virtual void DeletePhase();
    virtual void setBG(QString image, int x, int y, qreal px, qreal py);
    virtual void resetBG(QString image, int x, int y, qreal px, qreal py);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // SCENE_H
