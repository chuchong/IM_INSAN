#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SceneManager *g_sceneManager = SceneManager::getInstance();

}

MainWindow::~MainWindow()
{
    delete ui;
}
