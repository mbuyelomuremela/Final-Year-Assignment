#include "transaction.h"


Transaction::Transaction(QString c,QList<PurchasedItem*> items,QDate d,QTime t)
    :customerName{c},purchasedItems{items},transactionDate{d},transactionTime{t}
{
}

QString Transaction::getCustomerName() const
{
    return customerName;
}

QList<PurchasedItem *> Transaction::getPurchasedItems() const
{
    return purchasedItems;
}

QDate Transaction::getTransactionDate() const
{
    return transactionDate;
}

QTime Transaction::getTransactionTime() const
{
    return transactionTime;
}

Transaction::~Transaction()
{

    qDeleteAll(purchasedItems);
    purchasedItems.clear();

}
