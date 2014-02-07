#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QPixmap>
#include <QList>
#include <QTime>
#include <QVariantMap>
#include <QProcess>
#include "settings.h"

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class DownloadManager : public QObject {
    Q_OBJECT

public:
    explicit DownloadManager(QObject *parent = 0);

    void setNetworkAccessManager(QNetworkAccessManager *manager);
    void setOutputFilename(QString outputFilename);
    void setUrl(QString downloadUrl);
    void performDownload();

signals:

public slots:
    void downloadFinished();

private:
    QNetworkAccessManager *nam;
    QString outputFilename;
    QString downloadUrl;
    QNetworkReply *downloadReply;

};

#endif // DOWNLOADMANAGER_H
