#include "item.h"


Item::Item(QString n)
    :name(n)
{
}

QString Item::getItemName() const
{
    return name;
}

QString Item::getType() const
{
    return "Uknown";
}

Item::~Item()
{

}
