#include <QtSql>
#include "xmlropidparser.h"

#include <QtXml>
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>




XmlRopidParser::XmlRopidParser()
{





}

void XmlRopidParser::databazeStart()
{
    ropidSQL.Pripoj();
}


void XmlRopidParser::otevriSoubor()
{
    qDebug()<<"predOtevrenimSouboru";
    QDomDocument doc("mydocument");
    QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"fail1";
        return;
    }
    if (!doc.setContent(&file))
    {
        qDebug()<<"fail2";
        file.close();
        return;
    }
    file.close();
    qDebug()<<"uspech";
    QDomElement koren=doc.firstChildElement();
    vlozM(koren);
    vlozD(koren);
    vlozZ(koren);

}

int XmlRopidParser::vlozD(QDomElement koren)
{
    QDomNodeList m=koren.elementsByTagName("d");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO d(c,n,ncis,ico,dic,ul,me,psc,tel,em) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ncis"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ico"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("dic"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ul"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("me"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("psc"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("tel"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("em"));

        queryString+=("\"  );");
        qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }

    return 1;
}

int XmlRopidParser::vlozM(QDomElement koren)
{

    QDomNodeList m=koren.elementsByTagName("m");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO m(c,n) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\"  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    return 1;
}


int XmlRopidParser::vlozZ(QDomElement koren)
{
    QDomNodeList m=koren.elementsByTagName("z");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO z(u,z,n,pop,cis,ois,co,no,spz,ids,tp,sx,sy,lat,lng,sta,m,bbn,kidos,st) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("u"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("pop"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("cis"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ois"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("co"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("no"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("spz"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ids"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("tp"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("sx"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("sy"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("lat"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("lng"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("sta"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("m"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("bbn"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("kidos"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("st"));

        queryString+=("\"  );");
        qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }

    return 1;
}




/*
int XmlMpvParser::parsujDomDokument()
{
    qDebug()<<"parsujDomDokument";
    QDomElement root = vstupniDomDokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("t").at(0).toElement().elementsByTagName("o");
    int docasnyPocetPrestupu= nodes.count();
    for (int i=0; i<nodes.count();i++)
    {
        mujPrestup[i].stan=nodes.at(i).attributes().namedItem("stan").nodeValue();
        mujPrestup[i].lin=nodes.at(i).attributes().namedItem("lin").nodeValue();
        mujPrestup[i].alias=nodes.at(i).attributes().namedItem("alias").nodeValue();
        mujPrestup[i].spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();
        mujPrestup[i].smer=nodes.at(i).attributes().namedItem("smer").nodeValue();
        mujPrestup[i].odj=nodes.at(i).attributes().namedItem("odj").nodeValue();
        mujPrestup[i].zpoz=nodes.at(i).attributes().namedItem("zpoz").nodeValue().toInt();
        mujPrestup[i].sled=nodes.at(i).attributes().namedItem("sled").nodeValue().toInt();
        mujPrestup[i].np=nodes.at(i).attributes().namedItem("np").nodeValue().toInt();
        mujPrestup[i].nad=nodes.at(i).attributes().namedItem("nad").nodeValue().toInt();
        mujPrestup[i].t=nodes.at(i).attributes().namedItem("t").nodeValue();
        mujPrestup[i].dd=nodes.at(i).attributes().namedItem("dd").nodeValue().toInt();
        mujPrestup[i].smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();
        qDebug()<<mujPrestup[i].smer;
    }
    return docasnyPocetPrestupu;
}
*/
