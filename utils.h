#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QProcess>
#include <QVariantList>
#include <QTimer>
#include <QTime>
#include <QApplication>
#include <QScreen>
#include <QDebug>

#include "qtquick2applicationviewer.h"



class Utils : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentTime
               READ getCurrentTime
               NOTIFY currentTimeChanged)
    Q_PROPERTY(int screenWidth
               READ getScreenWidth
               CONSTANT)
    Q_PROPERTY(int screenHeight
               READ getScreenHeight
               CONSTANT)
public:
    explicit Utils(QObject *parent = 0);

    QString getCurrentTime() const;
    int getScreenWidth();
    int getScreenHeight();
    
    void setView(QtQuick2ApplicationViewer *value);

public slots:

signals:
    void alert(const QString &message);
    void currentTimeChanged();

private:

    QtQuick2ApplicationViewer* view;
};

#endif // UTILS_H
