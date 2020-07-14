#include "sqlpraceropid.h"

SqlPraceRopid::SqlPraceRopid()
{

}


void SqlPraceRopid::Pripoj()
{
    qDebug()<< "SQLprace::Pripoj";
    this->mojeDatabaze = QSqlDatabase::addDatabase("QMYSQL","my_sql_db");
    this->mojeDatabaze.setHostName("127.0.0.1");
    this->mojeDatabaze.setDatabaseName("ropidXMLimport");
    this->mojeDatabaze.setUserName("uzivatel2");
    this->mojeDatabaze.setPassword("iOrXsX4FQZdbcSTf");
    bool ok = this->mojeDatabaze.open();
    if (ok==true)
    {
        qDebug()<<"podarilo se pripojit k databazi ROPID";
    }
    //vysledek=ok;
}


