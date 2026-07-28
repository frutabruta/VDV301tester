#include "sqlropidxmlqueries.h"
#include <QLoggingCategory>

SqlRopidXmlQueries::SqlRopidXmlQueries()
{
    this->dbOpen();
}

//test Pridani Komentare prechodu na SQLITE



/*!

*/
int SqlRopidXmlQueries::getVehicleRunStops(QVector<Trip> &tripList , int tripIndex, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    qDebug()<<"trip list length: "<<tripList.length()<<" trip index:"<<tripIndex<<" kj:"<<kj;

    if(tripIndex>=tripList.count())
    {
        qDebug()<< "trip index out of range";
        return  0;
    }
    this->dbOpen();

    //Spoj docasnySpoj;
    QVector<StopPointDestination> temporaryTripList;


    QString queryString=createGetTripQueryBase();

    //eliminace všech smyček
    // queryString2+=(" AND  x.s2=0 ");


    queryString+=R"(
    WHERE s.s=:currentTripId
        AND ((x.s2=0) OR (x.xorder=0))
        AND s.kj LIKE :kj
        AND s.d=l.d
        AND z.kj LIKE :kj
        AND z.tu IS NULL
    ORDER BY x.xorder
       )";


    QSqlQuery query =  prepareAndExec(queryString, {
                                                      {":currentTripId", tripList.at(tripIndex).id},
                                                      {":kj",    kj}
                                                  });


    int stopCount=0;
    qDebug().noquote()<<queryString;

    int citacD=0;

    while (query.next())
    {
        citacD++;

        if (query.value(0).toString()!="")
        {
            //bool majak=false;
            bool ignore=false;
            StopPoint stopPoint;
            StopPointDestination stopPointDestination;
            Line line;
            Trip trip;
            int stopIndex = stopCount;
            stopPoint.StopIndex=stopIndex;
            //qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(pocetZastavek);
            QString aois=query.value(query.record().indexOf("l.aois")).toString();
            if (aois!="")
            {
                line.lineName=aois;
            }
            else
            {
                line.lineName=query.value(query.record().indexOf("l.c")).toString();
            }
            line.c=query.value(query.record().indexOf("l.c")).toInt();
            line.lc=query.value(query.record().indexOf("l.lc")).toInt();
            line.lineNumber=query.value(query.record().indexOf("l.lc")).toString();
            line.lineType=query.value(query.record().indexOf("l.tl")).toString();
            line.isNight=query.value(query.record().indexOf("l.noc")).toBool();
            line.isDiversion=query.value(query.record().indexOf("s.vy")).toBool();
            line.kli=query.value(query.record().indexOf("l.kli")).toInt();

            trip.idRopid=query.value(query.record().indexOf("s.c")).toInt();
            trip.id=query.value(query.record().indexOf("s.s")).toInt();
            trip.line=line;

            stopPoint.idCis=query.value( query.record().indexOf("z.cis")).toInt();
            stopPoint.idOis=query.value(query.record().indexOf("z.ois")).toUInt();

            stopPoint.idU=query.value(query.record().indexOf("z.u")).toUInt();
            stopPoint.idZ=query.value(query.record().indexOf("z.z")).toUInt();
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

            stopPoint.fareZoneList.append(createInterRegionFareZones(tp,pz,pc,query.value(query.record().indexOf("l.cids")).toString(),query.value(query.record().indexOf("l.tl")).toString()));
            stopPoint.StopName=query.value(query.record().indexOf("t.ri")).toString();
            stopPoint.platformName=query.value(query.record().indexOf("z.sta")).toString();
            stopPoint.ids ="PID";

            if(line.lineType!="A")
            {
                if(!line.isNight)
                {
                    stopPoint.NameFront=query.value(query.record().indexOf("t.ctn")).toString();
                    stopPoint.NameSide=query.value(query.record().indexOf("t.btn")).toString();
                    stopPoint.NameLcd=query.value(query.record().indexOf("t.lcdn")).toString();
                    stopPoint.NameInner=query.value(query.record().indexOf("t.vtn")).toString();
                }
                else
                {
                    stopPoint.NameFront=query.value(query.record().indexOf("t.ctnnoc")).toString();
                    stopPoint.NameSide=query.value(query.record().indexOf("t.btnnoc")).toString();
                    stopPoint.NameLcd=query.value(query.record().indexOf("t.lcdnnoc")).toString();
                    stopPoint.NameInner=query.value(query.record().indexOf("t.vtnnoc")).toString();
                }
            }
            else
            {
                if(!line.isNight)
                {
                    stopPoint.NameFront=query.value(query.record().indexOf("t.ctm")).toString();
                    stopPoint.NameSide=query.value(query.record().indexOf("t.btm")).toString();
                    stopPoint.NameLcd=query.value(query.record().indexOf("t.lcdm")).toString();
                    stopPoint.NameInner=query.value(query.record().indexOf("t.vtm")).toString();
                }
                else
                {
                    stopPoint.NameFront=query.value(query.record().indexOf("t.ctmnoc")).toString();
                    stopPoint.NameSide=query.value(query.record().indexOf("t.btmnoc")).toString();
                    stopPoint.NameLcd=query.value(query.record().indexOf("t.lcdmnoc")).toString();
                    stopPoint.NameInner=query.value(query.record().indexOf("t.vtmnoc")).toString();
                }
            }

            stopPoint.additionalTextMessage =query.value(query.record().indexOf("t.hl")).toString();

            QString arrivalTime =query.value( query.record().indexOf("x.p")).toString();
            stopPoint.ArrivalTime=arrivalTime;
            QString departureTime =query.value( query.record().indexOf("x.o")).toString();
            stopPoint.DepartureTime=departureTime;
            stopPoint.isViapoint=query.value(query.record().indexOf("x.na")).toBool();
            stopPoint.onRequest =query.value(query.record().indexOf("x.zn")).toBool();
            stopPoint.neozn =query.value(query.record().indexOf("x.neozn")).toBool();
            stopPoint.zast =query.value(query.record().indexOf("x.zast")).toBool();
            stopPoint.transferMetroA =query.value(query.record().indexOf("x.xA")).toBool();
            stopPoint.transferMetroB =query.value(query.record().indexOf("x.xB")).toBool();
            stopPoint.transferMetroC =query.value(query.record().indexOf("x.xC")).toBool();
            stopPoint.transferMetroD =query.value(query.record().indexOf("x.xD")).toBool();
            stopPoint.transferTrain =query.value(query.record().indexOf("x.xVla")).toBool();
            stopPoint.transferAirplane =query.value(query.record().indexOf("x.xLet")).toBool();
            stopPoint.transferFerry =query.value(query.record().indexOf("x.xLod")).toBool();
            stopPoint.zsol=query.value(query.record().indexOf("x.zsol")).toBool();
            stopPoint.lng=query.value(query.record().indexOf("z.lng")).toDouble();
            stopPoint.lat=query.value(query.record().indexOf("z.lat")).toDouble();
            stopPoint.sx=query.value(query.record().indexOf("z.sx")).toDouble();
            stopPoint.sy=query.value(query.record().indexOf("z.sy")).toDouble();
            stopPoint.radius=query.value(query.record().indexOf("z.rdisp")).toInt();
            bool s2=query.value(query.record().indexOf("x.s2")).toBool();
            qDebug()<<"radius is: "<<stopPoint.radius;


            qDebug()<<"note count: "<<QString::number(stopPoint.notesList.count());


            if(  query.value(query.record().indexOf("x.t")).toString() =="Majak")
            {
               // majak=true;
                ignore=true;
            }

            stopPoint.notesList=getNotesFromTripS(query.value(query.record().indexOf("x.s_id")).toInt(),query.value(query.record().indexOf("x.xorder")).toInt());
            stopPoint.stopNoteList=getNotesFromTripSNew(query.value(query.record().indexOf("x.s_id")).toInt(),query.value(query.record().indexOf("x.xorder")).toInt());


            if(stopPoint.additionalTextMessage!="")
            {
                qDebug()<<"additionalVlozeno "<<stopPoint.additionalTextMessage;
            }

            getPolygonFromStopPoint(stopPoint,kj,false);
            getPolygonFromStopPoint(stopPoint,kj,true);

            stopCount++;

            stopPointDestination.line=line;
            stopPointDestination.stopPoint=stopPoint;

            if((citacD!=1)&&(s2==true))
            {
                ignore=true;
            }

            if (ignore==false)
            {
                temporaryTripList.push_back(stopPointDestination);
            }
        }
    }

    stopCount=temporaryTripList.length();
    this->dbClose();
    if (stopCount ==0)
    {

        return 0;
    }

    StopPoint destinationStopPoint;
    destinationStopPoint=temporaryTripList.at(temporaryTripList.length()-1).stopPoint;
    if(tripList.at(tripIndex).continuesWithNextTrip==true)
    {
        if(tripList.length()>(tripIndex+1))
        {
            QString topDestinationName=destinationStopPoint.NameFront+destinationStopPoint.NameFront2;
            destinationStopPoint.NameFront=topDestinationName;
            destinationStopPoint.NameFront2="a dále jako linka "+tripList.at(tripIndex+1).line.lineName;// interniSeznamZastavek.first().linka.LineName;
            qDebug()<<"bottom line content: "<<destinationStopPoint.NameFront2;
        }

    }


    for (int i=temporaryTripList.size()-1;i>=0;i--)
    {
        temporaryTripList[i].destination=destinationStopPoint;
        if (temporaryTripList.at(i).stopPoint.zsol==true)
        {
            qDebug()<<"destination changed to : "<<temporaryTripList.at(i).stopPoint.NameSide;
            destinationStopPoint=temporaryTripList.at(i).stopPoint;
        }


    }

    tripList[tripIndex].globalStopPointDestinationList=temporaryTripList;

    return 1;
}

