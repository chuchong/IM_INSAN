#include "Breed.h"

Breed::Breed(){ clearHash();}

Breed::~Breed(){qDebug() << "delete breed" << name_;}

void Breed::setLogic(int type)
{
    qDebug() <<"logic" << type;
    logicType = ((parent_ != nullptr&& type == 0)? parent_->getLogic():type);
    qDebug() <<"logic" << logicType;
}

void Breed::setHeight(int h)
{
    height = ((parent_ != nullptr&& h == 0)? parent_->getHeight():h);
}

void Breed::setWidth(int w)
{
    width = ((parent_ != nullptr&& w == 0)? parent_->getWidth():w);
}

void Breed::addSkill(const EffectSeed &seed)
{
    if(seed.inherit == 1){
        assert(parent_ != nullptr);
        skillBar[seed.num] = parent_->getSkillBar().value(seed.num);
    }
    else{
        if(seed.effectName == "")
            return;
        else
            skillBar[seed.num] = new EffectSeed(seed.effectName,seed.toName,seed.num,seed.inherit
                                            ,seed.parameter);
    }
}

void Breed::setHp(int hp){
    maxHp_ = ((parent_ != nullptr&& hp == 0)? parent_->getHp():hp);//若有父指针且输入零,则选择父亲的血量
}

void Breed::setMaxVx(qreal maxVx){
    maxVx_ = ((parent_!= nullptr && maxVx == 0)? parent_->getMaxVx():maxVx);
}

void Breed::setMaxVy(qreal maxVy){
    maxVy_ = ((parent_!= nullptr && maxVy == 0)? parent_->getMaxVy():maxVy);
}

void Breed::setA(qreal a){
    a_ = ((parent_!= nullptr&& a == 0)? parent_->getA():a);
}

void Breed::setImage(QString im){
    image_ = ((parent_!= nullptr && im == "")? parent_->getImage():im);
}

void Breed::setType(QString type)
{
    if(parent_ != nullptr && type == ""){
        type_ = parent_ -> getType();
        return;
    }
    else
        type_ = type;
}

void Breed::clearHash()
{
    QHash<int,EffectSeed*>::Iterator i;
    for(i = skillBar.begin(); i != skillBar.end(); i ++) {
        delete i.value();
    }
    skillBar.clear();
}

const QHash<int, EffectSeed *> &Breed::getSkillBar()
{
    return skillBar;
}


SpriteObject *Breed::newSprite()
{
    return new SpriteObject(*this);
}

int Breed::getWidth(){return width;}
int Breed::getHeight(){return height;}

int Breed::getHp(){return maxHp_;}

int Breed::getLogic(){return logicType;}

qreal Breed::getMaxVx(){return maxVx_;}

qreal Breed::getMaxVy(){return maxVy_;}

qreal Breed::getVx(){return vx_;}

qreal Breed::getVy(){return vy_;}

qreal Breed::getA(){return a_;}

QString Breed::getImage(){return image_;}

QString Breed::getName(){return name_;}

QString Breed::getType(){return type_;}//下一步根据type

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
