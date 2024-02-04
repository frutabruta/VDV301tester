#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>




//MAIN



//koment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    konfigurace(QCoreApplication::applicationDirPath()),
    settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat),
    golemio(""), //klic do golemia
    logfile(QCoreApplication::applicationDirPath()),
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",47477,"1.0"), //47477
    customerInformationService1_0("CustomerInformationService","_ibisip_http._tcp",47479,"1.0"),
    customerInformationService2_2CZ1_0("CustomerInformationService","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    customerInformationService2_3("CustomerInformationService","_ibisip_http._tcp",47481,"2.3"),
    //customerInformationService2_2CZ1_0("CustomerInformationService (2)","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    ticketValidationService2_3CZ1_0("TicketValidationService","_ibisip_http._tcp",47483,"2.2CZ1.0"),
    //deviceManagementServiceSubscriber("DeviceManagementService","DeviceStatus","2.2CZ1.0","_ibisip_http._tcp",48477),//puvodni port 48479, novy 59631
    devMgmtSubscriber("DeviceManagementService","DeviceStatus","1.0","_ibisip_http._tcp",48477),

    ui(new Ui::MainWindow)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->setupUi(this);

    ui->pushButton_menu_jizda->setEnabled(false);
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );
    ui->tabWidget_hlavni->setCurrentWidget(ui->tab_palPC);
    ui->pushButton_menu_turnus->setChecked(true);
    ui->pushButton_nast_nactiXMLropid->setDisabled(true);

    vektorCis.push_back(&customerInformationService1_0);
    vektorCis.push_back(&customerInformationService2_2CZ1_0);
    vektorCis.push_back(&customerInformationService2_3);

    //QString konstantaPocetDni=settings.value("konstanty/pocetDni").toString();
    //settings.setValue("golemio/api-key","XXX");

    mapaVykresleni.setCestaMapa(QCoreApplication::applicationDirPath());




    //settings.setValue("General/language","en");
    QString jazyk=settings.value("app/language").toString();

    qDebug()<<" novy jazyk:"<<jazyk;
    retranslateUi(jazyk);


    natahniKonstanty();

    //ui->stackedWidget_palPc->setWindowState(Qt::WindowFullScreen);


    //inicializace databaze
    inicializaceVyberovychPoli();

    //propojeni vsech slotu
    vsechnyConnecty();

    on_pushButton_nactiDetekce_clicked();


    nastartujVsechnyVdv301Sluzby();
    nastartujSluzbuZeZasobniku(vektorCis);




    //vyplneni polozky build pro rozliseni zkompilovanych verzi
    //QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);



    //kalendarJizd
    pracovniDatumPrvniDenDat();

    //cesty souboru
    hlasic.zmenUmisteniProgramu(umisteniProgramu);
    konfigurace.vytvorDefaultniKonfiguraci();
    konfigurace.otevriSoubor();

    MainWindowPomocne::naplnTabulkuHlaseni(ui->tableWidget_oznameni,konfigurace.specialniHlaseni);

    //hlasic.nastavCestu(konfigurace.cestaHlaseni);

    logfile.defaultniLog(souborLogu);
    logfile.novySoubor(souborLogu);
    logfile.pridejNaKonecSouboru(souborLogu,QDateTime::currentDateTime().toString()+" program spuštěn");


    //zobrazeni
    nastavLabelCestyXml();
    ui->statusBar->showMessage("test");

    //inicializace timeru
    timerTrvaniZmenyPasma.setSingleShot(true);
    timerTrvaniZmenyPasma.setInterval(konfigurace.trvaniZobrazeniPasma);

    timerSpecialniOznameniSmazat.setSingleShot(true);
    timerSpecialniOznameniSmazat.setInterval(konfigurace.trvaniZobrazeniOznameni);

    timerStahniPrestupy.setInterval(konfigurace.intervalStahovaniPrestupu);

    timerAfterStopToBetweenStop.setSingleShot(true);
    timerAfterStopToBetweenStop.setInterval(konfigurace.intervalAfterStopToBetweenStop);

}


MainWindow::~MainWindow()
{
    delete proxyModel;
    delete ui;
}

void MainWindow::retranslateUi(QString language)
{
    QTranslator translator;

    qApp->removeTranslator(&translator);
    if(translator.load(":/lang_"+language+".qm"))
    {
        qApp->installTranslator(&translator);
        ui->calendarWidget->setLocale(QLocale::English);
        qDebug()<<"zmena jazyka";
        ui->retranslateUi(this);
    }
    else
    {
        popUpMessage(tr("language file not found"));
    }
}


void MainWindow::nastartujSluzbuZeZasobniku(QVector<CustomerInformationService*> &seznamSluzeb)
{
    if(!seznamSluzeb.isEmpty())
    {
        CustomerInformationService* aktualniSluzba=seznamSluzeb.takeFirst();
        qDebug()<<"v zasobniku zustava sluzeb: "<<seznamSluzeb.count();
        qDebug()<<Q_FUNC_INFO<<" "<<aktualniSluzba->mServiceName<<" "<<aktualniSluzba->globalVersion;
        aktualniSluzba->slotStartServer();
    }
}

void MainWindow::slotSluzbaVratilaVysledekStartu(QString nastartovanaSluzba)
{
    qDebug()<<Q_FUNC_INFO<<" "<<nastartovanaSluzba;
    nastartujSluzbuZeZasobniku(vektorCis);

}

void MainWindow::natahniKonstanty()
{
    qDebug()<<Q_FUNC_INFO;


    if(settings.value("golemio/adresa").isNull())
    {
        eventPoznamkaRidici("konfiguracni soubor neexistuje/je vadny");
    }
    else
    {
        qDebug()<<"konfiguracni soubor nacten";
    }
    qDebug()<<" konstanty status "<<settings.status();


    if(settings.value("golemio/datovyZdroj").toString()=="mpvnet")
    {
        pouzitGolemio=false;
    }
    golemio.setKlic(settings.value("golemio/apiKey").toByteArray());
    golemio.setAdresa(settings.value("golemio/adresa").toString());


    ui->label_build->setText(textVerze());
    ui->label_build->setTextInteractionFlags(Qt::TextSelectableByMouse);

    golemio.setParametry(settings.value("golemio/parametry").toString());

    deviceManagementService1_0.setDeviceName(settings.value("deviceManagementService1_0/deviceName").toString());
    deviceManagementService1_0.setDeviceManufacturer(settings.value("deviceManagementService1_0/deviceManufacturer").toString());
    deviceManagementService1_0.setDeviceSerialNumber(settings.value("deviceManagementService1_0/deviceSerialNumber").toString());
    deviceManagementService1_0.setDeviceClass(settings.value("deviceManagementService1_0/deviceClass").toString());
    deviceManagementService1_0.setDeviceId(settings.value("deviceManagementService1_0/deviceId").toString());
    deviceManagementService1_0.setSwVersion(textVerze());
    deviceManagementService1_0.slotDataUpdate();

    deviceManagementService1_0.setPortNumber(settings.value("deviceManagementService1_0/port").toInt() ); //47477
    customerInformationService1_0.setPortNumber(settings.value("customerInformationService1_0/port").toInt() );
    customerInformationService2_2CZ1_0.setPortNumber(settings.value("customerInformationService2_2CZ1_0/port").toInt() );
    customerInformationService2_3.setPortNumber(settings.value("customerInformationService2_3/port").toInt() );

}



