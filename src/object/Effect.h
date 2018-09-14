//effect即为技能的基本单元
#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include "EffectSeed.h"
#include "../Constant.h"

class SceneBattle;
class SpriteObject;
class Effect: public QObject
{
    Q_OBJECT
protected:
    QString effectName = "";
    SpriteObject *from_ = nullptr;
    SceneBattle *scene_ = nullptr;
    QString toName_ = "";
    int hp_ = 1;
    int num;
public:
    Effect(SpriteObject * from, SceneBattle * scene, const EffectInitialInfo & iniInfo)
    :effectName(iniInfo.seed.effectName),from_(from),scene_(scene),
      toName_(iniInfo.seed.toName),hp_(iniInfo.seed.initHp),
    num(iniInfo.seed.num){ }
    virtual bool isDead(){return hp_ <= 0;}
    virtual bool isAlive(){return hp_ > 0;}
    virtual void setDead(){hp_ = 0;}
    virtual int Happen() = 0;//int for other use
    virtual int getNum(){return num;}
};
//产生一个toname对象
class GenerateEffect : public Effect{
private:
    QPointF point_;
public:
    GenerateEffect(SpriteObject * from, SceneBattle * scene,
                   const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo),point_(initInfo.bornPoint){

    }
    virtual int Happen();
};
//将from的速度调整到任意toname的一个对象的方向
class ChaseEffect : public Effect{
public:
    ChaseEffect(SpriteObject * from, SceneBattle * scene,
                 const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo){

    }
    virtual int Happen();
};
class ChaseByNameEffect :public Effect{
public:
    ChaseByNameEffect(SpriteObject * from, SceneBattle * scene,
                      const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo){

    }
        virtual int Happen();
};
//将from的速度调整到远离toname的一个对象的方向
class DuckEffect: public Effect{
public:
    DuckEffect(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        Effect(from, scene, initInfo){

    }
    virtual int Happen();
};
//将单个框内所有物体杀死
class  KillEffect : public Effect{
    QRectF rect;
public:
    KillEffect(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
       Effect(from, scene, initInfo),rect(initInfo.targetRect){

    }
    virtual int Happen();
};
//为单个框内物体增加/减少血量 修改init值就变成了杀伤
//TODO 注意!!
class  HealEffect : public Effect{
private:
    int parameter;
    QRectF rect;
public:
    HealEffect(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo),parameter(initInfo.seed.parameter),
        rect(initInfo.targetRect){

    }
    virtual int Happen();
};
//牺牲自己...其实是一系列的effect 但我的时间有点太紧迫了
class SacrificeEffect:public HealEffect{
private:
public:
    SacrificeEffect(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        HealEffect(from,scene,initInfo){

    }
    virtual int Happen();
};

class MoveEffect:public Effect{
private:
    QPointF point_;
public:
    MoveEffect(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo&info):
        Effect(from, scene, info),point_(info.targetRect.topLeft()){

    }
    virtual int Happen();
};

class HealEffectByClass : public Effect{
private:
    int parameter;
    QRectF rect;
public:
    HealEffectByClass(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo),parameter(initInfo.seed.parameter),
        rect(initInfo.targetRect){

    }
    virtual int Happen();
};


class HealEffectByName : public Effect{
private:
    int parameter;
    QRectF rect;
public:
    HealEffectByName(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        Effect(from,scene,initInfo),parameter(initInfo.seed.parameter),
        rect(initInfo.targetRect){

    }
    virtual int Happen();
};

class SacrificeEffectByName:public HealEffectByName{
private:
public:
    SacrificeEffectByName(SpriteObject * from, SceneBattle * scene,
               const EffectInitialInfo &initInfo):
        HealEffectByName(from,scene,initInfo){

    }
    virtual int Happen();
};

class EffectFactury
{
private:
// if effects is too many
// then use effect effectHashMap to help set factury
//    QHash<QString, int> effectHshMap;
public:
    void clearPool();
//    Effect *addEffect(EffectSeed seed);
//    void parseFromJson(QString url);
 //   在复杂一些就可以用了
    EffectFactury();
    Effect *getEffect(SpriteObject * from, SceneBattle * scene,
                      const EffectInitialInfo &seed);

};

#endif // EFFECT_H
