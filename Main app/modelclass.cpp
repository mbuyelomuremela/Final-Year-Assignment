#include "modelclass.h"

#include <QStandardItemModel>
#include <QXmlStreamWriter>
#include <QUdpSocket>
#include <QStringList>


ModelClass *ModelClass::modelClass = NULL;


ModelClass *ModelClass::getModelClass()
{

    if(modelClass == 0)
        modelClass = new ModelClass;
    return modelClass;

}

QStandardItemModel *ModelClass::getModel() const
{
    return model;
}

ModelClass::~ModelClass()
{

}

void ModelClass::updateModel(Transaction *t)
{

    QStandardItem *transactiondatetimeitem = new QStandardItem(t->getTransactionDate().toString() + " " + t->getTransactionTime().toString());

    bool customerDoesNotExist = true; // Assume that customer owning transaction is not already in the model

    // Checks if the customer has made a transaction before. if yes, set transactiondatetimeitem as a child for that customer
    // Instead of adding as new customer
    for(int row = 0; row < model->rowCount(); row++){

        QStandardItem *customer = model->item(row);

        if(t->getCustomerName() == customer->text()){

            customer->setChild(customer->rowCount(),transactiondatetimeitem);

            customerDoesNotExist = false; // Customer has made a transaction before
            break;

        }

    }

    // Customer has never made a transaction before, add as new customer
    if(customerDoesNotExist){

        QStandardItem *customer = new QStandardItem(t->getCustomerName());

        model->setItem(model->rowCount(),customer);

        customer->setChild(customer->rowCount(),transactiondatetimeitem);

    }

    // Adding items for transaction
    foreach (PurchasedItem *i, t->getPurchasedItems()) {

        QStandardItem *name = new QStandardItem(i->getName());
        QStandardItem *type = new QStandardItem(i->getType());
        QStandardItem *quantity = new QStandardItem(QString::number(i->getQuantity()));

        QList<QStandardItem*> lineitem;

        lineitem << name << type << quantity;

        transactiondatetimeitem->appendRow(lineitem);

    }

}

void ModelClass::purseXmlContent()
{

    QString xmlContent;

    QXmlStreamWriter writer(&xmlContent); // Writing to xmlContent

    writer.setAutoFormatting(true);

    writer.writeStartDocument(); // starts the document

    writer.writeStartElement("ModelData");

    // Checks if there's any transaction recorded. else write empty xml data
    if(model->hasChildren()){

        int customers = model->rowCount(); // number of customers who made transactions

        for(int cRow = 0; cRow < customers; cRow++){

            QStandardItem *cItem = model->item(cRow);

            writer.writeStartElement("Customer");

            writer.writeAttribute("customer",cItem->text());

            int transactions = cItem->rowCount(); // number of transactions that belong to the customer

            for(int traRow = 0; traRow < transactions; traRow++){

                QStandardItem *transactionDate = cItem->child(traRow);

                writer.writeStartElement("transaction");

                writer.writeAttribute("date",transactionDate->text());

                int items = transactionDate->rowCount(); // number of items purchased as part of the transaction

                for(int i = 0; i < items; i++){

                    QStandardItem *name = transactionDate->child(i,0);
                    QStandardItem *type = transactionDate->child(i,1);
                    QStandardItem *quantity = transactionDate->child(i,2);

                    writer.writeStartElement("lineitem");

                    writer.writeAttribute("name",name->text());
                    writer.writeAttribute("type",type->text());
                    writer.writeAttribute("quantity",quantity->text());

                    writer.writeEndElement();

                }

                writer.writeEndElement();

            }

            writer.writeEndElement();
        }
    }

    writer.writeEndElement();

    writer.writeEndDocument(); // end document

    QByteArray datagram = xmlContent.toLatin1();

    senderSocket->writeDatagram(datagram,QHostAddress::Broadcast,1996);

    emit xmlContentSent();
    emit finished();

}

ModelClass::ModelClass()
    :model{new QStandardItemModel(this)},
     senderSocket{new QUdpSocket(this)}
{

    model->setColumnCount(3);

    QStringList headerLabels;
    headerLabels << "Transaction" << "Type" << "Quantity";

    model->setHorizontalHeaderLabels(headerLabels);

}
