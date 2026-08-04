#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>

#include "mainwindowpomocne.h"




//MAIN

Q_LOGGING_CATEGORY(MainWindowLog, "MainWindow")

//koment

MainWindow::MainWindow(QSettings* newQSettings, QWidget *parent) :
    QMainWindow(parent),
    konfigurace(QCoreApplication::applicationDirPath()),
    //  settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat),
    golemio(""), //klic do golemia
    logfile(QCoreApplication::applicationDirPath()),
    //  timeService1_0("TimeService","_ibisip_udp._udp",123,"1.0"),
    logWindow(this),
    avl(12346), //47477
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",47477,"1.0","_ropid_vdv301tester"),
    customerInformationService1_0("CustomerInformationService","_ibisip_http._tcp",47479,"1.0"),
    customerInformationService2_3("CustomerInformationService","_ibisip_http._tcp",47481,"2.3","_ropid_vdv301tester_2_3"),
    //customerInformationService2_2CZ1_0("CustomerInformationService (2)","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    customerInformationService2_3CZ1_0("CustomerInformationService","_ibisip_http._tcp",47482,"2.3CZ1.0","_ropid_vdv301tester_2_3cz1_0"),
    //deviceManagementServiceSubscriber("DeviceManagementService","DeviceStatus","2.2CZ1.0","_ibisip_http._tcp",48477),//puvodni port 48479, novy 59631
    // devMgmtSubscriber("DeviceManagementService","DeviceStatus","1.0","_ibisip_http._tcp",48477),
    //devMgmtSubscriber("DeviceManagementService","DeviceStatus","2.2","_ibisip_http._tcp",48477),
    ticketValidationService2_2("TicketValidationService","_ibisip_http._tcp",47483,"2.2","_fake_ropid_vdv301tester_2_2"),
    devMgmtSubscriber("DeviceManagementService","DeviceStatus","2.3CZ1.0","_ibisip_http._tcp",48477),
    ui(new Ui::MainWindow)
{
    logHandler.setRelay(&relay);
    logHandler.setIncludeContextFileLine(false);
    logHandler.install();
    logHandler.setTimestampFormat(QStringLiteral("dd/MM/yyyy hh:mm:ss"));
    logHandler.setCategoryLevels(QStringLiteral("app.net"), 1, 1, 1, 1);


    ui->setupUi(this);
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    QString loggingRules="";
    loggingRules+="DisplayLabel=false\n";
    loggingRules+="DisplayLabelLcd=false\n";
    loggingRules+="DisplayLabelLcd2_3=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0_Jis=false\n";
    loggingRules+="DisplayLabelLed=false\n";
    loggingRules+="InLineFormatParser=false\n";
    loggingRules+="XmlParser=false\n";
    loggingRules+="XmlParser2_3=false\n";
    loggingRules+="MainWindow=false\n";
    loggingRules+="SvgVykreslovani=false\n";
    loggingRules+="XmlCommon*=false\n";
    loggingRules+="ColorDisplayRules=false\n";
    loggingRules+="ConnectionMPV=false\n";
    loggingRules+="QueueSoundPlayer=false\n";
    loggingRules+="Golemio*=false\n";


    /*
    loggingRules+="DisplayLabel=false\n";
    loggingRules+="DisplayLabelLcd=false\n";
    loggingRules+="DisplayLabelLcd2_3=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0_Jis=false\n";
    loggingRules+="DisplayLabelLed=false\n";
    loggingRules+="InLineFormatParser=false\n";
    loggingRules+="XmlParser=false\n";
    loggingRules+="XmlParser2_3=false\n";
    loggingRules+="MainWindow=false\n";
    loggingRules+="SvgVykreslovani=false\n";
    */

    ui->plainTextEdit_debug_rules->setPlainText(loggingRules);

    QLoggingCategory::setFilterRules(loggingRules);


    settings=newQSettings;

    ui->pushButton_menu_ride->setEnabled(false);
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );
    ui->tabWidget_hlavni->setCurrentWidget(ui->tab_palPC);
    ui->pushButton_menu_vehicleRun->setChecked(true);
    ui->pushButton_data_startXmlRopidImport->setDisabled(true);

    vektorCis.push_back(&customerInformationService1_0);
    vektorCis.push_back(&customerInformationService2_3);
    vektorCis.push_back(&customerInformationService2_3CZ1_0);

    vektorCisPermanent.push_back(&customerInformationService1_0);
    vektorCisPermanent.push_back(&customerInformationService2_3);
    vektorCisPermanent.push_back(&customerInformationService2_3CZ1_0);

    mapPlot.setHtmlResultPath(QCoreApplication::applicationDirPath()+"/mapFiles");
    mapPlot.mapServer.setMapFilesPath(QCoreApplication::applicationDirPath()+"/mapFiles");

    loadConstantsFromSettingsFile();

    QString jazyk=settings->value("app/language").toString();

    qCDebug(MainWindowLog)<<" novy jazyk:"<<jazyk;
    retranslateUi(jazyk);

    if(blockBonjour)
    {
        setWindowTitle(windowTitle()+" | "+tr("režim bez Bonjour"));
    }

    if(ibisIsEnabled)
    {
        ibisOvladani.start();
    }


    devMgmtSubscriber.start();

    //ui->stackedWidget_palPc->setWindowState(Qt::WindowFullScreen);


    //inicializace databaze
    initializeSelectionListView();

    //propojeni vsech slotu
    allConnects();

    on_pushButton_detection_loadHwConfig_clicked();

    startAllVdv301Services();

    //kalendarJizd
    workingDateFirstDateOfDataValidity();

    //cesty souboru
    voiceAnnouncer.setApplicationDirectory(applicationDirectory);
    konfigurace.createDefaultFile();
    konfigurace.openFile();
    
    MainWindowPomocne::naplnTabulkuHlaseni(ui->tableWidget_specialAnnouncements,konfigurace.announcementList);

    logfile.defaultniLog(logFileQFile);
    logfile.novySoubor(logFileQFile);
    logfile.pridejNaKonecSouboru(logFileQFile,QDateTime::currentDateTime().toString()+" program spuštěn");

    //zobrazeni
    setXmlPathLabel();
    ui->statusBar->showMessage("test");

    //inicializace timeru
    timerFareZoneChangeDuration.setSingleShot(true);
    timerFareZoneChangeDuration.setInterval(konfigurace.trvaniZobrazeniPasma);

    timerLineChangeDuration.setSingleShot(true);
    timerLineChangeDuration.setInterval(konfigurace.trvaniZobrazeniPasma);

    timerSpecialAnnoucementHide.setSingleShot(true);
    timerSpecialAnnoucementHide.setInterval(konfigurace.trvaniZobrazeniOznameni);

    timerDownloadConnections.setInterval(konfigurace.intervalStahovaniPrestupu);

    timerAfterStopToBetweenStop.setSingleShot(true);
    timerAfterStopToBetweenStop.setInterval(konfigurace.intervalAfterStopToBetweenStop);

    eventExitService();
}


MainWindow::~MainWindow()
{
    // delete proxyModel;
    modelConnection->deleteLater();
    delete ui;
}


/*!
přesunutí connectů pro větší přehlednost
*/
void MainWindow::allConnects()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    this->dumpSubscribers1_0(customerInformationService1_0.subscriberList);

    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers1_0);
    connect(&customerInformationService1_0,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);
    connect(&customerInformationService2_3,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);
    connect(&customerInformationService2_3CZ1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers2_3CZ1_0);
    connect(&customerInformationService2_3CZ1_0,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);
    connect(&customerInformationService2_3CZ1_0,&HttpService::signalPortUpdate,this,&MainWindow::slotCis2_3CZ1_0PortUpdate);

    connect(&xmlMpvParser,&XmlMpvParser::stazeniHotovo,this,&MainWindow::slotMpvNetReady);
    connect(&golemio,&GolemioDepartureBoardsV2::stazeniHotovo,this,&MainWindow::slotGolemioReady);

    //connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::aktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);
    connect(&devMgmtSubscriber,&IbisIpSubscriber::signalUpdateDeviceList,this,&MainWindow::slotServiceTableUpdate);

    //connect(deviceManagementServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    //connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);

    //vypis stavu testu
    connect(&testDemo,&Vdv301testy::update,this,&MainWindow::testPopulateTestPhases);
    connect(&testSubscribeServer,&Vdv301testy::update,this,&MainWindow::testPopulateTestPhases);

    //jednotliveTesty
    //  connect(&testSubscribeServer,&TestOdberuServer::signalVymazSeznamOdberatelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotRemoveAllSubscribers);
    //  connect(&testSubscribeServer,&TestOdberuServer::signalNastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStartDnsSd);
    //  connect(&testSubscribeServer,&TestOdberuServer::signalZastavCisTimer,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStopTimer);
    //  connect(&testSubscribeServer,&TestOdberuServer::signalOdesliDataDoPanelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotSendDataToSubscribers);

    //   connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalDumpSubscriberList,&testSubscribeServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    //   connect(&customerInformationService2_2CZ1_0,&HttpService::signalReplyToPostReceived,&testSubscribeServer,&TestOdberuServer::slotVypisOdpovedServeru);

    //vypinani sluzeb pomoci prepinacu
    //  connect(ui->radioButton_ON1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpService::slotStartDnsSd);
    //  connect(ui->radioButton_OFF1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpService::slotStop);

    connect(ui->radioButton_ON2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpService::slotStop);

    connect(ui->radioButton_ON3,&QRadioButton::clicked,&ticketValidationService2_2,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF3,&QRadioButton::clicked,&ticketValidationService2_2,&HttpService::slotStop);

    connect(ui->radioButton_ON4,&QRadioButton::clicked,&customerInformationService1_0,&HttpService::slotStartDnsSd);
    connect(ui->radioButton_OFF4,&QRadioButton::clicked,&customerInformationService1_0,&HttpService::slotStop);

    //vypisovani stavovych hlasek do stavoveho radku vespod okna
    connect(&sqlRopidQueries,&SqlRopidXmlQueries::signalErrorMessage,this,&MainWindow::slotVypisSqlVysledek);
    connect(&sqlRopidQueries,&SqlRopidXmlQueries::signalErrorMessage,this,&MainWindow::vypisDiagnostika);

    //prepinani stavu radio prepinacu podle stavu sluzeb
    //   connect(&customerInformationService2_2CZ1_0,&HttpService::signalStav,this,&MainWindow::radio1);
    connect(&deviceManagementService1_0,&HttpService::signalStav,this,&MainWindow::radio2);
    connect(&ticketValidationService2_2,&HttpService::signalStav,this,&MainWindow::radio3);
    connect(&customerInformationService1_0,&HttpService::signalStav,this,&MainWindow::radio4);

    //konfigurace
    connect(&konfigurace,&SpecialAnnouncementParser::signalError,this,&MainWindow::vypisDiagnostika);

    //casovace
    connect(&timerFareZoneChangeDuration,&QTimer::timeout,this,&MainWindow::eventFareZoneChangeHide);
    connect(&timerLineChangeDuration,&QTimer::timeout,this,&MainWindow::eventLineChangeHide);
    connect(&timerAfterStopToBetweenStop,&QTimer::timeout,this,&MainWindow::eventAfterStopToBetweenStop);
    connect(&timerDownloadConnections,&QTimer::timeout,this,&MainWindow::slotDownloadConnectionsFromCurrentStop);
    connect(&timerSpecialAnnoucementHide,&QTimer::timeout,this,&MainWindow::eventSpecialAnnouncementHide);

    //position simulator
    // connect(&trajectoryJumper,&TrajectoryJumper::signalMapaBod,&locationEvents,&LocationEvents::slotGnssUpdate);

    //connect(&trajectoryJumper,&TrajectoryJumper::signalChangeWgs,&avl,&Avl::slotUpdatePosition);
    connect(&trajectoryJumper,&TrajectoryJumper::signalChangeWgs84,this,&MainWindow::slotGnssUpdateWgs84);
    connect(&trajectoryJumper,&TrajectoryJumper::signalChangeSjtsk,this,&MainWindow::slotGnssUpdateSjtsk);


    connect(&gnssSusbcriber,&GnssLocationServiceSubscriberDummy::signalCoordinatesReceived,this,&MainWindow::slotGnssUpdateWgs84);

    //position reader
    connect(&locationEvents,&LocationEvents::signalArrivedAtStop,this,&MainWindow::slotLocationEnterArea);
    connect(&locationEvents,&LocationEvents::signalDepartedStop,this,&MainWindow::slotLocationLeaveArea);
}


