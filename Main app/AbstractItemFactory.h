#ifndef ABSTRACTITEMFACTORY_H
#define ABSTRACTITEMFACTORY_H

#include "item.h"


class AbstractItemFcatory
{

public:

    virtual Item* createItem(QString t, QString n) = 0;

};

#endif // ABSTRACTITEMFACTORY_H
