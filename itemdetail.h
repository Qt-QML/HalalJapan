#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include <QObject>
#include <QVariant>
#include <QDir>
#include "settings.h"
#include "globalfunction.h"

class ItemDetail : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString itemId
               READ  getItemId
               CONSTANT
               )
    Q_PROPERTY(QString itemName
               READ  getItemName
               CONSTANT
               )
    Q_PROPERTY(QString itemApproved
               READ  getItemApproved
               CONSTANT
               )
    Q_PROPERTY(QString itemLastUpdate
               READ  getItemLastUpdate
               CONSTANT
               )
    Q_PROPERTY(QString itemBarcode
               READ  getItemBarcode
               CONSTANT
               )
    Q_PROPERTY(QString itemCategory
               READ  getItemCategory
               CONSTANT
               )
    Q_PROPERTY(QString itemConfirmDate
               READ  getItemConfirmDate
               CONSTANT
               )
    Q_PROPERTY(QString itemContributor
               READ  getItemContributor
               CONSTANT
               )
    Q_PROPERTY(QString itemDesc
               READ  getItemDesc
               CONSTANT
               )
    Q_PROPERTY(QString itemIngredientPic
               READ  getItemIngredientPic
               CONSTANT
               )
    Q_PROPERTY(QString itemPic
               READ  getItemPic
               CONSTANT
               )
    Q_PROPERTY(QString itemProducer
               READ  getItemProducer
               CONSTANT
               )
    Q_PROPERTY(QString itemReason
               READ  getItemReason
               CONSTANT
               )
    Q_PROPERTY(QString itemStatus
               READ  getItemStatus
               CONSTANT
               )
    Q_PROPERTY(QString itemThumb
               READ  getItemThumb
               CONSTANT
               )
public:
    explicit ItemDetail(QObject *parent = 0);

    QVariantMap getItemMap() const;
    void setItemMap(const QVariantMap &value);

    QString getItemId();
    QString getItemName();
    QString getItemApproved();
    QString getItemLastUpdate();
    QString getItemBarcode();
    QString getItemCategory();
    QString getItemConfirmDate();
    QString getItemContributor();
    QString getItemDesc();
    QString getItemIngredientPic();
    QString getItemPic();
    QString getItemProducer();
    QString getItemReason();
    QString getItemStatus();
    QString getItemThumb();

signals:
    void itemMapChanged();

public slots:

private:
    QVariantMap itemMap;

};

#endif // ITEMDETAIL_H
