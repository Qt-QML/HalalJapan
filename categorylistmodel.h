#ifndef CATEGORYLISTMODEL_H
#define CATEGORYLISTMODEL_H

#include <QAbstractListModel>
#include "paginationlistmodel.h"
#include "globalfunction.h"
#include "categorydetail.h"

class CategoryListModel : public QAbstractListModel
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
    Q_PROPERTY(QVariantMap currentCategoryMap
               READ  getCurrentCategoryMap
               CONSTANT
               )
    Q_PROPERTY(CategoryDetail* currentCategoryDetail
               READ  getCurrentCategoryDetail
               CONSTANT
               )
public:
    explicit CategoryListModel(QObject *parent = 0);

    int getCurrentPage() const;
    void setCurrentPage(int value);

    int getTotalPage() const;
    void setTotalPage(int value);

    void generatePage(int currentPage, int totalPage);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif

    QVariantMap getAllItemMap() const;
    void setAllItemMap(const QVariantMap &value);

//    bool compareNumber(const QString &s1, const QString &s2);
    PaginationListModel *getPaginationModel() const;

    QVariantMap getCurrentCategoryMap() const;
    void setCurrentCategoryMap(const QVariantMap &value);

    Q_INVOKABLE void selectItemFromIndex(int index);

    int getCurrentIndex() const;
    void setCurrentIndex(int value);

    void setCurrentCategoryDetailByIndex(int index);

    CategoryDetail *getCurrentCategoryDetail() const;

signals:
    void currentPageChanged();
    void totalPageChanged();

    void currentIndexChanged();

public slots:
    void addItem(QVariantMap itemMap);

private:
    QStringList itemIndexList;
    QVariantMap allItemMap, currentCategoryMap;
    QHash<int, QByteArray> roles;

    CategoryDetail *currentCategoryDetail;

    PaginationListModel *paginationModel;

    int currentPage, totalPage, currentIndex;

    enum ItemRoles
    {
        IdRole = Qt::UserRole+1,
        NameRole,
        ApprovedRole,
        LastUpdateRole,
    };

};

//#if QT_VERSION < 0x050000
Q_DECLARE_METATYPE(CategoryListModel*)
//#endif

#endif // CATEGORYLISTMODEL_H
