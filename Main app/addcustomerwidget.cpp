#include "addcustomerwidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>


AddCustomerWidget::AddCustomerWidget(QWidget *parent)
    : QWidget{parent},
      lineEditCustomerName{new QLineEdit(this)},
      btnAddCustomer{new QPushButton("Add Customer",this)}
{

    setWindowTitle("Customer");

    setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    setMaximumSize(QSize(400,100));
    setMinimumSize(QSize(400,100));

    setUpWidgets();

    connect(btnAddCustomer,&QPushButton::clicked,this,&AddCustomerWidget::addCustomerButtonClicked);

    setStyleSheet("background-color:#5e645b;");

    customerList = CustomerList::getCustomerList();

}

void AddCustomerWidget::setUpWidgets()
{

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    QFormLayout *f_layout = new QFormLayout;

    const QRegularExpression customerPattern("[A-Za-z0-9\\s]*");
    const QValidator *validateCustomerName = new QRegularExpressionValidator(customerPattern);

    f_layout->addRow("Customer name",lineEditCustomerName);
    lineEditCustomerName->setPlaceholderText("Enter here....");
    lineEditCustomerName->setValidator(validateCustomerName);
    lineEditCustomerName->setStyleSheet("background-color:#ffffff;");

    f_layout->addWidget(btnAddCustomer);
    btnAddCustomer->setToolTip("adds cutomer to a list of customers!");
    btnAddCustomer->setCursor(QCursor(Qt::PointingHandCursor));

    QLabel *labelPixmap = new QLabel;

    const QPixmap pixmap(":/images/Images/customers.jpg");

    labelPixmap->setPixmap(pixmap.scaled(100,100,Qt::KeepAspectRatio));

    main_layout->addWidget(labelPixmap);
    main_layout->addLayout(f_layout);
}

AddCustomerWidget::~AddCustomerWidget()
{
    delete customerList;
    delete c;
}

void AddCustomerWidget::addCustomerButtonClicked()
{

    if(!lineEditCustomerName->text().isEmpty()){

        c = new Customer(lineEditCustomerName->text());

        customerList->addCustomer(c);

        lineEditCustomerName->clear();
        lineEditCustomerName->setFocus();

        emit customerAdded(c);

    }else{

        QMessageBox::critical(this,"Critical","Enter customer name");
    }

}


