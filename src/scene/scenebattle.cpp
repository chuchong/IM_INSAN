#include "SceneBattle.h"

SceneBattle::SceneBattle()
{
    position = QPointF(0,0);
}

void SceneBattle::parseFromFile(QString url)
{

   QSettings config(url,QSettings::IniFormat);
    background_url = config.value("/background/url").toString();
    factury.parseFromJson(config.value("/breedfactury/url").toString());

}

void SceneBattle::update()
{

}

void SceneBattle::redraw()
{

}

void SceneBattle::load()
{
    background= factury.getBG(background_url,900,600,0,0);
    allList.push_back(background);
    addItem(background);
    timerId = startTimer(FRAME);

}

void SceneBattle::unload()
{
    qDebug() << "unload";
    for(auto iter: allList)
        delete iter;

    fishes.clear();
    allList.clear();
    baits.clear();
    factury.clearPool();
    clear();
    disconnect();
    killTimer(timerId);
}

void SceneBattle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //生成bait
    SpriteObject *bait = factury.getSpriteByTypeName(event->scenePos().x(),
                                                     event->scenePos().y(),
                                                     "bait");
    bait->setPos(event->scenePos());
    allList.append(bait);
    addItem(bait);
    baits.append(bait);
}

void SceneBattle::timerEvent(QTimerEvent *event)
{
    for(auto iter: allList){
        iter->run();
    }
    if(qrand() % 100 == 1){
        SpriteObject* fish = factury.getSpriteByTypeName(position.x(),
                                                         position.y(),
                                                         "fish");
        allList.append(fish);
        addItem(fish);
        fishes.append(fish);
    }
    for(auto iter : baits){
        qDebug() << iter->pos().y();
        if(iter->pos().y() > 600){
            iter->setHP(-1);
         }
     }
        //删怪了
   DeletePhase();


}
//看是否需要
void SceneBattle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    position = event->scenePos();
}

void SceneBattle::DeletePhase()
{
    for(int i = 0; i< baits.size();){

        if (baits[i]->isDead()){
            baits.removeAt(i);
        i --;
        }
        i ++;
    }

    for(int i = 0; i< fishes.size();){

        if (fishes[i]->isDead()){
            fishes.removeAt(i);
            qDebug()<<"one fish starves to death";
            i --;
        }
        i ++;
    }

    Scene::DeletePhase();
}

