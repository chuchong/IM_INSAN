//工厂,负责sprite生产销毁
//TODO可以考虑从jason读取文件并初始化,或者原型模式
#ifndef BREEDFACTURY_H
#define BREEDFACTURY_H
//#include <QHash>
#include "../Constant.h"
#include "Object.h"
#include "SpriteObject.h"
#include "BlockObject.h"
class GameObject;
class BreedFactury
{
private:
//    void setHP(Object * o_ptr, int hp);似乎是公共步骤
public:
    BreedFactury();
    GameObject *getBG(QString image, int x, int y, qreal px, qreal py);
    void killBG(GameObject *);
};

#endif // BREEDFACTURY_H
