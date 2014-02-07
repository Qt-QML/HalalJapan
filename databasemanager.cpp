#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    isUpdate = false;
    filename = "HalalFood.db";

    connect(this, SIGNAL(finished()), this, SLOT(clearQuery()));
    connect(this, SIGNAL(itemInserted()), this, SLOT(findItemTotalPage()));
    connect(this, SIGNAL(categoryInserted()), this, SLOT(findCategoryTotalPage()));
}

DatabaseManager::DatabaseManager(QString filename, QObject *parent) :
    QObject(parent)
{
    isUpdate = false;

    setFilename(filename);
    connect(this, SIGNAL(finished()), this, SLOT(clearQuery()));
    connect(this, SIGNAL(itemInserted()), this, SLOT(findItemTotalPage()));
    connect(this, SIGNAL(categoryInserted()), this, SLOT(findCategoryTotalPage()));
    connect(this, SIGNAL(producerInserted()), this, SLOT(findProducerTotalPage()));
}

bool DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    query = QSqlQuery(db);

#if defined(Q_OS_LINUX) || defined(Q_WS_MAEMO_5) || defined(Q_OS_BLACKBERRY)
    // NOTE: We have to store database file into user home folder in Linux

    QString databasePath = Settings::instance()->getResourcesPath();

    if(databasePath.isEmpty())
    {
#if QT_VERSION >= 0x050000
        // android
        // data/data/org.qtproject.example.HalalFood/files/.HalalFood/
        databasePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
#else
        databasePath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#endif
        databasePath.append(QDir::separator()).append(".HalalFood");
        databasePath.append(QDir::separator()).append(filename);
        databasePath = QDir::toNativeSeparators(databasePath);

    }
    else
    {
        databasePath = databasePath.append(QDir::separator()).append(filename);
    }

    db.setDatabaseName(databasePath);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName(filename);
#endif

    emit finished();

    // Open databasee
    return db.open();
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::createTables()
{
    query.clear();

    // Create table "category"
    bool ret = false;
    if (db.isOpen())
    {
        ret = query.exec("CREATE TABLE category "
                         "(id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "approved INTEGER,"
                         "last_update INTEGER)"
               );
    }

    // Create table "items"
    ret = false;
    if (db.isOpen())
    {
        ret = query.exec("CREATE TABLE items"
                         "(id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "approved INTEGER,"
                         "last_update INTEGER,"
                         "barcode STRING,"
                         "category STRING,"
                         "confirm_date INTEGER,"
                         "contributor STRING,"
                         "desc TEXT,"
                         "ingredient_pic TEXT,"
                         "pic STRING,"
                         "producer STRING,"
                         "reason TEXT,"
                         "status STRING,"
                         "thumb STRING)"
               );
    }

    // Create table "producer"
    ret = false;
    if (db.isOpen())
    {
        ret = query.exec("CREATE TABLE producer"
                         "(id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "approved INTEGER,"
                         "last_update INTEGER)"
               );
    }

    ret = false;
    if (db.isOpen())
    {
        ret = query.exec("CREATE TABLE places"
                         "(id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "address TEXT,"
                         "approved INTEGER,"
                         "coordinate STRING,"
                         "desc TEXT,"
                         "email STRING,"
                         "last_update INTEGER,"
                         "location STRING,"
                         "phone STRING,"
                         "type STRING,"
                         "website STRING)"
               );
    }

    emit finished();

    return ret;
}

QString DatabaseManager::getFilename() const
{
    return filename;
}

void DatabaseManager::setFilename(const QString &value)
{
    filename = value;
}

QVariantMap DatabaseManager::getAllDataMap() const
{
    return allDataMap;
}

void DatabaseManager::setAllDataMap(const QVariantMap &value)
{
    allDataMap = value;
}

void DatabaseManager::firstSynchronizedStarted()
{
    if(!allDataMap.isEmpty())
    {
        QString replaceString = "IGNORE";
        QString tableColumn = "id";

        QString queryString;
        QStringList contentList, valueList;
        QString valueString;
        int counter;

        foreach (QString tableName, allDataMap.keys())
        {
            contentList = allDataMap.value(tableName).toStringList();

            counter = 0;
            foreach (QString value, contentList) {
                valueList.append(value);
                counter++;

                if(counter % 200 == 0)
                {
                    valueString = valueList.join("), (");

                    queryString = QString("INSERT OR %1 INTO %2 (%3) VALUES (%4)").arg(replaceString).arg(tableName).arg(tableColumn).arg(valueString);
                    if(query.exec(queryString))
                        valueList.clear();
                }
            }

            valueString = valueList.join("), (");
            queryString = QString("INSERT OR %1 INTO %2 (%3) VALUES (%4)").arg(replaceString).arg(tableName).arg(tableColumn).arg(valueString);
            if(query.exec(queryString))
                valueList.clear();
        }
    }

    emit itemInserted();
    emit categoryInserted();
    emit producerInserted();
    emit placeInserted();
    emit finished();
}

