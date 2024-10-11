#include "additemswidget.h"

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>


AddItemsWidget::AddItemsWidget(QWidget *parent)
    : QWidget{parent},
      lineEditItemName{new QLineEdit(this)},
      boxSelectItemType{new QComboBox(this)},
      btnAddItem{new QPushButton("Add Item",this)}
{

    setWindowTitle("Item");

    setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    setMaximumSize(QSize(400,100));
    setMinimumSize(QSize(400,100));

    setUpWidgets();

    connect(btnAddItem,&QPushButton::clicked,this,&AddItemsWidget::addItemButtonClicked);

    setStyleSheet("background-color:#5e645b;");

    factory = new ItemFactory;

}

BackupItemList *AddItemsWidget::getBackupList() const
{
    return backupList;
}

AddItemsWidget::~AddItemsWidget()
{

    delete factory;
    delete item;
    delete backupList;

}

void AddItemsWidget::addItemButtonClicked()
{

    if(boxSelectItemType->currentIndex() != -1 && !lineEditItemName->text().isEmpty()){

        item = factory->createItem(boxSelectItemType->currentText(),lineEditItemName->text());

        ItemList::getItemList()->addItem(item);

        backupList = ItemList::getItemList()->createBackupList();

        boxSelectItemType->setCurrentIndex(-1);
        lineEditItemName->clear();
        lineEditItemName->setFocus();

        emit itemAdded(item);

    }else{

        QMessageBox::critical(this,"Critical","Enter all required data");
    }

}

void AddItemsWidget::setUpWidgets()
{

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    QFormLayout *f_layout = new QFormLayout;

    const QRegularExpression itemPattern("[A-Za-z0-9\\s]*");
    const QValidator *validateItemName = new QRegularExpressionValidator(itemPattern,this);

    QStringList types;
    types << "Book" << "Magazine";

    boxSelectItemType->addItems(types);
    boxSelectItemType->setCurrentIndex(-1);

    f_layout->addRow("Item name",lineEditItemName);
    lineEditItemName->setPlaceholderText("Book/magazine title here...");
    lineEditItemName->setValidator(validateItemName);
    lineEditItemName->setStyleSheet("background-color:#ffffff;");

    f_layout->addRow("Item type",boxSelectItemType);

    f_layout->addWidget(btnAddItem);
    btnAddItem->setToolTip("adds item to a list of items!");
    btnAddItem->setCursor(QCursor(Qt::PointingHandCursor));

    QLabel *labelPixmap = new QLabel;

    const QPixmap pixmap(":/images/Images/book.jpg");

    labelPixmap->setPixmap(pixmap.scaled(100,100,Qt::KeepAspectRatio));

    main_layout->addWidget(labelPixmap);
    main_layout->addLayout(f_layout);

}
