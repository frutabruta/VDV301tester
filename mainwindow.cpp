#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VDV301struktury/cestaudaje.h"
#include "xmlgenerator.h"

#include <QNetworkReply>
#include "VDV301struktury/zastavka.h"
#include "VDV301testy/vdv301testy.h"



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
    qDebug()<<"MainWindow::MainWindow";
    ui->setupUi(this);
    ui->prepinadloStran->setCurrentIndex(1);
    ui->prepinadloStran->setWindowState(Qt::WindowFullScreen);

    //manualni pridani subscriberu pro pripad nefunkcnosti DNS-SD
    //seznamSubscriberu.push_back(QUrl("http://192.168.12.128:60011"));
    //seznamSubscriberu.push_back(QUrl("http://127.0.0.1:48479"));

    //inicializace databaze
    startDatabaze();

    //propojeni vsech slotu
    vsechnyConnecty();

    nastartujVsechnySluzby();

    //vyplneni polozky build pro rozliseni zkompilovanych verzi
    QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);
    ui->label_build->setText(compilationTime);

    //cesty souboru
    hlasic.zmenUmisteniProgramu(umisteniProgramu);
    konfigurace.vytvorDefaultniKonfiguraci();
    konfigurace.otevriSoubor();


    logfile.defaultniLog(log);
    logfile.novySoubor(log);

    logfile.pridejNaKonecSouboru(log,QDateTime::currentDateTime().toString()+" program spuštěn");

    ui->statusBar->showMessage("test");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vsechnyConnecty()
{
    //vypisy subscriberu
    connect(&customerInformationService1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalVypisSubscriberu,this,&MainWindow::vypisSubscribery2);
    this->vypisSubscribery(customerInformationService1_0.seznamSubscriberu);
    this->vypisSubscribery2(customerInformationService2_2CZ1_0.seznamSubscriberu);
    connect(&xmlMpvParser,SIGNAL(stazeniHotovo()),this,SLOT(MpvNetReady()));

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



    // connect(&testOdberuServer,&TestOdberuServer::nastartujSluzbu,&customerInformationService2_2CZ1_0,&CustomerInformationService::start);


    //vypisovani stavovych hlasek do stavoveho radku vespod okna
    connect(&mojesql,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);
    connect(&mojesql,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);
    connect(&xmlRopidParser,&XmlRopidParser::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);


    //prepinani stavu radio prepinacu podle stavu sluzeb
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio1);
    connect(&deviceManagementService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio2);
    connect(&ticketValidationService2_3CZ1_0,&HttpSluzba::signalStav,this,&MainWindow::radio3);
    connect(&customerInformationService1_0,&HttpSluzba::signalStav,this,&MainWindow::radio4);

    //konfigurace
    connect(&konfigurace,&Konfigurace::odesliChybovouHlasku,this,&MainWindow::vypisDiagnostika);
}

void MainWindow::testNaplnOkno(int index)
{
    qDebug()<<"MainWindow::testNaplnOkno";
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
void MainWindow::testStart(int index)
{
    qDebug()<<"MainWindow::testStart";
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
void MainWindow::testStop(int index)
{
    qDebug()<<"MainWindow::testStop";
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

void MainWindow::nastartujVsechnySluzby()
{
    deviceManagementService1_0.slotStart(true);
    customerInformationService1_0.slotStart(true);
    customerInformationService2_2CZ1_0.slotStart(true);
    ticketValidationService2_3CZ1_0.slotStart(true);
}
void MainWindow::xmlHromadnyUpdate()
{
    qDebug()<<"MainWindow::xmlHromadnyUpdate()";
    qDebug()<<"delka seznamu tripu "<<stavSystemu.aktObeh.seznamSpoju.length();
    if (stavSystemu.aktObeh.seznamSpoju.isEmpty())
    {
        qDebug()<<"seznam tripu je prazdny";
        return;
    }
    QDomDocument vstupniDomXmlPrestupy;
    if (stavSystemu.prestupy==true)
    {
        Zastavka aktZastavka=stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka;
        xmlMpvParser.StahniMpvXml(aktZastavka.cisloCis, aktZastavka.ids);
    }
    qDebug()<<QString::number(stavSystemu.indexAktZastavky);
    QVector<prestupMPV> prestupy;
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
    ticketValidationService2_3CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
}





void MainWindow::MpvNetReady()
{
    qDebug()<<"MainWindow::MpvNetReady";
    xmlMpvParser.naplnVstupDokument(xmlMpvParser.stazenaData);
    QVector<prestupMPV> prestupy=xmlMpvParser.parsujDomDokument();
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu );
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,stavSystemu);
}






int MainWindow::on_prikaztlacitko_clicked()
{
    qDebug()<<"MainWindow::on_prikaztlacitko_clicked";
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktspoj.linka.c =ui->polelinky->text().toInt();
    stavSystemu.aktspoj.cisloRopid=ui->polespoje->text().toInt();

    stavSystemu.indexAktZastavky=0;

    QString textDoPole="";

    int vysledek=mojesql.StahniSeznam( stavSystemu.aktspoj.linka,stavSystemu.aktspoj.cisloRopid,stavSystemu.aktObeh.seznamSpoju,platnostSpoje);
    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }

    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }
    xmlHromadnyUpdate();
    if(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        AktualizaceDispleje();
        stavSystemu.locationState="AtStop";
        ui->tlacitkoZpetVydej->setChecked(1);
        ui->prepinadloStran->setCurrentIndex(0);
    }
    return 1;
}