QString SqlRopidXmlQueries::createGetTripQueryBase()
{
    qDebug()<< Q_FUNC_INFO;

    QString queryString=R"(
        SELECT DISTINCT
        z.n, z.tp, z.tp2, z.tp3, z.cis, z.ois, z.u, z.z, z.lng, z.lat, z.sx, z.sy, z.rdisp, z.sta,
        t.ri,t.hl,
        t.ctn, t.btn, t.lcdn, t.vtn,
        t.ctnnoc, t.btnnoc, t.lcdnnoc, t.vtnnoc,
        t.ctm, t.btm, t.lcdm, t.vtm,
        t.ctmnoc, t.btmnoc, t.lcdmnoc, t.vtmnoc,
        l.c, l.lc, l.tl, l.aois, l.noc, l.cids, l.tl, l.kli,
        x.o, x.p, x.t, x.na, x.zn, x.neozn, x.zast, x.xA, x.xB, x.xC, x.xD, x.xVla, x.xLet, x.xLod, x.xorder, x.zsol, x.s1, x.s2, x.s_id,
        s.ns, s.c, s.vy,
        ids.z AS pz1,
        ids2.z AS pz2,
        ids3.z AS pz3,
        ids.c AS pc1,
        ids2.c AS pc2,
        ids3.c AS pc3
        FROM x
        LEFT JOIN s ON x.s_id=s.s
        LEFT JOIN z ON x.u = z.u AND x.z=z.z
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        LEFT JOIN t ON t.u=x.u AND t.z=x.z
        LEFT JOIN ids ON z.ids=ids.c
        LEFT JOIN ids AS ids2 ON z.ids2=ids2.c
        LEFT JOIN ids AS ids3 ON z.ids3=ids3.c
    )";
    return queryString;
}




