#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>


//MAIN



//koment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    konfigurace(QCoreApplication::applicationDirPath()),
    settings(QCoreApplication::applicationDirPath()+"/nastaveni.ini", QSettings::IniFormat),
    golemio(""), //klic do golemia
    logfile(QCoreApplication::applicationDirPath()),
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",47477,"1.0"), //47477
    customerInformationService1_0("CustomerInformationService","_ibisip_http._tcp",47479,"1.0"),
    customerInformationService2_2CZ1_0("CustomerInformationService","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    customerInformationService2_4("CustomerInformationService","_ibisip_http._tcp",47481,"2.4"),
    //customerInformationService2_2CZ1_0("CustomerInformationService (2)","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    ticketValidationService2_3CZ1_0("TicketValidationService","_ibisip_http._tcp",47483,"2.2CZ1.0"),
    //deviceManagementServiceSubscriber("DeviceManagementService","DeviceStatus","2.2CZ1.0","_ibisip_http._tcp",48477),//puvodni port 48479, novy 59631
    deviceManagementServiceSubscriber("DeviceManagementService","DeviceStatus","2.2CZ1.0","_ibisip_http._tcp",48477),

    ui(new Ui::MainWindow)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->setupUi(this);

    ui->pushButton_menu_jizda->setEnabled(false);
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );
    ui->tabWidget_hlavni->setCurrentWidget(ui->tab_palPC);
    ui->pushButton_menu_turnus->setChecked(true);
    ui->pushButton_nast_nactiXMLropid->setDisabled(true);

    vektorCis.push_back(&customerInformationService1_0);
    vektorCis.push_back(&customerInformationService2_2CZ1_0);
    vektorCis.push_back(&customerInformationService2_4);

    //QString konstantaPocetDni=settings.value("konstanty/pocetDni").toString();
    //settings.setValue("golemio/api-key","XXX");

    mapaVykresleni.setCestaMapa(QCoreApplication::applicationDirPath());



    QTranslator translator;
    //settings.setValue("General/language","en");
    QString jazyk=settings.value("app/language").toString();

    qDebug()<<" novy jazyk:"<<jazyk;
    if (jazyk=="en")
    {
        qApp->removeTranslator(&translator);
        translator.load(":/lang_en.qm");
        qApp->installTranslator(&translator);
        ui->calendarWidget->setLocale(QLocale::English);
        qDebug()<<"zmena jazyka";
    }
    ui->retranslateUi(this);


    natahniKonstanty();

    //ui->stackedWidget_palPc->setWindowState(Qt::WindowFullScreen);


    //inicializace databaze
    inicializaceVyberovychPoli();

    //propojeni vsech slotu
    vsechnyConnecty();

    on_pushButton_nactiDetekce_clicked();



    nastartujSluzbuZeZasobniku(vektorCis);

    //nastartujVsechnyVdv301Sluzby();


    //vyplneni polozky build pro rozliseni zkompilovanych verzi
    //QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);



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
    timerTrvaniZmenyPasma->setSingleShot(true);
    timerTrvaniZmenyPasma->setInterval(konfigurace.trvaniZobrazeniPasma);

    timerSpecialniOznameniSmazat.setSingleShot(true);
    timerSpecialniOznameniSmazat.setInterval(konfigurace.trvaniZobrazeniOznameni);

    timerStahniPrestupy.setInterval(konfigurace.intervalStahovaniPrestupu);

    timerAfterStopToBetweenStop.setSingleShot(true);
    timerAfterStopToBetweenStop.setInterval(konfigurace.intervalAfterStopToBetweenStop);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::nastartujSluzbuZeZasobniku(QVector<CustomerInformationService*> &seznamSluzeb)
{
    if(!seznamSluzeb.isEmpty())
    {
        CustomerInformationService* aktualniSluzba=seznamSluzeb.takeFirst();
        qDebug()<<"v zasobniku zustava sluzeb: "<<seznamSluzeb.count();
        aktualniSluzba->slotStartServer();
    }
}

void MainWindow::slotSluzbaVratilaVysledekStartu(QString nastartovanaSluzba)
{
    qDebug()<<Q_FUNC_INFO<<" "<<nastartovanaSluzba;
    nastartujSluzbuZeZasobniku(vektorCis);

}

