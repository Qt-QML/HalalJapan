#include "halaljapanapi.h"

HalalJapanAPI::HalalJapanAPI(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
    batchMode = false;

    itemListModel = new ItemListModel;
    categoryListModel = new CategoryListModel;
    producerListModel = new CategoryListModel;
    placeListModel = new PlaceListModel;

//    QObject::connect(this, SIGNAL(downloadDataFinished()), this, SLOT(checkDownloadData()));
//    QObject::connect(this, SIGNAL(batchDownloadTriggered()), this, SLOT(startBatchDownload()));

//    QObject::connect(this, SIGNAL(itemRetrieved(QVariantMap)), itemListModel, SLOT(addItem(QVariantMap)));
}

void HalalJapanAPI::firstSync()
{
    QUrl url("http://halal-japan.fuwafuwa.info/");
    url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("r", "sync");
    urlQuery.addQueryItem("last_update", "2011-01-01 00:00:00");

    url.setQuery(urlQuery);
#else
    url.addQueryItem("r", "sync");
    url.addQueryItem("last_update", "2011-01-01 00:00:00");
#endif

    QNetworkReply *reply = sendRequest(url, GET);
    connect(reply, SIGNAL(finished()), this, SLOT(firstSyncFinished()));
}

void HalalJapanAPI::firstSyncFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        bool parsingOk;

        QVariantMap contentMap = Json::parse(response, parsingOk).toMap();

        if(parsingOk)
        {
            QStringList contentMapKeys = contentMap.keys();
//            int i=0;

            QStringList contentList;
//            QString tableName;

            QVariantMap allDataMap;

            foreach (QString contentMapKey, contentMapKeys) {
                if(contentMapKey == "pages")
                    continue;

//                qDebug() << contentMap.value(contentMapKey).toString();
                contentList = contentMap.value(contentMapKey).toString().split(", ");

                /*if(contentMapKey == "places")
                    tableName = "place";
                else if(contentMapKey == "items")
                    tableName = "data";
                else
                    tableName = contentMapKey;*/

                allDataMap.insert(contentMapKey, contentList);
            }

            if(!allDataMap.empty())
            {
                databaseManager->setAllDataMap(allDataMap);

                QThread *thread = new QThread;
                databaseManager->moveToThread(thread);

                connect(thread, SIGNAL(started()), databaseManager, SLOT(firstSynchronizedStarted()));
                connect(databaseManager, SIGNAL(finished()), thread, SLOT(quit()));
//                connect(this, SIGNAL(abortBatchModeChanged()), thread, SLOT(quit()));
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                connect(thread, SIGNAL(finished()), this, SLOT(clearBusyMessage()));
                connect(thread, SIGNAL(finished()), this, SIGNAL(finished()));
                connect(thread, SIGNAL(destroyed()), this, SLOT(resetDatabaseThread()));
    //                connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
                thread->start();

                emit firstSyncChanged(false);

    //            qDebug() << allDataMap.keys() << allDataMap.value("data").toList();
//                setBatchMode(false);
            }
        }
    }

//    clearBusyMessage();
}

void HalalJapanAPI::getLastUpdate()
{
    QUrl url("http://halal-japan.fuwafuwa.info/");
    url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("r", "date");
    url.setQuery(urlQuery);
#else
    url.addQueryItem("r", "date");
#endif

    QNetworkReply *reply = sendRequest(url, GET);
    connect(reply, SIGNAL(finished()), this, SLOT(lastUpdateDownloaded()));
}

void HalalJapanAPI::lastUpdateDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        bool parsingOk;

        QVariantMap contentMap = Json::parse(response, parsingOk).toMap();

        emit lastUpdated(contentMap.value("date").toDateTime());
    }
}

void HalalJapanAPI::getUpdateDataByDate(QDateTime dateTime)
{
    QUrl url("http://halal-japan.fuwafuwa.info/");
    url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("r", "sync");
    urlQuery.addQueryItem("last_update", dateTime.toString("yyyy-MM-dd HH:mm:ss"));
//    urlQuery.addQueryItem("last_update", "2011-01-01 00:00:00");
    url.setQuery(urlQuery);
#else
    url.addQueryItem("r", "sync");
    url.addQueryItem("last_update", dateTime.toString("yyyy-MM-dd HH:mm:ss"));
#endif

    QNetworkReply *reply = sendRequest(url, GET);
    connect(reply, SIGNAL(finished()), this, SLOT(updateDataDownloaded()));
}

