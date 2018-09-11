//工厂,负责sprite生产销毁
//TODO可以考虑从jason读取文件并初始化,或者原型模式
#ifndef BREEDFACTURY_H
#define BREEDFACTURY_H
#include <QHash>
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
#include "Breed.h"
class BreedFactury
{
private:
    QHash<QString, Breed*> breedPool; //疑似应该放在factury中
public:
    void clearPool();
    void addBreeds(QString name, QString parent,
                   QString image = "",
                  qreal maxVx = 0, qreal maxVy = 0,qreal a = 0,
                   int hp = 0,
                   qreal vx = 0, qreal vy = 0);
    void parseFromJson(QString url);
    SpriteObject *getSpriteByTypeName(int x, int y, QString typeName);
    BreedFactury();
    ~BreedFactury();
    BlockObject *getBG(QString image, int x, int y, qreal px, qreal py);
    BlockObject *getButton(QString image, int x, int y, qreal px, qreal py, CONDITIONS_ID a_cond);
    void killBG(GameObject *);
//    SpriteObject *getBait(QString image, int x, int y, qreal px, qreal py,
//                          qreal vx = 0, qreal vy = VELOCITY_OF_BAIT);
};

#endif // BREEDFACTURY_H
