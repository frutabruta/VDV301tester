#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VDV301struktury/cestaudaje.h"
#include "xmlgenerator.h"

#include <QNetworkReply>
#include "VDV301struktury/zastavka.h"
#include "VDV301testy/vdv301testy.h"
#include "QFileDialog"
#include "QMessageBox"
//koment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logfile(QCoreApplication::applicationDirPath()),
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",47477,"1.0"),
    customerInformationService1_0("CustomerInformationService","_ibisip_http._tcp",47479,"1.0"),
    customerInformationService2_2CZ1_0("CustomerInformationService (2)","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    ticketValidationService2_3CZ1_0("TicketValidationService","_ibisip_http._tcp",47481,"2.2CZ1.0"),
    konfigurace(QCoreApplication::applicationDirPath()),
    ui(new Ui::MainWindow)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->setupUi(this);

    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );

    ui->stackedWidget_palPc->setWindowState(Qt::WindowFullScreen);


    //inicializace databaze
    inicializaceVyberovychPoli();

    //propojeni vsech slotu
    vsechnyConnecty();

    nastartujVsechnyVdv301Sluzby();

    //vyplneni polozky build pro rozliseni zkompilovanych verzi
    QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);
    ui->label_build->setText(compilationTime);

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
    timerTrvaniZmenyPasma->setInterval(konfigurace.trvaniZobrazeniPasma);
    timerTrvaniZmenyPasma->setSingleShot(true);

    timerSpecialniOznameniSmazat.setSingleShot(true);
    timerSpecialniOznameniSmazat.setInterval(konfigurace.trvaniZobrazeniOznameni);

    timerStahniPrestupy.setInterval(konfigurace.intervalStahovaniPrestupu);

    timerAfterStopToBetweenStop->setInterval(konfigurace.intervalAfterStopToBetweenStop);
    timerAfterStopToBetweenStop->setSingleShot(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}



/*!
přesunutí connectů pro větší přehlednost
*/
void MainWindow::vsechnyConnecty()
{
    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery1_0);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery2_2CZ);
    this->vypisSubscribery1_0(customerInformationService1_0.seznamSubscriberu);
    this->vypisSubscribery2_2CZ(customerInformationService2_2CZ1_0.seznamSubscriberu);
    connect(&xmlMpvParser,SIGNAL(stazeniHotovo()),this,SLOT(slotMpvNetReady()));

    //vypis stavu testu
    connect(&vzorovyTest,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);
    connect(&testOdberuServer,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);

    //jednotliveTesty
    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalVypisSubscriberu,&testOdberuServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&testOdberuServer,&TestOdberuServer::signalVymazSeznamOdberatelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotVymazSubscribery);
    connect(&testOdberuServer,&TestOdberuServer::signalNastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStart);
    connect(&testOdberuServer,&TestOdberuServer::signalZastavCisTimer,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotZastavCasovac);
    connect(&testOdberuServer,&TestOdberuServer::signalOdesliDataDoPanelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotTedOdesliNaPanely);

    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalVypisSubscriberu,&testOdberuServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalOdpovedNaPost,&testOdberuServer,&TestOdberuServer::slotVypisOdpovedServeru);

    //vypinani sluzeb pomoci prepinacu
    connect(ui->radioButton_ON1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpSluzba::slotStart);
    connect(ui->radioButton_OFF1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpSluzba::slotStart);
    connect(ui->radioButton_OFF2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpSluzba::slotStart);
    connect(ui->radioButton_OFF3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON4,&QRadioButton::clicked,&customerInformationService1_0,&HttpSluzba::slotStart);
    connect(ui->radioButton_OFF4,&QRadioButton::clicked,&customerInformationService1_0,&HttpSluzba::slotStop);



    //vypisovani stavovych hlasek do stavoveho radku vespod okna
    connect(&sqlPraceRopid,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);
    connect(&sqlPraceRopid,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);
    connect(&xmlRopidParser,&XmlRopidParser::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);


    //prepinani stavu radio prepinacu podle stavu sluzeb
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio1);
    connect(&deviceManagementService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio2);
    connect(&ticketValidationService2_3CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio3);
    connect(&customerInformationService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio4);

    //konfigurace
    connect(&konfigurace,&Konfigurace::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);


    //casovace
    connect(timerTrvaniZmenyPasma,&QTimer::timeout,this,&MainWindow::eventSkryjZmenuTarifnihoPasma);
    connect(timerAfterStopToBetweenStop,&QTimer::timeout,this,&MainWindow::eventAfterStopToBetweenStop);
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
    deviceManagementService1_0.slotStart(true);
    customerInformationService1_0.slotStart(true);
    customerInformationService2_2CZ1_0.slotStart(true);
    ticketValidationService2_3CZ1_0.slotStart(true);
}


