#include "magazineitem.h"


MagazineItem::MagazineItem(QString n)
    :Item(n)
{

}

QString MagazineItem::getType() const
{
    return "Magazine";
}

MagazineItem::~MagazineItem()
{

}
