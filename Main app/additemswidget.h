#ifndef ADDITEMSWIDGET_H
#define ADDITEMSWIDGET_H

#include "item.h"
#include "itemfactory.h"
#include "itemlist.h"

#include <QWidget>

class QLineEdit;
class QComboBox;
class QPushButton;


class AddItemsWidget : public QWidget
{

    Q_OBJECT

    QLineEdit *lineEditItemName;
    QComboBox *boxSelectItemType;
    QPushButton *btnAddItem;

    ItemFactory *factory;
    Item *item;

    BackupItemList *backupList;

    void setUpWidgets();

public:

    explicit AddItemsWidget(QWidget *parent = NULL);

    BackupItemList * getBackupList() const;

    ~AddItemsWidget();

public slots:

    void addItemButtonClicked();

signals:

    void itemAdded(Item *i);

};

#endif // ADDITEMSWIDGET_H