QString MainWindow::avlSetGeneral()
{
    avl.setTurnus(vehicleState.currentVehicleRun.rootLine.c,vehicleState.currentVehicleRun.order);
    avl.setEvc(vehicleState.vehicleNumber);

    // avl.setEvents("O");
    // avl.generateJsonMessage();
    // avl.triggerUpdate("O");

    return "";
}

void MainWindow::avlSetStop(StopPointDestination currentStopPointDestination)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    avl.setLine(currentStopPointDestination.line.c);
    avl.setAkt(TypeConvertor::idUidZtoMpvNumber(currentStopPointDestination.stopPoint.idU,currentStopPointDestination.stopPoint.idZ));
    avl.setTakt(TypeConvertor::qTimeToMpvDatetime(QTime::currentTime()));
    avl.setKonc(TypeConvertor::idUidZtoMpvNumber(currentStopPointDestination.destination.idU,currentStopPointDestination.destination.idZ));
    avl.setTjr(TypeConvertor::qTimeToMpvDatetime(currentStopPointDestination.stopPoint.departureToQTime()));
    //  avl.setCoordinates(currentStopPointDestination.stopPoint.lat,currentStopPointDestination.stopPoint.lng);
}



void MainWindow::connectionListToTable(QVector<ConnectionGolemio> connectionList,QTableWidget* tableWidget)
{
    eraseTable(tableWidget);

    foreach(ConnectionGolemio connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}



void MainWindow::connectionToTable(ConnectionGolemio connection, QTableWidget* tableWidget)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QString lineName=connection.routeShortName;
    cell = new QTableWidgetItem(lineName);

    tableWidget->setItem(row, 0, cell);

    QString destinationName=connection.tripHeadsign;
    cell = new QTableWidgetItem(destinationName);
    tableWidget->setItem(row, 1, cell);

    cell = new QTableWidgetItem(connection.departureTimestampMinutes);
    tableWidget->setItem(row, 2, cell);

    cell = new QTableWidgetItem(connection.departureTimestampScheduled.toString("hh:mm") );
    tableWidget->setItem(row, 3, cell);

    cell = new QTableWidgetItem(connection.departureTimestampPredicted.toString("hh:mm") );
    tableWidget->setItem(row, 4, cell);

    tableWidget->resizeColumnsToContents();
}


void MainWindow::connectyImport(XmlImportJr *xmlImportJr)
{
    connect(xmlImportJr,&XmlRopidImportStream::resultReady, this, &MainWindow::slotImportFinished);
    connect(xmlImportJr,&XmlRopidImportStream::finished, xmlImportJr, &QObject::deleteLater);
    connect(xmlImportJr,&XmlRopidImportStream::finished, this, &MainWindow::slotImportAktivujTlacitka);

    connect(xmlImportJr,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgress,this,&MainWindow::slotSetProgress);
    connect(xmlImportJr,&XmlRopidImportStream::signalNastavProgressMax,this,&MainWindow::slotSetProgressMax);
}


/*!

*/
QString MainWindow::createDataValidityMask()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    return sqlRopidQueries.createValidyMaskFromDate(vehicleState.referenceDate,validityFrom, validityTo);
}


QVector<Vdv301DisplayContent> MainWindow::createGlobalDisplayContentOutOfService2_3()
{
    QVector<Vdv301DisplayContent> output;

    Vdv301DisplayContent front;
    front.displayContentType=DisplayContentFront;

    Vdv301Destination frontDestination;
    frontDestination.destinationRef="0";
    frontDestination.destinationNameList<<Vdv301InternationalText("OUT OF SERVICE","cs");

    front.destination=frontDestination;
    output<<front;

    Vdv301DisplayContent side;
    side.displayContentType=DisplayContentSide;
    Vdv301Destination sideDestination;
    sideDestination.destinationRef="0";
    sideDestination.destinationNameList<<Vdv301InternationalText("OUT OF SERVICE","cs");

    side.destination=sideDestination;
    output<<side;

    Vdv301DisplayContent rear;
    rear.displayContentType=DisplayContentRear;
    Vdv301Destination rearDestination;
    rearDestination.destinationRef="0";
    rearDestination.destinationNameList<<Vdv301InternationalText("OUT OF SERVICE","cs");

    rear.destination=rearDestination;

    Vdv301Line rearLine;
    rearLine.lineRef="0";
    rearLine.lineNameList<<Vdv301InternationalText("OUT OF","cs");
    rearLine.lineNameList<<Vdv301InternationalText("SERVICE","cs");
    rear.lineInformation=rearLine;
    output<<rear;

    Vdv301DisplayContent lcd;
    lcd.displayContentType=DisplayContentLcd;
    Vdv301Destination lcdDestination;
    lcdDestination.destinationRef="0";
    lcdDestination.destinationNameList<<Vdv301InternationalText("OUT OF SERVICE","cs");

    lcd.destination=lcdDestination;
    output<<lcd;

    return output;
}

void MainWindow::dumpServicesToTable(QVector<DevMgmtPublisherStruct> serviceListDetected, QVector<DevMgmtPublisherStruct> serviceListConfigured)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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



/*!

*/
void MainWindow::dumpSubscribers1_0(QVector<Subscriber> adresy)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_manual_subscriberList1_0);
}



void MainWindow::dumpSubscribers2_3CZ1_0(QVector<Subscriber> adresy)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_manual_subscriberList2_3CZ1_0);
}



void MainWindow::dumpSubscribersToTable(QVector<Subscriber> adresy, QTableWidget* tabulka)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    tabulka->setRowCount(0);
    qCDebug(MainWindowLog)<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qCDebug(MainWindowLog)<<"vracim 0";
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
        qCDebug(MainWindowLog)<<"vracim 1";
    }
}


void MainWindow::eraseTable(QTableWidget *tableWidget)
{
    //used to erase tablewidgets without program crash due to signals
    //  https://stackoverflow.com/a/31564541
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}

void MainWindow::eventStartVisualAnnoucement(AdditionalAnnoucement announcement)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.specialAnnouncementQueue<<announcement;
    eventAnnouncementContinue();
}


void MainWindow::eventAfterStopToBetweenStop()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.locationState=Vdv301Enumerations::LocationStateBetweenStop;
    if(FareZone::showZoneChangeCheck(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0-1].stopPoint.fareZoneList,this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.fareZoneList))
    {
        qCDebug(MainWindowLog)<<"srovnani pasem zastavek "<<this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0-1].stopPoint.StopName<<" a "<<this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.StopName;
        eventFareZoneChange(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0-1].stopPoint.fareZoneList,this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.fareZoneList);
    }
    else
    {
        eventFareZoneChangeHide();
        xmlVdv301UpdateContent();
    }

    updateDriverDisplay();
}


void MainWindow::eventAnnouncementContinue()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    if(vehicleState.isSpecialAnnoucementUsed)
    {
        // vehicleState.isSpecialAnnoucementUsed=true;
        qCDebug(MainWindowLog)<<"queue is already running";
        qCDebug(MainWindowLog)<<"announcement queue count running"<<vehicleState.specialAnnouncementQueue.count();
    }
    else
    {
        if(!vehicleState.specialAnnouncementQueue.isEmpty())
        {
            qCDebug(MainWindowLog)<<"announcement queue count not running"<<vehicleState.specialAnnouncementQueue.count();
            vehicleState.currentSpecialAnnoucement=vehicleState.specialAnnouncementQueue.first();
            vehicleState.specialAnnouncementQueue.removeFirst();
            timerSpecialAnnoucementHide.setInterval(vehicleState.currentSpecialAnnoucement.duration);
            vehicleState.isSpecialAnnoucementUsed=true;
            timerSpecialAnnoucementHide.start();
        }
        else
        {
            qCDebug(MainWindowLog)<<"announcement queue is empty";
        }
        xmlVdv301UpdateContent();
    }
}

void MainWindow::eventAnnouncementToDriver(QString poznamka)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(replaceDriverAnnouncementFormatting(poznamka));
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
}



/*!

*/

int MainWindow::eventArrival()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventStopTimersRide();

    if(!isInRange(vehicleState.currentStopIndex0,vehicleState.getCurrentTrip().globalStopPointDestinationList.count(),Q_FUNC_INFO ))
    {
        return 0;
    }
    StopPointDestination currentStopPointDestination=this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0];

    vehicleState.secondsDelay=MainWindowPomocne::getSecondsDelayFromStop(currentStopPointDestination.stopPoint.arrivalToQTime(),currentStopPointDestination.stopPoint.departureToQTime());

    avlSetStop(currentStopPointDestination);
    if(!trajectoryJumper.isRunning)
    {
        avl.setCoordinates(currentStopPointDestination.stopPoint.lat,currentStopPointDestination.stopPoint.lng);
    }

    if(avlEnabled)
    {
        avl.triggerUpdate("O");
    }


    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateDoorsOpen;

    if (vehicleState.currentStopIndex0<(this->vehicleState.countCurrentTripStops()-1))
    {
        switch(announcementType)
        {
        case 0:
            voiceAnnouncer.announceThisAndNextStop(currentStopPointDestination.stopPoint,this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0+1].stopPoint);
            break;
        case 1:
            voiceAnnouncer.announceThisStop(currentStopPointDestination.stopPoint);
            break;
        case 2:
            break;
        default:
            break;

        }
    }
    else
    {
        voiceAnnouncer.composeLastStopAnnouncement(currentStopPointDestination.stopPoint);
    }

    vehicleState.locationState=Vdv301Enumerations::LocationStateAtStop;
    updateDriverDisplay();
    if(!handleArrivalNotes(this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.stopNoteList))
    {
        xmlVdv301UpdateContent();
    }
    else
    {
        qCDebug(MainWindowLog) << "used special announcement, not updating again";
    }


    /* deprecated
    QVector<QString> poznamky=this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint.notesList;
    qCDebug(MainWindowLog)<<"poznamek je tolik: "<<QString::number(poznamky.count());

    foreach(QString poznamka, poznamky)
    {
        eventAnnouncementToDriver(poznamka);
    }
*/

    //manual plot of current stop when simulation is not running
    if(!trajectoryJumper.isRunning)
    {
        //   trajectoryJumper.gnssWebSockerServer.setData(currentStopPointDestination.stopPoint.lat,currentStopPointDestination.stopPoint.lng,MnozinaBodu::WGS84, trajectoryJumper.centerMap);
    }

    locationEvents.expectedStopPointDestination=currentStopPointDestination;
    return 1;
}



