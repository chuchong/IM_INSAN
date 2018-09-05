#include "Object.h"

Object::Object(QString image, int x, int y, qreal px, qreal py)
    :imageRc_(image),size_(x,y),point_(px,pz)
{

}

void Object::paint(ComponentPaint &cp)
{
    cp.paint(this);
}