void HalalJapanAPI::getItemFromDatabase(int page, int limit)
{
    itemUrlList.clear();
    QVariantMap allItemMap = databaseManager->getItemInPage(page, limit);

//    qDebug() << "masuk";

    if(!allItemMap.isEmpty())
    {
        QVariantMap itemMap;
        QStringList itemKeyList = allItemMap.keys();
        QString name, id, status;

        foreach (QString key, itemKeyList)
        {
            itemMap = allItemMap.value(key).toMap();

            id = itemMap.value("id", "").toString();
            name = itemMap.value("name", "").toString();
            status = itemMap.value("status", "").toString();
//            qDebug() << itemMap;

    //        if(name.isEmpty() && approved.isEmpty())
            if(name.isEmpty() && status.isEmpty())
            {
                QUrl url("http://halal-japan.fuwafuwa.info/");
                url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
                QUrlQuery urlQuery;
                urlQuery.addQueryItem("r", "data");
                urlQuery.addQueryItem("table", "data");
                urlQuery.addQueryItem("id", id);
                url.setQuery(urlQuery);
#else
                url.addQueryItem("r", "data");
                url.addQueryItem("table", "data");
                url.addQueryItem("id", id);
#endif
                itemUrlList.append(url);
            }
            else
            {
                QString picUrl, filename;
                foreach (QString itemKey, itemMap.keys())
                {
                    if(itemKey == "pic" || itemKey == "ingredient_pic" || itemKey == "thumb")
                    {
                        picUrl = itemMap.value(itemKey).toString();
                        if(!picUrl.isEmpty())
                        {
                            filename = urlToFilename(picUrl);
                            filename.prepend(QDir::separator());
                            filename.prepend(Settings::instance()->getImagesPath());
                            picUrl.prepend("http://halal-japan.fuwafuwa.info");

                            DownloadManager *dm = new DownloadManager;
                            dm->setUrl(picUrl);
                            dm->setOutputFilename(filename);
                            dm->performDownload();
                        }
                    }
                }
            }
        }

//        qDebug() << "itemListModel->generatePage(page, itemListModel->getTotalPage());";
        itemListModel->generatePage(page, itemListModel->getTotalPage());
    }

    itemListModel->setAllItemMap(allItemMap);

    // untuk menghindari insert ke database secara bersamaan
    if(!itemUrlList.isEmpty())
    {
        setBusyMessage("Retrieve items from server...");
        setBatchMode(true);
        batchDownloadItemStarted();
    }
    else
    {
        emit finished();
    }
}

void HalalJapanAPI::getCategoryFromDatabase(int page, int limit)
{
    categoryUrlList.clear();
    QVariantMap allItemMap = databaseManager->getCategoryInPage(page, limit);

//    qSort(itemKeyList.begin(), itemKeyList.end(), compareNumber);
//    qDebug() << itemKeyList;

    if(!allItemMap.isEmpty())
    {
        QVariantMap itemMap;
        QStringList itemKeyList = allItemMap.keys();
        QString name, approved, id;

        foreach (QString key, itemKeyList)
        {
            itemMap = allItemMap.value(key).toMap();

            id = itemMap.value("id", "").toString();
            name = itemMap.value("name", "").toString();
    //        approved = itemMap.value("approved", "").toString();

    //        if(name.isEmpty() && approved.isEmpty())
            if(name.isEmpty())
            {
                QUrl url("http://halal-japan.fuwafuwa.info/");
                url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
                QUrlQuery urlQuery;
                urlQuery.addQueryItem("r", "data");
                urlQuery.addQueryItem("table", "category");
                urlQuery.addQueryItem("id", id);
                url.setQuery(urlQuery);
#else
                url.addQueryItem("r", "data");
                url.addQueryItem("table", "category");
                url.addQueryItem("id", id);
#endif
                categoryUrlList.append(url);
            }
        }

        categoryListModel->generatePage(page, categoryListModel->getTotalPage());
    }

    categoryListModel->setAllItemMap(allItemMap);

    // untuk menghindari insert ke database secara bersamaan
    if(!categoryUrlList.isEmpty())
    {
        setBusyMessage("Retrieve items from server...");
        batchDownloadCategoryStarted();
    }
    else
    {
        emit finished();
    }
}

