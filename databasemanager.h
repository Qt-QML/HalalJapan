#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QDir>
#include <QtSql/QtSql>
#include <QFile>
#include <QDateTime>
#include "settings.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    explicit DatabaseManager(QString filename, QObject *parent = 0);

    bool openDB();
    bool deleteDB();

    int findTotalPage(QString tableName, int limit);

    bool insertCategory(QVariantMap categoryMap);
    bool insertItem(QVariantMap itemMap);
    bool insertProducer(QVariantMap producerMap);
    bool insertPlace(QVariantMap placeMap);
//    bool insertData(QString dataTable, QVariantMap dataMap);
//    bool insertData(QString tableName, QVariantMap dataMap, bool isUpdate = false);

    bool executeQueryString(QString queryString);

    QSqlError lastError();

    bool createTables();
    
    QString getFilename() const;
    void setFilename(const QString &value);

    QVariantMap getAllDataMap() const;
    void setAllDataMap(const QVariantMap &value);

    bool getIsUpdate() const;
    void setIsUpdate(bool value);

    QVariantMap getItemByQuery(QString queryString, QStringList fields);
    QVariantMap getItemInPage(int page, int limit);
    QVariantMap getCategoryInPage(int page, int limit);
    QVariantMap getProducerInPage(int page, int limit);
    QVariantMap getPlaceInPage(int page, int limit);

    void prepareInsertData(QString tableName, QVariantMap dataMap, bool update = false);
    QSqlQuery getQuery() const;
    void setQuery(const QSqlQuery &value);

signals:
    void finished();

    void itemInserted();
    void itemTotalPageChanged(int);
    void categoryInserted();
    void categoryTotalPageChanged(int);
    void producerInserted();
    void producerTotalPageChanged(int);
    void placeInserted();
    void placeTotalPageChanged(int);
    
public slots:
    void firstSynchronizedStarted();
    void clearQuery();
    void findItemTotalPage();
    void findCategoryTotalPage();
    void findProducerTotalPage();
    void findPlaceTotalPage();
    bool executeQuery();

private:
    QSqlDatabase db;
    QSqlQuery query;
    QString filename;

    bool isUpdate;

    QVariantMap allDataMap;
};

#endif // DATABASEMANAGER_H