/*!
přesunutí connectů pro větší přehlednost
*/
void MainWindow::vsechnyConnecty()
{
    qDebug()<<Q_FUNC_INFO;

    this->vypisSubscribery1_0(customerInformationService1_0.subscriberList);
    this->vypisSubscribery2_2CZ(customerInformationService2_2CZ1_0.subscriberList);


    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::vypisSubscribery1_0);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::vypisSubscribery2_2CZ);
    connect(&customerInformationService2_3,&HttpService::signalDumpSubscriberList,this,&MainWindow::vypisSubscribery2_3);



    connect(&customerInformationService1_0,&HttpService::signalServicePublished,this,&MainWindow::slotSluzbaVratilaVysledekStartu);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalServicePublished,this,&MainWindow::slotSluzbaVratilaVysledekStartu);
    connect(&customerInformationService2_3,&HttpService::signalServicePublished,this,&MainWindow::slotSluzbaVratilaVysledekStartu);


    connect(&xmlMpvParser,&XmlMpvParser::stazeniHotovo,this,&MainWindow::slotMpvNetReady);
    connect(&golemio,&Golemio::stazeniHotovo,this,&MainWindow::slotGolemioReady);

    //vypis deviceMAnagementServices publisheru
    // connect(&deviceManagementServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::slotXmlDoPromenne);


    //connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::aktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);
    connect(&devMgmtSubscriber,&IbisIpSubscriber::signalUpdateDeviceList,this,&MainWindow::slotAktualizaceTabulkySluzeb);


    //connect(deviceManagementServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    // connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);

    //vypis stavu testu
    connect(&vzorovyTest,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);
    connect(&testOdberuServer,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);

    //jednotliveTesty
    connect(&testOdberuServer,&TestOdberuServer::signalVymazSeznamOdberatelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotRemoveAllSubscribers);
    connect(&testOdberuServer,&TestOdberuServer::signalNastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStartDnsSd);
    connect(&testOdberuServer,&TestOdberuServer::signalZastavCisTimer,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStopTimer);
    connect(&testOdberuServer,&TestOdberuServer::signalOdesliDataDoPanelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotSendDataToSubscribers);


    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalDumpSubscriberList,&testOdberuServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalReplyToPostReceived,&testOdberuServer,&TestOdberuServer::slotVypisOdpovedServeru);

    //vypinani sluzeb pomoci prepinacu
    connect(ui->radioButton_ON1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpService::slotStop);

    connect(ui->radioButton_ON2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpService::slotStop);

    connect(ui->radioButton_ON3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpService::slotStop);

    connect(ui->radioButton_ON4,&QRadioButton::clicked,&customerInformationService1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF4,&QRadioButton::clicked,&customerInformationService1_0,&HttpService::slotStop);

    //vypisovani stavovych hlasek do stavoveho radku vespod okna
    connect(&sqlPraceRopid,&SqlRopidXmlDotazy::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(&sqlPraceRopid,&SqlRopidXmlDotazy::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);

    //  connect(&xmlRopidImportStream,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);

    // connect(this,&MainWindow::signalZahajImport, &xmlRopidImportStream,&XmlRopidImportStream::slotOtevriSoubor);

    //prepinani stavu radio prepinacu podle stavu sluzeb
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalStav,this,&MainWindow::radio1);
    connect(&deviceManagementService1_0,&HttpService::signalStav,this,&MainWindow::radio2);
    connect(&ticketValidationService2_3CZ1_0,&HttpService::signalStav,this,&MainWindow::radio3);
    connect(&customerInformationService1_0,&HttpService::signalStav,this,&MainWindow::radio4);

    //konfigurace
    connect(&konfigurace,&Konfigurace::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);

    //casovace
    connect(&timerTrvaniZmenyPasma,&QTimer::timeout,this,&MainWindow::eventSkryjZmenuTarifnihoPasma);
    connect(&timerAfterStopToBetweenStop,&QTimer::timeout,this,&MainWindow::eventAfterStopToBetweenStop);
    connect(&timerStahniPrestupy,&QTimer::timeout,this,&MainWindow::slotStahniPrestupyAktZastavky);
    connect(&timerSpecialniOznameniSmazat,&QTimer::timeout,this,&MainWindow::slotVymazatSpecialniOznameni);
}



/*!

*/
void MainWindow::testNaplnOkno(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        vzorovyTest.emitujUpdate();
        break;
    case 1:
        testOdberuServer.emitujUpdate();
        break;
    default:
        break;
    }
}



/*!
start vzorového testu
*/
void MainWindow::testStart(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        vzorovyTest.start();
        break;
    case 1:
        testOdberuServer.start();
        break;
    default:
        qDebug()<<"test s indexem "<<QString::number(index)<<" neexistuje";
        break;
    }
}


/*!

*/
void MainWindow::testStop(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        vzorovyTest.stop();
        break;
    case 1:
        testOdberuServer.stop();
        break;
    default:
        qDebug()<<"test s indexem "<<QString::number(index)<<" neexistuje";
        break;
    }
}


/*!

*/
void MainWindow::nastartujVsechnyVdv301Sluzby()
{
    qDebug() <<  Q_FUNC_INFO;
    deviceManagementService1_0.slotStartServer();
    /*
    customerInformationService1_0.slotStartServer();
    customerInformationService2_2CZ1_0.slotStartServer();
    customerInformationService2_4.slotStartServer();
    */
    ticketValidationService2_3CZ1_0.slotStartServer();
}


/*!

*/
void MainWindow::xmlVdv301HromadnyUpdate()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug()<<"delka seznamu tripu "<<stavSystemu.currentVehicleRun.tripList.length();
    if (stavSystemu.currentVehicleRun.tripList.isEmpty())
    {
        qDebug()<<"seznam tripu je prazdny";
        return;
    }
    //QDomDocument vstupniDomXmlPrestupy;
    if (stavSystemu.showConnections==true)
    {
        slotStahniPrestupyAktZastavky();
        timerStahniPrestupy.start();
    }
    else
    {
        timerStahniPrestupy.stop();
    }

    QVector<Connection> prestupy;

    cisAktualizaceObsahu(prestupy,stavSystemu);

    ticketValidationService2_3CZ1_0.updateServiceContent(prestupy,stavSystemu);
    deviceManagementService1_0.serviceContentUpdate();
}

void MainWindow::slotStahniPrestupyAktZastavky()
{
    qDebug() <<  Q_FUNC_INFO;
    StopPoint aktZastavka=stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint;
    if(pouzitGolemio)
    {
        golemio.stahniMpvXml(aktZastavka.idCis, aktZastavka.ids);
    }
    else
    {
        xmlMpvParser.stahniMpvXml(aktZastavka.idCis, aktZastavka.ids);
    }


}


/*!

*/
void MainWindow::slotMpvNetReady()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    xmlMpvParser.naplnVstupDokument(xmlMpvParser.stazenaData);
    QVector<ConnectionMPV> prestupyMpv=xmlMpvParser.parsujDomDokument();
    if(filtrovatPrestupy)
    {
        prestupyMpv=xmlMpvParser.vyfiltrujPrestupy(prestupyMpv,stavSystemu.currentLine);
    }
    QVector<Connection> prestupy;
    foreach(auto polozka, prestupyMpv)
    {
        prestupy.push_back(polozka.toConnection());
    }


    cisAktualizaceObsahu(prestupy,stavSystemu);
}

void MainWindow::slotGolemioReady()
{
    qDebug() <<  Q_FUNC_INFO;
    //qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    golemio.naplnVstupDokument(golemio.stazenaData);
    QVector<ConnectionGolemio> prestupyGolemio=golemio.parsujDomDokument();

    qDebug()<<"bum10";

    QVector<Connection> prestupy;
    foreach(ConnectionGolemio polozka,prestupyGolemio)
    {
        prestupy.push_back(polozka.toConnection());
    }
    qDebug()<<"bum11";
    if(filtrovatPrestupy)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }
    qDebug()<<"pocet Prestupu ve vektoru: "<<prestupy.count();

    cisAktualizaceObsahu(prestupy,stavSystemu);

}


void MainWindow::cisAktualizaceObsahu(QVector<Connection> prestupy, VehicleState mStavSystemu )
{
    customerInformationService1_0.updateServiceContent(prestupy,mStavSystemu );
    customerInformationService2_2CZ1_0.updateServiceContent(prestupy,mStavSystemu);
    customerInformationService2_3.updateServiceContent(prestupy,mStavSystemu);
}


/*!

*/
int MainWindow::on_pushButton_prikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.reset();
    stavSystemu.doorState="AllDoorsClosed";


    /*
     * odeslani spoje doplneneho na turnus
*/

    stavSystemu.currentTrip.line.c =ui->polelinky->text().toInt();
    stavSystemu.currentTrip.idRopid=ui->polespoje->text().toInt();

    int kmenovaLinka=0;;
    int poradi=0;
    int order=0;
    sqlPraceRopid.najdiTurnusZeSpoje( stavSystemu.currentTrip,kmenovaLinka,poradi,order, this->vyrobMaskuKalendareJizd() );

    stavSystemu.currentStopIndex0=0;

    ui->poleLinkyTurnus->setText(QString::number(kmenovaLinka));
    stavSystemu.currentVehicleRun.rootLine.c=kmenovaLinka;


    /*
    if (sqlPraceRopid.vytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd() )==1)
    {
        naplnVyberPoradi(seznamObehu);
    }
    */


    stavSystemu.currentVehicleRun.order=poradi ;
    if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.currentVehicleRun,this->vyrobMaskuKalendareJizd())==1)
    {
        // naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
    }


    Trip hledanySpoj=stavSystemu.currentTrip;
    stavSystemu.currentTripIndex=sqlPraceRopid.poziceSpojeNaSeznamu(stavSystemu.currentVehicleRun.tripList,hledanySpoj);

    if(! MainWindowPomocne::jeVRozsahu(stavSystemu.currentTripIndex,stavSystemu.currentVehicleRun.tripList.size(),Q_FUNC_INFO))
    {
        return 0;
    }

    stavSystemu.currentTrip=stavSystemu.currentVehicleRun.tripList.at(stavSystemu.currentTripIndex);
    ui->poleLinkyTurnus->setText(QString::number(stavSystemu.currentTrip.line.c));
    ui->poleSpojeTurnus->setText(QString::number(stavSystemu.currentTrip.idRopid));
    stavSystemu.currentLine.lineNumber =ui->poleLinkyTurnus->text();

    stavSystemu.currentStopIndex0=0;

    int vysledek=natahniSeznamSpojeKomplet();
    if (vysledek==1)
    {
        eventVstupDoVydeje();
    }
    return vysledek;
}


