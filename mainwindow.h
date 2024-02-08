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
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vdv301displaycontent.h"

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
#include "ibisovladani.h"
#include "voiceannouncer.h"
#include "konfigurace.h"
#include "logfile.h"
#include "mainwindowpomocne.h"
#include "MapaVykresleni/mapavykresleni.h"

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
    //ve vterinach

    //datove struktury
    VehicleState vehicleState;


    //SQLprace mojesql;
    SqlRopidXmlQueries sqlRopidQuerries;

    //instance knihoven
    Konfigurace konfigurace;
    QSettings settings;

    XmlMpvParser xmlMpvParser;
    Golemio golemio;
    //  XmlRopidImportStream xmlRopidImportStream;
    IbisOvladani ibisOvladani;
    VoiceAnnouncer voiceAnnouncer;
    Logfile logfile;
    QFile logFileQFile;
    MapaVykresleni mapPlot;

    //VDV301testy
    TestDemo testDemo;
    TestOdberuServer testSubscribeServer;
    int testIndex=0;

    void testStart(int index);
    void testStop(int index);

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


    TicketValidationService ticketValidationService2_3CZ1_0;
    QVector<CustomerInformationService*> vektorCis;

    //IBIS-IP subscriber
    DevMgmtSubscriber2 devMgmtSubscriber;



    //selection dialogues
    void truncateQListWidget(QListWidget *vstup);

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



    void dumpStopsToTable(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, QString locationState);

    int natahniSeznamSpojeKomplet();
    void resetTripList();
    void updateVehicleLocationDisplay(QString stav);


    //timery
    QTimer timerFareZoneChangeDuration; //fare  change announcement vanishes after timeout
    QTimer timerAfterStopToBetweenStop;
    QTimer timerDownloadConnections;
    QTimer timerSpecialAnnoucementHide;



    QString nahradZnacky(QString vstup);




    QString textVerze();




    void modelDoTabulkySeradit(QSqlQueryModel* modelInput, QTableView* tableView);
    void retranslateUi(QString language);
public slots:
    void slotVypisSqlVysledek(QString vstup);

    void slotAktualizacePracData(); //unused
private slots:
    //tlacitka

    //tlacitka Menu

    void on_pushButton_menu_turnus_clicked();
    void on_pushButton_menu_linkospoj_clicked();
    void on_pushButton_menu_jizda_clicked();
    void on_pushButton_menu_oznameni_clicked();
    void on_pushButton_menu_fullscreen_clicked();
    void on_pushButton_menu_quit_clicked();

    //tlacitka Menu2
    void on_pushButton_menu2_quit_clicked();
    void on_pushButton_menu2_fullscreen_clicked();
    void on_pushButton_menu2_sluzby_clicked();
    void on_pushButton_menu2_prubehTestu_clicked();
    void on_pushButton_menu2_rezerva_clicked();

    //tlacitka Linka/spoj
    int on_pushButton_prikaz_clicked();
    void on_checkBox_connections_stateChanged(int arg1); //zapnuti MPV prestupu


    //tlacitka Turnus
    int on_pushButton_turnus_prikaz_clicked();



    //tlacitka jizda
    void on_pushButton_jizda_sipkaDal_clicked();
    void on_pushButton_jizda_sipkaZpet_clicked();

    void on_pushButton_jizda_sipkaDalSkok_clicked();
    void on_pushButton_jizda_sipkaZpetSkok_clicked();

    void on_pushButton_jizda_IBIS_clicked();

    void on_pushButton_jizda_beforeStop_clicked();
    void on_pushButton_jizda_atStop_clicked();
    void on_pushButton_jizda_afterStop_clicked();
    void on_pushButton_jizda_betweenStop_clicked();

    void on_tableWidgetNasledujiciZastavky_cellClicked(int row, int column);
       void on_pushButton_jizda_mapa_clicked();

    //checkboxy jizda
    void on_radioButton_singleDoorOpen_clicked();
    void on_radioButton_allDoorsClosed_clicked();
    void on_radioButton_doorsOpen_clicked();
    void on_radioButton_singleDoorCloser_clicked();    
    void on_checkBox_stopRequested_clicked(bool checked);

    //tlacitka Test

    void on_pushButton_startTest_clicked();
    void on_pushButton_stopTest_clicked();
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_test3_clicked();
    void on_pushButton_test4_clicked();


    //tlacitka Nast.
    void on_calendarWidget_selectionChanged();
    void on_pushButton_nast_dnes_clicked();
    void on_pushButton_nast_truncate_clicked();
    void on_pushButton_nast_xmlVyberCestu_clicked();
    void on_pushButton_nast_nactiXMLropid_clicked();
    void on_pushButton_nast_nastavPort_clicked();
    void on_pushButton_nast_odesliPrikaz_clicked();

    //tlacitka Manual
    void on_pushButton_manual_addsubscriber_clicked();
    void on_pushButton_manual_removeSubscriber_clicked();
    void on_pushButton_manual_addsubscriber_2_clicked();
    void on_pushButton_manual_removeSubscriber_2_clicked();
    void on_pushButton_manual_smazOkno_clicked();
    void on_pushButton_manual_odesliXml_clicked();
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
    void on_pushButton_setGolemioKey_clicked();
    void on_radioButton_language_cs_clicked();
    void on_radioButton_language_en_clicked();

    //XML import
    void slotImportFinished();
    void slotImportDeaktivujTlacitka();
    void slotImportAktivujTlacitka();
    void slotSetProgress(int hodnota);
    void slotSetProgressMax(int hodnota);

    //device management service detection
    void on_pushButton_ulozDetekce_clicked();
    void on_pushButton_nactiDetekce_clicked();
    void on_pushButton_refreshDetekce_clicked();

    //selection lists
    void on_listView_linky_clicked(const QModelIndex &index);
    void on_listView_kmenovaLinka_clicked(const QModelIndex &index);
    void on_listView_poradi_clicked(const QModelIndex &index);
    void on_tableView_turnusSpoj_clicked(const QModelIndex &index);
    void on_tableView_connection_clicked(const QModelIndex &index);

    //test
    void testPopulateTestPhases(QVector<PolozkaTestu> &seznamPolozek); //unused

    //misc
    void on_tableWidget_oznameni_cellClicked(int row, int column);
    void slotServiceTableUpdate();


signals:
    void signalZahajImport(QString cesta);
};

#endif // MAINWINDOW_H
