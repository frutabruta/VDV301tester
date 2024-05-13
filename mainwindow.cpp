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
   // devMgmtSubscriber("DeviceManagementService","DeviceStatus","1.0","_ibisip_http._tcp",48477),
    devMgmtSubscriber("DeviceManagementService","DeviceStatus","2.2","_ibisip_http._tcp",48477),

    ui(new Ui::MainWindow)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->setupUi(this);

    ui->pushButton_menu_ride->setEnabled(false);
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );
    ui->tabWidget_hlavni->setCurrentWidget(ui->tab_palPC);
    ui->pushButton_menu_vehicleRun->setChecked(true);
    ui->pushButton_data_startXmlRopidImport->setDisabled(true);

    vektorCis.push_back(&customerInformationService1_0);
    vektorCis.push_back(&customerInformationService2_2CZ1_0);
    vektorCis.push_back(&customerInformationService2_3);

    //QString konstantaPocetDni=settings.value("konstanty/pocetDni").toString();
    //settings.setValue("golemio/api-key","XXX");

    mapPlot.setCestaMapa(QCoreApplication::applicationDirPath());




    //settings.setValue("General/language","en");
    QString jazyk=settings.value("app/language").toString();

    qDebug()<<" novy jazyk:"<<jazyk;
    retranslateUi(jazyk);


    loadConstantsFromSettingsFile();

    if(ibisIsEnabled)
    {
        ibisOvladani.start();
    }

    //ui->stackedWidget_palPc->setWindowState(Qt::WindowFullScreen);


    //inicializace databaze
    initializeSelectionListView();

    //propojeni vsech slotu
    allConnects();

    on_pushButton_detection_loadHwConfig_clicked();


    startAllVdv301Services();
    startServiceFromList(vektorCis);


    //vyplneni polozky build pro rozliseni zkompilovanych verzi
    //QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);

    //kalendarJizd
    workingDateFirstDateOfDataValidity();

    //cesty souboru
    voiceAnnouncer.zmenUmisteniProgramu(applicationDirectory);
    konfigurace.vytvorDefaultniKonfiguraci();
    konfigurace.otevriSoubor();
    
    MainWindowPomocne::naplnTabulkuHlaseni(ui->tableWidget_specialAnnouncements,konfigurace.specialniHlaseni);

    //hlasic.nastavCestu(konfigurace.cestaHlaseni);

    logfile.defaultniLog(logFileQFile);
    logfile.novySoubor(logFileQFile);
    logfile.pridejNaKonecSouboru(logFileQFile,QDateTime::currentDateTime().toString()+" program spuštěn");


    //zobrazeni
    setXmlPathLabel();
    ui->statusBar->showMessage("test");

    //inicializace timeru
    timerFareZoneChangeDuration.setSingleShot(true);
    timerFareZoneChangeDuration.setInterval(konfigurace.trvaniZobrazeniPasma);

    timerSpecialAnnoucementHide.setSingleShot(true);
    timerSpecialAnnoucementHide.setInterval(konfigurace.trvaniZobrazeniOznameni);

    timerDownloadConnections.setInterval(konfigurace.intervalStahovaniPrestupu);

    timerAfterStopToBetweenStop.setSingleShot(true);
    timerAfterStopToBetweenStop.setInterval(konfigurace.intervalAfterStopToBetweenStop);

}


MainWindow::~MainWindow()
{
    delete proxyModel;
    delete modelConnection;
    delete ui;
}


/*!
přesunutí connectů pro větší přehlednost
*/
void MainWindow::allConnects()
{
    qDebug()<<Q_FUNC_INFO;

    this->dumpSubscribers1_0(customerInformationService1_0.subscriberList);
    this->dumpSubscribers2_2CZ(customerInformationService2_2CZ1_0.subscriberList);

    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers1_0);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers2_2CZ);
    connect(&customerInformationService2_3,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers2_3);

    connect(&customerInformationService1_0,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);
    connect(&customerInformationService2_3,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);


    connect(&xmlMpvParser,&XmlMpvParser::stazeniHotovo,this,&MainWindow::slotMpvNetReady);
    connect(&golemio,&Golemio::stazeniHotovo,this,&MainWindow::slotGolemioReady);

    //vypis deviceMAnagementServices publisheru
    // connect(&deviceManagementServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::slotXmlDoPromenne);


    //connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::aktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);
    connect(&devMgmtSubscriber,&IbisIpSubscriber::signalUpdateDeviceList,this,&MainWindow::slotServiceTableUpdate);


    //connect(deviceManagementServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    // connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);

    //vypis stavu testu
    connect(&testDemo,&Vdv301testy::update,this,&MainWindow::testPopulateTestPhases);
    connect(&testSubscribeServer,&Vdv301testy::update,this,&MainWindow::testPopulateTestPhases);

    //jednotliveTesty
    connect(&testSubscribeServer,&TestOdberuServer::signalVymazSeznamOdberatelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotRemoveAllSubscribers);
    connect(&testSubscribeServer,&TestOdberuServer::signalNastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStartDnsSd);
    connect(&testSubscribeServer,&TestOdberuServer::signalZastavCisTimer,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStopTimer);
    connect(&testSubscribeServer,&TestOdberuServer::signalOdesliDataDoPanelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotSendDataToSubscribers);


    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalDumpSubscriberList,&testSubscribeServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&customerInformationService2_2CZ1_0,&HttpService::signalReplyToPostReceived,&testSubscribeServer,&TestOdberuServer::slotVypisOdpovedServeru);

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
    connect(&sqlRopidQuerries,&SqlRopidXmlQueries::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(&sqlRopidQuerries,&SqlRopidXmlQueries::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);

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
    connect(&timerFareZoneChangeDuration,&QTimer::timeout,this,&MainWindow::eventFareZoneChangeHide);
    connect(&timerAfterStopToBetweenStop,&QTimer::timeout,this,&MainWindow::eventAfterStopToBetweenStop);
    connect(&timerDownloadConnections,&QTimer::timeout,this,&MainWindow::slotDownloadConnectionsFromCurrentStop);
    connect(&timerSpecialAnnoucementHide,&QTimer::timeout,this,&MainWindow::evenSpecialAnnouncementHide);
}

void MainWindow::retranslateUi(QString language)
{
    QTranslator translator;

    qApp->removeTranslator(&translator);
    if(translator.load(":/lang_"+language+".qm"))
    {
        qApp->installTranslator(&translator);
        ui->calendarWidget_data_workingDate->setLocale(QLocale::English);
        qDebug()<<"zmena jazyka";
        ui->retranslateUi(this);
    }
    else
    {
        popUpMessage(tr("language file not found"));
    }
}


