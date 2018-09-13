#ifndef LOGICFSM_H
#define LOGICFSM_H
#include "Logic.h"
//先是不同的logic
class LogicState{
protected:
    SpriteObject* ob_;
public:
    LogicState(SpriteObject *ob);
};

struct LogicTransition{
    LogicState* from_;
    LogicState* to_;
    int input_;
    LogicTransition(LogicState* from, LogicState* to, int input):
    from_(from),to_(to),input_(input){
    }
};
//class LogicStateRandomWalk: public LogicState{
//    LogicStateRandomWalk(SpriteObject *ob):LogicState(ob){}
//    void stateRun();
//};

class LogicFSM{
    LogicFSM()
    {

    }
};
#endif // LOGICFSM_H
