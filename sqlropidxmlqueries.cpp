#include "sqlropidxmlqueries.h"





SqlRopidXmlQueries::SqlRopidXmlQueries()
{
    this->otevriDB();
}

//test Pridani Komentare prechodu na SQLITE

/*!

*/







/*!

*/
int SqlRopidXmlQueries::stahniSeznamCelySpojTurnus(QVector<Trip> &seznamSpoju , int indexSpoje, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    qDebug()<<"delka seznamu spoju: "<<seznamSpoju.length()<<" indexSpoje:"<<indexSpoje<<" kj:"<<kj;
    this->otevriDB();
    //Spoj docasnySpoj;
    QVector<StopPointDestination> docasnySeznamZastavek;


    QString queryString2=stahniSeznamSpolecnaCastDotazu();

    //eliminace všech smyček
    // queryString2+=(" AND  x.s2=0 ");


    queryString2+=("WHERE s.s=");
    queryString2+=( QString::number(seznamSpoju.at(indexSpoje).id));
    //  queryString2+=(" AND  x.s2=0 ");


    queryString2+=(" AND  s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=(" AND s.d=l.d ");

    queryString2+=("ORDER BY x.xorder");


    QSqlQuery query(queryString2,this->mojeDatabaze);
    int pocetZastavek=0;
    qDebug()<<queryString2;

    int citacD=0;

    while (query.next())
    {
        citacD++;

        if (query.value(0).toString()!="")
        {
            bool majak=false;
            bool ignorovat=false;
            StopPoint aktZast;
            StopPointDestination aktZastCil;
            Line aktLinka;
            Trip aktSpoj;
            int cisloZast = pocetZastavek;
            aktZast.StopIndex=cisloZast;
            //qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(pocetZastavek);
            QString aois=query.value(query.record().indexOf("l.aois")).toString();
            if (aois!="")
            {
                aktLinka.lineName=aois;
            }
            else
            {
                aktLinka.lineName=query.value(query.record().indexOf("l.c")).toString();
            }
            aktLinka.lineNumber=query.value(query.record().indexOf("l.lc")).toString();
            aktLinka.lineType=query.value(query.record().indexOf("l.tl")).toString();
            aktLinka.isNight=query.value(query.record().indexOf("l.noc")).toBool();
            aktLinka.isDiversion=query.value(query.record().indexOf("s.vy")).toBool();

            aktSpoj.idRopid=query.value(query.record().indexOf("s.c")).toInt();
            aktZast.idCis=query.value( query.record().indexOf("z.cis")).toInt();
            aktZast.idOis=query.value(query.record().indexOf("z.ois")).toUInt();

            aktZast.idU=query.value(query.record().indexOf("z.u")).toUInt();
            aktZast.idZ=query.value(query.record().indexOf("z.z")).toUInt();
            //pasma
            QVector<QString> tp;
            tp.append(query.value(query.record().indexOf("z.tp")).toString());
            tp.append(query.value(query.record().indexOf("z.tp2")).toString());
            tp.append(query.value(query.record().indexOf("z.tp3")).toString());

            QVector<QString> pz;
            pz.append(query.value(query.record().indexOf("pz1")).toString());
            pz.append(query.value(query.record().indexOf("pz2")).toString());
            pz.append(query.value(query.record().indexOf("pz3")).toString());
            QVector<QString> pc;
            pc.append(query.value(query.record().indexOf("pc1")).toString());
            pc.append(query.value(query.record().indexOf("pc2")).toString());
            pc.append(query.value(query.record().indexOf("pc3")).toString());

            aktZast.fareZoneList.append(vyrobPasmaMezikraj(tp,pz,pc,query.value(query.record().indexOf("l.cids")).toString(),query.value(query.record().indexOf("l.tl")).toString()));
            aktZast.StopName=query.value(query.record().indexOf("t.ri")).toString();
            aktZast.ids ="PID";

            if(aktLinka.lineType!="A")
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

            QString arrivalTime =query.value( query.record().indexOf("x.p")).toString();
            aktZast.ArrivalTime=arrivalTime;
            QString departureTime =query.value( query.record().indexOf("x.o")).toString();
            aktZast.DepartureTime=departureTime;
            aktZast.isViapoint=query.value(query.record().indexOf("x.na")).toInt();
            aktZast.onRequest =query.value(query.record().indexOf("x.zn")).toBool();
            aktZast.transferMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            aktZast.transferMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            aktZast.transferMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            aktZast.transferMetroD =query.value(query.record().indexOf("x.xD")).toBool();
            aktZast.transferTrain =query.value(query.record().indexOf("x.xVla")).toBool();
            aktZast.transferAirplane =query.value(query.record().indexOf("x.xLet")).toBool();
            aktZast.transferFerry =query.value(query.record().indexOf("x.xLod")).toBool();
            aktZast.zsol=query.value(query.record().indexOf("x.zsol")).toBool();
            aktZast.lng=query.value(query.record().indexOf("z.lng")).toDouble();
            aktZast.lat=query.value(query.record().indexOf("z.lat")).toDouble();
            aktZast.radius=query.value(query.record().indexOf("z.rdisp")).toInt();
            qDebug()<<"radius je: "<<aktZast.radius;


            aktZast.notesList=stahniPoznamky(query.value(query.record().indexOf("x.s_id")).toInt(),query.value(query.record().indexOf("x.xorder")).toInt());

            qDebug()<<"pocetPoznamek "<<QString::number(aktZast.notesList.count());


            aktLinka.kli=query.value(query.record().indexOf("l.kli")).toInt();


            if(  query.value(query.record().indexOf("x.t")).toString() =="Majak")
            {
                majak=true;
                ignorovat=true;
            }


            if(aktZast.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<aktZast.additionalTextMessage;
            }
            pocetZastavek++;

            aktZastCil.line=aktLinka;
            aktZastCil.stopPoint=aktZast;

            bool s2=query.value(query.record().indexOf("x.s2")).toBool();

            if((citacD!=1)&&(s2==true))
            {
                ignorovat=true;
            }

            if (ignorovat==false)
            {
                docasnySeznamZastavek.push_back(aktZastCil);
            }
        }
    }

    pocetZastavek=docasnySeznamZastavek.length();
    this->zavriDB();
    if (pocetZastavek ==0)
    {

        return 0;
    }

    StopPoint cilovaZastavka;
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).stopPoint;
    if(seznamSpoju.at(indexSpoje).continuesWithNextTrip==true)
    {
        QString novyHorniCil=cilovaZastavka.NameFront+cilovaZastavka.NameFront2;
        cilovaZastavka.NameFront=novyHorniCil;
        cilovaZastavka.NameFront2="a dále jako linka "+seznamSpoju.at(indexSpoje+1).line.lineName;// interniSeznamZastavek.first().linka.LineName;
        qDebug()<<"obsah spodniho radku "<<cilovaZastavka.NameFront2;
    }


    for (int i=docasnySeznamZastavek.size()-1;i>=0;i--)
    {
        if (docasnySeznamZastavek.at(i).stopPoint.zsol==true)
        {
            qDebug()<<"zmena konecne na"<<docasnySeznamZastavek.at(i).stopPoint.NameSide;
            cilovaZastavka=docasnySeznamZastavek.at(i).stopPoint;
        }

        docasnySeznamZastavek[i].destination=cilovaZastavka;
    }

    seznamSpoju[indexSpoje].globalStopPointDestinationList=docasnySeznamZastavek;

    return 1;
}

