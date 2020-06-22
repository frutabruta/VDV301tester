#ifndef BLABLA_H
#define BLABLA_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class blabla : public QMainWindow
{
    Q_OBJECT
public:
    explicit blabla(QWidget *parent = nullptr);
    int cislo;
    int pocetZastavek;
    int aktlinka;
    int aktspoj;
    int cisloVozu;
    int otevreneDvere;
    int vystupniStrana;


signals:

public slots:
};

#endif // BLABLA_H
