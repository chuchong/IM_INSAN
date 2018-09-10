//无AI逻辑,仅有画面\输入交互的可见单位
#ifndef BLOCKOBJECT_H
#define BLOCKOBJECT_H
#include <QObject>
#include "ObjectGame.h"
class BlockObject : public GameObject
{
private:
    S_CONDITIONS condition_;
public:
    BlockObject();
    BlockObject(QString image, int x, int y, qreal px, qreal py);
    S_CONDITIONS getCondition(){return condition_;}
    void setCondition(S_CONDITIONS cond){condition_= cond;}
    virtual void setHP (int hp = 1){}//无逻辑物体生命值为1,在工厂中生命清零,然后被管理器析构
};

#endif // BLOCKOBJECT_H
