#include "categorydetail.h"

CategoryDetail::CategoryDetail(QObject *parent) :
    QObject(parent)
{
}
QVariantMap CategoryDetail::getItemMap() const
{
    return itemMap;
}

void CategoryDetail::setItemMap(const QVariantMap &value)
{
    itemMap = value;
    emit itemMapChanged();
}

QString CategoryDetail::getItemId()
{
    return itemMap.value("id", "").toString();
}

QString CategoryDetail::getItemName()
{
    return itemMap.value("name", "").toString();
}

bool CategoryDetail::getItemApproved()
{
    return itemMap.value("approved", false).toBool();
}

QString CategoryDetail::getItemLastUpdate()
{
    return itemMap.value("last_update").toString();
}