/*!

*/
int MainWindow::eventDeparture()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if((vehicleState.currentStopIndex0+1)>=this->vehicleState.getCurrentTrip().globalStopPointDestinationList.count())
    {
        qCDebug(MainWindowLog)<<"departure from last stop";
        eventDepartureFromLastStop();
        return 0;
    }
    else
    {
        eventStopTimersRide();
        vehicleState.locationState=Vdv301Enumerations::LocationStateAfterStop;

        StopPointDestination departingFromStopPointDestination=this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0];


        vehicleState.currentStopIndex0++;

        StopPointDestination currentStopPointDestination=this->vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0];
        locationEvents.expectedStopPointDestination=currentStopPointDestination;
        avlSetStop(currentStopPointDestination);
        avl.triggerUpdate("O");

        vehicleState.secondsDelay=MainWindowPomocne::getSecondsDelayFromStop(currentStopPointDestination.stopPoint.departureToQTime(),currentStopPointDestination.stopPoint.arrivalToQTime());

        if(!handleDepartureNotes(departingFromStopPointDestination.stopPoint.stopNoteList))
        {
            xmlVdv301UpdateContent();
        }
        else
        {
            qCDebug(MainWindowLog) << "used special announcement, not updating again";
        }




        updateDriverDisplay();

        switch(announcementType)
        {
        case 0:
        {
            if(vehicleState.currentStopIndex0==1)
            {
                voiceAnnouncer.composeFirstStopDeparture(currentStopPointDestination.stopPoint);
            }
        }
        break;
        case 1:
            voiceAnnouncer.announceNextStop(currentStopPointDestination.stopPoint);

            break;
        case 2:
            break;
        default:
            break;

        }
        //timerAfterStopToBetweenStop.start(); //disabled due to possible crashes caused by this
    }

    return 1;
}

void MainWindow::eventDepartureFromLastStop()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    popUpMessage("departure from last stop");
}


void MainWindow::eventEnterService()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->pushButton_menu_ride->setDisabled(false);
    locationEvents.expectedStopPointDestination=vehicleState.getCurrentTrip().globalStopPointDestinationList[vehicleState.currentStopIndex0];
    xmlVdv301UpdateContent();
    avlSetGeneral();

    if(avlEnabled)
    {
        avl.timerStart();
    }
}


void MainWindow::eventExitService()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    ui->pushButton_menu_ride->setDisabled(true);
    trajectoryJumper.stop();
    timerAfterStopToBetweenStop.stop();
    timerDownloadConnections.stop();
    timerFareZoneChangeDuration.stop();
    avl.timerStop();
    resetTripList();

    globalDisplayContentList2_3CZ1_0=createGlobalDisplayContentOutOfService2_3();

    xmlVdv301UpdateContent();
    initializeSelectionListView();
}


/*!
 * \brief MainWindow::eventGoToNextTrip
    přepíná na další spoj na turnusu posunem indexů, pokud návazný spoj neexistuje
*/


//není implementováno
void MainWindow::eventFareSystemChangeHide()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    /* stavSystemu.zobrazZmenuPasma=false;
   xmlVdv301HromadnyUpdate();
   */
}


//není implementováno
void MainWindow::eventFareSystemChangeShow()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    /*stavSystemu.zobrazZmenuPasma=true;
    xmlVdv301HromadnyUpdate();

    timerTrvaniZmenyPasma->setInterval(10000);
    timerTrvaniZmenyPasma->setSingleShot(true);
    timerTrvaniZmenyPasma->start();
    */
}

void MainWindow::eventFareZoneChange(QString zoneFrom, QString zoneTo)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    vehicleState.showFareZoneChange=true;

    QString fareZoneChangeText=R"(
        <font size="90"><color fg="#ffffff"><b>Prosím pozor! Změna tarifního pásma.</b></color></font><br>
        <font size="68"><color fg="#969696">Attention please! Change of fare zone.</color></font>
    )";

    AdditionalAnnoucement fareZoneChangeAnnouncement;
    fareZoneChangeAnnouncement.text=fareZoneChangeText;
    fareZoneChangeAnnouncement.type="FareZoneChange";
    fareZoneChangeAnnouncement.changeFrom=zoneFrom;
    fareZoneChangeAnnouncement.changeTo=zoneTo;
    fareZoneChangeAnnouncement.duration=konfigurace.trvaniZobrazeniPasma;
    eventStartVisualAnnoucement(fareZoneChangeAnnouncement);

    //  xmlVdv301UpdateContent();
    voiceAnnouncer.composeFareZoneChange();

    timerFareZoneChangeDuration.start();
}


void MainWindow::eventFareZoneChange(QVector<FareZone> fareZoneListFrom, QVector<FareZone> fareZoneListTo)
{
    eventFareZoneChange(FareZone::fareZoneListToString(FareZone::filterZonesFromSystem(fareZoneListFrom,"PID"),","),FareZone::fareZoneListToString(FareZone::filterZonesFromSystem(fareZoneListTo,"PID"),","));
}

void MainWindow::eventFareZoneChangeHide()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.showFareZoneChange=false;
    //  eventAnnouncementContinue();
    // xmlVdv301UpdateContent();
}

void MainWindow::eventGoToNextTrip()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    qCDebug(MainWindowLog)<<"index "<<vehicleState.currentTripIndex<<" pocetSpoju "<<vehicleState.currentVehicleRun.tripList.count();
    if ((vehicleState.currentTripIndex)<(vehicleState.currentVehicleRun.tripList.count()-1))
    {
        QString lineFrom="";
        QString lineTo="";


        if(!vehicleState.getCurrentTrip().globalStopPointDestinationList.isEmpty())
        {
            lineFrom=vehicleState.getCurrentTrip().globalStopPointDestinationList.last().line.lineName;
        }

        bool doEventLineChange=false;
        if(vehicleState.getCurrentTrip().continuesWithNextTrip)
        {
            doEventLineChange=true;

        }

        vehicleState.currentTripIndex++;
        vehicleState.currentStopIndex0=0;

        if(!vehicleState.getCurrentTrip().globalStopPointDestinationList.isEmpty())
        {
            lineTo=vehicleState.getCurrentTrip().globalStopPointDestinationList.first().line.lineName;
        }

        if(doEventLineChange)
        {
            eventLineChange(lineFrom,lineTo);
        }
        /*
        lineFrom=vehicleState.getCurrentTrip().globalStopPointDestinationList.last().line.lineName;

        //vehicleState.currentTrip=vehicleState.getCurrentTrip();
        if(vehicleState.currentTrip.globalStopPointDestinationList.isEmpty())
        {
            qCDebug(MainWindowLog)<<"globalStopPointDestinationList is empty";
        }
        else
        {
            lineTo=vehicleState.getCurrentTrip().globalStopPointDestinationList.first().line.lineName;
        }

        // AktualizaceDispleje();
*/
        
        initializeTheTrip();
        //xmlVdv301UpdateContent(); initialize the trip already contains update content
    }
    else
    {
        qCDebug(MainWindowLog)<<"posledni spoj ze seznamu, nelze se dale posouvat";
    }
}

void MainWindow::eventLineChange(QString lineFrom, QString lineTo)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    QString lineChangeText=R"(
        <font size="90"><color fg="#ffffff"><b>Prosím pozor! Změna čísla linky.</b></color></font><br>
        <font size="72"><color fg="#969696">Attention please! Line number change.</color></font>
    )";

    //values are a mock-up at the moment
    AdditionalAnnoucement lineChangeAnnouncement;
    lineChangeAnnouncement.text=lineChangeText;
    lineChangeAnnouncement.type="LineChange";
    lineChangeAnnouncement.changeFrom=lineFrom;
    lineChangeAnnouncement.changeTo=lineTo;
    lineChangeAnnouncement.duration=konfigurace.trvaniZobrazeniPasma;
    eventStartVisualAnnoucement(lineChangeAnnouncement);

    //  xmlVdv301UpdateContent();
    //voiceAnnouncer.kompletZmenaTarifnihoPasma();

    //  timerLineChangeDuration.start();
}

void MainWindow::eventLineChangeHide()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    // now handled as an announcement
}

void MainWindow::eventShowManualAnnoucementFromList(int index, QVector<AdditionalAnnoucement> additionalAnnouncementList)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if((index>=0)&&(index<additionalAnnouncementList.count()))
    {
        eventStartWholeAnnouncement(additionalAnnouncementList.at(index));
    }
}

void MainWindow::eventStartWholeAnnouncement(AdditionalAnnoucement additionalAnnouncement)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    voiceAnnouncer.composeSpecialAnnouncement(additionalAnnouncement);
    eventStartVisualAnnoucement(additionalAnnouncement);
}


void MainWindow::eventStartNoteAnnoucement(StopNote stopNote)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;


    AdditionalAnnoucement additionalAnnouncement;
    additionalAnnouncement.duration=10000;
    if(!stopNote.text.isEmpty())
    {
        if(stopNote.text.length()>128)
        {
            //long text small font
            additionalAnnouncement.text=AdditionalAnnoucement::formatText(stopNote.lcdText,65);
            additionalAnnouncement.duration=20000;
        }
        else
        {
            //short text bigger font
            additionalAnnouncement.text=AdditionalAnnoucement::formatText(stopNote.lcdText,85);
        }
    }

    //additionalAnnouncement.text=stopNote.lcdText;
    additionalAnnouncement.icon="<icon type=\"c_Info\">[i]</icon>";
    if(!stopNote.soundName.isEmpty())
    {
        additionalAnnouncement.mp3.append(stopNote.soundName+".mp3");
    }

    eventStartWholeAnnouncement(additionalAnnouncement);

    /*
    if(!additionalAnnouncement.text.isEmpty())
    {
        eventStartVisualAnnoucement(additionalAnnouncement);
    }
*/

    if(stopNote.speakerDriver)
    {

    }
    if(stopNote.speakerInside)
    {

    }
    if(stopNote.speakerOutside)
    {

    }



}



