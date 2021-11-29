#include "logfile.h"
#include <QtDebug>
#include <QtXml>

Logfile::Logfile(QString cestaProgramu)
{
cesta=cestaProgramu;
}









void Logfile::otevriSoubor()
{
    qDebug()<<"Logfile::otevriSoubor";
    //QDomDocument doc("mydocument");
   // QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");

    QFile file(cesta+"/log/log.xml");





    if (!file.open(QIODevice::ReadOnly))
    {
        emit odesliChybovouHlasku("soubor logu se nepovedlo otevrit");
        qDebug()<<"fail1";
        return;
    }
    /*
    if (!doc.setContent(&file))
    {
         emit odesliChybovouHlasku("soubor konfigurace se nepovedlo otevrit2");
        qDebug()<<"fail2";
        file.close();
        return;
    }
    */
    file.close();

    qDebug()<<"uspech";




}

void Logfile::novySoubor(QFile &soubor)
{
    qDebug()<<"Logfile::novySoubor";





    //cestaLong=soubor.fileName().right();
    //QString slozka=
    QString cestaLong= QFileInfo(soubor.fileName()).dir().absolutePath();

    QDir dir;
    qDebug()<<"cestaLong "<<dir;

    if (!dir.exists(cestaLong))
    {
        qDebug()<<"slozka neexistuje";
        if(dir.mkpath(cestaLong))
        {
            qDebug()<<"slozku se povedlo vytvorit";
        }
        else
        {
            qDebug()<<"slozku se NEpovedlo vytvorit";
        }
    }
    else
    {
        qDebug()<<"slozka existuje";
    }

    QString cestaSouboru=soubor.fileName();
    //QFile soubor2(cestaSouboru);

    qDebug()<<"cestaSouboru "<<cestaSouboru;
    soubor.open(QIODevice::WriteOnly); // Or QIODevice::ReadWrite
/*



    QString filename=cesta+"/log/log.xml";
    qDebug()<<"cesta k logu "<<filename;
    QFile soubor( filename );
    if ( file.open(QIODevice::ReadWrite) ) // if (f.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream( &soubor );
        stream << "test";
                  //xmlko.toString();
                 // "something" << Qt::endl;
    }
    else
    {
        qDebug()<<"problem se souborem";
    }
    */

    soubor.close();


}

void Logfile::nastavCestuSouboru(QFile &soubor, QString cesta, QString nazevSouboru)
{
    qDebug()<<"Logfile::nastavCestuSouboru";
    soubor.close();
    QString celaCesta=cesta+"/"+nazevSouboru;
    qDebug()<<"cela cesta "<<celaCesta;
    soubor.setFileName(celaCesta);
}

void Logfile::defaultniLog(QFile &soubor)
{
    qDebug()<<"Logfile::defaultniLog";
    QString cestaLong(cesta+"/log");
    nastavCestuSouboru(soubor,cestaLong,"log.txt");
}


bool Logfile::souborExistuje(QString path)
{
    qDebug()<<"Konfigurace::souborExistuje";
    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qDebug()<<"soubor "<<path<<" existuje";
        return true;
    } else {
        qDebug()<<"soubor "<<path<<" neexistuje";
        return false;
    }
}

bool Logfile::pridejNaKonecSouboru( QFile &soubor,QString vstup)
{
    qDebug()<<"Logfile::pridejNaKonecSouboru";

    bool vysledek=true;
/*

    QString cestaSouboru=cestaLong + "log.txt";
    QFile soubor(cestaSouboru);

    qDebug()<<"cestaSouboru "<<cestaSouboru;
    soubor.open(QIODevice::WriteOnly);
    */




    if (soubor.open(QIODevice::WriteOnly | QIODevice::Append))
    {
      QTextStream stream(&soubor);
       stream<<vstup<<Qt::endl;
       soubor.close();
       vysledek=true;
    }
    else
    {
        qDebug()<<"do souboru nelze zapsat";
        vysledek=false;
    }









  return vysledek;



}




