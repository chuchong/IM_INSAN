#ifndef COMPONENTPAINT_H
#define COMPONENTPAINT_H

#include <QObject>
#include <QPainter>
#include <QImage>
#include "../Constant.h"
#include "../object/ObjectGame.h"
class GameObject;
class ComponentPaint
{
private:
    QPaintDevice *device_;
public:
    ComponentPaint(QPaintDevice *device);
    void paint(GameObject *ob);
};

#endif // COMPONENTPAINT_H
