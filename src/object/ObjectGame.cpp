#include "ObjectGame.h"

GameObject::~GameObject()
{

}

QRectF GameObject::boundingRect() const
{

    int w = pixmap().width();
    int h = pixmap().height();
    int x =this->pos().x();
    int y = this->pos().y();
//    rect.moveTopLeft(QPoint(this->x(),this->y()));
//    qDebug() << w << h << "rect :" << this->pos().x() << this->pos().y();
    return QRect(0,0,w,h);

}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(0,0,pixmap().width(),pixmap().height(),
                        pixmap());
}

QPainterPath GameObject::shape() const
{
    //注意paint默认返回boundingrect 坑啊
    QPainterPath path;
    QRect r(this->pos().x(),this->pos().y(),pixmap().width(),pixmap().height());
    path.addRect(r);
    return path;
}

void GameObject::setHP(int hp)
{
    hp_ = hp;
}

void GameObject::setImage(QString image)
{
    QPixmap pixmap;
    pixmap.load(image);
    setPixmap(pixmap);
}

bool GameObject::isDead(){
    if(hp_ <= 0)
        return true;
    else
        return false;
}

void GameObject::run()
{

}

//QRectF &GameObject::getRect()
//{
//    return pixmap().rect();
//}
