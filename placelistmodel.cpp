#include "placelistmodel.h"

PlaceListModel::PlaceListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    paginationModel = new PaginationListModel;

    currentPlaceDetail = new PlaceDetail;

    currentPage = totalPage = 1;
    generatePage(currentPage, totalPage);

    roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, QByteArray("id"));
    roles.insert(NameRole, QByteArray("itemName"));
    roles.insert(ApprovedRole, QByteArray("approved"));
    roles.insert(LastUpdateRole, QByteArray("lastUpdate"));
    roles.insert(AddressRole, QByteArray("address"));
    roles.insert(CategoryRole, QByteArray("category"));
    roles.insert(CoordinateRole, QByteArray("coordinate"));
    roles.insert(DescRole, QByteArray("desc"));
    roles.insert(EmailRole, QByteArray("email"));
    roles.insert(LocationRole, QByteArray("location"));
    roles.insert(PhoneRole, QByteArray("phone"));
    roles.insert(TypeRole, QByteArray("type"));
    roles.insert(WebsiteRole, QByteArray("website"));

#if QT_VERSION < 0x050000
    setRoleNames(roles);
#endif
}

int PlaceListModel::getCurrentPage() const
{
    return currentPage;
}

void PlaceListModel::setCurrentPage(int value)
{
    currentPage = value;
    emit currentPageChanged();
}

void PlaceListModel::generatePage(int currentPage, int totalPage)
{
    setCurrentPage(currentPage);
    setTotalPage(totalPage);
    paginationModel->generatePage(currentPage, totalPage);
}

QVariant PlaceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > (itemIndexList.count()-1) )
        return QVariant();

    QVariantMap itemMap = allItemMap.value(itemIndexList.at(index.row())).toMap();
    switch (role) {
        case IdRole:
            return itemMap.value("id").toString();
        case NameRole:
            return itemMap.value("name").toString();
        case ApprovedRole:
            return itemMap.value("approved").toString();
        case LastUpdateRole:
            return itemMap.value("last_update").toString();
        case AddressRole:
            return itemMap.value("address").toString();
        case CategoryRole:
            return itemMap.value("category").toString();
        case CoordinateRole:
            return itemMap.value("coordinate").toString();
        case DescRole:
            return itemMap.value("desc").toString();
        case EmailRole:
            return itemMap.value("email").toString();
        case LocationRole:
            return itemMap.value("location").toString();
        case PhoneRole:
            return itemMap.value("phone").toString();
        case TypeRole:
            return itemMap.value("type").toString();
        case WebsiteRole:
            return itemMap.value("website").toString();
        default:
            return QVariant();
    }
}

int PlaceListModel::rowCount(const QModelIndex &parent) const
{
    return itemIndexList.count();
}
#if QT_VERSION >= 0x050000
QHash<int, QByteArray> PlaceListModel::roleNames() const
{
    return roles;
}
#endif
QVariantMap PlaceListModel::getAllItemMap() const
{
    return allItemMap;
}

void PlaceListModel::setAllItemMap(const QVariantMap &value)
{
    emit beginResetModel();
    allItemMap = value;
    itemIndexList = allItemMap.keys();
    qSort(itemIndexList.begin(), itemIndexList.end(), compareNumber);
    emit endResetModel();
}

int PlaceListModel::getTotalPage() const
{
    return totalPage;
}

void PlaceListModel::setTotalPage(int value)
{
    totalPage = value;
    emit totalPageChanged();
}

PaginationListModel *PlaceListModel::getPaginationModel() const
{
    return paginationModel;
}

QVariantMap PlaceListModel::getCurrentPlaceMap() const
{
    return currentPlaceMap;
}

void PlaceListModel::setCurrentPlaceMap(const QVariantMap &value)
{
    currentPlaceMap = value;
}

void PlaceListModel::selectItemFromIndex(int index)
{
    setCurrentPlaceMap(allItemMap.value(itemIndexList.at(index)).toMap());
}

void PlaceListModel::setCurrentPlaceDetailByIndex(int index)
{
    setCurrentPlaceMap(allItemMap.value(itemIndexList.at(index)).toMap());
    currentPlaceDetail->setItemMap(currentPlaceMap);
}

int PlaceListModel::getCurrentIndex() const
{
    return currentIndex;
}

void PlaceListModel::setCurrentIndex(int value)
{
    currentIndex = value;
    setCurrentPlaceDetailByIndex(value);
    emit currentIndexChanged();
}

PlaceDetail *PlaceListModel::getCurrentPlaceDetail()
{
    return currentPlaceDetail;
}

void PlaceListModel::addItem(QVariantMap itemMap)
{
    QString id = itemMap.value("id").toString();
    if(allItemMap.value(id).isValid())
    {
        allItemMap.insert(id, itemMap);
        emit dataChanged(index(itemIndexList.indexOf(id)), index(itemIndexList.indexOf(id)));
    }
}
