#include "SpriteObject.h"

SpriteObject::SpriteObject()
{

}

SpriteObject::SpriteObject(QString image, int x, int y, qreal px, qreal py)
    :GameObject(image, x, y, px, py)
{

}