void HalalJapanAPI::getProducerFromDatabase(int page, int limit)
{
    producerUrlList.clear();
    QVariantMap allItemMap = databaseManager->getProducerInPage(page, limit);

//    qSort(itemKeyList.begin(), itemKeyList.end(), compareNumber);
//    qDebug() << itemKeyList;

    if(!allItemMap.isEmpty())
    {
        QVariantMap itemMap;
        QStringList itemKeyList = allItemMap.keys();
        QString name, approved, id;

        foreach (QString key, itemKeyList)
        {
            itemMap = allItemMap.value(key).toMap();

            id = itemMap.value("id", "").toString();
            name = itemMap.value("name", "").toString();
    //        approved = itemMap.value("approved", "").toString();

    //        if(name.isEmpty() && approved.isEmpty())
            if(name.isEmpty())
            {
                QUrl url("http://halal-japan.fuwafuwa.info/");
                url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
                QUrlQuery urlQuery;
                urlQuery.addQueryItem("r", "data");
                urlQuery.addQueryItem("table", "producer");
                urlQuery.addQueryItem("id", id);
                url.setQuery(urlQuery);
#else
                url.addQueryItem("r", "data");
                url.addQueryItem("table", "producer");
                url.addQueryItem("id", id);
#endif
                producerUrlList.append(url);
            }
        }

        producerListModel->generatePage(page, producerListModel->getTotalPage());
    }

    producerListModel->setAllItemMap(allItemMap);

    // untuk menghindari insert ke database secara bersamaan
    if(!producerUrlList.isEmpty())
    {
        setBusyMessage("Retrieve items from server...");
        batchDownloadProducerStarted();
    }
    else
    {
        emit finished();
    }
}

void HalalJapanAPI::getPlaceFromDatabase(int page, int limit)
{
    placeUrlList.clear();
    QVariantMap allItemMap = databaseManager->getPlaceInPage(page, limit);

//    qSort(itemKeyList.begin(), itemKeyList.end(), compareNumber);
//    qDebug() << itemKeyList;

    if(!allItemMap.isEmpty())
    {
        QVariantMap itemMap;
        QStringList itemKeyList = allItemMap.keys();
        QString name, approved, id;

        foreach (QString key, itemKeyList)
        {
            itemMap = allItemMap.value(key).toMap();

            id = itemMap.value("id", "").toString();
            name = itemMap.value("name", "").toString();
    //        approved = itemMap.value("approved", "").toString();

    //        if(name.isEmpty() && approved.isEmpty())
            if(name.isEmpty())
            {
                QUrl url("http://halal-japan.fuwafuwa.info/");
                url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
                QUrlQuery urlQuery;
                urlQuery.addQueryItem("r", "data");
                urlQuery.addQueryItem("table", "place");
                urlQuery.addQueryItem("id", id);
                url.setQuery(urlQuery);
#else
                url.addQueryItem("r", "data");
                url.addQueryItem("table", "place");
                url.addQueryItem("id", id);
#endif
                placeUrlList.append(url);
            }
        }

        placeListModel->generatePage(page, placeListModel->getTotalPage());
    }

    placeListModel->setAllItemMap(allItemMap);

    // untuk menghindari insert ke database secara bersamaan
    if(!placeUrlList.isEmpty())
    {
        setBusyMessage("Retrieve items from server...");
        batchDownloadPlaceStarted();
    }
    else
    {
        emit finished();
    }
}

void HalalJapanAPI::getItemByCategory(QString category, int page, int limit)
{
    QStringList fields;
    fields << "*";

    QString queryString = QString("SELECT %1 FROM items WHERE category LIKE '%%2%' LIMIT %3, %4").arg(fields.join(",")).arg(category).arg((page-1)*limit).arg(limit);
    QVariantMap allItemMap = databaseManager->getItemByQuery(queryString, fields);

    if(allItemMap.count() > 0)
    {
        itemListModel->setCurrentPage(page);
        itemListModel->setAllItemMap(allItemMap);
    }
    else {
        if(page == 1) {
            itemListModel->setAllItemMap(allItemMap);
            alert("No item(s) found on this category");
        }
        else
            alert("No more item(s) found on this category");
    }
}