QString SqlRopidXmlQueries::stahniSeznamSpolecnaCastDotazu()
{
    qDebug()<< Q_FUNC_INFO;
    /*
   Mozna nahrada!

dbManager->query.prepare("INSERT INTO users (username, pass, userGroup) VALUES (:name, :pass, :group)");

dbManager->query.bindValue(":name", username);
dbManager->query.bindValue(":pass", password);
dbManager->query.bindValue(":group", 0);
dbManager->query.exec();

      */
    QString queryString2("SELECT DISTINCT   ");
    queryString2+=("z.n, z.tp, z.tp2, z.tp3, z.cis, z.ois, z.u, z.z, z.lng, z.lat, z.rdisp, ");
    queryString2+=("t.ri,t.hl, ");
    queryString2+=("t.ctn, t.btn, t.lcdn, t.vtn, ");
    queryString2+=("t.ctm, t.btm, t.lcdm, t.vtm, ");
    queryString2+=("l.c, l.lc, l.tl, l.aois,l.noc, l.cids, l.tl, l.kli, ");
    queryString2+=("x.o, x.p, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, x.zsol, x.s1, x.s2, x.s_id, ");
    queryString2+=("s.ns, s.c, s.vy, ");
    queryString2+=("ids.z AS pz1, ");
    queryString2+=("ids2.z AS pz2, ");
    queryString2+=("ids3.z AS pz3, ");
    queryString2+=("ids.c AS pc1, ");
    queryString2+=("ids2.c AS pc2, ");
    queryString2+=("ids3.c AS pc3 ");
    queryString2+=("FROM x ");
    queryString2+=("LEFT JOIN s ON x.s_id=s.s ");
    queryString2+=("LEFT JOIN z ON x.u = z.u AND x.z=z.z ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("LEFT JOIN t ON t.u=x.u AND t.z=x.z " );
    queryString2+=("LEFT JOIN ids ON z.ids=ids.c " );
    queryString2+=("LEFT JOIN ids AS ids2 ON z.ids2=ids2.c " );
    queryString2+=("LEFT JOIN ids AS ids3 ON z.ids3=ids3.c " );

    return queryString2;
}

/*!

*/
void SqlRopidXmlQueries::vypisPole(QVector<StopPointDestination> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< Q_FUNC_INFO;
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].stopPoint.StopIndex)+"  "+docasnySeznamZastavek[i].stopPoint.StopName+" cil:  "+docasnySeznamZastavek[i].destination.StopName+" linka"+docasnySeznamZastavek[i].line.lineName+"\n";
    }
}