int MainWindow::on_prikazTlacitkoTurnus_clicked()
{
    qDebug()<<"MainWindow::on_prikazTurnuslacitko_clicked";
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text().toInt();

    stavSystemu.indexAktZastavky=0;
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
        //if(ui->listTurnusSpoje)

        stavSystemu.indexTripu=ui->listTurnusSpoje->currentRow();
        qDebug()<<"zjisteni zvolene pozice v seznamu"<<stavSystemu.indexTripu;
        if (stavSystemu.indexTripu<0)
        {
            this->vypisDiagnostika("není zvolený spoj");
            return 0;
        }
    }

    vysledek=mojesql.StahniSeznamCelySpoj(stavSystemu.aktObeh.seznamSpoju,stavSystemu.indexTripu,platnostSpoje);
    qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    if (stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).navazujici==true)
    {
        vysledek=mojesql.StahniSeznamCelySpoj(stavSystemu.aktObeh.seznamSpoju,stavSystemu.indexTripu+1,platnostSpoje);
        qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;

    }

    qDebug()<<"je nacteno "<<stavSystemu.aktObeh.seznamSpoju.length()<<" spoju";



    //  int vysledek=mojesql.StahniSeznamCelySpoj(stavSystemu.aktspoj,this->stavSystemu.aktObeh.seznamSpoju,platnostSpoje);
    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }

    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }
    xmlHromadnyUpdate();
    if(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        AktualizaceDispleje();
        stavSystemu.locationState="AtStop";
        ui->tlacitkoZpetVydej->setChecked(1);
        ui->prepinadloStran->setCurrentIndex(0);
    }
    return 1;
}

void MainWindow::on_sipkaNahoru_clicked()
{
    qDebug()<<"\n MainWindow::on_sipkaNahoru_clicked() \n";
    if (stavSystemu.indexAktZastavky<(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.count()-1))
    {
        if(stavSystemu.locationState=="AtStop")
        {
            stavSystemu.locationState="AfterStop";
            ui->AfterStop->setChecked(true);
            stavSystemu.indexAktZastavky++;
            priOdjezdu();
        }
        else
        {
            if(stavSystemu.locationState=="BeforeStop")
            {
                stavSystemu.locationState="AtStop";
                ui->AtStop_2->setChecked(true);
                priPrijezdu();
            }

            if(stavSystemu.locationState=="BetweenStop")
            {
                stavSystemu.locationState="BeforeStop";
                ui->BeforeStop->setChecked(true);
            }

            if(stavSystemu.locationState=="AfterStop")
            {stavSystemu.locationState="BetweenStop";
                ui->BetweenStop->setChecked(true);
            }
        }
    }
    AktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    xmlHromadnyUpdate();
}