void HalalJapanAPI::getItemByProducer(QString producer, int page, int limit)
{
    QStringList fields;
    fields << "*";

    QString queryString = QString("SELECT %1 FROM items WHERE producer LIKE '%%2%' LIMIT %3, %4").arg(fields.join(",")).arg(producer).arg((page-1)*limit).arg(limit);
    QVariantMap allItemMap = databaseManager->getItemByQuery(queryString, fields);

    if(allItemMap.count() > 0)
    {
        itemListModel->setCurrentPage(page);
        itemListModel->setAllItemMap(allItemMap);
    }
    else {
        if(page == 1) {
            itemListModel->setAllItemMap(allItemMap);
            alert("No item(s) found produced by this producer");
        }
        else
            alert("No more item(s) found produced by this producer");
    }
}

void HalalJapanAPI::getItemByPlace(QString place, int page, int limit)
{
    /*QString queryString = QString("SELECT * FROM items WHERE producer LIKE '%%1%' LIMIT %2, %3").arg(place).arg((page-1)*limit).arg(limit);
    QVariantMap allItemMap = databaseManager->getItemByQuery(queryString, page, limit);

    if(allItemMap.count() > 0)
    {
        itemListModel->setCurrentPage(page);
        itemListModel->setAllItemMap(allItemMap);
    }
    else {
        if(page == 1) {
            itemListModel->setAllItemMap(allItemMap);
            alert("No item(s) found on this location");
        }
        else
            alert("No more item(s) found on this location");
    }*/
}

void HalalJapanAPI::retrieveAllItem()
{
    itemUrlList.clear();

    QStringList fields;
    fields << "id" << "name" << "status";

    QString queryString = QString("SELECT %1 FROM items ORDER BY id ASC;").arg(fields.join(","));
    QVariantMap allItemMap = databaseManager->getItemByQuery(queryString, fields);
//    allItemMap.clear();
    if(allItemMap.count() > 0)
    {
        QVariantMap itemMap;
        QStringList allItemMapKeys = allItemMap.keys();
        qSort(allItemMapKeys.begin(), allItemMapKeys.end(), compareNumber);
        QString name, id, status;

        foreach (QString key, allItemMapKeys)
        {
            itemMap = allItemMap.value(key).toMap();

            id = itemMap.value("id", "").toString();
            name = itemMap.value("name", "").toString();
            status = itemMap.value("status", "").toString();

            if(name.isEmpty() && status.isEmpty())
            {
//                qDebug() << id << name << status << itemMap;
                QUrl url("http://halal-japan.fuwafuwa.info/");
                url.setPath("/jh-update.php");

#if QT_VERSION >= 0x050000
                QUrlQuery urlQuery;
                urlQuery.addQueryItem("r", "data");
                urlQuery.addQueryItem("table", "data");
                urlQuery.addQueryItem("id", id);
                url.setQuery(urlQuery);
#else
                url.addQueryItem("r", "data");
                url.addQueryItem("table", "data");
                url.addQueryItem("id", id);
#endif
                itemUrlList.append(url);
            }
        }
//        itemListModel->setCurrentPage(page);
//        itemListModel->setAllItemMap(allItemMap);
    }

    // untuk menghindari insert ke database secara bersamaan
    if(!itemUrlList.isEmpty())
    {
        setBatchMode(true);
        setBusyMessage("Retrieve all items from server...");
        batchDownloadItemStarted();
    }
    else
    {
        emit finished();
    }
}

void HalalJapanAPI::abortBatchMode()
{
    setBatchMode(false);
    emit abortBatchModeChanged();
    emit finished();
}

QNetworkReply *HalalJapanAPI::sendRequest(QUrl url, HttpMethod method)
{
    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("User-Agent", "Halal Food App Using Maemo 5");
    request.setUrl(url);

    if(method == GET)
        return manager->get(request);
    else if(method == POST)
    {
#if QT_VERSION >= 0x050000
        return manager->post(request, url.query().toLatin1());
#endif
    }

    return 0;
}

