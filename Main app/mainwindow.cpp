#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QThread>
#include <QLabel>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      menu_Add_Items{new QMenu(tr("Add"),this)},
      menu_XmlFile{new QMenu(tr("Xml"),this)},
      menu_Backup{new QMenu(tr("Backup"),this)},
      menu_About{new QMenu(tr("About"),this)},
      menu_Help{new QMenu(tr("Help"),this)},
      action_Add_Item{new QAction(tr("Add item"),this)},
      action_Add_Customer{new QAction(tr("Add customer"),this)},
      actionGroup{new QActionGroup(this)},
      action_Generate_Xml{new QAction(tr("Generate Xml"),this)},
      thread{new QThread},
      action_Backup{new QAction(tr("Backup"),this)},
      action_About{new QAction(tr("About"),this)},
      action_Help{new QAction(tr("Help"),this)},
      itemWidget{new AddItemsWidget},
      customerWidget{new AddCustomerWidget},
      transactionWidgets{new TransactionWidget(this)},
      itemsLabel{new QLabel("Items in store = 0",this)},
      customerLabel{new QLabel("Customers = 0",this)},
      transactionLabel{new QLabel("Transactions = 0",this)}
{

    setWindowTitle("Book store system");

    setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    setIconSize(QSize(30,30));

    setWindowState(Qt::WindowMaximized);

    setUpActions();

    setUpCentralWidgets();

    connect(actionGroup,&QActionGroup::triggered,this,&MainWindow::showAddWidget);

    connect(action_Generate_Xml,&QAction::triggered,this,&MainWindow::sendXmlContent);
    connect(action_Backup,&QAction::triggered,this,&MainWindow::restoreItemList);
    connect(action_About,&QAction::triggered,this,&MainWindow::actionAboutTriggered);
    connect(action_Help,&QAction::triggered,this,&MainWindow::actionHelpTriggered);

    customerList = CustomerList::getCustomerList();
    itemList = ItemList::getItemList();
    transactionList = TransactionList::getTransactionList();

    modelClass = ModelClass::getModelClass();
    modelClass->moveToThread(thread);

    connect(customerList,&CustomerList::customerAdded,this,&MainWindow::updateCustomerLabel);
    connect(itemList,&ItemList::itemAdded,this,&MainWindow::updateItemsLabel);
    connect(transactionList,&TransactionList::transactionAdded,this,&MainWindow::updateTransactionsLabel);
    connect(modelClass,&ModelClass::xmlContentSent,this,&MainWindow::updateSendXmlLabel);

    connect(thread,&QThread::started,modelClass,&ModelClass::purseXmlContent);
   // connect(modelClass,&ModelClass::finished,modelClass,&ModelClass::deleteLater);
    connect(modelClass,&ModelClass::finished,thread,&QThread::quit);
    //connect(thread,&QThread::finished,thread,&QThread::deleteLater);

    statusBar()->setStyleSheet("background-color:#655e6f;");
    statusBar()->addPermanentWidget(customerLabel);
    statusBar()->addPermanentWidget(transactionLabel);
    statusBar()->addPermanentWidget(itemsLabel);

    setStyleSheet("background-color:#5e645b;");

}

MainWindow::~MainWindow()
{

    delete customerList;
    delete itemList;
    delete transactionList;

    delete modelClass;
    delete thread;
}

void MainWindow::setUpActions()
{

    menuBar()->addMenu(menu_Add_Items);
    menuBar()->addSeparator();
    menuBar()->addMenu(menu_XmlFile);
    menuBar()->addSeparator();
    menuBar()->addMenu(menu_Backup);
    menuBar()->addMenu(menu_About);
    menuBar()->addMenu(menu_Help);

    QToolBar *tool_bar = new QToolBar(this);
    addToolBar(Qt::RightToolBarArea,tool_bar);

    tool_bar->setMovable(false);

    actionGroup->addAction(action_Add_Item);
    actionGroup->addAction(action_Add_Customer);

    action_Add_Customer->setIcon(QIcon(":/images/Images/add_customer.jpg"));

    action_Add_Item->setIcon(QIcon(":/images/Images/add_book.jpg"));

    action_Backup->setIcon(QIcon(":/images/Images/restore.jpg"));

    action_Generate_Xml->setIcon(QIcon(":/images/Images/xml.jpg"));

    action_About->setIcon(QIcon(":/images/Images/about.png"));

    action_Help->setIcon(QIcon(":/images/Images/help.png"));

    menu_Add_Items->addActions(actionGroup->actions());
    menu_XmlFile->addAction(action_Generate_Xml);
    menu_Backup->addAction(action_Backup);
    menu_About->addAction(action_About);
    menu_Help->addAction(action_Help);

    tool_bar->addAction(action_Add_Customer);
    tool_bar->addAction(action_Add_Item);

    tool_bar->addSeparator();

    tool_bar->addAction(action_Backup);

    tool_bar->addSeparator();

    tool_bar->addAction(action_Generate_Xml);

    tool_bar->addAction(action_About);

    tool_bar->addAction(action_Help);

    const QString styleSheet("background-color:#655e6f;border:none;color:white;font-weight:bold;");

    menuBar()->setStyleSheet(styleSheet);
    tool_bar->setStyleSheet(styleSheet);

}