QString SqlRopidXmlQueries::fareZoneToString(QVector<FareZone> fareZoneList, QString delimiter)
{
    QString vysledek="";

    if (fareZoneList.count()==0)
    {
        return "";
    }
    for(int i=0; i<fareZoneList.count()-1;i++)
    {
        vysledek+=fareZoneList.at(i).name;
        vysledek+=delimiter;
    }
    vysledek+=fareZoneList.last().name;
    return vysledek;
}


QVector<QString> SqlRopidXmlQueries::getNotesFromTripS(int tripS, int xorder)
{
    qDebug()<< Q_FUNC_INFO;
    //this->dbOpen();
    QVector<QString> noteList;

    QString queryString=R"(
        SELECT x_po.s, x_po.xorder, x_po.po,  po.c, po.t, po.ois
        FROM  x_po
        LEFT JOIN po ON x_po.po=po.c
        WHERE po.t<>""
            AND po.ois=1
            AND  x_po.s=:tripS
            AND x_po.xorder=:xorder
    )";


    QSqlQuery query =  prepareAndExec(queryString, {
                                                      {":tripS", tripS},
                                                      {":xorder",xorder}
                                                  });


    while (query.next())
    {
        int index=query.record().indexOf("po.t");
        qDebug()<<" index: "<<index;
        QString noteText=query.value(query.record().indexOf("po.t")).toString();
        noteList.push_back(noteText);
    }

    return noteList;
}

QVector<StopNote> SqlRopidXmlQueries::getNotesFromTripSNew(int tripS, int xorder)
{
    qDebug()<< Q_FUNC_INFO;
    //this->dbOpen();
    QVector<StopNote> noteList;

    QString queryString=R"(
        SELECT x_po.s, x_po.xorder, x_po.po,  po.c, po.t, po.ois, po.thls, po.tpan, po.kan, po.akce,  po.nahr
        FROM  x_po
        LEFT JOIN po ON x_po.po=po.c
        WHERE po.t<>""
            AND po.ois=1
            AND  x_po.s=:tripS
            AND x_po.xorder=:xorder
    )";

    QSqlQuery query =  prepareAndExec(queryString, {
                                                      {":tripS", tripS},
                                                      {":xorder",xorder}
                                                  });

    while (query.next())
    {
        int index=query.record().indexOf("po.t");
        qDebug()<<" index: "<<index;
        StopNote stopNote;
        stopNote.text=query.value(query.record().indexOf("po.t")).toString();
        stopNote.lcdText=query.value(query.record().indexOf("po.tpan")).toString();
        stopNote.showToDriver=query.value(query.record().indexOf("po.ois")).toBool();
        stopNote.isSpecialAnnouncement=query.value(query.record().indexOf("po.thls")).toBool();
        stopNote.soundName=query.value(query.record().indexOf("po.nahr")).toString();
        stopNote.setActivationFlags(query.value(query.record().indexOf("po.akce")).toInt());
        stopNote.setSpeakerFlags(query.value(query.record().indexOf("po.kan")).toInt());
        noteList.push_back(stopNote);
    }

    return noteList;
}



