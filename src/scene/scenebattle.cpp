#include "SceneBattle.h"
#include "../object/ObjectSprite.h"
SpriteObject* SceneBattle::addSprite(QPointF point,QString name)
{
    SpriteObject* sprite = factury.getSpriteByTypeName(point.x(),
                                                        point.y(),
                                                         name);
    qDebug()<<"add" << name;
    assert(sprite != nullptr);
    allList.append(sprite);

    if(sprite->getType() == "money")
        moneyList.append(sprite);

    addItem(sprite);
    connect(sprite,&SpriteObject::generateSkill,
            this,&SceneBattle::addSkill);
    connect(sprite, &SpriteObject::generateSkillWithTargetRect,
            this, &SceneBattle::addSkillWithTargetRect);

    return sprite;
}



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
    moneyText = new QGraphicsSimpleTextItem();
    addItem(moneyText);
    fishes.append(addSprite(QPointF(600,540),"friend_saya"));

}

void SceneBattle::unload()
{
    qDebug() << "unload";
    for(auto iter: allList){
        delete iter;
//        removeItem(iter);
    }
    if(effectList.size() != 0){
        for(auto iter: effectList){
            delete iter;
        }
        effectList.clear();
    }

    if(aliens.size() != 0){
        for(auto iter: aliens){
            delete iter;
        }
        aliens.clear();
    }

    if(moneyList.size() != 0){
        for(auto iter: moneyList){
            delete iter;
        }
        moneyList.clear();
    }

    delete moneyText;
    fishes.clear();
    allList.clear();
    baits.clear();
    factury.clearPool();
    disconnect();
    killTimer(timerId);
}

void SceneBattle::getIn()
{
    timerId = startTimer(FRAME);
}

void SceneBattle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //生成bait
    position = event->scenePos();
    QPointF p2 = position;
    static bool bug = 0;
    if(!bug){
    QPointF p1 = position;
    bug = 1;

    SpriteObject* fish = addSprite(p1,"fish_little");
    fishes.append(fish);
    }
//鼠标点击的物体
    QList<SpriteObject*> selectList;
    for(auto iter:allList){
        SpriteObject* sprite = dynamic_cast<SpriteObject*> (iter);
        if(sprite!=nullptr && sprite->contains(position)){
                selectList.append(sprite);
        }
    }

    for(auto iter:selectList){
        //money
        int respond = iter->input(LOGIC_INPUT_CLICK);
        if(respond == OUTPUT_MONEY){
           iter->setHp(-1);
        }
        else if(respond == OUTPUT_ALIEN){
//            moveSpriteToPoint(iter,position);
         qreal newx = 2 * iter->getX() + iter->getWidth() - position.x();
         qreal newy = 2 * iter->getY()+ iter->getHeight() - position.y();

         iter->setPos(newx,newy);
         iter->update();
         return;
        }
    }


    SpriteObject*bait = addSprite(p2,"bait");
    baits.append(bait);
}

void SceneBattle::timerEvent(QTimerEvent *event)
{


    for(auto iter: allList){
//        iter->setPos(iter->getPosPoint());
        iter->run();
    }
    for(auto iter: effectList){
        iter->Happen();
        iter->setDead();
    }

    for(auto iter : baits){
        if(iter->pos().y() > 600){
            iter->setHP(-1);
         }
     }

    moneyText->setText(QString::number(money));
    //删怪了

   DeletePhase();


}
//看是否需要
void SceneBattle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    position = event->scenePos();
}

void SceneBattle::keyPressEvent(QKeyEvent *event)
{
    SpriteObject*bait = addSprite(position,"bait");
    baits.append(bait);

    SpriteObject * al = addSprite(position,"alien_2");
    sendAlienMessage();
    aliens.append(al);
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

    if(aliens.size() != 0){
        for(int i = 0; i< aliens.size();){
            if(aliens[i]->isDead()){
               aliens.removeAt(i);
                    i --;
                }
            i ++;
        }
        if(aliens.size() == 0)
            sendNoAlienMessage();
    }

    for(int i = 0; i< fishes.size();){

        if (fishes[i]->isDead()){
            fishes.removeAt(i);
            qDebug()<<"one fish starves to death";
            i --;
        }
        i ++;
    }

    for(int i = 0; i< moneyList.size();){

        if (moneyList[i]->isDead()){
            this->money += moneyList[i]->getMaxHp();
            moneyList.removeAt(i);
            qDebug()<<"one fish starves to death";
            i --;
        }
        i ++;
    }

    for(auto iter :moneyList){
        if(outOfRect(iter))
            iter->setHp(0);
    }

    for(int i = 0; i< effectList.size();){
        if(effectList[i]->isDead()){
            delete effectList[i];
            effectList.removeAt(i);
            i --;
        }
        i ++;
    }



    Scene::DeletePhase();
}