/*!

*/
void MainWindow::xmlVdv301HromadnyUpdate()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug()<<"delka seznamu tripu "<<stavSystemu.aktObeh.seznamSpoju.length();
    if (stavSystemu.aktObeh.seznamSpoju.isEmpty())
    {
        qDebug()<<"seznam tripu je prazdny";
        return;
    }
    QDomDocument vstupniDomXmlPrestupy;
    if (stavSystemu.prestupy==true)
    {
        slotStahniPrestupyAktZastavky();
        timerStahniPrestupy.start();
    }
    else
    {
        timerStahniPrestupy.stop();
    }

    QVector<PrestupMPV> prestupy;
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
    ticketValidationService2_3CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
}

void MainWindow::slotStahniPrestupyAktZastavky()
{
    qDebug() <<  Q_FUNC_INFO;
    Zastavka aktZastavka=stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka;
    xmlMpvParser.stahniMpvXml(aktZastavka.cisloCis, aktZastavka.ids);
}


/*!

*/
void MainWindow::slotMpvNetReady()
{
    qDebug() <<  Q_FUNC_INFO;
    xmlMpvParser.naplnVstupDokument(xmlMpvParser.stazenaData);
    QVector<PrestupMPV> prestupy=xmlMpvParser.parsujDomDokument();
    if(filtrovatPrestupy)
    {
        prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu );
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
}





/*!

*/
int MainWindow::on_pushButton_prikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.vymaz();
    stavSystemu.doorState="AllDoorsClosed";


    /*
     * odeslani spoje doplneneho na turnus
*/

    stavSystemu.aktspoj.linka.c =ui->polelinky->text().toInt();
    stavSystemu.aktspoj.cisloRopid=ui->polespoje->text().toInt();

    int kmenovaLinka=0;;
    int poradi=0;
    int order=0;
    sqlPraceRopid.najdiTurnusZeSpoje( stavSystemu.aktspoj,kmenovaLinka,poradi,order, this->vyrobMaskuKalendareJizd() );

    stavSystemu.indexAktZastavky=0;



    ui->poleLinkyTurnus->setText(QString::number(kmenovaLinka));
    stavSystemu.aktObeh.kmenovaLinka.c=kmenovaLinka;


    if (sqlPraceRopid.vytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd() )==1)
    {
        naplnVyberPoradi(seznamObehu);
    }


    stavSystemu.aktObeh.p=poradi ;
    if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.aktObeh,this->vyrobMaskuKalendareJizd())==1)
    {
        naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
    }

    Spoj hledanySpoj=stavSystemu.aktspoj;
    stavSystemu.indexSpojeNaObehu=sqlPraceRopid.poziceSpojeNaSeznamu(stavSystemu.aktObeh.seznamSpoju,hledanySpoj);

    if(! MainWindowPomocne::jeVRozsahu(stavSystemu.indexSpojeNaObehu,stavSystemu.aktObeh.seznamSpoju.size(),"MainWindow::on_prikaztlacitko_clicked"))
    {
        return 0;
    }

    stavSystemu.aktspoj=stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexSpojeNaObehu);
    ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
    ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text().toInt();

    stavSystemu.indexAktZastavky=0;

    return natahniSeznamSpojeKomplet();

}




/*!

*/
int MainWindow::on_pushButton_turnus_prikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text().toInt();

    stavSystemu.indexAktZastavky=0;
    stavSystemu.indexSpojeNaObehu=ui->listTurnusSpoje->currentRow();
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
    Spoj iterSpoj;

    if(ui->listTurnusSpoje->count()==0)
    {
        qDebug()<<"neni zvoleny spoj";
        this->vypisDiagnostika("není zvoleno pořadí");
        return 0;
    }
    else
    {
        qDebug()<<"zjisteni zvolene pozice v seznamu"<<stavSystemu.indexSpojeNaObehu;
        if (stavSystemu.indexSpojeNaObehu<0)
        {
            this->vypisDiagnostika("není zvolený spoj");
            return 0;
        }
    }


    vysledek=sqlPraceRopid.stahniSeznamCelySpojTurnus(stavSystemu.aktObeh.seznamSpoju,stavSystemu.indexSpojeNaObehu,this->vyrobMaskuKalendareJizd());
    qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    if (stavSystemu.aktualniSpojNaObehu().navazujici==true)
    {
        vysledek=sqlPraceRopid.stahniSeznamCelySpojTurnus(stavSystemu.aktObeh.seznamSpoju,stavSystemu.indexSpojeNaObehu+1,this->vyrobMaskuKalendareJizd());
        qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    }

    qDebug()<<"je nacteno "<<stavSystemu.aktObeh.seznamSpoju.length()<<" spoju";

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
    if(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek.empty()==1)
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
    }
    return 1;
}


