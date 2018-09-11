#include "Logic.h"

Logic::Logic(SpriteObject *ob):object_(ob)
{

}


void FishLogic::runState0()
{
    int r_num = qrand();
    birthtime ++;
    if(birthtime == 29){
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
            break;
        case 3:
            object_ ->VY() = -object_->maxVY();
            break;
        };
    }
    if(birthtime >= 1800){
        object_->SkillEvolve();
    }

    if(birthtime % 50 == 0){
        int r_b = r_num %100;
        if(r_b <= 80)
            object_->SkillGenerate();
    }

    object_->HP() --;
    if(object_->HP() <= 400)
        state_ = 1;

}

void FishLogic::runState1()
{
    object_->HP() --;
    object_->SkillReachTarget();

    if(object_->HP() >= 800)
        state_=0;
}

void FishLogic::runState2()
{
    object_->SkillLeaveTarget();
}

void FishLogic::inputState0(int in)
{
    if(in == LOGIC_INPUT_DANGER)
        state_ = 2;
}

void FishLogic::inputState1(int in)
{
    if(in == LOGIC_INPUT_DANGER)
        state_ = 2;
}

void FishLogic::inputState2(int in)
{
    if(in == LOGIC_INPUT_SAFE)
        state_ = 0;
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

void FishLogic::handleInput(int input)
{
if(state_ == 0)
    inputState0(input);
else if(state_ == 1)
    inputState1(input);
else if(state_ == 2)
    inputState2(input);
}
