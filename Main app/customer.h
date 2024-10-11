#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>


class Customer
{

public:

    Customer(QString n);

    QString getCustomerName() const;

    ~Customer();

private:

    QString name;

};

#endif // CUSTOMER_H