QString SqlRopidXmlQueries::pasmaDoStringu(QVector<FareZone> pasma, QString delimiter)
{
    QString vysledek="";

    if (pasma.count()==0)
    {
        return "";
    }
    for(int i=0; i<pasma.count()-1;i++)
    {
        vysledek+=pasma.at(i).name;
        vysledek+=delimiter;
    }
    vysledek+=pasma.last().name;
    return vysledek;
}


QVector<QString> SqlRopidXmlQueries::stahniPoznamky(int idSpoje, int xorder)
{
    qDebug()<< Q_FUNC_INFO;
    //this->otevriDB();
    QVector<QString> seznamPoznamek;


    QString queryString2("");
    queryString2+=("SELECT x_po.s, x_po.xorder, x_po.po,  po.c, po.t, po.ois ");
    queryString2+=("FROM  x_po  ");
    queryString2+=("LEFT JOIN po ON x_po.po=po.c ");
    queryString2+=("WHERE po.t<>\"\" ");
    queryString2+=("AND po.ois=1 ");
    queryString2+=("AND  x_po.s=");
    queryString2+=QString::number(idSpoje);
    queryString2+=(" AND x_po.xorder=");
    queryString2+=QString::number(xorder);


    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror"<<  query.lastError();
    qDebug().noquote()<<queryString2;
    //  qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {

        QString poznamka=query.value(query.record().indexOf("po.t")).toString();
        seznamPoznamek.push_back(poznamka);
        citacMaximum++;

    }
    // this->zavriDB();


    return seznamPoznamek;
}

