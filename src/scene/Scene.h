//Scene是指一个场景
#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "../Constant.h"
class Scene:public QObject
{
    Q_OBJECT
private:
    SCENE_TYPE sceneType;
public:
    Scene();

    //从本地文档中读取配置文件,大体上包含json ini
    virtual void parseFromFile(QString j) = 0;
    virtual void update() = 0;//逻辑
    virtual void redraw() = 0;//绘制
    virtual void load() = 0;
    virtual void unload() = 0;
};

#endif // SCENE_H
