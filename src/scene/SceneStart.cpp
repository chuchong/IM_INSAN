#include "SceneStart.h"

SceneStart::SceneStart()
{
    sceneId = SCENE_START;
    background_url = ":/BG_STARTMENU";
}

void SceneStart::parseFromFile(QString j)
{
    QSettings config(j,QSettings::IniFormat);
    background_url = config.value("/background/url").toString();
    sceneId = config.value("/sceneId/id").toInt();
    qDebug()<<sceneId;
}


void SceneStart::redraw()
{

}

void SceneStart::load()
{
    sceneId = SCENE_START;

    BlockObject *bg = factury.getBG(background_url,900,600,0,0);
    this->allList.append(bg);
    this->background = bg;
    this->addItem(bg);
    bg->setZValue(0);
//    startTimer(100);

    BlockObject *startButton = factury.getButton(":/BUTTON_START",
                                            101, 28, 700, 400,
                                            CONDITION_START);
    qDebug() << startButton->pos().x() << startButton->pos().y();
    BlockObject *exitButton = factury.getButton(":/BUTTON_EXIT",
                                             101,28,700,500,
                                                CONDITION_QUIT);

    this->allList.append(startButton);
    allList.append(exitButton);

    buttons.append(startButton);
    buttons.append(exitButton);

    this->addItem(startButton);
    this->addItem(exitButton);

    startButton->setZValue(1);
    exitButton->setZValue(1);

    timerNum = startTimer(1000);
}

void SceneStart::unload()
{

    for(GameObject* iter:allList){
        delete iter;
//        removeItem(iter);
    }
    allList.clear();
    buttons.clear();
    disconnect();
    killTimer(timerNum);
}

void SceneStart::getIn()
{

}

void SceneStart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!buttons.isEmpty()){
        for(BlockObject* button: buttons){
            qDebug() << event->scenePos().x();
            qDebug() << event->scenePos().y();
            qDebug() << button->pos();
            if(button != nullptr && button->contains(event->scenePos())){
                    S_CONDITIONS buf = button->getCondition();
                    emit sendCondition(buf);
                    return;//!!否则两线程撞车
             }
         }
    }
}

void SceneStart::timerEvent(QTimerEvent *event)
{
    background->update();
}

void SceneStart::update()
{

}