Trip SqlRopidXmlQueries::getTripDescriptionFromId(int tripId, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    this->dbOpen();
    Trip trip;

    QString  queryString= R"(
        SELECT DISTINCT l.c, l.aois,  l.lc, s.c,s.s, z.n AS Z, zz.n AS DO, substr(time(x.o, 'unixepoch'),1,5) AS start, substr(time(xx.p, 'unixepoch'),1,5) AS konec
        FROM s
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        LEFT JOIN x ON s.s=x.s_id AND x.xorder=0
        LEFT JOIN z ON x.u=z.u AND x.z=z.z
        LEFT JOIN (
            SELECT x.u, x.z, x.s_id, MAX(x.p) AS p, MAX(x.xorder) AS pocet
            FROM (SELECT x.o,x.p,x.s_id,x.xorder, x.u, x.z FROM x WHERE s2=0) AS x
            GROUP BY x.s_id ) AS xx ON xx.s_id=s.s
        LEFT JOIN z AS zz ON xx.u=zz.u AND xx.z=zz.z
        WHERE s.s=:tripId
            AND s.man !=1
            AND s.kj LIKE :kj
            AND z.kj LIKE :kj
        ORDER BY s.c ASC, s.s ASC
    )";


    QSqlQuery query =  prepareAndExec(queryString, {
                                                      {":tripId", tripId},
                                                      {":kj",kj}
                                                  });



    qDebug().noquote()<<queryString;

    while (query.next())
    {
        trip.line.c=query.value(query.record().indexOf("l.c")).toInt();
        trip.line.lineName=query.value(query.record().indexOf("l.aois")).toString();
        trip.line.lc=query.value(query.record().indexOf("l.lc")).toInt();
        trip.line.lineNumber=query.value(query.record().indexOf("l.lc")).toString();

        trip.idRopid=query.value(query.record().indexOf("s.c")).toInt();
        trip.id=query.value(query.record().indexOf("s.s")).toInt();

        StopPointDestination firstStop;
        StopPointDestination lastStop;

        firstStop.stopPoint.NameLcd=query.value(query.record().indexOf("Z")).toString();
        lastStop.stopPoint.NameLcd=query.value(query.record().indexOf("DO")).toString();

        trip.globalStopPointDestinationList.append(firstStop);
        trip.globalStopPointDestinationList.append(lastStop);
    }
    // this->dbClose();


    return trip;
}

