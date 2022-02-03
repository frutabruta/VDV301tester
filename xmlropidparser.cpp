#include <QtSql>
#include "xmlropidparser.h"

#include <QtXml>
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>





XmlRopidParser::XmlRopidParser()
{
    vstupniXmlSouborCesta="xml_zdroje/XML_X926_20211006_20211012";
}

int XmlRopidParser::databazeStart(QString adresaServeru)
{
    return   ropidSQL.Pripoj();
}


void XmlRopidParser::otevriSoubor(QString cesta)
{
    qDebug()<<"predOtevrenimSouboru";
    QDomDocument doc("mydocument");
    // QFile file("xml_zdroje/XML_Zlicin_20200702_20200705.xml");

    QFile file(cesta);





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




    /*
    ropidSQL.mojeDatabaze.close();
    ropidSQL.mojeDatabaze.open();
    */
    // ropidSQL.mojeDatabaze.close();
    this->databazeStart("ahoj");
    qDebug()<<"is driver available "<<QString::number(ropidSQL.mojeDatabaze.isDriverAvailable("QSQLITE"));
    qDebug()<<"je databaze otevrena "<<QString::number(ropidSQL.mojeDatabaze.isOpen());
    qDebug()<<"je databaze validni "<<QString::number(ropidSQL.mojeDatabaze.isValid());
    if(ropidSQL.mojeDatabaze.transaction())
    {
        // QSqlQuery query(ropidSQL.mojeDatabaze);
        vlozPlatnost(koren, platnostOd, platnostDo);
        vlozDd(koren);
        emit odesliChybovouHlasku("dokoncen import Dd");
        //vlozTv(koren);
        vlozTv2(koren);

        vlozM(koren);

        vlozD(koren);

        vlozP(koren);

        vlozZ(koren);

        vlozL(koren);

        vlozS(koren);

        vlozT(koren);
        vlozO(koren);

        //emit odesliChybovouHlasku("Import hotov!");

        if(!ropidSQL.mojeDatabaze.commit())
        {
            qDebug() << "Failed to commit";
            ropidSQL.mojeDatabaze.rollback();
        }
    }
    else
    {
        qDebug() << "Failed to start transaction mode";
        qDebug()<<ropidSQL.mojeDatabaze.lastError();
    }
    ropidSQL.zavriDB();


}



int XmlRopidParser::vlozPlatnost(QDomElement koren, QDate &plOd, QDate &plDo)
{
    qDebug()<<"XmlRopidParser::vlozPlatnost";


    plOd=QDate::fromString(koren.attribute("od"),Qt::ISODate);
    plDo=QDate::fromString(koren.attribute("do"),Qt::ISODate);


    // QString queryString("INSERT INTO hlavicka(platnostod,platnostdo) VALUES("+ plOd.toString(Qt::ISODate)+","+plDo.toString(Qt::ISODate)+")");









    QDomElement element = koren;
    QVector<navrat> polozky;
    polozky.push_back(inicializujPolozku("od",element.attribute("od"),"String"));
    polozky.push_back(inicializujPolozku("do",element.attribute("do"),"String"));
    polozky.push_back(inicializujPolozku("režim",element.attribute("režim"),"String"));
    QString queryString=this->slozInsert("hlavicka",polozky);
    QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    qDebug()<<queryString;


    QString vystup="platnost dat od "+plOd.toString(Qt::ISODate)+" do "+plDo.toString(Qt::ISODate);
    //   QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    qDebug()<<vystup;
    emit odesliChybovouHlasku(vystup );






    return 1;
}


