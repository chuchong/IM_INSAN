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
class BreedFactury;
//生产技能的种子

class SpriteObject :public GameObject
{
    Q_OBJECT

    int sgn(qreal x);
private:
    Logic *logic = nullptr;
    Breed & breed_ ;
    qreal maxVx;
    qreal maxVy;
    qreal vx;
    qreal vy;
    qreal ax;
    qreal ay;
    qreal a;
    SpriteObject(Breed& breed, GameObject * parent =nullptr);
    friend class Breed;
    friend class BreedFactury;
    friend class Logic;
public:
    ~SpriteObject();
    void bounceBack();
    void timerEvent(QTimerEvent *event);
    void setVelocity(qreal vx, qreal vy);
    virtual void toDie() override;
    virtual void setHp(int hp);
    virtual void run() override;
    virtual int input(int message);
    void moveToPoint(QPointF p);

    virtual bool isDead();
    QString getType();
    QString getName();
    //use for logic
public:
    qreal &VX();
    qreal &VY();
    qreal &AX();
    qreal &AY();
    int &HP();
    qreal getY();
    qreal getX();
    int getWidth();
    int getHeight();

    int &XFRAME();
    int &YFRAME();
    qreal& maxVX();
    qreal& maxVY();
    int getMaxHp();

    //以下为"技能":能对scene中其他sprite产生效果的,能杀掉自己的
private:
    void clearSkills();
public:
    void useSkill(int);//使用几技能
    void useTargetRectSkill(int,const QRectF & rect);
    bool haveSkill(int);
signals:
    void generateSkill(EffectSeed *, SpriteObject *from);//通过哦generate breed 中不同的参数
    void generateSkillWithTargetRect(EffectSeed * seed, SpriteObject *from,const QRectF & rect);
};
#endif // SPRITEOBJECT_H
