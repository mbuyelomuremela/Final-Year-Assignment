#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "AbstractItemFactory.h"
#include "bookitem.h"
#include "magazineitem.h"


class ItemFactory : public AbstractItemFcatory
{

public:

    ItemFactory();

    Item* createItem(QString t, QString n) override;

    ~ItemFactory();
};

#endif // ITEMFACTORY_H