int SqlRopidXmlQueries::getVehicleRunFromTripLC(Trip trip, int &rootLine, int &vehicleRun, int &tripIndex, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    this->initialize();

    QString queryString= R"("
        SELECT DISTINCT s.s, s.c, s.kj, l.c,l.lc,l.aois, sp_po.l, sp_po.p, sp_po.ord
        FROM s
        LEFT JOIN sp_po ON sp_po.s=s.s
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        WHERE l.c=:trip_line_c
            AND s.c=:trip_idRopid
            AND  s.man !=1
            AND s.kj LIKE :kj
        ORDER BY s.s
    )";

    QSqlQuery query =  prepareAndExec(queryString, {
                                                        {":trip_line_c", trip.line.c},
                                                        {":trip_idRopid",trip.idRopid},
                                                        {":kj",kj}
                                                  });

    qDebug()<<queryString;
    // qDebug()<<"DebugPointB";
    int resdultCounter=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            resdultCounter++;
            rootLine=query.value(query.record().indexOf("sp_po.l")).toInt();
            vehicleRun=query.value(query.record().indexOf("sp_po.p")).toInt();
            tripIndex=query.value(query.record().indexOf("sp_po.ord")).toInt()-1;
        }
    }

    qDebug()<<"Trip "<<trip.line.c<<"/"<<trip.idRopid<<" belongs to vehicle run: "<<rootLine<<"/"<<vehicleRun<<" index on line:"<<tripIndex;
    this->dbClose();
    if (resdultCounter==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int SqlRopidXmlQueries::getVehicleRunFromTripS(Trip trip, int &rootLine, int &vehicleRun, int &tripIndex, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    this->initialize();

    QString queryString=R"(
        SELECT DISTINCT s.s, s.c, s.kj, l.c,l.lc,l.aois, sp_po.l, sp_po.p, sp_po.ord
        FROM s
        LEFT JOIN sp_po ON sp_po.s=s.s
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        WHERE s.s=:trip_id
            AND  s.man !=1
            AND s.kj LIKE :kj
        ORDER BY s.s
    )";

    QSqlQuery query =  prepareAndExec(queryString, {
                                                    {":trip_id",trip.id},
                                                    {":kj",    kj}
                                                });


    qDebug()<<queryString;
    // qDebug()<<"DebugPointB";
    int resdultCounter=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            resdultCounter++;
            rootLine=query.value(query.record().indexOf("sp_po.l")).toInt();
            vehicleRun=query.value(query.record().indexOf("sp_po.p")).toInt();
            tripIndex=query.value(query.record().indexOf("sp_po.ord")).toInt()-1;
        }
    }

    qDebug()<<"Trip "<<trip.line.c<<"/"<<trip.idRopid<<" belongs to vehicle run: "<<rootLine<<"/"<<vehicleRun<<" index on line:"<<tripIndex;
    this->dbClose();
    if (resdultCounter==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int SqlRopidXmlQueries::getTripSfromC(Trip &trip, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    this->initialize();

    QString queryString=R"(
        SELECT DISTINCT s.s FROM s
        WHERE s.l=:trip_line_c
            AND s.c=:trip_idRopid
            AND s.kj LIKE :kj
        ORDER BY s.c
    )";


    QSqlQuery query =  prepareAndExec(queryString, {
                                                        {":trip_line_c", trip.line.c},
                                                        {":trip_idRopid", trip.idRopid},
                                                        {":kj",    kj}
                                                  });


    qDebug().noquote()<<queryString;

    int counter=0;
    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            counter++;
            trip.id=query.value(query.record().indexOf("s.s")).toInt();
        }
    }

 //   qDebug()<<"Spoj "<<spoj.line.c<<"/"<<spoj.idRopid<<" spada pod kurz "<<kmenovaLinka<<"/"<<poradi<<" order:"<<order;
    this->dbClose();
    if (counter==0)
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
int SqlRopidXmlQueries::getTripListFromVehicleRun(VehicleRun &vehicleRun, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    vehicleRun.tripList.clear();
    this->initialize();
    QString queryString=R"(
        SELECT DISTINCT sp_po.l, sp_po.p, sp_po.kj, sp_po.s, sp_po.pokrac, s.c, s.s, s.l, l.c, l.lc, l.kli, l.aois
        FROM sp_po
        LEFT JOIN s ON sp_po.s=s.s
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        WHERE sp_po.l= :vehicleRun_rootline_c
            AND  (( s.man !=1) OR (s.zvd=12))
            AND  sp_po.p=:vehicleRunOrder
            AND sp_po.kj LIKE :kj
        ORDER BY sp_po.ord
    )";


    QSqlQuery query =  prepareAndExec(queryString, {
                                                      {":vehicleRun_rootline_c", vehicleRun.rootLine.c},
                                                      {":vehicleRunOrder", vehicleRun.order},
                                                      {":kj",    kj}
                                                  });



    qDebug().noquote() << queryString;


    qDebug().noquote() << "SQL:" << query.boundValues();

    int resultCounter=0;
    while (query.next())
    {

        Trip trip;
        trip.id=query.value(query.record().indexOf("s.s")).toInt();
        trip.idRopid=query.value(query.record().indexOf("s.c")).toInt();       
        trip.continuesWithNextTrip=query.value(query.record().indexOf("sp_po.pokrac")).toBool();

        trip.line.c=query.value(query.record().indexOf("s.l")).toInt();
        trip.line.lc=query.value(query.record().indexOf("l.lc")).toInt();
        trip.line.kli=query.value(query.record().indexOf("l.kli")).toInt();

        QString alias=query.value(query.record().indexOf("l.aois")).toString();
        //  qDebug()<<"alias "<<alias<<" linka.c "<<docasnySpoj.linka.c;
        if(alias.isEmpty())
        {
            trip.line.lineName=QString::number(trip.line.c);
        }
        else
        {
            trip.line.lineName=alias;
        }

        //qDebug()<<"jmeno docasny spoj linky "<<docasnySpoj.linka.LineName;
        vehicleRun.tripList.push_back(trip);
        resultCounter++;
        // qDebug()<<docasnySpoj.cisloRopid;
    }

    this->dbClose();
    if (resultCounter==0)
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
int SqlRopidXmlQueries::getDatasetValidity(QDate &dateFrom, QDate &dateTo, QString &ver)
{


    qDebug()<< Q_FUNC_INFO;

    this->initialize();

    QString queryString("SELECT DISTINCT h.od, h.do, h.ver FROM hlavicka AS h ");


    QSqlQuery query=prepareAndExec(queryString);


    int resultCounter=0;
    while (query.next())
    {

        if (query.value(0).toString()!="")
        {
            dateFrom=query.value(query.record().indexOf("od")).toDate();
            dateTo=query.value(query.record().indexOf("do")).toDate();
            ver=query.value(query.record().indexOf("ver")).toString();
            resultCounter++;
        }
    }

    this->dbClose();
    if (resultCounter==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


QString SqlRopidXmlQueries::getTrajectoryType()
{
    qDebug()<< Q_FUNC_INFO;

    this->initialize();

    int wcount=0; //WGS84 coordinates count
    int scount=0; //SJTSK coordinates count

    QString queryString("SELECT COUNT(x) AS scount, COUNT(lat) AS wcount FROM bod ");

    QSqlQuery query =  prepareAndExec(queryString);

    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            scount=query.value(query.record().indexOf("scount")).toInt();
            wcount=query.value(query.record().indexOf("wcount")).toInt();
        }
    }

    this->dbClose();
    if(wcount>0)
    {
        return "WGS84";
    }
    else if(scount>0)
    {
        return "S_JTSK";
    }
    return "N/A";
}


