#include "GVariantKeeper.h"
GVariantKeeper::Auto GVariantKeeper::auto_;
GVariantKeeper* GVariantKeeper::p_Instance = nullptr;
SceneStory *GVariantKeeper::loadingScene = nullptr;
SceneMachine *GVariantKeeper::firstWMachine =nullptr;
SceneMachine *GVariantKeeper::secondWMachine = nullptr;
std::mutex GVariantKeeper::mutex_;
QList<Scene *> GVariantKeeper::allScenes;
QList<S_CONDITIONS *> GVariantKeeper::allConditions;



GVariantKeeper::GVariantKeeper()
{
    //初始化那个Transition
    SceneStart *currScene = new SceneStart;
    allScenes.append(currScene);

    SceneStory *story1 = new SceneStory;
    allScenes.append(story1);
    story1->parseFromFile(":/configure/INI_STORY_1_1");

    S_CONDITIONS *cond = new S_CONDITIONS;
    allConditions.append(cond);

    cond->insert(CONDITION_DEBUG);
    Transition* debugTrans = new Transition(currScene,story1,*cond);

    QList<Transition>  *qli = new QList<Transition>();
    qli->append(*debugTrans);

    firstWMachine =new SceneMachine(*qli,currScene);//好烦啊,这些Machine里面的指针好容易漏出去
    secondWMachine =new SceneMachine(*qli,currScene);

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
    for(auto iter: allScenes)
        delete iter;
    allScenes.clear();
    for(auto iter: allConditions)
        delete iter;
    allConditions.clear();
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

