#include "placedetail.h"

PlaceDetail::PlaceDetail(QObject *parent) :
    QObject(parent)
{
}

QVariantMap PlaceDetail::getItemMap() const
{
    return itemMap;
}

void PlaceDetail::setItemMap(const QVariantMap &value)
{
    itemMap = value;
    emit itemMapChanged();
}

QString PlaceDetail::getItemId()
{
    return itemMap.value("id", "").toString();
}

QString PlaceDetail::getItemName()
{
    return itemMap.value("name", "-").toString();
}

bool PlaceDetail::getItemApproved()
{
    return itemMap.value("approved", false).toBool();
}

QString PlaceDetail::getItemLastUpdate()
{
    return itemMap.value("last_update").toString();
}

QString PlaceDetail::getItemAddress()
{
    return itemMap.value("address").toString();
}

QString PlaceDetail::getItemCoordinate()
{
    return itemMap.value("coordinate").toString();
}

QString PlaceDetail::getItemDesc()
{
    return itemMap.value("desc").toString();
}

QString PlaceDetail::getItemEmail()
{
    return itemMap.value("email", "-").toString();
}

QString PlaceDetail::getItemLocation()
{
    return itemMap.value("location").toString();
}

QString PlaceDetail::getItemPhone()
{
    return itemMap.value("phone", "-").toString();
}

QString PlaceDetail::getItemType()
{
    return itemMap.value("type").toString();
}

QString PlaceDetail::getItemWebsite()
{
    return itemMap.value("website", "-").toString();
}
