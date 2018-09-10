#include "ObjectGame.h"

QRectF GameObject::boundingRect() const
{

    int w = pixmap().width();
    int h = pixmap().height();
    int x =this->pos().x();
    int y = this->pos().y();
//    rect.moveTopLeft(QPoint(this->x(),this->y()));
    qDebug() << w << h << "rect :" << this->pos().x() << this->pos().y();
    return QRect(0,0,w,h);

}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(0,0,pixmap().width(),pixmap().height(),
                        pixmap());
}

QPainterPath GameObject::shape() const
{
    QPainterPath path;
    QRect r(this->pos().x(),this->pos().y(),pixmap().width(),pixmap().height());
    path.addRect(r);
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
