#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#define ILLEGAL_CHARS "[\"@&~=\\/:?#!|<>*^]"
#include <QString>
#include <QRegExp>
bool compareNumber(const QString& s1,const QString& s2);
QString urlToFilename(QString url);
#endif // GLOBALFUNCTION_H