void MainWindow::natahniKonstanty()
{
    qDebug()<<Q_FUNC_INFO;


    if(settings.value("golemio/adresa").isNull())
    {
        eventPoznamkaRidici("konfiguracni soubor neexistuje/je vadny");
    }
    else
    {
        qDebug()<<"konfiguracni soubor nacten";
    }
    qDebug()<<" konstanty status "<<settings.status();


    if(settings.value("golemio/datovyZdroj").toString()=="mpvnet")
    {
        pouzitGolemio=false;
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
    deviceManagementService1_0.slotAktualizaceDat();

    deviceManagementService1_0.setCisloPortu(settings.value("deviceManagementService1_0/port").toInt() ); //47477
    customerInformationService1_0.setCisloPortu(settings.value("customerInformationService1_0/port").toInt() );
    customerInformationService2_2CZ1_0.setCisloPortu(settings.value("customerInformationService2_2CZ1_0/port").toInt() );
    customerInformationService2_4.setCisloPortu(settings.value("customerInformationService2_4/port").toInt() );

}



/*!
přesunutí connectů pro větší přehlednost
*/
void MainWindow::vsechnyConnecty()
{
    qDebug()<<Q_FUNC_INFO;
    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery1_0);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery2_2CZ);
    this->vypisSubscribery1_0(customerInformationService1_0.seznamSubscriberu);
    this->vypisSubscribery2_2CZ(customerInformationService2_2CZ1_0.seznamSubscriberu);

    connect(&customerInformationService1_0,&HttpSluzba::signalSluzbaPublikovana,this,&MainWindow::slotSluzbaVratilaVysledekStartu);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalSluzbaPublikovana,this,&MainWindow::slotSluzbaVratilaVysledekStartu);
    connect(&customerInformationService2_4,&HttpSluzba::signalSluzbaPublikovana,this,&MainWindow::slotSluzbaVratilaVysledekStartu);


    connect(&xmlMpvParser,&XmlMpvParser::stazeniHotovo,this,&MainWindow::slotMpvNetReady);
    connect(&golemio,&Golemio::stazeniHotovo,this,&MainWindow::slotGolemioReady);

    //vypis deviceMAnagementServices publisheru
    // connect(&deviceManagementServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::slotXmlDoPromenne);


    //connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::aktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);
    connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::signalAktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);


    //connect(deviceManagementServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    // connect(&deviceManagementServiceSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);

    //vypis stavu testu
    connect(&vzorovyTest,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);
    connect(&testOdberuServer,&Vdv301testy::update,this,&MainWindow::testyVykresliCasti);

    //jednotliveTesty
    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalVypisSubscriberu,&testOdberuServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&testOdberuServer,&TestOdberuServer::signalVymazSeznamOdberatelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotVymazSubscribery);
    connect(&testOdberuServer,&TestOdberuServer::signalNastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotStartDnsSd);
    connect(&testOdberuServer,&TestOdberuServer::signalZastavCisTimer,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotZastavCasovac);
    connect(&testOdberuServer,&TestOdberuServer::signalOdesliDataDoPanelu,&customerInformationService2_2CZ1_0,&CustomerInformationService::slotTedOdesliNaPanely);

    connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalVypisSubscriberu,&testOdberuServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalOdpovedNaPost,&testOdberuServer,&TestOdberuServer::slotVypisOdpovedServeru);

    //vypinani sluzeb pomoci prepinacu
    connect(ui->radioButton_ON1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpSluzba::slotStartDnsSd);
    connect(ui->radioButton_OFF1,&QRadioButton::clicked,&customerInformationService2_2CZ1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpSluzba::slotStartDnsSd);
    connect(ui->radioButton_OFF2,&QRadioButton::clicked,&deviceManagementService1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpSluzba::slotStartDnsSd);
    connect(ui->radioButton_OFF3,&QRadioButton::clicked,&ticketValidationService2_3CZ1_0,&HttpSluzba::slotStop);

    connect(ui->radioButton_ON4,&QRadioButton::clicked,&customerInformationService1_0,&HttpSluzba::slotStartDnsSd);
    connect(ui->radioButton_OFF4,&QRadioButton::clicked,&customerInformationService1_0,&HttpSluzba::slotStop);

    //vypisovani stavovych hlasek do stavoveho radku vespod okna
    connect(&sqlPraceRopid,&SqlRopidXmlDotazy::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(&sqlPraceRopid,&SqlRopidXmlDotazy::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);

    //  connect(&xmlRopidImportStream,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);

    // connect(this,&MainWindow::signalZahajImport, &xmlRopidImportStream,&XmlRopidImportStream::slotOtevriSoubor);

    //prepinani stavu radio prepinacu podle stavu sluzeb
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio1);
    connect(&deviceManagementService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio2);
    connect(&ticketValidationService2_3CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio3);
    connect(&customerInformationService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio4);

    //konfigurace
    connect(&konfigurace,&Konfigurace::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);

    //casovace
    connect(timerTrvaniZmenyPasma,&QTimer::timeout,this,&MainWindow::eventSkryjZmenuTarifnihoPasma);
    connect(&timerAfterStopToBetweenStop,&QTimer::timeout,this,&MainWindow::eventAfterStopToBetweenStop);
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

    QVector<Prestup> prestupy;

    cisAktualizaceObsahu(prestupy,stavSystemu);

    ticketValidationService2_3CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
    deviceManagementService1_0.aktualizaceObsahuSluzby();
}

