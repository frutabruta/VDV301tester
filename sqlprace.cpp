#include "sqlprace.h"
#include <QCoreApplication>
#include <QtSql>
#include "VDV301_Display/seznamzastavek.h"


SQLprace::SQLprace()
{
    qDebug()<< "SQLprace::SQLprace";
    vysledek=0;
}

void SQLprace::Pripoj()
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

void SQLprace::TestDotaz (QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje)
{
    qDebug()<< "SQLprace::TestDotaz";
    QString queryString("SELECT a.stop_order, b.name, a.time  FROM lineroutestoptime a");
    queryString+=(" LEFT JOIN  stop b ON b.id = a.stop_id ");
    queryString+=("LEFT JOIN lineroute c ON a.lineroute_id=c.id ");
    queryString+=("LEFT JOIN line d ON c.line_ID = d.ID ");
    queryString+=("WHERE d.licencenumber=");
    queryString+=( QString::number(cislolinky));
    queryString+=( " AND c.route_id =");
    queryString+=( QString::number(cislospoje));
    queryString+=( " AND a.stop_order>=");
    queryString+=( QString::number(cisloporadi));
    queryString+=("  ORDER BY a.stop_order ASC LIMIT 5");
    QSqlQuery query(queryString,this->mojeDatabaze);
    while (query.next())
    {
        QString blabla = query.value(0).toString();
        QString blabla2 = query.value(1).toString();
        QString necum = query.value(2).toString();
        textPoleObsah+=blabla+" "+blabla2+" "+necum+"\n";
    }


}

void SQLprace::StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek )
{
    qDebug()<< "SQLprace::StahniSeznam";
    qInfo()<<"DebugPointA";
    QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");
    queryString+=(" LEFT JOIN  stop b ON b.id = a.stop_id ");
    queryString+=(" LEFT JOIN lineroute c ON a.lineroute_id=c.id ");
    queryString+=(" LEFT JOIN line d ON c.line_ID = d.ID ");
    queryString+=(" LEFT JOIN stopids e ON b.id = e.stop_id ");
    queryString+=(" LEFT JOIN ids f ON e.ids_id=f.id ");
    queryString+=(" WHERE d.licencenumber=");
    queryString+=( QString::number(cisloLinky));
    queryString+=( " AND c.route_id =");
    queryString+=( QString::number(cisloSpoje));
    /* queryString+=( " AND a.stop_order>=");
      queryString+=( QString::number(cisloporadi));  */
    queryString+=("  ORDER BY a.stop_order");
    //queryString+=("  ASC LIMIT 5");
    QSqlQuery query(queryString,this->mojeDatabaze);
    int counter=0;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        if (query.value(1).toString()!="")
        {

            int cisloZast = query.value(0).toInt();
            if (cisloZast>=citacMaximum)
            {
                citacMaximum=cisloZast;
            }
            docasnySeznamZastavek[cisloZast].StopIndex=cisloZast;
            QString cisloZastString = QString::number(cisloZast);
            qDebug()<<query.value(0).toString();
            QString jmenoZastavky = query.value(1).toString();
            docasnySeznamZastavek[cisloZast].StopName= jmenoZastavky;
            QString casPrijezdu = query.value(2).toString();
            docasnySeznamZastavek[cisloZast].cisloCis=query.value(3).toInt();
            docasnySeznamZastavek[cisloZast].ids =query.value(4).toString();
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<citacMaximum ;
        }
    }
    counter=citacMaximum;
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(counter);
    QString cil=docasnySeznamZastavek[counter].StopName;

    for (int i=1; i<=counter;i++)
    {
        docasnySeznamZastavek[i].DestinationName=cil;
    }
    qInfo()<<"DebugPointF";
    VypisPole(docasnySeznamZastavek,counter);
    pocetVysledku=counter;
    qInfo()<<"pocetzastavek je"<<QString::number(pocetVysledku);
}




void SQLprace::zjistiPocet (int &pocetvysledku, int cisloporadi, int cislolinky, int cislospoje)
{
    qDebug()<< "SQLprace::zjistiPocet";
    QString queryString("SELECT count(a.ID) FROM lineroutestoptime a");
    queryString+=("         LEFT JOIN  stop b ON b.id = a.stop_id ");
    queryString+=("LEFT JOIN lineroute c ON a.lineroute_id=c.id ");
    queryString+=("LEFT JOIN line d ON c.line_ID = d.ID ");
    queryString+=("WHERE d.licencenumber="+ QString::number(cislolinky)+" AND c.route_id ="+ QString::number(cislospoje) +" AND a.stop_order>="+ QString::number(cisloporadi));
    queryString+=("  ORDER BY a.stop_order ");
    QSqlQuery query(queryString,this->mojeDatabaze);
    int i=0;
    while (query.next())
    {
        pocetvysledku = query.value(0).toInt();
        qInfo()<<"vysledekSQLdotazu cislo  "<<QString::number(i);
        i++;
    }



}

void SQLprace::VypisPole(SeznamZastavek *docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=1;i<=pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].StopIndex)+"  "+docasnySeznamZastavek[i].StopName+" cil:  "+docasnySeznamZastavek[i].DestinationName+"\n";
    }
}

