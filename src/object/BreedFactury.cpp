#include "BreedFactury.h"

BreedFactury::BreedFactury()
{

}

BlockObject *BreedFactury::getBG(QString image, int x, int y, qreal px, qreal py)
{
    BlockObject * o_ptr= new BlockObject();
    o_ptr-> setImage(image);
    o_ptr-> setPos(px, py);
    o_ptr-> setHP(HP_OF_BLOCK);
    return o_ptr;
}

BlockObject *BreedFactury::getButton(QString image, int x, int y, qreal px, qreal py, CONDITIONS_ID a_condi)
{
    BlockObject * o_ptr= new BlockObject();
    o_ptr-> setImage(image);
    o_ptr-> setPos(px, py);
    o_ptr-> setHP(HP_OF_BLOCK);
    o_ptr-> setCondition(QSet<int>::fromList({a_condi}));
    return o_ptr;
}

void BreedFactury::killBG(GameObject * o_ptr)
{
    o_ptr->setHP(0);
}
