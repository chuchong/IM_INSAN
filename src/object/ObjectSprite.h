//可见,有运动逻辑,可被交互的对象
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <QObject>
#include "ObjectGame.h"
class SpriteObject :public GameObject
{
//    already have
//    QString imageRc_;
//    QPointF point_;//rect_ 和 pixmap().rect() 不一定是一个事物,后者是外轮廓的闭包
//                //而rectf_可以有其他用处
//    int hp_;//"万物皆精灵",当hp为0的时候,清除,默认情况下,就连背景也有1点hp
//    int height;//指定高度
//
//    virtual void setHP(int);
//    virtual void setImage(QString image);
//    virtual bool isDead(){
//        return (hp_ <= 0);
//    }
//    virtual int getRelativeHeight(){//确认画图的上下关系
//        return (int)((height << 7) + pixmap().rect().y());
//    }
private:

public:
    SpriteObject();
    SpriteObject(QString image, int x, int y, qreal px, qreal py);

};

#endif // SPRITEOBJECT_H
