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
    else if(sprite->getType() .startsWith( "fish"))
        fishes.append(sprite);
    else if(sprite->getType() == "bait")
        baits.append(sprite);
    else if(sprite->getType() == "friend")
        //TODO :CHECK
        fishes.append(sprite);
    else if(sprite->getType() == "alien")
        aliens.append(sprite);


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

SceneBattle::~SceneBattle(){
    factury.clearPool();
    qDebug() << "delete battle";/*this->unload();*/}

void SceneBattle::parseFromFile(QString url)
{

    QSettings config(url,QSettings::IniFormat);
    background_url = config.value("/background/url").toString();
    factury.parseFromJson(config.value("/breedfactury/url").toString());
    sceneId = config.value("/sceneid/id").toInt();
    qDebug()<<sceneId;
}

void SceneBattle::update()
{

}

void SceneBattle::redraw()
{

}

void SceneBattle::load()
{
    isEnd = 0;
    background= factury.getBG(background_url,900,600,0,0);
    allList.push_back(background);
    addItem(background);
//    timerId = startTimer(FRAME);
    moneyText = new QGraphicsSimpleTextItem();
    addItem(moneyText);
    if(hasSaya)
    fishes.append(addSprite(QPointF(600,530),"friend_saya"));

//    SpriteObject * n = factury.getSpriteByTypeName(100,0,"faker_fish");
//    addItem (n);
    money = 2000;
    maxBait = 1;
    damage = 100;
    moneyText->setPos(20,500);

//    uiBlocks.clear();
    addBlocks(24, 2);
    addBlocks(90,2);
    addBlocks(148,2);
    addBlocks(225,2);
    addBlocks(290,2);
    addBlocks(367,2);
    addBlocks(440,2);
    addBlocks(511,2);

//    for(int i = 0; i < 8; i ++)
//        blockIsDead[i] = 0;

}



void SceneBattle::addBlocks(int x, int y)
{
    QRectF r(0,0,50,50);
    r.moveTopLeft(QPointF(x,y));
    rects.append(r);
}

void SceneBattle::showWarning()
{
    addSprite(QPointF(400,300),"warning");
}

void SceneBattle::unload()
{
    qDebug() << "unload";
    for(auto iter: allList){
        delete iter;

    }
    if(effectList.size() != 0){
        for(auto iter: effectList){
            delete iter;
        }
        effectList.clear();
    }


     aliens.clear();
     moneyList.clear();
    delete moneyText;
    fishes.clear();
    allList.clear();
    baits.clear();

    disconnect();
    killTimer(timerId);
    killTimer(alienTime);
    rects.clear();

}

void SceneBattle::getIn()
{
    timerId = startTimer(FRAME);
    alienTime = startTimer(5000);
    this->update();

}

void SceneBattle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    bool is = rects[0].contains(QPointF(40,30));
    int a = 1+ is;
    for(int i =0; i < 8; i ++){
        if(rects[i].contains(event->scenePos())){
                clickBlock(i);
        }
    }

    //生成bait
    position = event->scenePos();

    if(position.y() > 100){
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
               return;
            }
            else if(respond == OUTPUT_ALIEN){
             iter->HP() -= damage;
             qreal newx = 2 * iter->getX() + iter->getWidth()/2 - position.x();
             qreal newy = 2 * iter->getY()+ iter->getHeight()/2 - position.y();

             iter->bounceBack();
             iter->setPos(newx,newy);
             iter->update();
             return;
            }
            else if(respond == OUTPUT_ALIEN_NO_EFFECT){
                return ;
            }
        }

        if(baits.size() < maxBait && money > 20){
            SpriteObject*bait = addSprite(position,baitNameMap[baitExp]);
            money -= 20;
        }
    }
//    else
//    {
//        int x = position.x() / 100;
//        clickBlock(x);
//    }

//    baits.append(bait);
}

void SceneBattle::timerEvent(QTimerEvent *event)
{
//    for(int i = 0; i < 8; i ++){
//        if(!blockIsDead[i] && money > conditions[i]){
//            uiBlocks[i]->input(LOGIC_INPUT_ACTIVATE);
//        }
//    }
    int id = event->timerId();
    if(timerId == id){

        for(auto iter: allList){
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

        moneyText->setText(QString::number(money) +"          最大baits 数:" +  QString::number(maxBait));
        //删怪了

       DeletePhase();

       if(money <= 0){
           emit sendCondition(QSet<int>::fromList({CONDITION_LOSE}));
        isEnd = 1;
       }
    }
    else if(alienTime == id){
        static int  times = 2;
        if(times % 4 == 0)
            showWarning();
        else if(times % 4 == 1){
            int x = qrand();
            int posx = x % 100 + 600;
            int posy = x % 100 + 400;
            int z = x % 2;
            QPointF pnow(posx,posy);
            if(z == 0){
                aliens.append(addSprite(pnow,"alien_1"));
                sendAlienMessage();
            }
            else{
                aliens.append(addSprite(pnow,"alien_2"));
                sendAlienMessage();
            }
        }
        times ++;
    }
}
//看是否需要
void SceneBattle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    position = event->scenePos();
}