void MainWindow::slotStahniPrestupyAktZastavky()
{
    qDebug() <<  Q_FUNC_INFO;
    Zastavka aktZastavka=stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka;
    if(pouzitGolemio)
    {
        golemio.stahniMpvXml(aktZastavka.cisloCis, aktZastavka.ids);
    }
    else
    {
        xmlMpvParser.stahniMpvXml(aktZastavka.cisloCis, aktZastavka.ids);
    }


}


/*!

*/
void MainWindow::slotMpvNetReady()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    xmlMpvParser.naplnVstupDokument(xmlMpvParser.stazenaData);
    QVector<PrestupMPV> prestupyMpv=xmlMpvParser.parsujDomDokument();
    if(filtrovatPrestupy)
    {
        prestupyMpv=xmlMpvParser.vyfiltrujPrestupy(prestupyMpv,stavSystemu.aktlinka);
    }
    QVector<Prestup> prestupy;
    foreach(auto polozka, prestupyMpv)
    {
        prestupy.push_back(polozka.toPrestup());
    }


    cisAktualizaceObsahu(prestupy,stavSystemu);
}

void MainWindow::slotGolemioReady()
{
    qDebug() <<  Q_FUNC_INFO;
    //qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    golemio.naplnVstupDokument(golemio.stazenaData);
    QVector<PrestupGolemio> prestupyGolemio=golemio.parsujDomDokument();

    qDebug()<<"bum10";

    QVector<Prestup> prestupy;
    foreach(auto polozka,prestupyGolemio)
    {
        prestupy.push_back(polozka.toPrestup());
    }
    qDebug()<<"bum11";
    if(filtrovatPrestupy)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }
    qDebug()<<"pocet Prestupu ve vektoru: "<<prestupy.count();

    cisAktualizaceObsahu(prestupy,stavSystemu);

}


void MainWindow::cisAktualizaceObsahu(QVector<Prestup> prestupy, CestaUdaje mStavSystemu )
{
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,mStavSystemu );
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,mStavSystemu);
    customerInformationService2_4.aktualizaceObsahuSluzby(prestupy,mStavSystemu);
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


    /*
    if (sqlPraceRopid.vytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd() )==1)
    {
        naplnVyberPoradi(seznamObehu);
    }
    */


    stavSystemu.aktObeh.p=poradi ;
    if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.aktObeh,this->vyrobMaskuKalendareJizd())==1)
    {
        // naplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);
    }


    Spoj hledanySpoj=stavSystemu.aktspoj;
    stavSystemu.indexSpojeNaObehu=sqlPraceRopid.poziceSpojeNaSeznamu(stavSystemu.aktObeh.seznamSpoju,hledanySpoj);

    if(! MainWindowPomocne::jeVRozsahu(stavSystemu.indexSpojeNaObehu,stavSystemu.aktObeh.seznamSpoju.size(),Q_FUNC_INFO))
    {
        return 0;
    }

    stavSystemu.aktspoj=stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexSpojeNaObehu);
    ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
    ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text();

    stavSystemu.indexAktZastavky=0;

    int vysledek=natahniSeznamSpojeKomplet();
    if (vysledek==1)
    {
        eventVstupDoVydeje();
    }
    return vysledek;
}


/*!

*/
int MainWindow::on_pushButton_turnus_prikaz_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text();

    stavSystemu.indexAktZastavky=0;

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

    if((ui->tableView_turnusSpoj->model()->rowCount()==0)&&(ui->listView_spoje->model()->rowCount()==0))
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
        eventVstupDoVydeje();
        // mapaVykresleni.vypisGpsDoHtml(stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,true,true,true,MapaVykresleni::WGS84);
    }
    return 1;
}




