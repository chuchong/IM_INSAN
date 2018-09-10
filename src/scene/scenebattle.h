#ifndef SCENEBATTLE_H
#define SCENEBATTLE_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "Scene.h"

class SceneBattle : public Scene
{
private:
    SCENE_ID next;//

public:
    SceneBattle();
    ~SceneBattle(){ this->unload();}
    virtual void parseFromFile(QString j);
    virtual void update();
    virtual void redraw();
    virtual void load();
    virtual void unload();
    virtual SCENE_TYPE getSceneType(){
        return BATTLE;
    }
//    virtual Scene *duplicateScene(Scene *);
};

#endif // SCENEBATTLE_H
