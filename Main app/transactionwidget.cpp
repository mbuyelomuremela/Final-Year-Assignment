#include "transactionwidget.h"

#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QTextEdit>
#include <QHeaderView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QStandardItemModel>


TransactionWidget::TransactionWidget(QWidget *parent)
    : QWidget{parent},
      boxSelectCustomer{new QComboBox(this)},
      boxSelectType{new QComboBox(this)},
      boxSelectItemName{new QComboBox(this)},
      spinEditQuantity{new QSpinBox(this)},
      btnAddItemPurchased{new QPushButton("Add to cart",this)},
      btnaddTransaction{new QPushButton("Pay",this)},
      textEdit{new QTextEdit(this)},
      treeView{new QTreeView(this)}
{

    setUpWidgets();

    customerList = CustomerList::getCustomerList();
    modelClass = ModelClass::getModelClass();
    transactionList = TransactionList::getTransactionList();
    itemList = ItemList::getItemList();

    connect(btnAddItemPurchased,&QPushButton::clicked,this,&TransactionWidget::btnAddItemPurchasedClicked);
    connect(btnaddTransaction,&QPushButton::clicked,this,&TransactionWidget::btnaddTransactionClicked);

    connect(customerList,&CustomerList::newCustomer,this,&TransactionWidget::updateBoxSelectCustomer);

    connect(boxSelectType,&QComboBox::currentTextChanged,this,&TransactionWidget::updateBoxSelectItemName);

    treeView->setModel(modelClass->getModel());
    treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


TransactionWidget::~TransactionWidget()
{

    delete customerList;
    delete modelClass;
    delete transactionList;
    delete itemList;

    qDeleteAll(items);
    items.clear();

}

void TransactionWidget::btnAddItemPurchasedClicked()
{

    bool itemSelected = ((boxSelectType->currentIndex() != -1) && (boxSelectItemName->currentIndex() != -1));
    bool customerSelected = (boxSelectCustomer->currentIndex() != -1);
    bool quantitySelected = (spinEditQuantity->value() != 0);

    if(itemSelected && customerSelected && quantitySelected){

        item = new PurchasedItem(boxSelectType->currentText(),boxSelectItemName->currentText(),spinEditQuantity->value());
        items.append(item);

        textEdit->setPlainText(item->toString() + "\n" + textEdit->toPlainText());

        boxSelectType->setCurrentIndex(-1);
        boxSelectItemName->setCurrentIndex(-1);
        spinEditQuantity->setValue(0);

        // This prevent selecting another customer while the current customer's transaction is not completed
        boxSelectCustomer->setEnabled(false);

    }

}

void TransactionWidget::btnaddTransactionClicked()
{

    if(boxSelectCustomer->currentIndex() != -1){

        t = new Transaction(boxSelectCustomer->currentText(),items,QDate::currentDate(),QTime::currentTime());

        transactionList->addTransaction(t);

        modelClass->updateModel(t);

        boxSelectCustomer->setCurrentIndex(-1);
        boxSelectCustomer->setEnabled(true);

        textEdit->clear();
        items.clear();
    }

}

void TransactionWidget::updateBoxSelectItemName(QString t)
{

    boxSelectItemName->setEditable(true);
    boxSelectItemName->clear();

    if(t == "Book"){

        foreach(BookItem *i,itemList->getBookItems()){
            boxSelectItemName->addItem(i->getItemName());
        }

    }

    if(t == "Magazine"){

        foreach(MagazineItem *i,itemList->getMagazineItems()){
            boxSelectItemName->addItem(i->getItemName());
        }

    }

    boxSelectItemName->setEditable(false);

}

void TransactionWidget::updateBoxSelectCustomer(Customer *c)
{

    boxSelectCustomer->setEditable(true);

    boxSelectCustomer->addItem(c->getCustomerName());

    boxSelectCustomer->setEditable(false);

    boxSelectCustomer->setCurrentIndex(-1);

}

void TransactionWidget::setUpWidgets()
{

    QGridLayout *layout = new QGridLayout(this);

    QHBoxLayout *lay_itemType = new QHBoxLayout;
    QHBoxLayout *lay_itemName = new QHBoxLayout;
    QHBoxLayout *lay_customer = new QHBoxLayout;
    QHBoxLayout *lay_quantity = new QHBoxLayout;

    QLabel *labelCustomerName = new QLabel("Select Customer");
    lay_customer->addWidget(labelCustomerName,0,Qt::AlignRight);
    lay_customer->addWidget(boxSelectCustomer,0,Qt::AlignLeft);

    QLabel *labelItemType = new QLabel("Select Item Type");
    lay_itemType->addWidget(labelItemType,0,Qt::AlignRight);
    lay_itemType->addWidget(boxSelectType,0,Qt::AlignLeft);

    QLabel *labelItemName = new QLabel("Select Item");
    lay_itemName->addWidget(labelItemName,0,Qt::AlignRight);
    lay_itemName->addWidget(boxSelectItemName,0,Qt::AlignLeft);

    QLabel *labelQuantity = new QLabel("Quantity");
    lay_quantity->addWidget(labelQuantity,0,Qt::AlignRight);
    lay_quantity->addWidget(spinEditQuantity,0,Qt::AlignLeft);

    layout->addLayout(lay_itemType,0,0,1,2);
    layout->addLayout(lay_itemName,1,0,1,2);
    layout->addLayout(lay_customer,0,2,1,2);
    layout->addLayout(lay_quantity,1,2,1,2);

    layout->addWidget(btnAddItemPurchased,2,2,1,1,Qt::AlignRight);
    btnAddItemPurchased->setToolTip("adds item to cart!");
    btnAddItemPurchased->setCursor(QCursor(Qt::PointingHandCursor));

    layout->addWidget(textEdit,3,0,2,4);
    textEdit->setStyleSheet("background-color:#ffffff;");
    textEdit->setEnabled(false);

    layout->addWidget(btnaddTransaction,5,3,1,1);

    layout->addWidget(treeView,6,0,4,4);

    boxSelectType->addItem("Book");
    boxSelectType->addItem("Magazine");
    boxSelectType->setCurrentIndex(-1);

    boxSelectType->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    boxSelectItemName->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    boxSelectCustomer->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    btnaddTransaction->setIcon(QIcon(":/images/Images/pay.jpg"));
    btnaddTransaction->setIconSize(QSize(40,40));
    btnaddTransaction->setFixedSize(70,70);
    btnaddTransaction->setToolTip("complete and add transaction!");
    btnaddTransaction->setCursor(QCursor(Qt::PointingHandCursor));

    treeView->setStyleSheet("background-color:#ffffff;");

}


