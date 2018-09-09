#include "Scene.h"

Scene::Scene(QObject *parent):
    QGraphicsScene(parent)
{

}

void Scene::sortAndPaintPhase()
{
    qSort(allList.begin(),allList.end(),
          [](GameObject * ob_1, GameObject * ob_2)->bool{
        return ob_1->getRelativeHeight() > ob_2->getRelativeHeight();
                                            }
            );//根据相对高度排序
    for(auto iter : allList){
//        paintComp_->paint(iter);
    }
}

void Scene::DeletePhase()
{
    for(auto iter = allList.begin();iter != allList.end();){
        if((*iter)->isDead()){
            delete (*iter);
            allList.erase(iter ++);//!iter ++ 防止迭代器失效
        }
    }
}

void Scene::setBG(QString image, int x, int y, qreal px, qreal py)
{
    GameObject *bg = factury.getBG(image, x, y, px, py);
    allList.push_back(bg);
    background = dynamic_cast<BlockObject *>(bg);
}

void Scene::resetBG(QString image, int x, int y, qreal px, qreal py)
{
    GameObject *bg = factury.getBG(image, x, y, px, py);
    allList.push_back(bg);
    background = dynamic_cast<BlockObject *>(bg);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
