//可见,有运动逻辑,可被交互的对象
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <QObject>
#include "Object.h"
class SpriteObject :public Object/* public QObject*/
{
//    Q_OBJECT
public:
    explicit SpriteObject();

signals:

public slots:
};

#endif // SPRITEOBJECT_H
