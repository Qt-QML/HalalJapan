#ifndef PLACEDETAIL_H
#define PLACEDETAIL_H

#include <QObject>
#include <QVariant>

class PlaceDetail : public QObject
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
    Q_PROPERTY(QString itemApproved
               READ  getItemApproved
               CONSTANT
               )
    Q_PROPERTY(QString itemLastUpdate
               READ  getItemLastUpdate
               CONSTANT
               )
    Q_PROPERTY(QString itemAddress
               READ  getItemAddress
               CONSTANT
               )
    Q_PROPERTY(QString itemCoordinate
               READ  getItemCoordinate
               CONSTANT
               )
    Q_PROPERTY(QString itemDesc
               READ  getItemDesc
               CONSTANT
               )
    Q_PROPERTY(QString itemEmail
               READ  getItemEmail
               CONSTANT
               )
    Q_PROPERTY(QString itemLocation
               READ  getItemLocation
               CONSTANT
               )
    Q_PROPERTY(QString itemPhone
               READ  getItemPhone
               CONSTANT
               )
    Q_PROPERTY(QString itemType
               READ  getItemType
               CONSTANT
               )
    Q_PROPERTY(QString itemWebsite
               READ  getItemWebsite
               CONSTANT
               )
public:
    explicit PlaceDetail(QObject *parent = 0);

    QVariantMap getItemMap() const;
    void setItemMap(const QVariantMap &value);

    QString getItemId();
    QString getItemName();
    bool getItemApproved();
    QString getItemLastUpdate();

    QString getItemAddress();
    QString getItemCoordinate();
    QString getItemDesc();
    QString getItemEmail();
    QString getItemLocation();
    QString getItemPhone();
    QString getItemType();
    QString getItemWebsite();

signals:
    void itemMapChanged();

public slots:

private:
    QVariantMap itemMap;
};

#endif // PLACEDETAIL_H
