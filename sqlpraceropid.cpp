#include "sqlpraceropid.h"
#include "VDV301struktury/zastavka.h"
#include "xmlgenerator.h"
#include "VDV301struktury/zastavkacil.h"
//#include "VDV301struktury/trip.h"
#include "VDV301struktury/obeh.h"

SqlPraceRopid::SqlPraceRopid()
{

}

//test Pridani Komentare prechodu na SQLITE

/*!

*/
int SqlPraceRopid::Pripoj()

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

/*!

*/
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


/*!

*/
int SqlPraceRopid::zavriDB()
{
    qDebug()<< "SQLpraceRopid::zavriDB";
    this->mojeDatabaze.close();
    if(1)
    {
        QString chybaZavriDb="DB se povedlo zavřít";
        emit odesliChybovouHlasku(chybaZavriDb);
        qDebug()<<chybaZavriDb;

        return 1;
    }
    else
    {
        QString chybaZavriDb="DB se nepovedlo zavřít";
        emit odesliChybovouHlasku(chybaZavriDb);
        qDebug()<<chybaZavriDb;

    }
    return 0;
}



/*!

*/
int SqlPraceRopid::StahniSeznamLinkospoj(Linka docasnaLinka, int cisloSpoje,QVector<Spoj> &seznamSpoju , QString kj )
{
    qDebug()<< "SQLprace::StahniSeznamLinkospoj";
    this->otevriDB();
    seznamSpoju.clear();
    Spoj aktualniTrip;
    aktualniTrip.globalniSeznamZastavek.clear();
    QVector<ZastavkaCil> docasnySeznamZastavek;


    QString queryString2("SELECT DISTINCT   ");
    queryString2+=("z.n, z.tp, z.tp2, z.tp3, z.cis, z.ois, ");
    queryString2+=("t.ri,t.hl, ");
    queryString2+=("t.ctn, t.btn, t.lcdn, t.vtn, ");
    queryString2+=("t.ctm, t.btm, t.lcdm, t.vtm, ");
    queryString2+=("l.c, l.lc, l.tl, l.aois,l.noc, l.cids, l.tl, ");
    queryString2+=("x.o, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, x.zsol, x.s1, x.s2, ");
    queryString2+=("s.ns, s.c, ");
    queryString2+=("ids.z AS pz1, ");
    queryString2+=("ids2.z AS pz2, ");
    queryString2+=("ids3.z AS pz3, ");
    queryString2+=("ids.c AS pc1, ");
    queryString2+=("ids2.c AS pc2, ");
    queryString2+=("ids3.c AS pc3 ");
    queryString2+=("FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    queryString2+=("LEFT JOIN ids ON z.ids=ids.c " );
    queryString2+=("LEFT JOIN ids AS ids2 ON z.ids2=ids2.c " );
    queryString2+=("LEFT JOIN ids AS ids3 ON z.ids3=ids3.c " );

    queryString2+=("WHERE l.c=");
    queryString2+=( QString::number(docasnaLinka.c));
    //290664
    queryString2+=(" AND s.c=");
    queryString2+=( QString::number(cisloSpoje));
    queryString2+=(" AND  x.s2=0 ");
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
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
    int pocetZastavek=0;
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    Zastavka cilovaZastavka;
    int navazujiciSpoj=0;
    int citacD=0;

    while (query.next())
    {
        citacD++;

        if (query.value(0).toString()!="")
        {
            bool majak=false;
            bool ignorovat=false;
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            Spoj aktSpoj;
            int cisloZast = pocetZastavek; //query.value(0).toInt();

            aktZast.StopIndex=cisloZast;
            qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(pocetZastavek);

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


            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();
           // xmlGenerator xmlgen;
            //aktZast.seznamPasem= xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp")).toString(),"PID");

         //   QVector<Pasmo> pasma1= xmlgen.pasmoStringDoVectoru(, );
           // QVector<Pasmo> pasma2= xmlgen.pasmoStringDoVectoru(query.value(query.record().indexOf("z.tp2")).toString(), query.value(query.record().indexOf("pz2")).toString() );

            QVector<QString> tp;
            tp.append(query.value(query.record().indexOf("z.tp")).toString());
            tp.append(query.value(query.record().indexOf("z.tp2")).toString());
            tp.append(query.value(query.record().indexOf("z.tp3")).toString());

            QVector<QString> pz;
            pz.append( query.value(query.record().indexOf("pz1")).toString());
            pz.append( query.value(query.record().indexOf("pz2")).toString());
            pz.append( query.value(query.record().indexOf("pz3")).toString());
            QVector<QString> pc;
            pc.append( query.value(query.record().indexOf("pc1")).toString());
            pc.append( query.value(query.record().indexOf("pc2")).toString());
            pc.append( query.value(query.record().indexOf("pc3")).toString());

            aktZast.seznamPasem.append(vyrobPasmaMezikraj(tp,pz,pc,query.value(query.record().indexOf("l.cids")).toString(),query.value(query.record().indexOf("l.tl")).toString()));




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
            aktZast.zsol=query.value(query.record().indexOf("x.zsol")).toBool();

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
            pocetZastavek++;
            qDebug()<<"citac: "<<pocetZastavek     ;
            qDebug()<<aktZast.StopName;


            //aktZastCil.spoj=aktSpoj;

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
    pocetZastavek=docasnySeznamZastavek.length();
    qDebug()<<"po pocitani zastavek";
    this->zavriDB();
    if (pocetZastavek ==0)
    {

        return 0;
    }
    qInfo()<<"DebugPointD"<<"velikost counteru je "<<QString::number(pocetZastavek);
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).zastavka;

    qInfo()<<"DebugPointD5";

    for (int i=docasnySeznamZastavek.size()-1;i>=0;i--)
    {
        if (docasnySeznamZastavek.at(i).zastavka.zsol==true)
        {
            qDebug()<<"zmena konecne na"<<docasnySeznamZastavek.at(i).zastavka.NameSide;
            cilovaZastavka=docasnySeznamZastavek.at(i).zastavka;
        }
        docasnySeznamZastavek[i].cil=cilovaZastavka;
    }
    /*
    for (int i=0; i<pocetZastavek;i++)
    {
        //docasnySeznamZastavek[i].DestinationName=cilovaZastavka.StopName ;
        //docasnySeznamZastavek[i].zastavka.DestinationCis=cilovaZastavka.cisloCis;
        docasnySeznamZastavek[i].cil=cilovaZastavka;
    }*/
    qInfo()<<"DebugPointF";
    // VypisPole(docasnySeznamZastavek,counter);
    qInfo()<<"pocetzastavek je"<<QString::number(docasnySeznamZastavek.length());

    aktualniTrip.globalniSeznamZastavek=docasnySeznamZastavek;
    aktualniTrip.cisloRopid=cisloSpoje;
    seznamSpoju.clear();
    seznamSpoju.append(aktualniTrip);



    return 1;
}






/*!

*/
int SqlPraceRopid::StahniSeznamCelySpojTurnus(QVector<Spoj> &seznamSpoju ,int indexSpoje,QString kj)
{
    qDebug()<< "StahniSeznamCelySpojTurnus";
    qDebug()<<"delka seznamu spoju: "<<seznamSpoju.length()<<" indexSpoje:"<<indexSpoje<<" kj:"<<kj;
    this->otevriDB();
    //seznamTripu.clear();
    Spoj docasnySpoj;
    QVector<ZastavkaCil> docasnySeznamZastavek;


    QString queryString2("SELECT DISTINCT   ");
    queryString2+=("z.n, z.tp, z.tp2, z.tp3, z.cis, z.ois, ");
    queryString2+=("t.ri,t.hl, ");
    queryString2+=("t.ctn, t.btn, t.lcdn, t.vtn, ");
    queryString2+=("t.ctm, t.btm, t.lcdm, t.vtm, ");
    queryString2+=("l.c, l.lc, l.tl, l.aois,l.noc,  l.cids, l.tl, ");
    queryString2+=("x.o, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, x.zsol, x.s1, x.s2, ");
    queryString2+=("s.ns, s.c, ");
    queryString2+=("ids.z AS pz1, ");
    queryString2+=("ids2.z AS pz2, ");
    queryString2+=("ids3.z AS pz3, ");
    queryString2+=("ids.c AS pc1, ");
    queryString2+=("ids2.c AS pc2, ");
    queryString2+=("ids3.c AS pc3 ");
    queryString2+=("FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    queryString2+=("LEFT JOIN ids ON z.ids=ids.c " );
    queryString2+=("LEFT JOIN ids AS ids2 ON z.ids2=ids2.c " );
    queryString2+=("LEFT JOIN ids AS ids3 ON z.ids3=ids3.c " );

    queryString2+=("WHERE s.s=");
    queryString2+=( QString::number(seznamSpoju.at(indexSpoje).cislo));
    //queryString2+=( QString::number(docasnySpoj.cislo));
    //290664
    queryString2+=(" AND  x.s2=0 ");
    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
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

    //int navazujiciSpoj=0;
    int citacD=0;

    while (query.next())
    {
        citacD++;

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
            //aktSpoj.navazujici=query.value(query.record().indexOf("s.")).toInt();

            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt() ;
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();


            //pasma
            QVector<QString> tp;
            tp.append(query.value(query.record().indexOf("z.tp")).toString());
            tp.append(query.value(query.record().indexOf("z.tp2")).toString());
            tp.append(query.value(query.record().indexOf("z.tp3")).toString());

            QVector<QString> pz;
            pz.append( query.value(query.record().indexOf("pz1")).toString());
            pz.append( query.value(query.record().indexOf("pz2")).toString());
            pz.append( query.value(query.record().indexOf("pz3")).toString());
            QVector<QString> pc;
            pc.append( query.value(query.record().indexOf("pc1")).toString());
            pc.append( query.value(query.record().indexOf("pc2")).toString());
            pc.append( query.value(query.record().indexOf("pc3")).toString());

            aktZast.seznamPasem.append(vyrobPasmaMezikraj(tp,pz,pc,query.value(query.record().indexOf("l.cids")).toString(),query.value(query.record().indexOf("l.tl")).toString()));



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
            aktZast.zsol=query.value(query.record().indexOf("x.zsol")).toBool();

            if(  query.value(query.record().indexOf("x.t")).toString() =="Majak")
            {
                majak=true;
                ignorovat=true;
            }

            //navazujiciSpoj=query.value(query.record().indexOf("s.ns")).toInt();

            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            qInfo()<<"DebugPointC";
            counter++;
            qDebug()<<"citac: "<<counter     ;
            qDebug()<<aktZast.StopName;


            //aktZastCil.spoj=aktSpoj;

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




    Zastavka cilovaZastavka;
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).zastavka;
    if(seznamSpoju.at(indexSpoje).navazujici==true)
    {

        QString novyHorniCil=cilovaZastavka.NameFront+cilovaZastavka.NameFront2;
        cilovaZastavka.NameFront=novyHorniCil;
        cilovaZastavka.NameFront2="a dále jako linka "+seznamSpoju.at(indexSpoje+1).linka.LineName;// interniSeznamZastavek.first().linka.LineName;
        qDebug()<<"obsah spodniho radku "<<cilovaZastavka.NameFront2;

    }


    qInfo()<<"DebugPointD5";
    for (int i=docasnySeznamZastavek.size()-1;i>=0;i--)
    {
        if (docasnySeznamZastavek.at(i).zastavka.zsol==true)
        {
            qDebug()<<"zmena konecne na"<<docasnySeznamZastavek.at(i).zastavka.NameSide;
            cilovaZastavka=docasnySeznamZastavek.at(i).zastavka;
        }

        docasnySeznamZastavek[i].cil=cilovaZastavka;
    }
    qInfo()<<"DebugPointF";
    // VypisPole(docasnySeznamZastavek,counter);
    qInfo()<<"pocetzastavek je"<<QString::number(docasnySeznamZastavek.length());





    // aktualniTrip.spoj=seznamSpoju.at(indexTripu);
    // aktualniTrip.navaz=docasnySpoj.navazujici;
    //seznamSpoju.at(indexSpoje).globalniSeznamZastavek=docasnySeznamZastavek;
    seznamSpoju[indexSpoje].globalniSeznamZastavek=docasnySeznamZastavek;

    //docasnySeznamZastavek=seznamSpoju.at(indexSpoje).globalniSeznamZastavek;

    return 1;
}


/*!

*/
void SqlPraceRopid::VypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< "SQLprace::VypisPole";
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].zastavka.StopIndex)+"  "+docasnySeznamZastavek[i].zastavka.StopName+" cil:  "+docasnySeznamZastavek[i].cil.StopName+" linka"+docasnySeznamZastavek[i].linka.LineName+"\n";
    }
}


