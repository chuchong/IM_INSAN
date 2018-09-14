#include "Logic.h"
#include "ObjectSprite.h"
Logic::~Logic(){}

Logic::Logic(SpriteObject *ob):object_(ob)
{

}


void FishLogic::runState0()
{
    int r_num = qrand();
    birthtime ++;
    if(birthtime % 29 == 0){
        int r_a = r_num % 4;
        switch(r_a){
        case 0:
            object_ -> VX() = object_->maxVX();
            break;
        case 1:
            object_ -> VX() = -object_->maxVX();
            break;
        case 2:
            object_ -> VY() = object_->maxVY();
            object_ ->AY() = -object_->AY();
            break;
        case 3:
            object_ ->VY() = -object_->maxVY();
            object_->AY() = - object_->AY();
            break;
        };
    }
    if(birthtime >= para_evolvetime){
//        进化成下一条鱼
        if(object_->haveSkill(1)){
            object_->useSkill(1);
            object_->setHp(-1);
            suicide = 1;
        }
    }

    if(birthtime  % para_moneytime == 0){
        int r_b = r_num %100;
        if(r_b <= 80){
//         产生金币
            if(object_->haveSkill(2)){
                object_->useSkill(2);
            }
        }

    }

    object_->HP() --;
    if(object_->HP() <= 400){
//        object_->setVelocity(0,0);
        state_ = 1;
        object_->YFRAME() = 1;
        object_->update();
        object_->maxVX() *= 2;
        object_->maxVY() *= 4;
        object_->VX() *= 2;
    qDebug() << "I'm hungry";
    }
}

void FishLogic::runState1()//饥饿
{
    object_->HP() --;
//    找食物
//    int r_num = qrand() % 100;
//    if(r_num <= 20){
        if(object_->haveSkill(3))
        object_->useSkill(3);
//    }

    if(object_->HP() >= 800){
        state_=0;
        object_->YFRAME() = 0;
        object_->update();
        object_->maxVX() /= 2;
        object_->maxVY() /=4;
        object_->VX() /= 2;
    }
//    //换成尸体
//    if(object_->HP() == 0)
//        object_->XFRAME() = 2;
}

void FishLogic::runState2()
{
//   躲外星人
    int r_num = qrand() % 100;
    if(r_num <= 40){
        if(object_->haveSkill(4))
        object_->useSkill(4);
    }
}