/*!

*/
void MainWindow::on_pushButton_jizda_sipkaNahoru_clicked()
{
    qDebug() <<  Q_FUNC_INFO;


    if (stavSystemu.indexAktZastavky<(this->stavSystemu.pocetZastavekAktualnihoSpoje()))
    {
        if((stavSystemu.locationState=="AtStop")&&((stavSystemu.indexAktZastavky<(stavSystemu.pocetZastavekAktualnihoSpoje()-1) )))
        {
            stavSystemu.locationState="AfterStop";
            ui->pushButton_jizda_afterStop->setChecked(true);

            stavSystemu.indexAktZastavky++;
            eventOdjezd();
        }
        else
        {
            qDebug()<<"dalsi? index:"<<stavSystemu.indexAktZastavky<<" pocetZastavek:"<<stavSystemu.pocetZastavekAktualnihoSpoje();
            if((stavSystemu.locationState=="AtStop")&&((stavSystemu.indexAktZastavky+1)==stavSystemu.pocetZastavekAktualnihoSpoje()))
            {
                this->dalsiSpoj();
            }


            if(stavSystemu.locationState=="BeforeStop")
            {
                stavSystemu.locationState="AtStop";
                ui->pushButton_jizda_atStop->setChecked(true);
                eventPrijezd();
            }

            if(stavSystemu.locationState=="BetweenStop")
            {
                stavSystemu.locationState="BeforeStop";
                ui->pushButton_jizda_beforeStop->setChecked(true);
            }

            if(stavSystemu.locationState=="AfterStop")
            {stavSystemu.locationState="BetweenStop";
                ui->pushButton_jizda_betweenStop->setChecked(true);
                eventAfterStopToBetweenStop();
            }
        }
    }


    aktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";
    // ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky+1));
    xmlVdv301HromadnyUpdate();
}



/*!

*/
void MainWindow::on_pushButton_jizda_sipkaDolu_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.indexAktZastavky>=1)
    {
        if(stavSystemu.locationState=="AfterStop")
        {
            stavSystemu.locationState="AtStop";
            stavSystemu.indexAktZastavky--;
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
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    xmlVdv301HromadnyUpdate();
}



/*!

*/
void MainWindow::on_pushButton_nast_pripojeni_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    inicializaceVyberovychPoli();


}





/*!
 \fn void MainWindow::inicializaceVyberovychPoli()

pripoji se k databazi a naplni okna pro vyber spoju
*/
void MainWindow::inicializaceVyberovychPoli()
{
    qDebug() <<  Q_FUNC_INFO;
    sqlPraceRopid.pripoj();
    vymazSeznam(ui->listLinek);
    vymazSeznam(ui->listSpoje);

    vymazSeznam(ui->listKmenovychLinek);
    vymazSeznam(ui->listPoradi);
    vymazSeznam(ui->listTurnusSpoje);

    if (sqlPraceRopid.vytvorSeznamLinek(seznamLinek,this->vyrobMaskuKalendareJizd())==1)
    {

        naplnVyberLinky(seznamLinek);

        QVector<Linka> kmenoveLinky;
        sqlPraceRopid.vytvorSeznamKmenovychLinek(kmenoveLinky,vyrobMaskuKalendareJizd());
        naplnKmenoveLinky(kmenoveLinky);

        aktualizaceKalendare();
        ui->NazevVysledku->setText("OK2");
    }
    else
    {
        ui->NazevVysledku->setText("FAIL2");
        qDebug()<<"chyba nacitani linek";
    }
}