void MainWindow::eventSpecialAnnouncementHide()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.isSpecialAnnoucementUsed=false;
    eventAnnouncementContinue();
    //xmlVdv301UpdateContent();
}



void MainWindow::eventStopTimersRide()
{
    timerAfterStopToBetweenStop.stop();

    timerFareZoneChangeDuration.stop();
    vehicleState.showFareZoneChange=false;

    timerSpecialAnnoucementHide.stop();
    vehicleState.isSpecialAnnoucementUsed=false;
}


bool MainWindow::handleArrivalNotes(QVector<StopNote> stopNoteList)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    bool usedAnnouncement=false;
    foreach(StopNote note, stopNoteList)
    {
        if(note.activateOnArrival)
        {
            eventStartNoteAnnoucement(note);
            usedAnnouncement=true;
            if(note.showToDriver)
            {
                eventAnnouncementToDriver(note.text);
            }
        }

    }
    return usedAnnouncement;
}

bool MainWindow::handleDepartureNotes(QVector<StopNote> stopNoteList)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    bool usedAnnouncement=false;
    foreach(StopNote note, stopNoteList)
    {
        if(note.activateOnDeparture)
        {
            // eventAnnouncementToDriver("departure "+note.text);
            eventStartNoteAnnoucement(note);
            usedAnnouncement=true;
            if(note.showToDriver)
            {
                eventAnnouncementToDriver(note.text);
            }
        }
    }
    return usedAnnouncement;
}


void MainWindow::infoTextListToTable(QVector<GolemioInfotext> infotextList,QTableWidget* tableWidget)
{
    eraseTable(tableWidget);

    foreach(GolemioInfotext infoText, infotextList)
    {
        infoTextToTable(infoText,tableWidget);
    }
}


void MainWindow::infoTextToTable(GolemioInfotext golemioInfotext, QTableWidget* tableWidget)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    cell = new QTableWidgetItem(GolemioInfotext::displayTypeToQString(golemioInfotext.display_type));
    tableWidget->setItem(row, 0, cell);

    cell = new QTableWidgetItem(golemioInfotext.text);
    tableWidget->setItem(row, 1, cell);

    cell = new QTableWidgetItem(golemioInfotext.text_en);
    tableWidget->setItem(row, 3, cell);
    /*
    cell = new QTableWidgetItem(golemioInfotext.valid_from.toString("" .departureTimestampScheduled.toString("hh:mm") );
    tableWidget->setItem(row, 2, cell);

    cell = new QTableWidgetItem(golemioInfotext.departureTimestampPredicted.toString("hh:mm") );
    tableWidget->setItem(row, 3, cell);
*/
    tableWidget->resizeColumnsToContents();
}




/*!
 * \brief MainWindow::initializeTheTrip
 * \return
 */
int MainWindow::initializeTheTrip()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    QString textDoPole="";
    int vysledek=0;
    Trip iterSpoj;

    qCDebug(MainWindowLog) <<" vehicleState.currentTripIndex "<<vehicleState.currentTripIndex;

    if((ui->tableView_lineTrip->model()->rowCount()==0)&&(ui->tableView_trip->model()->rowCount()==0))
    {
        qCDebug(MainWindowLog)<<"neni zvoleny spoj";
        this->vypisDiagnostika("není zvoleno pořadí");
        return 0;
    }
    else
    {
        qCDebug(MainWindowLog)<<"zjisteni zvolene pozice v seznamu"<<vehicleState.currentTripIndex;
        if (vehicleState.currentTripIndex<0)
        {
            this->vypisDiagnostika("není zvolený spoj");
            return 0;
        }
    }


    vysledek=sqlRopidQueries.getVehicleRunStops(vehicleState.currentVehicleRun.tripList,vehicleState.currentTripIndex,this->createDataValidityMask());
    qCDebug(MainWindowLog)<<"nacetl jsem spoj s vysledkem "<<vysledek;


    if (vehicleState.getCurrentTrip().continuesWithNextTrip)
    {
        vysledek=sqlRopidQueries.getVehicleRunStops(vehicleState.currentVehicleRun.tripList,vehicleState.currentTripIndex+1,this->createDataValidityMask());
        if(vysledek)
        {
            qCDebug(MainWindowLog)<<"nacetl jsem spoj s vysledkem "<<vysledek;
        }
        else
        {
            qCDebug(MainWindowLog)<<"following trip not loaded";
            vysledek=1;
        }
    }


    qCDebug(MainWindowLog)<<"je nacteno "<<vehicleState.currentVehicleRun.tripList.length()<<" spoju";

    if (vysledek==2)
    {
        qCDebug(MainWindowLog)<<"existuje navazujici spoj";
    }

    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        return 0;

    }
    globalDisplayContentList2_3CZ1_0.clear();

    //   xmlVdv301UpdateContent();
    if(this->vehicleState.getCurrentTrip().globalStopPointDestinationList.empty()==1)
    {
        qCDebug(MainWindowLog)<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        updateDriverDisplay();
        vehicleState.locationState=Vdv301Enumerations::LocationStateAtStop;
        ui->pushButton_menu_ride->setChecked(1);
        ui->stackedWidget_palPc->setCurrentWidget(ui->page_ride);
        eventEnterService();
        // mapaVykresleni.vypisGpsDoHtml(stavSystemu.getCurrentTrip().globalniSeznamZastavek,true,true,true,MapaVykresleni::WGS84);
    }
    return 1;
}




/*!
 \fn void MainWindow::initializeSelectionListView()

pripoji se k databazi a naplni okna pro vyber spoju
*/
void MainWindow::initializeSelectionListView()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    sqlRopidQueries.initialize();

    ui->listView_lineRun->setModel(&emptyQSqlQueryModel);
    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);

    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);

    QSqlQueryModel* modelLinky=sqlRopidQueries.getLineListModel(this->createDataValidityMask());
    QSqlQueryModel* modelKmenoveLinky=sqlRopidQueries.getRootLineListModel(this->createDataValidityMask());

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
        qCDebug(MainWindowLog)<<"chyba nacitani linek";
    }
}




int MainWindow::isInRange(int index, int valueCount, QString functionName)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    if((index<valueCount)&&(index>=0))
    {
        return 1;
    }
    else
    {
        QString errorText="value "+QString::number(index)+" is out of range "+ QString::number(valueCount)+" "+functionName;
        popUpMessage(errorText);

        qCDebug(MainWindowLog)<<errorText;

        return 0;
    }
}


void MainWindow::loadConstantsFromSettingsFile()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    if(settings->value("golemio/adresa").isNull())
    {
        eventAnnouncementToDriver("konfiguracni soubor neexistuje/je vadny");
    }
    else
    {
        qCDebug(MainWindowLog)<<"konfiguracni soubor nacten";
    }
    qCDebug(MainWindowLog)<<" konstanty status "<<settings->status();

    if(settings->value("golemio/datovyZdroj").toString()=="mpvnet")
    {
        useGolemioApi=false;
    }
    golemio.setKey(settings->value("golemio/apiKey").toByteArray());
    ui->lineEdit_configuration_golemioKey->setText(settings->value("golemio/apiKey").toByteArray());
    golemio.setAddress(settings->value("golemio/adresa").toString());
    vehicleState.showConnections=settings->value("golemio/enabled").toBool();
    ui->checkBox_configuration_enableConnections->setChecked(vehicleState.showConnections);

    vehicleState.vehicleNumber=settings->value("vehicleProperties/vehicleRef").toInt();
    ui->lineEdit_vehicleRef->setText(QString::number(vehicleState.vehicleNumber));

    if(settings->value("vehicleProperties/vehicleMode").toString()!="")
    {
        vehicleState.vehicleMode=settings->value("vehicleProperties/vehicleMode").toString();
    }

    if(settings->value("vehicleProperties/vehicleSubMode").toString()!="")
    {
        vehicleState.vehicleSubMode=settings->value("vehicleProperties/vehicleSubMode").toString();
    }


    setVehicleTypeFromLineType=settings->value("vehicleProperties/overrideByLineType").toBool();
    ui->checkBox_vechicleTypeFromLine->setChecked(setVehicleTypeFromLineType);

    blockBonjour=settings->value("app/blockBonjour").toBool();

    ui->label_build->setText(textVerze());
    ui->label_build->setTextInteractionFlags(Qt::TextSelectableByMouse);

    golemio.setParameters(settings->value("golemio/parametry").toString());

    deviceManagementService1_0.setDeviceName(settings->value("deviceManagementService1_0/deviceName").toString());
    deviceManagementService1_0.setDeviceManufacturer(settings->value("deviceManagementService1_0/deviceManufacturer").toString());
    deviceManagementService1_0.setDeviceSerialNumber(settings->value("deviceManagementService1_0/deviceSerialNumber").toString());
    deviceManagementService1_0.setDeviceClass(settings->value("deviceManagementService1_0/deviceClass").toString());
    deviceManagementService1_0.setDeviceId(settings->value("deviceManagementService1_0/deviceId").toString());
    deviceManagementService1_0.setSwVersion(textVerze());
    deviceManagementService1_0.slotDataUpdate();
    deviceManagementService1_0.blockBonjour=blockBonjour;
    deviceManagementService1_0.setPortNumber(settings->value("deviceManagementService1_0/port").toInt() ); //47477

    customerInformationService1_0.setPortNumber(settings->value("customerInformationService1_0/port").toInt() );
    customerInformationService2_3.setPortNumber(settings->value("customerInformationService2_3/port").toInt());
    customerInformationService2_3CZ1_0.setPortNumber(settings->value("customerInformationService2_3CZ1_0/port").toInt());

    devMgmtSubscriber.blockBonjour=blockBonjour;

    ibisIsEnabled=settings->value("ibis/enable").toBool();
    ibisOvladani.setSerialPortName(settings->value("ibis/portName").toString());
    ui->lineEdit_configuration_IbisPort->setText(ibisOvladani.serialPortName());

    ui->checkBox_configuration_logToFile->setChecked(settings->value("debug/logToFile").toBool());

    xmlFilePath=settings->value("data/xmlPath").toString();
    ui->label_data_pathContent->setText(xmlFilePath);
    ui->pushButton_data_startXmlRopidImport->setEnabled(!xmlFilePath.isEmpty());

    trajectoryJumper.centerMap=settings->value("locationSimulator/centerMap").toBool();
    ui->checkBox_positionCenterMap->setChecked(trajectoryJumper.centerMap);

    trajectoryJumper.stopAtStops=settings->value("locationSimulator/stopAtStops").toBool();
    ui->checkBox_positionStopAtStops->setChecked(trajectoryJumper.stopAtStops);

}


