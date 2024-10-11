#ifndef MAGAZINEITEM_H
#define MAGAZINEITEM_H

#include "item.h"


class MagazineItem : public Item
{

public:

    MagazineItem(QString n);

    QString getType() const override;

    ~MagazineItem();

};

#endif // MAGAZINEITEM_H
