#include "itemfactory.h"


ItemFactory::ItemFactory()
{

}

Item *ItemFactory::createItem(QString t, QString n)
{
    if(t == "Book")
        return new BookItem(n);
    if(t == "Magazine")
        return new MagazineItem(n);
    return 0;
}

ItemFactory::~ItemFactory()
{

}