/*!

*/
void MainWindow::on_pushButton_jizda_sipkaDal_clicked()
{
    qDebug() <<  Q_FUNC_INFO;


    if (stavSystemu.indexAktZastavky<(this->stavSystemu.pocetZastavekAktualnihoSpoje()))
    {
        if((stavSystemu.locationState=="AtStop")&&((stavSystemu.indexAktZastavky<(stavSystemu.pocetZastavekAktualnihoSpoje()-1) )))
        {
            stavSystemu.locationState="AfterStop";
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

                eventPrijezd();
            }

            if(stavSystemu.locationState=="BetweenStop")
            {
                stavSystemu.locationState="BeforeStop";
            }

            if(stavSystemu.locationState=="AfterStop")
            {
                stavSystemu.locationState="BetweenStop";
                eventAfterStopToBetweenStop();
            }
        }
    }


    aktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";
    // ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky+1));
    xmlVdv301HromadnyUpdate();
}



void MainWindow::vykresliStav(QString stav)
{
    qDebug() <<  Q_FUNC_INFO;
    if(stav=="BeforeStop")
    {
        ui->pushButton_jizda_beforeStop->setChecked(true);
    }
    if(stav=="AtStop")
    {
        ui->pushButton_jizda_atStop->setChecked(true);
    }
    if(stav=="AfterStop")
    {
        ui->pushButton_jizda_afterStop->setChecked(true);
    }
    if(stav=="BetweenStop")
    {
        ui->pushButton_jizda_betweenStop->setChecked(true);
    }
    ui->locationStateIndicator->setText(stavSystemu.locationState);
}



/*!

*/
void MainWindow::on_pushButton_jizda_sipkaZpet_clicked()
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
 \fn void MainWindow::inicializaceVyberovychPoli()

pripoji se k databazi a naplni okna pro vyber spoju
*/
void MainWindow::inicializaceVyberovychPoli()
{
    qDebug() <<  Q_FUNC_INFO;
    sqlPraceRopid.pripoj();

    ui->listView_spoje->setModel(&prazdnyModel);

    ui->listView_poradi->setModel(&prazdnyModel);
    ui->tableView_turnusSpoj->setModel(&prazdnyModel);

    QSqlQueryModel* modelLinky=sqlPraceRopid.stahniSeznamLinekModel(this->vyrobMaskuKalendareJizd());
    QSqlQueryModel* modelKmenoveLinky=sqlPraceRopid.stahniSeznamKmenovychLinekModel(this->vyrobMaskuKalendareJizd());

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

        ui->listView_linky->setModel(modelLinky);
        ui->listView_linky->setModelColumn(modelLinky->record().indexOf("l.c"));

        ui->listView_kmenovaLinka->setModel(modelKmenoveLinky);
        ui->listView_kmenovaLinka->setModelColumn(modelKmenoveLinky->record().indexOf("l.c"));

        aktualizaceKalendare();
    }
    else
    {

        qDebug()<<"chyba nacitani linek";
    }
}



/*!
načte platnost a nastaví rozsahy klikatelných oblastí kalendáře
*/
void MainWindow::aktualizaceKalendare()
{
    qDebug() <<  Q_FUNC_INFO;
    if(sqlPraceRopid.nactiPlatnost(platnostOd,platnostDo))
    {
        ui->calendarWidget->setMinimumDate(platnostOd);
        ui->calendarWidget->setMaximumDate(platnostDo);
    }
    else
    {
        ui->calendarWidget->setMinimumDate(QDate(1900, 1, 1));
        ui->calendarWidget->setMaximumDate(QDate(3000, 1, 1));
    }
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


    vykresliStav(stavSystemu.locationState);
}


/*!

*/
void MainWindow::on_pushButton_jizda_sipkaZpetSkok_clicked()
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
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.prestupy= ui->checkBox->isChecked();
}


/*!

*/
void MainWindow::on_pushButton_nast_nactiXMLropid_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    //   emit signalZahajImport(xmlRopidImportStream.vstupniXmlSouborCesta);

    eventOpusteniVydeje();
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_turnus );


    XmlRopidImportStream *xmlRopidImportStream =  new XmlRopidImportStream();

    xmlRopidImportStream->truncateAll();

    xmlRopidImportStream->vstupniXmlSouborCesta=cestaXml;

    connect(xmlRopidImportStream,&XmlRopidImportStream::resultReady, this, &MainWindow::slotImportDokoncen);
    connect(xmlRopidImportStream,&XmlRopidImportStream::finished, xmlRopidImportStream, &QObject::deleteLater);
    connect(xmlRopidImportStream,&XmlRopidImportStream::finished, this, &MainWindow::slotImportAktivujTlacitka);

    connect(xmlRopidImportStream,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisSqlVysledek);
    connect(xmlRopidImportStream,&XmlRopidImportStream::signalNastavProgress,this,&MainWindow::slotNastavProgress);
    connect(xmlRopidImportStream,&XmlRopidImportStream::signalNastavProgressMax,this,&MainWindow::slotNastavProgressMax);

    xmlRopidImportStream->start();


    //xmlRopidImportStream.otevriSoubor(xmlRopidImportStream.vstupniXmlSouborCesta);

}




