#ifndef SKILLSEED_H
#define SKILLSEED_H
#include <QString>
#include <QPointF>
struct EffectSeed{
public:
    QString effectName = "";
    QString toName = "";
    int hp = 1;
};
struct EffectInitialInfo{
public:
    EffectSeed seed;
    QPointF bornPoint;
}
#endif // SKILLSEED_H
