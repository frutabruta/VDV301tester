#include "sqlropidxmldotazy.h"





SqlRopidXmlDotazy::SqlRopidXmlDotazy()
{
    this->otevriDB();
}

//test Pridani Komentare prechodu na SQLITE

/*!

*/







/*!

*/
int SqlRopidXmlDotazy::stahniSeznamCelySpojTurnus(QVector<Spoj> &seznamSpoju ,int indexSpoje,QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    qDebug()<<"delka seznamu spoju: "<<seznamSpoju.length()<<" indexSpoje:"<<indexSpoje<<" kj:"<<kj;
    this->otevriDB();
    //Spoj docasnySpoj;
    QVector<ZastavkaCil> docasnySeznamZastavek;


    QString queryString2=stahniSeznamSpolecnaCastDotazu();

    //eliminace všech smyček
    // queryString2+=(" AND  x.s2=0 ");


    queryString2+=("WHERE s.s=");
    queryString2+=( QString::number(seznamSpoju.at(indexSpoje).cislo));
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
            Zastavka aktZast;
            ZastavkaCil aktZastCil;
            Linka aktLinka;
            Spoj aktSpoj;
            int cisloZast = pocetZastavek;
            aktZast.StopIndex=cisloZast;
            //qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(pocetZastavek);
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
            aktLinka.isDiversion=query.value(query.record().indexOf("s.vy")).toBool();

            aktSpoj.cisloRopid=query.value(query.record().indexOf("s.c")).toInt();
            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt();
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();

            aktZast.cisloU=query.value(query.record().indexOf("z.u")).toUInt();
            aktZast.cisloZ=query.value(query.record().indexOf("z.z")).toUInt();
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

            aktZast.seznamPasem.append(vyrobPasmaMezikraj(tp,pz,pc,query.value(query.record().indexOf("l.cids")).toString(),query.value(query.record().indexOf("l.tl")).toString()));
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
            aktZast.lng=query.value(query.record().indexOf("z.lng")).toDouble();
            aktZast.lat=query.value(query.record().indexOf("z.lat")).toDouble();
            aktZast.radius=query.value(query.record().indexOf("z.rdisp")).toInt();
            qDebug()<<"radius je: "<<aktZast.radius;


            aktZast.seznamPoznamek=stahniPoznamky(query.value(query.record().indexOf("x.s_id")).toInt(),query.value(query.record().indexOf("x.xorder")).toInt());

            qDebug()<<"pocetPoznamek "<<QString::number(aktZast.seznamPoznamek.count());


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

            aktZastCil.linka=aktLinka;
            aktZastCil.zastavka=aktZast;

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

    Zastavka cilovaZastavka;
    cilovaZastavka=docasnySeznamZastavek.at(docasnySeznamZastavek.length()-1).zastavka;
    if(seznamSpoju.at(indexSpoje).navazujici==true)
    {
        QString novyHorniCil=cilovaZastavka.NameFront+cilovaZastavka.NameFront2;
        cilovaZastavka.NameFront=novyHorniCil;
        cilovaZastavka.NameFront2="a dále jako linka "+seznamSpoju.at(indexSpoje+1).linka.LineName;// interniSeznamZastavek.first().linka.LineName;
        qDebug()<<"obsah spodniho radku "<<cilovaZastavka.NameFront2;
    }


    for (int i=docasnySeznamZastavek.size()-1;i>=0;i--)
    {
        if (docasnySeznamZastavek.at(i).zastavka.zsol==true)
        {
            qDebug()<<"zmena konecne na"<<docasnySeznamZastavek.at(i).zastavka.NameSide;
            cilovaZastavka=docasnySeznamZastavek.at(i).zastavka;
        }

        docasnySeznamZastavek[i].cil=cilovaZastavka;
    }

    seznamSpoju[indexSpoje].globalniSeznamZastavek=docasnySeznamZastavek;

    return 1;
}

QString SqlRopidXmlDotazy::stahniSeznamSpolecnaCastDotazu()
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
    queryString2+=("x.o, x.t, x.na, x.zn, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, x.zsol, x.s1, x.s2, x.s_id, ");
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
void SqlRopidXmlDotazy::vypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek)
{
    qDebug()<< Q_FUNC_INFO;
    for (int i=0;i<pocetZastavek;i++)
    {
        qInfo()<<QString::number(docasnySeznamZastavek[i].zastavka.StopIndex)+"  "+docasnySeznamZastavek[i].zastavka.StopName+" cil:  "+docasnySeznamZastavek[i].cil.StopName+" linka"+docasnySeznamZastavek[i].linka.LineName+"\n";
    }
}



QString SqlRopidXmlDotazy::pasmaDoStringu(QVector<Pasmo> pasma, QString delimiter)
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


QVector<QString> SqlRopidXmlDotazy::stahniPoznamky(int idSpoje, int xorder)
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

