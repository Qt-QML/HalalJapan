#ifndef CATEGORYDETAIL_H
#define CATEGORYDETAIL_H

#include <QObject>
#include <QVariant>

class CategoryDetail : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString itemId
               READ  getItemId
               CONSTANT
               )
    Q_PROPERTY(QString itemName
               READ  getItemName
               CONSTANT
               )
    Q_PROPERTY(bool itemApproved
               READ  getItemApproved
               CONSTANT
               )
    Q_PROPERTY(QString itemLastUpdate
               READ  getItemLastUpdate
               CONSTANT
               )
public:
    explicit CategoryDetail(QObject *parent = 0);

    QString getItemId();
    QString getItemName();
    bool getItemApproved();
    QString getItemLastUpdate();

    QVariantMap getItemMap() const;
    void setItemMap(const QVariantMap &value);

signals:
    void itemMapChanged();

public slots:

private:
    QVariantMap itemMap;
};

#endif // CATEGORYDETAIL_H
