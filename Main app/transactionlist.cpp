#include "transactionlist.h"


TransactionList *TransactionList::transactionList = NULL;


TransactionList::TransactionList()
{

}

TransactionList *TransactionList::getTransactionList()
{

    if(transactionList == 0)
        transactionList = new TransactionList;
    return transactionList;

}

void TransactionList::addTransaction(Transaction *t)
{

    transactions.append(t);

    totalNumberOfTransactions++;

    emit transactionAdded(totalNumberOfTransactions);

}

TransactionList::~TransactionList()
{

    qDeleteAll(transactions);
    transactions.clear();

}
