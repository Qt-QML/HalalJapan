#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#if QT_VERSION >= 0x050000
    #include <QStandardPaths>
#else
    #include <QDesktopServices>
#endif
#include <QDir>
#include <QDateTime>

class Settings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(QString theme
               READ getTheme
               WRITE setTheme
               NOTIFY themeChanged
               )

    Q_PROPERTY(int itemPerPage
               READ getItemPerPage
               WRITE setItemPerPage
               NOTIFY itemPerPageChanged
               )
    Q_PROPERTY(int categoryPerPage
               READ getCategoryPerPage
               WRITE setCategoryPerPage
               NOTIFY categoryPerPageChanged
               )
    Q_PROPERTY(int producerPerPage
               READ getProducerPerPage
               WRITE setProducerPerPage
               NOTIFY producerPerPageChanged
               )
    Q_PROPERTY(int placePerPage
               READ getPlacePerPage
               WRITE setPlacePerPage
               NOTIFY placePerPageChanged
               )
    Q_PROPERTY(QString activeColor
               READ getActiveColor
               WRITE setActiveColor
               NOTIFY activeColorChanged
               )
    Q_PROPERTY(QString activeColorString
               READ getActiveColorString
               WRITE setActiveColorString
               NOTIFY activeColorStringChanged)
    Q_PROPERTY(QString gradientColor
               READ getGradientColor
               WRITE setGradientColor
               NOTIFY gradientColorChanged)
    Q_PROPERTY(QString gradientColorHigh
               READ getGradientColorHigh
               WRITE setGradientColorHigh
               NOTIFY gradientColorHighChanged)

    Q_PROPERTY(QDateTime lastUdpate
               READ getLastUdpate
               WRITE setLastUdpate
               NOTIFY lastUpdateChanged
               )
public:
    explicit Settings(QObject *parent = 0);

    static Settings* instance();

    void restoreSettings();
    
    QDateTime getLastUdpate() const;
    QString getActiveColor() const;

    QString getTheme() const;
    void setTheme(const QString &value);

    QString getActiveColorString() const;
    void setActiveColorString(const QString &value);

    QString getGradientColor() const;
    void setGradientColor(const QString &value);

    QString getGradientColorHigh() const;
    void setGradientColorHigh(const QString &value);

    QString getResourcesPath() const;
    void setResourcesPath(const QString &value);

    QString getImagesPath() const;
    void setImagesPath(const QString &value);

    int getItemPerPage() const;
    void setItemPerPage(int value);

    int getCategoryPerPage() const;
    void setCategoryPerPage(int value);

    int getProducerPerPage() const;
    void setProducerPerPage(int value);

    int getPlacePerPage() const;
    void setPlacePerPage(int value);

    bool getFirstRunning() const;

    Q_INVOKABLE void resetAllSettings();

signals:
    void lastUpdateChanged();

    void itemPerPageChanged();
    void categoryPerPageChanged();
    void producerPerPageChanged();
    void placePerPageChanged();

    void themeChanged();
    void activeColorChanged();
    void activeColorStringChanged();
    void gradientColorChanged();
    void gradientColorHighChanged();
    
public slots:
    void setLastUdpate(const QDateTime &value);
    void setActiveColor(const QString &value);
    void setFirstRunning(bool value);

    void saveSettings();

private:
    QDateTime lastUdpate;

    int itemPerPage, categoryPerPage, producerPerPage, placePerPage;

    QString theme;
    QString activeColor;
    QString activeColorString;
    QString gradientColor;
    QString gradientColorHigh;

    QString resourcesPath;
    QString imagesPath;

    bool firstRunning;
    
};

#endif // SETTINGS_H
