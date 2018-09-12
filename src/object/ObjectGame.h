//一切可见非文本对象
//TODO 将其附着在QGraphicsItem上(设为子类?)
#ifndef OBJECT_H
#define OBJECT_H
#include <QImage>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include "../Constant.h"
class ComponentPaint;
class BreedFactury;
class GameObject: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
//    to debug
//    virtual void setPos(int x, int y) = delete;
//    virtual QPointF pos() = delete;

    int xframe_ = 0; //in which part of its image
    int yframe_ = 0;
    int height_ = 0;//height of it's box
    int width_ = 0;//width of it's box
//    QPointF pointf_;//it's reality box
    QString imageRc_;
    int hp_ ;//"万物皆精灵",当hp为0的时候,清除,默认情况下,就连背景也有1点hp
//    int height;//指定高度
public:
    //继承而来
    virtual ~GameObject();
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;

    GameObject(QGraphicsPixmapItem *parent = nullptr):
    QGraphicsPixmapItem(parent){}//以让工厂类能较好的工作而设计,直接使用会出错

    //TODO 各种set方便工厂类
    virtual void setHP(int);
    virtual void setImage(QString image);
    virtual void setRect(int wi, int he){
        width_ = wi; height_ = he;}
    virtual void setPosX(qreal x){pos().setX(x);}
    virtual void setPosY(qreal y){pos().setY(y);}
//    virtual void setPos(int x, int y){
//        setPosX(x);setPosY(y);}
//    virtual void setPos(QPointF p){
//        pointf_ = p;
//    }
//    QPointF pos(){
//        return pos();}

    virtual bool isDead();
    virtual int getRelativeHeight(){//确认画图的上下关系
        return (int)((this->zValue()) + pixmap().rect().y());
    }
    virtual void run();
//    QRectF& getRect();
    friend class ComponentPaint;
};

#endif // OBJECT_H
