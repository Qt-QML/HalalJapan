#ifndef ITEMLISTMODEL_H
#define ITEMLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "paginationlistmodel.h"
#include "settings.h"
#include "globalfunction.h"
#include "itemdetail.h"

class ItemListModel : public QAbstractListModel
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
    Q_PROPERTY(QVariantMap currentItemMap
               READ  getCurrentItemMap
               CONSTANT
               )
    Q_PROPERTY(ItemDetail* currentItemDetail
               READ  getCurrentItemDetail
               CONSTANT
               )
public:
    explicit ItemListModel(QObject *parent = 0);

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

    QVariantMap getCurrentItemMap() const;
    void setCurrentItemMap(const QVariantMap &value);

    Q_INVOKABLE void selectItemFromIndex(int index);

    int getCurrentIndex() const;
    void setCurrentIndex(int value);


    ItemDetail *getCurrentItemDetail() const;
    void setCurrentItemDetail(ItemDetail *value);
    void setCurrentItemDetailByIndex(const int index);

signals:
    void currentPageChanged();
    void totalPageChanged();
    void currentIndexChanged();

public slots:
    void addItem(QVariantMap itemMap);

private:
    QStringList itemIndexList;
    QVariantMap allItemMap, currentItemMap;
    QHash<int, QByteArray> roles;

    PaginationListModel *paginationModel;

    ItemDetail *currentItemDetail;

    int currentPage, totalPage, currentIndex;

    enum ItemRoles
    {
        IdRole = Qt::UserRole+1,
        NameRole,
        ApprovedRole,
        LastUpdateRole,
        BarcodeRole,
        CategoryRole,
        ConfirmDateRole,
        ContributorRole,
        DescRole,
        IngredientPicRole,
        PicRole,
        ProducerRole,
        ReasonRole,
        StatusRole,
        ThumbRole
    };

};

//#if QT_VERSION < 0x050000
Q_DECLARE_METATYPE(ItemListModel*)
//#endif

#endif // ITEMLISTMODEL_H
