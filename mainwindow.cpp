#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blabla.h"
#include "sqlprace.h"
#include "httpserver/myhttpserver.h"
#include "xmlgenerator.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //HHserver(10);
    ui->setupUi(this);

    //MainWindow::setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    ui->prepinadloStran->setCurrentIndex(0);
}

int MainWindow::vytvor()
{

    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_prikaztlacitko_clicked()
{
    novatrida.aktlinka=ui->polelinky->text().toInt();
    novatrida.aktspoj=ui->polespoje->text().toInt();
    novatrida.cislo=1;
    mojesql.zjistiPocet(novatrida.pocetZastavek,novatrida.cislo, novatrida.aktlinka,novatrida.aktspoj);
    QString textDoPole="";

    mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj);

    ui->prikazovyvysledek->setText(textDoPole);
}



void MainWindow::on_sipkaNahoru_clicked()
{

   if (novatrida.cislo<novatrida.pocetZastavek)
   {
   novatrida.cislo++;
   QString textDoPole="";
   mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj);
   ui->prikazovyvysledek->setText(textDoPole);
   }
   ui->popisek->setText(QString::number(novatrida.cislo));

}

void MainWindow::on_sipkaDolu_clicked()
{
    if (novatrida.cislo>=1)
    {
    novatrida.cislo--;
    QString textDoPole="";
    mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj);
    ui->prikazovyvysledek->setText(textDoPole);
    }
    ui->popisek->setText(QString::number(novatrida.cislo));

}

void MainWindow::on_ubratTlacitko_clicked()
{

    QByteArray argumentXMLserveru = "";
    //argumentXMLserveru.append(ui->prikazovyvysledek->text());
    QByteArray vysledek =TestXmlGenerator.AllData() ;
    argumentXMLserveru.append(vysledek);
    HHserver.zapisDoPromenne(argumentXMLserveru);




    novatrida.cislo--;
    ui->popisek->setText(QString::number(novatrida.cislo));
}

void MainWindow::on_pripojeniTlacitko_clicked()
{
    mojesql.Pripoj();
    if (mojesql.vysledek==0)
    {
     ui->NazevVysledku->setText("nepovedlo se");
    }
    else
    {
        ui->NazevVysledku->setText("povedlo se");
    }
}

void MainWindow::on_pridatTlacitko_clicked()
{
    QByteArray argumentXMLserveru = "";
    //argumentXMLserveru.append(ui->prikazovyvysledek->text());
    QByteArray vysledek =TestXmlGenerator.devStatus() ;
    argumentXMLserveru.append(vysledek);
    HHserver.zapisDoPromenne(argumentXMLserveru);
    novatrida.cislo++;
    qInfo() << "clicked pridat";
    ui->popisek->setText(QString::number(novatrida.cislo));
}

void MainWindow::on_quitTlacitko_clicked()
{
    MainWindow::close();
}
