#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>

class SqlPraceRopid
{
public:
    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    void Pripoj();
};

#endif // SQLPRACEROPID_H
