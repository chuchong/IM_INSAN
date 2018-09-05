#ifndef COMPONENTPAINT_H
#define COMPONENTPAINT_H

#include <QObject>
#include <QPainter>
#include <QImage>
#include "../object/Object.h"
class ComponentPaint
{
private:
    QPaintDevice *device;
public:
    ComponentPaint();
    void paint(Object *ob);
};

#endif // COMPONENTPAINT_H
