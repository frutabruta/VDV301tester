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

    QByteArray devStatus();
    QByteArray createTimestamp();
    QByteArray AllData2(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, bool poslatHlavicku);
    QByteArray AllDataRopid(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, bool poslatHlavicku);
signals:

public slots:
};

#endif // XMLGENERATOR_H