int XmlRopidParser::vlozDd(QDomElement koren)
{
    qDebug()<<"zacatekImportuDd";
    QDomNodeList m=koren.elementsByTagName("dd");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku Dd je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {

        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
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
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku Tv je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku ;i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
        QString queryString("INSERT INTO tv(c,z,n,dd,np) VALUES( ");
        queryString+=(m.at(i).toElement().attribute("c"));
        queryString+=(" ,");
        queryString+=(overString( m.at(i).toElement().attribute("z")));
        queryString+=(" ,\"");
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
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku Tv2 je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("z",element.attribute("z"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("dd",element.attribute("dd"),"Integer"));
        polozky.push_back(inicializujPolozku("np",element.attribute("np"),"Boolean"));
        QString queryString=this->slozInsert("tv",polozky);
        qDebug()<<"TV2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    emit odesliChybovouHlasku("dokoncen import Tv2");
    return 1;
}

int XmlRopidParser::vlozO(QDomElement koren)
{
    qDebug()<<"XmlRopidParser::vlozO";
    QDomNodeList m=koren.elementsByTagName("o");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku O je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("l",element.attribute("l"),"Integer"));
        polozky.push_back(inicializujPolozku("p",element.attribute("p"),"Integer"));
        polozky.push_back(inicializujPolozku("kj",element.attribute("kj"),"String"));
        //přepsat pro vložení spojů jednotlivě!
        polozky.push_back(inicializujPolozku("sp",element.attribute("sp"),"String"));
        polozky.push_back(inicializujPolozku("tv",element.attribute("tv"),"Integer"));
        polozky.push_back(inicializujPolozku("td",element.attribute("td"),"Integer"));
        vlozSpPo(element);
        QString queryString=this->slozInsert("o",polozky);
        qDebug()<<"O "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    emit odesliChybovouHlasku("dokoncen import O");
    return 1;
}


int XmlRopidParser::vlozSpPo(QDomElement koren)
{
    qDebug()<<"XmlRopidParser::vlozSpPo";
    QDomElement element = koren;
    //QDomNodeList m=koren.elementsByTagName("s");


    QString spoje="2971 2972 2973 2974 2975 2976 2977 2978 2979 2980 2981 2982 2983 2984 2985 2986 2987 2988 2989 2990 2991 2992 2993 2994 2995 2996 2997 2998 2999 3000 3001";
    spoje=element.attribute("sp");
    QStringList seznam=spoje.split(" ");

    QString linka=element.attribute("l");
    QString poradi=element.attribute("p");
    QString kalendar=element.attribute("kj");
    //element.attribute("sp")

    int pocetPrvku=seznam.count();
    qDebug()<<"pocet spoju v obehu "+element.attribute("l")+"/"+element.attribute("p")+" je "<<pocetPrvku;

    QDomNodeList dlouheSpoje=element.elementsByTagName("ds");

    QVector<int> navazujiciSpoje=seznamDlouhychSpoju(dlouheSpoje);

    for (int i=0;i<pocetPrvku;i++)
    {
        //QDomElement element = m.at(i).toElement();


        //QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("l",linka,"Integer"));
        polozky.push_back(inicializujPolozku("p",poradi,"Integer"));
        polozky.push_back(inicializujPolozku("kj",kalendar,"String"));
        //přepsat pro vložení spojů jednotlivě!
        polozky.push_back(inicializujPolozku("s",seznam.at(i),"Integer"));
        polozky.push_back(inicializujPolozku("pokrac",QString::number(navazujiciSpoje.contains(seznam.at(i).toInt())),"Boolean"));
        polozky.push_back(inicializujPolozku("ord",QString::number(i),"Integer"));
        //vlozSpPo(element);
        QString queryString=this->slozInsert("sp_po",polozky);
        qDebug()<<"sp_po "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }

    qDebug()<<"konecImportu sp_po";
    return 1;
}

QVector<int> XmlRopidParser::seznamDlouhychSpoju(QDomNodeList &dlouheSpoje)
{
    qDebug()<<"XmlRopidParser::seznamDlouhychSpoju";
    QVector<int> navazujiciSpoje;

    for(int i=0;i<dlouheSpoje.length();i++)
    {
        QString retezec= dlouheSpoje.at(i).toElement().attribute("sp");
        qDebug()<<"retezec dlouhych spoju "<<retezec;
        QStringList seznam= retezec.split(" ");

        if (seznam.length()>1)
        {
            seznam.removeLast();

            for (int j=0;j<seznam.length();j++)
            {
                navazujiciSpoje.append(seznam.at(j).toInt());
                qDebug()<<"navazujici spoj "<<seznam.at(j).toInt();
            }
        }
        else
        {
            qDebug()<<"seznam dlouhych spoju je prazdny";
        }

    }




    return navazujiciSpoje;

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
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku L je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("d",element.attribute("d"),"Integer"));
        polozky.push_back(inicializujPolozku("lc",element.attribute("lc"),"Integer"));
        polozky.push_back(inicializujPolozku("tl",element.attribute("tl"),"String"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));
        polozky.push_back(inicializujPolozku("kup",element.attribute("kup"),"Integer"));
        polozky.push_back(inicializujPolozku("ids",element.attribute("ids"),"Boolean"));
        polozky.push_back(inicializujPolozku("noc",element.attribute("noc"),"Boolean"));
        polozky.push_back(inicializujPolozku("aois",element.attribute("aois"),"String"));
        polozky.push_back(inicializujPolozku("a",element.attribute("a"),"String"));
        QString queryString=this->slozInsert("l",polozky);
        qDebug()<<"l2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    emit odesliChybovouHlasku("dokoncen import L");
    qDebug()<<"konecImportuL";
    return 1;
}