/*!

*/
int MainWindow::on_pushButton_turnus_prikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.currentLine.lineNumber =ui->poleLinkyTurnus->text();

    stavSystemu.currentStopIndex0=0;

    return natahniSeznamSpojeKomplet();
}

/*!
 * \brief MainWindow::natahniSeznamSpojeKomplet
 * \return
 */
int MainWindow::natahniSeznamSpojeKomplet()
{
    qDebug() <<  Q_FUNC_INFO;
    QString textDoPole="";
    int vysledek=0;
    Trip iterSpoj;

    if((ui->tableView_turnusSpoj->model()->rowCount()==0)&&(ui->tableView_connection->model()->rowCount()==0))
    {
        qDebug()<<"neni zvoleny spoj";
        this->vypisDiagnostika("není zvoleno pořadí");
        return 0;
    }
    else
    {
        qDebug()<<"zjisteni zvolene pozice v seznamu"<<stavSystemu.currentTripIndex;
        if (stavSystemu.currentTripIndex<0)
        {
            this->vypisDiagnostika("není zvolený spoj");
            return 0;
        }
    }


    vysledek=sqlPraceRopid.stahniSeznamCelySpojTurnus(stavSystemu.currentVehicleRun.tripList,stavSystemu.currentTripIndex,this->vyrobMaskuKalendareJizd());
    qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    if (stavSystemu.getCurrentTrip().continuesWithNextTrip==true)
    {
        vysledek=sqlPraceRopid.stahniSeznamCelySpojTurnus(stavSystemu.currentVehicleRun.tripList,stavSystemu.currentTripIndex+1,this->vyrobMaskuKalendareJizd());
        qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    }

    qDebug()<<"je nacteno "<<stavSystemu.currentVehicleRun.tripList.length()<<" spoju";

    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }

    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        return 0;

    }
    xmlVdv301HromadnyUpdate();
    if(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        aktualizaceDispleje();
        stavSystemu.locationState="AtStop";
        ui->pushButton_menu_jizda->setChecked(1);
        ui->stackedWidget_palPc->setCurrentWidget(ui->page_jizda);
        eventVstupDoVydeje();
        // mapaVykresleni.vypisGpsDoHtml(stavSystemu.getCurrentTrip().globalniSeznamZastavek,true,true,true,MapaVykresleni::WGS84);
    }
    return 1;
}




/*!

*/
void MainWindow::on_pushButton_jizda_sipkaDal_clicked()
{
    qDebug() <<  Q_FUNC_INFO;


    if (stavSystemu.currentStopIndex0<(this->stavSystemu.countCurrentTripStops()))
    {
        if((stavSystemu.locationState=="AtStop")&&((stavSystemu.currentStopIndex0<(stavSystemu.countCurrentTripStops()-1) )))
        {
            stavSystemu.locationState="AfterStop";
            stavSystemu.currentStopIndex0++;
            eventOdjezd();
        }
        else
        {
            qDebug()<<"dalsi? index:"<<stavSystemu.currentStopIndex0<<" pocetZastavek:"<<stavSystemu.countCurrentTripStops();
            if((stavSystemu.locationState=="AtStop")&&((stavSystemu.currentStopIndex0+1)==stavSystemu.countCurrentTripStops()))
            {
                this->dalsiSpoj();
            }


            if(stavSystemu.locationState=="BeforeStop")
            {
                stavSystemu.locationState="AtStop";

                eventPrijezd();
            }

            if(stavSystemu.locationState=="BetweenStop")
            {
                stavSystemu.locationState="BeforeStop";
            }

            if(stavSystemu.locationState=="AfterStop")
            {
                stavSystemu.locationState="BetweenStop";
                eventAfterStopToBetweenStop();
            }
        }
    }


    aktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";
    // ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0+1));
    xmlVdv301HromadnyUpdate();
}



void MainWindow::vykresliStav(QString stav)
{
    qDebug() <<  Q_FUNC_INFO;
    if(stav=="BeforeStop")
    {
        ui->pushButton_jizda_beforeStop->setChecked(true);
    }
    if(stav=="AtStop")
    {
        ui->pushButton_jizda_atStop->setChecked(true);
    }
    if(stav=="AfterStop")
    {
        ui->pushButton_jizda_afterStop->setChecked(true);
    }
    if(stav=="BetweenStop")
    {
        ui->pushButton_jizda_betweenStop->setChecked(true);
    }
    ui->locationStateIndicator->setText(stavSystemu.locationState);
}



/*!

*/
void MainWindow::on_pushButton_jizda_sipkaZpet_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.currentStopIndex0>=1)
    {
        if(stavSystemu.locationState=="AfterStop")
        {
            stavSystemu.locationState="AtStop";
            stavSystemu.currentStopIndex0--;
            eventPrijezd();
        }
        else
        {
            if(stavSystemu.locationState=="BetweenStop")
            {stavSystemu.locationState="AfterStop";}

            if(stavSystemu.locationState=="BeforeStop")
            {stavSystemu.locationState="BetweenStop";}

            if(stavSystemu.locationState=="AtStop")
            {stavSystemu.locationState="BeforeStop";}
        }
        aktualizaceDispleje();
    }
    ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0));
    xmlVdv301HromadnyUpdate();
}


/*!
 \fn void MainWindow::inicializaceVyberovychPoli()

pripoji se k databazi a naplni okna pro vyber spoju
*/
void MainWindow::inicializaceVyberovychPoli()
{
    qDebug() <<  Q_FUNC_INFO;
    sqlPraceRopid.pripoj();



    ui->listView_poradi->setModel(&prazdnyModel);
    ui->tableView_turnusSpoj->setModel(&prazdnyModel);

    ui->tableView_connection->setModel(&prazdnyModel);

    QSqlQueryModel* modelLinky=sqlPraceRopid.stahniSeznamLinekModel(this->vyrobMaskuKalendareJizd());
    QSqlQueryModel* modelKmenoveLinky=sqlPraceRopid.stahniSeznamKmenovychLinekModel(this->vyrobMaskuKalendareJizd());

    if (modelLinky->rowCount()>0)
    {
        while ( modelLinky->canFetchMore())
        {
            modelLinky->fetchMore();
        }
        while ( modelKmenoveLinky->canFetchMore())
        {
            modelKmenoveLinky->fetchMore();
        }

        ui->listView_linky->setModel(modelLinky);
        ui->listView_linky->setModelColumn(modelLinky->record().indexOf("l.c"));

        ui->listView_kmenovaLinka->setModel(modelKmenoveLinky);
        ui->listView_kmenovaLinka->setModelColumn(modelKmenoveLinky->record().indexOf("l.c"));

        aktualizaceKalendare();
    }
    else
    {

        qDebug()<<"chyba nacitani linek";
    }
}



/*!
načte platnost a nastaví rozsahy klikatelných oblastí kalendáře
*/
void MainWindow::aktualizaceKalendare()
{
    qDebug() <<  Q_FUNC_INFO;
    if(sqlPraceRopid.nactiPlatnost(platnostOd,platnostDo))
    {
        ui->calendarWidget->setMinimumDate(platnostOd);
        ui->calendarWidget->setMaximumDate(platnostDo);
    }
    else
    {
        ui->calendarWidget->setMinimumDate(QDate(1900, 1, 1));
        ui->calendarWidget->setMaximumDate(QDate(3000, 1, 1));
    }
}


