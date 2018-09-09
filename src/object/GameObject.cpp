#include "GameObject.h"

QRectF GameObject::boundingRect() const
{
    QRectF rect = this->pixmap().rect();
    return rect;

}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(QPoint(0,0),
                        pixmap());
}

QPainterPath GameObject::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void GameObject::setHP(int hp)
{
    hp = hp_;
}

void GameObject::setImage(QString image)
{
    QPixmap pixmap;
    pixmap.load(image);
    setPixmap(pixmap);
}

//QRectF &GameObject::getRect()
//{
//    return pixmap().rect();
//}
