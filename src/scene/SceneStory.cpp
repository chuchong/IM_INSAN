#include "SceneStory.h"

SceneStory::SceneStory(QString url)
{
    parseFromFile(url);
}

void SceneStory::parseFromFile(QString j)
{
    QSettings config(j,QSettings::IniFormat);
    QString background = config.value("/background/url").toString();
    QString script = config.value("/script/url").toString();

    qDebug()<< background << script;
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
