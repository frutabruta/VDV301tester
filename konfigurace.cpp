#include "konfigurace.h"
#include <QtDebug>
#include <QtXml>

Konfigurace::Konfigurace(QString cestaProgramu)
{
    cesta=cestaProgramu;



}





void Konfigurace::otevriSoubor()
{
    qDebug() <<  Q_FUNC_INFO;
    QDomDocument doc;//("mydocument");
    // QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");


    QString kompletCesta=cesta+"/konfigurace/konfigurace.xml";
    QFile file(kompletCesta);

    qDebug()<<" oteviram soubor "<<kompletCesta;





    if (!file.open(QIODevice::ReadOnly))
    {
        emit odesliChybovouHlasku("soubor konfigurace se nepovedlo otevrit");
        qDebug()<<"fail1";
         file.close();
        return;
    }
    qDebug()<<"velikost souboru konfigurace je "<<file.size();

    // https://stackoverflow.com/questions/42117178/qdomdocument-setcontent-return-false
    QString errorStr;
    int errorLine;
    int errorColumn;
    if(!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {

        emit odesliChybovouHlasku("soubor konfigurace je vadný:"+errorStr+" at line "+QString::number(errorLine)+" column "+QString::number(errorColumn ));

        file.close();
        return;

    }




    qDebug()<<"uspech";
    QDomElement koren=doc.firstChildElement();

    cestaHlaseni=natahniCestaHlaseni(doc);
    natahniSpecialniHlaseni(doc);
    file.close();




}

void Konfigurace::vytvorDefaultniKonfiguraci()
{
    qDebug() <<  Q_FUNC_INFO;


      QString filename=cesta+"/konfigurace/konfigurace.xml";
     if(souborExistuje(filename))
     {
         qDebug()<<"soubor uz existuje";
         return;
     }

    QDomDocument xmlko;
    QDomElement parent=xmlko.createElement("konfigurace");
    xmlko.appendChild(parent);

    QDomElement hlaseni=xmlko.createElement("hlaseni");
    QDomElement hlaseniCesta=xmlko.createElement("cesta");
    hlaseniCesta.appendChild(xmlko.createTextNode(hlaseniDefaultniCesta));
    hlaseni.appendChild(hlaseniCesta);


    parent.appendChild(hlaseni);



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
    qDebug() <<  Q_FUNC_INFO;

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


QString Konfigurace::natahniCestaHlaseni(QDomDocument xmlko)
{
    qDebug() <<  Q_FUNC_INFO;
    QString vysledek=xmlko.firstChildElement("konfigurace").firstChildElement("hlaseni").firstChildElement("cesta").firstChild().nodeValue() ;

    qDebug()<<vysledek;

    return vysledek;
}

int Konfigurace::natahniSpecialniHlaseni(QDomDocument xmlko)
{
    QDomNodeList seznamHlaseni=xmlko.firstChildElement("konfigurace").firstChildElement("hlaseni").firstChildElement("special").elementsByTagName("polozka");
    specialniHlaseni.clear();
    if(seznamHlaseni.isEmpty())
    {
        return 0;
    }

    for(int i=0; i<seznamHlaseni.count(); i++)
    {
        QDomElement element=seznamHlaseni.at(i).toElement();
        SpecialniHlaseni polozka;
        polozka.type=element.firstChildElement("type").text();
        polozka.text=element.firstChildElement("text").text();
        polozka.title=element.firstChildElement("headline").text();
        polozka.displayName=element.firstChildElement("displayName").text();

        QDomNodeList segmentyMp3=element.elementsByTagName("mp3");
        for(int j=0;j<segmentyMp3.count();j++)
        {
            QString mp3soubor=segmentyMp3.at(j).firstChild().nodeValue();
            qDebug()<<"nactena MP3: "<<mp3soubor;
            polozka.mp3.push_back(mp3soubor);
        }

        specialniHlaseni.push_back(polozka);

        qDebug()<<"nacteno specialni hlaseni "<<polozka.type<<" "<<polozka.title<<" "<<polozka.displayName<<" "<<polozka.text<<" pocetMP3:"<<polozka.mp3.count();



    }


    QString vysledek=xmlko.firstChildElement("konfigurace").firstChildElement("hlaseni").firstChildElement("cesta").firstChild().nodeValue() ;


    return 1;


}


