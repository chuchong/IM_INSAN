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
    setVelocity(qreal vx, qreal vy);
    virtual void setHp(int hp){hp_ = hp;}
    virtual void run() override;
    QString getType();


};

#endif // SPRITEOBJECT_H