/*!
načte platnost a nastaví rozsahy klikatelných oblastí kalendáře
*/
void MainWindow::aktualizaceKalendare()
{
    qDebug() <<  Q_FUNC_INFO;
    if(sqlPraceRopid.nactiPlatnost(xmlRopidParser.platnostOd,xmlRopidParser.platnostDo))
    {
        ui->calendarWidget->setMinimumDate(xmlRopidParser.platnostOd);
        ui->calendarWidget->setMaximumDate(xmlRopidParser.platnostDo);
    }
    else
    {
        ui->calendarWidget->setMinimumDate(QDate(1900, 1, 1));
        ui->calendarWidget->setMaximumDate(QDate(3000, 1, 1));
    }
}




/*!

*/
void MainWindow::naplnVyberLinky(QVector<Linka> docasnySeznamLinek)
{
    qDebug() <<  Q_FUNC_INFO;
    vymazSeznam(ui->listLinek);



    //qDebug()<<"vymazano";
    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        //newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).lc));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listLinek->addItem( newItem);
    }

}







/*!
naplní seznam kmenových linek
*/
void MainWindow::naplnKmenoveLinky(QVector<Linka> docasnySeznamLinek)
{
    qDebug() <<  Q_FUNC_INFO;

    vymazSeznam(ui->listKmenovychLinek);

    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listKmenovychLinek->addItem( newItem);
    }
}


/*!

*/
void MainWindow::naplnVyberSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug() <<  Q_FUNC_INFO;


    vymazSeznam(ui->listSpoje);


    qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
    for (int i = 0; i < docasnySeznamSpoju.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamSpoju.at(i).cisloRopid));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamSpoju.at(i).cisloRopid ));
        ui->listSpoje->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberSpoje_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberSpoje_konec";

}



/*!

*/
void MainWindow::naplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listTurnusSpoje->count()!=0)
    {
        ui->listTurnusSpoje->clear();
    }
    qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
    for (int i = 0; i < docasnySeznamSpoju.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        QString linka=QString::number(docasnySeznamSpoju.at(i).linka.c);
        QString spoj=QString::number(docasnySeznamSpoju.at(i).cisloRopid);

        newItem->setText(linka+"/"+spoj);
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamSpoju.at(i).cisloRopid ));
        ui->listTurnusSpoje->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberTurnusSpoje_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberTurnusSpoje_konec";

}



/*!

*/
void MainWindow::naplnVyberPoradi(QVector<Obeh> docasnySeznamObehu)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listPoradi->count()!=0)
    {
        ui->listPoradi->clear();
    }
    for (int i = 0; i < docasnySeznamObehu.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamObehu.at(i).p));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamObehu.at(i).p ));
        ui->listPoradi->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberPoradi_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberPoradi_konec";

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

    if(this->stavSystemu.aktObeh.seznamSpoju.length()<=stavSystemu.indexSpojeNaObehu)
    {
        qDebug()<<"spoj odpovidajici indexu neexistuje";
        return;
    }

    vypisZastavkyTabulka(stavSystemu.indexAktZastavky,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.locationState);
    int delkaGlobalnihoSeznamu= this->stavSystemu.pocetZastavekAktualnihoSpoje();
    int indexZastavky=stavSystemu.indexAktZastavky;
    qDebug()<<"delka seznamu spoju "<<this->stavSystemu.aktObeh.seznamSpoju.length()<<" index "<<stavSystemu.indexSpojeNaObehu<<" delka globsezzast "<< delkaGlobalnihoSeznamu  << " indexAktZast "<<indexZastavky   ;

    if (indexZastavky>=delkaGlobalnihoSeznamu)
    {
        qDebug()<<"index zastavky je mimo rozsah";
        return;
    }

    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky+1));
    ui->label_aktLinka->setText(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).linka.LineNumber);
    ui->label_aktSpoj->setText(QString::number(this->stavSystemu.aktualniSpojNaObehu().cisloRopid));


    ui->locationStateIndicator->setText(stavSystemu.locationState);
}




/*!

*/
void MainWindow::on_pushButton_jizda_ubrat_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.indexAktZastavky>=2)
    {
        stavSystemu.indexAktZastavky--;
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

}





/*!

*/






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
void MainWindow::on_checkBox_stateChanged(int arg1)
{

    qDebug()<<"MainWindow::on_checkBox_stateChanged";
    stavSystemu.prestupy= ui->checkBox->isChecked();
}


/*!

*/
void MainWindow::on_pushButton_nast_nactiXMLropid_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    xmlRopidParser.otevriSoubor(xmlRopidParser.vstupniXmlSouborCesta);
    this->pracovniDatumPrvniDenDat();
    this->inicializaceVyberovychPoli();
}


/*!

*/
void MainWindow::on_pushButton_menu_nastaveni_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_nastaveni);

}