void HalalJapanAPI::batchDownloadItemStarted()
{
    if(!itemUrlList.isEmpty()) {
        QNetworkReply *reply = sendRequest(itemUrlList.takeFirst(), GET);
        QObject::connect(reply, SIGNAL(finished()), this, SLOT(batchItemDownloaded()));
        QObject::connect(this, SIGNAL(abortBatchModeChanged()), reply, SLOT(abort()));
    }
    else
    {
        setBatchMode(false);
        emit finished();
        clearBusyMessage();
    }
}

void HalalJapanAPI::batchDownloadCategoryStarted()
{
    if(!categoryUrlList.isEmpty())
    {
        QNetworkReply *reply = sendRequest(categoryUrlList.takeFirst(), GET);
        QObject::connect(reply, SIGNAL(finished()), this, SLOT(batchCategoryDownloaded()));
        QObject::connect(this, SIGNAL(abortBatchModeChanged()), reply, SLOT(abort()));
    }
    else
    {
        emit finished();
        clearBusyMessage();
    }
}

void HalalJapanAPI::batchDownloadProducerStarted()
{
    if(!producerUrlList.isEmpty())
    {
        QNetworkReply *reply = sendRequest(producerUrlList.takeFirst(), GET);
        QObject::connect(reply, SIGNAL(finished()), this, SLOT(batchProducerDownloaded()));
        QObject::connect(this, SIGNAL(abortBatchModeChanged()), reply, SLOT(abort()));
    }
    else
    {
        emit finished();
        clearBusyMessage();
    }
}

void HalalJapanAPI::batchDownloadPlaceStarted()
{
    if(!placeUrlList.isEmpty())
    {
        QNetworkReply *reply = sendRequest(placeUrlList.takeFirst(), GET);
        QObject::connect(reply, SIGNAL(finished()), this, SLOT(batchPlaceDownloaded()));
        QObject::connect(this, SIGNAL(abortBatchModeChanged()), reply, SLOT(abort()));
    }
    else
    {
        emit finished();
        clearBusyMessage();
    }
}

void HalalJapanAPI::batchItemDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
//    qDebug() << reply->url().toString();

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        QVariantMap contentMap = itemResponseDataToMap(response);

        if(!contentMap.isEmpty())
        {
            itemListModel->addItem(contentMap);
            databaseManager->prepareInsertData("items", contentMap, true);

            QThread *thread = new QThread;
            databaseManager->moveToThread(thread);

            connect(thread, SIGNAL(started()), databaseManager, SLOT(executeQuery()));
            connect(databaseManager, SIGNAL(finished()), thread, SLOT(quit()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), this, SLOT(batchDownloadItemStarted()));
            connect(thread, SIGNAL(destroyed()), this, SLOT(resetDatabaseThread()));
//                connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
            thread->start();
        }
//        batchDownloadItemStarted();
    }
}

void HalalJapanAPI::batchCategoryDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        QVariantMap contentMap = categoryResponseDataToMap(response);

        if(!contentMap.isEmpty())
        {
            categoryListModel->addItem(contentMap);
            databaseManager->prepareInsertData("category", contentMap, true);

            QThread *thread = new QThread;
            databaseManager->moveToThread(thread);

            connect(thread, SIGNAL(started()), databaseManager, SLOT(executeQuery()));
            connect(databaseManager, SIGNAL(finished()), thread, SLOT(quit()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), this, SLOT(batchDownloadCategoryStarted()));
            connect(thread, SIGNAL(destroyed()), this, SLOT(resetDatabaseThread()));
//                connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
            thread->start();
        }
//        batchDownloadItemStarted();
    }
}

void HalalJapanAPI::batchProducerDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        QVariantMap contentMap = categoryResponseDataToMap(response);

        if(!contentMap.isEmpty())
        {
            producerListModel->addItem(contentMap);
            databaseManager->prepareInsertData("producer", contentMap, true);

            QThread *thread = new QThread;
            databaseManager->moveToThread(thread);

            connect(thread, SIGNAL(started()), databaseManager, SLOT(executeQuery()));
            connect(databaseManager, SIGNAL(finished()), thread, SLOT(quit()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), this, SLOT(batchDownloadProducerStarted()));
            connect(thread, SIGNAL(destroyed()), this, SLOT(resetDatabaseThread()));
//                connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
            thread->start();
        }
