//工厂,负责sprite生产销毁
//TODO可以考虑从jason读取文件并初始化,或者原型模式
#ifndef BREEDFACTURY_H
#define BREEDFACTURY_H
//#include <QHash>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "../Constant.h"
#include "ObjectGame.h"
#include "ObjectSprite.h"
#include "ObjectBlock.h"
class GameObject;
class BreedFactury
{
private:
//    void setHP(Object * o_ptr, int hp);似乎是公共步骤
public:
    BreedFactury();
    BlockObject *getBG(QString image, int x, int y, qreal px, qreal py);
    BlockObject *getButton(QString image, int x, int y, qreal px, qreal py, CONDITIONS_ID a_cond);
    void killBG(GameObject *);
};

#endif // BREEDFACTURY_H
