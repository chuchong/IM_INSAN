//可见,有运动逻辑,可被交互的对象
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <QObject>
#include "Object.h"
class SpriteObject :public GameObject
{
//    Q_OBJECT
public:
    SpriteObject();
    SpriteObject(QString image, int x, int y, qreal px, qreal py);

};

#endif // SPRITEOBJECT_H
