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
    bool hasSaya = 0;
    bool isEnd = 0;
    EffectFactury effectFactury;
    QGraphicsSimpleTextItem * moneyText;

    SCENE_ID next;//
    QList<SpriteObject *> baits;
    QList<SpriteObject *> fishes;
    int timerId = 0;
    int alienTime = 0;
    QPointF position;
    QList<Effect*> effectList;
    SpriteObject* addSprite(QPointF point, QString name);
    QList<SpriteObject*> aliens;
    QList<SpriteObject*> moneyList;

    int money = 2000;
    int spriteDis(SpriteObject * o1, SpriteObject * o2);


    int baitExp = 0;
    const QList<QString> baitNameMap = {"bait","bait_2","bait_3"};

    int maxBait = 1;
    int damage = 100;//the damage of weapon;

    QList<int> conditions = {0,0,0,500,1000,5000,1000,10000};
    QList<QRectF> rects;

    void addBlocks(int x, int y);
    void showWarning();
public:
    SceneBattle();
    ~SceneBattle();
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
    void directOneToAnother(SpriteObject * mover, QString targetType);
    void directOneToAnotherByName(SpriteObject * mover, QString targetName);
    void aoeKill(QRectF aoeRect, QString killType);
    void aoeKillByClass(QRectF aoeRect, QString killClass);
    void aoeKillByName(QRectF aoeRect, QString killName);
    QList<SpriteObject*> findTargetsInRect(QRectF rect, QString type);
    QList<SpriteObject*> findTargetsInRectByClass(QRectF rect, QString type);
    QList<SpriteObject *> findTargetsInRectByName(QRectF rect, QString type);
    bool healSprite(SpriteObject * object,int parameter);//1 for works , 0 for not work
//    int moveSpriteToPoint(SpriteObject * object, QPointF p);
    void sendAlienMessage();
    void sendNoAlienMessage();
    bool outOfRect(SpriteObject * ob);
    void clickBlock(int i);
};

#endif // SCENEBATTLE_H
