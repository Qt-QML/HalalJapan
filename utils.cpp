#include "utils.h"

Utils::Utils(QObject *parent) :
    QObject(parent)
{
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(30000);
    connect(timer, SIGNAL(timeout()), this, SIGNAL(currentTimeChanged()));
    timer->start();
    emit currentTimeChanged();
}

QString Utils::getCurrentTime() const
{
    return QTime::currentTime().toString("h:mm AP");
}

int Utils::getScreenWidth()
{
    return QApplication::primaryScreen()->geometry().width();
}

int Utils::getScreenHeight()
{
    return QApplication::primaryScreen()->geometry().height();
}

void Utils::setView(QtQuick2ApplicationViewer *value)
{
    view = value;
}
