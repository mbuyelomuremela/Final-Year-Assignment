#include "customerlist.h"


CustomerList *CustomerList::customerList = NULL;


CustomerList *CustomerList::getCustomerList()
{

    if(customerList == 0)
        customerList = new CustomerList;
    return customerList;

}

void CustomerList::addCustomer(Customer *c)
{

    customers.append(c);

    totalNumberOfCustomers++;

    emit customerAdded(totalNumberOfCustomers);
    emit newCustomer(c);

}

QList<Customer *> CustomerList::getCustomers() const
{
    return customers;
}

CustomerList::~CustomerList()
{

    qDeleteAll(customers);
    customers.clear();

}

CustomerList::CustomerList()
{

}