void SceneBattle::addSkillWithTargetRect(EffectSeed *seed, SpriteObject *from, const QRectF &rect)
{
    EffectInitialInfo i(*seed);
    i.bornPoint = from->pos();
    i.targetRect = rect;
    Effect* newEf = effectFactury.getEffect(from,this,i);
    effectList.append(newEf);
}

void SceneBattle::addSkill(EffectSeed *seed, SpriteObject *from)
{
    EffectInitialInfo i(*seed); i.bornPoint = from->pos();
    Effect* newEf = effectFactury.getEffect(from,this,i);
    effectList.append(newEf);
}

void SceneBattle::addSpriteFromName(QPointF point, QString name)
{
    addSprite(point, name);
}

void SceneBattle::aoeKill(QRectF aoeRect, QString killType)
{
    QGraphicsRectItem bufRec (aoeRect);
    this->addItem(&bufRec);
    auto intersectList = bufRec.collidingItems();
    if(intersectList.size() == 0)
        return;
    QList<SpriteObject*> selectList;
    for(auto iter : intersectList){
        SpriteObject* sprite = dynamic_cast<SpriteObject*> (iter);
        if(sprite!=nullptr){
            if(sprite->getType() == killType)
                selectList.append(sprite);
        }
    }

    if(selectList.size()!= 0){
        for(auto i :selectList){
            i->setHp(-1);
        }
    }
}

QList<SpriteObject *> SceneBattle::findTargetsInRect(QRectF rect, QString type)
{
    QGraphicsRectItem bufRec (rect);
    addItem(&bufRec);
    auto intersectList = bufRec.collidingItems();
    QList<SpriteObject *>objectList;

    for(auto iter: intersectList){
        SpriteObject * ob = dynamic_cast<SpriteObject *>(iter);
        if( ob != nullptr && ob->getType() == type)
            objectList.append(ob);
    }
    return objectList;
}

bool SceneBattle::healSprite(SpriteObject *object, int parameter)
{
    int result = object->input(LOGIC_INPUT_HEAL);
    if(result == OUTPUT_SUCCESS){
        object->HP() += parameter;
        return 1;
    }
    else
        return 0;
}

int SceneBattle::moveSpriteToPoint(SpriteObject *object, QPointF p)
{
    return 0;
}

void SceneBattle::sendAlienMessage()
{
    for(auto iter:fishes){
        iter->input(LOGIC_INPUT_DANGER);
    }
}

void SceneBattle::sendNoAlienMessage()
{
    for(auto iter:fishes){
        iter->input(LOGIC_INPUT_SAFE);
    }
}

bool SceneBattle::outOfRect(SpriteObject *ob)
{
    if(background->contains(ob->pos()))
        return 0;
    else
        return 1;
}

void SceneBattle::directOneToAnother(SpriteObject *mover, QString targetName)
{
    QList<SpriteObject*> selectList;
    for(auto iter : allList){
        SpriteObject* sprite = dynamic_cast<SpriteObject*> (iter);
        if(sprite!=nullptr){
            if(sprite->getType() == targetName)
                selectList.append(sprite);
        }
    }
    if(!selectList.isEmpty()){
        SpriteObject* target;
        int min_d = INT_MAX;//int 足够了吧
        for(auto i:selectList){
            int dis = spriteDis(mover, i);
            if(dis < min_d && dis > 1e-5){
                target = i;
                min_d = dis;
            }
        }
        mover->moveToPoint(target->pos());
        return;
    }
}

void SceneBattle::directOneToAnotherByName(SpriteObject *mover, QString targetName)
{
    QList<SpriteObject*> selectList;
    for(auto iter : allList){
        SpriteObject* sprite = dynamic_cast<SpriteObject*> (iter);
        if(sprite!=nullptr){
            if(sprite->getName() == targetName)
                selectList.append(sprite);
        }
    }
    if(!selectList.isEmpty()){
        SpriteObject* target;
        int min_d = INT_MAX;//int 足够了吧
        for(auto i:selectList){
            int dis = spriteDis(mover, i);
            if(dis < min_d && dis > 1e-5){
                target = i;
                min_d = dis;
            }
        }
        mover->moveToPoint(target->pos());
        return;
    }
}

int SceneBattle::spriteDis(SpriteObject *o1, SpriteObject *o2)
{
    return (o1->pos() - o2->pos()).manhattanLength();
}

