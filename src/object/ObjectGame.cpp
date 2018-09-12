#include "ObjectGame.h"

GameObject::~GameObject()
{

}

QRectF GameObject::boundingRect() const
{

//    qDebug() << pointf_;
    return QRect(0,0,width_,height_);
}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    qDebug() << width_ << "" << height_ << pointf_;
    painter->drawPixmap(0,0, width_, height_,
                        pixmap(),
                        xframe_ * width_ , yframe_ * height_, width_, height_);
    qDebug() <<pos().x() << pos().y();
}

QPainterPath GameObject::shape() const
{
    //注意paint默认返回boundingrect 坑啊

    QPainterPath path;
    QRect boundingrect(pos().x(),pos().y(),width_ , height_ );
    qDebug() << width_ << height_;
    path.addRect(boundingrect);
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