void DatabaseManager::clearQuery()
{
    query.clear();
}

void DatabaseManager::findItemTotalPage()
{
    int totalPage = findTotalPage("items", Settings::instance()->getItemPerPage());
    emit itemTotalPageChanged(totalPage);
}

void DatabaseManager::findCategoryTotalPage()
{
    int totalPage = findTotalPage("Category", Settings::instance()->getCategoryPerPage());
    emit categoryTotalPageChanged(totalPage);
}

void DatabaseManager::findProducerTotalPage()
{
    int totalPage = findTotalPage("producer", Settings::instance()->getProducerPerPage());
    emit producerTotalPageChanged(totalPage);
}

void DatabaseManager::findPlaceTotalPage()
{
    int totalPage = findTotalPage("places", Settings::instance()->getPlacePerPage());
    emit placeTotalPageChanged(totalPage);
}

bool DatabaseManager::executeQuery()
{
    if(query.exec() && !isUpdate)
        emit itemInserted();

    emit finished();
}
QSqlQuery DatabaseManager::getQuery() const
{
    return query;
}

void DatabaseManager::setQuery(const QSqlQuery &value)
{
    query = value;
}


bool DatabaseManager::getIsUpdate() const
{
    return isUpdate;
}

void DatabaseManager::setIsUpdate(bool value)
{
    isUpdate = value;
}

bool DatabaseManager::deleteDB()
{
    // Close database
    db.close();

#if defined(Q_OS_LINUX) || defined(Q_WS_MAEMO_5) || defined(Q_OS_BLACKBERRY)
    // NOTE: We have to store database file into user home folder in Linux

    QString databasePath = Settings::instance()->getResourcesPath();

    if(databasePath.isEmpty())
    {
#if QT_VERSION >= 0x050000
        // android
        // data/data/org.qtproject.example.HalalFood/files/.HalalFood/
        databasePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
#else
        databasePath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#endif
        databasePath.append(QDir::separator()).append(".HalalFood");
        databasePath.append(QDir::separator()).append(filename);
        databasePath = QDir::toNativeSeparators(databasePath);

    }
    else
    {
        databasePath = databasePath.append(QDir::separator()).append(filename);
    }

    return QFile::remove(databasePath);
#else

    // Remove created database binary file
    return QFile::remove(filename);
#endif
}

int DatabaseManager::findTotalPage(QString tableName, int limit)
{
    QString queryString = QString("SELECT COUNT(id) FROM %1").arg(tableName);
    query.clear();
    query.exec(queryString);
    int recordCount = 0;
    int currentTotalPage = 1;

    while(query.next())
    {
        recordCount = query.value(0).toInt();
        currentTotalPage = ceil((double)recordCount / limit);
        if(currentTotalPage == 0)
            currentTotalPage = 1;
    }

    return currentTotalPage;
}

bool DatabaseManager::insertCategory(QVariantMap categoryMap)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        QString queryString = QString("INSERT OR REPLACE INTO category(id, name, approved, last_update) VALUES(%1,'%2',%3,%4)")
                .arg(categoryMap.value("id").toInt())
                .arg(categoryMap.value("name").toString())
                .arg(categoryMap.value("approved").toInt())
                .arg(QDateTime::fromString(categoryMap.value("last_update", "2011-01-01 00:00:00").toString(), "yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch());

        ret = query.exec(queryString);
    }

    return ret;
}