int FishLogic::inputState0(int in)
{
    if(in == LOGIC_INPUT_DANGER){
        state_ = 2;
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSUCCESS;
}

int FishLogic::inputState1(int in)
{
    if(in == LOGIC_INPUT_DANGER){
        state_ = 2;
        return OUTPUT_SUCCESS;
    }
    if(in == LOGIC_INPUT_FEED){
        object_->YFRAME() = 0;
        object_->setHP(2000);
        state_ = 0;
        object_ ->update();
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSUCCESS;
}

int FishLogic::inputState2(int in)
{
    if(in == LOGIC_INPUT_SAFE){
        state_ = 0;
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSUCCESS;
}

void FishLogic::run()
{
    if(object_->haveSkill(5)){
        QRectF rect = object_->boundingRect();
        rect.moveTopLeft(object_->pos());
        object_->useTargetRectSkill(5,rect);
    }// 成为别人的食物

    //共10张图 -maxVX <-> maxVx
    int i = ((object_->VX() / object_->maxVX()) * 4.5) + 4.5;
    if( i >= 9) i = 9; if( i<= 0) i = 0;
    object_->XFRAME() = i;

    if(state_ == 0)
        runState0();
    else if(state_ == 1)
        runState1();
    else if(state_ == 2)
        runState2();
}

void FishLogic::die()
{
    if(object_->haveSkill(8) && suicide == 0)
    object_->useSkill(8);//变成尸体
}

int FishLogic::handleInput(int input)
{
if( input == LOGIC_INPUT_HEAL)
        return OUTPUT_SUCCESS;
if(state_ == 0)
    return inputState0(input);
else if(state_ == 1)
    return inputState1(input);
else if(state_ == 2)
    return inputState2(input);
}

void BaitLogic::die()
{
//    object_->useSkill(5);
}

void BaitLogic::run(){
    object_->XFRAME() ++;
    if(object_->XFRAME() == 10)
        object_->XFRAME() = 0;

    QRectF rect = object_->boundingRect();
    rect.moveTopLeft(object_->pos());
    object_->useTargetRectSkill(1,rect);
    object_->useTargetRectSkill(2,rect);
}

int BaitLogic::handleInput(int INPUT_NUMBER){
    return OUTPUT_SUCCESS;
}

void MoneyLogic::die()
{

}

void MoneyLogic::run()
{

}

int MoneyLogic::handleInput(int INPUT_NUMBER)
{
    if(INPUT_NUMBER == LOGIC_INPUT_CLICK){
        return OUTPUT_MONEY;
        object_->setHp(-1);
    }
    else
        return OUTPUT_UNSUCCESS;

}

void AlienLogic::die()
{
    //
    object_->useSkill(4);
}

void AlienLogic::run()
{


    if(object_->HP() <= 0){
        object_->useSkill(4);
    }
    birthtime ++;
    if(birthtime % 10 == 0){
        object_->useSkill(1);
        object_->useSkill(3);

        object_ -> XFRAME() ++;
        if(object_->XFRAME() * object_->getWidth() >= object_->pixmap().width() )
            object_->XFRAME() = 0;

    }

    QRectF rect = object_->boundingRect();
    rect.moveTopLeft(object_->pos());
    object_->useTargetRectSkill(2,rect);
}

int AlienLogic::handleInput(int INPUT_NUMBER)
{
    if(INPUT_NUMBER == LOGIC_INPUT_CLICK && object_->getName() != "alien_2"){
        return OUTPUT_ALIEN;
    }
    else if(INPUT_NUMBER == LOGIC_INPUT_CLICK && object_->getName() == "alien_2"){
        return OUTPUT_ALIEN_NO_EFFECT;
    }
    else
        return OUTPUT_UNSUCCESS;
}

void FriendLogic::die()
{

}

void FriendLogic::run()
{
    if(has_enemy == 0){
        object_->VY() = 0;
        birthtime ++;

        object_->useSkill(3);

        if(birthtime % 3 == 0){
        QRectF rect = object_->boundingRect();
        rect.moveTopLeft(object_->pos());
        object_->useTargetRectSkill(2,rect);
        }
    }
    else{
        object_->VX() = object_->VY() = 0;
    }
}

int FriendLogic::handleInput(int INPUT_NUMBER)
{
    if(INPUT_NUMBER == LOGIC_INPUT_DANGER){
        has_enemy = 1;
        object_->XFRAME() = 1;
        return OUTPUT_SUCCESS;
    }
    else if(INPUT_NUMBER == LOGIC_INPUT_SAFE){
        has_enemy = 0;
        object_->XFRAME() = 0;
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSUCCESS;
}

void BodyLogic::die()
{

}

void BodyLogic::run()
{
    object_->HP() --;
    if(object_ -> HP() % 15 == 0)
        object_->XFRAME() += 1;
}

int BodyLogic::handleInput(int INPUT_NUMBER)
{
    return OUTPUT_UNSUCCESS;
}

void BarLogic::die()
{

}

void BarLogic::run()
{
    if(this->activated){
        object_ -> HP() --;
        int hp = object_->HP();
        if(hp >= 40)
            object_ ->XFRAME() = 1;
        else if(hp >= 20)
            object_ ->XFRAME() = 2;
        else if(hp < 20)
            object_->XFRAME() = 3;
    }
//    object_->XFRAME() = 0;
//    object_->update();
}

int BarLogic::handleInput(int INPUT_NUMBER)
{
    if(INPUT_NUMBER == LOGIC_INPUT_ACTIVATE){
        activated = 1;
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSUCCESS;
//    if(INPUT_NUMBER == LOGIC_INPUT_CLICK){
//        if(object_->haveSkill(1))
//            object_->useSkill(1);
//        return OUTPUT_SUCCESS;
//    }
//    else return OUTPUT_UNSUCCESS;
}

void NoLogic::die()
{

}

void NoLogic::run()
{
    object_->HP() --;
}

int NoLogic::handleInput(int INPUT_NUMBER)
{
    return OUTPUT_UNSUCCESS;
}