void MainWindow::on_sipkaDolu_clicked()
{
    qDebug()<<"\n on_sipkaDolu_clicked \n";
    if (stavSystemu.indexAktZastavky>=1)
    {
        if(stavSystemu.locationState=="AfterStop")
        {
            stavSystemu.locationState="AtStop";
            stavSystemu.indexAktZastavky--;
            priPrijezdu();
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
        //QString textDoPole="";
        AktualizaceDispleje();
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    xmlHromadnyUpdate();
}


void MainWindow::on_pripojeniTlacitko_clicked()
{
    qDebug()<<"\n on_pripojeniTlacitko_clicked \n";
    startDatabaze();
}

void MainWindow::startDatabaze()
{
    qDebug()<<"MainWindow::startDatabaze()";
    mojesql.Pripoj();
    if (mojesql.VytvorSeznamLinek(seznamLinek)==1)
    {
        NaplnVyberLinky(seznamLinek);
        QVector<Linka> kmenoveLinky;
        mojesql.VytvorSeznamKmenovychLinek(kmenoveLinky);
        NaplnKmenoveLinky(kmenoveLinky);
        ui->NazevVysledku->setText("OK2");
    }
    else
    {
        ui->NazevVysledku->setText("FAIL2");
        qDebug()<<"chyba nacitani linek";
    }
}

void MainWindow::NaplnVyberLinky(QVector<Linka> docasnySeznamLinek)
{
    ui->listLinek->clear();
    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        //newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).lc));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listLinek->addItem( newItem);
    }

}

void MainWindow::NaplnKmenoveLinky(QVector<Linka> docasnySeznamLinek)
{
    ui->listKmenovychLinek->clear();
    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listKmenovychLinek->addItem( newItem);
    }

}

void MainWindow::NaplnVyberSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug()<<"MainWindow::NaplnVyberSpoje";
    ui->listSpoje->clear();
    /*
    if (ui->listSpoje->count()!=0)
    {
        ui->listSpoje->clear();
    }*/
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

void MainWindow::NaplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug()<<"MainWindow::NaplnVyberTurnusSpoje";
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

void MainWindow::NaplnVyberPoradi(QVector<Obeh> docasnySeznamObehu)
{
    qDebug()<<"MainWindow::NaplnVyberPoradi";
    if (ui->listPoradi->count()!=0)
    {
        ui->listPoradi->clear();
    }
    // qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
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


void MainWindow::AktualizaceDispleje()
{
    qDebug()<<"MainWindow::AktualizaceDispleje()";
    QString textDoPoleAkt="";
    QString casDoPoleAkt="";
    QString textDoPoleNasl="";
    QString textPoleCasuNasl="";
    mojesql.vytvorHlavniAktualni(textDoPoleAkt,casDoPoleAkt,stavSystemu.indexAktZastavky,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.locationState);
    mojesql.vytvorHlavniTextNasledujici(textDoPoleNasl,textPoleCasuNasl,stavSystemu.indexAktZastavky,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.locationState);


    ui->labelAktZastJmeno->setText(textDoPoleAkt);
    ui->labelAktZastCas->setText(casDoPoleAkt);
    ui->prikazovyvysledek->setText(textDoPoleNasl);
    ui->prikazovyvysledek_cas->setText(textPoleCasuNasl);
    ui->label_aktLinka->setText(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).linka.LineNumber);
    ui->label_aktSpoj->setText(QString::number(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).cisloRopid));

    ui->locationStateIndicator->setText(stavSystemu.locationState);

}