/*!

*/
QString SqlRopidXmlQueries::createValidyMaskFromDate(QDate workingDate, QDate validityStart, QDate validityEnd)
{
    QString result="";

    int numberOfDays=1;

    numberOfDays=-workingDate.daysTo(validityStart);

    if(!isDateInRange(workingDate,validityStart,validityEnd))
    {
        qDebug("date is out of validity range");
        return "x";
    }

    for(int i=0;i<numberOfDays;i++)
    {
        result+="_";
    }
    result+="1%";
    qDebug()<<"datat validity start:"<<validityStart<<" working date: "<<workingDate<<" validity mask: "<<result;
    return result;

}


QVector<FareZone> SqlRopidXmlQueries::createInterRegionFareZones(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc,  QString cids,QString tl)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> output;
    FareZone fareZone;
    QStringList allowedSystems = cids.split(' ');
    qDebug()<<"found this many systems: "<<allowedSystems.count();

    for(int i=0;i<tp.length();i++)
    {
        QVector<FareZone> fareZoneList= fareZoneListStringToVector(tp.at(i), pz.at(i),tl);
        if(allowedSystems.contains(pc.at(i)))
        {
            output.append(fareZoneList);
        }
    }
    return output;
}

QVector<FareZone> SqlRopidXmlQueries::fareZoneListStringToVector(QString inputText,QString system,QString tl)
{
    QStringList stringList = inputText.split(',');
    QVector<FareZone> fareZoneList;

    for (int i=0;i<stringList.length();i++)
    {
        FareZone fareZone;
        fareZone.name=stringList.at(i);
        fareZone.system=system;

        if(fareZone.name!="-")
        {
            if(tl=="A")
            {
                if(fareZone.name=="P")
                {
                    fareZoneList.append(fareZone);
                }
            }
            else
            {
                if (fareZone.name!="P")
                {
                    fareZoneList.append(fareZone);
                }
            }
        }
    }
    return fareZoneList;
}


///////////////////////// model view approach

QSqlQueryModel* SqlRopidXmlQueries::getLineListModel(QString kj)
{
    QSqlQuery query = prepareAndExec(
        "SELECT DISTINCT l.c FROM l WHERE l.kj LIKE :kj ORDER BY l.c;",
        {{":kj", kj}}
        );
    if (!query.isActive()) return nullptr;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* SqlRopidXmlQueries::getRootLineListModel(QString kj)
{
    qDebug() << Q_FUNC_INFO;

    QString queryString= R"(
        SELECT DISTINCT o.l, l.c, l.n
        FROM o
        LEFT JOIN l ON o.l = l.c
        WHERE o.kj LIKE :kj
        AND l.c IS NOT NULL
        ORDER BY l.c;
    )";

    return queryModelWrapper(
        queryString,
        {{":kj", kj}}
        );
}

/*
QSqlQueryModel* SqlRopidXmlQueries::stahniSeznamSpojuModel(Line line, QString kj)
{
    qDebug() <<  Q_FUNC_INFO;

    QString queryString2("SELECT DISTINCT s.s, s.c, s.kj, l.c,l.aois FROM s ");
    queryString2+=("LEFT JOIN l ON s.l=l.c  AND s.d=l.d ");
    queryString2+=("WHERE l.c=");
    queryString2+=( QString::number(line.c));
    queryString2+=(" AND  s.man !=1 ");
    queryString2+=(" AND s.kj LIKE '");
    queryString2+=(kj);
    queryString2+=("' ");
    queryString2+=(" ORDER BY s.c");

    QSqlQueryModel *model= new QSqlTableModel(this) ;
    model->setQuery(queryString2);

    return model;
}
*/

QSqlQueryModel* SqlRopidXmlQueries::getVehicleRunListModel(Line line, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    this->initialize();
    qInfo()<<"DebugPointA";
    QString queryString=R"(
    SELECT DISTINCT o.l, o.p
    FROM o
    WHERE o.l= :lineC
    AND o.kj LIKE :kj
    ORDER BY o.p
    )";

    qDebug()<<line.c;

    return queryModelWrapper(
        queryString,
        {
            {":lineC",line.c},
            {":kj", kj}
        });
}