void MainWindow::startServiceFromList(QVector<CustomerInformationService*> &seznamSluzeb)
{
    if(!seznamSluzeb.isEmpty())
    {
        CustomerInformationService* aktualniSluzba=seznamSluzeb.takeFirst();
        qDebug()<<"v zasobniku zustava sluzeb: "<<seznamSluzeb.count();
        qDebug()<<Q_FUNC_INFO<<" "<<aktualniSluzba->mServiceName<<" "<<aktualniSluzba->version();
        aktualniSluzba->slotStartServer();
    }
}

void MainWindow::slotVdv301ServiceStartResult(QString nastartovanaSluzba)
{
    qDebug()<<Q_FUNC_INFO<<" "<<nastartovanaSluzba;
    startServiceFromList(vektorCis);

}

void MainWindow::loadConstantsFromSettingsFile()
{
    qDebug()<<Q_FUNC_INFO;


    if(settings.value("golemio/adresa").isNull())
    {
        eventAnnouncementToDriver("konfiguracni soubor neexistuje/je vadny");
    }
    else
    {
        qDebug()<<"konfiguracni soubor nacten";
    }
    qDebug()<<" konstanty status "<<settings.status();


    if(settings.value("golemio/datovyZdroj").toString()=="mpvnet")
    {
        useGolemioApi=false;
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
    customerInformationService2_3.setPortNumber(settings.value("customerInformationService2_3/port").toInt());

    ibisIsEnabled=settings.value("ibis/enable").toBool();
    ibisOvladani.setSerialPortName(settings.value("ibis/portName").toString());
    ui->lineEdit_configuration_IbisPort->setText(ibisOvladani.serialPortName());
}





/*!

*/
void MainWindow::testPopulateWindow(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        testDemo.emitujUpdate();
        break;
    case 1:
        testSubscribeServer.emitujUpdate();
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
        testDemo.start();
        break;
    case 1:
        testSubscribeServer.start();
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
        testDemo.stop();
        break;
    case 1:
        testSubscribeServer.stop();
        break;
    default:
        qDebug()<<"test s indexem "<<QString::number(index)<<" neexistuje";
        break;
    }
}


/*!

*/
void MainWindow::startAllVdv301Services()
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
void MainWindow::xmlVdv301UpdateContent()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug()<<"delka seznamu tripu "<<vehicleState.currentVehicleRun.tripList.length();
    if (vehicleState.currentVehicleRun.tripList.isEmpty())
    {
        qDebug()<<"seznam tripu je prazdny";
        return;
    }
    //QDomDocument vstupniDomXmlPrestupy;
    if (vehicleState.showConnections==true)
    {
        slotDownloadConnectionsFromCurrentStop();
        timerDownloadConnections.start();
    }
    else
    {
        timerDownloadConnections.stop();
    }

    QVector<Connection> connectionList;

    xmlVdv301UpdateCis(connectionList,vehicleState);

    ticketValidationService2_3CZ1_0.updateServiceContent(connectionList,vehicleState);
    deviceManagementService1_0.serviceContentUpdate();
}

void MainWindow::slotDownloadConnectionsFromCurrentStop()
{
    qDebug() <<  Q_FUNC_INFO;
    StopPoint aktZastavka=vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint;
    if(useGolemioApi)
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
    if(filterConnections)
    {
        prestupyMpv=xmlMpvParser.vyfiltrujPrestupy(prestupyMpv,vehicleState.currentLine);
    }
    QVector<Connection> prestupy;
    foreach(auto polozka, prestupyMpv)
    {
        prestupy.push_back(polozka.toConnection());
    }


    xmlVdv301UpdateCis(prestupy,vehicleState);
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
    if(filterConnections)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }
    qDebug()<<"pocet Prestupu ve vektoru: "<<prestupy.count();

    xmlVdv301UpdateCis(prestupy,vehicleState);

}


void MainWindow::xmlVdv301UpdateCis(QVector<Connection> prestupy, VehicleState mStavSystemu )
{
    customerInformationService1_0.updateServiceContent(prestupy,mStavSystemu );
    customerInformationService2_2CZ1_0.updateServiceContent(prestupy,mStavSystemu);
    customerInformationService2_3.updateServiceContent(prestupy,mStavSystemu);
}



/*!
 * \brief MainWindow::initializeTheTrip
 * \return
 */
int MainWindow::initializeTheTrip()
{
    qDebug() <<  Q_FUNC_INFO;
    QString textDoPole="";
    int vysledek=0;
    Trip iterSpoj;
    
    if((ui->tableView_lineTrip->model()->rowCount()==0)&&(ui->tableView_trip->model()->rowCount()==0))
    {
        qDebug()<<"neni zvoleny spoj";
        this->vypisDiagnostika("není zvoleno pořadí");
        return 0;
    }
    else
    {
        qDebug()<<"zjisteni zvolene pozice v seznamu"<<vehicleState.currentTripIndex;
        if (vehicleState.currentTripIndex<0)
        {
            this->vypisDiagnostika("není zvolený spoj");
            return 0;
        }
    }


    vysledek=sqlRopidQuerries.stahniSeznamCelySpojTurnus(vehicleState.currentVehicleRun.tripList,vehicleState.currentTripIndex,this->createDataValidityMask());
    qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    if (vehicleState.getCurrentTrip().continuesWithNextTrip==true)
    {
        vysledek=sqlRopidQuerries.stahniSeznamCelySpojTurnus(vehicleState.currentVehicleRun.tripList,vehicleState.currentTripIndex+1,this->createDataValidityMask());
        qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    }

    qDebug()<<"je nacteno "<<vehicleState.currentVehicleRun.tripList.length()<<" spoju";

    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }

    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        return 0;

    }
    xmlVdv301UpdateContent();
    if(this->vehicleState.getCurrentTrip().globalStopPointDestinationList.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        updateDriverDisplay();
        vehicleState.locationState="AtStop";
        ui->pushButton_menu_ride->setChecked(1);
        ui->stackedWidget_palPc->setCurrentWidget(ui->page_ride);
        eventEnterService();
        // mapaVykresleni.vypisGpsDoHtml(stavSystemu.getCurrentTrip().globalniSeznamZastavek,true,true,true,MapaVykresleni::WGS84);
    }
    return 1;
}



void MainWindow::updateVehicleLocationDisplay(QString stav)
{
    qDebug() <<  Q_FUNC_INFO;
    if(stav=="BeforeStop")
    {
        ui->pushButton_ride_beforeStop->setChecked(true);
    }
    if(stav=="AtStop")
    {
        ui->pushButton_ride_atStop->setChecked(true);
    }
    if(stav=="AfterStop")
    {
        ui->pushButton_ride_afterStop->setChecked(true);
    }
    if(stav=="BetweenStop")
    {
        ui->pushButton_ride_betweenStop->setChecked(true);
    }
    ui->label_ride_locationStateIndicator->setText(vehicleState.locationState);
}