void MainWindow::on_pridatTlacitko_clicked()
{
    qDebug()<<"\n on_pridatTlacitko_clicked \n";
    if (stavSystemu.indexAktZastavky<(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.count()-1))
    {
        stavSystemu.indexAktZastavky++;
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_ubratTlacitko_clicked()
{
    qDebug()<<"\n on_ubratTlacitko_clicked \n";
    if (stavSystemu.indexAktZastavky>=2)
    {
        stavSystemu.indexAktZastavky--;
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_quitTlacitko_clicked()
{
    qDebug()<<"\n on_quitTlacitko_clicked \n";
    MainWindow::close();
    QApplication::exit(0);
    //QCoreApplication::exit(0);

}





void MainWindow::on_BeforeStop_clicked()
{

    stavSystemu.locationState="BeforeStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_AtStop_2_clicked()
{
    qDebug()<<"";
    priPrijezdu();

}

void MainWindow::on_AfterStop_clicked()
{
    qDebug()<<"";
    stavSystemu.locationState="AfterStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_BetweenStop_clicked()
{
    qDebug()<<"";
    stavSystemu.locationState="BetweenStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_prestupyCheckbox_stateChanged(int arg1)
{
    arg1=1;
    qDebug()<<"MainWindow::on_prestupyCheckbox_stateChanged";
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    arg1=1;
    qDebug()<<"MainWindow::on_checkBox_stateChanged";
    stavSystemu.prestupy= ui->checkBox->checkState();
}



void MainWindow::on_tlacitkoNactiXMLropid_clicked()
{
    qDebug()<<"";
    xmlRopidParser.otevriSoubor();
}



void MainWindow::on_tlacitkoNastaveni_clicked()
{
    qDebug()<<"";
    ui->prepinadloStran->setCurrentIndex(2);
}


void MainWindow::on_tlacitkoTruncate_clicked()
{
    qDebug()<<"";
    xmlRopidParser.truncateAll();
}

void MainWindow::on_tlacitkoOdesliPrikaz_clicked()
{
    qDebug()<<"";
    // ibisOvladani.dopocetCelni("l006");
}

void MainWindow::on_tlacitkoNastavPort_clicked()
{
    qDebug()<<"on_tlacitkoNastavPort_clicked()";


    ibisOvladani.globalniSeriovyPort=ui->lineEdit_jmenoPortu->text();
    ibisOvladani.dopocetCelni("l006");
    ibisOvladani.dopocetCelni("aA1 ahoj");
    ibisOvladani.dopocetCelni("v povel v\\");
    ibisOvladani.dopocetCelni("zA povel zA");
    ibisOvladani.dopocetCelni("zN povel zN");
    ibisOvladani.dopocetCelni("xC2");
}

void MainWindow::on_tlacitkoIBIS_clicked()
{
    qDebug()<<"on_tlacitkoIBIS_clicked()";
    ibisOvladani.dopocetCelni("xC2");
    ibisOvladani.odesliFrontKomplet(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliSideKomplet(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odeslikompletBUSEjednoradekAA(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliRearKomplet(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
}


int MainWindow::priPrijezdu()
{
    qDebug()<<"MainWindow::priPrijezdu";

    stavSystemu.doorState="DoorsOpen";


    if (stavSystemu.indexAktZastavky<(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek.length()-1))
    {
        hlasic.kompletZastavka(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloCis,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloOis);
    }
    else
    {
        hlasic.kompletKonecna(this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->stavSystemu.aktObeh.seznamSpoju.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis );
    }
    stavSystemu.locationState="AtStop";
    xmlHromadnyUpdate();

    return 1;
}

int MainWindow::priOdjezdu()
{
    qDebug()<<"MainWindow::priOdjezdu()";
    //this->bonjourStartKomplet();

    //bonjourStartPublish();

    return 1;
}




void MainWindow::on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->polelinky->setText(ui->listLinek->currentItem()->data(Qt::UserRole ).toString() );
    stavSystemu.aktlinka.c=ui->listLinek->currentItem()->data(Qt::UserRole).toString().toInt();
    qDebug()<<"tady budu vypisovat vybrane spoje";
    qDebug()<<"raw "<<ui->listLinek->currentItem()->data(Qt::UserRole)<<" int "<<ui->listLinek->currentItem()->data(Qt::UserRole).toInt();
    ui->listSpoje->clear();
    if (mojesql.VytvorSeznamSpoju(seznamSpoju,stavSystemu.aktlinka)==1)
    {
        NaplnVyberSpoje(seznamSpoju);
    }
}

void MainWindow::on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"on_listKmenovychLinek_currentItemChanged";
    ui->poleLinkyTurnus->setText(ui->listKmenovychLinek->currentItem()->data(Qt::UserRole ).toString() );

    stavSystemu.aktObeh.kmenovaLinka.c=ui->listKmenovychLinek->currentItem()->data(Qt::UserRole).toInt();

    ui->listPoradi->clear();

    ui->listTurnusSpoje->clear();

    if (mojesql.VytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka )==1)
    {

        NaplnVyberPoradi(seznamObehu);


    }
}


void MainWindow::on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listPoradi_currentItemChanged";
    if (ui->listPoradi->count()!=0)
    {
        if(ui->listPoradi->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);

            qDebug()<<"xx"+ QString::number( ui->listPoradi->currentRow());
            qDebug()<<"current item:"+ui->listPoradi->currentItem()->data(Qt::UserRole).toString();

            //ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
            stavSystemu.aktObeh.p=ui->listPoradi->currentItem()->data(Qt::UserRole).toInt() ;

            if (mojesql.VytvorSeznamTurnusSpoju(stavSystemu.aktObeh)==1)
            {
                NaplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);

            }


        }

    }
}


void MainWindow::on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listSpoje_currentItemChanged";
    if (ui->listSpoje->count()!=0)
    {
        if(ui->listSpoje->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);
            qDebug()<<"xx"+ QString::number( ui->listSpoje->currentRow());
            qDebug()<<"current item:"+ui->listSpoje->currentItem()->data(Qt::UserRole).toString();
            ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
            //stavSystemu.aktspoj=ui->listSpoje->currentItem()->data(Qt::UserRole).toInt() ;
            int indexVyberu=ui->listSpoje->currentRow();
            stavSystemu.aktspoj=seznamSpoju.at(indexVyberu);
        }

    }
}

void MainWindow::on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listTurnusSpoje_currentItemChanged";
    if (ui->listTurnusSpoje->count()!=0)
    {
        if(ui->listTurnusSpoje->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);
            qDebug()<<"xx"+ QString::number( ui->listTurnusSpoje->currentRow());
            qDebug()<<"current item:"+ui->listTurnusSpoje->currentItem()->data(Qt::UserRole).toString();
            int zvolenaPolozka=ui->listTurnusSpoje->currentRow();
            qDebug()<<"current row "<<zvolenaPolozka;
            qDebug()<<"delka seznamu spoju"<<stavSystemu.aktObeh.seznamSpoju.size()<<" zvolena polozka "<<zvolenaPolozka;
            stavSystemu.aktspoj=stavSystemu.aktObeh.seznamSpoju.at(zvolenaPolozka);
            ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
            //ui->poleSpojeTurnus->setText(ui->listTurnusSpoje->currentItem()->data(Qt::UserRole).toString());
            ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));



        }

    }
}




