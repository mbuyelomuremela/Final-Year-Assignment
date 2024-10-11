#ifndef BOOKITEM_H
#define BOOKITEM_H

#include "item.h"


class BookItem : public Item
{

public:

    BookItem(QString n);

    QString getType() const override;

    ~BookItem();

};

#endif // BOOKITEM_H
