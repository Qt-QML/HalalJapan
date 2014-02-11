#ifndef HALALJAPANAPI_H
#define HALALJAPANAPI_H

#include <QObject>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif

#include <QDate>
#include "json.h"
#include "databasemanager.h"
#include "downloadmanager.h"
#include "categorylistmodel.h"
#include "itemlistmodel.h"
#include "globalfunction.h"
#include "placelistmodel.h"

using namespace QtJson;

enum HttpMethod {
    GET,   //!< Sets the HTTP method to GET
    POST,  //!< Sets the HTTP method to POST
    HEAD,  //!< Sets the HTTP method to HEAD
    DELETE,  //!< Sets the HTTP method to DELETE
    PUT   //!< Sets the HTTP method to PUT
};

class HalalJapanAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool batchMode
               READ getBatchMode
               WRITE setBatchMode
               NOTIFY batchModeChanged
               )

    Q_PROPERTY(ItemListModel* itemListModel
               READ getItemListModel
               CONSTANT
               )

    Q_PROPERTY(CategoryListModel* categoryListModel
               READ getCategoryListModel
               CONSTANT
               )

    Q_PROPERTY(CategoryListModel* producerListModel
               READ getProducerListModel
               CONSTANT
               )

    Q_PROPERTY(PlaceListModel* placeListModel
               READ getPlaceListModel
               CONSTANT
               )

    Q_PROPERTY(QString busyMessage
               READ  getBusyMessage
               WRITE setBusyMessage
               NOTIFY busyMessageChanged
               )
public:
    explicit HalalJapanAPI(QObject *parent = 0);

    Q_INVOKABLE void firstSync();
    Q_INVOKABLE void getLastUpdate();
    Q_INVOKABLE void getUpdateDataByDate(QDateTime dateTime);

    Q_INVOKABLE void getItemFromDatabase(int page, int limit);
    Q_INVOKABLE void getCategoryFromDatabase(int page, int limit);
    Q_INVOKABLE void getProducerFromDatabase(int page, int limit);
    Q_INVOKABLE void getPlaceFromDatabase(int page, int limit);

    Q_INVOKABLE void getItemByCategory(QString category, int page, int limit);
    Q_INVOKABLE void getItemByProducer(QString producer, int page, int limit);
    Q_INVOKABLE void getItemByPlace(QString place, int page, int limit);

    Q_INVOKABLE void retrieveAllItem();
    Q_INVOKABLE void abortBatchMode();

    QNetworkReply *sendRequest(QUrl url, HttpMethod method);
    DatabaseManager *getDatabaseManager() const;
    void setDatabaseManager(DatabaseManager *value);

    bool getBatchMode() const;
    void setBatchMode(bool value);

    QString getBusyMessage() const;
    void setBusyMessage(const QString &value);

    ItemListModel *getItemListModel() const;
    CategoryListModel *getCategoryListModel() const;
    CategoryListModel *getProducerListModel() const;
    PlaceListModel *getPlaceListModel() const;

    QVariantMap itemResponseDataToMap(QByteArray response);
    QVariantMap categoryResponseDataToMap(QByteArray response);
signals:
    void abortBatchModeChanged();
    void batchModeChanged();

    void lastUpdated(QDateTime lastUpdate);
    void startBatchDownloadItem();

    void itemRetrieved(QVariantMap itemMap);
    void alert(QString message);

    void busyMessageChanged();
    void finished();

    void firstSyncChanged(bool ok);

public slots:
    void lastUpdateDownloaded();
    void firstSyncFinished();

    void batchDownloadItemStarted();
    void batchDownloadCategoryStarted();
    void batchDownloadProducerStarted();
    void batchDownloadPlaceStarted();

    void batchItemDownloaded();
    void batchCategoryDownloaded();
    void batchProducerDownloaded();
    void batchPlaceDownloaded();

    void resetDatabaseThread();
    void clearBusyMessage();
    void setItemTotalPage(int totalPage);
    void setCategoryTotalPage(int totalPage);
    void setProducerTotalPage(int totalPage);
    void setPlaceTotalPage(int totalPage);

private:
    QNetworkAccessManager *manager;
    DatabaseManager *databaseManager;

    QList<QUrl> itemUrlList;
    QList<QUrl> categoryUrlList;
    QList<QUrl> producerUrlList;
    QList<QUrl> placeUrlList;
    QString busyMessage;

    bool batchMode;
    QString currentState;

    ItemListModel *itemListModel;
    CategoryListModel *categoryListModel;
    CategoryListModel *producerListModel;
    PlaceListModel *placeListModel;
};

#endif // HALALJAPANAPI_H