/*!

*/
void SqlPraceRopid::vytvorDisplejRidiceAktualniZastavka(QString &textPoleObsah,QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek,QString locationState)
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
        QString pasma= pasmaDoStringu(docasnySeznamZastavek.at(i).zastavka.seznamPasem,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).zastavka.naZnameni==true)
        {
            znameni="(x)";
        }
        textPoleObsah+=cisloZastavky+" "+jmenoZastavky+znameni+pasma;
        qDebug()<<cisloZastavky<<" "<<jmenoZastavky<<" "<<casOdjezdu<<"\n";
        textPoleCasu+=casOdjezdu;
    }


    qDebug()<< "SQLpraceRopid::TestDotaz konec";

}

QString SqlPraceRopid::pasmaDoStringu(QVector<Pasmo> pasma, QString delimiter)
{
    QString vysledek="";

    if (pasma.count()==0)
    {
        return "";
    }
    for(int i=0; i<pasma.count()-1;i++)
    {
        vysledek+=pasma.at(i).nazev;
        vysledek+=delimiter;
    }
    vysledek+=pasma.last().nazev;
    return vysledek;
}




/*!
vytvoří seznam následujících zastávek pro zobrazení na displeji řidiče
*/
void SqlPraceRopid::vytvorDisplejRidiceSeznamZastavek (QString &textPoleObsah,QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState)
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
        QString pasma= pasmaDoStringu(docasnySeznamZastavek.at(i).zastavka.seznamPasem,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).zastavka.naZnameni==true)
        {
            znameni="(x)";
        }

        textPoleObsah+=cisloZastavky+" "+nazevZastavky2+znameni+"|"+pasma+"\n";
        textPoleCasu+=odjezdZeZastavky+"\n";


        qDebug()<<cisloZastavky<<" "<<nazevZastavky2<<odjezdZeZastavky<<"\n";
        //textPoleCasu+=necum+"\n";
    }
    qDebug()<< "SQLpraceRopid::TestDotaz konec";

}


