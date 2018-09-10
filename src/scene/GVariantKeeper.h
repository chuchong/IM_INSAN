#ifndef GVARIANTKEEPER_H
#define GVARIANTKEEPER_H
//这是一个负责管理全局变量的类,单例模式
#include <iostream>
#include <mutex>
#include <QList>
#include <QSet>
#include "SceneMachine.h"
#include "Scene.h"
#include "SceneBattle.h"
#include "SceneSelect.h"
#include "SceneStory.h"
#include "SceneStart.h"
#include "../Constant.h"

class GVariantKeeper
{
private://防止外用
    explicit GVariantKeeper();
    ~GVariantKeeper();
    GVariantKeeper(const GVariantKeeper &) = delete;
    GVariantKeeper& operator=(const GVariantKeeper &) = delete;
//    template void cleanPointer(T* t_pointer){
//        if(T != nullptr){
//            delete t_pointer;
//            pointer == nullptr;
//        }
//    }应该没必要 因为不用了
public:
    static GVariantKeeper *getInstance();
    static SceneMachine *getFirstWeekMachine();
    static SceneMachine *getSecondWeekMachine();
    static Scene *getLoadingScene();
    static void destroyInstance();
private://这是单例
    static GVariantKeeper *p_Instance;
    class Auto;//自动释放
    static Auto auto_;
private://这里以下的不用考虑析构
    static std::mutex mutex_;
    static SceneStory *loadingScene;//loadingScene可以多做几个,
private://这里以下的要考虑他们的析构
    static SceneMachine *firstWMachine;//一周目所有的自动机
    static SceneMachine *secondWMachine;//二周目所有的自动机
    static QList<Scene*> allScenes;//负责所有Scene的析构
    static QList<S_CONDITIONS*> allConditions;
};

class GVariantKeeper::Auto{
public:
    ~Auto();
};
#endif // GVARIANTKEEPER_H