int XmlRopidParser::vlozD(QDomElement koren)
{
    qDebug()<<"zacatekImportuD";
    QDomNodeList m=koren.elementsByTagName("d");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku D je "<<pocetPrvku;

    for (int i=0;i<pocetPrvku;i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
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
    emit odesliChybovouHlasku("dokoncen import D");
    return 1;
}


int XmlRopidParser::vlozP(QDomElement koren)
{
    qDebug()<<"vlozP";
    qDebug()<<"zacatekImportuP";
    QDomNodeList m=koren.elementsByTagName("p");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku P je "<<pocetPrvku;

    for (int i=0;i<pocetPrvku;i++)
    {
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
    emit odesliChybovouHlasku("dokoncen import P");
    qDebug()<<"konecImportuP";
    return 1;
}

int XmlRopidParser::vlozM(QDomElement koren)
{
    qDebug()<<"zacatekImportuM";
    // emit odesliChybovouHlasku("");
    QDomNodeList m=koren.elementsByTagName("m");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku M je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        QDomElement element = m.at(i).toElement();
        QVector<navrat> polozky;
        polozky.push_back(inicializujPolozku("c",element.attribute("c"),"Integer"));
        polozky.push_back(inicializujPolozku("n",element.attribute("n"),"String"));

        QString queryString=this->slozInsert("m",polozky);
        qDebug()<<"m2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    emit odesliChybovouHlasku("dokoncen import M");
    qDebug()<<"konecImportuM";
    return 1;
}


int XmlRopidParser::vlozZ(QDomElement koren)
{
    qDebug()<<"zacatekImportuZ";
    QDomNodeList m=koren.elementsByTagName("z");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku Z je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        qDebug()<<m.at(i).toElement().attribute("n");
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
    emit odesliChybovouHlasku("dokoncen import Z");
    qDebug()<<"konecImportuZ";
    return 1;
}

int XmlRopidParser::vlozS(QDomElement koren)
{
    qDebug()<<"zacatekImportuS";
    QDomNodeList m=koren.elementsByTagName("s");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku S je "<<pocetPrvku;





    for (int i=0;i<pocetPrvku;i++)
    {
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
        polozky.push_back(inicializujPolozku("ns",element.attribute("ns"),"Integer"));



        QString queryString=this->slozInsert("s",polozky);
        //qDebug()<<"s2 "<<queryString;

        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
        vlozX(m.at(i).toElement());
    }
    emit odesliChybovouHlasku("dokoncen import S");

    qDebug()<<"konecImportuS";
    return 1;
}



int XmlRopidParser::vlozT(QDomElement koren)
{
    qDebug()<<"zacatekImportuT";
    QDomNodeList m=koren.elementsByTagName("t");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku T je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {

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
        polozky.push_back(inicializujPolozku("hl",element.attribute("hl"),"String"));



        QString queryString=this->slozInsert("t",polozky);
        // qDebug()<<"t2 "<<queryString;
        QSqlQuery query(queryString,ropidSQL.mojeDatabaze);
    }
    emit odesliChybovouHlasku("dokoncen import T");
    qDebug()<<"konecImportuT";

    return 1;
}

int XmlRopidParser::vlozX(QDomElement koren)
{
    qDebug()<<"zacatekImportuX";
    QDomNodeList m=koren.elementsByTagName("x");
    int pocetPrvku=m.count();
    qDebug()<<"pocet prvku X je "<<pocetPrvku;
    for (int i=0;i<pocetPrvku;i++)
    {
        QDomElement prvek=m.at(i).toElement();
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
        polozky.push_back(inicializujPolozku("xorder",QString::number(i),"Integer"));
        polozky.push_back(inicializujPolozku("zsol",element.attribute("zsol"),"Boolean"));
        //polozky.push_back(inicializujPolozku("AA","BB","String"));



        QString queryString=this->slozInsert("x",polozky);
        //qDebug()<<"x2 "<<queryString;
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
    ropidSQL.Pripoj();
    truncateTable("`t`");
    truncateTable("`x`");
    truncateTable("`s`");
    truncateTable("`l`");
    truncateTable("`z`");
    truncateTable("`m`");
    truncateTable("`o`");
    truncateTable("`p`");
    truncateTable("`d`");
    truncateTable("`sp_po`");
    truncateTable("`tv`");
    truncateTable("`dd`");
    truncateTable("`hlavicka`");
    emit odesliChybovouHlasku("databaze vymazana");
    //truncateTable("");
    ropidSQL.zavriDB();
    return 1;


}

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




