#include "BreedFactury.h"

BreedFactury::BreedFactury()
{

}

GameObject *BreedFactury::getBG(QString image, int x, int y, qreal px, qreal py)
{
    GameObject * o_ptr= new BlockObject(image, x, y, px, py);
    o_ptr->setHP(HP_OF_BLOCK);
    return o_ptr;
}

void BreedFactury::killBG(GameObject * o_ptr)
{
    o_ptr->setHP(0);
}