void MainWindow::on_tlacitkoZpetVydej_clicked()
{
    ui->prepinadloStran->setCurrentIndex(0);
}

void MainWindow::on_tlacitkoLinkospoj_clicked()
{
    ui->prepinadloStran->setCurrentIndex(1);
}



void MainWindow::inicializacePoli()
{
    stavSystemu.aktObeh.seznamSpoju.clear();
    seznamLinek.clear();
    seznamSpoju.clear();
    stavSystemu.vymaz();
}

void MainWindow::on_tlacitkoSmazOkno_clicked()
{
    ui->plainTextEditCustomXml->clear();
}

void MainWindow::on_tlacitkoManual_clicked()
{
    ui->prepinadloStran->setCurrentIndex(3);
}

void MainWindow::on_tlacitkoOdesliXml_clicked()
{
    qDebug()<<"on_tlacitkoOdesliXml_clicked()";
    QByteArray vysledek2="";

    //vysledek2.append(ui->plainTextEditCustomXml->toPlainText());
    vysledek2=vysledek2+ui->plainTextEditCustomXml->toPlainText().toUtf8();
    //CustomerInformationService.ObnoveniServeru(vysledek2);
    customerInformationService1_0.nastavObsahTela("AllData",vysledek2);
    customerInformationService2_2CZ1_0.nastavObsahTela("AllData",vysledek2);
    for(int i=0;i<customerInformationService1_0.seznamSubscriberu.count();i++ )
    {
        customerInformationService1_0.PostDoDispleje(customerInformationService1_0.seznamSubscriberu[i].adresa,vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";
}


void MainWindow::vypisSubscribery(QVector<Subscriber> adresy)
{
    qDebug()<<"MainWindow::vypisSubscribery";
    ui->seznamOdberatelu->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qDebug()<<"vracim 0";
        //return 0;
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
        //return 1;
    }


}

void MainWindow::vypisSubscribery2(QVector<Subscriber> adresy)
{
    qDebug()<<"MainWindow::vypisSubscribery2";
    //ui->seznamOdberatelu->clear();
    ui->seznamOdberatelu2->setRowCount(0);
    //ui->odberatele_tableView->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qDebug()<<"vracim 0";
        //return 0;
    }
    else
    {
        for (int i = 0;  i < adresy.count(); i++)
        {
            //ui->seznamOdberatelu->addItem(adresy.at(i).adresa.toString()+"_"+adresy.at(i).struktura );
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
            /*
            ui->tabulkaSubscriberu->setItem(row, 2, cell);
            ui->tabulkaSubscriberu->resizeColumnsToContents();

            cell = new QTableWidgetItem(QString::number(port));
            ui->tabulkaSubscriberu->setItem(row, 3, cell);
            ui->tabulkaSubscriberu->resizeColumnsToContents();
            */

        }
        qDebug()<<"vracim 1";
        //return 1;
    }


}





void MainWindow::on_tlacitkoAddsubscriber_clicked()
{
    vypisDiagnostika(customerInformationService1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));






}


