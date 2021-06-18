#include "sqlpraceropid.h"
#include "VDV301struktury/zastavka.h"
#include "xmlgenerator.h"
#include "VDV301struktury/zastavkacil.h"

SqlPraceRopid::SqlPraceRopid()
{

}

//test Pridani Komentare prechodu na SQLITE
int SqlPraceRopid::Pripoj(QString adresa)

{
    qDebug()<< "SQLprace::Pripoj";
    this->mojeDatabaze = QSqlDatabase::addDatabase("QSQLITE");
    //this->mojeDatabaze.setHostName(adresa);
    //this->mojeDatabaze.setPort(3306);
    //this->mojeDatabaze.setHostName("127.0.0.1");
    QString nazevSouboru="data.sqlite";
    QString cesta=QCoreApplication::applicationDirPath()+"/"+nazevSouboru;
    qDebug()<<"cesta:"<<cesta;
    this->mojeDatabaze.setDatabaseName(cesta);
    // this->mojeDatabaze.setUserName("uzivatel2");
    //this->mojeDatabaze.setPassword("iOrXsX4FQZdbcSTf");
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

}




int SqlPraceRopid::StahniSeznam(int cisloLinky, int cisloSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost )
{
    docasnySeznamZastavek.clear();
    qDebug()<< "SQLprace::StahniSeznam";
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT z.n, z.tp, x.o,z.cis,t.ri,t.ctn,t.btn,t.lcdn,l.c,l.lc,t.vtn,z.ois,x.na,x.zn,x.xA,x.xB,x.xC,x.xD,x.xVla,x.xLet,x.xLod, x.xorder, t.hl,s.ns FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    queryString2+=("WHERE l.lc=");
    queryString2+=( QString::number(cisloLinky));
    //290664
    queryString2+=(" AND s.c=");
    queryString2+=( QString::number(cisloSpoje));
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
    queryString2+=("ORDER BY x.xorder");



    /*
   Mozna nahrada!

dbManager->query.prepare("INSERT INTO users (username, pass, userGroup) VALUES (:name, :pass, :group)");

dbManager->query.bindValue(":name", username);
dbManager->query.bindValue(":pass", password);
dbManager->query.bindValue(":group", 0);
dbManager->query.exec();

      */
    QSqlQuery query(queryString2,this->mojeDatabaze);
    int counter=0;
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    Zastavka cilovaZastavka;
    int navazujiciSpoj=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            int cisloZast = counter; //query.value(0).toInt();
            if (cisloZast>=citacMaximum)
            {
                citacMaximum=cisloZast;
            }
            aktZast.StopIndex=cisloZast;
            QString cisloZastString = QString::number(cisloZast);
            qDebug()<<QString::number(counter);
            //QString jmenoZastavky = query.value(0).toString();
            QString jmenoZastavky =query.value( query.record().indexOf("z.n")).toString();

            aktZast.StopName= jmenoZastavky;
            //QString casPrijezdu =  query.value(1).toString();
            QString casPrijezdu =query.value( query.record().indexOf("x.o")).toString();
            aktZast.DepartureTime=casPrijezdu;
            //aktZast.cisloCis=query.value(2).toInt();
            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.ids ="PID";//query.value(4).toString();
            //aktZast.StopName=query.value(3).toString();
            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();

            aktZast.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
            aktZast.NameSide=query.value(query.record().indexOf("t.btn")).toString();
            aktZast.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();

            aktLinka.LineName=query.value(query.record().indexOf("l.c")).toString();
            aktLinka.LineNumber=query.value(query.record().indexOf("l.lc")).toString();
            aktZast.nacestna=query.value(query.record().indexOf("x.na")).toInt();
            aktZast.naZnameni =query.value(query.record().indexOf("x.zn")).toBool();
            aktZast.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
            aktZast.prestupMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.prestupMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xD")).toBool();
            aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();
            aktZast.prestupLetadlo =query.value(query.record().indexOf("x.xLet")).toBool();
            aktZast.prestupPrivoz =query.value(query.record().indexOf("x.xLod")).toBool();
            aktZast.additionalTextMessage =query.value(query.record().indexOf("t.hl")).toString();

            navazujiciSpoj=query.value(query.record().indexOf("s.ns")).toInt();



            xmlGenerator xmlgen;
            aktZast.seznamPasem=xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp")).toString(),"PID");
            qDebug()<<"pasmo"<<query.value(query.record().indexOf("z.tp")).toString();
            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<citacMaximum ;
            qDebug()<<aktZast.StopName;
            aktZastCil.linka=aktLinka;
            aktZastCil.zastavka=aktZast;
            docasnySeznamZastavek.push_back(aktZastCil);
        }
    }
    counter=docasnySeznamZastavek.length();
    if (counter ==0)
    {
        return 0;
    }
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(counter);
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).zastavka;

    qInfo()<<"DebugPointD5";
    for (int i=0; i<counter;i++)
    {
        //docasnySeznamZastavek[i].DestinationName=cilovaZastavka.StopName ;
        //docasnySeznamZastavek[i].zastavka.DestinationCis=cilovaZastavka.cisloCis;
        docasnySeznamZastavek[i].cil=cilovaZastavka;
    }
    qInfo()<<"DebugPointF";
    // VypisPole(docasnySeznamZastavek,counter);
    qInfo()<<"pocetzastavek je"<<QString::number(docasnySeznamZastavek.length());

    if (navazujiciSpoj!=0)
    {
        qDebug()<<"navazujici spoj ma cislo "<<QString::number(navazujiciSpoj);
        StahniSeznamNavazSpoj(navazujiciSpoj,docasnySeznamZastavek,platnost);
    }
    else
    {
        qDebug()<<"navazujici spoj neni";
    }



    return 1;
}