/*!
bezpečně vymaže obsah QListWidget
*/
void MainWindow::vymazSeznam(QListWidget *vstup)
{
    // https://stackoverflow.com/a/53632933
    vstup->blockSignals(true);
    vstup->clear();
    vstup->blockSignals(false);
}


/*!

*/
void MainWindow::aktualizaceDispleje()
{
    qDebug() <<  Q_FUNC_INFO;

    if(this->stavSystemu.currentVehicleRun.tripList.length()<=stavSystemu.currentTripIndex)
    {
        qDebug()<<"spoj odpovidajici indexu neexistuje";
        return;
    }

    vypisZastavkyTabulka(stavSystemu.currentStopIndex0,this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.locationState);
    int delkaGlobalnihoSeznamu= this->stavSystemu.countCurrentTripStops();
    int indexZastavky=stavSystemu.currentStopIndex0;
    qDebug()<<"delka seznamu spoju "<<this->stavSystemu.currentVehicleRun.tripList.length()<<" index "<<stavSystemu.currentTripIndex<<" delka globsezzast "<< delkaGlobalnihoSeznamu  << " indexAktZast "<<indexZastavky   ;

    if (indexZastavky>=delkaGlobalnihoSeznamu)
    {
        qDebug()<<"index zastavky je mimo rozsah";
        return;
    }

    ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0+1));
    ui->label_aktLinka->setText(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList.at(stavSystemu.currentStopIndex0).line.lineNumber);
    ui->label_aktSpoj->setText(QString::number(this->stavSystemu.getCurrentTrip().idRopid));


    vykresliStav(stavSystemu.locationState);
}


/*!

*/
void MainWindow::on_pushButton_jizda_sipkaZpetSkok_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.currentStopIndex0>=2)
    {
        stavSystemu.currentStopIndex0--;
    }
    ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0));
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

}



/*!

*/
void MainWindow::on_pushButton_menu_quit_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    MainWindow::close();
    QApplication::exit(0);
    //QCoreApplication::exit(0);

}


/*!

*/

void MainWindow::on_pushButton_jizda_beforeStop_clicked()
{

    stavSystemu.locationState="BeforeStop";
    xmlVdv301HromadnyUpdate();
}

/*!

*/
void MainWindow::on_pushButton_jizda_atStop_clicked()
{

    eventPrijezd();

}



/*!

*/
void MainWindow::on_pushButton_jizda_afterStop_clicked()
{

    stavSystemu.locationState="AfterStop";
    xmlVdv301HromadnyUpdate();
}



/*!

*/
void MainWindow::on_pushButton_jizda_betweenStop_clicked()
{

    stavSystemu.locationState="BetweenStop";
    xmlVdv301HromadnyUpdate();
}



/*!

*/
void MainWindow::on_checkBox_connections_stateChanged(int arg1)
{
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.showConnections= ui->checkBox_connections->isChecked();
}


/*!

*/
void MainWindow::on_pushButton_nast_nactiXMLropid_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    //   emit signalZahajImport(xmlRopidImportStream.vstupniXmlSouborCesta);

    eventOpusteniVydeje();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );


    XmlImportJr *xmlImportJr =  new XmlImportJr();

    xmlImportJr->truncateAll();

    xmlImportJr->vstupniXmlSouborCesta=cestaXml;

    connectyImport(xmlImportJr);


    xmlImportJr->start();


    //xmlRopidImportStream.otevriSoubor(xmlRopidImportStream.vstupniXmlSouborCesta);

}


void MainWindow::connectyImport(XmlImportJr *xmlImportJr)
{
    connect(xmlImportJr,&XmlRopidImportStream::resultReady, this, &MainWindow::slotImportDokoncen);
    connect(xmlImportJr,&XmlRopidImportStream::finished, xmlImportJr, &QObject::deleteLater);
    connect(xmlImportJr,&XmlRopidImportStream::finished, this, &MainWindow::slotImportAktivujTlacitka);

    connect(xmlImportJr,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgress,this,&MainWindow::slotNastavProgress);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgressMax,this,&MainWindow::slotNastavProgressMax);

    /*

    connect(xmlImportJr,&XmlRopidImportStream::resultReady, this, &MainWindow::handleResultsJr);
    connect(xmlImportJr,&XmlRopidImportStream::finished, xmlImportJr, &QObject::deleteLater);
    connect(xmlImportJr,&XmlRopidImportStream::finished, this, &MainWindow::slotAktivujTlacitka);

    connect(xmlImportJr,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);
*/

}




void MainWindow::slotNastavProgress(int hodnota)
{
    ui->progressBar_importXml->setValue(hodnota);
    // qDebug()<<QString::number(hodnota)<<"/"<<QString::number(ui->progressBar->maximum());
}


void MainWindow::slotNastavProgressMax(int hodnota)
{
    //resetujProgressBar();
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(hodnota);
    ui->progressBar_importXml->setMaximum(hodnota);
}

void MainWindow::slotImportDokoncen()
{
    qDebug() <<  Q_FUNC_INFO;
    this->pracovniDatumPrvniDenDat();
    this->inicializaceVyberovychPoli();
}


void MainWindow::slotImportDeaktivujTlacitka()
{
    qDebug() <<  Q_FUNC_INFO;

}

void MainWindow::slotImportAktivujTlacitka()
{
    qDebug() <<  Q_FUNC_INFO;

}


/*!

*/
void MainWindow::on_pushButton_nast_truncate_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    XmlImportJr *xmlImportJr =  new XmlImportJr();

    xmlImportJr->truncateAll();
    xmlImportJr->vacuum();
}


/*!

*/
void MainWindow::on_pushButton_nast_odesliPrikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    // ibisOvladani.dopocetCelni("l006");
}


/*!

*/
void MainWindow::on_pushButton_nast_nastavPort_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.globalniSeriovyPort=ui->lineEdit_jmenoPortu->text();
    ibisOvladani.dopocetKontrolnihoZnaku("l006");
    // ibisOvladani.dopocetKontrolnihoZnaku("aA1 ahoj");
    // ibisOvladani.dopocetKontrolnihoZnaku("v povel v\\");
    // ibisOvladani.dopocetKontrolnihoZnaku("zA povel zA");
    // ibisOvladani.dopocetKontrolnihoZnaku("zN povel zN");
    // ibisOvladani.dopocetKontrolnihoZnaku("xC2");
}


/*!

*/
void MainWindow::on_pushButton_jizda_IBIS_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.dopocetKontrolnihoZnaku("xC2");
    ibisOvladani.odesliFrontKomplet(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.currentStopIndex0);
    ibisOvladani.odesliSideKomplet(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.currentStopIndex0);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.currentStopIndex0);
    ibisOvladani.odeslikompletBUSEjednoradekAA(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.currentStopIndex0);
    ibisOvladani.odesliRearKomplet(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList,stavSystemu.currentStopIndex0);

}


/*!

*/
int MainWindow::eventPrijezd()
{
    qDebug() <<  Q_FUNC_INFO;

    stavSystemu.doorState="DoorsOpen";

    if (stavSystemu.currentStopIndex0<(this->stavSystemu.countCurrentTripStops()-1))
    {
        hlasic.kompletZastavka(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint,this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0+1].stopPoint);
    }
    else
    {
        hlasic.kompletKonecna(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint);
    }



    stavSystemu.locationState="AtStop";
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

    QVector<QString> poznamky=this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint.notesList;
    qDebug()<<"poznamek je tolik: "<<QString::number(poznamky.count());
    foreach(QString poznamka, poznamky)
    {
        eventPoznamkaRidici(poznamka);
    }

    return 1;
}



/*!

*/
int MainWindow::eventOdjezd()
{
    qDebug() <<  Q_FUNC_INFO;

    if(stavSystemu.currentStopIndex0==1)
    {
        hlasic.kompletOdjezdPrvniZastavka(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint);
    }

    timerAfterStopToBetweenStop.start();


    return 1;
}

void MainWindow::eventAfterStopToBetweenStop()
{
    qDebug() <<  Q_FUNC_INFO;
    if(FareZone::showZoneChangeCheck(this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0-1].stopPoint.fareZoneList,this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint.fareZoneList))
    {
        qDebug()<<"srovnani pasem zastavek "<<this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0-1].stopPoint.StopName<<" a "<<this->stavSystemu.getCurrentTrip().globalStopPointDestinationList[stavSystemu.currentStopIndex0].stopPoint.StopName;
        eventZmenaTarifnihoPasma();
    }
    else
    {
        eventSkryjZmenuTarifnihoPasma();
    }
    stavSystemu.locationState="BetweenStop";
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

}


