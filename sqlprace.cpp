#include "sqlprace.h"
#include <QCoreApplication>
#include <QtSql>



SQLprace::SQLprace()
{
   vysledek=0;
}

void SQLprace::Pripoj()
{


    this->mojeDatabaze = QSqlDatabase::addDatabase("QMYSQL","my_sql_db");
    //db.setHostName("sql.endora.cz");
    this->mojeDatabaze.setHostName("127.0.0.1");
    this->mojeDatabaze.setDatabaseName("eichlada");
    this->mojeDatabaze.setUserName("jaadmin");
    //db.setPort(3310);
    this->mojeDatabaze.setPassword("abcXYZ123");
    bool ok = this->mojeDatabaze.open();
    vysledek=ok;
    //return db;
}

void SQLprace::TestDotaz (QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje)
{





       // QString queryString("SELECT *  FROM novatabulka");
         QString queryString("SELECT a.stop_order, b.name, a.time  FROM lineroutestoptime a");
         queryString+=(" LEFT JOIN  stop b ON b.id = a.stop_id ");
         queryString+=("LEFT JOIN lineroute c ON a.lineroute_id=c.id ");
         queryString+=("LEFT JOIN line d ON c.line_ID = d.ID ");
         queryString+=("WHERE d.licencenumber=");
         queryString+=( QString::number(cislolinky));
         //queryString+=( QString::number(820741));
         queryString+=( " AND c.route_id =");
         queryString+=( QString::number(cislospoje));
         queryString+=( " AND a.stop_order>=");
         queryString+=( QString::number(cisloporadi));
         queryString+=("  ORDER BY a.stop_order ASC LIMIT 5");
         QSqlQuery query(queryString,this->mojeDatabaze);


        while (query.next()) {
                QString blabla = query.value(0).toString();
                QString blabla2 = query.value(1).toString();
                QString necum = query.value(2).toString();
                textPoleObsah+=blabla+" "+blabla2+" "+necum+"\n";

                //int salary = query.value(1).toInt();
                //qDebug() << name << salary;
            }
        //textPoleObsah="ahoj";


}


void SQLprace::zjistiPocet (int &pocetvysledku, int cisloporadi, int cislolinky, int cislospoje)
{





       // QString queryString("SELECT *  FROM novatabulka");
    QString queryString("SELECT count(a.ID) FROM lineroutestoptime a");
    queryString+=(" LEFT JOIN  stop b ON b.id = a.stop_id ");
    queryString+=("LEFT JOIN lineroute c ON a.lineroute_id=c.id ");
    queryString+=("LEFT JOIN line d ON c.line_ID = d.ID ");
    queryString+=("WHERE d.licencenumber="+ QString::number(cislolinky)+" AND c.route_id ="+ QString::number(cislospoje) +" AND a.stop_order>="+ QString::number(cisloporadi));
    queryString+=("  ORDER BY a.stop_order ");
        QSqlQuery query(queryString,this->mojeDatabaze);


        while (query.next()) {


                pocetvysledku = query.value(0).toInt();
                //qDebug() << name << salary;
            }
        //textPoleObsah="ahoj";


}

