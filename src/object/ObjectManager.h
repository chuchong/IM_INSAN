#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QList>
#include "Object.h"
#include "BlockObject.h"
#include "SpriteObject.h"
#include "EffectContainer.h"
#include "BreedFactury.h"
#include "../component/ComponentPaint.h"
class ObjectManager
{
private:
    //生产者
    BreedFactury factury;
    //记录所有 Object
    QList<GameObject *> allList;
    //分项记录各类Object
    QList<BlockObject *> buttonsList;
    BlockObject *background;
    QList<SpriteObject *> fishList;
    QList<SpriteObject *> enemiesList;
    QList<SpriteObject *> friendsList;
    QList<SpriteObject *> bonusList;
    SpriteObject * boss;
    //技能我将其和Object分开了
    QList<EffectContainer *> skillsList;
    //以下是各类组件(Component)助其代工
    ComponentPaint *paintComp_;
public:
    ObjectManager(ComponentPaint *paintComp);
    void sortAndPaintPhase();
    void DeletePhase();
    void setBG(QString image, int x, int y, qreal px, qreal py);
    void resetBG(QString image, int x, int y, qreal px, qreal py);
};

#endif // OBJECTMANAGER_H
