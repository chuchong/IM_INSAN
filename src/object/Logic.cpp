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
    if(birthtime >= 1800){
//        进化成下一条鱼
        if(object_->haveSkill(1)){
            object_->useSkill(1);
            object_->setHp(-1);
        }
    }

    if(birthtime  % 250 == 0){
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
        object_->XFRAME() = 1;
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
        object_->XFRAME() = 0;
        object_->update();
        object_->maxVX() /= 2;
        object_->maxVY() /=4;
        object_->VX() /= 2;
    }
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
    return OUTPUT_UNSECCESS;
}

int FishLogic::inputState1(int in)
{
    if(in == LOGIC_INPUT_DANGER){
        state_ = 2;
        return OUTPUT_SUCCESS;
    }
    if(in == LOGIC_INPUT_FEED){
        object_->XFRAME() = 0;
        object_->setHP(2000);
        state_ = 0;
        object_ ->update();
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSECCESS;
}

int FishLogic::inputState2(int in)
{
    if(in == LOGIC_INPUT_SAFE){
        state_ = 0;
        return OUTPUT_SUCCESS;
    }
    return OUTPUT_UNSECCESS;
}

void FishLogic::run()
{
    if(state_ == 0)
        runState0();
    else if(state_ == 1)
        runState1();
    else if(state_ == 2)
        runState2();
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

void BaitLogic::run(){
    QRectF rect = object_->boundingRect();
    rect.moveTopLeft(object_->pos());
    object_->useTargetRectSkill(1,rect);
}

int BaitLogic::handleInput(int INPUT_NUMBER){
    return OUTPUT_SUCCESS;
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
        return OUTPUT_UNSECCESS;

}
