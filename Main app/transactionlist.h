#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include "transaction.h"

#include <QObject>


class TransactionList : public QObject
{

    Q_OBJECT

    TransactionList();
    static TransactionList *transactionList;

    QList<Transaction*> transactions;
    int totalNumberOfTransactions = 0;

public:

    static TransactionList* getTransactionList();

    void addTransaction(Transaction *t);

    ~TransactionList();

signals:

    void transactionAdded(int n);

};

#endif // TRANSACTIONLIST_H