void MainWindow::modelDoTabulkySeradit(QSqlQueryModel* modelInput,QTableView* tableView)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    QStringListModel emptyModel;
    if(modelInput==NULL)
    {
        qCDebug(MainWindowLog)<<"model je prazdny";
        tableView->setModel(&emptyModel);
        return;
    }
    qCDebug(MainWindowLog)<<"model size:"<<modelInput->rowCount()<<" "<<modelInput->columnCount();

    while ( modelInput->canFetchMore())
    {
        modelInput->fetchMore();
    }

    if(modelInput->rowCount()==0)
    {
        tableView->setModel(&emptyModel);
        return;
    }

    proxyModel.setSourceModel(modelInput);

    tableView->setModel(&proxyModel);
    tableView->show();
    tableView->resizeColumnsToContents();
    connect(tableView->horizontalHeader(),SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),tableView,SLOT(sortByColumn(int,Qt::SortOrder)));
    int pocet= proxyModel.rowCount();
    qCDebug(MainWindowLog)<<"pocet vysledku: "<<QString::number(pocet);
}



/*!

*/
void MainWindow::on_calendarWidget_data_workingDate_selectionChanged()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.referenceDate=ui->calendarWidget_data_workingDate->selectedDate();
    updataWorkingDate();
}


void MainWindow::on_checkBox_avlRelay_stateChanged(int arg1)
{
    avlEnabled=arg1;

    if(avlEnabled)
    {
        avl.timerStart();
    }
    else
    {
        avl.timerStop();
    }
}


/*!

*/
void MainWindow::on_checkBox_configuration_enableConnections_stateChanged(int arg1)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    vehicleState.showConnections=ui->checkBox_configuration_enableConnections->isChecked();
    settings->setValue("golemio/enabled",vehicleState.showConnections);
}

void MainWindow::on_checkBox_configuration_logToFile_stateChanged(int arg1)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    settings->setValue("debug/logToFile",arg1);
}

void MainWindow::on_checkBox_positionCenterMap_stateChanged(int arg1)
{
    trajectoryJumper.centerMap=arg1;
    settings->setValue("locationSimulator/centerMap",trajectoryJumper.centerMap);
}


void MainWindow::on_checkBox_positionStopAtStops_stateChanged(int arg1)
{
    trajectoryJumper.stopAtStops=arg1;
    settings->setValue("locationSimulator/stopAtStops",trajectoryJumper.stopAtStops);
}


void MainWindow::on_checkBox_ride_stopRequested_clicked(bool checked)
{
    vehicleState.isVehicleStopRequested=checked;
    xmlVdv301UpdateContent();
}


void MainWindow::on_checkBox_vechicleTypeFromLine_stateChanged(int arg1)
{
    setVehicleTypeFromLineType=arg1;
    settings->setValue("vehicleProperties/overrideByLineType",setVehicleTypeFromLineType);
}


void MainWindow::on_listView_lineRun_clicked(const QModelIndex &index)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    vehicleState.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();

    if (ui->listView_lineRun->model()->rowCount()!=0)
    {
        if(index.row()>=0)
        {
            vehicleState.currentVehicleRun.order=index.data(Qt::DisplayRole).toString().toInt();

            /// zakomentovat?
            if (sqlRopidQueries.getTripListFromVehicleRun(vehicleState.currentVehicleRun,this->createDataValidityMask())==1)
            {
                qCDebug(MainWindowLog)<<"pocetSpoju: "<<vehicleState.currentVehicleRun.tripList.count();
            }
            else
            {
                qCDebug(MainWindowLog)<<"spoje nenalezeny";
            }

            QSqlQueryModel* modelTurnusSpoj=sqlRopidQueries.getTripListFromVehicleRunModel(vehicleState.currentVehicleRun, this->createDataValidityMask());
            ui->tableView_lineTrip->setModel(modelTurnusSpoj);

            ui->tableView_lineTrip->hideColumn(6);
            ui->tableView_lineTrip->hideColumn(7);

            ui->tableView_lineTrip->resizeColumnsToContents();
        }
    }
}




void MainWindow::on_listView_line_clicked(const QModelIndex &index)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    vehicleState.currentLine.c=index.data(Qt::DisplayRole).toString().toInt();
    qCDebug(MainWindowLog)<<"cislo linky:"<<vehicleState.currentLine.c;

    //  ui->lineEdit_lineNumber->setText(QString::number(vehicleState.currentLine.c ));
    modelConnection=sqlRopidQueries.getLineStopListModel(vehicleState.currentLine, this->createDataValidityMask());
    qCDebug(MainWindowLog)<<"model size:"<<modelConnection->rowCount()<<" "<<modelConnection->columnCount();

    modelDoTabulkySeradit(modelConnection,ui->tableView_trip);
    ui->tableView_trip->hideColumn(5);
    ui->tableView_trip->hideColumn(6);
    ui->tableView_trip->hideColumn(7);
}


void MainWindow::on_listView_rootLine_clicked(const QModelIndex &index)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    vehicleState.currentVehicleRun.rootLine.c= index.data(Qt::DisplayRole).toString().toInt();

    // ui->lineEdit_rootLine->setText(QString::number(vehicleState.currentVehicleRun.rootLine.c));

    QSqlQueryModel* modelPoradi=sqlRopidQueries.getVehicleRunListModel(vehicleState.currentVehicleRun.rootLine, this->createDataValidityMask());

    ui->listView_lineRun->setModel(modelPoradi);
    ui->listView_lineRun->setModelColumn(modelPoradi->record().indexOf("o.p"));

    ui->tableView_lineTrip->setModel(&emptyQSqlQueryModel);
}

/*!

*/
void MainWindow::on_pushButton_configuration_IbisSetPort_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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

void MainWindow::on_pushButton_configuration_setGolemioKey_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    settings->setValue("golemio/apiKey",ui->lineEdit_configuration_golemioKey->text());
    golemio.setKey(settings->value("golemio/apiKey").toByteArray());
}

/*!

*/
void MainWindow::on_pushButton_ride_IBIS_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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
void MainWindow::on_pushButton_data_startXmlRopidImport_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventExitService();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );

    QPointer<XmlImportJr> xmlImportJr =  new XmlImportJr();
    xmlImportJr->truncateAll();
    xmlImportJr->vstupniXmlSouborCesta=xmlFilePath;
    settings->setValue("data/xmlPath",xmlFilePath);
    connectyImport(xmlImportJr);
    xmlImportJr->start();
}



/*!

*/
void MainWindow::on_pushButton_data_truncate_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    XmlImportJr xmlImportJr;
    xmlImportJr.truncateAll();
    xmlImportJr.sqLiteZaklad.vacuum();
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


void MainWindow::on_pushButton_detection_setId_clicked()
{
    int selectedRow=ui->tableWidget_detection_deviceList->selectedItems().first()->row();

    QString newId=ui->tableWidget_detection_deviceList->item(selectedRow,2)->text();
    QString ipAddress=ui->tableWidget_detection_deviceList->item(selectedRow,4)->text();
    QString port=ui->tableWidget_detection_deviceList->item(selectedRow,5)->text();
    devMgmtSubscriber.postSetDeviceConfiguration(QUrl("http://"+ipAddress+":"+port+"/DeviceManagementService/SetDeviceConfiguration"),newId);
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
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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
        vypisDiagnostika("list is empty");
        return;
    }

    if (ui->tableWidget_manual_subscriberList1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nothing selected");
        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService1_0.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers1_0(customerInformationService1_0.subscriberList);
        vypisDiagnostika("removed");
    }
    else
    {
        vypisDiagnostika("could not remove");
    }
}




void MainWindow::on_pushButton_manual_removeSubscriber_3_clicked()
{
    if (ui->tableWidget_manual_subscriberList2_3CZ1_0->rowCount()==0)
    {
        vypisDiagnostika("list is empty");
        return;
    }

    if (ui->tableWidget_manual_subscriberList2_3CZ1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nothing selected");

        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList2_3CZ1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_3.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers2_3CZ1_0(customerInformationService2_3CZ1_0.subscriberList);
        vypisDiagnostika("removed");
    }
    else
    {
        vypisDiagnostika("could not remove");
    }
}



void MainWindow::on_pushButton_detection_refresh_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    devMgmtSubscriber.slotUpdateDeviceInfo();
}


void MainWindow::on_pushButton_detection_saveHwConfig_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    int i=0;
    settings->beginWriteArray("hwConfig");
    foreach(DevMgmtPublisherStruct zarizeni, devMgmtSubscriber.deviceListDetected)
    {
        // QJsonDocument json = QJsonDocument::fromVariant(zarizeni.toQMap() );
        settings->setArrayIndex(i);
        settings->setValue("deviceClass",zarizeni.deviceClass);
        settings->setValue("deviceId",zarizeni.deviceId);
        i++;
    }
    settings->endArray();
}


void MainWindow::on_pushButton_detection_loadHwConfig_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    devMgmtSubscriber.deviceListConfigured.clear();

    int size = settings->beginReadArray("hwConfig");
    for (int j = 0; j < size; ++j) {
        settings->setArrayIndex(j);
        DevMgmtPublisherStruct zarizeni;
        zarizeni.deviceId= settings->value("deviceId").toString();
        zarizeni.deviceClass= settings->value("deviceClass").toString();
        zarizeni.hwConfig=true;
        devMgmtSubscriber.deviceListConfigured.append(zarizeni);
        qCDebug(MainWindowLog)<<"device class: "<<zarizeni.deviceClass<<" id: "<<zarizeni.deviceId;
    }
    settings->endArray();
    qCDebug(MainWindowLog)<<"nacteno "<<QString::number(devMgmtSubscriber.deviceListConfigured.count())<<" zarizeni";
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
    QVector<StopPointDestination> stopPointList=vehicleState.getCurrentTrip().globalStopPointDestinationList;

    foreach(StopPointDestination stopPoint, stopPointList)
    {
        mapPlot.pridejMnozinu(MapyApiStops::polygonToSeznamMapaBod(stopPoint.stopPoint.polygonWgs84),false,false,false,false,true,false,MnozinaBodu::WGS84);
        mapPlot.pridejMnozinu(MapyApiStops::polygonToSeznamMapaBod(stopPoint.stopPoint.polygonWgs84_out ),false,false,false,false,false,true,MnozinaBodu::WGS84);
    }

    mapPlot.pridejMnozinu(MapyApiStops::seznamStopPointDestinationToSeznamMapaBod(stopPointList,true),true,false,false,false,false,false,MnozinaBodu::WGS84);
    mapPlot.pridejMnozinu(MapyApiStops::seznamStopPointDestinationToSeznamMapaBod(stopPointList,true),false,false,false,true,false,false,MnozinaBodu::WGS84);
    mapPlot.pridejMnozinu(sqlRopidQueries.getTrajectoryFromTripS(vehicleState.getCurrentTrip().id,this->createDataValidityMask()),false, true, false,false,false,false,MnozinaBodu::S_JTSK);

    Trip temporaryTrip=sqlRopidQueries.getTripDescriptionFromId(vehicleState.getCurrentTrip().id,this->createDataValidityMask());
    mapPlot.seznamMnozinDoJson(mapPlot.seznamMnozin, mapPlot.spojDoTabulky( temporaryTrip));
    mapPlot.openMap();
}

