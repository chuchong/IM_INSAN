#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->paintComponent = new ComponentPaint(this);
    this->objManager = new ObjectManager(paintComponent);
    connect(&loadThread, SIGNAL(finished()),
            &loadThread, SLOT(deleteLater()));
    connect(&loadThread, SIGNAL(sendFinishedScreen(ObjectManager*)),
            this, SLOT(receiveLoadScreen(ObjectManager*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//以下为利用多线程来显示加载页面的函数*2
void MainWindow::receiveLoadScreen(ObjectManager *newOb)
{
    delete objManager;
    objManager = newOb;
    update();

}

void MainWindow::changeScene(Scene *newScene)
{
   //更改Scene 实际上实现的是一个自动机
    if(0/*TODO 何时显示loading screen*/){
        if(!loadThread.isRunning())
            loadThread.start();
        //TODO:objManager变为加载中或者接受加载页面
        }

   if (currScene != nullptr)
      currScene->unload();
    newScene->load();
    currScene = newScene;
}
//-------以上为需要多线程的地方

void MainWindow::paintEvent(QPaintEvent *event)
{
    //TODO 注释以下代码,代码仅供调试
    objManager->setBG(":/BG_STARTMENU",900,600,0,0);
    objManager->sortAndPaintPhase();
}

//-----------以下为loadingthread所用
LoadingThread::LoadingThread(QObject *parent){}

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
       //msleep(1000)//至少让人看到我写了加载页面
    }
}
