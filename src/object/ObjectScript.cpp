#include "ObjectScript.h"

ObjectScript::ObjectScript(QGraphicsSimpleTextItem *parent) : QGraphicsSimpleTextItem(parent)
{

}

void ObjectScript::setScriptFromText(QString url)
{
    QFile file(url);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        scriptList.append(str);
    }
    this->setX(15);
    this->setFont(QFont("微软雅黑",15,QFont::Light));
    this->setBrush(QBrush(qRgba(COLOR_AOI)));
    showNextLine();
}

bool ObjectScript::showNextLine()
{
    if(!scriptList.isEmpty()){
        this->setText(this->text() % scriptList[0]);
        scriptList.removeAt(0);
        return 1;
    }
    else
        return 0;
}
