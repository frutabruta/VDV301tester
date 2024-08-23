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



//#include "VDV301DataStructures/stoppoint.h"
//#include "VDV301DataStructures/line.h"
#include "VDV301publisher/VDV301DataStructures/vehiclestate.h"
#include "VDV301publisher/VDV301DataStructures/stoppointdestination.h"
//#include "VDV301publisher/VDV301DataStructures/vdv301displaycontent.h"

//#include "VDV301publisher/httpservice.h"
#include "VDV301publisher/customerinformationservice.h"
#include "VDV301publisher/ticketvalidationservice.h"
#include "VDV301publisher/devicemanagementservice.h"

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
#include "golemio.h"
#include "XmlRopidImportStream/xmlimportjr.h"
#include "IbisSender/ipispid.h"
#include "VoiceAnnouncer/voiceannouncer.h"
#include "konfigurace.h"
#include "logfile.h"
#include "mainwindowpomocne.h"
#include "MapaVykresleni/mapyapistops.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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


    //ve vterinach

    //datove struktury
    VehicleState vehicleState;

    QVector<Vdv301DisplayContent> globalDisplayContentList2_3CZ1_0;


    //SQLprace mojesql;
    SqlRopidXmlQueries sqlRopidQueries;

    //instance knihoven
    Konfigurace konfigurace;
    QSettings settings;

    XmlMpvParser xmlMpvParser;
    Golemio golemio;
    //  XmlRopidImportStream xmlRopidImportStream;
    IpisPid ibisOvladani;
    VoiceAnnouncer voiceAnnouncer;
    Logfile logfile;
    QFile logFileQFile;
    MapyApiStops mapPlot;

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



    //modely

    QSqlQueryModel *modelConnection;
    QSqlQueryModel emptyQSqlQueryModel;
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);

    //udalosti

    int eventArrival();
    int eventDeparture();
    void eventFareZoneChange();
    void eventAfterStopToBetweenStop();
    void eventExitService();
    void eventEnterService();
    void eventAnnouncementToDriver(QString poznamka);
    void eventGoToNextTrip();
    void eventShowAnnoucement(int index, QVector<AdditionalAnnoucement> seznamHlaseni);


    void testPopulateWindow(int index);


    //IBIS-IP sluzby
    DeviceManagementService deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_2CZ1_0;
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
    void dumpSubscribers2_2CZ(QVector<Subscriber> adresy);
    void dumpSubscribers2_3(QVector<Subscriber> adresy);
    void dumpSubscribersToTable(QVector<Subscriber> adresy, QTableWidget *tabulka);
    void startAllVdv301Services();
    void stopServices(); //not implemented
    void startServiceFromList(QVector<CustomerInformationService *> &seznamSluzeb);
    void xmlVdv301UpdateContent();
    void xmlVdv301UpdateCis(QVector<Connection> prestupy, VehicleState mStavSystemu);

    void dumpServicesToTable(QVector<DevMgmtPublisherStruct> serviceListDetected, QVector<DevMgmtPublisherStruct> serviceListConfigured);
    void serviceToTable(DevMgmtPublisherStruct selectedDevice);
    void truncateSubscriberTable(QTableWidget *tableWidget);


    
    int initializeTheTrip();
    void resetTripList();
    void updateVehicleLocationDisplay(Vdv301Enumerations::LocationStateEnumeration locationState);


    //timery
    QTimer timerFareZoneChangeDuration; //fare  change announcement vanishes after timeout
    QTimer timerAfterStopToBetweenStop;
    QTimer timerDownloadConnections;
    QTimer timerSpecialAnnoucementHide;

    QString replaceDriverAnnouncementFormatting(QString input);

    QString textVerze();

    void modelDoTabulkySeradit(QSqlQueryModel* modelInput, QTableView* tableView);
    void retranslateUi(QString language);
    
    QVector<Vdv301DisplayContent> createGlobalDisplayContentOutOfService2_3();
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
    void on_pushButton_manual_addsubscriber_2_clicked();
    void on_pushButton_manual_removeSubscriber_2_clicked();
    void on_pushButton_manual_truncateCustomXml_clicked();
    void on_pushButton_manual_sendCustomXml_clicked();
    void on_pushButton_manual_addsubscriber_3_clicked();
    void on_pushButton_manual_removeSubscriber_3_clicked();

    //radio buttons
    void radio1(bool stav);
    void radio2(bool stav);
    void radio3(bool stav);
    void radio4(bool stav);

    //vlatni sloty
    void slotMpvNetReady();
    void vypisDiagnostika(QString vstup);

    //eventy zobrazeni na periferiích
    void eventFareSystemChangeShow();
    void eventFareSystemChangeHide();
    void eventFareZoneChangeHide();
    void evenSpecialAnnouncementHide();

    //VDV301
    void slotVdv301ServiceStartResult(QString nastartovanaSluzba);

    //connections
    void slotDownloadConnectionsFromCurrentStop();
    void slotGolemioReady();

    //settings screen

    void on_radioButton_configuration_language_cs_clicked();
    void on_radioButton_configuration_language_en_clicked();

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



    void on_pushButton_detection_setId_clicked();

signals:
         // void signalZahajImport(QString cesta);
};

#endif // MAINWINDOW_H
