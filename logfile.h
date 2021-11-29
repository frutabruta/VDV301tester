#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QFile>

class Logfile : public QObject
{
    Q_OBJECT
public:
    //Logfile();
    void otevriSoubor();
    QString cesta;
    Logfile(QString cestaProgramu);
    void novySoubor(QFile &soubor);
    bool souborExistuje(QString path);
    bool pridejNaKonecSouboru(QFile &soubor, QString vstup);
    void nastavCestuSouboru(QFile &soubor, QString cesta, QString nazevSouboru);
    void defaultniLog(QFile &soubor);
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);

};

#endif // LOGFILE_H