void SceneBattle::keyPressEvent(QKeyEvent *event)
{
    if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
            if(e->key() == Qt::Key_Z)
            {
               aliens.append(addSprite(position,"alien_1"));
                sendAlienMessage();
//                baits.append(bait);
            }
            else if(e->key() == Qt::Key_C)
            {
                aliens.append(addSprite(position,"alien_2"));
                sendAlienMessage();
//                aliens.append(al);
            }
            else if(e->key() == Qt::Key_X)
            {
                money += 10000;
            }
            else if(e->key() == Qt::Key_A)
            {
                fishes.append(addSprite(QPointF(600,530),"friend_saya"));
            }
        }
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
            qDebug()<<"got a coin";
            i --;
        }
        else if(outOfRect(moneyList[i])){
            moneyList.removeAt(i);
            qDebug()<<"got a coin";
            i --;
        }
        i ++;
    }

//    for(int i = 0; i< 8; i ++){
//        if(blockIsDead[i] != 1 && uiBlocks[i]->isDead()){
//            blockIsDead[i] = 1;
//        }
//    }

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
    auto selectList = findTargetsInRect(aoeRect, killType);
    if(selectList.size()!= 0){
        for(auto i :selectList){
            i->setHp(-1);
        }
    }
}

void SceneBattle::aoeKillByClass(QRectF aoeRect, QString killClass)
{
    auto selectList = findTargetsInRectByClass(aoeRect, killClass);
    if(selectList.size()!= 0){
        for(auto i :selectList){
            i->setHp(-1);
        }
    }
}

void SceneBattle::aoeKillByName(QRectF aoeRect, QString killName)
{
    auto selectList = findTargetsInRectByName(aoeRect, killName);
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

QList<SpriteObject *> SceneBattle::findTargetsInRectByClass(QRectF rect, QString className)
{
    QGraphicsRectItem bufRec (rect);
    addItem(&bufRec);
    auto intersectList = bufRec.collidingItems();
    QList<SpriteObject *>objectList;

    for(auto iter: intersectList){
        SpriteObject * ob = dynamic_cast<SpriteObject *>(iter);
        if( ob != nullptr && ob->getName().startsWith(className))
            objectList.append(ob);
    }
    return objectList;
}

QList<SpriteObject *> SceneBattle::findTargetsInRectByName(QRectF rect, QString name)
{
    QGraphicsRectItem bufRec (rect);
    addItem(&bufRec);
    auto intersectList = bufRec.collidingItems();
    QList<SpriteObject *>objectList;

    for(auto iter: intersectList){
        SpriteObject * ob = dynamic_cast<SpriteObject *>(iter);
        if( ob != nullptr && ob->getName() == name)
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

//int SceneBattle::moveSpriteToPoint(SpriteObject *object, QPointF p)
//{

//    return 0;
//}

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
            //TODO check 能否正常工作
            if(sprite->getType().startsWith(targetName))
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

//碰到了哪一个格子
void SceneBattle::clickBlock(int i)
{
    SpriteObject * o;
    switch(i){
    case 0:
        if(money > 100){
            o = addSprite(QPointF(100,110),"fish_little");
            money -= 100;
        }
        break;
    case 1:
        if(money > 2000 && baitExp <= 1){
            money -= 2000;
            baitExp += 1;
        }
        break;
    case 2:
        if(money > 400 && maxBait <= 6){
            money -= 400;
            maxBait += 1;
        }
        break;
    case 3:
        if(money > 1000){
            money -= 1000;
            o = addSprite(QPointF(300,110),"fish_meat");
        }
        break;
    case 4:
        if(money > 5000){
            money -= 5000;
            o = addSprite(QPointF(300,110),"fish_mama");
        }
        break;
    case 5:
        if(money > 10000){
            money -= 10000;
            o = addSprite(QPointF(300,110),"fish_big_meat");
        }
        break;
    case 6:
        if(money > 4000){
            money -= 4000;
            damage += 100;
        }
        break;
    case 7:
        if(money > 20000){
            money -= 20000;
            emit sendCondition(QSet<int>::fromList({CONDITION_WIN}));
            isEnd = 1;
        }
        break;
    case 8:
        money -= 50000;
    default:
        break;
    };
}
