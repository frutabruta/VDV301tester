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



#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/line.h"
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/stoppointdestination.h"

#include "VDV301publisher/httpservice.h"
#include "VDV301publisher/customerinformationservice.h"
#include "VDV301publisher/ticketvalidationservice.h"
#include "VDV301publisher/devicemanagementservice.h"

#include "VDV301subscriber/ibisipsubscriber.h"
#include "VDV301subscriber/devmgmtsubscriber.h"
#include "VDV301subscriber/devmgmtpublisherstruct.h"

#include "VDV301testy/vdv301testy.h"
#include "VDV301testy/testodberuserver.h"
#include "VDV301testy/testdemo.h"

#include "sqlropidxmldotazy.h"
#include "xmlmpvparser.h"
#include "golemio.h"
#include "XmlRopidImportStream/xmlimportjr.h"
#include "ibisovladani.h"
#include "hlasic.h"
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
    QString umisteniProgramu=QCoreApplication::applicationDirPath();

private:

    //konstanty
    bool filtrovatPrestupy=true;
    bool pouzitGolemio=true;
    //ve vterinach

    //datove struktury
    VehicleState stavSystemu;


    //SQLprace mojesql;
    SqlRopidXmlDotazy sqlPraceRopid;

    //instance knihoven
    Konfigurace konfigurace;
    QSettings settings;

    XmlMpvParser xmlMpvParser;
    Golemio golemio;
    //  XmlRopidImportStream xmlRopidImportStream;
    IbisOvladani ibisOvladani;
    Hlasic hlasic;
    Logfile logfile;
    QFile souborLogu;
    MapaVykresleni mapaVykresleni;

    //VDV301testy
    TestDemo vzorovyTest;
    TestOdberuServer testOdberuServer;
    int testIndex=0;

    void testStart(int index);
    void testStop(int index);

    //promenne
    QString cestaXml="";
    QDate platnostOd;
    QDate platnostDo;

    //modely

    QSqlQueryModel *modelSpoje2;
    QSqlQueryModel prazdnyModel;
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);

    //udalosti

    int eventPrijezd();
    int eventOdjezd();
    void eventZmenaTarifnihoPasma();
    void eventAfterStopToBetweenStop();
    void eventOpusteniVydeje();
    void eventVstupDoVydeje();
    void eventPoznamkaRidici(QString poznamka);

    void vsechnyConnecty();
    void testNaplnOkno(int index);
    void xmlVdv301HromadnyUpdate();

    //IBIS-IP sluzby
    DeviceManagementService deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_2CZ1_0;
    CustomerInformationService customerInformationService2_3;


    TicketValidationService ticketValidationService2_3CZ1_0;
    QVector<CustomerInformationService*> vektorCis;

    //IBIS-IP subscriber
    DevMgmtSubscriber devMgmtSubscriber;
    // IbisIpSubscriber deviceManagementServiceSubscriber;



    //vyberove dialogy
    void vymazSeznam(QListWidget *vstup);

    //prace s XML
    QString otevriSouborXmlDialog(QString cesta);
    void nastavLabelCestyXml();
    void aktualizacePracovnihoData();

    //prace s oknem
    Ui::MainWindow *ui;
    void aktualizaceDispleje();
    void toggleFullscreen();

    //void replyFinished(QNetworkReply *);
    void inicializaceVyberovychPoli();


    //VDV301

    void vypisSubscribery1_0(QVector<Subscriber> adresy);
    void vypisSubscribery2_2CZ(QVector<Subscriber> adresy);
    void vypisSubscriberyDoTabulky(QVector<Subscriber> adresy, QTableWidget *tabulka);
    void nastartujVsechnyVdv301Sluzby();
    void zastavSluzby(); //neimplementovano

    //kalendar jizd
    void pracovniDatumDnes();
    void pracovniDatumPrvniDenDat();
    void aktualizaceKalendare();
    QString vyrobMaskuKalendareJizd();

    void vypisZastavkyTabulka(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, QString locationState);
    void dalsiSpoj();
    int natahniSeznamSpojeKomplet();

    //timery
    QTimer timerTrvaniZmenyPasma; //po pvyprseni casovace zmizi zmena pasma
    // QTimer *timerAfterStopToBetweenStop = new QTimer(this);
    QTimer timerAfterStopToBetweenStop;
    QTimer timerStahniPrestupy;
    QTimer timerSpecialniOznameniSmazat;


    void resetSeznamuSpoju();
    void eventZobrazOznameni(int index, QVector<AdditionalAnnoucement> seznamHlaseni);
    void vykresliStav(QString stav);
    void vykresliSluzbyDoTabulky(QVector<DevMgmtPublisherStruct> seznamSluzebDetekce, QVector<DevMgmtPublisherStruct> seznamSluzebKonfigurace);
    void sluzbaDoTabulky(DevMgmtPublisherStruct zarizeni);
    void vymazTabulkuSubscriberu(QTableWidget *tableWidget);

    QString nahradZnacky(QString vstup);

    void natahniKonstanty();

    void cisAktualizaceObsahu(QVector<Connection> prestupy, VehicleState mStavSystemu);
    void nastartujSluzbuZeZasobniku(QVector<CustomerInformationService *> &seznamSluzeb);
    QString textVerze();
    void connectyImport(XmlImportJr *xmlImportJr);


    void vypisSubscribery2_3(QVector<Subscriber> adresy);
    void modelDoTabulkySeradit(QSqlQueryModel* modelInput, QTableView* tableView);
