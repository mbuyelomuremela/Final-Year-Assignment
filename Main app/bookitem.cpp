#include "bookitem.h"


BookItem::BookItem(QString n)
    :Item(n)
{

}

QString BookItem::getType() const
{
    return "Book";
}

BookItem::~BookItem()
{

}