int SqlPraceRopid::StahniSeznamNavazSpoj(int idSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost )
{
    //docasnySeznamZastavek.clear();
    int pocetPuvodnichZastavek=docasnySeznamZastavek.count();
    Linka posledniLinka;
    qDebug()<< "SQLprace::StahniSeznamNavazSpoj";
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT z.n, z.tp, x.o,z.cis,t.ri,t.ctn,t.btn,t.lcdn,l.c,l.lc,t.vtn,z.ois,x.na,x.zn,x.xA,x.xB,x.xC,x.xD,x.xVla,x.xLet,x.xLod, x.xorder, t.hl FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    // queryString2+=("WHERE l.lc=");
    //  queryString2+=( QString::number(cisloLinky));
    //290664
    queryString2+=("WHERE s.s=");
    queryString2+=( QString::number(idSpoje));
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
    queryString2+=("ORDER BY x.xorder");

    QSqlQuery query(queryString2,this->mojeDatabaze);
    int counter=0;
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    Zastavka cilovaZastavka;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            int cisloZast = counter; //query.value(0).toInt();
            if (cisloZast>=citacMaximum)
            {
                citacMaximum=cisloZast;
            }
            aktZast.StopIndex=cisloZast;
            QString cisloZastString = QString::number(cisloZast);
            qDebug()<<QString::number(counter);
            //QString jmenoZastavky = query.value(0).toString();
            QString jmenoZastavky =query.value( query.record().indexOf("z.n")).toString();

            aktZast.StopName= jmenoZastavky;
            //QString casPrijezdu =  query.value(1).toString();
            QString casPrijezdu =query.value( query.record().indexOf("x.o")).toString();
            aktZast.DepartureTime=casPrijezdu;
            //aktZast.cisloCis=query.value(2).toInt();
            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.ids ="PID";//query.value(4).toString();
            //aktZast.StopName=query.value(3).toString();
            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();

            aktZast.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
            aktZast.NameSide=query.value(query.record().indexOf("t.btn")).toString();
            aktZast.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();

            aktLinka.LineName=query.value(query.record().indexOf("l.c")).toString();
            aktLinka.LineNumber=query.value(query.record().indexOf("l.lc")).toString();
            aktZast.nacestna=query.value(query.record().indexOf("x.na")).toInt();
            aktZast.naZnameni =query.value(query.record().indexOf("x.zn")).toBool();
            aktZast.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
            aktZast.prestupMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.prestupMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xD")).toBool();
            aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();
            aktZast.prestupLetadlo =query.value(query.record().indexOf("x.xLet")).toBool();
            aktZast.prestupPrivoz =query.value(query.record().indexOf("x.xLod")).toBool();
            aktZast.additionalTextMessage =query.value(query.record().indexOf("t.hl")).toString();
            xmlGenerator xmlgen;
            aktZast.seznamPasem=xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp")).toString(),"PID");
            qDebug()<<"pasmo"<<query.value(query.record().indexOf("z.tp")).toString();
            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<citacMaximum ;
            qDebug()<<aktZast.StopName;

            aktZastCil.linka=aktLinka;
            aktZastCil.zastavka=aktZast;
            docasnySeznamZastavek.push_back(aktZastCil);
            posledniLinka=aktLinka;
        }
    }
    counter=docasnySeznamZastavek.length();
    if (counter ==0)
    {
        return 0;
    }
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(counter);
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).zastavka;

    qInfo()<<"DebugPointD5";
    for (int i=pocetPuvodnichZastavek; i<counter;i++)
    {
        //docasnySeznamZastavek[i].DestinationName=cilovaZastavka.StopName ;
        //docasnySeznamZastavek[i].zastavka.DestinationCis=cilovaZastavka.cisloCis;
        docasnySeznamZastavek[i].cil=cilovaZastavka;
        docasnySeznamZastavek[i].linka=posledniLinka;
    }
    qInfo()<<"DebugPointF_navaznySpoj";
    VypisPole(docasnySeznamZastavek,counter);
    qInfo()<<"pocetzastavek je"<<QString::number(docasnySeznamZastavek.length());
    return 1;
}


