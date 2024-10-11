#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include "customerlist.h"
#include "itemlist.h"
#include "transactionlist.h"
#include "modelclass.h"

#include <QWidget>

class QComboBox;
class QSpinBox;
class QPushButton;
class QTreeView;
class QTextEdit;


class TransactionWidget : public QWidget
{

    Q_OBJECT

    QComboBox *boxSelectCustomer;
    QComboBox *boxSelectType;
    QComboBox *boxSelectItemName;

    QSpinBox *spinEditQuantity;

    QPushButton *btnAddItemPurchased;
    QPushButton *btnaddTransaction;

    QTextEdit *textEdit;

    QTreeView *treeView;

    QList<PurchasedItem*> items;

    void setUpWidgets();

    CustomerList *customerList;
    ModelClass *modelClass;

    PurchasedItem *item;
    Transaction *t;
    TransactionList *transactionList;

    ItemList *itemList;

public:

    explicit TransactionWidget(QWidget *parent = NULL);

    ~TransactionWidget();

public slots:

    void btnAddItemPurchasedClicked();
    void btnaddTransactionClicked();

    void updateBoxSelectItemName(QString t);
    void updateBoxSelectCustomer(Customer *c);

};

#endif // TRANSACTIONWIDGET_H
