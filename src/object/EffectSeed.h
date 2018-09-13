#ifndef SKILLSEED_H
#define SKILLSEED_H
#include <QString>
#include <QPointF>
#include <QRectF>
struct EffectSeed{
public:
    QString effectName = "";
    QString toName = "";
    int num;//技能在栏位的位置,即是大家所说的x技能
    bool inherit = 0;
    int parameter = 0;//for some use?
    int initHp = 1;

    EffectSeed(QString name, QString to, int num, bool inh, int para):
    effectName(name),toName(to),num(num),inherit(inh), parameter(para){}
};
struct EffectInitialInfo{
public:
    EffectSeed seed;
    QPointF bornPoint;
    QRectF targetRect;
    EffectInitialInfo(const EffectSeed & seed):seed(seed){}
    void setTargetRect(const QRectF & rect){targetRect = rect;}
};
#endif // SKILLSEED_H
