#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include "customer.h"

#include <QObject>
#include <QList>


class CustomerList : public QObject
{

    Q_OBJECT

    CustomerList();
    static CustomerList *customerList;

    QList<Customer*> customers;

    int totalNumberOfCustomers = 0;

public:

    static CustomerList* getCustomerList();

    void addCustomer(Customer *c);

    QList<Customer*> getCustomers() const;

    ~CustomerList();

signals:

    void customerAdded(int n);
    void newCustomer(Customer *c);

};

#endif // CUSTOMERLIST_H