/*!
    modified version to support additional information
*/
QSqlQueryModel* SqlRopidXmlQueries::getTripListFromVehicleRunModel(VehicleRun &vehicleRun, QString kj)
{
    qDebug()<< Q_FUNC_INFO;

    if (!this->initialize())
    {
        qDebug() << "DB connect failed";
        return nullptr;
    }

    QString queryString=R"(
        SELECT DISTINCT l.c, s.c, substr(time(x.o, 'unixepoch'),1,5) AS start, z.n AS Z, substr(time(xx.p, 'unixepoch'),1,5) AS konec,  zz.n AS DO, s.s,  l.lc
        FROM sp_po
        LEFT JOIN s ON sp_po.s=s.s
        LEFT JOIN l ON s.l=l.c  AND s.d=l.d
        LEFT JOIN x ON s.s=x.s_id AND x.xorder=0
        LEFT JOIN z ON x.u=z.u AND x.z=z.z
        LEFT JOIN (
        SELECT x.u, x.z, x.s_id, MAX(x.p) AS p, MAX(x.xorder) AS pocet
        FROM (SELECT x.o,x.p,x.s_id,x.xorder, x.u, x.z FROM x WHERE s2=0) AS x
        GROUP BY x.s_id ) AS xx
        ON xx.s_id=s.s
        LEFT JOIN z AS zz ON xx.u=zz.u AND xx.z=zz.z

        WHERE sp_po.l = :vehicleRun_rootLine_c
            AND  ((s.man !=1) OR (s.zvd=12))
            AND  sp_po.p=:vehicleRun_order
            AND sp_po.kj LIKE :kj
            ORDER BY sp_po.ord
        )";


    return queryModelWrapper(
        queryString,
        {
            {":vehicleRun_rootLine_c", vehicleRun.rootLine.c},
            {":vehicleRun_order",      vehicleRun.order},
            {":kj", kj}
        });
}


//mapa


QVector<MapaBod> SqlRopidXmlQueries::getTrajectoryFromTripS(int tripS, QString kj)
{
    qDebug()<< Q_FUNC_INFO;
    //QVector<Spoj> &docasnySeznamSpoju,
    QVector<MapaBod> result;


    this->initialize();

    QString queryString="";

    queryString+= R"(
        SELECT DISTINCT
        bod.u1, bod.u2, bod.z1, bod.z2, bod.poradi, x2.u, x2.z, x.id, bod.x, bod.y, bod.lat, bod.lon,
        z.n, z.cis, z.ois,
        l.c, l.lc, l.tl,
        x.t, x.xorder, x.zsol, x.s1, x.s2, x.s_id,
        s.ns, s.c, s.vy, x.ROWID, x2.ROWID

        FROM (
            SELECT x.z, x.id, x.ROWID, x.t, x.xorder, x.zsol, x.s1,x.s2, x.s_id, x.u , ROW_NUMBER() OVER (ORDER BY x.ROWID) AS row_number
            FROM x
            WHERE x.t IS NULL
            ) AS x
        LEFT JOIN s ON x.s_id=s.s
        LEFT JOIN (
            SELECT x.z, x.id, x.ROWID, x.t, x.xorder, x.zsol, x.s1,x.s2, x.s_id, x.u , x.var, ROW_NUMBER() OVER (ORDER BY x.ROWID) AS row_number
            FROM x
            WHERE x.t IS NULL
            ) AS x2 ON x.row_number+1=(x2.row_number)
        LEFT JOIN z ON x.u = z.u AND x.z=z.z AND z.kj LIKE :kj
        LEFT JOIN l ON s.l=l.c
        LEFT JOIN t ON t.u=x.u AND t.z=x.z
        LEFT JOIN bod ON bod.u1=x.u AND bod.z1=x.z AND bod.u2=x2.u AND bod.z2=x2.z AND bod.var=x2.var AND bod.kj LIKE :kj
        WHERE s.s=:tripS
            AND  s.kj LIKE :kj  AND s.d=l.d
        ORDER BY x.xorder, bod.poradi
    )";


    QSqlQuery query=prepareAndExec(queryString,
                                    {
                                        {":kj", kj},
                                        {":tripS",tripS}
                                    }
                                     );


    while (query.next())
    {
        MapaBod bod;

        QString u1=query.value(query.record().indexOf("bod.u1")).toString();
        QString z1=query.value(query.record().indexOf("bod.z1")).toString();

        QString u2=query.value(query.record().indexOf("bod.u2")).toString();
        QString z2=query.value(query.record().indexOf("bod.z2")).toString();

        //bod.radius =query.value( query.record().indexOf("z.rdisp")).toInt();


        //bod.x=absoluteValue(query.value( query.record().indexOf("bod.x")).toDouble());
        //bod.y=absoluteValue(query.value( query.record().indexOf("bod.y")).toDouble());

        bod.x=query.value( query.record().indexOf("bod.x")).toDouble();
        bod.y=query.value( query.record().indexOf("bod.y")).toDouble();

        int poradi=query.value( query.record().indexOf("bod.poradi")).toInt();
        if(poradi==0)
        {
            bod.isStop=true;
        }


        bod.lat=absoluteValue(query.value( query.record().indexOf("bod.lat")).toDouble());
        bod.lng=absoluteValue(query.value( query.record().indexOf("bod.lon")).toDouble());

        QString obsah="";
        obsah+="u1: "+u1+" ";
        obsah+="z1: "+z1+" ";
        obsah+="u2: "+u2+" ";
        obsah+="z2: "+z2+" ";
        bod.obsah=obsah;

        if((bod.x!=0.0)&&(bod.y!=0.0))
        {
            result.push_back(bod);
        }
        else if((bod.lng!=0.0)&&(bod.lat!=0.0))
        {
            result.push_back(bod);
        }
        else
        {
            qDebug()<<"invalid coordinates";
        }


        // qDebug()<<docasnySpoj.cisloRopid;
    }



    this->dbClose();

    return result;
}