/*!

*/
void MainWindow::on_pushButton_manual_truncateCustomXml_clicked()
{
    ui->plainTextEdit_manual_customXml->clear();
}


void MainWindow::on_pushButton_manual_addsubscriber_2_3CZ1_0_clicked()
{
    vypisDiagnostika(customerInformationService2_3CZ1_0.handleNewSubscriber(Subscriber(ui->lineEdit_manual_subscriberAddress->text(),ui->lineEdit_manual_subscriberStructure->text())));
}


void MainWindow::on_pushButton_manual_removeSubscriber_2_3CZ1_0_clicked()
{
    if (ui->tableWidget_manual_subscriberList2_3CZ1_0->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->tableWidget_manual_subscriberList2_3CZ1_0->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");
        return;
    }
    int indexPolozky = ui->tableWidget_manual_subscriberList2_3CZ1_0->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_3CZ1_0.removeSubscriber(indexPolozky)==1)
    {
        dumpSubscribers2_3CZ1_0(customerInformationService2_3.subscriberList);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


/*!

*/
void MainWindow::on_pushButton_menu_ride_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_ride );

}


/*!

*/
void MainWindow::on_pushButton_menu_fullscreen_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    this->toggleFullscreen();
}


/*!

*/
void MainWindow::on_pushButton_menu2_fullscreen_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    this->toggleFullscreen();
}


/*!

*/
void MainWindow::on_pushButton_manual_sendCustomXml_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    QByteArray vysledek2="";

    customerInformationService1_0.timer.stop();
    customerInformationService2_3.timer.stop();
    customerInformationService2_3CZ1_0.timer.stop();

    timerDownloadConnections.stop();
    vysledek2=vysledek2+ui->plainTextEdit_manual_customXml->toPlainText().toUtf8();
    customerInformationService1_0.setBodyContent("AllData",vysledek2);
    customerInformationService2_3.setBodyContent("AllData",vysledek2);
    customerInformationService2_3CZ1_0.setBodyContent("AllData",vysledek2);


    for(int i=0;i<customerInformationService1_0.subscriberList.count();i++ )
    {
        customerInformationService1_0.postToSubscriber(customerInformationService1_0.subscriberList[i].address,vysledek2);
    }

    for(int i=0;i<customerInformationService2_3.subscriberList.count();i++ )
    {
        customerInformationService2_3.postToSubscriber(customerInformationService2_3.subscriberList[i].address,vysledek2);
    }

    for(int i=0;i<customerInformationService2_3CZ1_0.subscriberList.count();i++ )
    {
        customerInformationService2_3CZ1_0.postToSubscriber(customerInformationService2_3CZ1_0.subscriberList[i].address,vysledek2);
    }

    qCDebug(MainWindowLog)<<"\n MainWindow::xmlUpdate";
}



/*!

*/
void MainWindow::on_pushButton_ride_arrowPreviousStateSkip_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    MainWindow::close();
    QApplication::exit(0);
    //QCoreApplication::exit(0);
}


/*!

*/

void MainWindow::on_pushButton_ride_beforeStop_clicked()
{

    vehicleState.locationState=Vdv301Enumerations::LocationStateBeforeStop;
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
    vehicleState.locationState=Vdv301Enumerations::LocationStateAfterStop;
    xmlVdv301UpdateContent();
}



/*!

*/
void MainWindow::on_pushButton_ride_betweenStop_clicked()
{
    vehicleState.locationState=Vdv301Enumerations::LocationStateBetweenStop;
    xmlVdv301UpdateContent();
}




/*!

*/
void MainWindow::on_pushButton_configuration_IbisSendTest_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    // ibisOvladani.dopocetCelni("l006");
}



/*!

*/
void MainWindow::on_pushButton_ride_arrowNextState_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if (vehicleState.currentStopIndex0<(this->vehicleState.countCurrentTripStops()))
    {
        if((vehicleState.locationState==Vdv301Enumerations::LocationStateAtStop)&&((vehicleState.currentStopIndex0<(vehicleState.countCurrentTripStops()-1) )))
        {
            eventDeparture();
        }
        else
        {
            qCDebug(MainWindowLog)<<"dalsi? index:"<<vehicleState.currentStopIndex0<<" pocetZastavek:"<<vehicleState.countCurrentTripStops();
            if((vehicleState.locationState==Vdv301Enumerations::LocationStateAtStop)&&((vehicleState.currentStopIndex0+1)==vehicleState.countCurrentTripStops()))
            {
                this->eventGoToNextTrip();
            }

            switch (vehicleState.locationState)
            {
            case Vdv301Enumerations::LocationStateBeforeStop:
            {
                vehicleState.locationState=Vdv301Enumerations::LocationStateAtStop;
                eventArrival();
                break;
            }
            case Vdv301Enumerations::LocationStateBetweenStop:
            {
                vehicleState.locationState=Vdv301Enumerations::LocationStateBeforeStop;
                xmlVdv301UpdateContent();
                break;
            }
            case Vdv301Enumerations::LocationStateAfterStop:
            {
                vehicleState.locationState=Vdv301Enumerations::LocationStateBetweenStop;
                eventAfterStopToBetweenStop();
                break;
            }

            default:
                break;
            }
        }
    }

    updateDriverDisplay();
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateAllDoorsClosed;
}



/*!

*/
void MainWindow::on_pushButton_ride_arrowPreviousState_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    if (vehicleState.currentStopIndex0>=1)
    {
        switch(vehicleState.locationState)
        {
        case Vdv301Enumerations::LocationStateAfterStop:
        {
            vehicleState.locationState=Vdv301Enumerations::LocationStateAtStop;
            vehicleState.currentStopIndex0--;
            eventArrival();
            break;
        }
        case Vdv301Enumerations::LocationStateBetweenStop:
            vehicleState.locationState=Vdv301Enumerations::LocationStateAfterStop;
            xmlVdv301UpdateContent();
            break;
        case Vdv301Enumerations::LocationStateBeforeStop:
            vehicleState.locationState=Vdv301Enumerations::LocationStateBetweenStop;
            xmlVdv301UpdateContent();
            break;
        case Vdv301Enumerations::LocationStateAtStop:
            vehicleState.locationState=Vdv301Enumerations::LocationStateBeforeStop;
            xmlVdv301UpdateContent();
            break;
        default:
            break;
        }
        updateDriverDisplay();
    }
    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0));
}




void MainWindow::on_pushButton_menu2_rezerva_clicked()
{

}



/*!

*/
int MainWindow::on_pushButton_lineTrip_confirm_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //   vehicleState.reset();
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateAllDoorsClosed;

    /*
     * odeslani spoje doplneneho na turnus
    */


    /*
    vehicleState.currentTrip.line.c =ui->lineEdit_lineNumber->text().toInt();
    vehicleState.currentTrip.idRopid=ui->lineEdit_tripNumber->text().toInt();

    if(!sqlRopidQueries.getTripSfromC(vehicleState.currentTrip,this->createDataValidityMask()))
    {
        popUpMessage(tr("trip does not exist"));
        return 0;
    }

    */
    int kmenovaLinka=0;;
    int poradi=0;
    int order=0;
    vehicleState.currentStopIndex0=0;

    Trip hledanySpoj=vehicleState.currentTrip;

    if(sqlRopidQueries.getVehicleRunFromTripS(vehicleState.currentTrip,kmenovaLinka,poradi,order, this->createDataValidityMask() ))
    {

        vehicleState.currentVehicleRun.rootLine.c=kmenovaLinka;
        vehicleState.currentVehicleRun.order=poradi ;
        if (sqlRopidQueries.getTripListFromVehicleRun(vehicleState.currentVehicleRun,this->createDataValidityMask())==1)
        {
            // naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
        }

        vehicleState.currentTripIndex=vehicleState.currentVehicleRun.tripList.indexOf(hledanySpoj);
        qCDebug(MainWindowLog)<<"current trip index: "<< vehicleState.currentTripIndex<<" trip count: "<<vehicleState.currentVehicleRun.tripList.count();
        if(vehicleState.currentTripIndex==-1)
        {
            vehicleState.currentVehicleRun.tripList<<vehicleState.currentTrip;
            vehicleState.currentTripIndex=0;
            popUpMessage(tr("trip without vehicle run"));
        }
        else
        {
            if(! MainWindowPomocne::jeVRozsahu(vehicleState.currentTripIndex,vehicleState.currentVehicleRun.tripList.size(),Q_FUNC_INFO))
            {
                return 0;
            }
            else
            {
                vehicleState.currentTrip=vehicleState.currentVehicleRun.tripList.at(vehicleState.currentTripIndex);
            }
        }


    }
    else
    {
        qCDebug(MainWindowLog)<<"vehicle run not found";
    }


    vehicleState.currentStopIndex0=0;

    int vysledek=initializeTheTrip();
    //now included in initialize trip
    /*
    if (vysledek==1)
    {
        eventEnterService();
    }
    */
    return vysledek;
}


/*!

*/
int MainWindow::on_pushButton_lineRun_confirm_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateAllDoorsClosed;
    //vehicleState.currentLine.lineNumber =ui->lineEdit_rootLine->text();

    vehicleState.currentStopIndex0=0;

    if(!ui->listView_rootLine->currentIndex().isValid())
    {
        qCDebug(MainWindowLog)<<"no root line selected";
        return 0;
    }
    if(!ui->listView_lineRun->currentIndex().isValid())
    {
        qCDebug(MainWindowLog)<<"no vehicle run selected";
        return 0;
    }
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
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    this->on_pushButton_menu_quit_clicked();
}

void MainWindow::on_pushButton_options_debug_set_clicked()
{
    QLoggingCategory::setFilterRules(ui->plainTextEdit_debug_rules->toPlainText());
}


void MainWindow::on_pushButton_positionStart_clicked()
{
    trajectoryJumper.seznamMapaBodu=sqlRopidQueries.getTrajectoryFromTripS(vehicleState.getCurrentTrip().id,this->createDataValidityMask());
    trajectoryJumper.coordinatesSystem=trajectoryJumper.coordinateSystemFromMapaPointList(trajectoryJumper.seznamMapaBodu);

    if((xmlTrajectoryType=="WGS84")||(xmlTrajectoryType=="S_JTSK"))
    {
        trajectoryJumper.start();
    }
    else
    {
        popUpMessage(tr("no trajectories, cannot simulate location"));
    }
}


void MainWindow::on_pushButton_positionStop_clicked()
{
    trajectoryJumper.stop();
}

void MainWindow::on_pushButton_vehicleRefSet_clicked()
{
    vehicleState.vehicleNumber=ui->lineEdit_vehicleRef->text().toInt();
    settings->setValue("vehicleProperties/vehicleRef",vehicleState.vehicleNumber);
    avlSetGeneral();
}


