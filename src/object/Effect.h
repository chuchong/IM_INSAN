//effect即为技能的基本单元
#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include "../scene/SceneBattle.h"
#include "EffectSeed.h"
#include "ObjectSprite.h"

class Effect: public QObject
{
    Q_OBJECT
protected:
    SpriteObject *from_ = nullptr;
    SceneBattle *scene_ = nullptr;
    QString toName_ = "";
    int hp_ = 1;
public:
    Effect(SpriteObject * from, SceneBattle * scene, const EffectInitialInfo & iniInfo)
    :from_(from),scene_(scene),
      toName_(iniInfo.seed.toName),hp_(iniInfo.seed.hp){ }
    virtual int Happen() = 0;//int for other use
};
//产生一个toname对象
class GenerateEffect : public Effect{
private:
    QPointF point_;
public:
    GenerateEffect(SpriteObject * from, SceneBattle * scene,
                   const EffectInitialInfo initInfo):
        Effect(from,scene,initInfo),pointf_(initInfo.bornPoint){

    }
    virtual int Happen(){
        scene_->addSpriteFromName(point_,toName_);
    }
};
//将from的速度调整到任意toname的一个对象的方向
class DirectEffect : public Effect{
public:
    DirectEffect(SpriteObject * from, SceneBattle * scene,
                 const EffectInitialInfo initInfo):
        Effect(from,scene,initInfo){

    }
    virtual int Happen(){
        scene_->DirectOneToAnother(from_,toName_);
    }
};
#endif // EFFECT_H
