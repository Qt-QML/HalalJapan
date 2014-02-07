#include "paginationlistmodel.h"
#include <QDebug>

PaginationListModel::PaginationListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    currentPage = 1;
    totalPage = 1;
    roles = QAbstractListModel::roleNames();
    roles.insert(TextLabelRole, QByteArray("textLabel"));
    roles.insert(PageNumberRole, QByteArray("pageNumber"));

#if QT_VERSION < 0x050000
    setRoleNames(roles);
#endif
}

void PaginationListModel::generatePage(int currentPage, int totalPage)
{
    emit beginResetModel();
    if(currentPage > totalPage)
    {
        currentPage = totalPage;
    }
    setCurrentPage(currentPage);
    setTotalPage(totalPage);

    pageList.clear();

    int nextPage;
    int previousPage;
    if(currentPage != totalPage && currentPage != 1)
    {
        pageList.append(QString::number(currentPage));
    }

    for(int i=1; i<3;i++)
    {
        nextPage = currentPage + i;
        previousPage = currentPage - i;
        if(nextPage < totalPage)
        {
            pageList.append(QString::number(nextPage));
        }

        if(previousPage > 1)
        {
            pageList.prepend(QString::number(previousPage));
        }
    }

    pageList.prepend(QString::number(1));

    if(totalPage != 1)
    {
        pageList.append(QString::number(totalPage));
    }

    emit endResetModel();
}

QVariant PaginationListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid
    if (index.row() > (pageList.count()-1) )
        return QVariant();

    QString itemString = pageList.at(index.row());

    switch (role) {
        case TextLabelRole:
            if(itemString == "1")
            {
                return "first";
            }
            else if(itemString == QString::number(totalPage))
            {
                return "last";
            }
            else
            {
                return itemString;
            }
        case PageNumberRole:
            return itemString;
        default:
            return QVariant();
    }
}

int PaginationListModel::rowCount(const QModelIndex &parent) const
{
    return pageList.count();
}
#if QT_VERSION >= 0x050000
QHash<int, QByteArray> PaginationListModel::roleNames() const
{
    return roles;
}
#endif
int PaginationListModel::getItemCount()
{
    return pageList.count();
}
int PaginationListModel::getCurrentPage() const
{
    return currentPage;
}

void PaginationListModel::setCurrentPage(int value)
{
    currentPage = value;
}

int PaginationListModel::getTotalPage() const
{
    return totalPage;
}

void PaginationListModel::setTotalPage(int value)
{
    totalPage = value;
}