void MainWindow::on_radioButton_ride_singleDoorOpen_clicked()
{
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateSingleDoorOpen;
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_allDoorsClosed_clicked()
{
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateAllDoorsClosed;
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_doorsOpen_clicked()
{
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateDoorsOpen;
    xmlVdv301UpdateContent();
}


void MainWindow::on_radioButton_ride_singleDoorCloser_clicked()
{
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateSingleDoorClosed;
    xmlVdv301UpdateContent();
}

void MainWindow::on_radioButton_configuration_language_cs_clicked()
{
    retranslateUi("cs");
    settings->setValue("app/language","cs");
}


void MainWindow::on_radioButton_configuration_language_en_clicked()
{
    retranslateUi("en");
    settings->setValue("app/language","en");
}


void MainWindow::on_tableView_trip_clicked(const QModelIndex &index)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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

            vehicleState.currentTrip=docasnySpoj;
            int kmenovaLinka=0;
            int poradi=0;
            int order=0;

            sqlRopidQueries.getVehicleRunFromTripS(vehicleState.currentTrip, kmenovaLinka,poradi, order,this->createDataValidityMask());
            qCDebug(MainWindowLog)<<"test spoje do turnusu "<<kmenovaLinka<<"/"<<poradi<<" "<<order;
        }
    }
    qCDebug(MainWindowLog)<<"IDspoje:"<<docasnySpoj.id;
    vehicleState.currentTrip=docasnySpoj;
}



void MainWindow::on_tableView_lineTrip_clicked(const QModelIndex &index)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    if (index.model()->rowCount()!=0)
    {
        qCDebug(MainWindowLog)<<"current item bum";

        vehicleState.currentTrip.line.c=index.siblingAtColumn(0).data().toInt();
        vehicleState.currentTrip.idRopid=index.siblingAtColumn(1).data().toInt();
        vehicleState.currentTrip.id=index.siblingAtColumn(6).data().toInt();
        vehicleState.currentTripIndex=vehicleState.currentVehicleRun.tripList.indexOf(vehicleState.currentTrip);

        qCDebug(MainWindowLog)<<"index spoje na obehu: "<<QString::number(vehicleState.currentTripIndex)<<" delkaSeznamu: "<<vehicleState.currentVehicleRun.tripList.count();
        qCDebug(MainWindowLog)<<"hodnota polozky"<<QString::number(vehicleState.currentTrip.line.c)<<" spoj:"<<QString::number(vehicleState.currentTrip.idRopid);

        //NUTNE DOPLNIT

        //   ui->lineEdit_rootLine->setText(QString::number(vehicleState.currentTrip.line.c));
        //   ui->lineEdit_rootLineTripNumber->setText(QString::number(vehicleState.currentTrip.idRopid));
    }
}

void MainWindow::on_tableWidget_specialAnnouncements_cellClicked(int row, int column)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventShowManualAnnoucementFromList(row,konfigurace.announcementList);
}

void MainWindow::on_tableWidget_ride_stopList_cellClicked(int row, int column)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    vehicleState.locationState=Vdv301Enumerations::LocationStateAtStop;
    vehicleState.doorState=Vdv301Enumerations::DoorOpenStateAllDoorsClosed;
    ui->pushButton_ride_atStop->setChecked(true);
    vehicleState.currentStopIndex0=row;
    eventArrival();
}

/*!

*/
QString MainWindow::openXmlSelectDialogue(QString cesta)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), cesta,
                                                    tr("XML Ropid JŘ (*.xml);;All Files (*)"));
    return fileName;
}

void MainWindow::popUpMessage(QString messageText)
{
    QMessageBox msgBox;
    msgBox.setText(replaceDriverAnnouncementFormatting(messageText));
    msgBox.exec();
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



QString MainWindow::replaceDriverAnnouncementFormatting(QString input)
{
    QString output="";

    qCDebug(MainWindowLog).noquote()<<"retezec pred: "<<input;
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
    qCDebug(MainWindowLog).noquote()<<"retezec po: "<<output;

    return output;
}


void MainWindow::resetTripList()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.reset();
}



void MainWindow::retranslateUi(QString language)
{
    QTranslator translator;

    qApp->removeTranslator(&translator);
    if(translator.load(":/lang_"+language+".qm"))
    {
        qApp->installTranslator(&translator);
        ui->calendarWidget_data_workingDate->setLocale(QLocale::English);
        qCDebug(MainWindowLog)<<"zmena jazyka";
        ui->retranslateUi(this);
    }
    else
    {
        popUpMessage(tr("language file not found"));
    }
}






void MainWindow::setLineToSubMode()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    //ConnectionMPV::ddDoVdv301VehicleMode(vehicleState.getCurrentTrip().line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode);
    Line dummyLine;
    ConnectionMPV::ddDoVehicleMode(vehicleState.getCurrentTrip().line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,dummyLine);
}

/*!

*/
void MainWindow::setXmlPathLabel()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->label_data_pathContent->setText(xmlFilePath);

}


//vypis detekovanych sluzeb do tabulky
void MainWindow::serviceToTable(DevMgmtPublisherStruct zarizeni)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

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
   qCDebug(MainWindowLog) <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;
 */

    qint32 row;
    QTableWidgetItem *cell;

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

    qCDebug(MainWindowLog)<<"sluzbaDoTabulky_konec";
}


/*!

*/
void MainWindow::slotAktualizacePracData()
{
    initializeSelectionListView();
}

void MainWindow::slotCis2_3CZ1_0PortUpdate(int port)
{
    ui->label_statusCisPort->setText(QString::number(port));
}


void MainWindow::slotDownloadConnectionsFromCurrentStop()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //
    Trip currentTrip=vehicleState.getCurrentTrip();
    if(!currentTrip.globalStopPointDestinationList.isEmpty())
    {
        if(isInRange(vehicleState.currentStopIndex0,currentTrip.globalStopPointDestinationList.count(),Q_FUNC_INFO ))
        {
            StopPoint aktZastavka=currentTrip.globalStopPointDestinationList[vehicleState.currentStopIndex0].stopPoint;
            if(useGolemioApi)
            {
                golemio.startDataDownload(aktZastavka.idCis);
            }
            else
            {
                xmlMpvParser.stahniMpvXml(aktZastavka.idCis, aktZastavka.ids);
            }
        }
    }
}


void MainWindow::slotGnssUpdateWgs84(QPointF coordinates)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    avl.slotUpdatePosition(coordinates);
    updatePositionLabel(coordinates);
    locationEvents.slotGnssUpdateWgs84(coordinates);
    trajectoryJumper.setMapaBod(coordinates,MnozinaBodu::WGS84);
}

void MainWindow::slotGnssUpdateSjtsk(QPointF coordinates)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    updatePositionLabel(coordinates);
    locationEvents.slotGnssUpdateSjtsk(coordinates);
}



void MainWindow::slotGolemioReady()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    golemio.fillJsonFromQByteArray();
    QVector<ConnectionGolemio> prestupyGolemio=golemio.parseDomDocumentDepartures();
    QVector<GolemioInfotext> infotextsGolemio=golemio.parseDomDocumentInfotexts();

    qCDebug(MainWindowLog)<<"bum10";

    connectionListToTable(prestupyGolemio,ui->tableWidget_golemioConnections);
    infoTextListToTable(infotextsGolemio,ui->tableWidget_golemioInfotexts);

    QVector<Connection> prestupy;
    foreach(ConnectionGolemio polozka,prestupyGolemio)
    {
        prestupy.push_back(TypeConvertor::connectionGolemioToConnection(polozka));
    }
    qCDebug(MainWindowLog)<<"bum11";
    if(filterConnections)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }
    qCDebug(MainWindowLog)<<"pocet Prestupu ve vektoru: "<<prestupy.count();


    xmlVdv301UpdateCis(prestupy,vehicleState);
}



void MainWindow::slotImportFinished()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    this->workingDateFirstDateOfDataValidity();
    this->initializeSelectionListView();
}


void MainWindow::slotImportDeaktivujTlacitka()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

}

void MainWindow::slotImportAktivujTlacitka()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
}


void MainWindow::slotLocationEnterArea(StopPointDestination stopPoint)
{
    eventArrival();
}

void MainWindow::slotLocationLeaveArea(StopPointDestination stopPoint)
{
    // implement checks for departure from last stop!
    eventDeparture();
}

/*!

*/
void MainWindow::slotMpvNetReady()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qCDebug(MainWindowLog)<<"povypisu "<<xmlMpvParser.stazenaData.length();

    xmlMpvParser.naplnVstupDokument(xmlMpvParser.stazenaData);
    QVector<ConnectionMPV> prestupyMpv=xmlMpvParser.parsujDomDokument();
    if(filterConnections)
    {
        prestupyMpv=xmlMpvParser.vyfiltrujPrestupy(prestupyMpv,vehicleState.currentLine);
    }
    QVector<Connection> prestupy;
    foreach(ConnectionMPV polozka, prestupyMpv)
    {
        prestupy.push_back(polozka.toConnection());
    }

    if(!prestupy.isEmpty())
    {
        xmlVdv301UpdateCis(prestupy,vehicleState);
    }
}


void MainWindow::slotServiceTableUpdate()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    dumpServicesToTable(devMgmtSubscriber.deviceListDetected, devMgmtSubscriber.deviceListConfigured);
}


void MainWindow::slotSetProgress(int hodnota)
{
    ui->progressBar_data_importXml->setValue(hodnota);
    //qCDebug(MainWindowLog)<<QString::number(hodnota)<<"/"<<QString::number(ui->progressBar->maximum());
}


void MainWindow::slotSetProgressMax(int hodnota)
{
    //resetujProgressBar();
    qCDebug(MainWindowLog)<<Q_FUNC_INFO<<" "<<QString::number(hodnota);
    ui->progressBar_data_importXml->setMaximum(hodnota);
}


void MainWindow::slotVdv301ServiceStartResult(QString nastartovanaSluzba)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO<<" "<<nastartovanaSluzba;
    startServiceFromList(vektorCis);
}



/*!

*/
void MainWindow::startAllVdv301Services()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    deviceManagementService1_0.blockBonjour=blockBonjour;
    deviceManagementService1_0.slotStartServer();
    /*
    customerInformationService1_0.slotStartServer();
    customerInformationService2_2CZ1_0.slotStartServer();
    customerInformationService2_4.slotStartServer();
    */
    ticketValidationService2_2.blockBonjour=blockBonjour;
    ticketValidationService2_2.slotStartServer();

    if(blockBonjour)
    {
        foreach (CustomerInformationService *cisService, vektorCis) {
            cisService->blockBonjour=blockBonjour;
            cisService->slotStartServer();
        }
    }
    else
    {
        startServiceFromList(vektorCis);
    }
}