void MainWindow::slotNastavProgress(int hodnota)
{
    ui->progressBar_importXml->setValue(hodnota);
    // qDebug()<<QString::number(hodnota)<<"/"<<QString::number(ui->progressBar->maximum());
}


void MainWindow::slotNastavProgressMax(int hodnota)
{
    //resetujProgressBar();
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(hodnota);
    ui->progressBar_importXml->setMaximum(hodnota);
}

void MainWindow::slotImportDokoncen()
{
    qDebug() <<  Q_FUNC_INFO;
    this->pracovniDatumPrvniDenDat();
    this->inicializaceVyberovychPoli();
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
void MainWindow::on_pushButton_nast_truncate_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    XmlRopidImportStream *xmlRopidImportStream =  new XmlRopidImportStream();
    xmlRopidImportStream->truncateAll();
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
    ibisOvladani.dopocetKontrolnihoZnaku("l006");
    // ibisOvladani.dopocetKontrolnihoZnaku("aA1 ahoj");
    // ibisOvladani.dopocetKontrolnihoZnaku("v povel v\\");
    // ibisOvladani.dopocetKontrolnihoZnaku("zA povel zA");
    // ibisOvladani.dopocetKontrolnihoZnaku("zN povel zN");
    // ibisOvladani.dopocetKontrolnihoZnaku("xC2");
}


/*!

*/
void MainWindow::on_pushButton_jizda_IBIS_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    ibisOvladani.dopocetKontrolnihoZnaku("xC2");
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
        hlasic.kompletZastavka(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka,this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka);
    }
    else
    {
        hlasic.kompletKonecna(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka);
    }



    stavSystemu.locationState="AtStop";
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

    QVector<QString> poznamky=this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.seznamPoznamek;
    qDebug()<<"poznamek je tolik: "<<QString::number(poznamky.count());
    foreach(QString poznamka, poznamky)
    {
        eventPoznamkaRidici(poznamka);
    }

    return 1;
}



/*!

*/
int MainWindow::eventOdjezd()
{
    qDebug() <<  Q_FUNC_INFO;

    if(stavSystemu.indexAktZastavky==1)
    {
        hlasic.kompletOdjezdPrvniZastavka(this->stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka);
    }

    timerAfterStopToBetweenStop.start();


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
    stavSystemu.locationState="BetweenStop";
    aktualizaceDispleje();
    xmlVdv301HromadnyUpdate();

}


/*!

*/
void MainWindow::on_pushButton_menu_jizda_clicked()
{
    ui->stackedWidget_palPc->setCurrentWidget(ui->page_jizda );

}


