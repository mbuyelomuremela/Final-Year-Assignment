#ifndef ADDCUSTOMERWIDGET_H
#define ADDCUSTOMERWIDGET_H

#include "customerlist.h"

#include <QWidget>

class QLineEdit;
class QPushButton;


class AddCustomerWidget : public QWidget
{

    Q_OBJECT

    QLineEdit *lineEditCustomerName;
    QPushButton *btnAddCustomer;

    void setUpWidgets();

    CustomerList *customerList;
    Customer *c;

public:

    explicit AddCustomerWidget(QWidget *parent = NULL);

    ~AddCustomerWidget();

signals:

    void customerAdded(Customer *c);

public slots:

    void addCustomerButtonClicked();

};

#endif // ADDCUSTOMERWIDGET_H
