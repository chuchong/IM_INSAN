#include "mainwindow.h"
#include "ui_mainwindow.h"

//加载页面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    //    this->paintComponent = new ComponentPaint(this);
    gVariantIns = GVariantKeeper::getInstance();
    //TODO 这里加上判断,区分一二周目
    machine = GVariantKeeper::getFirstWeekMachine();

    currScene = machine->getStartScene();
    currScene -> load();
    currScene->setSceneRect(0,0,900,600);
    //TODO:注意的是每个不同的SCENE的指针也不一样,所以这个connect要在change的时候也要写
    connectToScene();
    update();
}

MainWindow::~MainWindow()
{
//
    delete ui;
}
//以下为利用多线程来显示加载页面的函数*3
//void MainWindow::receiveLoadScreen(Scene * newOb)
//{
//    changeSceneFromThread(newOb);
//}

void MainWindow::handleConditions(S_CONDITIONS conditions)
{
    if(conditions == QSet<int>({CONDITION_QUIT}))
        this->close();


    //if判断用不用多线程
    if( machine->getNextScene(conditions)!= nullptr){
        if(loadThread == nullptr  && machine->getNextScene(conditions)->getSceneType() == BATTLE){
            loadThread = new LoadingThread(this);
            connect(loadThread, SIGNAL(finished()),
                    loadThread, SLOT(deleteLater()));
            connect(loadThread, SIGNAL(sendFinishedScreen(Scene*)),
                    this, SLOT(changeSceneFromThread(Scene*)));
            loadThread->setCondition(conditions);
            loadThread->setMachine(this->machine);
            if(!loadThread->isRunning())
                loadThread->start();
            //只能用repaint
            //此时currScene = loadingScene正在被加工,不能使用
            //已经试用了将currScene指向loadingScene,并把paint事件更改的方法
            //上面那个方法内存突然炸掉了...
            repaint();
            }
        else{
           changeSceneNoThread(machine->getNextScene(conditions));
           machine->apply(conditions);
        }
    }
}

void MainWindow::changeSceneFromThread(Scene *newScene)
{
    //这时因为load unload 费事才放到子线程中,所以不需要再用了
   //更改Scene 实际上实现的是一个自动机
    loadThread->requestInterruption();
    loadThread = nullptr;
    currScene->unload();
    currScene = newScene;
    currScene->getIn();
    connectToScene();
    update();
}

//-------以上为需要多线程的地方

void MainWindow::changeSceneNoThread(Scene *newScene){
    currScene->unload();
    currScene=newScene;
    currScene->load();
    currScene->getIn();
    connectToScene();
    update();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    qDebug()<< "mainwindow delete";
//    currScene->unload();
    gVariantIns->destroyInstance();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //当loading的时候,不能使用currScene,必须先判断是否指针为空
    if(loadThread == nullptr){
     ui->graphicsView->setScene(currScene);
     currScene->setSceneRect(0,0,900,600);
    }
    else{
     ui->graphicsView->setScene(gVariantIns->getLoadingScene());
    }
}

void MainWindow::start()
{
    //    currScene = new SceneStart();
}

void MainWindow::connectToScene(){
    connect(currScene, SIGNAL(sendCondition(S_CONDITIONS)),this, SLOT(handleConditions(S_CONDITIONS)));
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
    qDebug()<<"thread die";
    requestInterruption();
    quit();
    wait();
}

void LoadingThread::run()
{
    while (!isInterruptionRequested())
    { // 是否请求终止
       if(!changed){
//           if (sceneFromMain != nullptr)
//                sceneFromMain->unload();//不可以delete !!这是一切问题的根源
           Scene* newScene = machine->getNextScene(conditions);
           machine->apply(conditions);
           newScene->load();
           msleep(1000);//至少让人看到我写了加载页面
           emit sendFinishedScreen(newScene);
           changed = 1;
       }
       else{
           msleep(500);
       }
    }
}
