#include "Breed.h"

Breed::Breed(){}

Breed::~Breed(){qDebug() << "delete breed" << name_;}

void Breed::setHp(int hp){
    if(parent_)
        hp_ = ((parent_ && hp == 0)? parent_->getHp():hp);//若有父指针且输入零,则选择父亲的血量
    }

void Breed::setMaxVx(qreal maxVx){
    maxVx_ = ((parent_ && maxVx == 0)? parent_->getMaxVx():maxVx);
}

void Breed::setMaxVy(qreal maxVy){
    maxVy_ = ((parent_ && maxVy == 0)? parent_->getMaxVy():maxVy);
}

void Breed::setA(qreal a){
    a_ = ((parent_&& a == 0)? parent_->getA():a);
}

void Breed::setImage(QString im){
    image_ = ((parent_ && im == "")? parent_->getImage():im);
}


SpriteObject *Breed::newSprite()
{
    return new SpriteObject(*this);
}

int Breed::getHp(){return hp_;}

qreal Breed::getMaxVx(){return maxVx_;}

qreal Breed::getMaxVy(){return maxVy_;}

qreal Breed::getVx(){return vx_;}

qreal Breed::getVy(){return vy_;}

qreal Breed::getA(){return a_;}

QString Breed::getImage(){return image_;}

QString Breed::getName(){return name_;}

void Breed::setInitial(QString name, Breed* parent,
                  QString image,
                  qreal maxVx, qreal maxVy,qreal a,
                   int hp)
{
    name_ = name;
    parent_ = parent;
    setA(a);
    setHp(hp);
    setMaxVx(maxVx);
    setMaxVy(maxVy);
    setImage(image);
}

void Breed::setIniVelo(qreal vx, qreal vy)
{
    vx_ = vx;
    vy_ = vy;
}