void MainWindow::setUpCentralWidgets()
{
    setCentralWidget(transactionWidgets);
}

void MainWindow::showAddWidget(QAction *a)
{

    if(a == action_Add_Item)
        itemWidget->show();

    if(a == action_Add_Customer)
        customerWidget->show();

}

void MainWindow::restoreItemList()
{
    itemList->restoreItemList(itemWidget->getBackupList());
}

void MainWindow::actionAboutTriggered()
{

    QString aboutApplication = "The application is capable of the following:\n";
    aboutApplication = aboutApplication + " 1. Keeping a list of customers.\n";
    aboutApplication = aboutApplication + " 2. Keeping a list of items( book or magazine).\n";
    aboutApplication = aboutApplication + " 3. Records the item(s) purchased against the customer who is buying that item.\n";
    aboutApplication = aboutApplication + " 4. Broadcasting all transactions in xml format to the listener app.\n\n";
    aboutApplication = aboutApplication + "Developed on 2023/08/10, entirely with C++ and Qt6 Framework.\n\n";


    QString aboutDeveloper = "Developer:\n";
    aboutDeveloper = aboutDeveloper + "Name : Mbuyelo Muremela.\n";
    aboutDeveloper = aboutDeveloper + "Qualification : Bachelor of science in Informatics.\n";
    aboutDeveloper = aboutDeveloper + "                University of South Africa.";

    QMessageBox::information(this,"action",aboutApplication + aboutDeveloper);

}

void MainWindow::actionHelpTriggered()
{

    QString howToGetStarted = "When the application starts, add items and customers before making any transaction.\n\n";

    QString howToAddCustomer = "To add customer, follow the steps:\n";
    howToAddCustomer = howToAddCustomer + " 1. Navigate to Add menu, and choose add customer option or click add customer icon.\n";
    howToAddCustomer = howToAddCustomer + " 2. Input the customer name(s) and click add customer button. this adds to a list of customers.\n\n";

    QString howToAddItem = "To add item, follow the steps:'\n";
    howToAddItem = howToAddItem + " 1. Navigate to Add menu, and choose add item option or click add item icon.\n";
    howToAddItem = howToAddItem + " 2. Input the name of the item.\n";
    howToAddItem = howToAddItem + " 3. Input the type of the item.\n";
    howToAddItem = howToAddItem + " 4. Click add item button. This adds to a list of customers.\n\n";

    QString howToMakeTransaction = "To make a transaction, follow the steps:\n";
    howToMakeTransaction = howToMakeTransaction + " 1. Select the type of item to be purchased.\n";
    howToMakeTransaction = howToMakeTransaction + " 2. Select the name of item to be purchased.\n";
    howToMakeTransaction = howToMakeTransaction + " 3. Select the customer purchasing the item.\n";
    howToMakeTransaction = howToMakeTransaction + " 4. Select the number of units(quantity) for the item being purchased.\n";
    howToMakeTransaction = howToMakeTransaction + " 5. Click add to cart button. This adds selected item to cart so that another item can be added for one transaction.\n";
    howToMakeTransaction = howToMakeTransaction + " 6. Once done adding all items, you click pay button to complete transaction for that particular customer. You can do one transaction for one customer at a time, but a transaction can have many items.\n";
    howToMakeTransaction = howToMakeTransaction + " 7. All transactions are displayed on transaction section with Transaction, Type, Quantity headings.\n\n";

    QString howToPurseXmlContent = "To send all transactions :\nSimply navigate to xml menu, and choose generate xml, or click xml icon.\n";

    QString help = howToGetStarted + howToAddCustomer + howToAddItem + howToMakeTransaction + howToPurseXmlContent;

    QMessageBox::information(this,"action",help);

}

void MainWindow::sendXmlContent()
{

    thread->start();

}

void MainWindow::updateCustomerLabel(int n)
{
    customerLabel->setText("Customers = " + QString::number(n));
}

void MainWindow::updateItemsLabel(int n, int m, int b)
{
    itemsLabel->setText("Items in store = " + QString::number(n) + " ( Magazine " + QString::number(m) + " | Book " + QString::number(b) + " )");
}

void MainWindow::updateTransactionsLabel(int n)
{
    transactionLabel->setText("Transactions = " + QString::number(n));
}

void MainWindow::updateSendXmlLabel()
{
    statusBar()->showMessage("xml sent",5000);
}