/*!
 \fn void MainWindow::initializeSelectionListView()

pripoji se k databazi a naplni okna pro vyber spoju
*/
void MainWindow::initializeSelectionListView()
{
    qDebug() <<  Q_FUNC_INFO;
    sqlRopidQuerries.pripoj();
    
    
    
    ui->listView_lineRun->setModel(&emptyQSqlQueryModel);
    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);
    
    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);

    QSqlQueryModel* modelLinky=sqlRopidQuerries.stahniSeznamLinekModel(this->createDataValidityMask());
    QSqlQueryModel* modelKmenoveLinky=sqlRopidQuerries.stahniSeznamKmenovychLinekModel(this->createDataValidityMask());

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
        
        ui->listView_line->setModel(modelLinky);
        ui->listView_line->setModelColumn(modelLinky->record().indexOf("l.c"));
        
        ui->listView_rootLine->setModel(modelKmenoveLinky);
        ui->listView_rootLine->setModelColumn(modelKmenoveLinky->record().indexOf("l.c"));

        updateCalendar();
    }
    else
    {

        qDebug()<<"chyba nacitani linek";
    }
}



/*!
načte platnost a nastaví rozsahy klikatelných oblastí kalendáře
*/
void MainWindow::updateCalendar()
{
    qDebug() <<  Q_FUNC_INFO;
    if(sqlRopidQuerries.nactiPlatnost(validityFrom,validityTo))
    {
        ui->calendarWidget_data_workingDate->setMinimumDate(validityFrom);
        ui->calendarWidget_data_workingDate->setMaximumDate(validityTo);
    }
    else
    {
        ui->calendarWidget_data_workingDate->setMinimumDate(QDate(1900, 1, 1));
        ui->calendarWidget_data_workingDate->setMaximumDate(QDate(3000, 1, 1));
    }
}


/*!
bezpečně vymaže obsah QListWidget
*/
void MainWindow::truncateQListWidget(QListWidget *vstup)
{
    // https://stackoverflow.com/a/53632933
    vstup->blockSignals(true);
    vstup->clear();
    vstup->blockSignals(false);
}


/*!

*/
void MainWindow::updateDriverDisplay()
{
    qDebug() <<  Q_FUNC_INFO;

    if(this->vehicleState.currentVehicleRun.tripList.length()<=vehicleState.currentTripIndex)
    {
        qDebug()<<"spoj odpovidajici indexu neexistuje";
        return;
    }

    dumpStopsToTable(vehicleState.currentStopIndex0,this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.locationState);
    int delkaGlobalnihoSeznamu= this->vehicleState.countCurrentTripStops();
    int indexZastavky=vehicleState.currentStopIndex0;
    qDebug()<<"delka seznamu spoju "<<this->vehicleState.currentVehicleRun.tripList.length()<<" index "<<vehicleState.currentTripIndex<<" delka globsezzast "<< delkaGlobalnihoSeznamu  << " indexAktZast "<<indexZastavky   ;

    if (indexZastavky>=delkaGlobalnihoSeznamu)
    {
        qDebug()<<"index zastavky je mimo rozsah";
        return;
    }

    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0+1));
    ui->label_ride_currentLineNumber->setText(this->vehicleState.getCurrentTrip().globalStopPointDestinationList.at(vehicleState.currentStopIndex0).line.lineNumber);
    ui->label_ride_currentTripNumber->setText(QString::number(this->vehicleState.getCurrentTrip().idRopid));


    updateVehicleLocationDisplay(vehicleState.locationState);
}





void MainWindow::connectyImport(XmlImportJr *xmlImportJr)
{
    connect(xmlImportJr,&XmlRopidImportStream::resultReady, this, &MainWindow::slotImportFinished);
    connect(xmlImportJr,&XmlRopidImportStream::finished, xmlImportJr, &QObject::deleteLater);
    connect(xmlImportJr,&XmlRopidImportStream::finished, this, &MainWindow::slotImportAktivujTlacitka);

    connect(xmlImportJr,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgress,this,&MainWindow::slotSetProgress);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgressMax,this,&MainWindow::slotSetProgressMax);

    /*

    connect(xmlImportJr,&XmlRopidImportStream::resultReady, this, &MainWindow::handleResultsJr);
    connect(xmlImportJr,&XmlRopidImportStream::finished, xmlImportJr, &QObject::deleteLater);
    connect(xmlImportJr,&XmlRopidImportStream::finished, this, &MainWindow::slotAktivujTlacitka);

    connect(xmlImportJr,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);
*/

}




void MainWindow::slotSetProgress(int hodnota)
{
    ui->progressBar_data_importXml->setValue(hodnota);
    // qDebug()<<QString::number(hodnota)<<"/"<<QString::number(ui->progressBar->maximum());
}


void MainWindow::slotSetProgressMax(int hodnota)
{
    //resetujProgressBar();
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(hodnota);
    ui->progressBar_data_importXml->setMaximum(hodnota);
}

void MainWindow::slotImportFinished()
{
    qDebug() <<  Q_FUNC_INFO;
    this->workingDateFirstDateOfDataValidity();
    this->initializeSelectionListView();
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
int MainWindow::eventArrival()
{
    qDebug() <<  Q_FUNC_INFO;

    vehicleState.doorState="DoorsOpen";

    if (vehicleState.currentStopIndex0<(this->vehicleState.countCurrentTripStops()-1))
    {
        voiceAnnouncer.kompletZastavka(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint,this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0+1].stopPoint);
    }
    else
    {
        voiceAnnouncer.kompletKonecna(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint);
    }



    vehicleState.locationState="AtStop";
    updateDriverDisplay();
    xmlVdv301UpdateContent();

    QVector<QString> poznamky=this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.notesList;
    qDebug()<<"poznamek je tolik: "<<QString::number(poznamky.count());
    foreach(QString poznamka, poznamky)
    {
        eventAnnouncementToDriver(poznamka);
    }

    return 1;
}



/*!

*/
int MainWindow::eventDeparture()
{
    qDebug() <<  Q_FUNC_INFO;

    if(vehicleState.currentStopIndex0==1)
    {
        voiceAnnouncer.kompletOdjezdPrvniZastavka(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint);
    }

    timerAfterStopToBetweenStop.start();


    return 1;
}

void MainWindow::eventAfterStopToBetweenStop()
{
    qDebug() <<  Q_FUNC_INFO;
    if(FareZone::showZoneChangeCheck(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0-1].stopPoint.fareZoneList,this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.fareZoneList))
    {
        qDebug()<<"srovnani pasem zastavek "<<this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0-1].stopPoint.StopName<<" a "<<this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.StopName;
        eventFareZoneChange();
    }
    else
    {
        eventFareZoneChangeHide();
    }
    vehicleState.locationState="BetweenStop";
    updateDriverDisplay();
    xmlVdv301UpdateContent();

}



