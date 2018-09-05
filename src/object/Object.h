//一切可见非文本对象
//TODO 将其附着在QGraphicsItem上(设为子类?)
#ifndef OBJECT_H
#define OBJECT_H
#include <QImage>
#include <QObject>

class ComponentPaint;
class BreedFactury;
class GameObject
{
    QString imageRc_;
    QRect rect_;
    int hp_;//"万物皆精灵",当hp为0的时候,清除,默认情况下,就连背景也有1点hp
    int height;//指定高度
public:
    GameObject(QString image, int x, int y, qreal px, qreal py);
    GameObject(){}//以让工厂类能较好的工作而设计,直接使用会出错

    //TODO 各种set方便工厂类
    virtual void setHP(int);

    virtual bool isDead(){
        return (hp_ <= 0);
    }
    virtual int getRelativeHeight(){//确认画图的上下关系
        return (int)((height << 7) + rect_.y());
    }
    QRect& getRect();
    friend class ComponentPaint;
};

#endif // OBJECT_H
