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


    BlockObject *button = factury.getBG(":/BUTTON_START", 101, 28, 0, 0);
    this->allList.append(button);
    buttons.append(button);
    this->addItem(button);
    button->setZValue(1);
}

void SceneStart::unload()
{

    for(GameObject* iter:allList){
        delete iter;
    }
    this->clear();
    allList.clear();
    buttons.clear();

}

void SceneStart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!buttons.isEmpty()){
        for(auto button: buttons){
            qDebug() << button->x();
            qDebug() << button->y();
            qDebug() << event->scenePos().x();
            qDebug() << event->scenePos().y();
            if(button->contains(event->scenePos())){
    //            this->unload();
                button->setPos(button->x() + 5,0);
                if(button->x() > 10){
                    S_CONDITIONS buf; buf.insert(CONDITION_DEBUG);
                    emit sendCondition(buf);
                }
            }
        }
    }
}

void SceneStart::update()
{

}
