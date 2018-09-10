#include "SceneStory.h"

SceneStory::SceneStory()
{
}

void SceneStory::parseFromFile(QString j)
{
    QSettings config(j,QSettings::IniFormat);
    background_url = config.value("/background/url").toString();
    this->script_url = config.value("/script/url").toString();

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
    delete background;
    delete script;
}

void SceneStory::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!script->showNextLine())
        1==1;
}


