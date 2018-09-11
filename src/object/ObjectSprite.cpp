#include "ObjectSprite.h"

int SpriteObject::sgn(qreal x)
{
    if(x > 0)
        return 1;
    else
        return -1;
}

//SpriteObject::SpriteObject()
//{
//    startTimer(100);
//}

SpriteObject::SpriteObject(Breed &breed):breed_(breed)
{
    imageRc_ = breed.getImage();
    hp_ = breed.getHp();
    breed_ = breed;
    maxVx = breed.getMaxVx();
    maxVy = breed.getMaxVy();

    //TODO change!
    ay = breed.getA();
    startTimer(100);
    a = 0;
    vx = vy = ax = 0;
    setImage(imageRc_);
}

SpriteObject::~SpriteObject(){
    qDebug()<<"delete" << breed_.getName();
}

//SpriteObject::SpriteObject(QString image, int x, int y, qreal px, qreal py)
//    :GameObject()
//{

//}

void SpriteObject::timerEvent(QTimerEvent *event)
{
    if(logic)
    logic->run(this);
    qreal new_x = this->pos().x() + vx;
    qreal new_y = this->pos().y() + vy;
    vx = (maxVx < sqrt(vx + ax))? (maxVx * sgn(vx + ax)): (vx + ax);
    vy = (maxVy < sqrt(vy + ay))? (maxVy * sgn(vy + ay)): (vy + ay);
    setPos(new_x,new_y);
}

SpriteObject::setVelocity(qreal vx, qreal vy)
{
    this->vx = vx;
    this->vy = vy;
}

QString SpriteObject::getType(){
    return breed_.getName();
}