void MainWindow::on_tlacitkoAddsubscriber_2_clicked()
{
    vypisDiagnostika( customerInformationService2_2CZ1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}




void MainWindow::on_tlacitkoRemoveSubscriber_clicked()
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
        vypisSubscribery(customerInformationService1_0.seznamSubscriberu);
        vypisDiagnostika("odstraneno");
    }
    else
    {

        vypisDiagnostika("nepovedlo se odstranit");
    }






}



void MainWindow::on_tlacitkoRemoveSubscriber_2_clicked()
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

        vypisSubscribery2(customerInformationService2_2CZ1_0.seznamSubscriberu);
        vypisDiagnostika("odstraneno");

    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


void MainWindow::on_tlacitkoHlaseniSlozka_clicked()
{
    qDebug()<<"nastavena cesta k hlaseni na "<<ui->lineEditHlaseniCesta->text();
    hlasic.cesta=ui->lineEditHlaseniCesta->text();
}


void MainWindow::vypisDiagnostika(QString vstup)
{
    qDebug()<<"subscribe diag "<<vstup;
    ui->label_diagnostika_manual->clear();
    ui->label_diagnostika_manual->setText(vstup);
    ui->statusBar->showMessage(vstup);
    logfile.pridejNaKonecSouboru(log,QDateTime::currentDateTime().toString()+" "+ vstup);

}


void MainWindow::vypisSqlVysledek(QString vstup)
{
    ui->label_diagnostika_sql->setText(vstup);
}

void MainWindow::on_tlacitkoTurnus_clicked()
{
    ui->prepinadloStran->setCurrentIndex(4);
}





void MainWindow::on_quitTlacitko_2_clicked()
{
    qDebug()<<"\n on_quitTlacitko_2_clicked \n";
    this->on_quitTlacitko_clicked();
}


void MainWindow::zastavSluzby()
{
    //customerInformationService1_0.
}

void MainWindow::on_tlacitkoPalubniPc_clicked()
{
    ui->stackedWidget_hlavni->setCurrentIndex(0);
}


void MainWindow::on_tlacitkoTestRozhrani_clicked()
{
    ui->stackedWidget_hlavni->setCurrentIndex(1);
}






void MainWindow::on_tlacitkoFullscreen_clicked()
{

    qDebug()<< "on_tlacitkoFullscreen_clicked";
    this->toggleFullscreen();


}
void MainWindow::on_tlacitkoFullscreen2_clicked()
{
    qDebug()<< "on_tlacitkoFullscreen2_clicked";
    this->toggleFullscreen();
}

//CIS 2.2CZ1.0
void MainWindow::radio1(bool stav)
{
    ui->radioButton_ON1->setChecked(stav);
    ui->radioButton_OFF1->setChecked(!stav);
}

//DEVMGMT 1:0
void MainWindow::radio2(bool stav)
{
    ui->radioButton_ON2->setChecked(stav);
    ui->radioButton_OFF2->setChecked(!stav);
}


//TicketValidationService 2.2CZ1.0
void MainWindow::radio3(bool stav)
{
    ui->radioButton_ON3->setChecked(stav);
    ui->radioButton_OFF3->setChecked(!stav);
}

//CIS 1.0
void MainWindow::radio4(bool stav)
{
    ui->radioButton_ON4->setChecked(stav);
    ui->radioButton_OFF4->setChecked(!stav);
}



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

void MainWindow::testyVykresliCasti(QVector<PolozkaTestu> &seznamPolozek)
{

    qDebug()<<"MainWindow::testyVykresliCasti";
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



void MainWindow::on_tlacitkoPrubehTestu_clicked()
{
    ui->stackedWidget_testy->setCurrentIndex(0);
}


void MainWindow::on_tlacitko_StartTest_clicked()
{
    testStart(testIndex);
    //vzorovyTest.start();
}


void MainWindow::on_TlacitkoStopTest_clicked()
{
    vzorovyTest.stop();
}




//tlacitka pro spusteni testu
void MainWindow::on_pushButton_test1_clicked()
{
    testIndex=0;
    testNaplnOkno(testIndex);
}

void MainWindow::on_pushButton_test2_clicked()
{
    testIndex=1;
    testNaplnOkno(testIndex);
}

void MainWindow::on_pushButton_test3_clicked()
{
    testIndex=2;
    testNaplnOkno(testIndex);
}

void MainWindow::on_pushButton_test4_clicked()
{
    testIndex=3;
    testNaplnOkno(testIndex);
}


void MainWindow::on_tlacitkoSluzby_clicked()
{
    ui->stackedWidget_testy->setCurrentIndex(1);
}

