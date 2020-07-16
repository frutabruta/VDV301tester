#include "sqlpraceropid.h"
#include "VDV301_Display/seznamzastavek.h"

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



void SqlPraceRopid::StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek )
{
    qDebug()<< "SQLprace::StahniSeznam";
    qInfo()<<"DebugPointA";
    //QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");

    QString queryString2("SELECT z.n, x.o,z.cis FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("WHERE l.lc=");
    queryString2+=( QString::number(cisloLinky));
    //290664
    queryString2+=(" AND s.c=");
    //6003");
    queryString2+=( QString::number(cisloSpoje));
    queryString2+=(" WHERE  s.kj LIKE '1%' ORDER BY x.o");

    /*
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
    */


    /* queryString+=( " AND a.stop_order>=");
      queryString+=( QString::number(cisloporadi));  */
    //queryString+=("  ORDER BY a.stop_order");


    //queryString+=("  ASC LIMIT 5");
    QSqlQuery query(queryString2,this->mojeDatabaze);
    int counter=0;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {

            int cisloZast = counter+1; //query.value(0).toInt();
            if (cisloZast>=citacMaximum)
            {
                citacMaximum=cisloZast;
            }
            docasnySeznamZastavek[cisloZast].StopIndex=cisloZast;
            QString cisloZastString = QString::number(cisloZast);
            qDebug()<<QString::number(counter);
            QString jmenoZastavky = query.value(0).toString();
            docasnySeznamZastavek[cisloZast].StopName= jmenoZastavky;
            QString casPrijezdu = query.value(1).toString();
            docasnySeznamZastavek[cisloZast].cisloCis=query.value(2).toInt();
            docasnySeznamZastavek[cisloZast].ids ="PID";//query.value(4).toString();
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


void SqlPraceRopid::VypisPole(SeznamZastavek *docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=1;i<=pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].StopIndex)+"  "+docasnySeznamZastavek[i].StopName+" cil:  "+docasnySeznamZastavek[i].DestinationName+"\n";
    }
}


