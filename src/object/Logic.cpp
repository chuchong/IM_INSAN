#include "Logic.h"

Logic::Logic(SpriteObject *ob):ob_(ob)
{

}

void Logic::run(SpriteObject *ob)
{
    qDebug()<<"run logic" << ob->getType();

}
