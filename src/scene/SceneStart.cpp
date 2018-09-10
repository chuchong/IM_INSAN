#include "SceneStart.h"

SceneStart::SceneStart()
{

}

void SceneStart::parseFromFile(QString j)
{

}


void SceneStart::redraw()
{

}

void SceneStart::load()
{
    sceneId = SCENE_START;

    BlockObject *bg = factury.getBG(":/BG_STARTMENU",900,600,0,0);
    this->allList.append(bg);
    this->background = bg;
    this->addItem(bg);
    bg->setZValue(0);


    BlockObject *startButton = factury.getButton(":/BUTTON_START",
                                            101, 28, 700, 400,
                                            CONDITION_START);
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
}

void SceneStart::unload()
{

    for(GameObject* iter:allList){
        delete iter;
    }
    this->clear();
    allList.clear();
    buttons.clear();
    disconnect();

}

void SceneStart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!buttons.isEmpty()){
        for(BlockObject* button: buttons){
            qDebug() << event->scenePos().x();
            qDebug() << event->scenePos().y();
            if(button != nullptr && button->contains(event->scenePos())){
                    S_CONDITIONS buf = button->getCondition();
                    emit sendCondition(buf);
//???                    return;//!!否则两线程撞车
             }
         }
    }
}

void SceneStart::update()
{

}