void MainWindow::dumpSubscribersToTable(QVector<Subscriber> adresy, QTableWidget* tabulka)
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
void MainWindow::dumpSubscribers1_0(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_manual_subscriberList1_0);
}

/*!

*/
void MainWindow::dumpSubscribers2_2CZ(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_manual_subscriberList2_2CZ1_0);
}

void MainWindow::dumpSubscribers2_3(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_manual_subscriberList2_3);
}


/*!

*/
void MainWindow::vypisDiagnostika(QString vstup)
{
    qDebug()<<" MainWindow::vypisDiagnostika "<<vstup;
    ui->label_diagnostika_manual->clear();
    ui->label_diagnostika_manual->setText(vstup);
    ui->statusBar->showMessage(vstup);
    logfile.pridejNaKonecSouboru(logFileQFile,QDateTime::currentDateTime().toString()+" "+ vstup);
}



/*!

*/
void MainWindow::slotVypisSqlVysledek(QString vstup)
{
    ui->label_data_sqlResult->setText(vstup);
}



/*!

*/
void MainWindow::stopServices()
{
    //customerInformationService1_0.
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
void MainWindow::testPopulateTestPhases(QVector<PolozkaTestu> &seznamPolozek)
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
void MainWindow::on_calendarWidget_data_workingDate_selectionChanged()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.referenceDate=ui->calendarWidget_data_workingDate->selectedDate();
    updataWorkingDate();
}



/*!

*/
void MainWindow::on_checkBox_configuration_enableConnections_stateChanged(int arg1)
{
    qDebug()<<Q_FUNC_INFO;
    vehicleState.showConnections=ui->checkBox_configuration_enableConnections->isChecked();
}



void MainWindow::on_checkBox_ride_stopRequested_clicked(bool checked)
{
    vehicleState.isVehicleStopRequested=checked;
    xmlVdv301UpdateContent();
}




void MainWindow::on_listView_line_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    vehicleState.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();
    qDebug()<<"cislo linky:"<<vehicleState.currentLine.c;
    
    
    
    ui->lineEdit_lineNumber->setText(QString::number(vehicleState.currentLine.c ));
    modelConnection=sqlRopidQuerries.stahniSeznamSpojuModel2(vehicleState.currentLine, this->createDataValidityMask());
    qDebug()<<"model size:"<<modelConnection->rowCount()<<" "<<modelConnection->columnCount();
    
    
    modelDoTabulkySeradit(modelConnection,ui->tableView_trip);
    ui->tableView_trip->hideColumn(5);
    ui->tableView_trip->hideColumn(6);
    ui->tableView_trip->hideColumn(7);




}



void MainWindow::on_listView_rootLine_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;

    vehicleState.currentVehicleRun.rootLine.c= index.data(Qt::DisplayRole).toString().toInt();
    
    ui->lineEdit_rootLine->setText(QString::number(vehicleState.currentVehicleRun.rootLine.c));

    QSqlQueryModel* modelPoradi=sqlRopidQuerries.stahniSeznamPoradiModel(vehicleState.currentVehicleRun.rootLine, this->createDataValidityMask());
    
    ui->listView_lineRun->setModel(modelPoradi);
    ui->listView_lineRun->setModelColumn(modelPoradi->record().indexOf("o.p"));
    
    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);
}

void MainWindow::on_listView_lineRun_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    vehicleState.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();
    
    if (ui->listView_lineRun->model()->rowCount()!=0)
    {
        if(index.row()>=0)
        {
            vehicleState.currentVehicleRun.order=index.data(Qt::DisplayRole).toString().toInt();

            /// zakomentovat?
            if (sqlRopidQuerries.vytvorSeznamTurnusSpoju(vehicleState.currentVehicleRun,this->createDataValidityMask())==1)
            {
                qDebug()<<"pocetSpoju: "<<vehicleState.currentVehicleRun.tripList.count();
            }
            else
            {
                qDebug()<<"spoje nenalezeny";
            }

            QSqlQueryModel* modelTurnusSpoj=sqlRopidQuerries.stahniSeznamTurnusSpojuModel(vehicleState.currentVehicleRun, this->createDataValidityMask());
            ui->tableView_lineTrip->setModel(modelTurnusSpoj);
            ui->tableView_lineTrip->resizeColumnsToContents();
        }
    }
}

/*!

*/
void MainWindow::on_pushButton_data_startXmlRopidImport_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    //   emit signalZahajImport(xmlRopidImportStream.vstupniXmlSouborCesta);

    eventExitService();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );


    XmlImportJr *xmlImportJr =  new XmlImportJr();

    xmlImportJr->truncateAll();

    xmlImportJr->vstupniXmlSouborCesta=xmlFilePath;

    connectyImport(xmlImportJr);

    xmlImportJr->start();

    //xmlRopidImportStream.otevriSoubor(xmlRopidImportStream.vstupniXmlSouborCesta);

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
    testDemo.stop();
}


/*!

*/
//tlacitka pro spusteni testu
void MainWindow::on_pushButton_test1_clicked()
{
    testIndex=0;
    testPopulateWindow(testIndex);
}


/*!

*/

void MainWindow::on_pushButton_test2_clicked()
{
    testIndex=1;
    testPopulateWindow(testIndex);
}


/*!

*/
void MainWindow::on_pushButton_test3_clicked()
{
    testIndex=2;
    testPopulateWindow(testIndex);
}


/*!

*/
void MainWindow::on_pushButton_test4_clicked()
{
    testIndex=3;
    testPopulateWindow(testIndex);
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
void MainWindow::on_pushButton_data_selectXmlPath_clicked()
{
    xmlFilePath=openXmlSelectDialogue(xmlFilePath);
    if (xmlFilePath=="")
    {
        ui->pushButton_data_startXmlRopidImport->setDisabled(true);
    }
    else
    {
        ui->pushButton_data_startXmlRopidImport->setDisabled(false);

    }
    setXmlPathLabel();
}


/*!

*/
void MainWindow::on_pushButton_data_today_clicked()
{
    workingDateToday();
}


/*!

*/
void MainWindow::on_pushButton_menu_lineTrip_clicked()
{
    eventExitService();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_lineTrip );

}



void MainWindow::on_pushButton_ride_arrowNextStateSkip_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (vehicleState.currentStopIndex0<(this->vehicleState.countCurrentTripStops()-1))
    {
        vehicleState.currentStopIndex0++;
    }
    else
    {
        this->eventGoToNextTrip();
    }
    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0));
    updateDriverDisplay();
    xmlVdv301UpdateContent();
}


