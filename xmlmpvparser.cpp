#include "xmlmpvparser.h"



XmlMpvParser::XmlMpvParser()
{
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
}
XmlMpvParser::~XmlMpvParser()
{
}

void XmlMpvParser::naplnVstupDokument(QByteArray vstup)
{
    qDebug()<<"XmlMpvParser::naplnVstupDokument\n";
    QByteArray llooll = vstup;
    QString s = QString::fromUtf8(vstup);
    QString str =QString::fromUtf8(vstup);
    s = QString::fromUtf8(str.toLatin1());
    vstupniDomDokument.setContent(llooll);
}

QVector<PrestupMPV> XmlMpvParser::parsujDomDokument()
{
    qDebug()<<"XmlMpvParser::parsujDomDokument";
    QDomElement root = vstupniDomDokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("t").at(0).toElement().elementsByTagName("o");
    seznamPrestupu.clear();
    for (int i=0; i<nodes.count();i++)
    {
        PrestupMPV novy;
        novy.stan=nodes.at(i).attributes().namedItem("stan").nodeValue();
        novy.lin=nodes.at(i).attributes().namedItem("lin").nodeValue();
        novy.alias=nodes.at(i).attributes().namedItem("alias").nodeValue();
        novy.spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();
        novy.smer=nodes.at(i).attributes().namedItem("smer").nodeValue();
        novy.zpoz=nodes.at(i).attributes().namedItem("zpoz").nodeValue().toInt();
        QDateTime odjezd=PrestupMPV::qStringDoQDateTime( nodes.at(i).attributes().namedItem("odj").nodeValue());
        novy.odj=odjezd;
         novy.odjReal=PrestupMPV::posunTimeStampZpozdeni( odjezd, novy.zpoz );
        novy.sled=nodes.at(i).attributes().namedItem("sled").nodeValue().toInt();
        if (nodes.at(i).attributes().namedItem("np").nodeValue()=="true")
        {novy.np=1;}
        else
        {novy.np=0;}
        novy.nad=nodes.at(i).attributes().namedItem("nad").nodeValue().toInt();
        novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();
        novy.dd=nodes.at(i).attributes().namedItem("dd").nodeValue().toInt();
        novy.smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();
        seznamPrestupu.append(novy);
        qDebug()<<novy.smer;

    }




    return seznamPrestupu;
}


// zdroj https://stackoverflow.com/questions/7218851/making-an-http-get-under-qt
//manager->get(QNetworkRequest(QUrl("http://www.mpvnet.cz/PID/x/21619?pocet=15&pz=true&t=true")));

void XmlMpvParser::stahniMpvXml(int cisloCis, QString Ids)
{
    qDebug()<<"XmlMpvParser::StahniMpvXml";


    // QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?pocet=15&pz=true&t=true";
   // QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?unite=true&ko=12702&pocet=24&t=true&ts=396"; //timeshift nočky
    QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?unite=true&ko=12702&pocet=24&t=true";
    qDebug()<<adresa;
    manager->get(QNetworkRequest(QUrl(adresa)));

}


QByteArray XmlMpvParser::requestReceived(QNetworkReply* replyoo)
{
    qDebug()<<"XmlMpvParser::requestReceived";
    QByteArray rawData = replyoo->readAll();
    QString textData(rawData);
    qDebug() << textData;
    this->stazenaData=rawData;
    emit stazeniHotovo();
    return rawData;
}

QVector<PrestupMPV> XmlMpvParser::vyfiltrujPrestupy(QVector<PrestupMPV> vstupniPrestupy, Linka linka)
{
    qDebug()<<"XmlMpvParser::vyfiltrujPrestupy";
    QVector<PrestupMPV> vyfiltrovanePrestupy;

    foreach(PrestupMPV aktualniPrestup, vstupniPrestupy)
    {
        if(aktualniPrestup.alias!=linka.LineName)
        {
            if(!jePrestupNaSeznamu(aktualniPrestup,vyfiltrovanePrestupy))
            {
                vyfiltrovanePrestupy.push_back(aktualniPrestup);
            }
        }
    }
    return vyfiltrovanePrestupy;
}



bool XmlMpvParser::jePrestupNaSeznamu(PrestupMPV prestup, QVector<PrestupMPV> seznamPrestupu)
{
    qDebug()<<"XmlMpvParser::jePrestupNaSeznamu";


    foreach(PrestupMPV testPrestup, seznamPrestupu)
    {
        if(testPrestup.alias==prestup.alias)
        {
            if(testPrestup.smer_c==prestup.smer_c)
            {
                return true;
            }
        }
    }
    return false;

}





