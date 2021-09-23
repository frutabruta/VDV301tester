#ifndef KONFIGURACE_H
#define KONFIGURACE_H

#include <QObject>
#include <QtXml>

class Konfigurace: public QObject
{
     Q_OBJECT
public:
    Konfigurace(QString cestaProgramu);
    void otevriSoubor();

    void vytvorDefaultniKonfiguraci();
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);

private:
    QString cesta="";
    QString hlaseniDefaultniCesta="/hlaseni";
    bool souborExistuje(QString path);
    QString najdiCestaHlaseni(QDomDocument xmlko);
};

#endif // KONFIGURACE_H
