#include "SceneStory.h"

SceneStory::SceneStory()
{
}

void SceneStory::parseFromFile(QString j)
{
    QSettings config(j,QSettings::IniFormat);
    QString background_url = config.value("/background/url").toString();
    QString script = config.value("/script/url").toString();

    background = factury.getBG(background_url,900,600,0,0);
    this->allList.append(background);
    background->setZValue(0);
    this->addItem(background);
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

}

void SceneStory::unload()
{

}


