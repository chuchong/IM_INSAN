//可见,有运动逻辑,可被交互的对象
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <QObject>
#include <QtMath>
#include "ObjectGame.h"
#include "Breed.h"
#include "Logic.h"
class Logic;
class Breed;
class SpriteObject :public GameObject
{
    int sgn(qreal x);
private:
    Logic *logic = nullptr;

    Breed & breed_ ;
    int hp_;
    qreal maxVx;
    qreal maxVy;
    qreal vx;
    qreal vy;
    qreal ax;
    qreal ay;
    qreal a;
    SpriteObject(Breed& breed);
    friend class Breed;
    friend class BreedFactury;
    friend class Logic;
public:
    ~SpriteObject();
    void timerEvent(QTimerEvent *event);
    void setVelocity(qreal vx, qreal vy);
    virtual void setHp(int hp){hp_ = hp;}
    virtual void run() override;
    virtual bool isDead(){
        if(hp_ <= 0)
            return 1;
        else
            return 0;
    }
    QString getType();

    //use for logic
public:
    qreal &VX(){return vx;}
    qreal &VY(){return vy;}
    qreal &AX(){return ax;}
    qreal &AY(){return ay;}
    int &HP(){return hp_;}

    qreal maxVX(){return maxVx;}
    qreal maxVY(){return maxVy;}

    //以下为"技能":能对scene中其他sprite产生效果的,能杀掉自己的
public:
    //即进化为新的一条鱼--自己死亡
    void SkillEvolve(){}
    //即产生一个新的东西
    void SkillGenerate(){}
    //靠近目标
    void SkillReachTarget(){}
    //远离目标
    void SkillLeaveTarget(){}
    //产生自己的尸体
    void SkillCreateBody(){}
};

#endif // SPRITEOBJECT_H
