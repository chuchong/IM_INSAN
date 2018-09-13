#include "BreedFactury.h"

void BreedFactury::clearPool()
{
   QHash<QString, Breed*>::Iterator i;
   for(i=breedPool.begin(); i != breedPool.end(); i ++) {
       delete i.value();
   }
   breedPool.clear();
}


void BreedFactury::parseFromJson(QString url)
{
    QFile loadFile(url);

     if(!loadFile.open(QIODevice::ReadOnly))
     {
         qDebug() << "could't open projects json";
         return;
     }

     QByteArray allData = loadFile.readAll();
     loadFile.close();

     QJsonParseError json_error;
     QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

     if(json_error.error != QJsonParseError::NoError)
     {
         assert(json_error.error == QJsonParseError::NoError);
         qDebug() << "json error!";
         return;
     }
    //以上为初始化过程
     //TODO 分开初始化不同的东西
     QJsonObject rootObj = jsonDoc.object();
     QJsonArray a = rootObj.value("x").toArray();
    //详见qt教程
     for(int i =0; i < a.size(); i ++){
         QJsonValue va(a[i]);
         QJsonObject sprite = va.toObject();
         QString image = sprite.value("image").toString();
         QString name = sprite.value("name").toString();
         QString parent = sprite.value("parent").toString();
         int hp = sprite.value("hp").toInt();
         qreal maxVx = sprite.value("maxVx").toDouble();
         qreal maxVy = sprite.value("maxVy").toDouble();
         qreal a = sprite.value("a").toDouble();
         int logic = sprite.value("logic").toInt();
         qreal vx = sprite.value("vx").toDouble();
         qreal vy = sprite.value("vy").toDouble();
         int width = sprite.value("width").toInt();
         int height = sprite.value("height").toInt();
         QString type = sprite.value("type").toString();
         Breed* breed = addBreeds(name,parent,image,maxVx,maxVy,a,hp,vx,vy,logic);
         assert( breed!= nullptr);
         breed->setHeight(height);
         breed->setWidth(width);
         breed->setType(type);

         QJsonArray skills = sprite.value("skills").toArray();
         for(int i = 0; i < skills.size(); i ++){
            QJsonObject aSkill = skills[i].toObject();
            QString name = aSkill.value("name").toString();
            QString to = aSkill.value("to").toString();
            int num = aSkill.value("number").toInt();
            bool inherit = aSkill.value("inherit").toBool();
            int parameter = aSkill.value("parameter").toInt();
            EffectSeed seed(name,to,num,inherit,parameter);
            breed->addSkill(seed);
         }

     }
}

Breed* BreedFactury::addBreeds(QString name, QString parent, QString image,
                             qreal maxVx, qreal maxVy, qreal a,
                             int hp,
                             qreal vx , qreal vy,
                             int logic){
    Breed *pa = nullptr;
    if(breedPool.contains(parent)){
       pa = breedPool[parent];
    }
    Breed * kid = new Breed();
    kid->setInitial(name,pa,image,maxVx,maxVy,a,hp);
    kid->setIniVelo(vx,vy);
    kid->setLogic(logic);
    breedPool.insert(name, kid);
    qDebug() << name;
    return kid;
}

SpriteObject *BreedFactury::getSpriteByTypeName(int px, int py, QString typeName){
    qDebug()<< typeName;
    assert(breedPool.contains(typeName));
   SpriteObject* ob = new SpriteObject(*breedPool[typeName]);
    ob->setPos(px,py);
    ob->setZValue(2);
    return ob;
}

BreedFactury::BreedFactury()
{

}

BreedFactury::~BreedFactury(){
    qDebug()<<"delete factury";
}



BlockObject *BreedFactury::getBG(QString image, int x, int y, qreal px, qreal py)
{
    BlockObject * o_ptr= new BlockObject();
    o_ptr-> setImage(image);
    o_ptr-> setPos(px,py);
    o_ptr-> setHP(HP_OF_BLOCK);
    o_ptr-> setRect(x,y);
    o_ptr-> setZValue(0);
    return o_ptr;
}

BlockObject *BreedFactury::getButton(QString image, int x, int y, qreal px, qreal py, CONDITIONS_ID a_condi)
{
    BlockObject * o_ptr= new BlockObject();
    o_ptr-> setImage(image);
    o_ptr-> setPos(px, py);
    o_ptr-> setHP(HP_OF_BLOCK);
    o_ptr-> setCondition(QSet<int>::fromList({a_condi}));
    o_ptr-> setRect(x,y);
    o_ptr-> setZValue(1);
    return o_ptr;
}

void BreedFactury::killBG(GameObject * o_ptr)
{
    o_ptr->setHP(0);
}
