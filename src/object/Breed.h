#ifndef BREED_H
#define BREED_H
#include <QtDebug>
#include <QString>
#include "ObjectSprite.h"
#include "Logic.h"
#include "EffectSeed.h"
class SpriteObject;
class BreedFactury;
//产生技能的种子

class Breed{//表示sprite 的种类,这才是真正的类!

private:
    //大概率会继承自父类的量

    void setHp(int hp = 0);
    void setMaxVx(qreal maxVx = 0);
    void setMaxVy(qreal maxVy = 0);
    void setA(qreal a = 0);
    void setImage(QString im);
    void setType(QString type);
public:
    QHash<int, EffectSeed* > skillBar;//再多个技能都足够了
                                    //如何继承技能?
    void clearHash();
    const  QHash<int, EffectSeed* > &getSkillBar();
    SpriteObject* newSprite();
    int getWidth();
    int getHeight();
    int getHp();
    int getLogic();
    qreal getMaxVx();
    qreal getMaxVy();
    qreal getVx();
    qreal getVy();
    qreal getA();
    QString getImage();
    QString getName();
    QString getType();
    static void clearPool();
private:
    friend class BreedFactury;
    void setInitial(QString name, Breed *parent,
                     QString image = "",
                    qreal maxVx = 0, qreal maxVy = 0,qreal a = 0,
                   int hp = 0);
     //讲道理真的会有人这么弄吗
    void setIniVelo(qreal vx, qreal vy);
    void setLogic(int type = 0);
    void setHeight(int h);
    void setWidth(int w);
    void addSkill(const EffectSeed & seed);
    Breed();
    ~Breed();
private:
    int width;
    int height;
    int maxHp_;//表示最大血量,现在先不区分最大血量和初始血量
    int logicType;//1 就是鱼的逻辑 , 0 是父亲的逻辑
    qreal maxVx_;
    qreal maxVy_;
    qreal vx_ = 0;
    qreal vy_ = 0;
    qreal a_;
    QString image_;
    Breed* parent_ = nullptr;
    QString name_;
    QString type_;//type 表示它是什么种族的, name表示他的真名从而为子类继承帮忙
};
#endif // BREED_H
