#ifndef MODELCLASS_H
#define MODELCLASS_H

#include "transaction.h"

#include <QObject>

class QStandardItemModel;
class QXmlStreamWriter;
class QUdpSocket;


class ModelClass : public QObject
{

    Q_OBJECT

    ModelClass();
    static ModelClass *modelClass;

    QStandardItemModel *model;

    QUdpSocket *senderSocket;

public:

    static ModelClass* getModelClass();

    QStandardItemModel* getModel() const;

    void updateModel(Transaction *t);

    ~ModelClass();

public slots:

    void purseXmlContent();

signals:

    void xmlContentSent();
    void finished();

};

#endif // MODELCLASS_H
