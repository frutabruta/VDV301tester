#include "sqlpraceropid.h"
#include "VDV301struktury/zastavka.h"
#include "xmlgenerator.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/trip.h"

SqlPraceRopid::SqlPraceRopid()
{

}

//test Pridani Komentare prechodu na SQLITE
int SqlPraceRopid::Pripoj(QString adresa)

{
    qDebug()<< "SQLpraceRopid::Pripoj";
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
    bool ok = otevriDB();
    if (ok==true)
    {
        emit odesliChybovouHlasku("připojení se povedlo");
        return 1;
    }
    else
    {
        emit odesliChybovouHlasku("připojení se nezdařilo");
        qDebug()<<"nepovedlo se";
        return 0;
    }

}


int SqlPraceRopid::otevriDB()
{
  qDebug()<< "SQLpraceRopid::otevriDB";
    if(this->mojeDatabaze.open())
    {
        qDebug()<<"podarilo se pripojit k databazi ROPID";
        qDebug()<<"is driver available "<<QString::number(mojeDatabaze.isDriverAvailable("QSQLITE"));
        qDebug()<<"je databaze otevrena "<<QString::number(mojeDatabaze.isOpen());
         emit odesliChybovouHlasku("je databaze otevrena");
        qDebug()<<"je databaze validni "<<QString::number(mojeDatabaze.isValid());
        // qDebug()<<"transaction mode"+QString::number(mojeDatabaze.transaction());
        return 1;
    }
    else
    {
        qDebug()<<"DB se nepovedlo otevrit "<<mojeDatabaze.lastError();

    }
    return 0;
}

int SqlPraceRopid::zavriDB()
{
     qDebug()<< "SQLpraceRopid::zavriDB";
    this->mojeDatabaze.close();
    if(1)
    {
        emit odesliChybovouHlasku("");
        qDebug()<<"DB se povedlo zavřít";

        return 1;
    }
    else
    {
        emit odesliChybovouHlasku("");
        qDebug()<<"DB se nepovedlo zavřít";

    }
    return 0;
}




