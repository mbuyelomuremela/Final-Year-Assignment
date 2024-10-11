#ifndef BACKUPITEMLIST_H
#define BACKUPITEMLIST_H

#include "bookitem.h"
#include "magazineitem.h"

#include <QList>


class BackupItemList
{

public:

    static BackupItemList* getBackupItemList();

    ~BackupItemList();

private:

    BackupItemList();

    friend class ItemList;

    void setState(QList<MagazineItem*> mList,QList<BookItem*> bList);

    QList<MagazineItem *> getMagazines() const;
    QList<BookItem *> getBooks() const;

    QList<MagazineItem*> magazines;
    QList<BookItem*> books;

    static BackupItemList* backupList;

};

#endif // BACKUPITEMLIST_H
