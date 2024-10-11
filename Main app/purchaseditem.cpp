#include "purchaseditem.h"


PurchasedItem::PurchasedItem(QString t, QString n, int q)
    :type{t},name{n},quantity{q}
{

}

QString PurchasedItem::toString() const
{

    return QString("Item : %1, Type : %2, Quantity : %3")
            .arg(name)
            .arg(type)
            .arg(quantity);

}

QString PurchasedItem::getType() const
{
    return type;
}

QString PurchasedItem::getName() const
{
    return name;
}

int PurchasedItem::getQuantity() const
{
    return quantity;
}

PurchasedItem::~PurchasedItem()
{

}
