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

    //datove struktury
    CestaUdaje stavSystemu;
    QVector <Linka> seznamLinek;
    QVector <Spoj> seznamSpoju;
    QVector <Obeh> seznamObehu;

    bool platnostSpoje=1;

    //SQLprace mojesql;
    SqlPraceRopid sqlPraceRopid;

    //instance knihoven
    XmlMpvParser xmlMpvParser;
    XmlRopidParser xmlRopidParser;
    IbisOvladani ibisOvladani;
    Hlasic hlasic;
    Logfile logfile;

    //VDV301testy
    TestDemo vzorovyTest;
    TestOdberuServer testOdberuServer;
    int testIndex=0;

    QFile log;

    //udalosti
    void xmlHromadnyUpdate();
    int priPrijezdu();
    int priOdjezdu();
    void vsechnyConnecty();
    void testNaplnOkno(int index);

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

    void testStart(int index);
    void testStop(int index);

    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void AktualizacePracovnihoData();
private:
    Ui::MainWindow *ui;
    //void replyFinished(QNetworkReply *);
    void AktualizaceDispleje();
    void startDatabaze();
    void inicializacePoli();
    void vypisSubscribery(QVector<Subscriber> adresy);

    void vypisSubscribery2(QVector<Subscriber> adresy);
    void NaplnVyberPoradi(QVector<Obeh> docasnySeznamObehu);
    void NaplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju);
    void zastavSluzby();
    void toggleFullscreen();
    void nastartujVsechnySluzby();


    void pracovniDatumDnes();
    void pracovniDatumPrvniDenDat();
public slots:
    void vypisSqlVysledek(QString vstup);
    void testyVykresliCasti(QVector<PolozkaTestu> &seznamPolozek);
    void slotAktualizacePracData();
private slots:
    //tlacitka
    int on_prikaztlacitko_clicked();
    void on_sipkaNahoru_clicked();
    void on_sipkaDolu_clicked();
    void on_ubratTlacitko_clicked();
    void on_pripojeniTlacitko_clicked();
    void on_pridatTlacitko_clicked();
    void on_quitTlacitko_clicked();

    void on_BeforeStop_clicked();
    void on_AtStop_2_clicked();
    void on_AfterStop_clicked();
    void on_BetweenStop_clicked();

    void on_tlacitkoNactiXMLropid_clicked();
    void on_tlacitkoNastaveni_clicked();
    void on_tlacitkoTruncate_clicked();
    void on_tlacitkoOdesliPrikaz_clicked();
    void on_tlacitkoNastavPort_clicked();
    void on_tlacitkoIBIS_clicked();
    void on_tlacitkoZpetVydej_clicked();
    void on_tlacitkoLinkospoj_clicked();
    void on_tlacitkoSmazOkno_clicked();
    void on_tlacitkoManual_clicked();
    void on_tlacitkoOdesliXml_clicked();

    void on_tlacitkoAddsubscriber_clicked();
    void on_tlacitkoRemoveSubscriber_clicked();
    void on_tlacitkoHlaseniSlozka_clicked();
    void on_tlacitkoAddsubscriber_2_clicked();
    void on_tlacitkoRemoveSubscriber_2_clicked();
    int on_prikazTlacitkoTurnus_clicked();
    void on_quitTlacitko_2_clicked();
    void on_tlacitkoPalubniPc_clicked();
    void on_tlacitkoTestRozhrani_clicked();
    void on_tlacitkoFullscreen_clicked();
    void on_tlacitkoFullscreen2_clicked();
    void on_tlacitkoTurnus_clicked();

    //tlacitkaTestu
    void on_tlacitkoPrubehTestu_clicked();
    void on_tlacitko_StartTest_clicked();
    void on_TlacitkoStopTest_clicked();
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_test3_clicked();
    void on_pushButton_test4_clicked();
    void on_tlacitkoSluzby_clicked();

    //checkbox
    void on_prestupyCheckbox_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);

    //radio buttons
    void radio1(bool stav);
    void radio2(bool stav);
    void radio3(bool stav);
    void radio4(bool stav);

    //zmeny seznamu
    void on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    //vlatni signaly
    void MpvNetReady();
    void vypisDiagnostika(QString vstup);




    void on_tlacitkoXmlVyberCestu_clicked();
    void on_calendarWidget_selectionChanged();
    void on_tlacitkoDnes_clicked();
};

#endif // MAINWINDOW_H
