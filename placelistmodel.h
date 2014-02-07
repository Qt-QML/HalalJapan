#ifndef PLACELISTMODEL_H
#define PLACELISTMODEL_H

#include <QAbstractListModel>
#include "placedetail.h"
#include "paginationlistmodel.h"
#include "globalfunction.h"

class PlaceListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex
               READ  getCurrentIndex
               WRITE setCurrentIndex
               NOTIFY currentIndexChanged
               )
    Q_PROPERTY(int currentPage
               READ  getCurrentPage
               WRITE setCurrentPage
               NOTIFY currentPageChanged
               )
    Q_PROPERTY(int totalPage
                   READ  getTotalPage
                   CONSTANT
                   )
    Q_PROPERTY(PaginationListModel* paginationModel
               READ  getPaginationModel
               CONSTANT
               )
    Q_PROPERTY(QVariantMap currentPlaceMap
               READ  getCurrentPlaceMap
               CONSTANT
               )
    Q_PROPERTY(PlaceDetail *currentPlaceDetail
               READ  getCurrentPlaceDetail
               CONSTANT
               )
public:
    explicit PlaceListModel(QObject *parent = 0);

    int getCurrentPage() const;
    void setCurrentPage(int value);
    void generatePage(int currentPage, int totalPage);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif

    QVariantMap getAllItemMap() const;
    void setAllItemMap(const QVariantMap &value);

//    bool compareNumber(const QString &s1, const QString &s2);
    int getTotalPage() const;
    void setTotalPage(int value);

    PaginationListModel *getPaginationModel() const;

    QVariantMap getCurrentPlaceMap() const;
    void setCurrentPlaceMap(const QVariantMap &value);

    Q_INVOKABLE void selectItemFromIndex(int index);

    void setCurrentPlaceDetailByIndex(int index);

    int getCurrentIndex() const;
    void setCurrentIndex(int value);

    PlaceDetail *getCurrentPlaceDetail();

signals:
    void currentPageChanged();
    void totalPageChanged();

    void currentIndexChanged();

public slots:
    void addItem(QVariantMap itemMap);

private:
    QStringList itemIndexList;
    QVariantMap allItemMap, currentPlaceMap;
    QHash<int, QByteArray> roles;

    PlaceDetail *currentPlaceDetail;
    PaginationListModel *paginationModel;

    int currentPage, totalPage, currentIndex;

    enum ItemRoles
    {
        IdRole = Qt::UserRole+1,
        NameRole,
        ApprovedRole,
        LastUpdateRole,
        AddressRole,
        CoordinateRole,
        CategoryRole,
        DescRole,
        EmailRole,
        LocationRole,
        PhoneRole,
        TypeRole,
        WebsiteRole
    };

};

//#if QT_VERSION < 0x050000
Q_DECLARE_METATYPE(PlaceListModel*)
//#endif

#endif // PLACELISTMODEL_H
