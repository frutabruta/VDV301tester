#include "sqlpraceropid.h"
#include "VDV301_Display/seznamzastavek.h"

SqlPraceRopid::SqlPraceRopid()
{

}


int SqlPraceRopid::Pripoj(QString adresa)
{
    qDebug()<< "SQLprace::Pripoj";
    this->mojeDatabaze = QSqlDatabase::addDatabase("QMYSQL","my_sql_db");
    this->mojeDatabaze.setHostName(adresa);
    //this->mojeDatabaze.setPort(3306);
    //this->mojeDatabaze.setHostName("127.0.0.1");
    this->mojeDatabaze.setDatabaseName("ropidXMLimport");
    this->mojeDatabaze.setUserName("uzivatel2");
    this->mojeDatabaze.setPassword("iOrXsX4FQZdbcSTf");
    bool ok = this->mojeDatabaze.open();
    if (ok==true)
    {
        qDebug()<<"podarilo se pripojit k databazi ROPID";
        return 1;
    }
    else
    {
        qDebug()<<"nepovedlo se";
        return 0;
    }
    //vysledek=ok;
}



int SqlPraceRopid::StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek, bool platnost )
{
    docasnySeznamZastavek.clear();
    qDebug()<< "SQLprace::StahniSeznam";
    qInfo()<<"DebugPointA";
    //QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");

    QString queryString2("SELECT DISTINCT z.n, x.o,z.cis,t.ri,t.ctn,t.btn,t.lcdn,l.c,x.na,t.vtn,z.ois,x.xA,x.xB,x.xC,x.xVla FROM x ");
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
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
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
            //aktZast.StopName=query.value(3).toString();
            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();

            aktZast.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
            aktZast.NameSide=query.value(query.record().indexOf("t.btn")).toString();
            aktZast.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();
            aktZast.LineName=query.value(query.record().indexOf("l.c")).toString();
            aktZast.nacestna=query.value(query.record().indexOf("t.btn")).toInt();
            aktZast.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
            aktZast.prestupMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.prestupMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();

            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<citacMaximum ;
            qDebug()<<aktZast.StopName;
            docasnySeznamZastavek.push_back(aktZast);
        }
    }
    counter=docasnySeznamZastavek.length();
    if (counter ==0)
    {
        return 0;
    }
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
    return 1;
}


void SqlPraceRopid::VypisPole(QVector<SeznamZastavek> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].StopIndex)+"  "+docasnySeznamZastavek[i].StopName+" cil:  "+docasnySeznamZastavek[i].DestinationName+"\n";
    }
}


void SqlPraceRopid::vytvorHlavniText (QString &textPoleObsah,QString &textPoleCasu, int cisloporadi, QVector<SeznamZastavek> docasnySeznamZastavek,int pocetZastavek)
{
    qDebug()<< "SQLpraceRopid::TestDotaz";
    int i=0;

    for (i=cisloporadi-1;i<(pocetZastavek-1);i++)
    {

        QString blabla = QString::number(i);
        QString blabla2 = docasnySeznamZastavek.at(i).StopName;
        QString necum =  vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).DepartureTime);
        textPoleObsah+=blabla+" "+blabla2+"\n";
        qDebug()<<blabla<<" "<<blabla2<<" "<<necum<<"\n";
        textPoleCasu+=necum+"\n";

    }
    qDebug()<< "SQLpraceRopid::TestDotaz konec";



}


int SqlPraceRopid::VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek)
{
    docasnySeznamLinek.clear();
    qDebug()<< "SqlPraceRopid::VytvorSeznamLinek";
    qInfo()<<"DebugPointA";
    //QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");

    QString queryString2("SELECT DISTINCT l.c,l.lc,l.n FROM l ");
    queryString2+=("ORDER BY l.c");

    //queryString2+=(" WHERE l.kj LIKE '1%' ");
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

            Linka docasnaLinka;
            docasnaLinka.c=query.value(0).toInt();
            docasnaLinka.lc=query.value(1).toInt();
            docasnaLinka.n=query.value(2).toString();

            docasnySeznamLinek.push_back(docasnaLinka);
            citacMaximum++;

        }
    }

    if (citacMaximum==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int SqlPraceRopid::VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, int cisloLinky)
{
    qDebug()<< "SqlPraceRopid::VytvorSeznamSpoju";
    docasnySeznamSpoju.clear();

    qInfo()<<"DebugPointA";
    //QString queryString("SELECT a.stop_order, b.name, a.time, b.cis_id,f.mpvalias FROM lineroutestoptime a ");

    QString queryString2("SELECT DISTINCT s.s, s.c FROM s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("WHERE l.lc=");
    queryString2+=( QString::number(cisloLinky));
    queryString2+=(" ORDER BY s.c");



    //queryString2+=(" AND  s.kj LIKE '1%' ORDER BY x.o");

    //queryString+=("  ASC LIMIT 5");
    QSqlQuery query(queryString2,this->mojeDatabaze);

    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {

            Spoj docasnySpoj;
            docasnySpoj.cislo=query.value(0).toInt();
            docasnySpoj.cisloRopid=query.value(1).toInt();



            docasnySeznamSpoju.push_back(docasnySpoj);
            citacMaximum++;
            qDebug()<<docasnySpoj.cisloRopid;

        }
    }

    if (citacMaximum==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

QString SqlPraceRopid::vytvorCasHodinyMinuty(QString vstup)
{
    qDebug()<<"SqlPraceRopid::vytvorCas";
    int cislo=vstup.toInt();
    int hodiny=cislo/3600;
    int minuty=(cislo%3600)/60;
    vstup="";
    vstup=QString::number(hodiny)+":"+doplnNulu( minuty,2);

    return vstup;
}

QString SqlPraceRopid::vytvorCasHodinyMinutySekundy(QString vstup)
{
    qDebug()<<"SqlPraceRopid::vytvorCas";
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
    qDebug()<<"SqlPraceRopid::doplnNulu";
    QString konverze= QString::number(cislo);
    while (konverze.length()<pocetMist)
    {
        konverze="0"+konverze;
    }

    return konverze;
}




