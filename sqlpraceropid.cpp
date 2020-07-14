#include "sqlpraceropid.h"

SqlPraceRopid::SqlPraceRopid()
{

}


void SqlPraceRopid::Pripoj()
{
    qDebug()<< "SQLprace::Pripoj";
    this->mojeDatabaze = QSqlDatabase::addDatabase("QMYSQL","my_sql_db");
    this->mojeDatabaze.setHostName("127.0.0.1");
    this->mojeDatabaze.setDatabaseName("eichlada");
    this->mojeDatabaze.setUserName("uzivatel");
    this->mojeDatabaze.setPassword("GcVPUZeLg3u7fuV");
    bool ok = this->mojeDatabaze.open();
    vysledek=ok;
}


