//#include "ObjectManager.h"

//ObjectManager::ObjectManager(ComponentPaint *paintComp):paintComp_(paintComp)
//{
//    QList<GameObject *> allList();
//    //分项记录各类Object
//    QList<BlockObject *> buttonsList();
//    BlockObject *background;
//    QList<SpriteObject *> fishList();
//    QList<SpriteObject *> enemiesList();
//    QList<SpriteObject *> friendsList();
//    QList<SpriteObject *> bonusList();
//    SpriteObject * boss;
//    //技能我将其和Object分开了
//    QList<EffectContainer *> skillsList();
//}

//void ObjectManager::sortAndPaintPhase()
//{
//    qSort(allList.begin(),allList.end(),
//          [](GameObject * ob_1, GameObject * ob_2)->bool{
//        return ob_1->getRelativeHeight() > ob_2->getRelativeHeight();
//                                            }
//            );//根据相对高度排序
//    for(auto iter : allList){
//        paintComp_->paint(iter);
//    }
//}

//void ObjectManager::DeletePhase()
//{

//    for(auto iter = allList.begin();iter != allList.end();){
//        if((*iter)->isDead()){
//            delete (*iter);
//            allList.erase(iter ++);//!iter ++ 防止迭代器失效
//        }
//    }
//}

//void ObjectManager::setBG(QString image, int x, int y, qreal px, qreal py)
//{
//    GameObject *bg = factury.getBG(image, x, y, px, py);
//    allList.push_back(bg);
//    background = dynamic_cast<BlockObject *>(bg);
//}

//void ObjectManager::resetBG(QString image, int x, int y, qreal px, qreal py)
//{
//    if(background != nullptr){
//        factury.killBG(background);
//        background = nullptr;
//    }
//    setBG(image, x, y, px, py);
//}