void MainWindow::on_pushButton_menu_specialAnnouncement_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_oznameni);

}


/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_clicked()
{
    vypisDiagnostika(customerInformationService1_0.handleNewSubscriber(Subscriber(ui->lineEdit_manual_subscriberAddress->text(),ui->lineEdit_manual_subscriberStructure->text())));
}



/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_2_clicked()
{
    vypisDiagnostika(customerInformationService2_2CZ1_0.handleNewSubscriber(Subscriber(ui->lineEdit_manual_subscriberAddress->text(),ui->lineEdit_manual_subscriberStructure->text())));
}


void MainWindow::on_pushButton_manual_addsubscriber_3_clicked()
{
    vypisDiagnostika(customerInformationService2_3.handleNewSubscriber(Subscriber(ui->lineEdit_manual_subscriberAddress->text(),ui->lineEdit_manual_subscriberStructure->text())));
}


/*!

*/
void MainWindow::on_pushButton_manual_removeSubscriber_clicked()
{
    if (ui->tableWidget_manual_subscriberList1_0->rowCount()==0)
    {

        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_manual_subscriberList1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrnao");
        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService1_0.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers1_0(customerInformationService1_0.subscriberList);
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
    if (ui->tableWidget_manual_subscriberList2_2CZ1_0->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_manual_subscriberList2_2CZ1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList2_2CZ1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_2CZ1_0.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers2_2CZ(customerInformationService2_2CZ1_0.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


void MainWindow::on_pushButton_manual_removeSubscriber_3_clicked()
{
    if (ui->tableWidget_manual_subscriberList2_3->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_manual_subscriberList2_3->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList2_3->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_3.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers2_3(customerInformationService2_3.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}



void MainWindow::on_pushButton_detection_refresh_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    devMgmtSubscriber.slotUpdateDeviceInfo();
}


void MainWindow::on_pushButton_detection_saveHwConfig_clicked()
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



void MainWindow::on_pushButton_detection_loadHwConfig_clicked()
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
    dumpServicesToTable(devMgmtSubscriber.deviceListDetected, devMgmtSubscriber.deviceListConfigured);
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


void MainWindow::on_pushButton_ride_map_clicked()
{
    mapPlot.seznamMnozin.clear();
    mapPlot.pridejMnozinu(MapaVykresleni::seznamStopPointDestinationToSeznamMapaBod(vehicleState.getCurrentTrip().globalStopPointDestinationList,true),true,false,false,false,MnozinaBodu::WGS84);
    mapPlot.pridejMnozinu(MapaVykresleni::seznamStopPointDestinationToSeznamMapaBod(vehicleState.getCurrentTrip().globalStopPointDestinationList,true),false,false,false,true,MnozinaBodu::WGS84);
    mapPlot.pridejMnozinu(sqlRopidQuerries.vytvorTrajektorii(vehicleState.getCurrentTrip().id,this->createDataValidityMask()),false, true, false,false, MnozinaBodu::J_STSK);

    mapPlot.seznamMnozinDoJson(mapPlot.seznamMnozin, mapPlot.spojDoTabulky( vehicleState.currentTrip));

}



/*!

*/
void MainWindow::on_pushButton_menu_ride_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_ride );

}


/*!

*/
void MainWindow::on_pushButton_manual_truncateCustomXml_clicked()
{
    ui->plainTextEdit_manual_customXml->clear();
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

*/
void MainWindow::on_pushButton_manual_sendCustomXml_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray vysledek2="";
    vysledek2=vysledek2+ui->plainTextEdit_manual_customXml->toPlainText().toUtf8();
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



/*!

*/
void MainWindow::on_pushButton_ride_arrowPreviousStateSkip_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (vehicleState.currentStopIndex0>=2)
    {
        vehicleState.currentStopIndex0--;
    }
    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0));
    updateDriverDisplay();
    xmlVdv301UpdateContent();

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

void MainWindow::on_pushButton_ride_beforeStop_clicked()
{

    vehicleState.locationState="BeforeStop";
    xmlVdv301UpdateContent();
}

/*!

*/
void MainWindow::on_pushButton_ride_atStop_clicked()
{

    eventArrival();

}



/*!

*/
void MainWindow::on_pushButton_ride_afterStop_clicked()
{

    vehicleState.locationState="AfterStop";
    xmlVdv301UpdateContent();
}



/*!

*/
void MainWindow::on_pushButton_ride_betweenStop_clicked()
{

    vehicleState.locationState="BetweenStop";
    xmlVdv301UpdateContent();
}




/*!

*/
void MainWindow::on_pushButton_data_truncate_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    XmlImportJr *xmlImportJr =  new XmlImportJr();

    xmlImportJr->truncateAll();
    xmlImportJr->vacuum();
}


/*!

*/
void MainWindow::on_pushButton_configuration_IbisSendTest_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    // ibisOvladani.dopocetCelni("l006");
}


/*!

*/
void MainWindow::on_pushButton_configuration_IbisSetPort_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.stop();
    ibisOvladani.setSerialPortName(ui->lineEdit_configuration_IbisPort->text());
    ibisOvladani.start();
    ibisOvladani.sendIpisTelegram("l006");
    // ibisOvladani.dopocetKontrolnihoZnaku("aA1 ahoj");
    // ibisOvladani.dopocetKontrolnihoZnaku("v povel v\\");
    // ibisOvladani.dopocetKontrolnihoZnaku("zA povel zA");
    // ibisOvladani.dopocetKontrolnihoZnaku("zN povel zN");
    // ibisOvladani.dopocetKontrolnihoZnaku("xC2");
}


/*!

*/
void MainWindow::on_pushButton_ride_IBIS_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.sendIpisTelegram("xC2");
    ibisOvladani.odesliFrontKomplet("1",this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);
    ibisOvladani.odesliSideKomplet("2",this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);
    ibisOvladani.odesliSideKomplet("3",this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet("<3B>",this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);
    ibisOvladani.odeslikompletBUSEjednoradekAA(this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);
    ibisOvladani.odesliRearKomplet("4",this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.currentStopIndex0);

}


