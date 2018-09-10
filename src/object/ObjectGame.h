//一切可见非文本对象
//TODO 将其附着在QGraphicsItem上(设为子类?)
#ifndef OBJECT_H
#define OBJECT_H
#include <QImage>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
class ComponentPaint;
class BreedFactury;
class GameObject: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    QString imageRc_;
    QPointF point_;//rect_ 和 pixmap().rect() 不一定是一个事物,后者是外轮廓的闭包
                //而rectf_可以有其他用处
    int hp_;//"万物皆精灵",当hp为0的时候,清除,默认情况下,就连背景也有1点hp
    int height;//指定高度
public:
    //继承而来
    QRectF boundingRect()const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    QPainterPath shape()const;

    GameObject(QGraphicsPixmapItem *parent = nullptr):
    QGraphicsPixmapItem(parent){}//以让工厂类能较好的工作而设计,直接使用会出错

    //TODO 各种set方便工厂类
    virtual void setHP(int);
    virtual void setImage(QString image);

    virtual bool isDead(){
        return (hp_ <= 0);
    }
    virtual int getRelativeHeight(){//确认画图的上下关系
        return (int)((height << 7) + pixmap().rect().y());
    }
//    QRectF& getRect();
    friend class ComponentPaint;
};

#endif // OBJECT_H