//        batchDownloadItemStarted();
    }
}

void HalalJapanAPI::batchPlaceDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        return;
    }
    else
    {
        QByteArray response = reply->readAll();
        bool parsingOk;

        QVariantMap contentMap = Json::parse(response, parsingOk).toMap();

        if(parsingOk)
        {
            placeListModel->addItem(contentMap);
            databaseManager->prepareInsertData("places", contentMap, true);

            QThread *thread = new QThread;
            databaseManager->moveToThread(thread);

            connect(thread, SIGNAL(started()), databaseManager, SLOT(executeQuery()));
            connect(databaseManager, SIGNAL(finished()), thread, SLOT(quit()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), this, SLOT(batchDownloadPlaceStarted()));
            connect(thread, SIGNAL(destroyed()), this, SLOT(resetDatabaseThread()));
//                connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
            thread->start();
        }
//        batchDownloadItemStarted();
    }
}

bool HalalJapanAPI::getBatchMode() const
{
    return batchMode;
}

void HalalJapanAPI::setBatchMode(bool value)
{
    batchMode = value;
    emit batchModeChanged();
}

DatabaseManager *HalalJapanAPI::getDatabaseManager() const
{
    return databaseManager;
}

void HalalJapanAPI::setDatabaseManager(DatabaseManager *value)
{
    databaseManager = value;
}

void HalalJapanAPI::resetDatabaseThread()
{
    databaseManager->moveToThread(QApplication::instance()->thread());
}

QString HalalJapanAPI::getBusyMessage() const
{
    return busyMessage;
}

void HalalJapanAPI::setBusyMessage(const QString &value)
{
    busyMessage = value;
    emit busyMessageChanged();
}

void HalalJapanAPI::clearBusyMessage()
{
    busyMessage = QString();
    emit busyMessageChanged();
}

QVariantMap HalalJapanAPI::itemResponseDataToMap(QByteArray response)
{
//    qDebug() << response;

    bool parsingOk;

    QVariantMap contentMap = Json::parse(response, parsingOk).toMap();

    if(parsingOk)
    {
        QString picUrl;
        QString filename;

        foreach (QString key, contentMap.keys())
        {
            if(key == "pic" || key == "ingredient_pic" || key == "thumb")
            {
                picUrl = contentMap.value(key).toString();
                if(!picUrl.isEmpty())
                {
                    filename = urlToFilename(picUrl);
                    filename.prepend(QDir::separator());
                    filename.prepend(Settings::instance()->getImagesPath());
                    picUrl.prepend("http://halal-japan.fuwafuwa.info");

//                    qDebug() << picUrl << filename;

                    DownloadManager *dm = new DownloadManager;
                    dm->setUrl(picUrl);
                    dm->setOutputFilename(filename);
                    dm->performDownload();
                }
            }
        }
    }

    return contentMap;
}

QVariantMap HalalJapanAPI::categoryResponseDataToMap(QByteArray response)
{
    bool parsingOk;

    QVariantMap contentMap = Json::parse(response, parsingOk).toMap();

    if(parsingOk)
    {
        return contentMap;
    }

    return QVariantMap();
}

void HalalJapanAPI::setItemTotalPage(int totalPage)
{
    itemListModel->setTotalPage(totalPage);
}

void HalalJapanAPI::setCategoryTotalPage(int totalPage)
{
    categoryListModel->setTotalPage(totalPage);
}

void HalalJapanAPI::setProducerTotalPage(int totalPage)
{
    producerListModel->setTotalPage(totalPage);
}

void HalalJapanAPI::setPlaceTotalPage(int totalPage)
{
    placeListModel->setTotalPage(totalPage);
}

ItemListModel *HalalJapanAPI::getItemListModel() const
{
    return itemListModel;
}

CategoryListModel *HalalJapanAPI::getCategoryListModel() const
{
    return categoryListModel;
}

CategoryListModel *HalalJapanAPI::getProducerListModel() const
{
    return producerListModel;
}

PlaceListModel *HalalJapanAPI::getPlaceListModel() const
{
    return placeListModel;
}