void SqlPraceRopid::VypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].zastavka.StopIndex)+"  "+docasnySeznamZastavek[i].zastavka.StopName+" cil:  "+docasnySeznamZastavek[i].cil.StopName+" linka"+docasnySeznamZastavek[i].linka.LineName+"\n";
    }
}

void SqlPraceRopid::vytvorHlavniAktualni(QString &textPoleObsah,QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek,QString locationState)
{
    qDebug()<< "SqlPraceRopid::vytvorHlavniAktualni";
    int i=0;
    textPoleObsah="";
    textPoleCasu="";
    if (locationState=="AtStop")
    {
        i=cisloporadi;
        QString cisloZastavky = QString::number(i);
        QString jmenoZastavky = docasnySeznamZastavek.at(i).zastavka.StopName;
        QString casOdjezdu =  vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).zastavka.DepartureTime);
        textPoleObsah+=cisloZastavky+" "+jmenoZastavky;
        qDebug()<<cisloZastavky<<" "<<jmenoZastavky<<" "<<casOdjezdu<<"\n";
        textPoleCasu+=casOdjezdu;
    }


    qDebug()<< "SQLpraceRopid::TestDotaz konec";

}

void SqlPraceRopid::vytvorHlavniTextNasledujici (QString &textPoleObsah,QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState)
{
    qDebug()<< "SqlPraceRopid::vytvorHlavniText";
    textPoleObsah="";
    textPoleCasu="";
    int i=0;
    int posunIndexu=0;
    if (locationState=="AtStop")
    {
        posunIndexu=1;
    }
    for (i=cisloporadi+posunIndexu;i<(docasnySeznamZastavek.count());i++)
    {
        QString cisloZastavky = QString::number(i);
        QString nazevZastavky2 = docasnySeznamZastavek.at(i).zastavka.StopName;
        QString odjezdZeZastavky =  vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).zastavka.DepartureTime);
        textPoleObsah+=cisloZastavky+" "+nazevZastavky2+"\n";
        textPoleCasu+=odjezdZeZastavky+"\n";
        qDebug()<<cisloZastavky<<" "<<nazevZastavky2<<" "<<odjezdZeZastavky<<"\n";
        //textPoleCasu+=necum+"\n";
    }
    qDebug()<< "SQLpraceRopid::TestDotaz konec";

}



int SqlPraceRopid::VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek)
{
    qDebug()<< "SqlPraceRopid::VytvorSeznamLinek";
    docasnySeznamLinek.clear();
    QString queryString2("SELECT DISTINCT l.c,l.lc,l.n FROM l ");
    queryString2+=("ORDER BY l.c;");
    QSqlQuery query;
    query.exec(queryString2); //this->mojeDatabaze);
    qDebug()<<"lasterror"<<  query.lastError();
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
    bool platnost = true;
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT s.s, s.c FROM s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("WHERE l.lc='");
    queryString2+=( QString::number(cisloLinky));
    queryString2+=("' AND  s.c !=1000 ");
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
    queryString2+=(" ORDER BY s.c");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
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





