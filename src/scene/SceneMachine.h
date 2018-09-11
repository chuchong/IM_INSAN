//负责管理Scene的自动机,因为有时mainwindow要多线程加载所以和mainwindow分开
//他和其他类最好可以通过Qobject 的信号和槽来通讯
//如你所见,这里存在一个很难处理的问题,那就是getNextScene时返回的是指针
//--也就是说一开始存放好的scene外界不能delete
//--但外界却能更改scene,也就是说这个只能靠默契
//以上已经修改了一下,现在Scene只能在栈上,且运行时不能delete了
#ifndef SCENEMACHINE_H
#define SCENEMACHINE_H
#include <QtDebug>
#include <QObject>
#include <QSet>
#include <QList>
#include "../Constant.h"
#include "Scene.h"
struct Transition{
    Scene *from;
    Scene *to;
    S_CONDITIONS consitions;//SConditions
    Transition(Scene *f, Scene *t, S_CONDITIONS sc):
    from(f),to(t),consitions(sc){

    }
private:
    friend class GVariantKeeper;//负责让他帮忙析构
    ~Transition(){//他不能去delete,因为这指针不属于他
    qDebug() << "delete transition";
    }
};
class SceneMachine : public QObject
{
    Q_OBJECT
private:
    Scene *start_;
    Scene *current;
    QList<Transition *> transitions;//不用指针的话会被自动析构
public:
    explicit SceneMachine(QList<Transition *> trans,
                          Scene *start,
                          QObject *parent = nullptr)
        : start_(start),
          current(start),
          transitions(trans),
          QObject(parent){

    }
    Scene *getStartScene(){
        return start_;
    }
    void apply(S_CONDITIONS conditions){
        current = getNextScene(conditions);
    }
    Scene *getNextScene(S_CONDITIONS conditions){
        for(Transition* transition : transitions){
            bool currentMatches = transition->from->equal(current);
            bool conditionMatches = transition->consitions.operator ==(conditions);
            if(currentMatches && conditionMatches){
                return transition->to;
            }
        }
        return nullptr;
    }
    ~SceneMachine(){
        qDebug() << "delete machine";      //do not delete current;
    }

signals:

public slots:
};

#endif // SCENEMACHINE_H
