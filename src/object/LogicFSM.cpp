#include "LogicFSM.h"


LogicState::LogicState(SpriteObject *ob):ob_(ob)
{

}

void LogicStateRandomWalk::stateRun()
{
   int ran = qrand() % 4;
   switch(ran){
   case 0:
        ob_->VX() = ob_->maxVX();
       break;
   case 1:
       ob_->VY() = ob_->maxVY();
       break;
   case 2:
       ob_->VX() = - ob_->maxVX();
       break;
   case 3:
       ob_->VY() = - ob_->maxVY();
   }
}
