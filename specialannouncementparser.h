#ifndef SPECIALANNOUNCEMENTPARSER_H
#define SPECIALANNOUNCEMENTPARSER_H

#include <QObject>
#include <QtXml>
#include <VDV301publisher/VDV301DataStructures/additionalannoucement.h>

class SpecialAnnouncementParser: public QObject
{
     Q_OBJECT


public:
     SpecialAnnouncementParser(QString appPath);
    void openFile();

     void createDefaultFile();
    QVector<AdditionalAnnoucement> announcementList;
    int loadSpecialAnnouncementList(QDomDocument xmlko);


    int trvaniZobrazeniPasma=10000;
    int intervalStahovaniPrestupu=20000;
    int intervalAfterStopToBetweenStop=20000;
    int trvaniZobrazeniOznameni=10000;
signals:
    void signalError(QString errorText);

private:
    QString cesta="";
    QString hlaseniDefaultniCesta="/hlaseni";

    bool fileExists(QString path);

};

#endif // SPECIALANNOUNCEMENTPARSER_H
