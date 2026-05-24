#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QListWidget>
#include <QtSerialPort/QSerialPort>
#include <QNetworkAccessManager>
#include <QMainWindow>
#include <QNetworkReply>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QRegularExpression> //qt6
#include <QTableWidget>
#include <QTableView>
#include <QLoggingCategory>


#include "VDV301publisher/VDV301DataStructures/vehiclestate.h"


//#include "VDV301publisher/httpservice.h"
#include "VDV301publisher/customerinformationservice.h"
#include "VDV301publisher/ticketvalidationservice.h"
#include "VDV301publisher/devicemanagementservice.h"
//#include "VDV301publisher/timeservice.h"

//#include "VDV301subscriber/ibisipsubscriber.h"
#include "VDV301subscriber/devmgmtsubscriber.h"
#include "VDV301subscriber/devmgmtsubscriber1.h"
#include "VDV301subscriber/devmgmtsubscriber2.h"
#include "VDV301subscriber/devmgmtpublisherstruct.h"

//#include "VDV301testy/vdv301testy.h"
#include "VDV301testy/testodberuserver.h"
#include "VDV301testy/testdemo.h"

#include "sqlropidxmlqueries.h"
#include "xmlmpvparser.h"
#include "GolemioClient/golemiodepartureboardsv2.h"
#include "XmlRopidImportStream/xmlimportjr.h"
#include "IbisSender/ipispid.h"
#include "VoiceAnnouncer/voiceannouncer.h"
#include "specialannouncementparser.h"
#include "logfile.h"
#include "MapaVykresleni/mapyapistops.h"
#include "typeconvertor.h"

#include "MapaVykresleni/trajectoryjumper.h"
#include "MapaVykresleni/coordinatestools.h"
#include "locationevents.h"
#include "Avl/avl.h"
#include "gnsslocationservicesubscriberdummy.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(QSettings* newQSettings,QString filePath, QWidget *parent = nullptr);
    ~MainWindow();

    //konstanty
    QString applicationDirectory=QCoreApplication::applicationDirPath();

    void popUpMessage(QString messageText);

