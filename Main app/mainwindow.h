#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "additemswidget.h"
#include "addcustomerwidget.h"
#include "transactionwidget.h"
#include "modelclass.h"

class QMenuBar;
class QMenu;
class QAction;
class QActionGroup;
class QLabel;
class QThread;


class MainWindow : public QMainWindow
{

    Q_OBJECT

    QMenu *menu_Add_Items;
    QMenu *menu_XmlFile;
    QMenu *menu_Backup;
    QMenu *menu_About;
    QMenu *menu_Help;

    QAction *action_Add_Item;
    QAction *action_Add_Customer;
    QActionGroup *actionGroup;

    QAction *action_Generate_Xml;

    QAction *action_Backup;

    QAction *action_About;

    QAction *action_Help;

    QThread *thread;

    AddItemsWidget *itemWidget;
    AddCustomerWidget *customerWidget;
    TransactionWidget *transactionWidgets;

    CustomerList *customerList;
    ItemList *itemList;
    TransactionList *transactionList;
    ModelClass *modelClass;

    QLabel *itemsLabel;
    QLabel *customerLabel;
    QLabel *transactionLabel;
    QLabel *sendXmlLabel;

    void setUpActions();
    void setUpCentralWidgets();

public:

    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

private slots:

    void showAddWidget(QAction *a);

    void restoreItemList();

    void actionAboutTriggered();
    void actionHelpTriggered();

    void sendXmlContent();

    void updateCustomerLabel(int n);
    void updateItemsLabel(int n,int m,int b);
    void updateTransactionsLabel(int n);
    void updateSendXmlLabel();

};

#endif // MAINWINDOW_H
