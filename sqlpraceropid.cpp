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



void SqlPraceRopid::StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek )
{
    docasnySeznamZastavek.clear();
    qDebug()<< "SQLprace::StahniSeznam";
    qInfo()<<"DebugPointA";
    //QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");

    QString queryString2("SELECT DISTINCT z.n, x.o,z.cis,t.ri,t.ctn,t.btn,t.lcdn FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    queryString2+=("WHERE l.lc=");
    queryString2+=( QString::number(cisloLinky));
    //290664
    queryString2+=(" AND s.c=");
    //6003");
    queryString2+=( QString::number(cisloSpoje));
    queryString2+=(" AND  s.kj LIKE '1%' ");
    //queryString2+=(" AND  s.kj LIKE '1%' ORDER BY x.o");

    //queryString+=("  ASC LIMIT 5");
    QSqlQuery query(queryString2,this->mojeDatabaze);
    int counter=0;
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            SeznamZastavek aktZast;
            int cisloZast = counter+1; //query.value(0).toInt();
            if (cisloZast>=citacMaximum)
            {
                citacMaximum=cisloZast;
            }
            aktZast.StopIndex=cisloZast;
            QString cisloZastString = QString::number(cisloZast);
            qDebug()<<QString::number(counter);
            QString jmenoZastavky = query.value(0).toString();
            aktZast.StopName= jmenoZastavky;
            QString casPrijezdu =  query.value(1).toString();
            aktZast.DepartureTime=casPrijezdu;
            aktZast.cisloCis=query.value(2).toInt();
            aktZast.ids ="PID";//query.value(4).toString();
            aktZast.StopName=query.value(3).toString();
            aktZast.NameFront=query.value(4).toString();
            aktZast.NameSide=query.value(5).toString();
            aktZast.NameLcd=query.value(6).toString();
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<citacMaximum ;
            qDebug()<<aktZast.StopName;
            docasnySeznamZastavek.push_back(aktZast);
        }
    }
    counter=docasnySeznamZastavek.length();
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(counter);
    QString cil=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).StopName;
    qInfo()<<"DebugPointD5";
    for (int i=0; i<counter;i++)
    {
        docasnySeznamZastavek[i].DestinationName=cil;
    }
    qInfo()<<"DebugPointF";
    VypisPole(docasnySeznamZastavek,counter);
    pocetVysledku=counter;
    qInfo()<<"pocetzastavek je"<<QString::number(pocetVysledku);
}


void SqlPraceRopid::VypisPole(QVector<SeznamZastavek> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].StopIndex)+"  "+docasnySeznamZastavek[i].StopName+" cil:  "+docasnySeznamZastavek[i].DestinationName+"\n";
    }
}


void SqlPraceRopid::TestDotaz (QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje, QVector<SeznamZastavek> docasnySeznamZastavek,int pocetZastavek)
{
    qDebug()<< "SQLpraceRopid::TestDotaz";
    int i=0;

    for (i=cisloporadi-1;i<(pocetZastavek-1);i++)
    {

        QString blabla = QString::number(i);
        QString blabla2 = docasnySeznamZastavek.at(i).StopName;
        QString necum =  vytvorCas(docasnySeznamZastavek.at(i).DepartureTime);
        textPoleObsah+=blabla+" "+blabla2+" "+necum+"\n";
        qDebug()<<blabla<<" "<<blabla2<<" "<<necum<<"\n";

    }
    qDebug()<< "SQLpraceRopid::TestDotaz konec";



}

QString SqlPraceRopid::vytvorCas(QString vstup)
{
    int cislo=vstup.toInt();
    int hodiny=cislo/3600;
    int minuty=(cislo%3600)/60;
    int sekundy=(cislo%3600)%60;
    vstup="";
    vstup=QString::number(hodiny)+":"+doplnNulu( minuty,2)+":"+doplnNulu(sekundy,2);
    return vstup;
}

QString SqlPraceRopid::doplnNulu(int cislo,int pocetMist)
{
    QString konverze= QString::number(cislo);
    while (konverze.length()<pocetMist)
    {
        konverze="0"+konverze;
    }

    return konverze;
}




