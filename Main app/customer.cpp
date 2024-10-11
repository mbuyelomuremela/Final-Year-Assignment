#include "customer.h"


Customer::Customer(QString n)
    :name(n)
{
}

QString Customer::getCustomerName() const
{
    return name;
}

Customer::~Customer()
{

}
