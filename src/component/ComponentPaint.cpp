#include "ComponentPaint.h"

ComponentPaint::ComponentPaint(QPaintDevice *device):device_(device)
{

}

void ComponentPaint::paint(Object *ob)
{
    QPainter painter(this->device);
    QPixmap  pix(ob->size_);
    pix.load(ob->imageRc_);
    qDebug() << pix.size();
    painter.drawPixmap(ob->point_, pix);
}