/*!

*/
int SqlPraceRopid::VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek, QString kj)
{

    qDebug()<< "SqlPraceRopid::VytvorSeznamLinek";
    this->otevriDB();
    docasnySeznamLinek.clear();
    QString queryString2("SELECT DISTINCT l.c,l.lc,l.n FROM l ");


    queryString2+=("WHERE l.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");


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
    qDebug()<<"bylo nalezeno tolik linek: "<<citacMaximum;
    if (citacMaximum==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



/*!

*/
int SqlPraceRopid::VytvorSeznamKmenovychLinek(QVector<Linka> &docasnySeznamLinek, QString kj)
{

    qDebug()<< "SqlPraceRopid::VytvorSeznamKmenovychLinek";
    this->otevriDB();
    bool platnost=true;
    docasnySeznamLinek.clear();
    QString queryString2("SELECT DISTINCT o.l,l.c,l.lc,l.n FROM o ");
    queryString2+=("LEFT JOIN l ON o.l=l.c ");

    queryString2+=("WHERE o.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    /*queryString2+=QString::number(platnost);
    queryString2+=("%' ");*/
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
            docasnaLinka.c=query.value(query.record().indexOf("l.c")).toInt();
            // query.value(0).toInt();
            docasnaLinka.lc=query.value(query.record().indexOf("l.lc")).toInt();
            //   query.value(1).toInt();
            docasnaLinka.n=query.value(query.record().indexOf("l.n")).toString();
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


/*!

*/
int SqlPraceRopid::VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, Linka docasnaLinka, QString kj)
{
    qDebug()<< "SqlPraceRopid::VytvorSeznamSpoju";
    docasnySeznamSpoju.clear();
    this->Pripoj();
    //bool platnost = true;
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT s.s, s.c, s.kj, l.c,l.lc,l.aois FROM s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("WHERE l.c=");
    queryString2+=( QString::number(docasnaLinka.c));
    //queryString2+=(" AND  s.c !=1000 "); //vlastnosti neveřejných spojů: číslo x000,  man="true" a ty="10"
    queryString2+=(" AND  s.man !=1 ");

    /*queryString2+=(" AND  s.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
    */

    queryString2+=(" AND s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");


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
            docasnySpoj.cislo=query.value(query.record().indexOf("s.s")).toInt();
            docasnySpoj.cisloRopid=query.value(query.record().indexOf("s.c")).toInt();
            docasnySpoj.linka.lc=query.value(query.record().indexOf("l.lc")).toInt();
            QString alias=query.value(query.record().indexOf("l.aois")).toString();
            if(!alias.isEmpty())
            {
                docasnySpoj.linka.LineName=docasnySpoj.linka.c;
            }
            else
            {
                docasnySpoj.linka.LineName=alias;
            }

            docasnySpoj.linka.c=query.value(query.record().indexOf("l.c")).toInt();
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


/*!

*/
int SqlPraceRopid::VytvorSeznamTurnusSpoju(Obeh &docasnyObeh, QString kj)
{
    //QVector<Spoj> &docasnySeznamSpoju,
    qDebug()<< "SqlPraceRopid::VytvorSeznamTurnusSpoju";
    docasnyObeh.seznamSpoju.clear();
    this->Pripoj();
    // bool platnost = true;
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT sp_po.l, sp_po.p, sp_po.kj, sp_po.s, sp_po.pokrac, s.c, s.s, s.l, l.c, l.lc, l.aois FROM sp_po ");

    queryString2+=("LEFT JOIN s ON sp_po.s=s.s ");
    queryString2+=("LEFT JOIN l ON sp_po.l=l.c ");
    queryString2+=("WHERE sp_po.l=");
    queryString2+=( QString::number(docasnyObeh.kmenovaLinka.c));
    //queryString2+=(" AND  s.c !=1000 ");
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND  sp_po.p=");



    queryString2+=( QString::number(docasnyObeh.p));


    /*

    queryString2+=(" AND  sp_po.kj LIKE '");
    queryString2+=QString::number(platnost);
    queryString2+=("%' ");
    */

    queryString2+=(" AND sp_po.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");

    queryString2+=(" ORDER BY sp_po.ord");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        /* if (query.value(0).toString()!="")
        {*/
        Spoj docasnySpoj;
        docasnySpoj.cislo=query.value(query.record().indexOf("s.s")).toInt();
        docasnySpoj.cisloRopid=query.value(query.record().indexOf("s.c")).toInt();
        docasnySpoj.linka.c=query.value(query.record().indexOf("s.l")).toInt();
        docasnySpoj.navazujici=query.value(query.record().indexOf("sp_po.pokrac")).toBool();

        QString alias=query.value(query.record().indexOf("l.aois")).toString();
        qDebug()<<"alias "<<alias<<" linka.c "<<docasnySpoj.linka.c;
        if(alias.isEmpty())
        {
            docasnySpoj.linka.LineName=QString::number(docasnySpoj.linka.c);
        }
        else
        {
            docasnySpoj.linka.LineName=alias;
        }

        /*}*/
        qDebug()<<"jmeno docasny spoj linky "<<docasnySpoj.linka.LineName;
        docasnyObeh.seznamSpoju.push_back(docasnySpoj);



        citacMaximum++;
        qDebug()<<docasnySpoj.cisloRopid;
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




/*!

*/
int SqlPraceRopid::VytvorSeznamPoradi(QVector<Obeh> &docasnySeznamObehu, Linka docasnaLinka, QString kj)
{
    qDebug()<< "SqlPraceRopid::VytvorSeznamPoradi";
    docasnySeznamObehu.clear();
    this->Pripoj();
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT o.l, o.p FROM o ");
    // queryString2+=("LEFT JOIN l ON s.l=l.c ");
    queryString2+=("WHERE o.l=");
    queryString2+=( QString::number(docasnaLinka.c));
    //queryString2+=("' AND  s.c !=1000 ");




    queryString2+=(" AND o.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");



    queryString2+=(" ORDER BY o.p");
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
            Obeh docasnyObeh;
            Linka docasnaLinka;

            // aktZast.prestupVlak =query.value(query.record().indexOf("x.xVla")).toBool();

            docasnyObeh.kmenovaLinka.c=query.value(query.record().indexOf("o.l")).toInt();
            docasnyObeh.p=query.value(query.record().indexOf("o.p")).toInt();

            docasnySeznamObehu.push_back(docasnyObeh);
            citacMaximum++;
            qDebug()<<docasnyObeh.kmenovaLinka.c<<"/"<<docasnyObeh.p;
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


/*!

*/
QString SqlPraceRopid::vytvorCasHodinyMinuty(QString vstup)
{
   // qDebug()<<"SqlPraceRopid::vytvorCas";
    int cislo=vstup.toInt();
    cislo=cislo%86400; //oprava pro spoje jedoucí přes půlnoc
    int hodiny=cislo/3600;
    int minuty=(cislo%3600)/60;
    vstup="";
    vstup=QString::number(hodiny)+":"+doplnNulu( minuty,2);
    return vstup;
}


/*!

*/
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


/*!

*/
QString SqlPraceRopid::doplnNulu(int cislo,int pocetMist)
{
    //qDebug()<<"SqlPraceRopid::doplnNulu";
    QString konverze= QString::number(cislo);
    while (konverze.length()<pocetMist)
    {
        konverze="0"+konverze;
    }
    return konverze;
}


/*!

*/
int SqlPraceRopid::nactiPlatnost(QDate &platnostOd, QDate &platnostDo)
{


    qDebug()<< "SqlPraceRopid::nactiPlatnost";

    this->Pripoj();

    QString queryString2("SELECT DISTINCT h.od, h.do FROM hlavicka AS h ");


    //  queryString2+=(" ORDER BY o.p");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;

    int citacMaximum=0;
    while (query.next())
    {

        if (query.value(0).toString()!="")
        {


            /*
            QString plod=query.value(query.record().indexOf("od")).toString();
            QString pldo=query.value(query.record().indexOf("do")).toString();
            qDebug()<<"string od "<<plod<<" do "<<pldo;
            */

            //   plOd=QDate::fromString(koren.attribute("od"),Qt::ISODate);
            //    plDo=QDate::fromString(koren.attribute("do"),Qt::ISODate);


            platnostOd=query.value(query.record().indexOf("od")).toDate();
            platnostDo=query.value(query.record().indexOf("do")).toDate();
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


/*!

*/
QString SqlPraceRopid::maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti)
{
    QString vysledek="";

    int pocetDni=1;

    pocetDni=-pracDatum.daysTo(prvniDenPlatnosti);

    if(!jeDatumVRozsahu(pracDatum,prvniDenPlatnosti,konecPlatnosti))
    {
        qDebug("datum je mimo rozsah platnosti");
        return "x";
    }

    for(int i=0;i<pocetDni;i++)
    {
        vysledek+="_";
    }
    vysledek+="1%";
    qDebug()<<"data plati od "<<prvniDenPlatnosti<<" prac datum je "<<pracDatum<<" maska pro SQL databazi je "<<vysledek;

    return vysledek;

}

/*!

*/
bool SqlPraceRopid::jeDatumVRozsahu(QDate datum, QDate zacatek, QDate konec)
{

    qDebug()<<"SqlPraceRopid::jeDatumVRozsahu";
    int rozdilZacatek=datum.daysTo(zacatek);
    int rozdilKonec=datum.daysTo(konec);

    qDebug()<<"pocet dni ZACATEK "<<rozdilZacatek<<" pocet dni KONEC "<<rozdilKonec;


    if ((rozdilZacatek<=0)&&(rozdilKonec>=0))
    {
        return true;
    }



    return false;
}


QVector<Pasmo> SqlPraceRopid::vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc,  QString cids,QString tl)
{
    qDebug()<<"SqlPraceRopid::vyrobPasmaMezikraj";
    QVector<Pasmo> vystup;

    Pasmo aktpasmo;


   QStringList povoleneSystemy = cids.split(' ');
   qDebug()<<"nalezeno "<<povoleneSystemy.count()<<" systemu";

   for(int i=0;i<tp.length();i++)
   {
        QVector<Pasmo> pasma= xmlGenerator::pasmoStringDoVectoru(tp.at(i), pz.at(i),tl);
        qDebug()<<"zpracovavam pasma "<<tp.at(i)<<" "<<pz.at(i);
        if(povoleneSystemy.contains(pc.at(i)))
        {
            vystup.append(pasma);
        }
   }








    return vystup;
}

