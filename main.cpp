#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QScreen>
#include "qtquick2applicationviewer.h"

#include "settings.h"
#include "utils.h"
#include "halaljapanapi.h"
#include "databasemanager.h"
#include "itemlistmodel.h"
#include "itemdetail.h"
#include "categorylistmodel.h"
#include "categorydetail.h"
#include "paginationlistmodel.h"
#include "placelistmodel.h"
#include "placedetail.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Settings settings;
    settings.restoreSettings();

    DatabaseManager databaseManager("HalalJapan.db");
    databaseManager.openDB();
    databaseManager.createTables();

    Utils utils;
//    qDebug() << app.primaryScreen()->geometry() << utils.getScreenWidth() << utils.getScreenHeight();

    HalalJapanAPI halalJapanAPI;
    halalJapanAPI.setDatabaseManager(&databaseManager);

    if(settings.getFirstRunning()) {
        QObject::connect(&halalJapanAPI, SIGNAL(firstSyncChanged(bool)), &settings, SLOT(setFirstRunning(bool)));
        halalJapanAPI.setBusyMessage("Preparing for first running...");
        halalJapanAPI.firstSync();
    }

    // inisialisai
    halalJapanAPI.setItemTotalPage(databaseManager.findTotalPage("items", settings.getItemPerPage()));
    halalJapanAPI.setCategoryTotalPage(databaseManager.findTotalPage("category", settings.getCategoryPerPage()));
    halalJapanAPI.setProducerTotalPage(databaseManager.findTotalPage("producer", settings.getCategoryPerPage()));
    halalJapanAPI.setPlaceTotalPage(databaseManager.findTotalPage("places", settings.getPlacePerPage()));

    QObject::connect(&app, SIGNAL(aboutToQuit()), &settings, SLOT(saveSettings()));
    QObject::connect(&halalJapanAPI, SIGNAL(lastUpdated(QDateTime)), &settings, SLOT(setLastUdpate(QDateTime)));

    QObject::connect(&settings, SIGNAL(itemPerPageChanged()), &databaseManager, SLOT(findItemTotalPage()));
    QObject::connect(&settings, SIGNAL(producerPerPageChanged()), &databaseManager, SLOT(findProducerTotalPage()));
    QObject::connect(&settings, SIGNAL(placePerPageChanged()), &databaseManager, SLOT(findPlaceTotalPage()));

    QObject::connect(&databaseManager, SIGNAL(itemTotalPageChanged(int)), &halalJapanAPI, SLOT(setItemTotalPage(int)));
    QObject::connect(&databaseManager, SIGNAL(categoryTotalPageChanged(int)), &halalJapanAPI, SLOT(setCategoryTotalPage(int)));
    QObject::connect(&databaseManager, SIGNAL(producerTotalPageChanged(int)), &halalJapanAPI, SLOT(setProducerTotalPage(int)));

    qRegisterMetaType<ItemListModel*>("ItemListModel");
    qmlRegisterType<ItemListModel>("Models",1,0,"ItemListModel");
    qRegisterMetaType<CategoryListModel*>("CategoryListModel");
    qmlRegisterType<CategoryListModel>("Models",1,0,"CategoryListModel");
    qRegisterMetaType<PaginationListModel*>("PaginationListModel");
    qmlRegisterType<PaginationListModel>("Models",1,0,"PaginationListModel");
    qRegisterMetaType<PlaceListModel*>("PlaceListModel");
    qmlRegisterType<PlaceListModel>("Models",1,0,"PlaceListModel");

    qmlRegisterType<ItemDetail>("Models",1,0,"ItemDetail");
    qmlRegisterType<CategoryDetail>("Models",1,0,"CategoryDetail");
    qmlRegisterType<PlaceDetail>("Models",1,0,"PlaceDetail");

    QtQuick2ApplicationViewer viewer;

    QQmlContext* rootContext = viewer.rootContext();
    rootContext->setContextProperty("Settings", &settings);
    rootContext->setContextProperty("Utils", &utils);
    rootContext->setContextProperty("HalalJapanAPI", &halalJapanAPI);

    viewer.setMainQmlFile(QStringLiteral("qml/HalalJapan/main.qml"));
#ifdef Q_OS_ANDROID
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif


    return app.exec();
}
