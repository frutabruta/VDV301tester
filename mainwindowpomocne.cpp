#include "mainwindowpomocne.h"
#include "sqlropidxmlqueries.h"
#include <QtDebug>
#include <QtWidgets>

MainWindowPomocne::MainWindowPomocne()
{

}



int MainWindowPomocne::jeVRozsahu(int index, int pocetHodnot, QString funkce)
{
    qDebug()<<Q_FUNC_INFO;
    if((index<pocetHodnot)&&(index>=0))
    {
        return 1;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("hodnota "+QString::number(index)+" je mimo rozsah "+ QString::number(pocetHodnot)+" "+funkce);
        msgBox.exec();
        qDebug()<<"hodnota "+QString::number(index)+" je mimo rozsah "+ QString::number(pocetHodnot)+" "+funkce;

       return 0;
    }

}

void MainWindowPomocne::naplnTabulkuHlaseni(QTableWidget *vstup, QVector<AdditionalAnnoucement> seznamHlaseni )
{

    qDebug() <<  Q_FUNC_INFO;
    vstup->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<seznamHlaseni .size();
    if (seznamHlaseni.size()==0)
    {
        qDebug()<<"vracim 0";
    }
    else
    {
        foreach (AdditionalAnnoucement hlaseni, seznamHlaseni)
        {


            qint32 row;
            QTableWidgetItem *cell;
            row = vstup->rowCount();
            vstup->insertRow(row);
            cell = new QTableWidgetItem(hlaseni.displayName);
            vstup->setItem(row, 0, cell);


            cell = new QTableWidgetItem(hlaseni.type);
            vstup->setItem(row, 1, cell);

            cell = new QTableWidgetItem(hlaseni.title);
            vstup->setItem(row, 2, cell);


            if(hlaseni.mp3.count()>0)
            {
            cell = new QTableWidgetItem(hlaseni.mp3.first());
            vstup->setItem(row, 3, cell);
            }
            cell = new QTableWidgetItem(hlaseni.text);
            vstup->setItem(row, 4, cell);


            vstup->resizeColumnsToContents();
            vstup->resizeRowsToContents();
        }
        qDebug()<<"vracim 1";
    }



}


void MainWindowPomocne::dumpStopsToTable(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, Vdv301Enumerations::LocationStateEnumeration locationState, SqlRopidXmlQueries &sqlRopidQuerries, QTableWidget *table )
{

    qDebug() <<  Q_FUNC_INFO;
    table->setRowCount(0);



    for (int i=0;i<(docasnySeznamZastavek.count());i++)
    {
        QString cisloZastavky = QString::number(i+1);
        QString nazevZastavky2 = docasnySeznamZastavek.at(i).stopPoint.StopName;
        QString odjezdZeZastavky =  sqlRopidQuerries.vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).stopPoint.DepartureTime);
        QString prijezdDoZastavky =  sqlRopidQuerries.vytvorCasHodinyMinuty(docasnySeznamZastavek.at(i).stopPoint.ArrivalTime);
        QString pasma= sqlRopidQuerries.pasmaDoStringu(docasnySeznamZastavek.at(i).stopPoint.fareZoneList,",");
        QString znameni="";
        if (docasnySeznamZastavek.at(i).stopPoint.onRequest==true)
        {
            znameni="(x)";
        }


        qint32 row;
        QTableWidgetItem *cell;
        row = table->rowCount();
        table->insertRow(row);

        cell = new QTableWidgetItem(cisloZastavky);
        table->setItem(row, 0, cell);

        cell = new QTableWidgetItem(nazevZastavky2);
        table->setItem(row, 1, cell);

        QString timeText="";
        if(prijezdDoZastavky==odjezdZeZastavky)
        {
            timeText=odjezdZeZastavky;
        }
        else
        {
            if(prijezdDoZastavky.isEmpty()||odjezdZeZastavky.isEmpty())
            {
                timeText=prijezdDoZastavky+odjezdZeZastavky;
            }
            else
            {
                timeText=prijezdDoZastavky+" "+odjezdZeZastavky;
            }

        }

        cell = new QTableWidgetItem(timeText);
        table->setItem(row, 2, cell);


        cell = new QTableWidgetItem(znameni);
        table->setItem(row, 3, cell);

        cell = new QTableWidgetItem(pasma);
        table->setItem(row, 4, cell);

        //   ui->tableWidgetNasledujiciZastavky->resizeColumnsToContents();

    }

    int zabarvenySloupec=1;
    int pocetRadkuTabulky=table->rowCount();
    if (pocetRadkuTabulky<=0)
    {
        qDebug()<<"tabulku nelze obarvit, je prazdna";
        // return;
    }
    else
    {
        if (locationState==Vdv301Enumerations::LocationStateAtStop)
        {

            QBrush cyan(Qt::cyan);
            table->item(cisloporadi,zabarvenySloupec)->setBackground(cyan);
        }
        else
        {
            QBrush gray(Qt::gray);
            table->item(cisloporadi,zabarvenySloupec)->setBackground(gray);
        }
        table->resizeColumnsToContents();
        table->resizeRowsToContents();
        table->scrollToItem(table->item(cisloporadi,0));
    }
}

/*
void MainWindowPomocne::vypisSubscribery2_2CZ(QVector<Subscriber> adresy)
{
    qDebug()<<"MainWindow::vypisSubscribery2_2CZ";

    ui->seznamOdberatelu2->setRowCount(0);

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


        }
        qDebug()<<"vracim 1";
        //return 1;
    }


}
*/