/*!

*/
void MainWindow::on_pushButton_menu_jizda_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_jizda );

}


/*!

*/
void MainWindow::on_pushButton_manual_smazOkno_clicked()
{
    ui->plainTextEdit_CustomXml->clear();
}


/*!

*/
void MainWindow::on_pushButton_manual_odesliXml_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray vysledek2="";
    vysledek2=vysledek2+ui->plainTextEdit_CustomXml->toPlainText().toUtf8();
    customerInformationService1_0.setBodyContent("AllData",vysledek2);
    customerInformationService2_2CZ1_0.setBodyContent("AllData",vysledek2);

    for(int i=0;i<customerInformationService1_0.subscriberList.count();i++ )
    {
        customerInformationService1_0.postToSubscriber(customerInformationService1_0.subscriberList[i].address,vysledek2);
    }
    for(int i=0;i<customerInformationService2_2CZ1_0.subscriberList.count();i++ )
    {
        customerInformationService2_2CZ1_0.postToSubscriber(customerInformationService2_2CZ1_0.subscriberList[i].address,vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";
}

void MainWindow::vypisSubscriberyDoTabulky(QVector<Subscriber> adresy, QTableWidget* tabulka)
{
    qDebug() <<  Q_FUNC_INFO;
    tabulka->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qDebug()<<"vracim 0";
    }
    else
    {
        for (int i = 0;  i < adresy.count(); i++)
        {
            Subscriber odberatel=adresy.at(i);

            qint32 row;
            QTableWidgetItem *cell;
            row = tabulka->rowCount();
            tabulka->insertRow(row);
            cell = new QTableWidgetItem(odberatel.address.toString());
            tabulka->setItem(row, 0, cell);


            cell = new QTableWidgetItem(odberatel.structure);
            tabulka->setItem(row, 1, cell);
            tabulka->resizeColumnsToContents();
        }
        qDebug()<<"vracim 1";
    }


}

/*!

*/
void MainWindow::vypisSubscribery1_0(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    vypisSubscriberyDoTabulky(adresy,ui->tableWidget_subscriberList1_0);
}

/*!

*/
void MainWindow::vypisSubscribery2_2CZ(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    vypisSubscriberyDoTabulky(adresy,ui->tableWidget_subscriberList2_2CZ1_0);
}

void MainWindow::vypisSubscribery2_3(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    vypisSubscriberyDoTabulky(adresy,ui->tableWidget_subscriberList2_3);
}


/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_clicked()
{
    vypisDiagnostika(customerInformationService1_0.handleNewSubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}



/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_2_clicked()
{
    vypisDiagnostika(customerInformationService2_2CZ1_0.handleNewSubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}


void MainWindow::on_pushButton_manual_addsubscriber_3_clicked()
{
    vypisDiagnostika(customerInformationService2_3.handleNewSubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}


/*!

*/
void MainWindow::on_pushButton_manual_removeSubscriber_clicked()
{
    if (ui->tableWidget_subscriberList1_0->rowCount()==0)
    {

        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_subscriberList1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrnao");
        return;
    }
    int indexPolozky = ui->tableWidget_subscriberList1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService1_0.removeSubscriber(indexPolozky)==1)
    {
        vypisSubscribery1_0(customerInformationService1_0.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


/*!

*/
void MainWindow::on_pushButton_manual_removeSubscriber_2_clicked()
{
    if (ui->tableWidget_subscriberList2_2CZ1_0->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_subscriberList2_2CZ1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->tableWidget_subscriberList2_2CZ1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_2CZ1_0.removeSubscriber(indexPolozky)==1)
    {
        vypisSubscribery2_2CZ(customerInformationService2_2CZ1_0.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


void MainWindow::on_pushButton_manual_removeSubscriber_3_clicked()
{
    if (ui->tableWidget_subscriberList2_3->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_subscriberList2_3->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->tableWidget_subscriberList2_3->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_3.removeSubscriber(indexPolozky)==1)
    {
        vypisSubscribery2_3(customerInformationService2_3.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}



/*!

*/
void MainWindow::vypisDiagnostika(QString vstup)
{
    qDebug()<<" MainWindow::vypisDiagnostika "<<vstup;
    ui->label_diagnostika_manual->clear();
    ui->label_diagnostika_manual->setText(vstup);
    ui->statusBar->showMessage(vstup);
    logfile.pridejNaKonecSouboru(souborLogu,QDateTime::currentDateTime().toString()+" "+ vstup);
}



/*!

*/
void MainWindow::slotVypisSqlVysledek(QString vstup)
{
    ui->label_diagnostika_sql->setText(vstup);
}


/*!

*/
void MainWindow::on_pushButton_menu_turnus_clicked()
{
    eventOpusteniVydeje();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );

}

/*!

*/
void MainWindow::on_pushButton_menu2_quit_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    this->on_pushButton_menu_quit_clicked();
}


/*!

*/
void MainWindow::zastavSluzby()
{
    //customerInformationService1_0.
}




/*!

*/
void MainWindow::on_pushButton_menu_fullscreen_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    this->toggleFullscreen();
}


/*!

*/
void MainWindow::on_pushButton_menu2_fullscreen_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    this->toggleFullscreen();
}


/*!
CIS 2.2CZ1.0
*/
void MainWindow::radio1(bool stav)
{
    ui->radioButton_ON1->setChecked(stav);
    ui->radioButton_OFF1->setChecked(!stav);
}


/*!
DEVMGMT 1:0
*/
void MainWindow::radio2(bool stav)
{
    ui->radioButton_ON2->setChecked(stav);
    ui->radioButton_OFF2->setChecked(!stav);
}


/*!
 TicketValidationService 2.2CZ1.0
*/

void MainWindow::radio3(bool stav)
{
    ui->radioButton_ON3->setChecked(stav);
    ui->radioButton_OFF3->setChecked(!stav);
}


/*!
CIS 1.0
*/

void MainWindow::radio4(bool stav)
{
    ui->radioButton_ON4->setChecked(stav);
    ui->radioButton_OFF4->setChecked(!stav);
}


/*!

*/
void MainWindow::toggleFullscreen()
{
    if (MainWindow::windowState()==Qt::WindowFullScreen )
    {
        MainWindow::setWindowState(Qt::WindowMaximized);
    }
    else
    {
        MainWindow::setWindowState(Qt::WindowFullScreen);
    }
}



/*!

*/
void MainWindow::testyVykresliCasti(QVector<PolozkaTestu> &seznamPolozek)
{

    qDebug() <<  Q_FUNC_INFO;
    for(int i =0;i<seznamPolozek.size();i++)
    {
        qDebug()<<i<<" "<<seznamPolozek.at(i).nazev<<" "<<seznamPolozek.at(i).vysledek;
    }

    ui->tableWidgetCastiTestu->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<seznamPolozek.size();
    if (seznamPolozek.size()==0)
    {
        qDebug()<<"vracim 0";
        //return 0;
    }
    else
    {
        for (int i = 0;  i < seznamPolozek.count(); i++)
        {
            qint32 row;
            QTableWidgetItem *cell;
            row = ui->tableWidgetCastiTestu->rowCount();
            ui->tableWidgetCastiTestu->insertRow(row);
            cell = new QTableWidgetItem(seznamPolozek.at(i).nazev);
            ui->tableWidgetCastiTestu->setItem(row, 0, cell);

            cell = new QTableWidgetItem(seznamPolozek.at(i).prubeh);
            ui->tableWidgetCastiTestu->setItem(row, 1, cell);

            cell = new QTableWidgetItem(seznamPolozek.at(i).vysledek);
            ui->tableWidgetCastiTestu->setItem(row, 2, cell);

            ui->tableWidgetCastiTestu->resizeColumnsToContents();
        }
        qDebug()<<"vracim 1";
        //return 1;
    }
}


/*!

*/
void MainWindow::on_pushButton_menu2_prubehTestu_clicked()
{
    ui->stackedWidget_testy->setCurrentIndex(0);
}


/*!

*/
void MainWindow::on_pushButton_startTest_clicked()
{
    testStart(testIndex);
    //vzorovyTest.start();
}



/*!

*/
void MainWindow::on_pushButton_stopTest_clicked()
{
    vzorovyTest.stop();
}


/*!

*/
//tlacitka pro spusteni testu
void MainWindow::on_pushButton_test1_clicked()
{
    testIndex=0;
    testNaplnOkno(testIndex);
}


/*!

*/

void MainWindow::on_pushButton_test2_clicked()
{
    testIndex=1;
    testNaplnOkno(testIndex);
}


/*!

*/
void MainWindow::on_pushButton_test3_clicked()
{
    testIndex=2;
    testNaplnOkno(testIndex);
}


/*!

*/
void MainWindow::on_pushButton_test4_clicked()
{
    testIndex=3;
    testNaplnOkno(testIndex);
}



/*!

*/
void MainWindow::on_pushButton_menu2_sluzby_clicked()
{
    ui->stackedWidget_testy->setCurrentIndex(1);
}


/*!
 * \brief popis
 */
void MainWindow::on_pushButton_nast_xmlVyberCestu_clicked()
{
    cestaXml=otevriSouborXmlDialog(cestaXml);
    if (cestaXml=="")
    {
        ui->pushButton_nast_nactiXMLropid->setDisabled(true);
    }
    else
    {
        ui->pushButton_nast_nactiXMLropid->setDisabled(false);

    }
    nastavLabelCestyXml();
}


/*!

*/
void MainWindow::on_pushButton_nast_dnes_clicked()
{
    pracovniDatumDnes();
}


/*!

*/
void MainWindow::nastavLabelCestyXml()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_cestaXml->setText(cestaXml);

}


/*!

*/
QString MainWindow::otevriSouborXmlDialog(QString cesta)
{
    qDebug() <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), cesta,
                                                    tr("XML Ropid JŘ (*.xml);;All Files (*)"));
    return fileName;
}


/*!

*/
void MainWindow::on_calendarWidget_selectionChanged()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.referenceDate=ui->calendarWidget->selectedDate();
    aktualizacePracovnihoData();
}



/*!

*/
void MainWindow::aktualizacePracovnihoData()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->dateEdit->setDate(stavSystemu.referenceDate);
    ui->calendarWidget->setSelectedDate(stavSystemu.referenceDate);

    qDebug()<<"od "<<platnostOd<<" do "<<platnostDo<<" pracovni "<<stavSystemu.referenceDate ;
    qDebug()<<"dnu do pracovnihodata "<< stavSystemu.referenceDate.daysTo(platnostOd) <<" dnu do zacatku platnosti " << stavSystemu.referenceDate.daysTo(platnostDo);


    this->vyrobMaskuKalendareJizd();
    sqlPraceRopid.maskaKalendarJizd(this->stavSystemu.referenceDate,platnostOd,platnostDo);

    inicializaceVyberovychPoli();
}

/*!
\brief popis
xxxxxx
*/
void MainWindow::pracovniDatumDnes()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.referenceDate=QDate::currentDate();
    aktualizacePracovnihoData();
}