/*!

*/
void MainWindow::on_pushButton_manual_smazOkno_clicked()
{
    ui->plainTextEditCustomXml->clear();
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
    for(int i=0;i<customerInformationService2_2CZ1_0.seznamSubscriberu.count();i++ )
    {
        customerInformationService2_2CZ1_0.PostDoDispleje(customerInformationService2_2CZ1_0.seznamSubscriberu[i].adresa,vysledek2);
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
void MainWindow::slotVypisSqlVysledek(QString vstup)
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
 * \brief popis
 */
void MainWindow::on_pushButton_nast_xmlVyberCestu_clicked()
{
    cestaXml=otevriSouborXmlDialog(cestaXml);
    if (cestaXml=="")
    {
        ui->pushButton_nast_nactiXMLropid->setDisabled(true);
    }
    else
    {
        ui->pushButton_nast_nactiXMLropid->setDisabled(false);

    }
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
    qDebug() <<  Q_FUNC_INFO;
    ui->label_cestaXml->setText(cestaXml);

}


/*!

*/
QString MainWindow::otevriSouborXmlDialog(QString cesta)
{
    qDebug() <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), cesta,
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

    qDebug()<<"od "<<platnostOd<<" do "<<platnostDo<<" pracovni "<<stavSystemu.pracovniDatum ;
    qDebug()<<"dnu do pracovnihodata "<< stavSystemu.pracovniDatum.daysTo(platnostOd) <<" dnu do zacatku platnosti " << stavSystemu.pracovniDatum.daysTo(platnostDo);


    this->vyrobMaskuKalendareJizd();
    sqlPraceRopid.maskaKalendarJizd(this->stavSystemu.pracovniDatum,platnostOd,platnostDo);

    inicializaceVyberovychPoli();
}

/*!
\brief popis
xxxxxx
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


    stavSystemu.pracovniDatum=platnostOd;
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
    return sqlPraceRopid.maskaKalendarJizd(stavSystemu.pracovniDatum,platnostOd, platnostDo);
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
        ui->tableWidgetNasledujiciZastavky->resizeRowsToContents();
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

void MainWindow::eventPoznamkaRidici(QString poznamka)
{
    qDebug() <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(nahradZnacky(poznamka));
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
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
    ui->pushButton_menu_jizda->setDisabled(false);
}

void MainWindow::eventOpusteniVydeje()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->pushButton_menu_jizda->setDisabled(true);
    timerAfterStopToBetweenStop.stop();
    timerStahniPrestupy.stop();
    timerTrvaniZmenyPasma->stop();
    resetSeznamuSpoju();

    customerInformationService1_0.mimoVydej();
    customerInformationService2_2CZ1_0.mimoVydej();
    customerInformationService2_4.mimoVydej();

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


void MainWindow::on_pushButton_jizda_sipkaDalSkok_clicked()
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

void MainWindow::on_radioButton_singleDoorOpen_clicked()
{
    stavSystemu.doorState="SingleDoorOpen";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_allDoorsClosed_clicked()
{
    stavSystemu.doorState="AllDoorsClosed";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_doorsOpen_clicked()
{
    stavSystemu.doorState="DoorsOpen";
    xmlVdv301HromadnyUpdate();
}


void MainWindow::on_radioButton_singleDoorCloser_clicked()
{
    stavSystemu.doorState="SingleDoorClosed";
    xmlVdv301HromadnyUpdate();
}

void MainWindow::slotAktualizaceTabulkySluzeb()
{
    qDebug()<<"MainWindow::slotAktualizaceTabulkySluzeb";
    vykresliSluzbyDoTabulky(deviceManagementServiceSubscriber.seznamZarizeniDetekce, deviceManagementServiceSubscriber.seznamZarizeniKonfigurace);
}

void MainWindow::vykresliSluzbyDoTabulky(QVector<DevMgmtPublisherStruct> seznamSluzebDetekce, QVector<DevMgmtPublisherStruct> seznamSluzebKonfigurace)
{
    qDebug() <<  Q_FUNC_INFO;
    // ui->tabulkaSubscriberu->setRowCount(0);
    vymazTabulkuSubscriberu(ui->tableWidget_seznamZarizeni);


    foreach(auto sluzba, seznamSluzebDetekce)
    {
        sluzbaDoTabulky(sluzba);
    }

    foreach(DevMgmtPublisherStruct sluzba, seznamSluzebKonfigurace)
    {
        if(!sluzba.isInListByIdClass(seznamSluzebDetekce))
        {
            sluzbaDoTabulky(sluzba);
        }

    }
}

void MainWindow::vymazTabulkuSubscriberu(QTableWidget *tableWidget)
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
void MainWindow::sluzbaDoTabulky(DevMgmtPublisherStruct zarizeni)
{
    //QZeroConfService zcs
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString sluzbaNazev=zarizeni.serviceName;
    QString ipadresa=zarizeni.adresa.toString() ;
    QString hostName=zarizeni.hostname;
    QString verze=zarizeni.ibisIpVersion;
    QString deviceClass=zarizeni.deviceClass;
    QString id=zarizeni.deviceId;
    int port=zarizeni.port;
    int hwConfig=zarizeni.hwConfig;
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;
 */

    row = ui->tableWidget_seznamZarizeni->rowCount();
    ui->tableWidget_seznamZarizeni->insertRow(row);

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
    ui->tableWidget_seznamZarizeni->setItem(row, 0, cell);


    cell = new QTableWidgetItem(deviceClass);
    ui->tableWidget_seznamZarizeni->setItem(row, 1, cell);

    cell = new QTableWidgetItem(id);
    ui->tableWidget_seznamZarizeni->setItem(row, 2, cell);

    cell = new QTableWidgetItem(hostName);
    ui->tableWidget_seznamZarizeni->setItem(row, 3, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tableWidget_seznamZarizeni->setItem(row, 4, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_seznamZarizeni->setItem(row, 5, cell);

    cell = new QTableWidgetItem(sluzbaNazev);
    ui->tableWidget_seznamZarizeni->setItem(row, 6, cell);

    cell = new QTableWidgetItem(verze);
    ui->tableWidget_seznamZarizeni->setItem(row, 7, cell);


    ui->tableWidget_seznamZarizeni->resizeColumnsToContents();

    qDebug()<<"sluzbaDoTabulky_konec";
}


QString MainWindow::nahradZnacky(QString vstup)
{
    QString vysledek="";

    qDebug().noquote()<<"retezec pred: "<<vstup;
    //  vysledek=vstup.replace(QRegExp("a"),"b");



    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //qt5
    QRegExp vyraz=QRegExp("\\\\([^<]*)\\\\");
      vyraz.setMinimal(true);
#else
    //qt6

    QRegularExpression vyraz("\\\\([^<]*)\\\\");

#endif




    vysledek=vstup.replace(vyraz,"<b>\\1</b>");
    qDebug().noquote()<<"retezec po: "<<vysledek;

    return vysledek;
}


void MainWindow::on_listView_linky_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.aktlinka.c=index.data(Qt::DisplayRole).toString().toInt();
    qDebug()<<"cislo linky:"<<stavSystemu.aktlinka.c;
    modelSpoje=sqlPraceRopid.stahniSeznamSpojuModel(stavSystemu.aktlinka, this->vyrobMaskuKalendareJizd()) ;
    ui->listView_spoje->setModel(modelSpoje);
    ui->listView_spoje->setModelColumn(modelSpoje->record().indexOf("s.c"));
    ui->polelinky->setText(QString::number(stavSystemu.aktlinka.c ));
}


void MainWindow::on_listView_spoje_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    Spoj docasnySpoj;

    if (ui->listView_spoje->model()->rowCount()>0)
    {
        if(index.isValid())
        {
            index.siblingAtColumn(1);
            docasnySpoj.cislo=index.siblingAtColumn(modelSpoje->record().indexOf("s.s")).data().toInt();
            docasnySpoj.cisloRopid=index.siblingAtColumn(modelSpoje->record().indexOf("s.c")).data().toInt();
            docasnySpoj.linka.lc=index.siblingAtColumn(modelSpoje->record().indexOf("l.lc")).data().toInt();
            docasnySpoj.linka.c=index.siblingAtColumn(modelSpoje->record().indexOf("l.c")).data().toInt();
            QString alias=index.siblingAtColumn(modelSpoje->record().indexOf("l.aois")).data().toString();
            if(alias=="")
            {
                docasnySpoj.linka.LineName=QString::number(docasnySpoj.linka.c );
            }
            else
            {
                docasnySpoj.linka.LineName=alias;
            }

            //docasnySpoj.linka.c=index.siblingAtColumn(modelSpoje->record().indexOf("l.c")).data().toInt();



            ui->polespoje->setText(QString::number(docasnySpoj.cisloRopid));

            stavSystemu.aktspoj=docasnySpoj;
            int kmenovaLinka=0;
            int poradi=0;
            int order=0;


            sqlPraceRopid.najdiTurnusZeSpoje(stavSystemu.aktspoj, kmenovaLinka,poradi, order,this->vyrobMaskuKalendareJizd());
            qDebug()<<"test spoje do turnusu "<<kmenovaLinka<<"/"<<poradi<<" "<<order;
        }
    }

    qDebug()<<"IDspoje:"<<docasnySpoj.cislo;
}

