//Scene是指一个场景
#ifndef SCENE_H
#define SCENE_H

#include <QObject>
class Scene
{
public:
    Scene();
    virtual void parseFromJason(QString j) = 0;
    virtual void update() = 0;
    virtual void redraw() = 0;
    virtual void load() = 0;
    virtual void unload() = 0;
};

#endif // SCENE_H