/*!

*/
void MainWindow::on_pushButton_ride_arrowNextState_clicked()
{
    qDebug() <<  Q_FUNC_INFO;


    if (vehicleState.currentStopIndex0<(this->vehicleState.countCurrentTripStops()))
    {
        if((vehicleState.locationState=="AtStop")&&((vehicleState.currentStopIndex0<(vehicleState.countCurrentTripStops()-1) )))
        {
            vehicleState.locationState="AfterStop";
            vehicleState.currentStopIndex0++;
            eventDeparture();
        }
        else
        {
            qDebug()<<"dalsi? index:"<<vehicleState.currentStopIndex0<<" pocetZastavek:"<<vehicleState.countCurrentTripStops();
            if((vehicleState.locationState=="AtStop")&&((vehicleState.currentStopIndex0+1)==vehicleState.countCurrentTripStops()))
            {
                this->eventGoToNextTrip();
            }


            if(vehicleState.locationState=="BeforeStop")
            {
                vehicleState.locationState="AtStop";

                eventArrival();
            }

            if(vehicleState.locationState=="BetweenStop")
            {
                vehicleState.locationState="BeforeStop";
            }

            if(vehicleState.locationState=="AfterStop")
            {
                vehicleState.locationState="BetweenStop";
                eventAfterStopToBetweenStop();
            }
        }
    }


    updateDriverDisplay();
    vehicleState.doorState="AllDoorsClosed";
    // ui->popisek->setText(QString::number(stavSystemu.currentStopIndex0+1));
    xmlVdv301UpdateContent();
}




/*!

*/
void MainWindow::on_pushButton_ride_arrowPreviousState_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (vehicleState.currentStopIndex0>=1)
    {
        if(vehicleState.locationState=="AfterStop")
        {
            vehicleState.locationState="AtStop";
            vehicleState.currentStopIndex0--;
            eventArrival();
        }
        else
        {
            if(vehicleState.locationState=="BetweenStop")
            {vehicleState.locationState="AfterStop";}

            if(vehicleState.locationState=="BeforeStop")
            {vehicleState.locationState="BetweenStop";}

            if(vehicleState.locationState=="AtStop")
            {vehicleState.locationState="BeforeStop";}
        }
        updateDriverDisplay();
    }
    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0));
    xmlVdv301UpdateContent();
}




void MainWindow::on_pushButton_menu2_rezerva_clicked()
{

}



/*!

*/
int MainWindow::on_pushButton_lineTrip_confirm_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.reset();
    vehicleState.doorState="AllDoorsClosed";


    /*
     * odeslani spoje doplneneho na turnus
*/
    
    vehicleState.currentTrip.line.c =ui->lineEdit_lineNumber->text().toInt();
    vehicleState.currentTrip.idRopid=ui->lineEdit_tripNumber->text().toInt();

    int kmenovaLinka=0;;
    int poradi=0;
    int order=0;
    sqlRopidQuerries.najdiTurnusZeSpoje( vehicleState.currentTrip,kmenovaLinka,poradi,order, this->createDataValidityMask() );

    vehicleState.currentStopIndex0=0;
    
    ui->lineEdit_rootLine->setText(QString::number(kmenovaLinka));
    vehicleState.currentVehicleRun.rootLine.c=kmenovaLinka;


    /*
    if (sqlPraceRopid.vytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd() )==1)
    {
        naplnVyberPoradi(seznamObehu);
    }
    */


    vehicleState.currentVehicleRun.order=poradi ;
    if (sqlRopidQuerries.vytvorSeznamTurnusSpoju(vehicleState.currentVehicleRun,this->createDataValidityMask())==1)
    {
        // naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
    }


    Trip hledanySpoj=vehicleState.currentTrip;
    vehicleState.currentTripIndex=sqlRopidQuerries.poziceSpojeNaSeznamu(vehicleState.currentVehicleRun.tripList,hledanySpoj);

    if(! MainWindowPomocne::jeVRozsahu(vehicleState.currentTripIndex,vehicleState.currentVehicleRun.tripList.size(),Q_FUNC_INFO))
    {
        return 0;
    }

    vehicleState.currentTrip=vehicleState.currentVehicleRun.tripList.at(vehicleState.currentTripIndex);
    ui->lineEdit_rootLine->setText(QString::number(vehicleState.currentTrip.line.c));
    ui->lineEdit_rootLineTripNumber->setText(QString::number(vehicleState.currentTrip.idRopid));
    vehicleState.currentLine.lineNumber =ui->lineEdit_rootLine->text();

    vehicleState.currentStopIndex0=0;

    int vysledek=initializeTheTrip();
    if (vysledek==1)
    {
        eventEnterService();
    }
    return vysledek;
}


/*!

*/
int MainWindow::on_pushButton_lineRun_confirm_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.doorState="AllDoorsClosed";
    vehicleState.currentLine.lineNumber =ui->lineEdit_rootLine->text();

    vehicleState.currentStopIndex0=0;

    return initializeTheTrip();
}


/*!

*/
void MainWindow::on_pushButton_menu_vehicleRun_clicked()
{
    eventExitService();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );

}

/*!

*/
void MainWindow::on_pushButton_menu2_quit_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    this->on_pushButton_menu_quit_clicked();
}

void MainWindow::on_pushButton_configuration_setGolemioKey_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    settings.setValue("golemio/apikey",ui->lineEdit_configuration_golemioKey->text());
    golemio.setKlic(settings.value("golemio/apiKey").toByteArray());
}