/*!

*/
void MainWindow::on_pushButton_nast_truncate_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    xmlRopidParser.truncateAll();
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
    ibisOvladani.dopocetCelni("l006");
    ibisOvladani.dopocetCelni("aA1 ahoj");
    ibisOvladani.dopocetCelni("v povel v\\");
    ibisOvladani.dopocetCelni("zA povel zA");
    ibisOvladani.dopocetCelni("zN povel zN");
    ibisOvladani.dopocetCelni("xC2");
}


/*!

*/
void MainWindow::on_pushButton_jizda_IBIS_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.dopocetCelni("xC2");
    ibisOvladani.odesliFrontKomplet(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliSideKomplet(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odeslikompletBUSEjednoradekAA(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliRearKomplet(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,stavSystemu.indexAktZastavky);
}




/*!

*/
int MainWindow::eventPrijezd()
{
    qDebug() <<  Q_FUNC_INFO;

    stavSystemu.doorState="DoorsOpen";


    if (stavSystemu.indexAktZastavky<(this->stavSystemu.pocetZastavekAktualnihoSpoje()-1))
    {
        hlasic.kompletZastavka(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloCis,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloOis);
    }
    else
    {
        hlasic.kompletKonecna(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis );
    }
    stavSystemu.locationState="AtStop";
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

    return 1;
}



/*!

*/
int MainWindow::eventOdjezd()
{
    qDebug() <<  Q_FUNC_INFO;




    timerAfterStopToBetweenStop->start();


    return 1;
}

void MainWindow::eventAfterStopToBetweenStop()
{
    qDebug() <<  Q_FUNC_INFO;
    if(Pasmo::podminkaHlasitZmenuPasma(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky-1].zastavka.seznamPasem,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.seznamPasem))
    {
        qDebug()<<"srovnani pasem zastavek "<<this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky-1].zastavka.StopName<<" a "<<this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.StopName;
        eventZmenaTarifnihoPasma();
    }
    else
    {
        eventSkryjZmenuTarifnihoPasma();
    }

}



/*!

*/
void MainWindow::on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listLinek->count()<=0)
    {
        qDebug()<<"seznam je prazdny";
        return;
    }
    ui->polelinky->setText(ui->listLinek->currentItem()->data(Qt::UserRole ).toString() );
    stavSystemu.aktlinka.c=ui->listLinek->currentItem()->data(Qt::UserRole).toString().toInt();
    qDebug()<<"tady budu vypisovat vybrane spoje";
    qDebug()<<"raw "<<ui->listLinek->currentItem()->data(Qt::UserRole)<<" int "<<ui->listLinek->currentItem()->data(Qt::UserRole).toInt();
    ui->listSpoje->clear();
    if (sqlPraceRopid.vytvorSeznamSpoju(seznamSpoju,stavSystemu.aktlinka, this->vyrobMaskuKalendareJizd())==1)
    {
        naplnVyberSpoje(seznamSpoju);
    }
}


/*!

*/
void MainWindow::on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->poleLinkyTurnus->setText(ui->listKmenovychLinek->currentItem()->data(Qt::UserRole ).toString() );

    stavSystemu.aktObeh.kmenovaLinka.c=ui->listKmenovychLinek->currentItem()->data(Qt::UserRole).toInt();

    ui->listPoradi->clear();

    ui->listTurnusSpoje->clear();

    if (sqlPraceRopid.vytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd() )==1)
    {

        naplnVyberPoradi(seznamObehu);


    }
}



/*!

*/
void MainWindow::on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listPoradi->count()!=0)
    {
        if(ui->listPoradi->currentRow()!=-1)
        {
            qDebug()<<"xx"+ QString::number( ui->listPoradi->currentRow());
            qDebug()<<"current item:"+ui->listPoradi->currentItem()->data(Qt::UserRole).toString();
            stavSystemu.aktObeh.p=ui->listPoradi->currentItem()->data(Qt::UserRole).toInt() ;
            if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.aktObeh,this->vyrobMaskuKalendareJizd())==1)
            {
                naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
            }


        }

    }
}