void MainWindow::on_listView_kmenovaLinka_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;

    stavSystemu.aktObeh.kmenovaLinka.c= index.data(Qt::DisplayRole).toString().toInt();

    ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktObeh.kmenovaLinka.c));

    QSqlQueryModel* modelPoradi=sqlPraceRopid.stahniSeznamPoradiModel(stavSystemu.aktObeh.kmenovaLinka, this->vyrobMaskuKalendareJizd());

    ui->listView_poradi->setModel(modelPoradi);
    ui->listView_poradi->setModelColumn(modelPoradi->record().indexOf("o.p"));

    ui->tableView_turnusSpoj->setModel(&prazdnyModel);
}

void MainWindow::on_listView_poradi_clicked(const QModelIndex &index)
{
    qDebug()<<Q_FUNC_INFO;
    stavSystemu.aktlinka.c=index.data(Qt::DisplayRole).toString().toInt();

    if (ui->listView_poradi->model()->rowCount()!=0)
    {
        if(index.row()>=0)
        {
            stavSystemu.aktObeh.p=index.data(Qt::DisplayRole).toString().toInt();

            /// zakomentovat?
            if (sqlPraceRopid.vytvorSeznamTurnusSpoju(stavSystemu.aktObeh,this->vyrobMaskuKalendareJizd())==1)
            {
                qDebug()<<"pocetSpoju: "<<stavSystemu.aktObeh.seznamSpoju.count();
            }
            else
            {
                qDebug()<<"spoje nenalezeny";
            }

            QSqlQueryModel* modelTurnusSpoj=sqlPraceRopid.stahniSeznamTurnusSpojuModel(stavSystemu.aktObeh, this->vyrobMaskuKalendareJizd());
            ui->tableView_turnusSpoj->setModel(modelTurnusSpoj);
            ui->tableView_turnusSpoj->resizeColumnsToContents();
        }
    }
}

