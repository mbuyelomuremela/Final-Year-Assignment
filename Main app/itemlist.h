#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "magazineitem.h"
#include "bookitem.h"
#include "backupitemlist.h"

#include <QObject>
#include <QList>


class ItemList : public QObject
{

    Q_OBJECT

    ItemList();
    static ItemList *itemList;

    QList<MagazineItem*> magazineItems;
    QList<BookItem*> bookItems;

    int totalNumberOfItems = 0;
    int numberOfMagazines = 0;
    int numberOfBooks = 0;

public:

    static ItemList* getItemList();

    void addItem(Item *i);

    QList<MagazineItem *> getMagazineItems() const;
    QList<BookItem *> getBookItems() const;

    BackupItemList* createBackupList() const;
    void restoreItemList(BackupItemList* backupList);

    ~ItemList();

signals:

    void itemAdded(int total,int magazines,int books);
    void newItem(Item *i);

};

#endif // ITEMLIST_H