/*!

*/
void MainWindow::pracovniDatumPrvniDenDat()
{
    qDebug() <<  Q_FUNC_INFO;
    aktualizaceKalendare();


    stavSystemu.referenceDate=platnostOd;
    aktualizacePracovnihoData();
}


/*!

*/
void MainWindow::slotAktualizacePracData()
{
    inicializaceVyberovychPoli();
}



/*!

*/
QString MainWindow::vyrobMaskuKalendareJizd()
{
    qDebug() <<  Q_FUNC_INFO;
    return sqlPraceRopid.maskaKalendarJizd(stavSystemu.referenceDate,platnostOd, platnostDo);
}



void MainWindow::vypisZastavkyTabulka(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, QString locationState)
{

    qDebug() <<  Q_FUNC_INFO;
    ui->tableWidgetNasledujiciZastavky->setRowCount(0);



    for (int i=0;i<(docasnySeznamZastavek.count());i++)
    {
        QString cisloZastavky = QString::number(i+1);
        QString nazevZastavky2 = docasnySeznamZastavek.at(i).stopPoint.StopName;
        QString odjezdZeZastavky =  sqlPraceRopid.vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).stopPoint.DepartureTime);
        QString pasma= sqlPraceRopid.pasmaDoStringu(docasnySeznamZastavek.at(i).stopPoint.fareZoneList,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).stopPoint.onRequest==true)
        {
            znameni="(x)";
        }


        qint32 row;
        QTableWidgetItem *cell;
        row = ui->tableWidgetNasledujiciZastavky->rowCount();
        ui->tableWidgetNasledujiciZastavky->insertRow(row);

        cell = new QTableWidgetItem(cisloZastavky);
        ui->tableWidgetNasledujiciZastavky->setItem(row, 0, cell);

        cell = new QTableWidgetItem(nazevZastavky2);
        ui->tableWidgetNasledujiciZastavky->setItem(row, 1, cell);


        cell = new QTableWidgetItem(odjezdZeZastavky);
        ui->tableWidgetNasledujiciZastavky->setItem(row, 2, cell);


        cell = new QTableWidgetItem(znameni);
        ui->tableWidgetNasledujiciZastavky->setItem(row, 3, cell);

        cell = new QTableWidgetItem(pasma);
        ui->tableWidgetNasledujiciZastavky->setItem(row, 4, cell);

        //   ui->tableWidgetNasledujiciZastavky->resizeColumnsToContents();

    }

    int zabarvenySloupec=1;
    int pocetRadkuTabulky=ui->tableWidgetNasledujiciZastavky->rowCount();
    if (pocetRadkuTabulky<=0)
    {
        qDebug()<<"tabulku nelze obarvit, je prazdna";
        // return;
    }
    else
    {
        if (locationState=="AtStop")
        {

            QBrush cyan(Qt::cyan);
            ui->tableWidgetNasledujiciZastavky->item(cisloporadi,zabarvenySloupec)->setBackground(cyan);
        }
        else
        {
            QBrush gray(Qt::gray);
            ui->tableWidgetNasledujiciZastavky->item(cisloporadi,zabarvenySloupec)->setBackground(gray);
        }
        ui->tableWidgetNasledujiciZastavky->resizeColumnsToContents();
        ui->tableWidgetNasledujiciZastavky->resizeRowsToContents();
        ui->tableWidgetNasledujiciZastavky->scrollToItem(ui->tableWidgetNasledujiciZastavky->item(cisloporadi,0));
    }
}

void MainWindow::on_tableWidgetNasledujiciZastavky_cellClicked(int row, int column)
{
    qDebug()<<"on_tableWidgetNasledujiciZastavky_cellClicked";
    stavSystemu.locationState="AtStop";
    ui->pushButton_jizda_atStop->setChecked(true);
    stavSystemu.currentStopIndex0=row;
    eventPrijezd();
    aktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";

    xmlVdv301HromadnyUpdate();
}


/*!
 * \brief MainWindow::dalsiSpoj
    přepíná na další spoj na turnusu posunem indexů, pokud návazný spoj neexistuje
*/
void MainWindow::dalsiSpoj()
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"index "<<stavSystemu.currentTripIndex<<" pocetSpoju "<<stavSystemu.currentVehicleRun.tripList.count();
    if ((stavSystemu.currentTripIndex)<(stavSystemu.currentVehicleRun.tripList.count()-1))
    {
        stavSystemu.currentTripIndex++;
        stavSystemu.currentStopIndex0=0;
        // AktualizaceDispleje();
        natahniSeznamSpojeKomplet();
        xmlVdv301HromadnyUpdate();
    }
    else
    {
        qDebug()<<"posledni spoj ze seznamu, nelze se dale posouvat";
    }
}


void MainWindow::eventZmenaTarifnihoPasma()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.showFareZoneChange=true;
    xmlVdv301HromadnyUpdate();
    hlasic.kompletZmenaTarifnihoPasma();
    timerTrvaniZmenyPasma.start();

}

void MainWindow::eventZobrazOznameni(int index, QVector<AdditionalAnnoucement> seznamHlaseni)
{
    qDebug() <<  Q_FUNC_INFO;

    if((index>=0)&&(index<seznamHlaseni.count()))
    {

        stavSystemu.currentSpecialAnnoucement=seznamHlaseni.at(index);
        stavSystemu.isSpecialAnnoucementUsed=true;
        //zobraz na panely
        xmlVdv301HromadnyUpdate();
        timerSpecialniOznameniSmazat.start();
        //spust hlaseni
        hlasic.kompletSpecialniHlaseni(stavSystemu.currentSpecialAnnoucement);
    }

}

void MainWindow::eventPoznamkaRidici(QString poznamka)
{
    qDebug() <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(nahradZnacky(poznamka));
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
}


void MainWindow::popUpMessage(QString messageText)
{
    QMessageBox msgBox;
    msgBox.setText(nahradZnacky(messageText));
    msgBox.exec();
}

void MainWindow::eventSkryjZmenuTarifnihoPasma()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.showFareZoneChange=false;
    xmlVdv301HromadnyUpdate();
}

