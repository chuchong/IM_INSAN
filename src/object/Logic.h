//控制sprite的逻辑
//logic 本打算也弄成可解释的
//但是时间有点紧张了,而且必要的logic其实也不多
//就直接写成子类了
//最后生成logic的时候,直接用数字指代就行了
#ifndef LOGIC_H
#define LOGIC_H
#include <QRandomGenerator>
#include <QObject>
#include "ObjectSprite.h"
class SpriteObject;
class Logic
{
protected:
    SpriteObject* object_;
public:
    virtual ~Logic(){}
    Logic(SpriteObject* ob);
    virtual void run() = 0;
    virtual void handleInput(int INPUT_NUMBER) =0;
};

//以下的本质上还是自动机,只是比较简单的,用来给鱼用,足够了
class FishLogic:public Logic{
private:
    int birthtime = 0;// 记录出生活活了多久了
    int frame = 0;// to set time//一帧 1/60秒
    int state_;//0:游荡 1:饥饿 2: 躲避 3:饱了
    void runState0();
    void runState1();
    void runState2();
    void runState3();
    void inputState0(int);
    void inputState1(int);
    void inputState2(int);

public:
    FishLogic(SpriteObject *ob):Logic(ob){
        state_ = 0;
    }
    virtual void run();
    virtual void handleInput(int);
};
#endif // LOGIC_H