bool DatabaseManager::insertItem(QVariantMap itemMap)
{
    query.clear();
    bool ret = false;
    if (db.isOpen())
    {
        QString lastUpdateString = itemMap.value("last_update", "2011-01-01 00:00:00").toString();
        QString confirmDateString = (itemMap.value("confirm_date").toString() == "0000-00-00" || itemMap.value("confirm_date").isNull()) ? lastUpdateString : itemMap.value("confirm_date").toString();

        QString queryString = QString("INSERT OR REPLACE INTO items(id, name, approved, last_update, barcode, category, confirm_date, contributor, desc, ingredient_pic, pic, producer, reason, status, thumb) VALUES(%1,'%2',%3,%4,'%5','%6',%7,'%8','%9','%10','%11','%12','%13','%14','%15')")
                .arg(itemMap.value("id").toInt())
                .arg(itemMap.value("name").toString().replace("'", "''"))
                .arg(itemMap.value("approved").toInt())
                .arg(QDateTime::fromString(lastUpdateString, "yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch())
                .arg(itemMap.value("barcode").toString())
                .arg(itemMap.value("category").toString())
                .arg(QDateTime::fromString(confirmDateString, "yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch())
                .arg(itemMap.value("contributor").toString())
                .arg(itemMap.value("desc").toString().replace("'", "''"))
                .arg(itemMap.value("ingredient_pic").toString())
                .arg(itemMap.value("pic").toString())
                .arg(itemMap.value("producer").toString().replace("'", "''"))
                .arg(itemMap.value("reason").toString())
                .arg(itemMap.value("status").toString())
                .arg(itemMap.value("thumb").toString());

        ret = query.exec(queryString);

//        qDebug() << lastUpdateString << itemMap.value("confirm_date", lastUpdateString).toString() << ret << itemMap.value("id").toInt();
//        qDebug() << itemMap.value("name").toString();
    }

    if(ret)
        emit itemInserted();

    return ret;
}

bool DatabaseManager::insertProducer(QVariantMap producerMap)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        QString queryString = QString("INSERT OR REPLACE INTO producer(id, name, approved, last_update) VALUES(%1,'%2',%3,%4)")
                .arg(producerMap.value("id").toInt())
                .arg(producerMap.value("name").toString())
                .arg(producerMap.value("approved").toInt())
                .arg(QDateTime::fromString(producerMap.value("last_update", "2011-01-01 00:00:00").toString(), "yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch());

        ret = query.exec(queryString);
    }

    return ret;
}

bool DatabaseManager::insertPlace(QVariantMap placeMap)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        QString queryString = QString("INSERT OR REPLACE INTO places(id, name, address, approved, coordinate, desc, email, last_update, location, phone, type, website) VALUES(%1,'%2','%3',%4,'%5','%6','%7',%8,'%9','%10','%11','%12')")
                .arg(placeMap.value("id").toInt())
                .arg(placeMap.value("name").toString())
                .arg(placeMap.value("address").toString())
                .arg(placeMap.value("approved").toString())
                .arg(placeMap.value("coordinate").toString())
                .arg(placeMap.value("desc").toString())
                .arg(placeMap.value("email").toString())
                .arg(QDateTime::fromString(placeMap.value("last_update", "2011-01-01 00:00:00").toString(), "yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch())
                .arg(placeMap.value("location").toString())
                .arg(placeMap.value("phone").toString())
                .arg(placeMap.value("type").toString())
                .arg(placeMap.value("website").toString());

        ret = query.exec(queryString);
    }

    return ret;
}

void DatabaseManager::prepareInsertData(QString tableName, QVariantMap dataMap, bool update)
{
    query.clear();
    setIsUpdate(update);

    QString replaceString = "IGNORE";
    if(update)
    {
        replaceString = "REPLACE";
    }

    QString tableColumn, targetColumn;

    foreach (QString key, dataMap.keys()) {
        tableColumn.append(key).append(",");
        targetColumn.append("?,");
    }

    tableColumn.remove(QRegExp(",$"));
    targetColumn.remove(QRegExp(",$"));

    QString queryString = QString("INSERT OR %1 INTO %2 (%3) VALUES (%4)").arg(replaceString).arg(tableName).arg(tableColumn).arg(targetColumn);
    query.prepare(queryString);

    foreach (QString key, dataMap.keys()) {
        query.addBindValue(dataMap.value(key).toString());
    }
}

bool DatabaseManager::executeQueryString(QString queryString)
{
    query.clear();
    bool ret = false;
    if (db.isOpen())
    {
        qDebug() << queryString;
        ret = query.exec(queryString);
    }

    return ret;
}

QVariantMap DatabaseManager::getItemByQuery(QString queryString, QStringList fields)
{
    query.exec(queryString);

    QVariantMap allItemMap, itemMap;
    int id;

    if(fields.count() == 1 && fields.at(0) == "*")
    {
        while (query.next())
        {
            id = query.value(0).toInt();
            itemMap.insert("id", id);
            itemMap.insert("name", query.value(1).toString());
            itemMap.insert("approved", query.value(2).toBool());
            itemMap.insert("last_update", query.value(3).toInt());
            itemMap.insert("barcode", query.value(4).toString());
            itemMap.insert("category", query.value(5).toString());
            itemMap.insert("confirm_date", query.value(6).toInt());
            itemMap.insert("contributor", query.value(7).toString());
            itemMap.insert("desc", query.value(8).toString());
            itemMap.insert("ingredient_pic", query.value(9).toString());
            itemMap.insert("pic", query.value(10).toString());
            itemMap.insert("producer", query.value(11).toString());
            itemMap.insert("reason", query.value(12).toString());
            itemMap.insert("status", query.value(13).toString());
            itemMap.insert("thumb", query.value(14).toString());

            allItemMap.insert(QString::number(id), itemMap);
        }
    }
    else
    {
        int fieldsCount = fields.count();
        QString id;
        while (query.next())
        {
            id = "";
            for(int i=0; i< fieldsCount; i++)
            {
                itemMap.insert(fields.at(i), query.value(i).toString());

                if(fields.at(i) == "id")
                    id = query.value(i).toString();
            }

            if(!id.isEmpty())
                allItemMap.insert(id, itemMap);
        }
    }

    return allItemMap;
}

QVariantMap DatabaseManager::getItemInPage(int page, int limit)
{
    QString queryString = QString("SELECT id, name, approved, last_update, barcode, category, confirm_date, contributor, desc, ingredient_pic, pic, producer, reason, status, thumb FROM items LIMIT %1, %2").arg((page-1)*limit).arg(limit);
    query.exec(queryString);

    QVariantMap allItemMap, itemMap;
    int id;

    while (query.next())
    {
        id = query.value(0).toInt();
        itemMap.insert("id", id);
        itemMap.insert("name", query.value(1).toString());
        itemMap.insert("approved", query.value(2).toBool());
        itemMap.insert("last_update", query.value(3).toInt());
        itemMap.insert("barcode", query.value(4).toString());
        itemMap.insert("category", query.value(5).toString());
        itemMap.insert("confirm_date", query.value(6).toInt());
        itemMap.insert("contributor", query.value(7).toString());
        itemMap.insert("desc", query.value(8).toString());
        itemMap.insert("ingredient_pic", query.value(9).toString());
        itemMap.insert("pic", query.value(10).toString());
        itemMap.insert("producer", query.value(11).toString());
        itemMap.insert("reason", query.value(12).toString());
        itemMap.insert("status", query.value(13).toString());
        itemMap.insert("thumb", query.value(14).toString());

        allItemMap.insert(QString::number(id), itemMap);
    }

    return allItemMap;
}

QVariantMap DatabaseManager::getCategoryInPage(int page, int limit)
{
    QString queryString = QString("SELECT id, name, approved, last_update FROM category LIMIT %1, %2").arg((page-1)*limit).arg(limit);
    query.exec(queryString);

    QVariantMap allItemMap, itemMap;
    int id;

    while (query.next())
    {
        id = query.value(0).toInt();
        itemMap.insert("id", id);
        itemMap.insert("name", query.value(1).toString());
        itemMap.insert("approved", query.value(2).toBool());
        itemMap.insert("last_update", query.value(3).toInt());

        allItemMap.insert(QString::number(id), itemMap);
    }

    return allItemMap;
}

QVariantMap DatabaseManager::getProducerInPage(int page, int limit)
{
    QString queryString = QString("SELECT id, name, approved, last_update FROM producer LIMIT %1, %2").arg((page-1)*limit).arg(limit);
    query.exec(queryString);

    QVariantMap allItemMap, itemMap;
    int id;

    while (query.next())
    {
        id = query.value(0).toInt();
        itemMap.insert("id", id);
        itemMap.insert("name", query.value(1).toString());
        itemMap.insert("approved", query.value(2).toBool());
        itemMap.insert("last_update", query.value(3).toInt());

        allItemMap.insert(QString::number(id), itemMap);
    }

    return allItemMap;
}

QVariantMap DatabaseManager::getPlaceInPage(int page, int limit)
{
    QString queryString = QString("SELECT id, name, approved, last_update, address, coordinate, desc, email, location, phone, type, website FROM places LIMIT %1, %2").arg((page-1)*limit).arg(limit);
    query.exec(queryString);

    QVariantMap allItemMap, itemMap;
    int id;

    while (query.next())
    {
        id = query.value(0).toInt();
        itemMap.insert("id", id);
        itemMap.insert("name", query.value(1).toString());
        itemMap.insert("approved", query.value(2).toBool());
        itemMap.insert("last_update", query.value(3).toInt());
        itemMap.insert("address", query.value(4).toString());
        itemMap.insert("coordinate", query.value(5).toString());
        itemMap.insert("desc", query.value(6).toString());
        itemMap.insert("email", query.value(7).toString());
        itemMap.insert("location", query.value(8).toString());
        itemMap.insert("phone", query.value(9).toString());
        itemMap.insert("type", query.value(10).toString());
        itemMap.insert("website", query.value(11).toString());

        allItemMap.insert(QString::number(id), itemMap);
    }

    return allItemMap;
}
