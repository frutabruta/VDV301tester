#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>

class Logfile : public QObject
{
    Q_OBJECT
public:
    //Logfile();
    void otevriSoubor();
    QString cesta;
    Logfile(QString cestaProgramu);
    void novySoubor();
    bool souborExistuje(QString path);
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);

};

#endif // LOGFILE_H
