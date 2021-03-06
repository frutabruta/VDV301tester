#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QObject>
#include "VDV301_Display/seznamzastavek.h"
#include <QCoreApplication>
#include <QDomDocument>

class xmlGenerator : public QMainWindow
{
    Q_OBJECT
public:
    explicit xmlGenerator(QWidget *parent = nullptr);

    QString devStatus();
    QString createTimestamp();
    QString AllData2(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
    QString AllDataRopid(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
    QString CurrentDisplayContent1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
signals:

public slots:
};

#endif // XMLGENERATOR_H
