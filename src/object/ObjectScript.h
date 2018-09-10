#ifndef OBJECTSCRIPT_H
#define OBJECTSCRIPT_H
#include <QtDebug>
#include <QObject>
#include <QGraphicsSimpleTextItem>
#include <QFile>
#include <QFont>
#include <QStringBuilder>
#include <QBrush>
#include <QRgb>
#include "../Constant.h"
class ObjectScript : public QObject, public QGraphicsSimpleTextItem
{
    Q_OBJECT
private:
    QStringList scriptList;
public:
    explicit ObjectScript(QGraphicsSimpleTextItem *parent = nullptr);
    void setScriptFromText(QString url);
    bool showNextLine();//if is end, send 0
signals:

public slots:
};

#endif // OBJECTSCRIPT_H
