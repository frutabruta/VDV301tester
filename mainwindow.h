#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "blabla.h"
#include "sqlprace.h"
#include "httpserver/myhttpserver.h"
#include "xmlgenerator.h"


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int vytvor();
    blabla novatrida;
    SQLprace mojesql;
    int cisloPortu=12;
    myHTTPserver HHserver(int cisloPortu);
    xmlGenerator TestXmlGenerator;

private slots:




    void on_prikaztlacitko_clicked();



    void on_sipkaNahoru_clicked();

    void on_sipkaDolu_clicked();

    void on_ubratTlacitko_clicked();

    void on_pripojeniTlacitko_clicked();

    void on_pridatTlacitko_clicked();

    void on_quitTlacitko_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