/*!

*/
void MainWindow::on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listSpoje->count()!=0)
    {
        if(ui->listSpoje->currentRow()!=-1)
        {

            qDebug()<<"xx"+ QString::number( ui->listSpoje->currentRow());
            qDebug()<<"current item:"+ui->listSpoje->currentItem()->data(Qt::UserRole).toString();
            ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
            int indexVyberu=ui->listSpoje->currentRow();
            stavSystemu.aktspoj=seznamSpoju.at(indexVyberu);
            int kmenovaLinka=0;
            int poradi=0;
            int order=0;
            sqlPraceRopid.najdiTurnusZeSpoje(stavSystemu.aktspoj, kmenovaLinka,poradi, order,this->vyrobMaskuKalendareJizd());
            qDebug()<<"test spoje do turnusu "<<kmenovaLinka<<"/"<<poradi<<" "<<order;
        }

    }
}



/*!

*/
void MainWindow::on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() <<  Q_FUNC_INFO;
    if (ui->listTurnusSpoje->count()!=0)
    {
        if(ui->listTurnusSpoje->currentRow()!=-1)
        {
            qDebug()<<"xx"+ QString::number( ui->listTurnusSpoje->currentRow());
            qDebug()<<"current item:"+ui->listTurnusSpoje->currentItem()->data(Qt::UserRole).toString();
            int zvolenaPolozka=ui->listTurnusSpoje->currentRow();
            qDebug()<<"current row "<<zvolenaPolozka;
            qDebug()<<"delka seznamu spoju"<<stavSystemu.aktObeh.seznamSpoju.size()<<" zvolena polozka "<<zvolenaPolozka;

            if(! MainWindowPomocne::jeVRozsahu(zvolenaPolozka,stavSystemu.aktObeh.seznamSpoju.size(),"MainWindow::on_listTurnusSpoje_currentItemChanged"))
            {

                return;
            }


            stavSystemu.aktspoj=stavSystemu.aktObeh.seznamSpoju.at(zvolenaPolozka);
            ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
            ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));
        }
    }
}





/*!

*/
void MainWindow::on_pushButton_menu_jizda_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_jizda );

}




/*!

*/
void MainWindow::inicializacePoli()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.aktObeh.seznamSpoju.clear();
    seznamLinek.clear();
    seznamSpoju.clear();
    stavSystemu.vymaz();
}



/*!

*/
void MainWindow::on_pushButton_manual_smazOkno_clicked()
{
    ui->plainTextEditCustomXml->clear();
}

void MainWindow::on_pushButton_menu_manual_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_manual );

}



/*!

*/
void MainWindow::on_pushButton_manual_odesliXml_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray vysledek2="";
    vysledek2=vysledek2+ui->plainTextEditCustomXml->toPlainText().toUtf8();
    customerInformationService1_0.nastavObsahTela("AllData",vysledek2);
    customerInformationService2_2CZ1_0.nastavObsahTela("AllData",vysledek2);
    for(int i=0;i<customerInformationService1_0.seznamSubscriberu.count();i++ )
    {
        customerInformationService1_0.PostDoDispleje(customerInformationService1_0.seznamSubscriberu[i].adresa,vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";
}



/*!

*/
void MainWindow::vypisSubscribery1_0(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->seznamOdberatelu->setRowCount(0);
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
            row = ui->seznamOdberatelu->rowCount();
            ui->seznamOdberatelu->insertRow(row);
            cell = new QTableWidgetItem(odberatel.adresa.toString());
            ui->seznamOdberatelu->setItem(row, 0, cell);


            cell = new QTableWidgetItem(odberatel.struktura);
            ui->seznamOdberatelu->setItem(row, 1, cell);
            ui->seznamOdberatelu->resizeColumnsToContents();
        }
        qDebug()<<"vracim 1";
    }


}




/*!

*/



void MainWindow::vypisSubscribery2_2CZ(QVector<Subscriber> adresy)
{
    qDebug() <<  Q_FUNC_INFO;

    ui->seznamOdberatelu2->setRowCount(0);

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
            row = ui->seznamOdberatelu2->rowCount();
            ui->seznamOdberatelu2->insertRow(row);
            cell = new QTableWidgetItem(odberatel.adresa.toString());

            ui->seznamOdberatelu2->setItem(row, 0, cell);
            cell = new QTableWidgetItem(odberatel.struktura);
            ui->seznamOdberatelu2->setItem(row, 1, cell);
            ui->seznamOdberatelu2->resizeColumnsToContents();


        }
        qDebug()<<"vracim 1";
    }
}





