#ifndef EFFECTFACTURY_H
#define EFFECTFACTURY_H
//其实是可以用来产生技能的
#include <QObject>
#include <QHash>
#include "EffectSeed.h"
#include "Effect.h"
class EffectFactury
{
private:
    QHash<QString, Effect *> effectPool;
public:
    void clearPool();
//    Effect *addEffect(EffectSeed seed);
//    void parseFromJson(QString url);
 //   在复杂一些就可以用了
    EffectFactury();
    Effect *getEffect(EffectSeed seed);

};

#endif // EFFECTFACTURY_H
