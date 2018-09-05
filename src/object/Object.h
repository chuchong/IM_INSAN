//一切可见非文本对象
#ifndef OBJECT_H
#define OBJECT_H
#include <QImage>
#include <QObject>

#include "../component/ComponentPaint.h"
class Object
{
    QString imageRc_;
    QRect size_;
    QPointF point_;
public:
    Object(String image, int x, int y, qreal px, qreal py);
    virtual void paint();
    friend class ComponentPaint;
};

#endif // OBJECT_H
