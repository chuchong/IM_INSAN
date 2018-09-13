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

SpriteObject::SpriteObject(Breed &breed, GameObject *parent):
    breed_(breed),
  GameObject(parent)
{
    qDebug()<<"his logictype" << breed.getLogic();
    width_ = breed.getWidth();
    height_ = breed.getHeight();
    imageRc_ = breed.getImage();
    hp_ = breed.getHp();
    breed_ = breed;
    maxVx = breed.getMaxVx();
    maxVy = breed.getMaxVy();
    //TODO change!
    vx = breed.getVx();
    vy = breed.getVy();
    a = breed.getA();
    setImage(imageRc_);

    if(breed.getLogic() == 1)
        this->logic = new FishLogic(this);
    else if(breed.getLogic() == 2)
        this->logic = new BaitLogic(this);
    else if(breed.getLogic() == 3)
        this->logic = new MoneyLogic(this);
    qDebug() << "my HP" << hp_;
}

SpriteObject::~SpriteObject(){
    qDebug()<<"delete" << breed_.getName();
    if(logic != nullptr)
        delete logic;
    clearSkills();
}

void SpriteObject::bounceBack()
{
    if(pos().y() > 600){
        vy = - vy;
        pos().setY(600);
    }
    if(pos().y() < 0){
        vy = - vy;
        pos().setY(0);
    }
    if(pos().x() > 900){
        vx = -vx;
        pos().setX(900);
    }
    if(pos().x() < 0){
        vx = - vx;
        pos().setX(0);
    }
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

void SpriteObject::setHp(int hp){hp_ = hp;}

void SpriteObject::run()
{
    if(this->hp_ > breed_.getHp())
        hp_ = breed_.getHp();
    if(logic)
    logic->run();


    if(getType() == "fish"){
        bounceBack();
    }
    vx = (maxVx < abs(vx + ax))? (maxVx * sgn(vx + ax)): (vx + ax);
    vy = (maxVy < abs(vy + ay))? (maxVy * sgn(vy + ay)): (vy + ay);

    qreal new_x = this->pos().x() + vx;
    qreal new_y = this->pos().y() + vy;
    setPos(new_x,new_y);
}

int SpriteObject::input(int message){
    return logic->handleInput(message);
}

void SpriteObject::moveToPoint(QPointF target)
{
    if(QPointF(target - pos()).manhattanLength() < 1e-5)
        return;
    qreal ABSV = sqrt(vx * vx + vy * vy);
    QPointF d = target - pos();
    qreal dx = d.x();
    qreal dy = d.y();
    qreal D = sqrt(dx * dx + dy * dy);
    vx = dx * ABSV / D;
    vy = dy * ABSV / D;
}

bool SpriteObject::isDead(){
    if(hp_ <= 0)
        return 1;
    else
        return 0;
}

QString SpriteObject::getType(){
    return breed_.getType();
}

qreal &SpriteObject::VX(){return vx;}

qreal &SpriteObject::VY(){return vy;}

qreal &SpriteObject::AX(){return ax;}

qreal &SpriteObject::AY(){return ay;}

int &SpriteObject::HP(){return hp_;}

int &SpriteObject::XFRAME(){return xframe_;}

int &SpriteObject::YFRAME(){return yframe_;}

qreal& SpriteObject::maxVX(){return maxVx;}

qreal &SpriteObject::maxVY(){return maxVy;}

void SpriteObject::clearSkills()
{
    // 如果作用域是局部的,改成指针
//    QHash<QString, EffectSeed*>::Iterator i;
//    for(i=skillBar.begin(); i != skillBar.end(); i ++) {
//        delete i.value();
//    }
//    skillBar.clear();
}


void SpriteObject::useSkill(int num)
{
    qDebug() << this->getType() << num;
    if(breed_.skillBar[num] != nullptr)
        emit generateSkill(breed_.skillBar[num], this);
}

void SpriteObject::useTargetRectSkill(int num, const QRectF &rect)
{
    qDebug() << this->getType() << num;
    if(breed_.skillBar[num] != nullptr)
        emit generateSkillWithTargetRect(breed_.skillBar[num], this,rect);
}

bool SpriteObject::haveSkill(int t)
{

    return breed_.skillBar.contains(t);
}


