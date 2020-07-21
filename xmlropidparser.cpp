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
    vlozDd(koren);
    vlozTv(koren);
    vlozM(koren);
    vlozD(koren);
    vlozP(koren);
    vlozZ(koren);
    vlozL(koren);
    vlozS(koren);
    vlozT(koren);

}

int XmlRopidParser::vlozTv(QDomElement koren)
{
    QDomNodeList m=koren.elementsByTagName("tv");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO tv(c,z,n,dd,np) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("dd"));
        queryString+=("\" ,");
        if(m.at(i).toElement().attribute("np")=="")
        {
          queryString+="false";
        }
        else
        {
            queryString+=(m.at(i).toElement().attribute("np"));


        }


        queryString+=("  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }

    return 1;
}


int XmlRopidParser::vlozL(QDomElement koren)
{
    qDebug()<<"zacatekImportuL";
    QDomNodeList m=koren.elementsByTagName("l");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO l(c,d,lc,tl,n,kup,ids,noc) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("d"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("lc"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("tl"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("kup"));
        queryString+=("\" ,");
        if(m.at(i).toElement().attribute("ids")=="")
        {
          queryString+="NULL";
        }
        else
        {
            queryString+=(m.at(i).toElement().attribute("ids"));


        }
        queryString+=( ",");
        if(m.at(i).toElement().attribute("noc")=="")
        {
          queryString+="NULL";
        }
        else
        {
            queryString+=(m.at(i).toElement().attribute("noc"));


        }

        /*
        queryString+=(m.at(i).toElement().attribute(""));
        queryString+=("\" ,\"");
        */
        queryString+=("  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuL";
    return 1;
}

int XmlRopidParser::vlozD(QDomElement koren)
{
    qDebug()<<"zacatekImportuD";
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
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuD";
    return 1;
}
int XmlRopidParser::vlozDd(QDomElement koren)
{
    qDebug()<<"zacatekImportuDd";
    QDomNodeList m=koren.elementsByTagName("dd");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO dd(c,z,n)  VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\");");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuDd";
    return 1;
}


int XmlRopidParser::vlozP(QDomElement koren)
{
    qDebug()<<"vlozP";
    qDebug()<<"zacatekImportuP";
    QDomNodeList m=koren.elementsByTagName("p");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO p(c,z,n,d,dd,u,mail)  VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("d"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("dd"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("u"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("mail"));
        queryString+=("\"  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuP";
    return 1;
}

int XmlRopidParser::vlozM(QDomElement koren)
{
    qDebug()<<"zacatekImportuM";
    QDomNodeList m=koren.elementsByTagName("m");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO m(c,n) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\"  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuM";
    return 1;
}


int XmlRopidParser::vlozZ(QDomElement koren)
{
    qDebug()<<"zacatekImportuZ";
    QDomNodeList m=koren.elementsByTagName("z");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO z(u,z,kj,n,pop,cis,ois,co,no,spz,ids,tp,sx,sy,lat,lng,sta,m,bbn,kidos,st,xA,xB,xC,xVla,xLod,xLet) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("u"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("kj"));
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
        queryString+=("\" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xA"));
        queryString+=(" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xB"));
        queryString+=(" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xC"));
        queryString+=(" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xVla"));
        queryString+=(" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xLod"));
        queryString+=(" ,");
        queryString+=overBoolean(m.at(i).toElement().attribute("xLet"));
        queryString+=("  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuZ";
    return 1;
}

int XmlRopidParser::vlozS(QDomElement koren)
{
    qDebug()<<"zacatekImportuS";
    QDomNodeList m=koren.elementsByTagName("s");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO s(s,id,l,p,dd,pr,d,tv,kj,ty,ch,ids,vy,man,c,neve) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("s"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("id"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("l"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("p"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("dd"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("pr"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("d"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("tv"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("kj"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ty"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ch"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("ids"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("vy"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("man"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("neve"));
        //queryString+=("\" ,\"");



        queryString+=("\"  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
        vlozX(m.at(i).toElement());
    }
    qDebug()<<"konecImportuS";
    return 1;
}


int XmlRopidParser::vlozT(QDomElement koren)
{
    qDebug()<<"zacatekImportuT";
    QDomNodeList m=koren.elementsByTagName("t");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO t(u,z,ois,cis,nza,ri,ji,vtm,vtn,btm,btn,ctm,ctn,lcdm,lcdn) VALUES( ");
        QDomElement prvek=m.at(i).toElement();
        queryString+=(prvek.attribute("u"));
        queryString+=(" ,\"");
        queryString+=(prvek.attribute("z"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ois"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("cis"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("nza"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ri"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ji"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("vtm"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("vtn"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("btm"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("btn"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ctm"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ctn"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("lcdm"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("lcdn"));
        //queryString+=("\" ,\"");



        queryString+=("\"  );");
        //qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuT";

    return 1;
}


int XmlRopidParser::vlozX(QDomElement koren)
{
    qDebug()<<"zacatekImportuX";
    QDomNodeList m=koren.elementsByTagName("x");
    for (int i=0;i<m.count();i++)
    {
        QDomElement prvek=m.at(i).toElement();
        //qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO x(s_id,u,z,p,o,t,ty,ces,zn,na,vyst,nast,xA,xB,xC,xD,xVla,xLod,xLet) VALUES( ");
        queryString+=(koren.attribute("s"));
        queryString+=(" ,\"");
        queryString+=(prvek.attribute("u"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("z"));
        queryString+=("\" ,");
        queryString+=(overInteger( prvek.attribute("p")));
        queryString+=(" ,");
        queryString+=(overInteger(prvek.attribute("o")));
        queryString+=(" ,\"");
        queryString+=(prvek.attribute("t"));
        queryString+=("\" ,\"");
        queryString+=(prvek.attribute("ty"));
        queryString+=("\" ,");
        queryString+=(overBoolean( prvek.attribute("ces")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("zn")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("na")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("vyst")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("nast")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xA")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xB")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xC")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xD")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xVla")));
        queryString+=(" ,");
        queryString+=(overBoolean( prvek.attribute("xLod")));
        queryString+=(" ,");
        queryString+=(overBoolean(  prvek.attribute("xLet")));
        //queryString+=("\" ,\"");



        queryString+=(" );");
        qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuX";

    return 1;
}


int XmlRopidParser::truncateTable(QString tabulka)
{

    QString queryString = ("DELETE FROM ");
    queryString+=tabulka;
    qDebug()<<queryString;
    QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    return 1;
}

int XmlRopidParser::truncateAll()
{
    /*
     * vlozM(koren);
    vlozD(koren);
    vlozZ(koren);
     * */
    //truncateTable("`t`");
    truncateTable("`x`");
    truncateTable("`s`");
    truncateTable("`l`");
    truncateTable("`z`");
    truncateTable("`m`");
    truncateTable("`p`");
    truncateTable("`d`");
    truncateTable("`tv`");
    truncateTable("`dd`");
    //truncateTable("");
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


QString XmlRopidParser::overBoolean(QString vstup)
{
    if (vstup=="")
    {
        vstup="false";
    }

    return vstup;
}


QString XmlRopidParser::overInteger(QString vstup)
{
    if (vstup=="")
    {
        vstup="NULL";
    }

    return vstup;
}

QString XmlRopidParser::vytvorCas(QString vstup)
{
    int cislo=vstup.toInt();
    int hodiny=cislo/3600;
    int minuty=(cislo%3600)/60;
    int sekundy=(cislo%3600)%60;
    vstup="";
    vstup=QString::number(hodiny)+""+QString::number(minuty)+""+QString::number(sekundy);
    return vstup;
}
