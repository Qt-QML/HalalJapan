#include "categorylistmodel.h"

CategoryListModel::CategoryListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    paginationModel = new PaginationListModel;

    currentCategoryDetail = new CategoryDetail;

    currentPage = totalPage = 1;
    generatePage(currentPage, totalPage);

    roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, QByteArray("id"));
    roles.insert(NameRole, QByteArray("itemName"));
    roles.insert(ApprovedRole, QByteArray("approved"));
    roles.insert(LastUpdateRole, QByteArray("lastUpdate"));

#if QT_VERSION < 0x050000
    setRoleNames(roles);
#endif
}

int CategoryListModel::getCurrentPage() const
{
    return currentPage;
}

void CategoryListModel::setCurrentPage(int value)
{
    currentPage = value;
    emit currentPageChanged();
}

int CategoryListModel::getTotalPage() const
{
    return totalPage;
}

void CategoryListModel::setTotalPage(int value)
{
    totalPage = value;
}

void CategoryListModel::generatePage(int currentPage, int totalPage)
{
    setCurrentPage(currentPage);
    paginationModel->generatePage(currentPage, totalPage);
}

QVariant CategoryListModel::data(const QModelIndex &index, int role) const
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
        default:
            return QVariant();
    }
}

int CategoryListModel::rowCount(const QModelIndex &parent) const
{
    return itemIndexList.count();
}

#if QT_VERSION >= 0x050000
QHash<int, QByteArray> CategoryListModel::roleNames() const
{
    return roles;
}
#endif

void CategoryListModel::setAllItemMap(const QVariantMap &value)
{
    emit beginResetModel();
    allItemMap = value;
    itemIndexList = allItemMap.keys();
    qSort(itemIndexList.begin(), itemIndexList.end(), compareNumber);
    emit endResetModel();
}

QVariantMap CategoryListModel::getAllItemMap() const
{
    return allItemMap;
}

PaginationListModel *CategoryListModel::getPaginationModel() const
{
    return paginationModel;
}

void CategoryListModel::addItem(QVariantMap itemMap)
{
    QString id = itemMap.value("id").toString();
    if(allItemMap.value(id).isValid())
    {
        allItemMap.insert(id, itemMap);
        emit dataChanged(index(itemIndexList.indexOf(id)), index(itemIndexList.indexOf(id)));
    }
}

CategoryDetail *CategoryListModel::getCurrentCategoryDetail() const
{
    return currentCategoryDetail;
}

QVariantMap CategoryListModel::getCurrentCategoryMap() const
{
    return currentCategoryMap;
}

void CategoryListModel::setCurrentCategoryMap(const QVariantMap &value)
{
    currentCategoryMap = value;
}

void CategoryListModel::selectItemFromIndex(int index)
{
    setCurrentCategoryMap(allItemMap.value(itemIndexList.at(index)).toMap());
}

int CategoryListModel::getCurrentIndex() const
{
    return currentIndex;
}

void CategoryListModel::setCurrentIndex(int value)
{
    currentIndex = value;
    setCurrentCategoryDetailByIndex(value);
    emit currentIndexChanged();
}

void CategoryListModel::setCurrentCategoryDetailByIndex(const int index)
{
    setCurrentCategoryMap(allItemMap.value(itemIndexList.at(index)).toMap());
    currentCategoryDetail->setItemMap(currentCategoryMap);
}

