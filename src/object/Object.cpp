#include "Object.h"

GameObject::GameObject(QString image, int x, int y, qreal px, qreal py)
    :imageRc_(image),rect_(px, py, x, y)
{

}

void GameObject::setHP(int hp)
{
    hp = hp_;
}

QRect &GameObject::getRect()
{
    return rect_;
}
