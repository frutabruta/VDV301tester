#include "konfigurace.h"
#include <QtDebug>
#include <QtXml>

Konfigurace::Konfigurace(QString cestaProgramu)
{
cesta=cestaProgramu;
}





void Konfigurace::otevriSoubor()
{
    qDebug()<<"Konfigurace::otevriSoubor";
    QDomDocument doc("mydocument");
   // QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");

    QFile file(cesta+"/konfigurace/konfigurace.xml");





    if (!file.open(QIODevice::ReadOnly))
    {
        emit odesliChybovouHlasku("soubor se nepovedlo otevrit");
        qDebug()<<"fail1";
        return;
    }
    if (!doc.setContent(&file))
    {
         emit odesliChybovouHlasku("soubor se nepovedlo otevrit2");
        qDebug()<<"fail2";
        file.close();
        return;
    }
    file.close();

    qDebug()<<"uspech";
    QDomElement koren=doc.firstChildElement();

    najdiCestaHlaseni(doc);




}

void Konfigurace::vytvorDefaultniKonfiguraci()
{
    qDebug()<<"Konfigurace::vytvorDefaultniKonfiguraci";
    QDomDocument xmlko;
    QDomElement parent=xmlko.createElement("konfigurace");
    xmlko.appendChild(parent);

    QDomElement hlaseni=xmlko.createElement("hlaseni");
    QDomElement hlaseniCesta=xmlko.createElement("cesta");
    hlaseniCesta.appendChild(xmlko.createTextNode(hlaseniDefaultniCesta));
    hlaseni.appendChild(hlaseniCesta);


    parent.appendChild(hlaseni);


    QString filename=cesta+"/konfigurace/konfigurace.xml";
    qDebug()<<"cesta ke konfiguraci "<<filename;
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << xmlko.toString();
                 // "something" << Qt::endl;
    }
    else
    {
        qDebug()<<"problem se souborem";
    }
    file.close();


}


bool Konfigurace::souborExistuje(QString path)
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


QString Konfigurace::najdiCestaHlaseni(QDomDocument xmlko)
{
    qDebug()<<" Konfigurace::najdiCestaHlaseni";
    QString vysledek=xmlko.firstChildElement("konfigurace").firstChildElement("hlaseni").firstChildElement("cesta").firstChild().nodeValue() ;

    qDebug()<<vysledek;

    return vysledek;
}


