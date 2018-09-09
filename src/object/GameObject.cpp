#include "GameObject.h"

QRectF GameObject::boundingRect() const
{
    QRectF rect = this->pixmap().rect();
    return rect;

}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(point_,
                        pixmap());
}

QPainterPath GameObject::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void GameObject::setPoint(int x, int y)
{
    point_.setX(x);
    point_.setY(y);
//    pixmap().rect().setTopLeft(point_);
}

void GameObject::setSize(int size_x, int size_y)
{
    pixmap().rect().setSize(QSize(size_x,size_y));
}

void GameObject::setHP(int hp)
{
    hp = hp_;
}

void GameObject::setImage(QString image, int x, int y, qreal px, qreal py)
{
    QPixmap pixmap;
    pixmap.load(image);
    setPoint(px, py);
    setSize(x, y);
    setPixmap(pixmap);
}

//QRectF &GameObject::getRect()
//{
//    return pixmap().rect();
//}
