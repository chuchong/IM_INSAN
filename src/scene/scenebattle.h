#ifndef SCENEBATTLE_H
#define SCENEBATTLE_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QtMath>
#include "Scene.h"
#include "../object/Effect.h"
#include "../object/ObjectSprite.h"


class SceneBattle : public Scene
{
private:
    QGraphicsSimpleTextItem * moneyText;

    EffectFactury effectFactury;
    SCENE_ID next;//
    QList<SpriteObject *> baits;
    QList<SpriteObject *> fishes;
    int timerId = 0;
    QPointF position;
    QList<Effect*> effectList;
    SpriteObject* addSprite(QPointF point, QString name);
    QList<SpriteObject*> aliens;
    QList<SpriteObject*> moneyList;
    int money = 0;
    int spriteDis(SpriteObject * o1, SpriteObject * o2);
//    QList<SpriteObject *>& findSpriteListByType(QString type);
public:
    SceneBattle();
    ~SceneBattle(){ qDebug() << "delete battle";/*this->unload();*/}
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual void getIn();
    virtual SCENE_TYPE getSceneType(){
        return BATTLE;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void DeletePhase();
public slots:
    void addSkillWithTargetRect(EffectSeed * seed, SpriteObject *from,const QRectF & rect);
    void addSkill(EffectSeed * seed, SpriteObject *from);
    void addSpriteFromName(QPointF point, QString name);
    void directOneToAnother(SpriteObject * mover, QString targetName);
    void aoeKill(QRectF aoeRect, QString killType);
    QList<SpriteObject*> findTargetsInRect(QRectF rect, QString type);
    bool healSprite(SpriteObject * object,int parameter);//1 for works , 0 for not work
    int moveSpriteToPoint(SpriteObject * object, QPointF p);
    void sendAlienMessage();
    void sendNoAlienMessage();
    bool outOfRect(SpriteObject * ob);
};

#endif // SCENEBATTLE_H
