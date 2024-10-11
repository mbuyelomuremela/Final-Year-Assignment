#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "purchaseditem.h"

#include <QList>
#include <QDate>
#include <QTime>


class Transaction
{

public:

    Transaction(QString c,QList<PurchasedItem*> items,QDate d,QTime t);

    QString getCustomerName() const;

    QList<PurchasedItem *> getPurchasedItems() const;

    QDate getTransactionDate() const;
    QTime getTransactionTime() const;

    ~Transaction();

private:

    QString customerName;

    QList<PurchasedItem*> purchasedItems;

    QDate transactionDate;
    QTime transactionTime;

};

#endif // TRANSACTION_H