//není implementováno
void MainWindow::eventZmenaTarifnihoSystemu()
{
    qDebug() <<  Q_FUNC_INFO;
    /*stavSystemu.zobrazZmenuPasma=true;
    xmlVdv301HromadnyUpdate();

    timerTrvaniZmenyPasma->setInterval(10000);
    timerTrvaniZmenyPasma->setSingleShot(true);
    timerTrvaniZmenyPasma->start();
    */

}

//není implementováno
void MainWindow::eventSkryjZmenuTarifnihoSystemu()
{
    qDebug() <<  Q_FUNC_INFO;
    /* stavSystemu.zobrazZmenuPasma=false;
   xmlVdv301HromadnyUpdate();
   */
}


void MainWindow::eventVstupDoVydeje()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->pushButton_menu_jizda->setDisabled(false);
}

void MainWindow::eventOpusteniVydeje()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->pushButton_menu_jizda->setDisabled(true);
    timerAfterStopToBetweenStop.stop();
    timerStahniPrestupy.stop();
    timerTrvaniZmenyPasma.stop();
    resetSeznamuSpoju();

    customerInformationService1_0.outOfService();
    customerInformationService2_2CZ1_0.outOfService();
    customerInformationService2_3.outOfService();

    xmlVdv301HromadnyUpdate();
    inicializaceVyberovychPoli();
}

void MainWindow::resetSeznamuSpoju()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.reset();
}


void MainWindow::modelDoTabulkySeradit(QSqlQueryModel* modelInput,QTableView* tableView)
{
    qDebug()<<Q_FUNC_INFO;

    if(modelInput==NULL)
    {
        qDebug()<<"model je prazdny";
        return;
    }
    qDebug()<<"model size:"<<modelInput->rowCount()<<" "<<modelInput->columnCount();



    while ( modelInput->canFetchMore())
    {
        modelInput->fetchMore();
    }

    if(modelInput->rowCount()==0)
    {
        return;
    }


    proxyModel->setSourceModel(modelInput);

    tableView->setModel(proxyModel);
    tableView->show();
    tableView->resizeColumnsToContents();
    connect(tableView->horizontalHeader(),SIGNAL(sortIndicatorChanged(int, Qt::SortOrder )),tableView,SLOT(sortByColumn(int, Qt::SortOrder )));
    int pocet= proxyModel->rowCount();
    qDebug()<<"pocet vysledku: "<<QString::number(pocet);
    //existujeLastError(model);
}
/*!

*/
void MainWindow::on_pushButton_menu_linkospoj_clicked()
{
    eventOpusteniVydeje();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_linkaspoj );

}


void MainWindow::on_pushButton_jizda_sipkaDalSkok_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.currentStopIndex0<(this->stavSystemu.countCurrentTripStops()-1))
    {
        stavSystemu.currentStopIndex0++;
    }
    else
    {
        this->dalsiSpoj();
    }
    ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0));
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_pushButton_menu_oznameni_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_oznameni);

}


void MainWindow::on_tableWidget_oznameni_cellClicked(int row, int column)
{
    qDebug() <<  Q_FUNC_INFO;
    eventZobrazOznameni(row,konfigurace.specialniHlaseni);
}


void MainWindow::slotVymazatSpecialniOznameni()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.isSpecialAnnoucementUsed=false;
    xmlVdv301HromadnyUpdate();
}

void MainWindow::on_radioButton_singleDoorOpen_clicked()
{
    stavSystemu.doorState="SingleDoorOpen";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_allDoorsClosed_clicked()
{
    stavSystemu.doorState="AllDoorsClosed";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_doorsOpen_clicked()
{
    stavSystemu.doorState="DoorsOpen";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_singleDoorCloser_clicked()
{
    stavSystemu.doorState="SingleDoorClosed";
    xmlVdv301HromadnyUpdate();
}

void MainWindow::slotAktualizaceTabulkySluzeb()
{
    qDebug()<<Q_FUNC_INFO;
    vykresliSluzbyDoTabulky(devMgmtSubscriber.deviceListDetected, devMgmtSubscriber.deviceListConfigured);
}

void MainWindow::vykresliSluzbyDoTabulky(QVector<DevMgmtPublisherStruct> seznamSluzebDetekce, QVector<DevMgmtPublisherStruct> seznamSluzebKonfigurace)
{
    qDebug() <<  Q_FUNC_INFO;
    // ui->tabulkaSubscriberu->setRowCount(0);
    vymazTabulkuSubscriberu(ui->tableWidget_seznamZarizeni);


    foreach(DevMgmtPublisherStruct sluzba, seznamSluzebDetekce)
    {
        sluzbaDoTabulky(sluzba);
    }

    foreach(DevMgmtPublisherStruct sluzba, seznamSluzebKonfigurace)
    {
        if(!sluzba.isInListByIdClass(seznamSluzebDetekce))
        {
            sluzbaDoTabulky(sluzba);
        }

    }
}

void MainWindow::vymazTabulkuSubscriberu(QTableWidget *tableWidget)
{
    qDebug() <<  Q_FUNC_INFO;
    //  https://stackoverflow.com/a/31564541
    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);
}


//vypis detekovanych sluzeb do tabulky
void MainWindow::sluzbaDoTabulky(DevMgmtPublisherStruct zarizeni)
{
    //QZeroConfService zcs
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString sluzbaNazev=zarizeni.serviceName;
    QString ipadresa=zarizeni.hostAddress.toString() ;
    QString hostName=zarizeni.hostname;
    QString verze=zarizeni.ibisIpVersion;
    QString deviceClass=zarizeni.deviceClass;
    QString id=zarizeni.deviceId;
    int port=zarizeni.portNumber;
    int hwConfig=zarizeni.hwConfig;
    QString status=zarizeni.status;
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;
 */

    row = ui->tableWidget_seznamZarizeni->rowCount();
    ui->tableWidget_seznamZarizeni->insertRow(row);

    cell = new QTableWidgetItem(QString::number(hwConfig));

    if(hwConfig==1)
    {
        if(ipadresa=="")
        {
            cell->setBackground(QColor(255,0,0));
        }
        else
        {
            cell->setBackground(QColor(0,255,0));
        }


    }
    else
    {
        cell->setBackground(QColor(255,255,0));
    }
    ui->tableWidget_seznamZarizeni->setItem(row, 0, cell);


    cell = new QTableWidgetItem(deviceClass);
    ui->tableWidget_seznamZarizeni->setItem(row, 1, cell);

    cell = new QTableWidgetItem(id);
    ui->tableWidget_seznamZarizeni->setItem(row, 2, cell);

    cell = new QTableWidgetItem(hostName);
    ui->tableWidget_seznamZarizeni->setItem(row, 3, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tableWidget_seznamZarizeni->setItem(row, 4, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_seznamZarizeni->setItem(row, 5, cell);

    cell = new QTableWidgetItem(sluzbaNazev);
    ui->tableWidget_seznamZarizeni->setItem(row, 6, cell);

    cell = new QTableWidgetItem(verze);
    ui->tableWidget_seznamZarizeni->setItem(row, 7, cell);

    cell = new QTableWidgetItem(status);
    ui->tableWidget_seznamZarizeni->setItem(row, 8, cell);

    ui->tableWidget_seznamZarizeni->resizeColumnsToContents();

    qDebug()<<"sluzbaDoTabulky_konec";
}


QString MainWindow::nahradZnacky(QString vstup)
{
    QString vysledek="";

    qDebug().noquote()<<"retezec pred: "<<vstup;
    //  vysledek=vstup.replace(QRegExp("a"),"b");



#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //qt5
    QRegExp vyraz=QRegExp("\\\\([^<]*)\\\\");
    vyraz.setMinimal(true);
#else
    //qt6

    QRegularExpression vyraz("\\\\([^<]*)\\\\");

#endif




    vysledek=vstup.replace(vyraz,"<b>\\1</b>");
    qDebug().noquote()<<"retezec po: "<<vysledek;

    return vysledek;
}


void MainWindow::on_listView_linky_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();
    qDebug()<<"cislo linky:"<<stavSystemu.currentLine.c;



    ui->polelinky->setText(QString::number(stavSystemu.currentLine.c ));
    modelSpoje2=sqlPraceRopid.stahniSeznamSpojuModel2(stavSystemu.currentLine, this->vyrobMaskuKalendareJizd());
    qDebug()<<"model size:"<<modelSpoje2->rowCount()<<" "<<modelSpoje2->columnCount();


    modelDoTabulkySeradit(modelSpoje2,ui->tableView_connection);
    ui->tableView_connection->hideColumn(5);
    ui->tableView_connection->hideColumn(6);
    ui->tableView_connection->hideColumn(7);




}



void MainWindow::on_listView_kmenovaLinka_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;

    stavSystemu.currentVehicleRun.rootLine.c= index.data(Qt::DisplayRole).toString().toInt();

    ui->poleLinkyTurnus->setText(QString::number(stavSystemu.currentVehicleRun.rootLine.c));

    QSqlQueryModel* modelPoradi=sqlPraceRopid.stahniSeznamPoradiModel(stavSystemu.currentVehicleRun.rootLine, this->vyrobMaskuKalendareJizd());

    ui->listView_poradi->setModel(modelPoradi);
    ui->listView_poradi->setModelColumn(modelPoradi->record().indexOf("o.p"));

    ui->tableView_turnusSpoj->setModel(&prazdnyModel);
}

void MainWindow::on_listView_poradi_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();

    if (ui->listView_poradi->model()->rowCount()!=0)
    {
        if(index.row()>=0)
        {
            stavSystemu.currentVehicleRun.order=index.data(Qt::DisplayRole).toString().toInt();

            /// zakomentovat?
            if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.currentVehicleRun,this->vyrobMaskuKalendareJizd())==1)
            {
                qDebug()<<"pocetSpoju: "<<stavSystemu.currentVehicleRun.tripList.count();
            }
            else
            {
                qDebug()<<"spoje nenalezeny";
            }

            QSqlQueryModel* modelTurnusSpoj=sqlPraceRopid.stahniSeznamTurnusSpojuModel(stavSystemu.currentVehicleRun, this->vyrobMaskuKalendareJizd());
            ui->tableView_turnusSpoj->setModel(modelTurnusSpoj);
            ui->tableView_turnusSpoj->resizeColumnsToContents();
        }
    }
}

