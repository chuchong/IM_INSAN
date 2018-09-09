#include "mainwindow.h"
#include "ui_mainwindow.h"
SceneStory* MainWindow::loadingScene;


//加载页面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->paintComponent = new ComponentPaint(this);


    loadingScene = new SceneStory();
    loadingScene->parseFromFile(":/configure/INI_STORY_1");

    //初始化那个Transition
    //!!!!TODO 弄好这些Scene*的析构 和初始化,全部都要是获得
    currScene = new SceneStart();
    S_CONDITIONS *cond = new S_CONDITIONS;
    cond->insert(CONDITION_DEBUG);
    Transition* debugTrans = new Transition(currScene,currScene,*cond);
    QList<Transition>  *qli = new QList<Transition>();
    qli->append(*debugTrans);
    machine =new SceneMachine(*qli,currScene);
    //以上的都要给我活着

    currScene -> load();
    currScene->setSceneRect(0,0,900,600);
    loadThread = new LoadingThread(this);
//注意的是每个不同的SCENE的指针也不一样,所以这个connect要完全
    connect(currScene, SIGNAL(sendCondition(S_CONDITIONS)),
            this, SLOT(handleConditions(S_CONDITIONS)));

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//以下为利用多线程来显示加载页面的函数*3
void MainWindow::receiveLoadScreen(Scene * newOb)
{
    changeScene(newOb);
}

void MainWindow::handleConditions(S_CONDITIONS conditions)
{
    if(currScene->getSceneId() == SCENE_START/*TODO 何时显示loading screen*/){
        loadThread = new LoadingThread(this);
        connect(loadThread, SIGNAL(finished()),
                loadThread, SLOT(deleteLater()));
        connect(loadThread, SIGNAL(sendFinishedScreen(Scene*)),
                this, SLOT(receiveLoadScreen(Scene*)));
        loadThread->setCondition(conditions);
        loadThread->setMachine(this->machine);
        loadThread->setScene(currScene);
        if(!loadThread->isRunning())
            loadThread->start();
        //TODO:objManager变为加载中或者接受加载页面
        //此时currScene = loadingScene正在被加工,不能使用
        repaint();
        }
}

void MainWindow::changeScene(Scene *newScene)
{

   //更改Scene 实际上实现的是一个自动机
    currScene = newScene;
    loadThread->requestInterruption();
    loadThread = nullptr;
    update();

}
//-------以上为需要多线程的地方

void MainWindow::paintEvent(QPaintEvent *event)
{
    //当loading的时候,不能使用currScene,必须先判断是否指针为空
    if(loadThread == nullptr || loadThread->isRunning() == false){
     ui->graphicsView->setScene(currScene);
     currScene->setSceneRect(0,0,900,600);
    }
    else{
     ui->graphicsView->setScene(loadingScene);
    }
}

void MainWindow::start()
{
//    currScene = new SceneStart();
}

//-----------以下为loadingthread所用
LoadingThread::LoadingThread(QObject *parent):
QThread(parent){}

void LoadingThread::setCondition(S_CONDITIONS condi)
{
    this->conditions = condi;
}

void LoadingThread::setMachine(SceneMachine *m)
{
    this->machine = m;
}

void LoadingThread::setScene(Scene * scene)
{
    this->sceneFromMain = scene;
}

LoadingThread::~LoadingThread()
{
    //以下是来自
    //https://blog.csdn.net/liang19890820/article/details/52186626
    //推荐的结束方法
    requestInterruption();
    quit();
    wait();
}

void LoadingThread::run()
{
    while (!isInterruptionRequested())
    { // 是否请求终止
       if(!changed){
           if (sceneFromMain != nullptr)
                sceneFromMain->unload();//不可以delete
           sceneFromMain = machine->getNextScene(conditions);
           sceneFromMain->load();
           msleep(1000);//至少让人看到我写了加载页面
           emit sendFinishedScreen(sceneFromMain);
           changed = 1;
       }
       else{
           msleep(500);
       }
    }
}