private:

    void allConnects();
    void loadConstantsFromSettingsFile();


    //konstanty
    bool filterConnections=true;
    bool useGolemioApi=true;
    bool ibisIsEnabled=false;
    int announcementType=1;
    // 0 Prague Bus
    // 1 Prague Metro
    // 2 Berlin

    bool blockBonjour=true;

    bool avlEnabled=false;

    bool setVehicleTypeFromLineType=true;

    int pkt=333; //message pkt counter

    //datove struktury
    VehicleState vehicleState;

    QVector<Vdv301DisplayContent> globalDisplayContentList2_3CZ1_0;


    //SQLprace mojesql;
    SqlRopidXmlQueries sqlRopidQueries;

    //instance knihoven
    SpecialAnnouncementParser konfigurace;
    QSettings *settings;

    XmlMpvParser xmlMpvParser;
    GolemioDepartureBoardsV2 golemio;
    //  XmlRopidImportStream xmlRopidImportStream;
    IpisPid ibisOvladani;
    VoiceAnnouncer voiceAnnouncer;
    Logfile logfile;
    QFile logFileQFile;
    MapyApiStops mapPlot;
    TrajectoryJumper trajectoryJumper;
    CoordinatesTools coordinateTools;
    LocationEvents locationEvents;
    Avl avl; //vehicle state sender

    GnssLocationServiceSubscriberDummy gnssSusbcriber;


    //VDV301testy
    TestDemo testDemo;
    TestOdberuServer testSubscribeServer;
    int testIndex=0;

    void testStart(int index);
    void testStop(int index); //unused

    //promenne
    QString xmlFilePath="";
    QDate validityFrom;
    QDate validityTo;
    QString xmlVersion="";
    QString xmlTrajectoryType=""; // N/A, WGS84, S-JTSK



    //modely

    QSqlQueryModel *modelConnection;
    QSqlQueryModel emptyQSqlQueryModel;

    QSortFilterProxyModel proxyModel; //= new QSortFilterProxyModel(this);

    //udalosti

    int eventArrival();
    void eventAfterStopToBetweenStop();
    int eventDeparture();
    void eventDepartureFromLastStop();
    void eventFareZoneChange(QString zoneFrom, QString zoneTo);
    void eventFareZoneChange(QVector<FareZone> fareZoneListFrom, QVector<FareZone> fareZoneListTo);  

    void eventLineChange(QString lineFrom, QString lineTo);

    void eventExitService();
    void eventEnterService();
    void eventAnnouncementToDriver(QString poznamka);
    void eventGoToNextTrip();
    void eventShowManualAnnoucement(int index, QVector<AdditionalAnnoucement> additionalAnnouncementList);
    void eventStopTimersRide();

    void testPopulateWindow(int index);


    //IBIS-IP sluzby
    //  TimeService timeService1_0;  //just publishes OS built in server
    DeviceManagementService deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_3;
    CustomerInformationService customerInformationService2_3CZ1_0;


    TicketValidationService ticketValidationService2_3CZ1_0;

    //list which changes - every service is poped after start
    QVector<CustomerInformationService*> vektorCis;

    //permanent list of all CIS instances, which doesn't change over time
    QVector<CustomerInformationService*> vektorCisPermanent;

    //IBIS-IP subscriber
    DevMgmtSubscriber2 devMgmtSubscriber;



    //selection dialogues
    void truncateQListWidget(QListWidget *vstup); //unused

    //XML management
    QString openXmlSelectDialogue(QString cesta);
    void setXmlPathLabel();
    void updataWorkingDate();
    void workingDateToday();
    void workingDateFirstDateOfDataValidity();
    void updateCalendar();
    QString createDataValidityMask();

    void connectyImport(XmlImportJr *xmlImportJr);

    //windows tools
    Ui::MainWindow *ui;
    void updateDriverDisplay();
    void toggleFullscreen();

    //void replyFinished(QNetworkReply *);
    void initializeSelectionListView();


    //VDV301

    void dumpSubscribers1_0(QVector<Subscriber> adresy);
    void dumpSubscribers2_3CZ1_0(QVector<Subscriber> adresy);
    void dumpSubscribersToTable(QVector<Subscriber> adresy, QTableWidget *tabulka);
    void startAllVdv301Services();
    void stopServices(); //not implemented
    void startServiceFromList(QVector<CustomerInformationService *> &seznamSluzeb);
    void xmlVdv301UpdateContent();
    void xmlVdv301UpdateCis(QVector<Connection> prestupy, VehicleState &mStavSystemu);

    void dumpServicesToTable(QVector<DevMgmtPublisherStruct> serviceListDetected, QVector<DevMgmtPublisherStruct> serviceListConfigured);
    void serviceToTable(DevMgmtPublisherStruct selectedDevice);
    void truncateSubscriberTable(QTableWidget *tableWidget);


    
    int initializeTheTrip();
    void resetTripList();
    void updateVehicleLocationDisplay(Vdv301Enumerations::LocationStateEnumeration locationState);
    void updatePositionLabel(QPointF coordinates);

    //timery
    QTimer timerFareZoneChangeDuration; //fare  change announcement vanishes after timeout
    QTimer timerLineChangeDuration; //line name change announcement vanishes after timeout
    QTimer timerAfterStopToBetweenStop;
    QTimer timerDownloadConnections;
    QTimer timerSpecialAnnoucementHide;

    QString replaceDriverAnnouncementFormatting(QString input);

    QString textVerze();

    void modelDoTabulkySeradit(QSqlQueryModel* modelInput, QTableView* tableView);
    void retranslateUi(QString language);
    
    QVector<Vdv301DisplayContent> createGlobalDisplayContentOutOfService2_3();
    int isInRange(int index, int valueCount, QString functionName);

    void connectionToTable(ConnectionGolemio connection, QTableWidget *tableWidget);
    void connectionListToTable(QVector<ConnectionGolemio> connectionList, QTableWidget *tableWidget);
    void eraseTable(QTableWidget *tableWidget);
    void infoTextListToTable(QVector<GolemioInfotext> infotextList, QTableWidget *tableWidget);
    void infoTextToTable(GolemioInfotext golemioInfotext, QTableWidget *tableWidget);

    void setLineToSubMode();
    QString avlSetGeneral();
    void avlSetStop(StopPointDestination currentStopPointDestination);


public slots:
    void slotVypisSqlVysledek(QString vstup);

    void slotAktualizacePracData(); //unused

