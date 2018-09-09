//负责管理Scene的自动机,因为有时mainwindow要多线程加载所以和mainwindow分开
//他和其他类最好可以通过Qobject 的信号和槽来通讯
//如你所见,这里存在一个很难处理的问题,那就是getNextScene时返回的是指针
//--也就是说一开始存放好的scene外界不能delete
//--但外界却能更改scene,也就是说这个只能靠默契
#ifndef SCENEMACHINE_H
#define SCENEMACHINE_H

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
    ~Transition(){
//        delete from;
//        delete to;
    }
};
class SceneMachine : public QObject
{
    Q_OBJECT
private:
    QList<Transition> transitions;
    Scene *current;
public:
    explicit SceneMachine(QList<Transition> trans,
                          Scene *start,
                          QObject *parent = nullptr)
        :transitions(trans),
          current(start),
          QObject(parent){

    }
    Scene *getNextScene(S_CONDITIONS conditions){
        for(Transition transition : transitions){
            bool currentMatches = transition.from->equal(current);
            bool conditionMatches = transition.consitions.operator ==(conditions);
            if(currentMatches && conditionMatches){
                return transition.to;
            }
        }
        return nullptr;
    }
    ~SceneMachine(){
        //do not delete current;
    }

signals:

public slots:
};

#endif // SCENEMACHINE_H