/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_clicked()
{
    vypisDiagnostika(customerInformationService1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}



/*!

*/
void MainWindow::on_pushButton_manual_addsubscriber_2_clicked()
{
    vypisDiagnostika( customerInformationService2_2CZ1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}


/*!

*/
void MainWindow::on_pushButton_manual_removeSubscriber_clicked()
{
    if (ui->seznamOdberatelu->rowCount()==0)
    {

        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->seznamOdberatelu->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrnao");
        return;
    }
    int indexPolozky = ui->seznamOdberatelu->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService1_0.odstranitSubscribera(indexPolozky)==1)
    {
        vypisSubscribery1_0(customerInformationService1_0.seznamSubscriberu);
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
    if (ui->seznamOdberatelu2->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->seznamOdberatelu2->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->seznamOdberatelu2->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_2CZ1_0.odstranitSubscribera(indexPolozky)==1)
    {
        vypisSubscribery2_2CZ(customerInformationService2_2CZ1_0.seznamSubscriberu);
        vypisDiagnostika("odstraneno");
    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


/*!

*/
void MainWindow::on_pushButton_nast_hlaseniSlozka_clicked()
{
    qDebug()<<"nastavena cesta k hlaseni na "<<ui->lineEditHlaseniCesta->text();
    //hlasic.cesta=ui->lineEditHlaseniCesta->text();
    hlasic.nastavCestu(ui->lineEditHlaseniCesta->text());
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
void MainWindow::vypisSqlVysledek(QString vstup)
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
void MainWindow::on_pushButton_menu2_palPc_clicked()
{
    ui->stackedWidget_hlavni->setCurrentIndex(0);
}


/*!

*/
void MainWindow::on_pushButton_menu_testRozhrani_clicked()
{
    ui->stackedWidget_hlavni->setCurrentIndex(1);
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

*/
void MainWindow::on_pushButton_nast_xmlVyberCestu_clicked()
{
    xmlRopidParser.vstupniXmlSouborCesta=otevriSouborXmlDialog();
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
    qDebug()<<"MainWindow::nastavLabelCestyXml()";
    ui->label_cestaXml->setText(xmlRopidParser.vstupniXmlSouborCesta);

}


/*!

*/
QString MainWindow::otevriSouborXmlDialog()
{
    qDebug() <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), "",
                                                    tr("XML Ropid JŘ (*.xml);;All Files (*)"));
    return fileName;
}


/*!

*/
void MainWindow::on_calendarWidget_selectionChanged()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.pracovniDatum=ui->calendarWidget->selectedDate();
    aktualizacePracovnihoData();
}



/*!

*/
void MainWindow::aktualizacePracovnihoData()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->dateEdit->setDate(stavSystemu.pracovniDatum);
    ui->calendarWidget->setSelectedDate(stavSystemu.pracovniDatum);

    qDebug()<<"od "<<xmlRopidParser.platnostOd<<" do "<<xmlRopidParser.platnostDo<<" pracovni "<<stavSystemu.pracovniDatum ;
    qDebug()<<"dnu do pracovnihodata "<< stavSystemu.pracovniDatum.daysTo(xmlRopidParser.platnostOd) <<" dnu do zacatku platnosti " << stavSystemu.pracovniDatum.daysTo(xmlRopidParser.platnostDo);


    this->vyrobMaskuKalendareJizd();
    sqlPraceRopid.maskaKalendarJizd(this->stavSystemu.pracovniDatum,xmlRopidParser.platnostOd,xmlRopidParser.platnostDo);

    inicializaceVyberovychPoli();
}

/*!

*/
void MainWindow::pracovniDatumDnes()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.pracovniDatum=QDate::currentDate();
    aktualizacePracovnihoData();
}


/*!

*/
void MainWindow::pracovniDatumPrvniDenDat()
{
    qDebug() <<  Q_FUNC_INFO;
    aktualizaceKalendare();


    stavSystemu.pracovniDatum=xmlRopidParser.platnostOd;
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
    return sqlPraceRopid.maskaKalendarJizd(stavSystemu.pracovniDatum,xmlRopidParser.platnostOd, xmlRopidParser.platnostDo);
}



void MainWindow::vypisZastavkyTabulka(int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState)
{

    qDebug() <<  Q_FUNC_INFO;
    ui->tableWidgetNasledujiciZastavky->setRowCount(0);



    for (int i=0;i<(docasnySeznamZastavek.count());i++)
    {
        QString cisloZastavky = QString::number(i+1);
        QString nazevZastavky2 = docasnySeznamZastavek.at(i).zastavka.StopName;
        QString odjezdZeZastavky =  sqlPraceRopid.vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).zastavka.DepartureTime);
        QString pasma= sqlPraceRopid.pasmaDoStringu(docasnySeznamZastavek.at(i).zastavka.seznamPasem,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).zastavka.naZnameni==true)
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
        ui->tableWidgetNasledujiciZastavky->scrollToItem(ui->tableWidgetNasledujiciZastavky->item(cisloporadi,0));
    }
}