int SqlPraceRopid::StahniSeznam(int cisloLinky, int cisloSpoje,QVector<Trip> &seznamTripu , bool platnost )
{
    this->otevriDB();

    seznamTripu.clear();
    Trip aktualniTrip;
    aktualniTrip.globalniSeznamZastavek.clear();

   // docasnySeznamZastavek.clear();
    qDebug()<< "SQLprace::StahniSeznam";


    QVector<ZastavkaCil> docasnySeznamZastavek;

        //    .first().globalniSeznamZastavek

    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT   ");
    queryString2+=("z.n, z.tp, z.cis, z.ois, ");
    queryString2+=("t.ri,t.hl, ");
    queryString2+=("t.ctn, t.btn, t.lcdn, t.vtn, ");
    queryString2+=("t.ctm, t.btm, t.lcdm, t.vtm, ");
    queryString2+=("l.c, l.lc, l.tl, l.aois,l.noc, ");
    queryString2+=("x.o, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, ");
    queryString2+=("s.ns, s.c ");
    queryString2+=("FROM x ");
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
    Zastavka cilovaZastavka;
    int navazujiciSpoj=0;
    int citacD=0;

    while (query.next())
    {
        //qDebug()<<"SQL citac pred zpracovanim"<<citacD;
        citacD++;
        //qDebug()<<query.lastError();

        if (query.value(0).toString()!="")
        {
            bool majak=false;
            bool ignorovat=false;
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            Spoj aktSpoj;
            int cisloZast = counter; //query.value(0).toInt();

            aktZast.StopIndex=cisloZast;
            qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(counter);

            //aktLinka.LineName=query.value(query.record().indexOf("l.c")).toString();
            QString aois=query.value(query.record().indexOf("l.aois")).toString();
            if (aois!="")
            {
                aktLinka.LineName=aois;
            }
            else
            {
                aktLinka.LineName=query.value(query.record().indexOf("l.c")).toString();
            }
            aktLinka.LineNumber=query.value(query.record().indexOf("l.lc")).toString();
            aktLinka.typLinky=query.value(query.record().indexOf("l.tl")).toString();
            aktLinka.isNight=query.value(query.record().indexOf("l.noc")).toBool();


            aktSpoj.cisloRopid=query.value(query.record().indexOf("s.c")).toInt();

            //aktZast.StopName =query.value( query.record().indexOf("z.n")).toString();
            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
            xmlGenerator xmlgen;
            aktZast.seznamPasem=xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp")).toString(),"PID");
            qDebug()<<"pasmo"<<query.value(query.record().indexOf("z.tp")).toString();

            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();
            aktZast.ids ="PID";

            if(aktLinka.typLinky!="A")
            {
                aktZast.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
                aktZast.NameSide=query.value(query.record().indexOf("t.btn")).toString();
                aktZast.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();
                aktZast.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
            }
            else
            {
                aktZast.NameFront=query.value(query.record().indexOf("t.ctm")).toString();
                aktZast.NameSide=query.value(query.record().indexOf("t.btm")).toString();
                aktZast.NameLcd=query.value(query.record().indexOf("t.lcdm")).toString();
                aktZast.NameInner=query.value(query.record().indexOf("t.vtm")).toString();
            }



            aktZast.additionalTextMessage =query.value(query.record().indexOf("t.hl")).toString();

            QString casPrijezdu =query.value( query.record().indexOf("x.o")).toString();
            aktZast.DepartureTime=casPrijezdu;



            // aktLinka.tl=query.value(query.record().indexOf("l.tl")).toString();

            aktZast.nacestna=query.value(query.record().indexOf("x.na")).toInt();
            aktZast.naZnameni =query.value(query.record().indexOf("x.zn")).toBool();
            aktZast.prestupMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.prestupMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xD")).toBool();
            aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();
            aktZast.prestupLetadlo =query.value(query.record().indexOf("x.xLet")).toBool();
            aktZast.prestupPrivoz =query.value(query.record().indexOf("x.xLod")).toBool();

            if(  query.value(query.record().indexOf("x.t")).toString() =="Majak")
            {
                majak=true;
                ignorovat=true;
            }

            navazujiciSpoj=query.value(query.record().indexOf("s.ns")).toInt();

            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<counter     ;
            qDebug()<<aktZast.StopName;


            aktZastCil.spoj=aktSpoj;

            aktZastCil.linka=aktLinka;
            aktZastCil.zastavka=aktZast;
            if (ignorovat==false)
            {
                qInfo()<<"DebugPointC3"<<" pridavam zastavku "<<aktZastCil.zastavka.StopName;
                docasnySeznamZastavek.push_back(aktZastCil);
            }
            qInfo()<<"DebugPointC5";
        }
    }
    qDebug()<<"pred pocitanim zastavek";
    counter=docasnySeznamZastavek.length();
    qDebug()<<"po pocitani zastavek";
    this->zavriDB();
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

    aktualniTrip.globalniSeznamZastavek=docasnySeznamZastavek;
    seznamTripu.append(aktualniTrip);

    if (navazujiciSpoj!=0)
    {
        qDebug()<<"navazujici spoj ma cislo "<<QString::number(navazujiciSpoj);
        StahniSeznamNavazSpoj(navazujiciSpoj,docasnySeznamZastavek,platnost);
        return 2;
    }
    else
    {
        qDebug()<<"navazujici spoj neni";
    }

    return 1;
}