void MainWindow::startServiceFromList(QVector<CustomerInformationService*> &seznamSluzeb)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    if(!seznamSluzeb.isEmpty())
    {
        QPointer<CustomerInformationService> aktualniSluzba=seznamSluzeb.takeFirst();
        aktualniSluzba->blockBonjour=blockBonjour;
        qCDebug(MainWindowLog)<<"v zasobniku zustava sluzeb: "<<seznamSluzeb.count();
        qCDebug(MainWindowLog)<<"starting"<<aktualniSluzba->mServiceName<<" "<<aktualniSluzba->version()<<" "<<aktualniSluzba->portNumber();
        aktualniSluzba->slotStartServer();
    }
}


/*!

*/
void MainWindow::stopServices()
{
    //customerInformationService1_0.
}

/*!

*/
void MainWindow::testPopulateWindow(int index)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        testDemo.start();
        break;
    case 1:
        testSubscribeServer.start();
        break;
    default:
        qCDebug(MainWindowLog)<<"test s indexem "<<QString::number(index)<<" neexistuje";
        break;
    }
}


/*!

*/
void MainWindow::testStop(int index)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    switch (index)
    {
    case 0:
        testDemo.stop();
        break;
    case 1:
        testSubscribeServer.stop();
        break;
    default:
        qCDebug(MainWindowLog)<<"test s indexem "<<QString::number(index)<<" neexistuje";
        break;
    }
}


/*!

*/
void MainWindow::slotVypisSqlVysledek(QString vstup)
{
    ui->label_data_sqlResult->setText(vstup);
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

    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    for(int i =0;i<seznamPolozek.size();i++)
    {
        qCDebug(MainWindowLog)<<i<<" "<<seznamPolozek.at(i).nazev<<" "<<seznamPolozek.at(i).vysledek;
    }

    ui->tableWidgetCastiTestu->setRowCount(0);
    qCDebug(MainWindowLog)<<"smazano"<<" adresy.size="<<seznamPolozek.size();
    if (seznamPolozek.size()==0)
    {
        qCDebug(MainWindowLog)<<"vracim 0";
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
        qCDebug(MainWindowLog)<<"vracim 1";
        //return 1;
    }
}




void MainWindow::truncateSubscriberTable(QTableWidget *tableWidget)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //  https://stackoverflow.com/a/31564541
    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);
}


QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qCDebug(MainWindowLog)<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}




/*!
načte platnost a nastaví rozsahy klikatelných oblastí kalendáře
*/
void MainWindow::updateCalendar()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    if(sqlRopidQueries.getDatasetValidity(validityFrom,validityTo,xmlVersion))
    {
        xmlTrajectoryType=sqlRopidQueries.getTrajectoryType();
        ui->calendarWidget_data_workingDate->setMinimumDate(validityFrom);
        ui->calendarWidget_data_workingDate->setMaximumDate(validityTo);
        ui->label_data_validFrom->setText(validityFrom.toString("dd. MM. yyyy"));
        ui->label_data_validTo->setText(validityTo.toString("dd. MM. yyyy"));
    }
    else
    {
        xmlTrajectoryType="N/A";
        xmlVersion="";
        ui->calendarWidget_data_workingDate->setMinimumDate(QDate(1900, 1, 1));
        ui->calendarWidget_data_workingDate->setMaximumDate(QDate(3000, 1, 1));
        ui->label_data_validFrom->setText("");
        ui->label_data_validTo->setText("");
    }
    ui->label_data_trajectoriesType->setText(xmlTrajectoryType);
    ui->label_data_version->setText(xmlVersion);
    ui->calendarWidget_data_workingDate->setFirstDayOfWeek(Qt::Monday);
}


/*!

*/

void MainWindow::updateDriverDisplay()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(this->vehicleState.currentVehicleRun.tripList.length()<=vehicleState.currentTripIndex)
    {
        qCDebug(MainWindowLog)<<"spoj odpovidajici indexu neexistuje";
        return;
    }

    MainWindowPomocne::dumpStopsToTable(vehicleState.currentStopIndex0,this->vehicleState.getCurrentTrip().globalStopPointDestinationList,vehicleState.locationState,sqlRopidQueries,  ui->tableWidget_ride_stopList);
    int delkaGlobalnihoSeznamu= this->vehicleState.countCurrentTripStops();
    int indexZastavky=vehicleState.currentStopIndex0;
    qCDebug(MainWindowLog)<<"delka seznamu spoju "<<this->vehicleState.currentVehicleRun.tripList.length()<<" index "<<vehicleState.currentTripIndex<<" delka globsezzast "<< delkaGlobalnihoSeznamu  << " indexAktZast "<<indexZastavky   ;

    if (indexZastavky>=delkaGlobalnihoSeznamu)
    {
        qCDebug(MainWindowLog)<<"index zastavky je mimo rozsah";
        return;
    }


    ui->label_ride_stopIndex->setText(QString::number(vehicleState.currentStopIndex0+1));
    vehicleState.currentTrip=vehicleState.getCurrentTrip();

    ui->label_ride_currentLineNumber->setText(this->vehicleState.getCurrentTrip().globalStopPointDestinationList.at(vehicleState.currentStopIndex0).line.lineNumber);
    ui->label_ride_currentTripNumber->setText(QString::number(this->vehicleState.getCurrentTrip().idRopid));

    ui->label_ride_currentVehicleRun->setText(QString::number(vehicleState.currentVehicleRun.rootLine.c)+"/"+QString::number(vehicleState.currentVehicleRun.order));

    ui->label_ride_currentDelay->setText(MainWindowPomocne::secondsToString(vehicleState.secondsDelay));

    //  ui->label_ride_currentDelay->setText(QTime::fromString(QString::number(vehicleState.secondsDelay),"s").toString("m:ss"));


    updateVehicleLocationDisplay(vehicleState.locationState);
}




void MainWindow::updatePositionLabel(QPointF coordinates)
{
    if(!coordinates.isNull())
    {
        ui->label_positionX->setText(QString::number(coordinates.x()));
        ui->label_positionY->setText(QString::number(coordinates.y()));
    }
    else
    {
        ui->label_positionX->setText("");
        ui->label_positionY->setText("");
    }

}


void MainWindow::updateVehicleLocationDisplay(Vdv301Enumerations::LocationStateEnumeration locationState)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    switch(locationState)
    {
    case Vdv301Enumerations::LocationStateBeforeStop:
        ui->pushButton_ride_beforeStop->setChecked(true);
        break;
    case Vdv301Enumerations::LocationStateAtStop:
        ui->pushButton_ride_atStop->setChecked(true);
        break;
    case Vdv301Enumerations::LocationStateAfterStop:
        ui->pushButton_ride_afterStop->setChecked(true);
        break;
    case Vdv301Enumerations::LocationStateBetweenStop:
        ui->pushButton_ride_betweenStop->setChecked(true);
        break;
    default:
        break;

    }

    ui->label_ride_locationStateIndicator->setText(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState));
}



/*!

*/
void MainWindow::updataWorkingDate()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->dateEdit_data_workingDate->setDate(vehicleState.referenceDate);
    ui->calendarWidget_data_workingDate->setSelectedDate(vehicleState.referenceDate);

    qCDebug(MainWindowLog)<<"od "<<validityFrom<<" do "<<validityTo<<" pracovni "<<vehicleState.referenceDate ;
    qCDebug(MainWindowLog)<<"dnu do pracovnihodata "<< vehicleState.referenceDate.daysTo(validityFrom) <<" dnu do zacatku platnosti " << vehicleState.referenceDate.daysTo(validityTo);

    this->createDataValidityMask();
    sqlRopidQueries.createValidyMaskFromDate(this->vehicleState.referenceDate,validityFrom,validityTo);

    initializeSelectionListView();
}



/*!

*/
void MainWindow::vypisDiagnostika(QString vstup)
{
    qCDebug(MainWindowLog)<<" MainWindow::vypisDiagnostika "<<vstup;
    ui->label_diagnostika_manual->clear();
    ui->label_diagnostika_manual->setText(vstup);
    ui->statusBar->showMessage(vstup);
    logfile.pridejNaKonecSouboru(logFileQFile,QDateTime::currentDateTime().toString()+" "+ vstup);
}



/*!
\brief popis
xxxxxx
*/
void MainWindow::workingDateToday()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    vehicleState.referenceDate=QDate::currentDate();
    updataWorkingDate();
}


/*!

*/
void MainWindow::workingDateFirstDateOfDataValidity()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    updateCalendar();
    vehicleState.referenceDate=validityFrom;
    updataWorkingDate();
}


/*!

*/
void MainWindow::xmlVdv301UpdateContent()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qCDebug(MainWindowLog)<<"delka seznamu tripu "<<vehicleState.currentVehicleRun.tripList.length();
    QVector<Connection> emptyConnectionList;

    if(setVehicleTypeFromLineType)
    {
        setLineToSubMode();
    }

    if (vehicleState.currentVehicleRun.tripList.isEmpty())
    {
        qCDebug(MainWindowLog)<<"seznam tripu je prazdny";
        xmlVdv301UpdateCis(emptyConnectionList,vehicleState);
    }
    else
    {
        if (vehicleState.showConnections==true)
        {
            slotDownloadConnectionsFromCurrentStop();
            timerDownloadConnections.start();
        }
        else
        {
            timerDownloadConnections.stop();
            xmlVdv301UpdateCis(emptyConnectionList,vehicleState);
        }
    }

    ticketValidationService2_2.updateServiceContent(emptyConnectionList,vehicleState);
    deviceManagementService1_0.serviceContentUpdate();
}



void MainWindow::xmlVdv301UpdateCis(QVector<Connection> prestupy, VehicleState &mStavSystemu )
{
    /*
    customerInformationService1_0.updateServiceContent(prestupy,mStavSystemu );
    customerInformationService2_2CZ1_0.updateServiceContent(prestupy,mStavSystemu);
    customerInformationService2_3.updateServiceContent(prestupy,mStavSystemu);
    customerInformationService2_3CZ1_0.updateServiceContent(prestupy,mStavSystemu);

    */

    customerInformationService2_3CZ1_0.setGlobalDisplayContentList(globalDisplayContentList2_3CZ1_0);

    foreach (QPointer<CustomerInformationService> selectedService, vektorCisPermanent)
    {
        selectedService->updateServiceContent(prestupy,mStavSystemu);
    }
}

void MainWindow::on_pushButton_debugOpenWindow_clicked()
{

    logWindow.show();
}


void MainWindow::on_checkBox_debugLogEnable_stateChanged(int arg1)
{
    if(arg1)
    {
        connect(&relay, &LoggerRelay::message,&logWindow,&LogWindow::slotLogWindowAppend,Qt::QueuedConnection);
    }
    else
    {
        disconnect(&relay, &LoggerRelay::message,&logWindow,&LogWindow::slotLogWindowAppend);
    }
}


void MainWindow::on_pushButton_specialAnnouncementManual_clicked()
{
    AdditionalAnnoucement announcement;
    announcement.text=ui->lineEdit_specialAnnouncementText->text();
    announcement.icon=ui->lineEdit_specialAnnouncementIcon->text();
    announcement.duration=ui->lineEdit_specialAnnouncementDuration->text().toInt()*1000;

    eventStartWholeAnnouncement(announcement);
}

