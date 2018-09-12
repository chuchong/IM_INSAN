#include "GVariantKeeper.h"
GVariantKeeper::Auto GVariantKeeper::auto_;
GVariantKeeper* GVariantKeeper::p_Instance = nullptr;
SceneStory *GVariantKeeper::loadingScene = nullptr;
SceneMachine *GVariantKeeper::firstWMachine =nullptr;
SceneMachine *GVariantKeeper::secondWMachine = nullptr;
std::mutex GVariantKeeper::mutex_;
QList<Scene *> GVariantKeeper::allScenes;
//QList<S_CONDITIONS *> GVariantKeeper::allConditions;
QList<Transition *> GVariantKeeper::allTransitions;


GVariantKeeper::GVariantKeeper()
{
    //初始化那个Transition
    SceneStart *startScene = new SceneStart;
    allScenes.append(startScene);

    SceneStory *story1 = new SceneStory;
    allScenes.append(story1);
    story1->parseFromFile(":/configure/INI_STORY_1_1");

    SceneBattle *battle1 = new SceneBattle;
    allScenes.append(battle1);
    battle1->parseFromFile(":/configure/INI_BATTLE_1");

    Transition *debugTrans = new Transition
                         (startScene,
                          story1,
                          QSet<int>::fromList({CONDITION_START}));
    allTransitions.append(debugTrans);

    Transition *debugTrans1 = new Transition
                         (story1,
                          battle1,
                          QSet<int>::fromList({CONDITION_START}));
    allTransitions.append(debugTrans1);

    QList<Transition*>  qli;
    qli.append(debugTrans);
    qli.append(debugTrans1);

//    firstWMachine =new SceneMachine(qli,startScene);//好烦啊,这些Machine里面的指针好容易漏出去
    secondWMachine =new SceneMachine(qli,startScene);
    //debug
    firstWMachine = new SceneMachine(qli,startScene);

    //以上的都要给我活着
    //!!!!TODO 弄好这些Scene*的析构 和初始化,全部都要是获得

    loadingScene = new SceneStory();
    allScenes.append(loadingScene);
    loadingScene->parseFromFile(":/configure/INI_LOADING");
    loadingScene->load();
}

GVariantKeeper::~GVariantKeeper()
{
    delete firstWMachine;
    delete secondWMachine;
    foreach(auto var,allTransitions)
        delete var;
    foreach(auto var, allScenes)
        delete var;

    allScenes.clear();
//    allConditions.clear();
    allTransitions.clear();
}


GVariantKeeper *GVariantKeeper::getInstance()
{
    if(p_Instance == nullptr){
        std::lock_guard<std::mutex> guard(mutex_);
        //以上线程安全保护
        if(p_Instance == nullptr){
            p_Instance = new GVariantKeeper;
        }
    }
    return p_Instance;
}

SceneMachine *GVariantKeeper::getFirstWeekMachine()
{
    return firstWMachine;
}

SceneMachine *GVariantKeeper::getSecondWeekMachine()
{
    return secondWMachine;
}

Scene *GVariantKeeper::getLoadingScene()
{
    return loadingScene;
}

void GVariantKeeper::destroyInstance()
{
    if(p_Instance != nullptr){
        delete p_Instance;
        p_Instance = nullptr;
    }
}

GVariantKeeper::Auto::~Auto()
{
    destroyInstance();
}

