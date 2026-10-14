#include "specialannouncementparser.h"
#include <QtDebug>
#include <QtXml>

SpecialAnnouncementParser::SpecialAnnouncementParser(QString appPath)
{
    cesta=appPath;
}





void SpecialAnnouncementParser::openFile()
{
    qDebug() <<  Q_FUNC_INFO;
    QDomDocument doc;//("mydocument");
    // QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");


    QString kompletCesta=cesta+"/announcementList.xml";
    QFile file(kompletCesta);

    qDebug()<<"opening file "<<kompletCesta;


    if (!file.open(QIODevice::ReadOnly))
    {
        emit signalError("announcementList file could not be loaded");
        qDebug()<<"fail1";
        file.close();
        return;
    }
    qDebug()<<"config file size is "<<file.size();

    // https://stackoverflow.com/questions/42117178/qdomdocument-setcontent-return-false
    QString errorStr;
    int errorLine;
    int errorColumn;
    if(!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {

        emit signalError("announcement list file is invalid:"+errorStr+" at line "+QString::number(errorLine)+" column "+QString::number(errorColumn ));

        file.close();
        return;
    }

    qDebug()<<"uspech";

    loadSpecialAnnouncementList(doc);
    file.close();
}

void SpecialAnnouncementParser::createDefaultFile()
{
    qDebug() <<  Q_FUNC_INFO;


    QString filename=cesta+"/konfigurace/konfigurace.xml";
    if(fileExists(filename))
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


bool SpecialAnnouncementParser::fileExists(QString path)
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


int SpecialAnnouncementParser::loadSpecialAnnouncementList(QDomDocument xmlko)
{
    QDomNodeList domAnnouncementList=xmlko.firstChildElement("announcementList").elementsByTagName("announcement");
    announcementList.clear();
    if(domAnnouncementList.isEmpty())
    {
        return 0;
    }

    for(int i=0; i<domAnnouncementList.count(); i++)
    {
        QDomElement element=domAnnouncementList.at(i).toElement();
        AdditionalAnnoucement newAnnouncement;
        newAnnouncement.displayName=element.firstChildElement("displayName").text();
        newAnnouncement.duration=element.firstChildElement("duration").text().toInt()*1000;
        newAnnouncement.type=element.firstChildElement("type").text();
        newAnnouncement.icon=element.firstChildElement("icon").text();
        newAnnouncement.text=element.firstChildElement("text").text();
        newAnnouncement.changeFrom=element.firstChildElement("changeFrom").text();
        newAnnouncement.changeTo=element.firstChildElement("changeTo").text();



        QDomNodeList segmentyMp3=element.elementsByTagName("mp3");
        for(int j=0;j<segmentyMp3.count();j++)
        {
            QString mp3soubor=segmentyMp3.at(j).firstChild().nodeValue();
            qDebug()<<"nactena MP3: "<<mp3soubor;
            newAnnouncement.mp3.push_back(mp3soubor);
        }

        announcementList.push_back(newAnnouncement);

        qDebug()<<"nacteno specialni hlaseni "<<newAnnouncement.type<<" "<<newAnnouncement.icon<<" "<<newAnnouncement.displayName<<" "<<newAnnouncement.text<<" pocetMP3:"<<newAnnouncement.mp3.count();



    }

    return 1;
}


