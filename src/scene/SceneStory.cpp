#include "SceneStory.h"

SceneStory::SceneStory()
{
}

void SceneStory::parseFromFile(QString j)
{
    QSettings config(j,QSettings::IniFormat);
    background_url = config.value("/background/url").toString();
    this->script_url = config.value("/script/url").toString();
    this->sceneId = config.value("/sceneid/id").toInt();
        qDebug()<<sceneId;
//    qDebug() << background_url << script;
}

void SceneStory::update()
{

}

void SceneStory::redraw()
{

}

void SceneStory::load()
{
    background = factury.getBG(background_url,900,600,0,0);
    this->allList.append(background);
    background->setZValue(0);
    this->addItem(background);

    script = new ObjectScript;
    script->setScriptFromText(script_url);
    this->addItem(script);
}

void SceneStory::unload()
{
    for(GameObject* iter : allList){
        delete iter;
//        removeItem(iter);不需要,自动remove了
    }
    allList.clear();
    delete script;
//    removeItem(script);
    disconnect();
}

void SceneStory::getIn()
{

}

void SceneStory::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(script != nullptr){
        if(!script->showNextLine()){
            S_CONDITIONS battle; battle.insert(CONDITION_START);
            emit sendCondition(battle);
            return;//!return is important
        }
    }
}



