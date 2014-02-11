#include "settings.h"
#include <QDebug>

Settings* settingsInstance = 0;

Settings::Settings(QObject *parent) :
    QSettings(QString("fpermana"), QString("HalalJapan"), parent)
{
    if (!settingsInstance) {
        settingsInstance = this;
    }
}

Settings* Settings::instance() {
    return settingsInstance;
}

void Settings::restoreSettings()
{
    setActiveColor(value("activeColor", QString("#066bbe")).toString());
    setTheme(value("theme", QString("light")).toString());

    setFirstRunning(value("firstRunning", true).toBool());

    setItemPerPage(value("itemPerPage", 20).toInt());
    setCategoryPerPage(value("categoryPerPage", 20).toInt());
    setProducerPerPage(value("producerPerPage", 20).toInt());
    setPlacePerPage(value("placePerPage", 20).toInt());

    setLastUdpate(value("lastUpdate", QDateTime::fromString("2011-01-01 00:00:00")).toDateTime());

    resourcesPath = value("resourcesPath").toString();
    if(resourcesPath.isEmpty())
    {
#if QT_VERSION >= 0x050000
        // android
        // data/data/org.qtproject.example.HalalFood/files/.HalalFood/
        resourcesPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
#else
        resourcesPath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#endif
        resourcesPath.append(QDir::separator()).append(".HalalFood");
    }

    if(!QDir(resourcesPath).exists())
        QDir().mkpath(resourcesPath);

    imagesPath = value("imagesPath").toString();
    if(imagesPath.isEmpty())
    {
#if QT_VERSION >= 0x050000
        // android
        // data/data/org.qtproject.example.HalalFood/files/.HalalFood/
        imagesPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
#else
        imagesPath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#endif
        imagesPath.append(QDir::separator()).append(".HalalJapan").append(QDir::separator()).append("images");
    }

    if(!QDir(imagesPath).exists())
        QDir().mkpath(imagesPath);
}

QDateTime Settings::getLastUdpate() const
{
    return lastUdpate;
}

void Settings::setLastUdpate(const QDateTime &value)
{
    lastUdpate = value;
    emit lastUpdateChanged();
}

QString Settings::getActiveColor() const
{
    return activeColor;
}

void Settings::setActiveColor(const QString &value)
{
    activeColor = value;
    emit activeColorChanged();
}

void Settings::saveSettings()
{
    setValue("activeColor", activeColor);
    setValue("lastUpdate", lastUdpate);
    setValue("theme", theme);

    setValue("itemPerPage", itemPerPage);
    setValue("categoryPerPage", categoryPerPage);
    setValue("producerPerPage", producerPerPage);
    setValue("placePerPage", placePerPage);

    setValue("resourcesPath", resourcesPath);
    setValue("imagesPath", imagesPath);

    setValue("firstRunning", firstRunning);
}
bool Settings::getFirstRunning() const
{
    return firstRunning;
}

void Settings::resetAllSettings()
{
    setTheme(QString("light"));

    setFirstRunning(true);
    setItemPerPage(20);
    setCategoryPerPage(20);
    setProducerPerPage(20);
    setPlacePerPage(20);

    setLastUdpate(QDateTime::fromString("2011-01-01 00:00:00"));

    saveSettings();
}

void Settings::setFirstRunning(bool value)
{
    firstRunning = value;
}


int Settings::getPlacePerPage() const
{
    return placePerPage;
}

void Settings::setPlacePerPage(int value)
{
    placePerPage = value;
    emit placePerPageChanged();
}

int Settings::getProducerPerPage() const
{
    return producerPerPage;
}

void Settings::setProducerPerPage(int value)
{
    producerPerPage = value;
    emit producerPerPageChanged();
}

int Settings::getCategoryPerPage() const
{
    return categoryPerPage;
}

void Settings::setCategoryPerPage(int value)
{
    categoryPerPage = value;
    emit categoryPerPageChanged();
}

int Settings::getItemPerPage() const
{
    return itemPerPage;
}

void Settings::setItemPerPage(int value)
{
    itemPerPage = value;
    emit itemPerPageChanged();
}


QString Settings::getImagesPath() const
{
    return imagesPath;
}

void Settings::setImagesPath(const QString &value)
{
    imagesPath = value;
}


QString Settings::getResourcesPath() const
{
    return resourcesPath;
}

void Settings::setResourcesPath(const QString &value)
{
    resourcesPath = value;
}

QString Settings::getTheme() const
{
    return theme;
}

void Settings::setTheme(const QString &value)
{
    theme = value;

    if (value == "light") {
        setGradientColor(QString("#edece8"));
        setGradientColorHigh("white");
    }
    else {
        setGradientColor(QString("black"));
        setGradientColorHigh("#524e4e");
    }
    emit themeChanged();
}

QString Settings::getGradientColorHigh() const
{
    return gradientColorHigh;
}

void Settings::setGradientColorHigh(const QString &value)
{
    gradientColorHigh = value;
    emit gradientColorHighChanged();
}

QString Settings::getGradientColor() const
{
    return gradientColor;
}

void Settings::setGradientColor(const QString &value)
{
    gradientColor = value;
    emit gradientColorChanged();
}

QString Settings::getActiveColorString() const
{
    return activeColorString;
}

void Settings::setActiveColorString(const QString &value)
{
    activeColorString = value;
    emit activeColorStringChanged();
}
