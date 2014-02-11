# Add more folders to ship with the application, here
folder_01.source = qml/HalalJapan
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += core network sql widgets

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    categorydetail.cpp \
    categorylistmodel.cpp \
    databasemanager.cpp \
    downloadmanager.cpp \
    globalfunction.cpp \
    utils.cpp \
    itemdetail.cpp \
    itemlistmodel.cpp \
    json.cpp \
    paginationlistmodel.cpp \
    placedetail.cpp \
    placelistmodel.cpp \
    settings.cpp \
    halaljapanapi.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    HalalJapan64.png \
    HalalJapan80.png \
    HalalJapan.pro.user \
    android/AndroidManifest.xml

HEADERS += \
    categorydetail.h \
    categorylistmodel.h \
    databasemanager.h \
    downloadmanager.h \
    settings.h \
    utils.h \
    globalfunction.h \
    itemdetail.h \
    itemlistmodel.h \
    json.h \
    paginationlistmodel.h \
    placedetail.h \
    placelistmodel.h \
    halaljapanapi.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