double SqlRopidXmlQueries::absoluteValue(double input)
{
    if (input<0)
    {
        input=-input;
    }
    return input;
}



QSqlQueryModel* SqlRopidXmlQueries::getLineStopListModel(Line line, QString kj)
{
    qDebug() << Q_FUNC_INFO;

    QString queryString;
    queryString += R"(
    SELECT DISTINCT s.c, z.n AS Z, zz.n AS DO,
    substr(time(x.o, 'unixepoch'),1,5) AS start,
    substr(time(xx.p, 'unixepoch'),1,5) AS konec,
    s.s, l.c, l.lc
    FROM s
    LEFT JOIN l ON s.l=l.c AND s.d=l.d
    LEFT JOIN x ON s.s=x.s_id AND x.xorder=0
    LEFT JOIN z ON x.u=z.u AND x.z=z.z
    LEFT JOIN (
        SELECT x.u, x.z, x.s_id, MAX(x.p) AS p, MAX(x.xorder) AS pocet
        FROM (SELECT x.o,x.p,x.s_id,x.xorder,x.u,x.z FROM x WHERE s2=0) AS x
        GROUP BY x.s_id
    ) AS xx ON xx.s_id=s.s
    LEFT JOIN z AS zz ON xx.u=zz.u AND xx.z=zz.z
    WHERE l.c=:lineC AND s.man != 1 AND s.kj LIKE :kj
    ORDER BY s.c ASC, s.s ASC;
    )";

   return queryModelWrapper(queryString, {
                                              {":lineC", line.c},
                                              {":kj",    kj}
                                          });
}


QSqlQueryModel* SqlRopidXmlQueries::queryModelWrapper(const QString &queryString,
                                                      const QVariantMap &bindings)
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query = prepareAndExec(queryString, bindings);

    if (!query.isActive())
        return nullptr;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(std::move(query));

    while (model->canFetchMore())
    {
        model->fetchMore();
    }

    qDebug()<<"model count "<<model->rowCount();

    return model;
}



bool SqlRopidXmlQueries::getPolygonFromStopPoint(StopPoint &stopPoint, QString kj, bool out)
{
    qDebug()<< Q_FUNC_INFO;
    //qDebug()<<" idSpoje:"<<idSpoje<<" kj:"<<kj;
    this->dbOpen();

    QPolygonF temporaryPolygon;


    //table name cannot be used in binding values
    QString queryString=R"(
    SELECT *
    FROM bod_polygon
    WHERE u=:stopPointIdU
    AND z=:stopPointIdZ
    AND  kj LIKE :kj
    ORDER BY poradi
    )";


    if(out)
    {
        queryString=R"(
        SELECT *
        FROM bod_polygon_out
        WHERE u=:stopPointIdU
        AND z=:stopPointIdZ
        AND  kj LIKE :kj
        ORDER BY poradi
    )";

    }



    QSqlQuery query = prepareAndExec(queryString, {
                                            {":stopPointIdU", stopPoint.idU},
                                            {":stopPointIdZ", stopPoint.idZ},
                                            {":kj",    kj}
                                          });


    while (query.next())
    {
        if (query.value(0).toString()!="")
        {
            double lat=0.0;
            double lng=0.0;

            lat=query.value(query.record().indexOf("lat")).toDouble();
            lng=query.value(query.record().indexOf("lon")).toDouble();

            if(out)
            {
                stopPoint.polygonWgs84_out.append(QPointF(lng,lat));
            }
            else
            {
                stopPoint.polygonWgs84.append(QPointF(lng,lat));
            }
        }
    }

    if(out)
    {
        if(stopPoint.polygonWgs84_out.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if(stopPoint.polygonWgs84.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}

