#ifndef PURCHASEDITEM_H
#define PURCHASEDITEM_H

#include <QString>


class PurchasedItem
{

public:

    PurchasedItem(QString t,QString n,int q);

    QString toString() const;

    QString getType() const;
    QString getName() const;
    int getQuantity() const;

    ~PurchasedItem();

private:

    QString type;
    QString name;
    int quantity;

};

#endif // PURCHASEDITEM_H