int SqlPraceRopid::StahniSeznamNavazSpoj(int idSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost )
{
    qDebug()<< "SQLprace::StahniSeznam";

    QVector <ZastavkaCil> interniSeznamZastavek;


    this->otevriDB();
    //docasnySeznamZastavek.clear();


    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT   ");
    queryString2+=("z.n, z.tp, z.cis, z.ois, ");
    queryString2+=("t.ri,t.hl, ");
    queryString2+=("t.ctn, t.btn, t.lcdn, t.vtn, ");
    queryString2+=("t.ctm, t.btm, t.lcdm, t.vtm, ");
    queryString2+=("l.c, l.lc, l.tl, ");
    queryString2+=("x.o, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, ");
    queryString2+=("s.ns ");
    queryString2+=("FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );

    queryString2+=("WHERE s.s=");
    queryString2+=( QString::number(idSpoje));
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
    Zastavka cilovaZastavka;
    int navazujiciSpoj=0;
    int citacD=0;

    while (query.next())
    {
        //qDebug()<<"SQL citac pred zpracovanim"<<citacD;
        citacD++;
        //qDebug()<<query.lastError();

        if (query.value(0).toString()!="")
        {
            bool majak=false;
            bool ignorovat=false;
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            int cisloZast = counter; //query.value(0).toInt();

            aktZast.StopIndex=cisloZast;
            qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(counter);

            aktLinka.LineName=query.value(query.record().indexOf("l.c")).toString();
            aktLinka.LineNumber=query.value(query.record().indexOf("l.lc")).toString();
            aktLinka.typLinky=query.value(query.record().indexOf("l.tl")).toString();




            //aktZast.StopName =query.value( query.record().indexOf("z.n")).toString();
            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
            xmlGenerator xmlgen;
            aktZast.seznamPasem=xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp")).toString(),"PID");
            qDebug()<<"pasmo"<<query.value(query.record().indexOf("z.tp")).toString();

            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();
            aktZast.ids ="PID";

            if(aktLinka.typLinky=="A")
            {
                aktZast.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
                aktZast.NameSide=query.value(query.record().indexOf("t.btn")).toString();
                aktZast.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();
                aktZast.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
            }
            else
            {
                aktZast.NameFront=query.value(query.record().indexOf("t.ctm")).toString();
                aktZast.NameSide=query.value(query.record().indexOf("t.btm")).toString();
                aktZast.NameLcd=query.value(query.record().indexOf("t.lcdm")).toString();
                aktZast.NameInner=query.value(query.record().indexOf("t.vtm")).toString();
            }



            aktZast.additionalTextMessage =query.value(query.record().indexOf("t.hl")).toString();

            QString casPrijezdu =query.value( query.record().indexOf("x.o")).toString();
            aktZast.DepartureTime=casPrijezdu;



            // aktLinka.tl=query.value(query.record().indexOf("l.tl")).toString();

            aktZast.nacestna=query.value(query.record().indexOf("x.na")).toInt();
            aktZast.naZnameni =query.value(query.record().indexOf("x.zn")).toBool();
            aktZast.prestupMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.prestupMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.prestupMetroC =query.value(query.record().indexOf("x.xD")).toBool();
            aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();
            aktZast.prestupLetadlo =query.value(query.record().indexOf("x.xLet")).toBool();
            aktZast.prestupPrivoz =query.value(query.record().indexOf("x.xLod")).toBool();

            if(  query.value(query.record().indexOf("x.t")).toString() =="Majak")
            {
                majak=true;
                ignorovat=true;
            }

            navazujiciSpoj=query.value(query.record().indexOf("s.ns")).toInt();

            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<counter     ;
            qDebug()<<aktZast.StopName;
            aktZastCil.linka=aktLinka;
            aktZastCil.zastavka=aktZast;
            if (ignorovat==false)
            {
                qInfo()<<"DebugPointC3"<<" pridavam zastavku "<<aktZastCil.zastavka.StopName;
                interniSeznamZastavek.push_back(aktZastCil);
            }
            qInfo()<<"DebugPointC5";
        }
    }
    qDebug()<<"pred pocitanim zastavek";
    counter=interniSeznamZastavek.length();
    qDebug()<<"po pocitani zastavek";
    this->zavriDB();
    if (counter ==0)
    {

        return 0;
    }
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(counter);
    cilovaZastavka=interniSeznamZastavek.at(interniSeznamZastavek.length()-1).zastavka;

    qInfo()<<"DebugPointD5";
    for (int i=0; i<counter;i++)
    {
        //docasnySeznamZastavek[i].DestinationName=cilovaZastavka.StopName ;
        //docasnySeznamZastavek[i].zastavka.DestinationCis=cilovaZastavka.cisloCis;
        interniSeznamZastavek[i].cil=cilovaZastavka;
    }
    qInfo()<<"DebugPointF";
    // VypisPole(docasnySeznamZastavek,counter);
    qInfo()<<"pocetzastavek je"<<QString::number(interniSeznamZastavek.length());

    if (navazujiciSpoj!=0)
    {
        qDebug()<<"navazujici spoj ma cislo "<<QString::number(navazujiciSpoj);
        return 2;
        StahniSeznamNavazSpoj(navazujiciSpoj,interniSeznamZastavek,platnost);

    }
    else
    {
        qDebug()<<"navazujici spoj2 neni";
    }

    if (docasnySeznamZastavek.size()>0 )
    {
        qDebug()<<"odstranuji posledni zastavku";
        docasnySeznamZastavek.removeLast();
    }

    for(int i=0;i<docasnySeznamZastavek.size();i++)
    {

        QString novyHorniCil=docasnySeznamZastavek.at(i).cil.NameFront+docasnySeznamZastavek.at(i).cil.NameFront2;
        docasnySeznamZastavek[i].cil.NameFront=novyHorniCil;
        docasnySeznamZastavek[i].cil.NameFront2="a dále jako linka "+interniSeznamZastavek.first().linka.LineName;
        qDebug()<<"obsah spodniho radku "<<docasnySeznamZastavek[i].cil.NameFront2;

    }

    docasnySeznamZastavek.append(interniSeznamZastavek);

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
    this->otevriDB();
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
    this->zavriDB();
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
    this->Pripoj("");
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

    this->zavriDB();
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





