#include "Effect.h"
#include "../scene/SceneBattle.h"
#include "ObjectSprite.h"
void EffectFactury::clearPool()
{

}

//Effect *EffectFactury::addEffect(EffectSeed seed)
//{

//}

//void EffectFactury::parseFromJson(QString url)
//{

//}

EffectFactury::EffectFactury()
{

}

Effect *EffectFactury::getEffect(SpriteObject * from, SceneBattle * scene,
                                 const EffectInitialInfo  &initInfo)
{
    if(initInfo.seed.effectName == "generate")
        return new GenerateEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "chase")
        return new ChaseEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "duck")
        return new DuckEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "kill")
        return new KillEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "heal")
        return new HealEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "sacrifice")
        return new SacrificeEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "move")
        return new MoveEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "chasebyname")
        return new ChaseByNameEffect(from,scene,initInfo);
    else if(initInfo.seed.effectName == "healbyclass")
        return new HealEffectByClass(from,scene,initInfo);
    else if(initInfo.seed.effectName == "healbyname")
        return new HealEffectByName(from,scene,initInfo);
    else if(initInfo.seed.effectName == "sacrificebyname")
        return new SacrificeEffectByName(from,scene,initInfo);
    assert(1);//something has got wrong
    return nullptr;
}

int ChaseEffect::Happen(){
    scene_->directOneToAnother(from_,toName_);
    return EFFECT_SUCCESS;
}

int DuckEffect::Happen(){
    scene_->directOneToAnother(from_,toName_);
    from_ ->VX() *= -1;
    from_ ->VY() *= -1;
    return EFFECT_SUCCESS;
}

int KillEffect::Happen(){
    scene_->aoeKill(rect, toName_);
    return EFFECT_SUCCESS;
}

int HealEffect::Happen(){
    auto sprites = scene_->findTargetsInRect(rect,toName_);
    for(auto iter:sprites){
        if(scene_->healSprite(iter,parameter))
            return EFFECT_SUCCESS;
    }
    return EFFECT_UNSUCCESS;
}

int SacrificeEffect::Happen(){
    if(HealEffect::Happen() == EFFECT_SUCCESS){
        from_->setHp(-1);
        return EFFECT_SUCCESS;
    }
    return EFFECT_UNSUCCESS;
}

int GenerateEffect::Happen(){
    scene_->addSpriteFromName(point_,toName_);
    return EFFECT_SUCCESS;
}

int MoveEffect::Happen()
{
//    scene_->moveSpriteToPoint(from_, point_);
       return 1;
}

int ChaseByNameEffect::Happen()
{
    scene_->directOneToAnotherByName(from_, toName_);
}

int HealEffectByClass::Happen()
{
    scene_->aoeKillByClass(rect, toName_);
    return EFFECT_SUCCESS;
}

int HealEffectByName::Happen()
{
    auto sprites = scene_->findTargetsInRectByName(rect,toName_);
    for(auto iter:sprites){
        if(scene_->healSprite(iter,parameter))
            return EFFECT_SUCCESS;
    }
    return EFFECT_UNSUCCESS;
}

int SacrificeEffectByName::Happen()
{
    if(HealEffectByName::Happen() == EFFECT_SUCCESS){
        from_->setHp(-1);
        return EFFECT_SUCCESS;
    }
    return EFFECT_UNSUCCESS;
}