void MainWindow::on_radioButton_ride_singleDoorOpen_clicked()
{
    vehicleState.doorState="SingleDoorOpen";
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_allDoorsClosed_clicked()
{
    vehicleState.doorState="AllDoorsClosed";
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_doorsOpen_clicked()
{
    vehicleState.doorState="DoorsOpen";
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_singleDoorCloser_clicked()
{
    vehicleState.doorState="SingleDoorClosed";
    xmlVdv301UpdateContent();
}

void MainWindow::on_radioButton_configuration_language_cs_clicked()
{
    retranslateUi("cs");
    settings.setValue("app/language","cs");

}


void MainWindow::on_radioButton_configuration_language_en_clicked()
{
    retranslateUi("en");
    settings.setValue("app/language","en");
}






void MainWindow::on_tableView_trip_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    Trip docasnySpoj;
    
    if (ui->tableView_trip->model()->rowCount()>0)
    {
        if(index.isValid())
        {
            docasnySpoj.id=index.siblingAtColumn(modelConnection->record().indexOf("s.s")).data().toInt();
            docasnySpoj.idRopid=index.siblingAtColumn(modelConnection->record().indexOf("s.c")).data().toInt();
            docasnySpoj.line.lc=index.siblingAtColumn(modelConnection->record().indexOf("l.lc")).data().toInt();
            docasnySpoj.line.c=index.siblingAtColumn(modelConnection->record().indexOf("l.c")).data().toInt();
            QString alias=index.siblingAtColumn(modelConnection->record().indexOf("l.aois")).data().toString();
            if(alias=="")
            {
                docasnySpoj.line.lineName=QString::number(docasnySpoj.line.c );
            }
            else
            {
                docasnySpoj.line.lineName=alias;
            }
            
            
            
            ui->lineEdit_tripNumber->setText(QString::number(docasnySpoj.idRopid));

            vehicleState.currentTrip=docasnySpoj;
            int kmenovaLinka=0;
            int poradi=0;
            int order=0;


            sqlRopidQuerries.najdiTurnusZeSpoje(vehicleState.currentTrip, kmenovaLinka,poradi, order,this->createDataValidityMask());
            qDebug()<<"test spoje do turnusu "<<kmenovaLinka<<"/"<<poradi<<" "<<order;

        }
    }

    qDebug()<<"IDspoje:"<<docasnySpoj.id;
}



void MainWindow::on_tableView_lineTrip_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    if (index.model()->rowCount()!=0)
    {
        qDebug()<<"current item bum";

        vehicleState.currentTrip.line.c=index.siblingAtColumn(0).data().toInt();
        vehicleState.currentTrip.idRopid=index.siblingAtColumn(1).data().toInt();

        vehicleState.currentTripIndex=vehicleState.currentVehicleRun.tripList.indexOf(vehicleState.currentTrip);
        qDebug()<<"index spoje na obehu: "<<QString::number(vehicleState.currentTripIndex)<<" delkaSeznamu: "<<vehicleState.currentVehicleRun.tripList.count();
        qDebug()<<"hodnota polozky"<<QString::number(vehicleState.currentTrip.line.c)<<" spoj:"<<QString::number(vehicleState.currentTrip.idRopid);

        //NUTNE DOPLNIT
        
        ui->lineEdit_rootLine->setText(QString::number(vehicleState.currentTrip.line.c));
        ui->lineEdit_rootLineTripNumber->setText(QString::number(vehicleState.currentTrip.idRopid));
    }
}

void MainWindow::on_tableWidget_specialAnnouncements_cellClicked(int row, int column)
{
    qDebug() <<  Q_FUNC_INFO;
    eventShowAnnoucement(row,konfigurace.specialniHlaseni);
}

void MainWindow::on_tableWidget_ride_stopList_cellClicked(int row, int column)
{
    qDebug()<<"on_tableWidgetNasledujiciZastavky_cellClicked";
    vehicleState.locationState="AtStop";
    ui->pushButton_ride_atStop->setChecked(true);
    vehicleState.currentStopIndex0=row;
    eventArrival();
    updateDriverDisplay();
    vehicleState.doorState="AllDoorsClosed";

    xmlVdv301UpdateContent();
}

/*!

*/
void MainWindow::setXmlPathLabel()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_data_pathContent->setText(xmlFilePath);

}


/*!

*/
QString MainWindow::openXmlSelectDialogue(QString cesta)
{
    qDebug() <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), cesta,
                                                    tr("XML Ropid JŘ (*.xml);;All Files (*)"));
    return fileName;
}





/*!

*/
void MainWindow::updataWorkingDate()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->dateEdit_data_workingDate->setDate(vehicleState.referenceDate);
    ui->calendarWidget_data_workingDate->setSelectedDate(vehicleState.referenceDate);

    qDebug()<<"od "<<validityFrom<<" do "<<validityTo<<" pracovni "<<vehicleState.referenceDate ;
    qDebug()<<"dnu do pracovnihodata "<< vehicleState.referenceDate.daysTo(validityFrom) <<" dnu do zacatku platnosti " << vehicleState.referenceDate.daysTo(validityTo);


    this->createDataValidityMask();
    sqlRopidQuerries.maskaKalendarJizd(this->vehicleState.referenceDate,validityFrom,validityTo);

    initializeSelectionListView();
}

/*!
\brief popis
xxxxxx
*/
void MainWindow::workingDateToday()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.referenceDate=QDate::currentDate();
    updataWorkingDate();
}


/*!

*/
void MainWindow::workingDateFirstDateOfDataValidity()
{
    qDebug() <<  Q_FUNC_INFO;
    updateCalendar();


    vehicleState.referenceDate=validityFrom;
    updataWorkingDate();
}


/*!

*/
void MainWindow::slotAktualizacePracData()
{
    initializeSelectionListView();
}



/*!

*/
QString MainWindow::createDataValidityMask()
{
    qDebug() <<  Q_FUNC_INFO;
    return sqlRopidQuerries.maskaKalendarJizd(vehicleState.referenceDate,validityFrom, validityTo);
}



void MainWindow::dumpStopsToTable(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, QString locationState)
{

    qDebug() <<  Q_FUNC_INFO;
    ui->tableWidget_ride_stopList->setRowCount(0);



    for (int i=0;i<(docasnySeznamZastavek.count());i++)
    {
        QString cisloZastavky = QString::number(i+1);
        QString nazevZastavky2 = docasnySeznamZastavek.at(i).stopPoint.StopName;
        QString odjezdZeZastavky =  sqlRopidQuerries.vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).stopPoint.DepartureTime);
        QString pasma= sqlRopidQuerries.pasmaDoStringu(docasnySeznamZastavek.at(i).stopPoint.fareZoneList,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).stopPoint.onRequest==true)
        {
            znameni="(x)";
        }


        qint32 row;
        QTableWidgetItem *cell;
        row = ui->tableWidget_ride_stopList->rowCount();
        ui->tableWidget_ride_stopList->insertRow(row);

        cell = new QTableWidgetItem(cisloZastavky);
        ui->tableWidget_ride_stopList->setItem(row, 0, cell);

        cell = new QTableWidgetItem(nazevZastavky2);
        ui->tableWidget_ride_stopList->setItem(row, 1, cell);


        cell = new QTableWidgetItem(odjezdZeZastavky);
        ui->tableWidget_ride_stopList->setItem(row, 2, cell);


        cell = new QTableWidgetItem(znameni);
        ui->tableWidget_ride_stopList->setItem(row, 3, cell);

        cell = new QTableWidgetItem(pasma);
        ui->tableWidget_ride_stopList->setItem(row, 4, cell);

        //   ui->tableWidgetNasledujiciZastavky->resizeColumnsToContents();

    }

    int zabarvenySloupec=1;
    int pocetRadkuTabulky=ui->tableWidget_ride_stopList->rowCount();
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
            ui->tableWidget_ride_stopList->item(cisloporadi,zabarvenySloupec)->setBackground(cyan);
        }
        else
        {
            QBrush gray(Qt::gray);
            ui->tableWidget_ride_stopList->item(cisloporadi,zabarvenySloupec)->setBackground(gray);
        }
        ui->tableWidget_ride_stopList->resizeColumnsToContents();
        ui->tableWidget_ride_stopList->resizeRowsToContents();
        ui->tableWidget_ride_stopList->scrollToItem(ui->tableWidget_ride_stopList->item(cisloporadi,0));
    }
}