void MainWindow::on_tableView_turnusSpoj_clicked(const QModelIndex &index)
{
    qDebug() <<  Q_FUNC_INFO;
    if (index.model()->rowCount()!=0)
    {
        qDebug()<<"current item bum";

        stavSystemu.aktspoj.linka.c=index.siblingAtColumn(0).data().toInt();
        stavSystemu.aktspoj.cisloRopid=index.siblingAtColumn(1).data().toInt();

        stavSystemu.indexSpojeNaObehu=stavSystemu.aktObeh.seznamSpoju.indexOf(stavSystemu.aktspoj);
        qDebug()<<"index spoje na obehu: "<<QString::number(stavSystemu.indexSpojeNaObehu)<<" delkaSeznamu: "<<stavSystemu.aktObeh.seznamSpoju.count();
        qDebug()<<"hodnota polozky"<<QString::number(stavSystemu.aktspoj.linka.c)<<" spoj:"<<QString::number(stavSystemu.aktspoj.cisloRopid);

        //NUTNE DOPLNIT

        ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
        ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));
    }
}


void MainWindow::on_pushButton_refreshDetekce_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    deviceManagementServiceSubscriber.slotAktualizaceZarizeni();
}


void MainWindow::on_pushButton_ulozDetekce_clicked()
{

    qDebug() <<  Q_FUNC_INFO;

    int i=0;
    settings.beginWriteArray("hwConfig");
    foreach(DevMgmtPublisherStruct zarizeni, deviceManagementServiceSubscriber.seznamZarizeniDetekce)
    {
        // QJsonDocument json = QJsonDocument::fromVariant(zarizeni.toQMap() );
        settings.setArrayIndex(i);
        settings.setValue("deviceClass",zarizeni.deviceClass);
        settings.setValue("deviceId",zarizeni.deviceId);
        i++;
    }
    settings.endArray();

}



void MainWindow::on_pushButton_nactiDetekce_clicked()
{
    qDebug() <<  Q_FUNC_INFO;

    deviceManagementServiceSubscriber.seznamZarizeniKonfigurace.clear();


    int size = settings.beginReadArray("hwConfig");
    for (int j = 0; j < size; ++j) {
        settings.setArrayIndex(j);
        DevMgmtPublisherStruct zarizeni;
        zarizeni.deviceId= settings.value("deviceId").toString();
        zarizeni.deviceClass= settings.value("deviceClass").toString();
        zarizeni.hwConfig=true;
        deviceManagementServiceSubscriber.seznamZarizeniKonfigurace.append(zarizeni);
        qDebug()<<"trida: "<<zarizeni.deviceClass<<" id: "<<zarizeni.deviceId;
    }
    settings.endArray();

    qDebug()<<"nacteno "<<QString::number(deviceManagementServiceSubscriber.seznamZarizeniKonfigurace.count())<<" zarizeni";
    vykresliSluzbyDoTabulky(deviceManagementServiceSubscriber.seznamZarizeniDetekce, deviceManagementServiceSubscriber.seznamZarizeniKonfigurace);
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


void MainWindow::on_pushButton_jizda_mapa_clicked()
{
    mapaVykresleni.seznamMnozin.clear();
    mapaVykresleni.pridejMnozinu(MapaVykresleni::seznamZastavkaCilToSeznamMapaBod(stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,true),true,false,false,false,MnozinaBodu::WGS84);
    mapaVykresleni.pridejMnozinu(MapaVykresleni::seznamZastavkaCilToSeznamMapaBod(stavSystemu.aktualniSpojNaObehu().globalniSeznamZastavek,true),false,false,false,true,MnozinaBodu::WGS84);
    mapaVykresleni.pridejMnozinu(sqlPraceRopid.vytvorTrajektorii(stavSystemu.aktualniSpojNaObehu().cislo,this->vyrobMaskuKalendareJizd()),false, true, false,false, MnozinaBodu::J_STSK);

    mapaVykresleni.seznamMnozinDoJson(mapaVykresleni.seznamMnozin, mapaVykresleni.spojDoTabulky( stavSystemu.aktspoj));

}

QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}
