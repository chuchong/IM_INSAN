#include "BreedFactury.h"

BreedFactury::BreedFactury()
{

}

BlockObject *BreedFactury::getBG(QString image, int x, int y, qreal px, qreal py)
{
    BlockObject * o_ptr= new BlockObject();
    o_ptr->setImage(image, x, y, px, py);
    o_ptr->setHP(HP_OF_BLOCK);
    return o_ptr;
}

void BreedFactury::killBG(GameObject * o_ptr)
{
    o_ptr->setHP(0);
}
