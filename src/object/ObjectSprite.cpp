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
    qDebug()<<"his logictype" << breed.getLogic();
    imageRc_ = breed.getImage();
    hp_ = breed.getHp();
    breed_ = breed;
    maxVx = breed.getMaxVx();
    maxVy = breed.getMaxVy();

    //TODO change!
    ay = breed.getA();
//    startTimer(16);
    a = 0;
    vx = vy = ax = 0;
    setImage(imageRc_);

    if(breed.getLogic() == 1)
        this->logic = new FishLogic(this);

    qDebug() << "my HP" << hp_;
}

SpriteObject::~SpriteObject(){
    qDebug()<<"delete" << breed_.getName();
    if(logic != nullptr)
        delete logic;
}

//SpriteObject::SpriteObject(QString image, int x, int y, qreal px, qreal py)
//    :GameObject()
//{

//}

void SpriteObject::timerEvent(QTimerEvent *event)
{

}

void SpriteObject::setVelocity(qreal vx, qreal vy)
{
    this->vx = vx;
    this->vy = vy;
}

void SpriteObject::run()
{
    if(logic)
    logic->run();


    if(getType() == "fish"){
        if(pos().y() > 600){
            pos().setY(600);
            vy = - vy;
        }
    }
    vx = (maxVx < sqrt(vx + ax))? (maxVx * sgn(vx + ax)): (vx + ax);
    vy = (maxVy < sqrt(vy + ay))? (maxVy * sgn(vy + ay)): (vy + ay);

    qreal new_x = this->pos().x() + vx;
    qreal new_y = this->pos().y() + vy;
    setPos(new_x,new_y);
}

QString SpriteObject::getType(){
    return breed_.getName();
}


