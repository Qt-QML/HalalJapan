#ifndef PAGINATIONLISTMODEL_H
#define PAGINATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class PaginationListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PaginationListModel(QObject *parent = 0);

    void generatePage(int currentPage, int totalPage);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif

    int getItemCount();
    
    int getCurrentPage() const;
    void setCurrentPage(int value);

    int getTotalPage() const;
    void setTotalPage(int value);

signals:
    
public slots:

private:
    QStringList pageList;
    QHash<int, QByteArray> roles;
    
    int currentPage, totalPage;

    enum ItemRoles
    {
        TextLabelRole = Qt::UserRole+1,
        PageNumberRole
    };
};

#if QT_VERSION < 0x050000
Q_DECLARE_METATYPE(PaginationListModel*)
#endif

#endif // PAGINATIONLISTMODEL_H