int SqlRopidXmlDotazy::najdiTurnusZeSpoje(Spoj spoj,int &kmenovaLinka,int &poradi,int &order, QString kj)
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
    queryString2+=(QString::number(spoj.linka.c));
    queryString2+=(" AND s.c=");
    queryString2+=(QString::number(spoj.cisloRopid));
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

    qDebug()<<"Spoj "<<spoj.linka.c<<"/"<<spoj.cisloRopid<<" spada pod kurz "<<kmenovaLinka<<"/"<<poradi<<" order:"<<order;
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
int SqlRopidXmlDotazy::vytvorSeznamTurnusSpoju(Obeh &docasnyObeh, QString kj)
{
    //QVector<Spoj> &docasnySeznamSpoju,
    qDebug()<< Q_FUNC_INFO;
    docasnyObeh.seznamSpoju.clear();
    this->pripoj();
    QString queryString2("SELECT DISTINCT sp_po.l, sp_po.p, sp_po.kj, sp_po.s, sp_po.pokrac, s.c, s.s, s.l, l.c, l.lc, l.aois FROM sp_po ");
    queryString2+=("LEFT JOIN s ON sp_po.s=s.s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE sp_po.l=");
    queryString2+=( QString::number(docasnyObeh.kmenovaLinka.c));
    //queryString2+=(" AND  s.c !=1000 ");
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND  sp_po.p=");
    queryString2+=( QString::number(docasnyObeh.p));


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

        Spoj docasnySpoj;
        docasnySpoj.cislo=query.value(query.record().indexOf("s.s")).toInt();
        docasnySpoj.cisloRopid=query.value(query.record().indexOf("s.c")).toInt();
        docasnySpoj.linka.c=query.value(query.record().indexOf("s.l")).toInt();
        docasnySpoj.navazujici=query.value(query.record().indexOf("sp_po.pokrac")).toBool();

        QString alias=query.value(query.record().indexOf("l.aois")).toString();
        //  qDebug()<<"alias "<<alias<<" linka.c "<<docasnySpoj.linka.c;
        if(alias.isEmpty())
        {
            docasnySpoj.linka.LineName=QString::number(docasnySpoj.linka.c);
        }
        else
        {
            docasnySpoj.linka.LineName=alias;
        }

        //qDebug()<<"jmeno docasny spoj linky "<<docasnySpoj.linka.LineName;
        docasnyObeh.seznamSpoju.push_back(docasnySpoj);
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


int SqlRopidXmlDotazy::poziceSpojeNaSeznamu(QVector<Spoj> seznamSpoju,Spoj spoj)
{
    qDebug()<< Q_FUNC_INFO;
    qDebug()<<"delka seznamu spoju: "<<seznamSpoju.count();
    for(int i=0;i<seznamSpoju.count();i++)
    {
        if((seznamSpoju.at(i).linka.c==spoj.linka.c)&&(seznamSpoju.at(i).cisloRopid)==spoj.cisloRopid)
        {
            return i;
        }
    }

    return -1;
}


/*!

*/
int SqlRopidXmlDotazy::nactiPlatnost(QDate &platnostOd, QDate &platnostDo)
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
QString SqlRopidXmlDotazy::maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti)
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


QVector<Pasmo> SqlRopidXmlDotazy::vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc,  QString cids,QString tl)
{
    qDebug()<<"SqlPraceRopid::vyrobPasmaMezikraj";
    QVector<Pasmo> vystup;
    Pasmo aktpasmo;
    QStringList povoleneSystemy = cids.split(' ');
    qDebug()<<"nalezeno "<<povoleneSystemy.count()<<" systemu";

    for(int i=0;i<tp.length();i++)
    {
        QVector<Pasmo> pasma= pasmoStringDoVectoru(tp.at(i), pz.at(i),tl);
        if(povoleneSystemy.contains(pc.at(i)))
        {
            vystup.append(pasma);
        }
    }
    return vystup;
}

QVector<Pasmo> SqlRopidXmlDotazy::pasmoStringDoVectoru(QString vstup,QString system,QString tl)
{
    QStringList stringPasma = vstup.split(',');
    QVector<Pasmo> seznamPasem;

    for (int i=0;i<stringPasma.length();i++)
    {
        Pasmo intPasmo;
        intPasmo.nazev=stringPasma.at(i);
        intPasmo.system=system;

        if(intPasmo.nazev!="-")
        {
            if(tl=="A")
            {
                if(intPasmo.nazev=="P")
                {
                    seznamPasem.append(intPasmo);
                }
            }
            else
            {
                if (intPasmo.nazev!="P")
                {
                    seznamPasem.append(intPasmo);
                }
            }
        }
    }
    return seznamPasem;
}


///////////////////////// model view approach

QSqlQueryModel* SqlRopidXmlDotazy::stahniSeznamLinekModel(QString kj)
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

QSqlQueryModel* SqlRopidXmlDotazy::stahniSeznamKmenovychLinekModel(QString kj)
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

QSqlQueryModel* SqlRopidXmlDotazy::stahniSeznamSpojuModel(Linka docasnaLinka, QString kj)
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


QSqlQueryModel* SqlRopidXmlDotazy::stahniSeznamPoradiModel( Linka docasnaLinka, QString kj)
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
QSqlQueryModel* SqlRopidXmlDotazy::stahniSeznamTurnusSpojuModel(Obeh &docasnyObeh, QString kj)
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
    queryString2+=( QString::number(docasnyObeh.kmenovaLinka.c));
    //queryString2+=(" AND  s.c !=1000 ");
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND  sp_po.p=");
    queryString2+=( QString::number(docasnyObeh.p));

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


QVector<MapaBod> SqlRopidXmlDotazy::vytvorTrajektorii(int cisloSpoje, QString kj)
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

double SqlRopidXmlDotazy::absolutniHodnota(double vstup)
{
    if (vstup<0)
    {
        vstup=-vstup;
    }
    return vstup;
}






