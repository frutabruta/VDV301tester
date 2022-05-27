#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QListWidget>
#include <QtSerialPort/QSerialPort>
#include <QNetworkAccessManager>
#include <QMainWindow>

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/zastavkacil.h"

#include "VDV301publisher/httpsluzba.h"
#include "VDV301publisher/customerinformationservice.h"
#include "VDV301publisher/ticketvalidationservice.h"

#include "VDV301testy/vdv301testy.h"
#include "VDV301testy/testodberuserver.h"
#include "VDV301testy/testdemo.h"

#include "sqlpraceropid.h"
#include "xmlmpvparser.h"
#include "xmlropidparser.h"
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

    //datove struktury
    CestaUdaje stavSystemu;
    QVector <Linka> seznamLinek;
    QVector <Spoj> seznamSpoju;
    QVector <Obeh> seznamObehu;

    //SQLprace mojesql;
    SqlPraceRopid sqlPraceRopid;

    //instance knihoven
    XmlMpvParser xmlMpvParser;
    XmlRopidParser xmlRopidParser;
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


    //udalosti

    int eventPrijezd();
    int eventOdjezd();
    void eventZmenaTarifnihoPasma();

    void vsechnyConnecty();
    void testNaplnOkno(int index);
    void xmlVdv301HromadnyUpdate();

    //IBIS-IP lsuzby
    HttpSluzba deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_2CZ1_0;
    TicketValidationService ticketValidationService2_3CZ1_0;

    //konfiguracni soubor
    Konfigurace konfigurace;

    //vyberove dialogy
    void NaplnVyberLinky(QVector<Linka> docasnySeznamLinek);
    void NaplnVyberSpoje(QVector<Spoj> docasnySeznamSpoju);
    void NaplnKmenoveLinky(QVector<Linka> docasnySeznamLinek);
    void NaplnVyberPoradi(QVector<Obeh> docasnySeznamObehu);
    void NaplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju);
    void vymazSeznam(QListWidget *vstup);

    //prace s XML
    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void AktualizacePracovnihoData();

    //prace s oknem
    Ui::MainWindow *ui;
    void AktualizaceDispleje();
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


public slots:
    void vypisSqlVysledek(QString vstup);
    void testyVykresliCasti(QVector<PolozkaTestu> &seznamPolozek);
    void slotAktualizacePracData();
private slots:
    //tlacitka

    //tlacitka Menu
    void on_tlacitkoLinkospoj_clicked();
    void on_tlacitkoTurnus_clicked();
    void on_tlacitkoZpetVydej_clicked();
    void on_tlacitkoTestRozhrani_clicked();
    void on_tlacitkoNastaveni_clicked();
    void on_tlacitkoManual_clicked();
    void on_tlacitkoFullscreen_clicked();
    void on_quitTlacitko_clicked();

    //tlacitka Menu2
    void on_quitTlacitko_2_clicked();
    void on_tlacitkoPalubniPc_clicked();

    void on_tlacitkoFullscreen2_clicked();


    //tlacitka Linka/spoj
    int on_prikaztlacitko_clicked();

    void on_checkBox_stateChanged(int arg1); //zapnuti MPV prestupu
    void on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    //tlacitka Turnus
    int on_prikazTlacitkoTurnus_clicked();

    void on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    //tlacitka Výdej
    void on_sipkaNahoru_clicked();
    void on_sipkaDolu_clicked();

    void on_pridatTlacitko_clicked();
    void on_ubratTlacitko_clicked();

    void on_tlacitkoIBIS_clicked();

    void on_BeforeStop_clicked();
    void on_AtStop_2_clicked();
    void on_AfterStop_clicked();
    void on_BetweenStop_clicked();

    void on_tableWidgetNasledujiciZastavky_cellClicked(int row, int column);

    //tlacitka Test
    void on_tlacitkoPrubehTestu_clicked();
    void on_tlacitko_StartTest_clicked();
    void on_TlacitkoStopTest_clicked();
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_test3_clicked();
    void on_pushButton_test4_clicked();
    void on_tlacitkoSluzby_clicked();

    //tlacitka Nast.
    void on_tlacitkoDnes_clicked();
    void on_calendarWidget_selectionChanged();
    void on_tlacitkoHlaseniSlozka_clicked();
    void on_pripojeniTlacitko_clicked();

    void on_tlacitkoTruncate_clicked();
    void on_tlacitkoXmlVyberCestu_clicked();
    void on_tlacitkoNactiXMLropid_clicked();

    void on_tlacitkoNastavPort_clicked();
    void on_tlacitkoOdesliPrikaz_clicked();
    //tlacitka Manual
    void on_tlacitkoAddsubscriber_clicked();
    void on_tlacitkoRemoveSubscriber_clicked();

    void on_tlacitkoAddsubscriber_2_clicked();
    void on_tlacitkoRemoveSubscriber_2_clicked();

    void on_tlacitkoSmazOkno_clicked();

    void on_tlacitkoOdesliXml_clicked();



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

};

#endif // MAINWINDOW_H
