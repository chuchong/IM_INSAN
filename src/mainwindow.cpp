#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->paintComponent = new ComponentPaint(this);
    this->objManager = new ObjectManager(paintComponent);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //TODO 注释以下代码,代码仅供调试
    objManager->setBG(":/BG_STARTMENU",900,600,0,0);
    objManager->sortAndPaintPhase();
}