void MainWindow::on_tableWidgetNasledujiciZastavky_cellClicked(int row, int column)
{
    qDebug()<<"on_tableWidgetNasledujiciZastavky_cellClicked";
    stavSystemu.locationState="AtStop";
    ui->pushButton_jizda_atStop->setChecked(true);
    stavSystemu.indexAktZastavky=row;
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

    qDebug()<<"index "<<stavSystemu.indexSpojeNaObehu<<" pocetSpoju "<<stavSystemu.aktObeh.seznamSpoju.count();
    if ((stavSystemu.indexSpojeNaObehu)<(stavSystemu.aktObeh.seznamSpoju.count()-1))
    {
        stavSystemu.indexSpojeNaObehu++;
        stavSystemu.indexAktZastavky=0;
        // AktualizaceDispleje();
        natahniSeznamSpojeKomplet();
        xmlVdv301HromadnyUpdate();
    }
    else
    {
        qDebug()<<"posledni spoj ze seznamu, nelze se dale posouvat";
    }




}

/*!
 * \brief MainWindow::dalsiSpojNavazujici přepnutí na další spoj na oběhu při existenci návazného spoje
 */
void MainWindow::dalsiSpojNavazujici()
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"index "<<stavSystemu.indexSpojeNaObehu<<" pocetSpoju "<<stavSystemu.aktObeh.seznamSpoju.count();
    if ((stavSystemu.indexSpojeNaObehu)<(stavSystemu.aktObeh.seznamSpoju.count()-1))
    {
        stavSystemu.indexSpojeNaObehu++;
        stavSystemu.indexAktZastavky=0;
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
    stavSystemu.zobrazZmenuPasma=true;
    xmlVdv301HromadnyUpdate();
    hlasic.kompletZmenaTarifnihoPasma();


    timerTrvaniZmenyPasma->start();

}

void MainWindow::eventZobrazOznameni(int index, QVector<SpecialniHlaseni> seznamHlaseni)
{
    qDebug() <<  Q_FUNC_INFO;

    if((index>=0)&&(index<seznamHlaseni.count()))
    {

        stavSystemu.aktivniSpecialniHlaseni=seznamHlaseni.at(index);
        stavSystemu.jeSpecialniHlaseni=true;
        //zobraz na panely
        xmlVdv301HromadnyUpdate();
        timerSpecialniOznameniSmazat.start();
    //spust hlaseni
        hlasic.kompletSpecialniHlaseni(stavSystemu.aktivniSpecialniHlaseni);


    }




}

void MainWindow::eventSkryjZmenuTarifnihoPasma()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.zobrazZmenuPasma=false;
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



void MainWindow::on_checkBox_MpvTurnusy_stateChanged(int arg1)
{
    qDebug() <<  Q_FUNC_INFO;
    arg1=1;

    stavSystemu.prestupy= ui->checkBox_MpvTurnusy->isChecked();
}


void MainWindow::eventVstupDoVydeje()
{
    qDebug() <<  Q_FUNC_INFO;
}

void MainWindow::eventOpusteniVydeje()
{
    qDebug() <<  Q_FUNC_INFO;

    timerAfterStopToBetweenStop->stop();
    timerStahniPrestupy.stop();
    timerTrvaniZmenyPasma->stop();
    resetSeznamuSpoju();
    customerInformationService1_0.mimoVydej();
    customerInformationService2_2CZ1_0.mimoVydej();
    xmlVdv301HromadnyUpdate();
    inicializaceVyberovychPoli();
}

void MainWindow::resetSeznamuSpoju()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.vymaz();
}

/*!

*/
void MainWindow::on_pushButton_menu_linkospoj_clicked()
{
    eventOpusteniVydeje();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_linkaspoj );

}





void MainWindow::on_pushButton_jizda_pridat_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    if (stavSystemu.indexAktZastavky<(this->stavSystemu.pocetZastavekAktualnihoSpoje()-1))
    {
        stavSystemu.indexAktZastavky++;
    }
    else
    {
        this->dalsiSpoj();
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
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
     stavSystemu.jeSpecialniHlaseni=false;
     xmlVdv301HromadnyUpdate();
}
