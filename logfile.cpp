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

    QFile file(cesta+"/konfigurace/konfigurace.xml");





    if (!file.open(QIODevice::ReadOnly))
    {
        emit odesliChybovouHlasku("soubor konfigurace se nepovedlo otevrit");
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

void Logfile::novySoubor()
{
    qDebug()<<"Logfile::novySoubor";
   /* QDomDocument xmlko;
    QDomElement parent=xmlko.createElement("konfigurace");
    xmlko.appendChild(parent);

    QDomElement hlaseni=xmlko.createElement("hlaseni");
    QDomElement hlaseniCesta=xmlko.createElement("cesta");
    hlaseniCesta.appendChild(xmlko.createTextNode(hlaseniDefaultniCesta));
    hlaseni.appendChild(hlaseniCesta);


    parent.appendChild(hlaseni);

*/
    QString filename=cesta+"/log/log.xml";
    qDebug()<<"cesta ke konfiguraci "<<filename;
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "test";
                  //xmlko.toString();
                 // "something" << Qt::endl;
    }
    else
    {
        qDebug()<<"problem se souborem";
    }
    file.close();


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