public slots:
    void slotVypisSqlVysledek(QString vstup);
    void testyVykresliCasti(QVector<PolozkaTestu> &seznamPolozek);
    void slotAktualizacePracData();
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

    //checkboxy jizda
    void on_radioButton_singleDoorOpen_clicked();
    void on_radioButton_allDoorsClosed_clicked();
    void on_radioButton_doorsOpen_clicked();
    void on_radioButton_singleDoorCloser_clicked();

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

    //radio buttons
    void radio1(bool stav);
    void radio2(bool stav);
    void radio3(bool stav);
    void radio4(bool stav);

    //vlatni sloty
    void slotMpvNetReady();
    void vypisDiagnostika(QString vstup);

    //eventy zobrazeni na periferiích
    void eventZmenaTarifnihoSystemu();
    void eventSkryjZmenuTarifnihoPasma();
    void eventSkryjZmenuTarifnihoSystemu();

    //nezarazeno
    void slotStahniPrestupyAktZastavky();

    void on_tableWidget_oznameni_cellClicked(int row, int column);
    void slotVymazatSpecialniOznameni();
    void slotAktualizaceTabulkySluzeb();

    void slotImportDokoncen();
    void slotImportDeaktivujTlacitka();
    void slotImportAktivujTlacitka();
    void slotNastavProgress(int hodnota);
    void slotNastavProgressMax(int hodnota);

    void on_listView_linky_clicked(const QModelIndex &index);

    void on_listView_kmenovaLinka_clicked(const QModelIndex &index);
    void on_listView_poradi_clicked(const QModelIndex &index);

    void on_tableView_turnusSpoj_clicked(const QModelIndex &index);
    void slotGolemioReady();

    void on_pushButton_refreshDetekce_clicked();

    void on_pushButton_ulozDetekce_clicked();

    void on_pushButton_nactiDetekce_clicked();

    void on_pushButton_jizda_mapa_clicked();

    void slotSluzbaVratilaVysledekStartu(QString nastartovanaSluzba);


    void on_checkBox_stopRequested_clicked(bool checked);

    void on_pushButton_manual_addsubscriber_3_clicked();

    void on_pushButton_manual_removeSubscriber_3_clicked();

    void on_pushButton_menu2_rezerva_clicked();

    void on_tableView_connection_clicked(const QModelIndex &index);

signals:
    void signalZahajImport(QString cesta);
};

#endif // MAINWINDOW_H