void MainWindow::on_tableView_turnusSpoj_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    if (index.model()->rowCount()!=0)
    {
        qDebug()<<"current item bum";

        stavSystemu.currentTrip.line.c=index.siblingAtColumn(0).data().toInt();
        stavSystemu.currentTrip.idRopid=index.siblingAtColumn(1).data().toInt();

        stavSystemu.currentTripIndex=stavSystemu.currentVehicleRun.tripList.indexOf(stavSystemu.currentTrip);
        qDebug()<<"index spoje na obehu: "<<QString::number(stavSystemu.currentTripIndex)<<" delkaSeznamu: "<<stavSystemu.currentVehicleRun.tripList.count();
        qDebug()<<"hodnota polozky"<<QString::number(stavSystemu.currentTrip.line.c)<<" spoj:"<<QString::number(stavSystemu.currentTrip.idRopid);

        //NUTNE DOPLNIT

        ui->poleLinkyTurnus->setText(QString::number(stavSystemu.currentTrip.line.c));
        ui->poleSpojeTurnus->setText(QString::number(stavSystemu.currentTrip.idRopid));
    }
}


void MainWindow::on_pushButton_refreshDetekce_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    devMgmtSubscriber.slotUpdateDeviceInfo();
}


void MainWindow::on_pushButton_ulozDetekce_clicked()
{

    qDebug() <<  Q_FUNC_INFO;

    int i=0;
    settings.beginWriteArray("hwConfig");
    foreach(DevMgmtPublisherStruct zarizeni, devMgmtSubscriber.deviceListDetected)
    {
        // QJsonDocument json = QJsonDocument::fromVariant(zarizeni.toQMap() );
        settings.setArrayIndex(i);
        settings.setValue("deviceClass",zarizeni.deviceClass);
        settings.setValue("deviceId",zarizeni.deviceId);
        i++;
    }
    settings.endArray();

}



void MainWindow::on_pushButton_nactiDetekce_clicked()
{
    qDebug() <<  Q_FUNC_INFO;

    devMgmtSubscriber.deviceListConfigured.clear();


    int size = settings.beginReadArray("hwConfig");
    for (int j = 0; j < size; ++j) {
        settings.setArrayIndex(j);
        DevMgmtPublisherStruct zarizeni;
        zarizeni.deviceId= settings.value("deviceId").toString();
        zarizeni.deviceClass= settings.value("deviceClass").toString();
        zarizeni.hwConfig=true;
        devMgmtSubscriber.deviceListConfigured.append(zarizeni);
        qDebug()<<"trida: "<<zarizeni.deviceClass<<" id: "<<zarizeni.deviceId;
    }
    settings.endArray();

    qDebug()<<"nacteno "<<QString::number(devMgmtSubscriber.deviceListConfigured.count())<<" zarizeni";
    vykresliSluzbyDoTabulky(devMgmtSubscriber.deviceListDetected, devMgmtSubscriber.deviceListConfigured);
}

/*
 Store
QMap<QString, QVariant> storeMap;
QMapIterator it(myMap);
// iterate through the map to save the values in your chosen format
while(it.hasNext())
{
    storeMap[it.key()] = QVariant(it.value());
    it.next();
}
settings.setValue("myKey", storeMap);
*/


void MainWindow::on_pushButton_jizda_mapa_clicked()
{
    mapaVykresleni.seznamMnozin.clear();
    mapaVykresleni.pridejMnozinu(MapaVykresleni::seznamStopPointDestinationToSeznamMapaBod(stavSystemu.getCurrentTrip().globalStopPointDestinationList,true),true,false,false,false,MnozinaBodu::WGS84);
    mapaVykresleni.pridejMnozinu(MapaVykresleni::seznamStopPointDestinationToSeznamMapaBod(stavSystemu.getCurrentTrip().globalStopPointDestinationList,true),false,false,false,true,MnozinaBodu::WGS84);
    mapaVykresleni.pridejMnozinu(sqlPraceRopid.vytvorTrajektorii(stavSystemu.getCurrentTrip().id,this->vyrobMaskuKalendareJizd()),false, true, false,false, MnozinaBodu::J_STSK);

    mapaVykresleni.seznamMnozinDoJson(mapaVykresleni.seznamMnozin, mapaVykresleni.spojDoTabulky( stavSystemu.currentTrip));

}

QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}



void MainWindow::on_checkBox_stopRequested_clicked(bool checked)
{
    stavSystemu.isVehicleStopRequested=checked;
    xmlVdv301HromadnyUpdate();
}





void MainWindow::on_pushButton_menu2_rezerva_clicked()
{

}


void MainWindow::on_tableView_connection_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    Trip docasnySpoj;

    if (ui->tableView_connection->model()->rowCount()>0)
    {
        if(index.isValid())
        {
            docasnySpoj.id=index.siblingAtColumn(modelSpoje2->record().indexOf("s.s")).data().toInt();
            docasnySpoj.idRopid=index.siblingAtColumn(modelSpoje2->record().indexOf("s.c")).data().toInt();
            docasnySpoj.line.lc=index.siblingAtColumn(modelSpoje2->record().indexOf("l.lc")).data().toInt();
            docasnySpoj.line.c=index.siblingAtColumn(modelSpoje2->record().indexOf("l.c")).data().toInt();
            QString alias=index.siblingAtColumn(modelSpoje2->record().indexOf("l.aois")).data().toString();
            if(alias=="")
            {
                docasnySpoj.line.lineName=QString::number(docasnySpoj.line.c );
            }
            else
            {
                docasnySpoj.line.lineName=alias;
            }



            ui->polespoje->setText(QString::number(docasnySpoj.idRopid));

            stavSystemu.currentTrip=docasnySpoj;
            int kmenovaLinka=0;
            int poradi=0;
            int order=0;


            sqlPraceRopid.najdiTurnusZeSpoje(stavSystemu.currentTrip, kmenovaLinka,poradi, order,this->vyrobMaskuKalendareJizd());
            qDebug()<<"test spoje do turnusu "<<kmenovaLinka<<"/"<<poradi<<" "<<order;

        }
    }

    qDebug()<<"IDspoje:"<<docasnySpoj.id;
}


void MainWindow::on_radioButton_language_cs_clicked()
{
    retranslateUi("cs");
    settings.setValue("app/language","cs");

}


void MainWindow::on_radioButton_language_en_clicked()
{
    retranslateUi("en");
    settings.setValue("app/language","en");
}


void MainWindow::on_pushButton_setGolemioKey_clicked()
{
    settings.setValue("golemio/apikey",ui->lineEdit_golemioKey->text());
    golemio.setKlic(settings.value("golemio/apiKey").toByteArray());
}

