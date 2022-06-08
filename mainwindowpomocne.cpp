#include "mainwindowpomocne.h"
#include <QtDebug>
#include <QtWidgets>

MainWindowPomocne::MainWindowPomocne()
{

}



int MainWindowPomocne::jeVRozsahu(int index, int pocetHodnot, QString funkce)
{
    if((index<pocetHodnot)&&(index>=0))
    {

        return 1;
    }

    else
    {
        QMessageBox msgBox;
        msgBox.setText("hodnota "+QString::number(index)+" je mimo rozsah "+ QString::number(pocetHodnot)+" "+funkce);
        msgBox.exec();
        qDebug()<<" hodnota mimo rozsah";

       return 0;
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
