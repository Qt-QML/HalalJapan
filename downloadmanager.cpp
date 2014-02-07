#include "downloadmanager.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QRegExp>
#include <QMap>
#include <QList>
#include <QUrl>
#include <QDir>
#include <QDebug>

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent)
{
    nam = new QNetworkAccessManager;
}

void DownloadManager::setNetworkAccessManager(QNetworkAccessManager *manager) {
    nam = manager;
}

void DownloadManager::setOutputFilename(QString outputFilename)
{
    this->outputFilename = outputFilename;
}

void DownloadManager::setUrl(QString downloadUrl)
{
    this->downloadUrl = downloadUrl;
}

void DownloadManager::performDownload()
{
    QFile outputFile(outputFilename);
    if(!outputFile.exists())
    {
        QUrl url(downloadUrl);
        QNetworkRequest request(url);
//        request.setRawHeader("Host", "halal-japan.fuwafuwa.info");
        request.setRawHeader("User-Agent", "Halal Food App Using Maemo 5");
//        request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:21.0) Gecko/20100101 Firefox/21.0");
//        request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
//        request.setRawHeader("Accept-Language", "en-US,en;q=0.5");

        downloadReply = nam->get(request);
        connect(downloadReply, SIGNAL(finished()), this, SLOT(downloadFinished()));
    }
}

void DownloadManager::downloadFinished()
{
    QUrl redirect = downloadReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirect.isEmpty())
    {
        downloadUrl = redirect.toString();
        performDownload();
    }
    else
    {
        if (downloadReply->error())
        {
            qDebug() << "error dm " << downloadReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        }
        else
        {
            QByteArray response = downloadReply->readAll();

            QFile outputFile(outputFilename);
            if (outputFile.open(QIODevice::WriteOnly))
            {
                outputFile.write(response);
            }
//            else {
//                qDebug() << response << "error";
//            }
            outputFile.close();
        }
    }
}
