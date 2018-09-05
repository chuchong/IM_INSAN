#include "ComponentPaint.h"

ComponentPaint::ComponentPaint(QPaintDevice *device):device_(device)
{

}

void ComponentPaint::paint(GameObject *ob)
{
    QRect& rect = ob->getRect();
    QPainter painter(this->device_);
    QPixmap  pix(rect.size());
    pix.load(ob->imageRc_);
    qDebug() << pix.size();
    painter.drawPixmap(rect.topLeft(), pix);
}