private slots:
    //tlacitka

    //tlacitka Menu
    
    void on_pushButton_menu_vehicleRun_clicked();
    void on_pushButton_menu_lineTrip_clicked();
    void on_pushButton_menu_ride_clicked();
    void on_pushButton_menu_specialAnnouncement_clicked();
    void on_pushButton_menu_fullscreen_clicked();
    void on_pushButton_menu_quit_clicked();

    //tlacitka Menu2
    void on_pushButton_menu2_quit_clicked();
    void on_pushButton_menu2_fullscreen_clicked();
    void on_pushButton_menu2_sluzby_clicked();
    void on_pushButton_menu2_prubehTestu_clicked();
    void on_pushButton_menu2_rezerva_clicked();

    //tlacitka Linka/spoj
    int on_pushButton_lineTrip_confirm_clicked();
    void on_checkBox_configuration_enableConnections_stateChanged(int arg1); //zapnuti MPV prestupu


    //tlacitka Turnus
    int on_pushButton_lineRun_confirm_clicked();



    //tlacitka jizda
    void on_pushButton_ride_arrowNextState_clicked();
    void on_pushButton_ride_arrowNextStateSkip_clicked();
    void on_pushButton_ride_arrowPreviousState_clicked();
    void on_pushButton_ride_arrowPreviousStateSkip_clicked();
    
    void on_pushButton_ride_beforeStop_clicked();
    void on_pushButton_ride_atStop_clicked();
    void on_pushButton_ride_afterStop_clicked();
    void on_pushButton_ride_betweenStop_clicked();    

    void on_pushButton_ride_map_clicked();
    void on_pushButton_ride_IBIS_clicked();

    void on_tableWidget_ride_stopList_cellClicked(int row, int column);

    //checkboxy jizda
    void on_radioButton_ride_singleDoorOpen_clicked();
    void on_radioButton_ride_allDoorsClosed_clicked();
    void on_radioButton_ride_doorsOpen_clicked();
    void on_radioButton_ride_singleDoorCloser_clicked();
    void on_checkBox_ride_stopRequested_clicked(bool checked);

    //tlacitka Test

    void on_pushButton_startTest_clicked();
    void on_pushButton_stopTest_clicked();
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_test3_clicked();
    void on_pushButton_test4_clicked();


    //tlacitka Nast.
    void on_calendarWidget_data_workingDate_selectionChanged();
    void on_pushButton_data_today_clicked();
    void on_pushButton_data_truncate_clicked();
    void on_pushButton_data_selectXmlPath_clicked();
    void on_pushButton_data_startXmlRopidImport_clicked();

    //configuration buttons
    void on_pushButton_configuration_IbisSetPort_clicked();
    void on_pushButton_configuration_IbisSendTest_clicked();
    void on_pushButton_configuration_setGolemioKey_clicked();

    //tlacitka Manual
    void on_pushButton_manual_addsubscriber_clicked();
    void on_pushButton_manual_removeSubscriber_clicked();

    void on_pushButton_manual_truncateCustomXml_clicked();
    void on_pushButton_manual_sendCustomXml_clicked();
    void on_pushButton_manual_addsubscriber_3_clicked();
    void on_pushButton_manual_removeSubscriber_3_clicked();

    void on_pushButton_manual_addsubscriber_2_3CZ1_0_clicked();
    void on_pushButton_manual_removeSubscriber_2_3CZ1_0_clicked();

    //radio buttons
    void radio1(bool stav);
    void radio2(bool stav);
    void radio3(bool stav);
    void radio4(bool stav);

    //vlatni sloty
    void slotMpvNetReady();
    void vypisDiagnostika(QString vstup);

    //eventy zobrazeni na periferiích
    void eventAddAnnoucement(AdditionalAnnoucement announcement);
    void eventAnnouncementContinue();
    void eventFareSystemChangeShow();
    void eventFareSystemChangeHide();
    void eventFareZoneChangeHide();
    void eventLineChangeHide();
    void eventSpecialAnnouncementHide();


    //VDV301
    void slotVdv301ServiceStartResult(QString nastartovanaSluzba);

    //connections
    void slotDownloadConnectionsFromCurrentStop();
    void slotGolemioReady();

    //settings screen

    void on_radioButton_configuration_language_cs_clicked();
    void on_radioButton_configuration_language_en_clicked();

    void on_checkBox_configuration_logToFile_stateChanged(int arg1);

    //XML import
    void slotImportFinished();
    void slotImportDeaktivujTlacitka();
    void slotImportAktivujTlacitka();
    void slotSetProgress(int hodnota);
    void slotSetProgressMax(int hodnota);

    //device management service detection
    void on_pushButton_detection_saveHwConfig_clicked();
    void on_pushButton_detection_loadHwConfig_clicked();
    void on_pushButton_detection_refresh_clicked();

    //selection lists
    void on_listView_line_clicked(const QModelIndex &index);
    void on_listView_rootLine_clicked(const QModelIndex &index);
    void on_listView_lineRun_clicked(const QModelIndex &index);
    void on_tableView_lineTrip_clicked(const QModelIndex &index);
    void on_tableView_trip_clicked(const QModelIndex &index);

    //test
    void testPopulateTestPhases(QVector<PolozkaTestu> &seznamPolozek); //unused

    //misc
    void on_tableWidget_specialAnnouncements_cellClicked(int row, int column);
    void slotServiceTableUpdate();

    //avl slots
    void slotGnssUpdateWgs84(QPointF coordinates);
    void slotGnssUpdateSjtsk(QPointF coordinates);
    void slotLocationEnterArea(StopPointDestination stopPoint);
    void slotLocationLeaveArea(StopPointDestination stopPoint);

    void on_pushButton_detection_setId_clicked();

    void on_pushButton_positionStart_clicked();
    void on_pushButton_positionStop_clicked();

    void on_checkBox_positionCenterMap_stateChanged(int arg1);
    void on_checkBox_positionStopAtStops_stateChanged(int arg1);

    void on_pushButton_vehicleRefSet_clicked();
    void on_checkBox_vechicleTypeFromLine_stateChanged(int arg1);

    void on_pushButton_options_debug_set_clicked();

    void on_checkBox_avlRelay_stateChanged(int arg1);


signals:
    // void signalZahajImport(QString cesta);
};

#endif // MAINWINDOW_H
