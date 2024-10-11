#ifndef ITEM_H
#define ITEM_H

#include <QString>


class Item
{

public:

    Item(QString n);

    QString getItemName() const;

    virtual QString getType() const;

    ~Item();

private:

    QString name;

};

#endif // ITEM_H