/*!
 * \brief MainWindow::eventGoToNextTrip
    přepíná na další spoj na turnusu posunem indexů, pokud návazný spoj neexistuje
*/
void MainWindow::eventGoToNextTrip()
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"index "<<vehicleState.currentTripIndex<<" pocetSpoju "<<vehicleState.currentVehicleRun.tripList.count();
    if ((vehicleState.currentTripIndex)<(vehicleState.currentVehicleRun.tripList.count()-1))
    {
        vehicleState.currentTripIndex++;
        vehicleState.currentStopIndex0=0;
        // AktualizaceDispleje();
        initializeTheTrip();
        xmlVdv301UpdateContent();
    }
    else
    {
        qDebug()<<"posledni spoj ze seznamu, nelze se dale posouvat";
    }
}


void MainWindow::eventFareZoneChange()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.showFareZoneChange=true;
    xmlVdv301UpdateContent();
    voiceAnnouncer.kompletZmenaTarifnihoPasma();
    timerFareZoneChangeDuration.start();

}

void MainWindow::eventShowAnnoucement(int index, QVector<AdditionalAnnoucement> seznamHlaseni)
{
    qDebug() <<  Q_FUNC_INFO;

    if((index>=0)&&(index<seznamHlaseni.count()))
    {

        vehicleState.currentSpecialAnnoucement=seznamHlaseni.at(index);
        vehicleState.isSpecialAnnoucementUsed=true;
        //zobraz na panely
        xmlVdv301UpdateContent();
        timerSpecialAnnoucementHide.start();
        //spust hlaseni
        voiceAnnouncer.kompletSpecialniHlaseni(vehicleState.currentSpecialAnnoucement);
    }

}

void MainWindow::eventAnnouncementToDriver(QString poznamka)
{
    qDebug() <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(replaceDriverAnnouncementFormatting(poznamka));
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
    msgBox.setText(replaceDriverAnnouncementFormatting(messageText));
    msgBox.exec();
}

void MainWindow::eventFareZoneChangeHide()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.showFareZoneChange=false;
    xmlVdv301UpdateContent();
}

//není implementováno
void MainWindow::eventFareSystemChangeShow()
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
void MainWindow::eventFareSystemChangeHide()
{
    qDebug() <<  Q_FUNC_INFO;
    /* stavSystemu.zobrazZmenuPasma=false;
   xmlVdv301HromadnyUpdate();
   */
}


void MainWindow::eventEnterService()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->pushButton_menu_ride->setDisabled(false);
}

void MainWindow::eventExitService()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->pushButton_menu_ride->setDisabled(true);
    timerAfterStopToBetweenStop.stop();
    timerDownloadConnections.stop();
    timerFareZoneChangeDuration.stop();
    resetTripList();

    customerInformationService1_0.outOfService();
    customerInformationService2_2CZ1_0.outOfService();
    customerInformationService2_3.outOfService();

    xmlVdv301UpdateContent();
    initializeSelectionListView();
}

void MainWindow::resetTripList()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.reset();
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


void MainWindow::evenSpecialAnnouncementHide()
{
    qDebug() <<  Q_FUNC_INFO;
    vehicleState.isSpecialAnnoucementUsed=false;
    xmlVdv301UpdateContent();
}


void MainWindow::slotServiceTableUpdate()
{
    qDebug()<<Q_FUNC_INFO;
    dumpServicesToTable(devMgmtSubscriber.deviceListDetected, devMgmtSubscriber.deviceListConfigured);
}

void MainWindow::dumpServicesToTable(QVector<DevMgmtPublisherStruct> serviceListDetected, QVector<DevMgmtPublisherStruct> serviceListConfigured)
{
    qDebug() <<  Q_FUNC_INFO;
    // ui->tabulkaSubscriberu->setRowCount(0);
    truncateSubscriberTable(ui->tableWidget_detection_deviceList);


    foreach(DevMgmtPublisherStruct sluzba, serviceListDetected)
    {
        serviceToTable(sluzba);
    }

    foreach(DevMgmtPublisherStruct sluzba, serviceListConfigured)
    {
        if(!sluzba.isInListByIdClass(serviceListDetected))
        {
            serviceToTable(sluzba);
        }

    }
}

void MainWindow::truncateSubscriberTable(QTableWidget *tableWidget)
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
void MainWindow::serviceToTable(DevMgmtPublisherStruct zarizeni)
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

    row = ui->tableWidget_detection_deviceList->rowCount();
    ui->tableWidget_detection_deviceList->insertRow(row);

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
    ui->tableWidget_detection_deviceList->setItem(row, 0, cell);


    cell = new QTableWidgetItem(deviceClass);
    ui->tableWidget_detection_deviceList->setItem(row, 1, cell);

    cell = new QTableWidgetItem(id);
    ui->tableWidget_detection_deviceList->setItem(row, 2, cell);

    cell = new QTableWidgetItem(hostName);
    ui->tableWidget_detection_deviceList->setItem(row, 3, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tableWidget_detection_deviceList->setItem(row, 4, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_detection_deviceList->setItem(row, 5, cell);

    cell = new QTableWidgetItem(sluzbaNazev);
    ui->tableWidget_detection_deviceList->setItem(row, 6, cell);

    cell = new QTableWidgetItem(verze);
    ui->tableWidget_detection_deviceList->setItem(row, 7, cell);

    cell = new QTableWidgetItem(status);
    ui->tableWidget_detection_deviceList->setItem(row, 8, cell);

    ui->tableWidget_detection_deviceList->resizeColumnsToContents();

    qDebug()<<"sluzbaDoTabulky_konec";
}


QString MainWindow::replaceDriverAnnouncementFormatting(QString input)
{
    QString output="";

    qDebug().noquote()<<"retezec pred: "<<input;
    //  vysledek=vstup.replace(QRegExp("a"),"b");



#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //qt5
    QRegExp vyraz=QRegExp("\\\\([^<]*)\\\\");
    vyraz.setMinimal(true);
#else
    //qt6

    QRegularExpression vyraz("\\\\([^<]*)\\\\");

#endif




    output=input.replace(vyraz,"<b>\\1</b>");
    qDebug().noquote()<<"retezec po: "<<output;

    return output;
}





QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}







void MainWindow::on_pushButton_detection_setId_clicked()
{
    int selectedRow=ui->tableWidget_detection_deviceList->selectedItems().first()->row();

    QString newId=ui->tableWidget_detection_deviceList->item(selectedRow,2)->text();
    QString ipAddress=ui->tableWidget_detection_deviceList->item(selectedRow,4)->text();
    QString port=ui->tableWidget_detection_deviceList->item(selectedRow,5)->text();
    devMgmtSubscriber.postSetDeviceConfiguration(QUrl("http://"+ipAddress+":"+port+"/DeviceManagementService/SetDeviceConfiguration"),newId);
}

