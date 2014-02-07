#include "itemlistmodel.h"
#include <QDebug>

ItemListModel::ItemListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    paginationModel = new PaginationListModel;
    currentItemDetail = new ItemDetail;

    currentPage = totalPage = 1;
    generatePage(currentPage, totalPage);

    roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, QByteArray("id"));
    roles.insert(NameRole, QByteArray("itemName"));
    roles.insert(ApprovedRole, QByteArray("approved"));
    roles.insert(LastUpdateRole, QByteArray("lastUpdate"));
    roles.insert(BarcodeRole, QByteArray("barcode"));
    roles.insert(CategoryRole, QByteArray("category"));
    roles.insert(ConfirmDateRole, QByteArray("confirmDate"));
    roles.insert(ContributorRole, QByteArray("contributor"));
    roles.insert(DescRole, QByteArray("desc"));
    roles.insert(IngredientPicRole, QByteArray("ingredientPic"));
    roles.insert(PicRole, QByteArray("pic"));
    roles.insert(ProducerRole, QByteArray("producer"));
    roles.insert(ReasonRole, QByteArray("reason"));
    roles.insert(StatusRole, QByteArray("status"));
    roles.insert(ThumbRole, QByteArray("thumb"));

#if QT_VERSION < 0x050000
    setRoleNames(roles);
#endif
}
int ItemListModel::getCurrentPage() const
{
    return currentPage;
}

void ItemListModel::setCurrentPage(int value)
{
    currentPage = value;
    emit currentPageChanged();
}

void ItemListModel::generatePage(int currentPage, int totalPage)
{
    setCurrentPage(currentPage);
    paginationModel->generatePage(currentPage, totalPage);
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > (itemIndexList.count()-1) )
        return QVariant();

    QVariantMap itemMap = allItemMap.value(itemIndexList.at(index.row())).toMap();
//    QString id = itemMap.value("id").toString();
    QString filename;
    QString prefix = QString("file://%1%2").arg(Settings::instance()->getImagesPath()).arg(QDir::separator());

    switch (role) {
        case IdRole:
            return itemMap.value("id").toString();
        case NameRole:
            return itemMap.value("name").toString();
        case ApprovedRole:
            return itemMap.value("approved").toString();
        case LastUpdateRole:
            return itemMap.value("last_update").toString();
        case BarcodeRole:
            return itemMap.value("barcode").toString();
        case CategoryRole:
            return itemMap.value("category").toString();
        case ConfirmDateRole:
            return itemMap.value("confirm_date").toString();
        case ContributorRole:
            return itemMap.value("contributor").toString();
        case DescRole:
            return itemMap.value("desc").toString();
        case IngredientPicRole:
            return itemMap.value("ingredient_pic").toString();
        case PicRole:
            filename = urlToFilename(itemMap.value("pic").toString());
            filename.prepend(prefix);
            return filename;
        case ProducerRole:
            return itemMap.value("producer").toString();
        case ReasonRole:
            return itemMap.value("reason").toString();
        case StatusRole:
            return itemMap.value("status").toString();
        case ThumbRole:
            filename = urlToFilename(itemMap.value("thumb").toString());
            filename.prepend(prefix);
            return filename;
        default:
            return QVariant();
    }
}

int ItemListModel::rowCount(const QModelIndex &parent) const
{
    return itemIndexList.count();
}

#if QT_VERSION >= 0x050000
QHash<int, QByteArray> ItemListModel::roleNames() const
{
    return roles;
}
#endif

QVariantMap ItemListModel::getAllItemMap() const
{
    return allItemMap;
}

void ItemListModel::setAllItemMap(const QVariantMap &value)
{
    emit beginResetModel();
    allItemMap = value;
    itemIndexList = allItemMap.keys();
    qSort(itemIndexList.begin(), itemIndexList.end(), compareNumber);
    emit endResetModel();
}

void ItemListModel::addItem(QVariantMap itemMap)
{
    QString id = itemMap.value("id").toString();
    if(allItemMap.value(id).isValid())
    {
        allItemMap.insert(id, itemMap);
        emit dataChanged(index(itemIndexList.indexOf(id)), index(itemIndexList.indexOf(id)));
    }
}

ItemDetail *ItemListModel::getCurrentItemDetail() const
{
    return currentItemDetail;
}

void ItemListModel::setCurrentItemDetail(ItemDetail *value)
{
    currentItemDetail = value;
}

void ItemListModel::setCurrentItemDetailByIndex(const int index)
{
    setCurrentItemMap(allItemMap.value(itemIndexList.at(index)).toMap());
    currentItemDetail->setItemMap(currentItemMap);
}

int ItemListModel::getCurrentIndex() const
{
    return currentIndex;
}

void ItemListModel::setCurrentIndex(int value)
{
    currentIndex = value;
    setCurrentItemDetailByIndex(value);
    emit currentIndexChanged();
}

QVariantMap ItemListModel::getCurrentItemMap() const
{
    return currentItemMap;
}

void ItemListModel::setCurrentItemMap(const QVariantMap &value)
{
    currentItemMap = value;
}

void ItemListModel::selectItemFromIndex(int index)
{
    setCurrentItemMap(allItemMap.value(itemIndexList.at(index)).toMap());
}


PaginationListModel *ItemListModel::getPaginationModel() const
{
    return paginationModel;
}


int ItemListModel::getTotalPage() const
{
    return totalPage;
}

void ItemListModel::setTotalPage(int value)
{
    totalPage = value;
    emit totalPageChanged();
}

