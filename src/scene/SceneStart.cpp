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
    BlockObject *bg = factury.getBG(":/BG_STARTMENU",900,600,0,0);
    this->allList.append(bg);
    this->background = bg;
    this->addItem(bg);
}

void SceneStart::unload()
{

}

void SceneStart::update()
{

}
