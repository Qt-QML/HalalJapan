#include "itemdetail.h"

ItemDetail::ItemDetail(QObject *parent) :
    QObject(parent)
{
}

QVariantMap ItemDetail::getItemMap() const
{
    return itemMap;
}

void ItemDetail::setItemMap(const QVariantMap &value)
{
    itemMap = value;
    emit itemMapChanged();
}

QString ItemDetail::getItemId()
{
    return itemMap.value("id", "").toString();
}

QString ItemDetail::getItemName()
{
    return itemMap.value("name", "").toString();
}

QString ItemDetail::getItemApproved()
{
    return itemMap.value("approved", "").toString();
}

QString ItemDetail::getItemLastUpdate()
{
    return itemMap.value("last_update").toString();
}

QString ItemDetail::getItemBarcode()
{
    return itemMap.value("barcode").toString();
}

QString ItemDetail::getItemCategory()
{
    return itemMap.value("category").toString();
}

QString ItemDetail::getItemConfirmDate()
{
    return itemMap.value("confirm_date").toString();
}

QString ItemDetail::getItemContributor()
{
    return itemMap.value("contributor").toString();
}

QString ItemDetail::getItemDesc()
{
    return itemMap.value("desc").toString();
}

QString ItemDetail::getItemIngredientPic()
{
    return itemMap.value("ingredient_pic").toString();
}

QString ItemDetail::getItemPic()
{
    QString prefix = QString("file://%1%2").arg(Settings::instance()->getImagesPath()).arg(QDir::separator());
    QString filename = urlToFilename(itemMap.value("pic").toString());
    filename.prepend(prefix);
    return filename;
}

QString ItemDetail::getItemProducer()
{
    return itemMap.value("producer").toString();
}

QString ItemDetail::getItemReason()
{
    return itemMap.value("reason").toString();
}

QString ItemDetail::getItemStatus()
{
    return itemMap.value("status").toString();
}

QString ItemDetail::getItemThumb()
{
    QString prefix = QString("file://%1%2").arg(Settings::instance()->getImagesPath()).arg(QDir::separator());
    QString filename = urlToFilename(itemMap.value("thumb").toString());
    filename.prepend(prefix);
    return filename;
}

