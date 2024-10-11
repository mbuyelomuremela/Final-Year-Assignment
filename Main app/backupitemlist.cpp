#include "backupitemlist.h"


BackupItemList* BackupItemList::backupList = NULL;



BackupItemList *BackupItemList::getBackupItemList()
{

    if(backupList == 0)
        backupList = new BackupItemList;
    return backupList;

}

BackupItemList::~BackupItemList()
{

    qDeleteAll(magazines);
    magazines.clear();

    qDeleteAll(books);
    books.clear();

}

BackupItemList::BackupItemList()
{

}

void BackupItemList::setState(QList<MagazineItem *> mList, QList<BookItem *> bList)
{

    bool itemDoesNotExist = true; // Assume that item is not available in the backup list

    foreach(MagazineItem *magazine, mList){

        // Checks if magazine is already in the backup list
        foreach(MagazineItem *i,magazines){

            if(i->getItemName() == magazine->getItemName() && i->getType() == magazine->getType()){

                itemDoesNotExist = false;
                break;
            }
        }

        if(itemDoesNotExist){

            MagazineItem *item = new MagazineItem(magazine->getItemName());
            magazines.append(item);
        }

    }

    // Repeate the process for books

    itemDoesNotExist = true;

    foreach(BookItem *book, bList){

        foreach(BookItem *i,books){

            if(i->getItemName() == book->getItemName() && i->getType() == book->getType()){

                itemDoesNotExist = false;
                break;
            }
        }

        if(itemDoesNotExist){

            BookItem *item = new BookItem(book->getItemName());
            books.append(item);
        }

    }

}

QList<BookItem *> BackupItemList::getBooks() const
{
    return books;
}

QList<MagazineItem *> BackupItemList::getMagazines() const
{
    return magazines;
}
