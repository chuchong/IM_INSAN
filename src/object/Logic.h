//控制sprite的逻辑
#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include "ObjectSprite.h"
class SpriteObject;
class Logic
{
public:
    Logic();
    virtual void run(SpriteObject *ob);
    virtual void setX();
};

#endif // LOGIC_H
