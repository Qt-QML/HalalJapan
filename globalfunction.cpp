#include "globalfunction.h"

bool compareNumber(const QString& s1,const QString& s2)
{
    return (s1.toInt()<s2.toInt());
}


QString urlToFilename(QString url)
{
    QString filename = url;
    QString firstPart = QString("^%1*").arg(ILLEGAL_CHARS);
    filename.replace(QRegExp(firstPart), "");
    filename.replace(QRegExp(ILLEGAL_CHARS), "+");

    return filename;
}
