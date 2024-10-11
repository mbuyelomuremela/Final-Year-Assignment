#include "itemlist.h"


ItemList* ItemList::itemList = NULL;


ItemList *ItemList::getItemList()
{

    if(itemList == 0)
        itemList = new ItemList;
    return itemList;

}

void ItemList::addItem(Item *i)
{

    if(i->getType() == "Magazine"){

        MagazineItem *item = dynamic_cast<MagazineItem*>(i);
        magazineItems.append(item);
        numberOfMagazines++;

    }

    if(i->getType() == "Book"){

        BookItem *item = dynamic_cast<BookItem*>(i);
        bookItems.append(item);
        numberOfBooks++;

    }

    totalNumberOfItems++;

    emit itemAdded(totalNumberOfItems,numberOfMagazines,numberOfBooks);

}


ItemList::ItemList()
{

}

QList<BookItem *> ItemList::getBookItems() const
{
    return bookItems;
}

BackupItemList *ItemList::createBackupList() const
{

    BackupItemList *backupList  = new BackupItemList;

    backupList->setState(magazineItems,bookItems);

    return backupList;

}

void ItemList::restoreItemList(BackupItemList *backupList)
{

    qDeleteAll(bookItems);
    bookItems.clear();

    qDeleteAll(magazineItems);
    magazineItems.clear();

    foreach(MagazineItem *magazine,backupList->getMagazines()){

        MagazineItem *item = new MagazineItem(magazine->getItemName());
        magazineItems.append(item);

    }

    foreach(BookItem *book,backupList->getBooks()){

        BookItem *item = new BookItem(book->getItemName());
        bookItems.append(item);

    }

}

ItemList::~ItemList()
{

    qDeleteAll(magazineItems);
    magazineItems.clear();

    qDeleteAll(bookItems);
    bookItems.clear();

}

QList<MagazineItem *> ItemList::getMagazineItems() const
{
    return magazineItems;
}
