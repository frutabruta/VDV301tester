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

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/zastavkacil.h"

#include "VDV301publisher/httpsluzba.h"
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
#include "XmlRopidImportStream/xmlropidimportstream.h"
#include "ibisovladani.h"
#include "hlasic.h"
#include "konfigurace.h"
#include "logfile.h"
#include "mainwindowpomocne.h"



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
    //ve vterinach
    //datove struktury
    CestaUdaje stavSystemu;
    QVector <Linka> seznamLinek;
    QVector <Spoj> seznamSpoju;
    QVector <Obeh> seznamObehu;

    //SQLprace mojesql;
    SqlRopidXmlDotazy sqlPraceRopid;

    //instance knihoven
    XmlMpvParser xmlMpvParser;
  //  XmlRopidImportStream xmlRopidImportStream;
    IbisOvladani ibisOvladani;
    Hlasic hlasic;
    Logfile logfile;
    QFile souborLogu;

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
    QSqlQueryModel *modelSpoje;

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

    //IBIS-IP lsuzby
    DeviceManagementService deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_2CZ1_0;
    TicketValidationService ticketValidationService2_3CZ1_0;

    //IBIS-IP subscriber
    DevMgmtSubscriber deviceManagementServiceSubscriber;
   // IbisIpSubscriber deviceManagementServiceSubscriber;


    //konfiguracni soubor
    Konfigurace konfigurace;

    //vyberove dialogy


    void naplnKmenoveLinky(QVector<Linka> docasnySeznamLinek);
    void naplnVyberPoradi(QVector<Obeh> docasnySeznamObehu);
    void naplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju);
    void vymazSeznam(QListWidget *vstup);

    //prace s XML
    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void aktualizacePracovnihoData();

    //prace s oknem
    Ui::MainWindow *ui;
    void aktualizaceDispleje();
    void toggleFullscreen();

    //void replyFinished(QNetworkReply *);
    void inicializaceVyberovychPoli();
    void inicializacePoli();

    //VDV301
    void vypisSubscribery1_0(QVector<Subscriber> adresy);
    void vypisSubscribery2_2CZ(QVector<Subscriber> adresy);
    void nastartujVsechnyVdv301Sluzby();
    void zastavSluzby();

    //kalendar jizd
    void pracovniDatumDnes();
    void pracovniDatumPrvniDenDat();
    void aktualizaceKalendare();
    QString vyrobMaskuKalendareJizd();

    void vypisZastavkyTabulka(int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState);
    void dalsiSpoj();
    void dalsiSpojNavazujici();
    int natahniSeznamSpojeKomplet();

    //timery
    QTimer *timerTrvaniZmenyPasma = new QTimer(this); //po pvyprseni casovace zmizi zmena pasma
   // QTimer *timerAfterStopToBetweenStop = new QTimer(this);
    QTimer timerAfterStopToBetweenStop;
    QTimer timerStahniPrestupy;
    QTimer timerSpecialniOznameniSmazat;


    void resetSeznamuSpoju();
    void eventZobrazOznameni(int index, QVector<SpecialniHlaseni> seznamHlaseni);
    void vykresliStav(QString stav);
    void vykresliSluzbyDoTabulky(QVector<DevMgmtPublisherStruct> seznamSluzeb);
    void sluzbaDoTabulky(DevMgmtPublisherStruct zcs);
    void vymazTabulkuSubscriberu(QTableWidget *tableWidget);

    QString nahradZnacky(QString vstup);
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

    void on_checkBox_stateChanged(int arg1); //zapnuti MPV prestupu


    //tlacitka Turnus
    int on_pushButton_turnus_prikaz_clicked();

    void on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

     void on_checkBox_MpvTurnusy_stateChanged(int arg1);

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

     void on_listView_spoje_clicked(const QModelIndex &index);

signals:
     void signalZahajImport(QString cesta);
};

#endif // MAINWINDOW_H
