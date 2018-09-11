//控制sprite的逻辑
#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include "ObjectSprite.h"
class SpriteObject;
class Logic
{
protected:
    SpriteObject* ob_;
public:
    Logic(SpriteObject* ob);
    virtual void run(SpriteObject *ob);
};

#endif // LOGIC_H