int SqlRopidXmlQueries::najdiTurnusZeSpoje(Trip spoj, int &kmenovaLinka, int &poradi, int &order, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    // docasnySeznamSpoju.clear();
    this->pripoj();
    //bool platnost = true;
    //qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT s.s, s.c, s.kj, l.c,l.lc,l.aois, sp_po.l, sp_po.p, sp_po.ord FROM s ");
    queryString2+=("LEFT JOIN sp_po ON sp_po.s=s.s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE l.c=");
    queryString2+=(QString::number(spoj.line.c));
    queryString2+=(" AND s.c=");
    queryString2+=(QString::number(spoj.idRopid));
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=(" ORDER BY s.c");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;
    // qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            citacMaximum++;
            kmenovaLinka=query.value(query.record().indexOf("sp_po.l")).toInt();
            poradi=query.value(query.record().indexOf("sp_po.p")).toInt();
            order=query.value(query.record().indexOf("sp_po.ord")).toInt()-1;
        }
    }

    qDebug()<<"Spoj "<<spoj.line.c<<"/"<<spoj.idRopid<<" spada pod kurz "<<kmenovaLinka<<"/"<<poradi<<" order:"<<order;
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
int SqlRopidXmlQueries::vytvorSeznamTurnusSpoju(VehicleRun &docasnyObeh, QString kj)
{
    //QVector<Spoj> &docasnySeznamSpoju,
    qDebug()<< Q_FUNC_INFO;
    docasnyObeh.tripList.clear();
    this->pripoj();
    QString queryString2("SELECT DISTINCT sp_po.l, sp_po.p, sp_po.kj, sp_po.s, sp_po.pokrac, s.c, s.s, s.l, l.c, l.lc, l.aois FROM sp_po ");
    queryString2+=("LEFT JOIN s ON sp_po.s=s.s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE sp_po.l=");
    queryString2+=( QString::number(docasnyObeh.rootLine.c));
    //queryString2+=(" AND  s.c !=1000 ");
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND  sp_po.p=");
    queryString2+=( QString::number(docasnyObeh.order));


    queryString2+=(" AND sp_po.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");

    queryString2+=(" ORDER BY sp_po.ord");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;
    //  qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {

        Trip docasnySpoj;
        docasnySpoj.id=query.value(query.record().indexOf("s.s")).toInt();
        docasnySpoj.idRopid=query.value(query.record().indexOf("s.c")).toInt();
        docasnySpoj.line.c=query.value(query.record().indexOf("s.l")).toInt();
        docasnySpoj.continuesWithNextTrip=query.value(query.record().indexOf("sp_po.pokrac")).toBool();

        QString alias=query.value(query.record().indexOf("l.aois")).toString();
        //  qDebug()<<"alias "<<alias<<" linka.c "<<docasnySpoj.linka.c;
        if(alias.isEmpty())
        {
            docasnySpoj.line.lineName=QString::number(docasnySpoj.line.c);
        }
        else
        {
            docasnySpoj.line.lineName=alias;
        }

        //qDebug()<<"jmeno docasny spoj linky "<<docasnySpoj.linka.LineName;
        docasnyObeh.tripList.push_back(docasnySpoj);
        citacMaximum++;
        // qDebug()<<docasnySpoj.cisloRopid;
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


int SqlRopidXmlQueries::poziceSpojeNaSeznamu(QVector<Trip> seznamSpoju, Trip spoj)
{
    qDebug()<< Q_FUNC_INFO;
    qDebug()<<"delka seznamu spoju: "<<seznamSpoju.count();
    for(int i=0;i<seznamSpoju.count();i++)
    {
        if((seznamSpoju.at(i).line.c==spoj.line.c)&&(seznamSpoju.at(i).idRopid)==spoj.idRopid)
        {
            return i;
        }
    }

    return -1;
}


/*!

*/
int SqlRopidXmlQueries::nactiPlatnost(QDate &platnostOd, QDate &platnostDo)
{


    qDebug()<< Q_FUNC_INFO;

    this->pripoj();

    QString queryString2("SELECT DISTINCT h.od, h.do FROM hlavicka AS h ");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;

    int citacMaximum=0;
    while (query.next())
    {

        if (query.value(0).toString()!="")
        {
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
QString SqlRopidXmlQueries::maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti)
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


QVector<FareZone> SqlRopidXmlQueries::vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc,  QString cids,QString tl)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> vystup;
    FareZone aktpasmo;
    QStringList povoleneSystemy = cids.split(' ');
    qDebug()<<"nalezeno "<<povoleneSystemy.count()<<" systemu";

    for(int i=0;i<tp.length();i++)
    {
        QVector<FareZone> pasma= pasmoStringDoVectoru(tp.at(i), pz.at(i),tl);
        if(povoleneSystemy.contains(pc.at(i)))
        {
            vystup.append(pasma);
        }
    }
    return vystup;
}

QVector<FareZone> SqlRopidXmlQueries::pasmoStringDoVectoru(QString vstup,QString system,QString tl)
{
    QStringList stringPasma = vstup.split(',');
    QVector<FareZone> seznamPasem;

    for (int i=0;i<stringPasma.length();i++)
    {
        FareZone intPasmo;
        intPasmo.name=stringPasma.at(i);
        intPasmo.system=system;

        if(intPasmo.name!="-")
        {
            if(tl=="A")
            {
                if(intPasmo.name=="P")
                {
                    seznamPasem.append(intPasmo);
                }
            }
            else
            {
                if (intPasmo.name!="P")
                {
                    seznamPasem.append(intPasmo);
                }
            }
        }
    }
    return seznamPasem;
}


///////////////////////// model view approach

QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamLinekModel(QString kj)
{
    qDebug() <<  Q_FUNC_INFO;

    QString queryString2("SELECT DISTINCT l.c FROM l ");
    //QString queryString2("SELECT DISTINCT l.c,l.lc,l.n FROM l ");
    queryString2+=("WHERE l.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=("ORDER BY l.c;");

    qDebug()<<queryString2;

    QSqlQueryModel *model= new QSqlTableModel ;
    model->setQuery(queryString2);

    return model;
}

QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamKmenovychLinekModel(QString kj)
{
    qDebug() <<  Q_FUNC_INFO;

    QString queryString2("SELECT DISTINCT o.l,l.c,l.n ");
    //QString queryString2("SELECT DISTINCT o.l,l.c,l.lc,l.n ");
    queryString2+=("FROM o ");
    queryString2+=("LEFT JOIN l ON o.l=l.c ");
    queryString2+=("WHERE o.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=("ORDER BY l.c;");

    qDebug()<<queryString2;

    QSqlQuery query;
    query.exec(queryString2);

    QSqlQueryModel *model= new QSqlTableModel ;
    model->setQuery(queryString2);
    return model;
}

QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamSpojuModel(Line docasnaLinka, QString kj)
{
    qDebug() <<  Q_FUNC_INFO;

    QString queryString2("SELECT DISTINCT s.s, s.c, s.kj, l.c,l.aois FROM s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE l.c=");
    queryString2+=( QString::number(docasnaLinka.c));
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=(" ORDER BY s.c");

    QSqlQueryModel *model= new QSqlTableModel ;
    model->setQuery(queryString2);

    return model;
}


QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamPoradiModel(Line docasnaLinka, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    this->pripoj();
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT o.l, o.p FROM o ");
    queryString2+=("WHERE o.l=");
    queryString2+=( QString::number(docasnaLinka.c));
    queryString2+=(" AND o.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=(" ORDER BY o.p");
    QSqlQuery query;
    query.exec(queryString2);
    qDebug()<<"lasterror "<<query.lastError();
    qDebug()<<queryString2;
    qDebug()<<"DebugPointB";

    QSqlQueryModel *model= new QSqlTableModel ;
    model->setQuery(queryString2);

    return model;
}


/*!

*/
QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamTurnusSpojuModel(VehicleRun &docasnyObeh, QString kj)
{
    //QVector<Spoj> &docasnySeznamSpoju,
    qDebug()<< Q_FUNC_INFO;

    this->pripoj();
    // bool platnost = true;
    qInfo()<<"DebugPointA";
    QString queryString2("SELECT DISTINCT l.c, s.c FROM sp_po ");
    queryString2+=("LEFT JOIN s ON sp_po.s=s.s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE sp_po.l=");
    queryString2+=( QString::number(docasnyObeh.rootLine.c));
    //queryString2+=(" AND  s.c !=1000 ");
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND  sp_po.p=");
    queryString2+=( QString::number(docasnyObeh.order));

    queryString2+=(" AND sp_po.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");

    queryString2+=(" ORDER BY sp_po.ord");
    QSqlQuery query;
    query.exec(queryString2);

    QSqlQueryModel *model= new QSqlTableModel ;
    model->setQuery(queryString2);

    return model;
}


//mapa


QVector<MapaBod> SqlRopidXmlQueries::vytvorTrajektorii(int cisloSpoje, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    //QVector<Spoj> &docasnySeznamSpoju,
    QVector<MapaBod> vystup;



    this->pripoj();

    QString queryString2="";


    queryString2+="SELECT DISTINCT ";
    queryString2+="bod.u1, bod.u2, bod.z1, bod.z2, bod.poradi, bod.x, bod.y, ";
    queryString2+="z.n, z.cis, z.ois,  ";
    queryString2+="l.c, l.lc, l.tl,  ";
    queryString2+="x.t, x.xorder, x.zsol, x.s1, x.s2, x.s_id,  ";
    queryString2+="s.ns, s.c, s.vy ";

    queryString2+="FROM x LEFT JOIN s ON x.s_id=s.s ";

    queryString2+="LEFT JOIN x AS x2 ON x.id+1=(x2.id) ";
    queryString2+="LEFT JOIN z ON x.u = z.u AND x.z=z.z ";
    queryString2+="LEFT JOIN l ON s.l=l.c  AND s.d=l.d ";
    queryString2+="LEFT JOIN t ON t.u=x.u AND t.z=x.z ";
    queryString2+="LEFT JOIN bod ON bod.u1=x.u AND bod.z1=x.z AND bod.u2=x2.u AND bod.z2=x2.z AND bod.var=x2.var ";
    queryString2+="WHERE s.s=";
    queryString2+=QString::number(cisloSpoje);
    queryString2+=" AND  s.kj LIKE '"+kj+"'  AND s.d=l.d ";
    queryString2+="ORDER BY x.xorder, bod.poradi ";

    QSqlQuery query;
    query.exec(queryString2);
    qDebug().noquote()<<queryString2;
    qDebug()<<"lasterror "<<query.lastError();

    //  qDebug()<<"DebugPointB";
    int citacMaximum=0;
    while (query.next())
    {
        MapaBod bod;

        QString u1=query.value(query.record().indexOf("bod.u1")).toString();
        QString z1=query.value(query.record().indexOf("bod.z1")).toString();

        QString u2=query.value(query.record().indexOf("bod.u2")).toString();
        QString z2=query.value(query.record().indexOf("bod.z2")).toString();

        //bod.radius =query.value( query.record().indexOf("z.rdisp")).toInt();

        bod.lat=absolutniHodnota(query.value( query.record().indexOf("bod.x")).toDouble());
        bod.lng=absolutniHodnota(query.value( query.record().indexOf("bod.y")).toDouble());

        QString obsah="";
        obsah+="u1: "+u1+" ";
        obsah+="z1: "+z1+" ";
        obsah+="u2: "+u2+" ";
        obsah+="z2: "+z2+" ";
        bod.obsah=obsah;

        if((bod.lat!=0.0)&&(bod.lng!=0.))
        {
            vystup.push_back(bod);
        }
        citacMaximum++;
        // qDebug()<<docasnySpoj.cisloRopid;
    }



    this->zavriDB();

    return vystup;
}

double SqlRopidXmlQueries::absolutniHodnota(double vstup)
{
    if (vstup<0)
    {
        vstup=-vstup;
    }
    return vstup;
}



QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamSpojuModel2(Line docasnaLinka, QString kj)
{
    qDebug() <<  Q_FUNC_INFO;

    QString queryString2(" SELECT DISTINCT s.c, z.n AS Z, zz.n AS DO, substr(time(x.o, 'unixepoch'),1,5) AS start, substr(time(xx.p, 'unixepoch'),1,5) AS konec, s.s, l.c, l.lc   "
                         " FROM s "
                         " LEFT JOIN l ON s.l=l.c  AND s.d=l.d "
                         " LEFT JOIN x ON s.s=x.s_id AND x.xorder=0"
                         " LEFT JOIN z ON x.u=z.u AND x.z=z.z"
                         " LEFT JOIN ("
                         " SELECT x.u, x.z, x.s_id, MAX(x.p) AS p, MAX(x.xorder) AS pocet "
                         " FROM (SELECT x.o,x.p,x.s_id,x.xorder, x.u, x.z FROM x WHERE s2=0) AS x "
                         " GROUP BY x.s_id ) AS xx"
                         " ON xx.s_id=s.s"
                         " LEFT JOIN z AS zz ON xx.u=zz.u AND xx.z=zz.z ");


    queryString2+=(" WHERE l.c="+QString::number(docasnaLinka.c)+" AND s.man !=1 AND s.kj LIKE '"+kj+"' ");
    queryString2+=(" ORDER BY s.c ASC, s.s ASC");

    qDebug().noquote()<<queryString2;

    QSqlQueryModel *modelData= new QSqlTableModel ;
    modelData->setQuery(queryString2);
    qDebug()<<modelData->lastError();

    while ( modelData->canFetchMore())
    {
        modelData->fetchMore();
    }

    return modelData;
}


