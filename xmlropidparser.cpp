#include <QtSql>
#include "xmlropidparser.h"

#include <QtXml>
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>





XmlRopidParser::XmlRopidParser()
{





}

void XmlRopidParser::databazeStart(QString adresaServeru)
{
    ropidSQL.Pripoj(adresaServeru );
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
    //vlozTv(koren);
    vlozTv2(koren);
    vlozM(koren);
    vlozD(koren);
    vlozP(koren);
    vlozZ(koren);
    vlozL(koren);
    vlozS(koren);
    vlozT(koren);

}


int XmlRopidParser::vlozDd(QDomElement koren)
{
    qDebug()<<"zacatekImportuDd";
    QDomNodeList m=koren.elementsByTagName("dd");
    for (int i=0;i<m.count();i++)
    {
        /*
        QString queryString("INSERT INTO dd(c,z,n)  VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=(" \",\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\");");
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
        */
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        //navrat polozka{"c",overInteger( m.at(i).toElement().attribute("c"))};
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        QString queryString=this->slozInsert("dd",polozky);
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuDd";
    return 1;
}


int XmlRopidParser::vlozTv(QDomElement koren)
{
    QDomNodeList m=koren.elementsByTagName("tv");
    for (int i=0;i<m.count();i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO tv(c,z,n,dd,np) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,");
        queryString+=(overString( m.at(i).toElement().attribute("z")));
        queryString+=(" ,\"");
        /*
         * queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("z"));
        queryString+=("\" ,\"");
        */
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
        qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }

    return 1;
}



int XmlRopidParser::vlozTv2(QDomElement koren)
{
    qDebug()<<"XmlRopidParser::vlozTv2";
    QDomNodeList m=koren.elementsByTagName("tv");
    for (int i=0;i<m.count();i++)
    {
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        //navrat polozka{"c",overInteger( m.at(i).toElement().attribute("c"))};
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("dd",element.attribute("dd"),"Integer"));
        polozky.push_back(inicializujPolozku("np",element.attribute("np"),"Boolean"));
        QString queryString=this->slozInsert("tv",polozky);
        qDebug()<<"TV2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    return 1;
}

XmlRopidParser::navrat XmlRopidParser::inicializujPolozku(QString nazevSloupce,QString obsah,QString typ)
{
    navrat ahoj;
    ahoj.typ=typ;
    ahoj.obsah=obsah;
    ahoj.nazevSloupce=nazevSloupce;

    if (ahoj.typ=="String")
    {
        ahoj.obsah=overString(obsah);
    }
    if (ahoj.typ=="Integer")
    {
        ahoj.obsah=overInteger(obsah);
    }
    if (ahoj.typ=="Boolean")
    {
        ahoj.obsah=overBoolean(obsah);
    }


    return ahoj;
}

QString XmlRopidParser::slozInsert(QString nazevTabulky, QVector<navrat> seznam)
{
    QString prikaz="";
    QString zacatek="INSERT INTO "+nazevTabulky+" (";
    QString hodnoty="";
    QString konec="  );";
    for(int i=0;i<(seznam.length());i++)
    {
        zacatek+=seznam[i].nazevSloupce;
        hodnoty+=seznam[i].obsah;
        if (i!= seznam.length()-1 )
        {
            zacatek+=" , ";
            hodnoty+=" , ";
        }
    }

    QString prostredek=") VALUES( ";
    prikaz=zacatek+prostredek+hodnoty+konec;

    return prikaz;
}



int XmlRopidParser::vlozL(QDomElement koren)
{

    qDebug()<<"zacatekImportuL";
    QDomNodeList m=koren.elementsByTagName("l");
    for (int i=0;i<m.count();i++)
    {
        //qDebug()<<m.at(i).toElement().attribute("n");
        /*QString queryString("INSERT INTO l(c,d,lc,tl,n,kup,ids,noc) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,\"");
        queryString+=(m.at(i).toElement().attribute("d"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("lc"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("tl"));
        queryString+=("\" ,\"");
        queryString+=(m.at(i).toElement().attribute("n"));
        queryString+=("\" ,");
        queryString+=overInteger(m.at(i).toElement().attribute("kup"));
        queryString+=(" ,");
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
*/
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        //navrat polozka{"c",overInteger( m.at(i).toElement().attribute("c"))};
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("d",element.attribute("d"),"Integer"));
        polozky.push_back(inicializujPolozku("lc",element.attribute("lc"),"Integer"));
        polozky.push_back(inicializujPolozku("tl",element.attribute("tl"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("kup",element.attribute("kup"),"Integer"));
        polozky.push_back(inicializujPolozku("ids",element.attribute("ids"),"Boolean"));
        polozky.push_back(inicializujPolozku("noc",element.attribute("noc"),"Boolean"));
        QString queryString=this->slozInsert("l",polozky);
        qDebug()<<"l2 "<<queryString;
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
        // QString queryString("INSERT INTO d(c,n,ncis,ico,dic,ul,me,psc,tel,em) VALUES( ");
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("ncis",element.attribute("ncis"),"String"));
        polozky.push_back(inicializujPolozku("ico",element.attribute("ico"),"Integer"));
        polozky.push_back(inicializujPolozku("dic",element.attribute("dic"),"String"));
        polozky.push_back(inicializujPolozku("ul",element.attribute("ul"),"String"));
        polozky.push_back(inicializujPolozku("me",element.attribute("me"),"String"));
        polozky.push_back(inicializujPolozku("psc",element.attribute("psc"),"Integer"));
        polozky.push_back(inicializujPolozku("tel",element.attribute("tel"),"String"));
        polozky.push_back(inicializujPolozku("em",element.attribute("em"),"String"));
        QString queryString=this->slozInsert("d",polozky);
        qDebug()<<"d2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    qDebug()<<"konecImportuD";
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
        //QString queryString("INSERT INTO p(c,z,n,d,dd,u,mail)  VALUES( ");
        //qDebug()<<m.at(i).toElement().attribute("n");

        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("d",element.attribute("d"),"Integer"));
        polozky.push_back(inicializujPolozku("dd",element.attribute("dd"),"Integer"));
        polozky.push_back(inicializujPolozku("u",element.attribute("u"),"Integer"));
        polozky.push_back(inicializujPolozku("mail",element.attribute("mail"),"String"));
        QString queryString=this->slozInsert("p",polozky);
        qDebug()<<"p2 "<<queryString;
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
        //QString queryString("INSERT INTO m(c,n) VALUES( ");
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));

        QString queryString=this->slozInsert("m",polozky);
        qDebug()<<"m2 "<<queryString;
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
        //QString queryString("INSERT INTO z(u,z,kj,n,pop,cis,ois,co,no,spz,ids,tp,sx,sy,lat,lng,sta,m,bbn,kidos,st,xA,xB,xC,xVla,xLod,xLet) VALUES( ");
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("u",element.attribute("u"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"Integer"));
        polozky.push_back(inicializujPolozku("kj",element.attribute("kj"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("pop",element.attribute("pop"),"String"));
        polozky.push_back(inicializujPolozku("cis",element.attribute("cis"),"Integer"));
        polozky.push_back(inicializujPolozku("ois",element.attribute("ois"),"Integer"));
        polozky.push_back(inicializujPolozku("co",element.attribute("co"),"Integer"));
        polozky.push_back(inicializujPolozku("no",element.attribute("no"),"String"));
        polozky.push_back(inicializujPolozku("spz",element.attribute("spz"),"String"));
        polozky.push_back(inicializujPolozku("ids",element.attribute("ids"),"Integer"));
        polozky.push_back(inicializujPolozku("tp",element.attribute("tp"),"String"));
        polozky.push_back(inicializujPolozku("sx",element.attribute("sx"),"String"));
        polozky.push_back(inicializujPolozku("sy",element.attribute("sx"),"String"));
        polozky.push_back(inicializujPolozku("lat",element.attribute("lat"),"String"));
        polozky.push_back(inicializujPolozku("lng",element.attribute("lng"),"String"));
        polozky.push_back(inicializujPolozku("sta",element.attribute("sta"),"String"));
        polozky.push_back(inicializujPolozku("m",element.attribute("m"),"Integer"));
        polozky.push_back(inicializujPolozku("bbn",element.attribute("bbn"),"Boolean"));
        polozky.push_back(inicializujPolozku("kidos",element.attribute("kidos"),"Integer"));
        polozky.push_back(inicializujPolozku("st",element.attribute("st"),"String"));
        polozky.push_back(inicializujPolozku("xA",element.attribute("xA"),"Boolean"));
        polozky.push_back(inicializujPolozku("xB",element.attribute("xB"),"Boolean"));
        polozky.push_back(inicializujPolozku("xC",element.attribute("xC"),"Boolean"));
        polozky.push_back(inicializujPolozku("xVla",element.attribute("xVla"),"Boolean"));
        polozky.push_back(inicializujPolozku("xLod",element.attribute("xLod"),"Boolean"));
        polozky.push_back(inicializujPolozku("xLet",element.attribute("xLed"),"Boolean"));

        QString queryString=this->slozInsert("z",polozky);
        qDebug()<<"z2 "<<queryString;
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
        // QString queryString("INSERT INTO s(s,id,l,p,dd,pr,d,tv,kj,ty,ch,ids,vy,man,c,neve) VALUES( ");
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("s",element.attribute("s"),"Integer"));
        polozky.push_back(inicializujPolozku("id",element.attribute("id"),"Integer"));
        polozky.push_back(inicializujPolozku("l",element.attribute("l"),"Integer"));
        polozky.push_back(inicializujPolozku("p",element.attribute("p"),"Integer"));
        polozky.push_back(inicializujPolozku("dd",element.attribute("dd"),"Integer"));
        polozky.push_back(inicializujPolozku("pr",element.attribute("pr"),"Integer"));
        polozky.push_back(inicializujPolozku("d",element.attribute("d"),"Integer"));
        polozky.push_back(inicializujPolozku("tv",element.attribute("tv"),"Integer"));
        polozky.push_back(inicializujPolozku("kj",element.attribute("kj"),"String"));
        polozky.push_back(inicializujPolozku("ty",element.attribute("ty"),"Integer"));
        polozky.push_back(inicializujPolozku("ch",element.attribute("ch"),"Integer"));
        polozky.push_back(inicializujPolozku("ids",element.attribute("ids"),"Boolean"));
        polozky.push_back(inicializujPolozku("vy",element.attribute("vy"),"Boolean"));
        polozky.push_back(inicializujPolozku("man",element.attribute("man"),"Boolean"));
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("neve",element.attribute("neve"),"Boolean"));



        QString queryString=this->slozInsert("s",polozky);
        qDebug()<<"s2 "<<queryString;
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
        //  QString queryString("INSERT INTO t(u,z,ois,cis,nza,ri,ji,vtm,vtn,btm,btn,ctm,ctn,lcdm,lcdn) VALUES( ");
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;

        polozky.push_back(inicializujPolozku("u",element.attribute("u"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"Integer"));
        polozky.push_back(inicializujPolozku("ois",element.attribute("ois"),"Integer"));
        polozky.push_back(inicializujPolozku("cis",element.attribute("cis"),"Integer"));
        polozky.push_back(inicializujPolozku("nza",element.attribute("nza"),"String"));
        polozky.push_back(inicializujPolozku("ri",element.attribute("ri"),"String"));
        polozky.push_back(inicializujPolozku("ji",element.attribute("ji"),"String"));
        polozky.push_back(inicializujPolozku("vtm",element.attribute("vtm"),"String"));
        polozky.push_back(inicializujPolozku("vtn",element.attribute("vtn"),"String"));
        polozky.push_back(inicializujPolozku("btm",element.attribute("btm"),"String"));
        polozky.push_back(inicializujPolozku("btn",element.attribute("btn"),"String"));
        polozky.push_back(inicializujPolozku("ctm",element.attribute("ctm"),"String"));
        polozky.push_back(inicializujPolozku("ctn",element.attribute("ctn"),"String"));
        polozky.push_back(inicializujPolozku("lcdm",element.attribute("lcdm"),"String"));
        polozky.push_back(inicializujPolozku("lcdn",element.attribute("lcdn"),"String"));

        /*
        polozky.push_back(inicializujPolozku("",element.attribute(""),"Integer"));
        polozky.push_back(inicializujPolozku("",element.attribute(""),"String"));
        polozky.push_back(inicializujPolozku("",element.attribute(""),"Boolean"));
        */



        QString queryString=this->slozInsert("t",polozky);
        qDebug()<<"t2 "<<queryString;
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
        /*
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
        queryString+=(" );");
        qDebug()<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze); */

       // QString queryString("INSERT INTO x(s_id,u,z,p,o,t,ty,ces,zn,na,vyst,nast,xA,xB,xC,xD,xVla,xLod,xLet) VALUES( ");

        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("s_id",koren.attribute("s"),"Integer"));
        polozky.push_back(inicializujPolozku("u",element.attribute("u"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"Integer"));
        polozky.push_back(inicializujPolozku("p",element.attribute("p"),"Integer"));
        polozky.push_back(inicializujPolozku("o",element.attribute("o"),"Integer"));
        polozky.push_back(inicializujPolozku("t",element.attribute("t"),"String"));
        polozky.push_back(inicializujPolozku("ty",element.attribute("ty"),"Integer"));
        polozky.push_back(inicializujPolozku("ces",element.attribute("ces"),"Boolean"));
        polozky.push_back(inicializujPolozku("zn",element.attribute("zn"),"Boolean"));
        polozky.push_back(inicializujPolozku("na",element.attribute("na"),"Boolean"));
        polozky.push_back(inicializujPolozku("vyst",element.attribute("vyst"),"Boolean"));
        polozky.push_back(inicializujPolozku("nast",element.attribute("nast"),"Boolean"));
        polozky.push_back(inicializujPolozku("xA",element.attribute("xA"),"Boolean"));
        polozky.push_back(inicializujPolozku("xB",element.attribute("xB"),"Boolean"));
        polozky.push_back(inicializujPolozku("xC",element.attribute("xC"),"Boolean"));
        polozky.push_back(inicializujPolozku("xD",element.attribute("xC"),"Boolean"));
        polozky.push_back(inicializujPolozku("xVla",element.attribute("xVla"),"Boolean"));
        polozky.push_back(inicializujPolozku("xLod",element.attribute("xLod"),"Boolean"));
        polozky.push_back(inicializujPolozku("xLet",element.attribute("xLed"),"Boolean"));


        /*
        polozky.push_back(inicializujPolozku("",element.attribute(""),"Integer"));
        polozky.push_back(inicializujPolozku("",element.attribute(""),"String"));
        polozky.push_back(inicializujPolozku("",element.attribute(""),"Boolean"));
        */



        QString queryString=this->slozInsert("x",polozky);
        qDebug()<<"x2 "<<queryString;
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
    truncateTable("`t`");
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

QString XmlRopidParser::overString(QString vstup)
{
    if (vstup=="")
    {
        vstup="NULL";
    }
    else
    {
        vstup="\""+vstup+"\"";
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
