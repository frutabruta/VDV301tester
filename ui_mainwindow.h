/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *bocniMenu;
    QPushButton *tlacitkoLinkospoj;
    QPushButton *tlacitkoZpetVydej;
    QPushButton *tlacitkoNastaveni;
    QPushButton *tlacitkoManual;
    QPushButton *tlacitkoNavic;
    QPushButton *quitTlacitko;
    QStackedWidget *prepinadloStran;
    QWidget *page_vydej;
    QGridLayout *gridLayout_3;
    QHBoxLayout *displej_hor_layout;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *Akt_Hor_Layout;
    QLabel *labelAktZastJmeno;
    QLabel *labelAktZastCas;
    QHBoxLayout *pristiHorLAyout;
    QLabel *prikazovyvysledek;
    QLabel *prikazovyvysledek_cas;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *popisek;
    QVBoxLayout *verticalLayout;
    QPushButton *pridatTlacitko;
    QPushButton *ubratTlacitko;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QPushButton *tlacitkoIBIS;
    QVBoxLayout *verticalLayout_4;
    QPushButton *sipkaNahoru;
    QPushButton *sipkaDolu;
    QVBoxLayout *verticalLayout_5;
    QPushButton *BeforeStop;
    QPushButton *AtStop_2;
    QPushButton *AfterStop;
    QPushButton *BetweenStop;
    QLabel *locationStateIndicator;
    QWidget *page_linkaspoj;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *polelinky;
    QLineEdit *polespoje;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QListWidget *listLinek;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QListWidget *listSpoje;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *prikaztlacitko;
    QWidget *page_nastaveni;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayoutSQLPeace;
    QLabel *label_5;
    QPushButton *tlacitkoSQL;
    QLabel *label_4;
    QLineEdit *lineEditSqlServer;
    QVBoxLayout *verticalLayoutvstupniData;
    QLabel *label_6;
    QPushButton *tlacitkoNactiXMLropid;
    QPushButton *tlacitkoUlozDoSQL;
    QPushButton *tlacitkoTruncate;
    QVBoxLayout *verticalLayoutseriovyPort;
    QLabel *label_7;
    QLineEdit *lineEdit_jmenoPortu;
    QPushButton *tlacitkoNastavPort;
    QPushButton *tlacitkoOdesliPrikaz;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *NazevVysledku;
    QPushButton *pripojeniTlacitko;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_14;
    QLabel *hlaseniLabel;
    QPushButton *tlacitkoHlaseniSlozka;
    QLineEdit *lineEditHlaseniCesta;
    QLabel *label_12;
    QLabel *label_build;
    QLabel *label_diagnostika_sql;
    QWidget *page_customXML;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QPlainTextEdit *plainTextEditCustomXml;
    QPushButton *tlacitkoSmazOkno;
    QPushButton *tlacitkoOdesliXml;
    QWidget *verticalLayoutWidget_10;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_11;
    QTableWidget *seznamOdberatelu;
    QLabel *label_15;
    QTableWidget *seznamOdberatelu2;
    QLineEdit *lineEdit_ipadresaOdberatele;
    QLineEdit *lineEdit_strukturaOdberu;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_13;
    QPushButton *tlacitkoAddsubscriber;
    QPushButton *tlacitkoRemoveSubscriber;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_14;
    QPushButton *tlacitkoAddsubscriber_2;
    QPushButton *tlacitkoRemoveSubscriber_2;
    QLabel *label_diagnostika_manual;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 480));
        MainWindow->setMaximumSize(QSize(800, 480));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_9->setContentsMargins(0, -1, -1, -1);
        bocniMenu = new QVBoxLayout();
        bocniMenu->setSpacing(6);
        bocniMenu->setObjectName(QString::fromUtf8("bocniMenu"));
        tlacitkoLinkospoj = new QPushButton(centralWidget);
        tlacitkoLinkospoj->setObjectName(QString::fromUtf8("tlacitkoLinkospoj"));
        tlacitkoLinkospoj->setMinimumSize(QSize(0, 80));
        tlacitkoLinkospoj->setMaximumSize(QSize(200, 200));
        QFont font;
        font.setPointSize(15);
        tlacitkoLinkospoj->setFont(font);
        tlacitkoLinkospoj->setCheckable(true);
        tlacitkoLinkospoj->setChecked(true);
        tlacitkoLinkospoj->setAutoExclusive(true);

        bocniMenu->addWidget(tlacitkoLinkospoj);

        tlacitkoZpetVydej = new QPushButton(centralWidget);
        tlacitkoZpetVydej->setObjectName(QString::fromUtf8("tlacitkoZpetVydej"));
        tlacitkoZpetVydej->setMinimumSize(QSize(0, 80));
        tlacitkoZpetVydej->setMaximumSize(QSize(200, 200));
        tlacitkoZpetVydej->setFont(font);
        tlacitkoZpetVydej->setCheckable(true);
        tlacitkoZpetVydej->setAutoExclusive(true);

        bocniMenu->addWidget(tlacitkoZpetVydej);

        tlacitkoNastaveni = new QPushButton(centralWidget);
        tlacitkoNastaveni->setObjectName(QString::fromUtf8("tlacitkoNastaveni"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tlacitkoNastaveni->sizePolicy().hasHeightForWidth());
        tlacitkoNastaveni->setSizePolicy(sizePolicy2);
        tlacitkoNastaveni->setMinimumSize(QSize(0, 80));
        tlacitkoNastaveni->setMaximumSize(QSize(200, 200));
        tlacitkoNastaveni->setFont(font);
        tlacitkoNastaveni->setCheckable(true);
        tlacitkoNastaveni->setAutoExclusive(true);

        bocniMenu->addWidget(tlacitkoNastaveni);

        tlacitkoManual = new QPushButton(centralWidget);
        tlacitkoManual->setObjectName(QString::fromUtf8("tlacitkoManual"));
        tlacitkoManual->setMinimumSize(QSize(0, 80));
        tlacitkoManual->setMaximumSize(QSize(200, 200));
        tlacitkoManual->setFont(font);
        tlacitkoManual->setCheckable(true);
        tlacitkoManual->setAutoExclusive(true);

        bocniMenu->addWidget(tlacitkoManual);

        tlacitkoNavic = new QPushButton(centralWidget);
        tlacitkoNavic->setObjectName(QString::fromUtf8("tlacitkoNavic"));
        tlacitkoNavic->setMinimumSize(QSize(0, 80));
        tlacitkoNavic->setMaximumSize(QSize(200, 200));
        tlacitkoNavic->setFont(font);
        tlacitkoNavic->setCheckable(true);
        tlacitkoNavic->setAutoExclusive(false);

        bocniMenu->addWidget(tlacitkoNavic);

        quitTlacitko = new QPushButton(centralWidget);
        quitTlacitko->setObjectName(QString::fromUtf8("quitTlacitko"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(quitTlacitko->sizePolicy().hasHeightForWidth());
        quitTlacitko->setSizePolicy(sizePolicy3);
        quitTlacitko->setMaximumSize(QSize(200, 200));
        QPalette palette;
        quitTlacitko->setPalette(palette);
        quitTlacitko->setFont(font);

        bocniMenu->addWidget(quitTlacitko);


        horizontalLayout_9->addLayout(bocniMenu);

        prepinadloStran = new QStackedWidget(centralWidget);
        prepinadloStran->setObjectName(QString::fromUtf8("prepinadloStran"));
        prepinadloStran->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(prepinadloStran->sizePolicy().hasHeightForWidth());
        prepinadloStran->setSizePolicy(sizePolicy4);
        prepinadloStran->setMinimumSize(QSize(150, 0));
        QPalette palette1;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(52, 101, 164, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 127, 191, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(106, 106, 159, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(42, 42, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(56, 56, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        QBrush brush9(QColor(255, 255, 255, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        QBrush brush10(QColor(85, 85, 127, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        QBrush brush11(QColor(255, 255, 255, 128));
        brush11.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        prepinadloStran->setPalette(palette1);
        prepinadloStran->setStyleSheet(QString::fromUtf8("/*background-color:rgb(52, 101, 164); */"));
        page_vydej = new QWidget();
        page_vydej->setObjectName(QString::fromUtf8("page_vydej"));
        gridLayout_3 = new QGridLayout(page_vydej);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        displej_hor_layout = new QHBoxLayout();
        displej_hor_layout->setSpacing(6);
        displej_hor_layout->setObjectName(QString::fromUtf8("displej_hor_layout"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        Akt_Hor_Layout = new QHBoxLayout();
        Akt_Hor_Layout->setSpacing(6);
        Akt_Hor_Layout->setObjectName(QString::fromUtf8("Akt_Hor_Layout"));
        labelAktZastJmeno = new QLabel(page_vydej);
        labelAktZastJmeno->setObjectName(QString::fromUtf8("labelAktZastJmeno"));
        labelAktZastJmeno->setMinimumSize(QSize(350, 0));
        QFont font1;
        font1.setPointSize(30);
        labelAktZastJmeno->setFont(font1);

        Akt_Hor_Layout->addWidget(labelAktZastJmeno);

        labelAktZastCas = new QLabel(page_vydej);
        labelAktZastCas->setObjectName(QString::fromUtf8("labelAktZastCas"));
        labelAktZastCas->setFont(font1);

        Akt_Hor_Layout->addWidget(labelAktZastCas);


        verticalLayout_13->addLayout(Akt_Hor_Layout);

        pristiHorLAyout = new QHBoxLayout();
        pristiHorLAyout->setSpacing(6);
        pristiHorLAyout->setObjectName(QString::fromUtf8("pristiHorLAyout"));
        prikazovyvysledek = new QLabel(page_vydej);
        prikazovyvysledek->setObjectName(QString::fromUtf8("prikazovyvysledek"));
        sizePolicy1.setHeightForWidth(prikazovyvysledek->sizePolicy().hasHeightForWidth());
        prikazovyvysledek->setSizePolicy(sizePolicy1);
        prikazovyvysledek->setMinimumSize(QSize(350, 270));
        prikazovyvysledek->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setPointSize(20);
        prikazovyvysledek->setFont(font2);
        prikazovyvysledek->setAutoFillBackground(false);
        prikazovyvysledek->setStyleSheet(QString::fromUtf8("background-color:rgb(32, 74, 135);\n"
"color: rgb(238, 238, 236);"));
        prikazovyvysledek->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        pristiHorLAyout->addWidget(prikazovyvysledek);

        prikazovyvysledek_cas = new QLabel(page_vydej);
        prikazovyvysledek_cas->setObjectName(QString::fromUtf8("prikazovyvysledek_cas"));
        prikazovyvysledek_cas->setMinimumSize(QSize(112, 270));
        prikazovyvysledek_cas->setFont(font2);
        prikazovyvysledek_cas->setAutoFillBackground(false);
        prikazovyvysledek_cas->setStyleSheet(QString::fromUtf8("background-color:rgb(32, 74, 135);\n"
"color: rgb(238, 238, 236);"));
        prikazovyvysledek_cas->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        pristiHorLAyout->addWidget(prikazovyvysledek_cas);


        verticalLayout_13->addLayout(pristiHorLAyout);


        displej_hor_layout->addLayout(verticalLayout_13);


        gridLayout_3->addLayout(displej_hor_layout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        popisek = new QLabel(page_vydej);
        popisek->setObjectName(QString::fromUtf8("popisek"));
        QFont font3;
        font3.setPointSize(24);
        popisek->setFont(font3);
        popisek->setTextFormat(Qt::PlainText);
        popisek->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(popisek);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        pridatTlacitko = new QPushButton(page_vydej);
        pridatTlacitko->setObjectName(QString::fromUtf8("pridatTlacitko"));
        pridatTlacitko->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pridatTlacitko->sizePolicy().hasHeightForWidth());
        pridatTlacitko->setSizePolicy(sizePolicy5);
        QFont font4;
        font4.setPointSize(14);
        pridatTlacitko->setFont(font4);

        verticalLayout->addWidget(pridatTlacitko);

        ubratTlacitko = new QPushButton(page_vydej);
        ubratTlacitko->setObjectName(QString::fromUtf8("ubratTlacitko"));
        sizePolicy5.setHeightForWidth(ubratTlacitko->sizePolicy().hasHeightForWidth());
        ubratTlacitko->setSizePolicy(sizePolicy5);
        ubratTlacitko->setFont(font4);

        verticalLayout->addWidget(ubratTlacitko);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        radioButton = new QRadioButton(page_vydej);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_6->addWidget(radioButton);

        radioButton_2 = new QRadioButton(page_vydej);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_6->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(page_vydej);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_6->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(page_vydej);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_6->addWidget(radioButton_4);


        horizontalLayout->addLayout(verticalLayout_6);


        horizontalLayout_3->addLayout(horizontalLayout);

        tlacitkoIBIS = new QPushButton(page_vydej);
        tlacitkoIBIS->setObjectName(QString::fromUtf8("tlacitkoIBIS"));

        horizontalLayout_3->addWidget(tlacitkoIBIS);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        sipkaNahoru = new QPushButton(page_vydej);
        sipkaNahoru->setObjectName(QString::fromUtf8("sipkaNahoru"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(sipkaNahoru->sizePolicy().hasHeightForWidth());
        sipkaNahoru->setSizePolicy(sizePolicy6);

        verticalLayout_4->addWidget(sipkaNahoru);

        sipkaDolu = new QPushButton(page_vydej);
        sipkaDolu->setObjectName(QString::fromUtf8("sipkaDolu"));
        sizePolicy5.setHeightForWidth(sipkaDolu->sizePolicy().hasHeightForWidth());
        sipkaDolu->setSizePolicy(sizePolicy5);

        verticalLayout_4->addWidget(sipkaDolu);


        gridLayout_3->addLayout(verticalLayout_4, 0, 4, 2, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetNoConstraint);
        BeforeStop = new QPushButton(page_vydej);
        BeforeStop->setObjectName(QString::fromUtf8("BeforeStop"));
        sizePolicy5.setHeightForWidth(BeforeStop->sizePolicy().hasHeightForWidth());
        BeforeStop->setSizePolicy(sizePolicy5);
        BeforeStop->setFont(font2);
        BeforeStop->setCheckable(true);
        BeforeStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(BeforeStop);

        AtStop_2 = new QPushButton(page_vydej);
        AtStop_2->setObjectName(QString::fromUtf8("AtStop_2"));
        sizePolicy5.setHeightForWidth(AtStop_2->sizePolicy().hasHeightForWidth());
        AtStop_2->setSizePolicy(sizePolicy5);
        AtStop_2->setFont(font2);
        AtStop_2->setCheckable(true);
        AtStop_2->setChecked(true);
        AtStop_2->setAutoExclusive(true);

        verticalLayout_5->addWidget(AtStop_2);

        AfterStop = new QPushButton(page_vydej);
        AfterStop->setObjectName(QString::fromUtf8("AfterStop"));
        sizePolicy5.setHeightForWidth(AfterStop->sizePolicy().hasHeightForWidth());
        AfterStop->setSizePolicy(sizePolicy5);
        AfterStop->setFont(font2);
        AfterStop->setCheckable(true);
        AfterStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(AfterStop);

        BetweenStop = new QPushButton(page_vydej);
        BetweenStop->setObjectName(QString::fromUtf8("BetweenStop"));
        sizePolicy5.setHeightForWidth(BetweenStop->sizePolicy().hasHeightForWidth());
        BetweenStop->setSizePolicy(sizePolicy5);
        QFont font5;
        font5.setPointSize(18);
        BetweenStop->setFont(font5);
        BetweenStop->setCheckable(true);
        BetweenStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(BetweenStop);

        locationStateIndicator = new QLabel(page_vydej);
        locationStateIndicator->setObjectName(QString::fromUtf8("locationStateIndicator"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(locationStateIndicator->sizePolicy().hasHeightForWidth());
        locationStateIndicator->setSizePolicy(sizePolicy7);

        verticalLayout_5->addWidget(locationStateIndicator);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 2, 1);

        prepinadloStran->addWidget(page_vydej);
        page_linkaspoj = new QWidget();
        page_linkaspoj->setObjectName(QString::fromUtf8("page_linkaspoj"));
        gridLayout_2 = new QGridLayout(page_linkaspoj);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_3->addLayout(horizontalLayout_2);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(page_linkaspoj);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        polelinky = new QLineEdit(page_linkaspoj);
        polelinky->setObjectName(QString::fromUtf8("polelinky"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush12(QColor(127, 127, 127, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush12);
        QBrush brush13(QColor(170, 170, 170, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush14(QColor(0, 0, 0, 128));
        brush14.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush14);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        QBrush brush15(QColor(0, 0, 0, 128));
        brush15.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush15);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        QBrush brush16(QColor(0, 0, 0, 128));
        brush16.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush16);
#endif
        polelinky->setPalette(palette2);
        polelinky->setFont(font2);
        polelinky->setAutoFillBackground(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, polelinky);

        polespoje = new QLineEdit(page_linkaspoj);
        polespoje->setObjectName(QString::fromUtf8("polespoje"));
        polespoje->setFont(font2);

        formLayout->setWidget(1, QFormLayout::FieldRole, polespoje);

        label_2 = new QLabel(page_linkaspoj);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);


        verticalLayout_3->addLayout(formLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        verticalLayout_3->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_8 = new QLabel(page_linkaspoj);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        verticalLayout_8->addWidget(label_8);

        listLinek = new QListWidget(page_linkaspoj);
        listLinek->setObjectName(QString::fromUtf8("listLinek"));
        listLinek->setFont(font);

        verticalLayout_8->addWidget(listLinek);


        horizontalLayout_7->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_9 = new QLabel(page_linkaspoj);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        verticalLayout_9->addWidget(label_9);

        listSpoje = new QListWidget(page_linkaspoj);
        listSpoje->setObjectName(QString::fromUtf8("listSpoje"));
        listSpoje->setFont(font);

        verticalLayout_9->addWidget(listSpoje);


        horizontalLayout_7->addLayout(verticalLayout_9);


        gridLayout_2->addLayout(horizontalLayout_7, 0, 2, 4, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        checkBox = new QCheckBox(page_linkaspoj);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_7->addWidget(checkBox);

        checkBox_2 = new QCheckBox(page_linkaspoj);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_7->addWidget(checkBox_2);


        gridLayout_2->addLayout(verticalLayout_7, 1, 0, 1, 2);

        prikaztlacitko = new QPushButton(page_linkaspoj);
        prikaztlacitko->setObjectName(QString::fromUtf8("prikaztlacitko"));
        sizePolicy6.setHeightForWidth(prikaztlacitko->sizePolicy().hasHeightForWidth());
        prikaztlacitko->setSizePolicy(sizePolicy6);
        prikaztlacitko->setFont(font2);

        gridLayout_2->addWidget(prikaztlacitko, 2, 0, 1, 1);

        prepinadloStran->addWidget(page_linkaspoj);
        page_nastaveni = new QWidget();
        page_nastaveni->setObjectName(QString::fromUtf8("page_nastaveni"));
        horizontalLayoutWidget_3 = new QWidget(page_nastaveni);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(100, 0, 523, 305));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayoutSQLPeace = new QVBoxLayout();
        verticalLayoutSQLPeace->setSpacing(6);
        verticalLayoutSQLPeace->setObjectName(QString::fromUtf8("verticalLayoutSQLPeace"));
        label_5 = new QLabel(horizontalLayoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);

        verticalLayoutSQLPeace->addWidget(label_5);

        tlacitkoSQL = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoSQL->setObjectName(QString::fromUtf8("tlacitkoSQL"));
        tlacitkoSQL->setMinimumSize(QSize(0, 80));

        verticalLayoutSQLPeace->addWidget(tlacitkoSQL);

        label_4 = new QLabel(horizontalLayoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayoutSQLPeace->addWidget(label_4);

        lineEditSqlServer = new QLineEdit(horizontalLayoutWidget_3);
        lineEditSqlServer->setObjectName(QString::fromUtf8("lineEditSqlServer"));

        verticalLayoutSQLPeace->addWidget(lineEditSqlServer);


        horizontalLayout_6->addLayout(verticalLayoutSQLPeace);

        verticalLayoutvstupniData = new QVBoxLayout();
        verticalLayoutvstupniData->setSpacing(6);
        verticalLayoutvstupniData->setObjectName(QString::fromUtf8("verticalLayoutvstupniData"));
        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);

        verticalLayoutvstupniData->addWidget(label_6);

        tlacitkoNactiXMLropid = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoNactiXMLropid->setObjectName(QString::fromUtf8("tlacitkoNactiXMLropid"));
        tlacitkoNactiXMLropid->setMinimumSize(QSize(0, 80));

        verticalLayoutvstupniData->addWidget(tlacitkoNactiXMLropid);

        tlacitkoUlozDoSQL = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoUlozDoSQL->setObjectName(QString::fromUtf8("tlacitkoUlozDoSQL"));
        tlacitkoUlozDoSQL->setMinimumSize(QSize(0, 80));

        verticalLayoutvstupniData->addWidget(tlacitkoUlozDoSQL);

        tlacitkoTruncate = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoTruncate->setObjectName(QString::fromUtf8("tlacitkoTruncate"));
        tlacitkoTruncate->setMinimumSize(QSize(0, 80));

        verticalLayoutvstupniData->addWidget(tlacitkoTruncate);


        horizontalLayout_6->addLayout(verticalLayoutvstupniData);

        verticalLayoutseriovyPort = new QVBoxLayout();
        verticalLayoutseriovyPort->setSpacing(6);
        verticalLayoutseriovyPort->setObjectName(QString::fromUtf8("verticalLayoutseriovyPort"));
        label_7 = new QLabel(horizontalLayoutWidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);

        verticalLayoutseriovyPort->addWidget(label_7);

        lineEdit_jmenoPortu = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_jmenoPortu->setObjectName(QString::fromUtf8("lineEdit_jmenoPortu"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        lineEdit_jmenoPortu->setPalette(palette3);

        verticalLayoutseriovyPort->addWidget(lineEdit_jmenoPortu);

        tlacitkoNastavPort = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoNastavPort->setObjectName(QString::fromUtf8("tlacitkoNastavPort"));
        tlacitkoNastavPort->setMinimumSize(QSize(0, 80));

        verticalLayoutseriovyPort->addWidget(tlacitkoNastavPort);

        tlacitkoOdesliPrikaz = new QPushButton(horizontalLayoutWidget_3);
        tlacitkoOdesliPrikaz->setObjectName(QString::fromUtf8("tlacitkoOdesliPrikaz"));
        tlacitkoOdesliPrikaz->setMinimumSize(QSize(0, 80));

        verticalLayoutseriovyPort->addWidget(tlacitkoOdesliPrikaz);


        horizontalLayout_6->addLayout(verticalLayoutseriovyPort);

        layoutWidget_2 = new QWidget(page_nastaveni);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(590, 130, 133, 119));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 20, 0);
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        NazevVysledku = new QLabel(layoutWidget_2);
        NazevVysledku->setObjectName(QString::fromUtf8("NazevVysledku"));

        verticalLayout_2->addWidget(NazevVysledku);

        pripojeniTlacitko = new QPushButton(layoutWidget_2);
        pripojeniTlacitko->setObjectName(QString::fromUtf8("pripojeniTlacitko"));
        sizePolicy5.setHeightForWidth(pripojeniTlacitko->sizePolicy().hasHeightForWidth());
        pripojeniTlacitko->setSizePolicy(sizePolicy5);

        verticalLayout_2->addWidget(pripojeniTlacitko);

        verticalLayoutWidget_2 = new QWidget(page_nastaveni);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(90, 320, 160, 77));
        verticalLayout_14 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        hlaseniLabel = new QLabel(verticalLayoutWidget_2);
        hlaseniLabel->setObjectName(QString::fromUtf8("hlaseniLabel"));

        verticalLayout_14->addWidget(hlaseniLabel);

        tlacitkoHlaseniSlozka = new QPushButton(verticalLayoutWidget_2);
        tlacitkoHlaseniSlozka->setObjectName(QString::fromUtf8("tlacitkoHlaseniSlozka"));

        verticalLayout_14->addWidget(tlacitkoHlaseniSlozka);

        lineEditHlaseniCesta = new QLineEdit(verticalLayoutWidget_2);
        lineEditHlaseniCesta->setObjectName(QString::fromUtf8("lineEditHlaseniCesta"));

        verticalLayout_14->addWidget(lineEditHlaseniCesta);

        label_12 = new QLabel(page_nastaveni);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(360, 340, 47, 13));
        label_build = new QLabel(page_nastaveni);
        label_build->setObjectName(QString::fromUtf8("label_build"));
        label_build->setGeometry(QRect(450, 340, 151, 16));
        label_diagnostika_sql = new QLabel(page_nastaveni);
        label_diagnostika_sql->setObjectName(QString::fromUtf8("label_diagnostika_sql"));
        label_diagnostika_sql->setGeometry(QRect(30, 300, 631, 16));
        prepinadloStran->addWidget(page_nastaveni);
        page_customXML = new QWidget();
        page_customXML->setObjectName(QString::fromUtf8("page_customXML"));
        verticalLayoutWidget_9 = new QWidget(page_customXML);
        verticalLayoutWidget_9->setObjectName(QString::fromUtf8("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(380, 20, 301, 371));
        verticalLayout_10 = new QVBoxLayout(verticalLayoutWidget_9);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(verticalLayoutWidget_9);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_10->addWidget(label_10);

        plainTextEditCustomXml = new QPlainTextEdit(verticalLayoutWidget_9);
        plainTextEditCustomXml->setObjectName(QString::fromUtf8("plainTextEditCustomXml"));

        verticalLayout_10->addWidget(plainTextEditCustomXml);

        tlacitkoSmazOkno = new QPushButton(page_customXML);
        tlacitkoSmazOkno->setObjectName(QString::fromUtf8("tlacitkoSmazOkno"));
        tlacitkoSmazOkno->setGeometry(QRect(210, 310, 151, 31));
        tlacitkoOdesliXml = new QPushButton(page_customXML);
        tlacitkoOdesliXml->setObjectName(QString::fromUtf8("tlacitkoOdesliXml"));
        tlacitkoOdesliXml->setGeometry(QRect(190, 360, 181, 31));
        verticalLayoutWidget_10 = new QWidget(page_customXML);
        verticalLayoutWidget_10->setObjectName(QString::fromUtf8("verticalLayoutWidget_10"));
        verticalLayoutWidget_10->setGeometry(QRect(20, 20, 351, 231));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_10);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(verticalLayoutWidget_10);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_11->addWidget(label_11);

        seznamOdberatelu = new QTableWidget(verticalLayoutWidget_10);
        if (seznamOdberatelu->columnCount() < 3)
            seznamOdberatelu->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        seznamOdberatelu->setObjectName(QString::fromUtf8("seznamOdberatelu"));

        verticalLayout_11->addWidget(seznamOdberatelu);

        label_15 = new QLabel(verticalLayoutWidget_10);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout_11->addWidget(label_15);

        seznamOdberatelu2 = new QTableWidget(verticalLayoutWidget_10);
        if (seznamOdberatelu2->columnCount() < 3)
            seznamOdberatelu2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        seznamOdberatelu2->setObjectName(QString::fromUtf8("seznamOdberatelu2"));

        verticalLayout_11->addWidget(seznamOdberatelu2);

        lineEdit_ipadresaOdberatele = new QLineEdit(page_customXML);
        lineEdit_ipadresaOdberatele->setObjectName(QString::fromUtf8("lineEdit_ipadresaOdberatele"));
        lineEdit_ipadresaOdberatele->setGeometry(QRect(30, 270, 201, 20));
        lineEdit_strukturaOdberu = new QLineEdit(page_customXML);
        lineEdit_strukturaOdberu->setObjectName(QString::fromUtf8("lineEdit_strukturaOdberu"));
        lineEdit_strukturaOdberu->setGeometry(QRect(240, 270, 113, 20));
        horizontalLayoutWidget = new QWidget(page_customXML);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 310, 194, 80));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        verticalLayout_12->addWidget(label_13);

        tlacitkoAddsubscriber = new QPushButton(horizontalLayoutWidget);
        tlacitkoAddsubscriber->setObjectName(QString::fromUtf8("tlacitkoAddsubscriber"));

        verticalLayout_12->addWidget(tlacitkoAddsubscriber);

        tlacitkoRemoveSubscriber = new QPushButton(horizontalLayoutWidget);
        tlacitkoRemoveSubscriber->setObjectName(QString::fromUtf8("tlacitkoRemoveSubscriber"));

        verticalLayout_12->addWidget(tlacitkoRemoveSubscriber);


        horizontalLayout_5->addLayout(verticalLayout_12);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_14 = new QLabel(horizontalLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_15->addWidget(label_14);

        tlacitkoAddsubscriber_2 = new QPushButton(horizontalLayoutWidget);
        tlacitkoAddsubscriber_2->setObjectName(QString::fromUtf8("tlacitkoAddsubscriber_2"));

        verticalLayout_15->addWidget(tlacitkoAddsubscriber_2);

        tlacitkoRemoveSubscriber_2 = new QPushButton(horizontalLayoutWidget);
        tlacitkoRemoveSubscriber_2->setObjectName(QString::fromUtf8("tlacitkoRemoveSubscriber_2"));

        verticalLayout_15->addWidget(tlacitkoRemoveSubscriber_2);


        horizontalLayout_5->addLayout(verticalLayout_15);

        label_diagnostika_manual = new QLabel(page_customXML);
        label_diagnostika_manual->setObjectName(QString::fromUtf8("label_diagnostika_manual"));
        label_diagnostika_manual->setGeometry(QRect(20, 390, 541, 16));
        prepinadloStran->addWidget(page_customXML);

        horizontalLayout_9->addWidget(prepinadloStran);


        gridLayout->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        prepinadloStran->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tlacitkoLinkospoj->setText(QCoreApplication::translate("MainWindow", "Linka\n"
"/spoj", nullptr));
        tlacitkoZpetVydej->setText(QCoreApplication::translate("MainWindow", "V\303\275dej", nullptr));
        tlacitkoNastaveni->setText(QCoreApplication::translate("MainWindow", "Nast.", nullptr));
        tlacitkoManual->setText(QCoreApplication::translate("MainWindow", "Manual", nullptr));
        tlacitkoNavic->setText(QCoreApplication::translate("MainWindow", "Fullscr.", nullptr));
        quitTlacitko->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        labelAktZastJmeno->setText(QCoreApplication::translate("MainWindow", "AktZast", nullptr));
        labelAktZastCas->setText(QCoreApplication::translate("MainWindow", "99:99", nullptr));
        prikazovyvysledek->setText(QCoreApplication::translate("MainWindow", "seznam zastavek", nullptr));
        prikazovyvysledek_cas->setText(QCoreApplication::translate("MainWindow", "12:01", nullptr));
        popisek->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pridatTlacitko->setText(QCoreApplication::translate("MainWindow", "P\305\231idat", nullptr));
        ubratTlacitko->setText(QCoreApplication::translate("MainWindow", "Ubrat", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "DoorsOpen", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "AllDoorsClosed", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "SingleDoorOpen", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "SingleDoorClosed", nullptr));
        tlacitkoIBIS->setText(QCoreApplication::translate("MainWindow", "IBIS", nullptr));
        sipkaNahoru->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        sipkaDolu->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        BeforeStop->setText(QCoreApplication::translate("MainWindow", "Before\n"
"Stop", nullptr));
        AtStop_2->setText(QCoreApplication::translate("MainWindow", "At\n"
"Stop", nullptr));
        AfterStop->setText(QCoreApplication::translate("MainWindow", "After\n"
"Stop", nullptr));
        BetweenStop->setText(QCoreApplication::translate("MainWindow", "Between\n"
"Stop", nullptr));
        locationStateIndicator->setText(QCoreApplication::translate("MainWindow", "locationState", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Linka</span></p></body></html>", nullptr));
        polelinky->setText(QCoreApplication::translate("MainWindow", "100952", nullptr));
        polespoje->setText(QCoreApplication::translate("MainWindow", "1001", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Spoj", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Seznam linek", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Seznam spoj\305\257", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "MPV p\305\231estupy", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "StopRequested", nullptr));
        prikaztlacitko->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "SQL pr\303\241ce", nullptr));
        tlacitkoSQL->setText(QCoreApplication::translate("MainWindow", "pripojSQL", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Adresa SQL serveru", nullptr));
        lineEditSqlServer->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Vstupn\303\255 data", nullptr));
        tlacitkoNactiXMLropid->setText(QCoreApplication::translate("MainWindow", "nactiXML", nullptr));
        tlacitkoUlozDoSQL->setText(QCoreApplication::translate("MainWindow", "ulozDoSQL", nullptr));
        tlacitkoTruncate->setText(QCoreApplication::translate("MainWindow", "TRUNCATE", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "S\303\251riov\303\275 port", nullptr));
        lineEdit_jmenoPortu->setText(QCoreApplication::translate("MainWindow", "ttyUSB0", nullptr));
        tlacitkoNastavPort->setText(QCoreApplication::translate("MainWindow", "nastav \304\215\303\255slo portu", nullptr));
        tlacitkoOdesliPrikaz->setText(QCoreApplication::translate("MainWindow", "odesliPrikaz", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Stav p\305\231ipojen\303\255:", nullptr));
        NazevVysledku->setText(QCoreApplication::translate("MainWindow", "stav pripojeni", nullptr));
        pripojeniTlacitko->setText(QCoreApplication::translate("MainWindow", "SQL Connect", nullptr));
        hlaseniLabel->setText(QCoreApplication::translate("MainWindow", "Slozka hlaseni", nullptr));
        tlacitkoHlaseniSlozka->setText(QCoreApplication::translate("MainWindow", "nastav slozku", nullptr));
        lineEditHlaseniCesta->setText(QCoreApplication::translate("MainWindow", "C:/Users/adam/Desktop/HLASENI", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "build", nullptr));
        label_build->setText(QCoreApplication::translate("MainWindow", "cisloBuildu", nullptr));
        label_diagnostika_sql->setText(QCoreApplication::translate("MainWindow", "Diagnostick\303\275 \305\231\303\241dek importu dat", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "CustomXML", nullptr));
        plainTextEditCustomXml->setPlainText(QCoreApplication::translate("MainWindow", "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
"<CustomerInformationService.GetAllDataResponse>\n"
" <AllData>\n"
"  <TimeStamp>\n"
"   <Value>2021-03-07T02:51:28</Value>\n"
"  </TimeStamp>\n"
"  <VehicleRef>\n"
"   <Value>33</Value>\n"
"  </VehicleRef>\n"
"  <DefaultLanguage>\n"
"   <Value>cz</Value>\n"
"  </DefaultLanguage>\n"
"  <TripInformation>\n"
"   <TripRef>\n"
"    <Value>3</Value>\n"
"   </TripRef>\n"
"   <StopSequence>\n"
"    <StopPoint>\n"
"     <StopIndex>\n"
"      <Value>0</Value>\n"
"     </StopIndex>\n"
"     <StopRef>\n"
"      <Value>Ref:0</Value>\n"
"     </StopRef>\n"
"     <StopName>\n"
"      <Value>S\303\255dli\305\241t\304\233 Radot\303\255n</Value>\n"
"      <Language>cz</Language>\n"
"     </StopName>\n"
"     <DisplayContent>\n"
"      <DisplayContentRef>\n"
"       <Value>1234</Value>\n"
"      </DisplayContentRef>\n"
"      <LineInformation>\n"
"       <LineRef>\n"
"        <Value>100315</Value>\n"
"       </LineRef>\n"
"       <LineName>\n"
"        <Value>315</Value>\n"
"      "
                        "  <Language>cz</Language>\n"
"       </LineName>\n"
"       <LineNumber>\n"
"        <Value>100315</Value>\n"
"       </LineNumber>\n"
"      </LineInformation>\n"
"      <Destination>\n"
"       <DestinationRef>\n"
"        <Value>22</Value>\n"
"       </DestinationRef>\n"
"       <DestinationName>\n"
"        <Value>Zdick\303\241</Value>\n"
"        <Language>cz</Language>\n"
"       </DestinationName>\n"
"      </Destination>\n"
"     </DisplayContent>\n"
"    </StopPoint>\n"
"    <StopPoint>\n"
"     <StopIndex>\n"
"      <Value>1</Value>\n"
"     </StopIndex>\n"
"     <StopRef>\n"
"      <Value>Ref:1</Value>\n"
"     </StopRef>\n"
"     <StopName>\n"
"      <Value>S\303\255dli\305\241t\304\233 Radot\303\255n</Value>\n"
"      <Language>cz</Language>\n"
"     </StopName>\n"
"     <DisplayContent>\n"
"      <DisplayContentRef>\n"
"       <Value>1234</Value>\n"
"      </DisplayContentRef>\n"
"      <LineInformation>\n"
"       <LineRef>\n"
"        <Value>100315</Value>\n"
"       </LineRef>\n"
"       <Line"
                        "Name>\n"
"        <Value>315</Value>\n"
"        <Language>cz</Language>\n"
"       </LineName>\n"
"       <LineNumber>\n"
"        <Value>100315</Value>\n"
"       </LineNumber>\n"
"      </LineInformation>\n"
"      <Destination>\n"
"       <DestinationRef>\n"
"        <Value>22</Value>\n"
"       </DestinationRef>\n"
"       <DestinationName>\n"
"        <Value>Zdick\303\241</Value>\n"
"        <Language>cz</Language>\n"
"       </DestinationName>\n"
"      </Destination>\n"
"     </DisplayContent>\n"
"    </StopPoint>\n"
"    <StopPoint>\n"
"     <StopIndex>\n"
"      <Value>2</Value>\n"
"     </StopIndex>\n"
"     <StopRef>\n"
"      <Value>Ref:2</Value>\n"
"     </StopRef>\n"
"     <StopName>\n"
"      <Value>\304\214erno\305\241ice,U Vod\303\241rny</Value>\n"
"      <Language>cz</Language>\n"
"     </StopName>\n"
"     <DisplayContent>\n"
"      <DisplayContentRef>\n"
"       <Value>1234</Value>\n"
"      </DisplayContentRef>\n"
"      <LineInformation>\n"
"       <LineRef>\n"
"        <Value>100315</Va"
                        "lue>\n"
"       </LineRef>\n"
"       <LineName>\n"
"        <Value>315</Value>\n"
"        <Language>cz</Language>\n"
"       </LineName>\n"
"       <LineNumber>\n"
"        <Value>100315</Value>\n"
"       </LineNumber>\n"
"      </LineInformation>\n"
"      <Destination>\n"
"       <DestinationRef>\n"
"        <Value>22</Value>\n"
"       </DestinationRef>\n"
"       <DestinationName>\n"
"        <Value>Zdick\303\241</Value>\n"
"        <Language>cz</Language>\n"
"       </DestinationName>\n"
"      </Destination>\n"
"     </DisplayContent>\n"
"    </StopPoint>\n"
"    <StopPoint>\n"
"     <StopIndex>\n"
"      <Value>3</Value>\n"
"     </StopIndex>\n"
"     <StopRef>\n"
"      <Value>Ref:3</Value>\n"
"     </StopRef>\n"
"     <StopName>\n"
"      <Value>\304\214erno\305\241ice,\305\275el.zast.</Value>\n"
"      <Language>cz</Language>\n"
"     </StopName>\n"
"     <DisplayContent>\n"
"      <DisplayContentRef>\n"
"       <Value>1234</Value>\n"
"      </DisplayContentRef>\n"
"      <LineInformation>\n"
"   "
                        "    <LineRef>\n"
"        <Value>100315</Value>\n"
"       </LineRef>\n"
"       <LineName>\n"
"        <Value>315</Value>\n"
"        <Language>cz</Language>\n"
"       </LineName>\n"
"       <LineNumber>\n"
"        <Value>100315</Value>\n"
"       </LineNumber>\n"
"      </LineInformation>\n"
"      <Destination>\n"
"       <DestinationRef>\n"
"        <Value>22</Value>\n"
"       </DestinationRef>\n"
"       <DestinationName>\n"
"        <Value>Zdick\303\241</Value>\n"
"        <Language>cz</Language>\n"
"       </DestinationName>\n"
"      </Destination>\n"
"     </DisplayContent>\n"
"    </StopPoint>\n"
"    <StopPoint>\n"
"     <StopIndex>\n"
"      <Value>4</Value>\n"
"     </StopIndex>\n"
"     <StopRef>\n"
"      <Value>Ref:4</Value>\n"
"     </StopRef>\n"
"     <StopName>\n"
"      <Value>Zdick\303\241</Value>\n"
"      <Language>cz</Language>\n"
"     </StopName>\n"
"     <DisplayContent>\n"
"      <DisplayContentRef>\n"
"       <Value>1234</Value>\n"
"      </DisplayContentRef>\n"
"      <LineInfo"
                        "rmation>\n"
"       <LineRef>\n"
"        <Value>100315</Value>\n"
"       </LineRef>\n"
"       <LineName>\n"
"        <Value>315</Value>\n"
"        <Language>cz</Language>\n"
"       </LineName>\n"
"       <LineNumber>\n"
"        <Value>100315</Value>\n"
"       </LineNumber>\n"
"      </LineInformation>\n"
"      <Destination>\n"
"       <DestinationRef>\n"
"        <Value>22</Value>\n"
"       </DestinationRef>\n"
"       <DestinationName>\n"
"        <Value>Zdick\303\241</Value>\n"
"        <Language>cz</Language>\n"
"       </DestinationName>\n"
"      </Destination>\n"
"     </DisplayContent>\n"
"    </StopPoint>\n"
"   </StopSequence>\n"
"   <LocationState>AtStop</LocationState>\n"
"  </TripInformation>\n"
"  <CurrentStopIndex>\n"
"   <Value>0</Value>\n"
"  </CurrentStopIndex>\n"
"  <RouteDeviation>onroute</RouteDeviation>\n"
"  <DoorState>AllDoorsClosed</DoorState>\n"
"  <VehicleStopRequested>\n"
"   <Value>0</Value>\n"
"  </VehicleStopRequested>\n"
"  <ExitSide>right</ExitSide>\n"
" </AllData>\n"
""
                        "</CustomerInformationService.GetAllDataResponse>", nullptr));
        tlacitkoSmazOkno->setText(QCoreApplication::translate("MainWindow", "Vyma\305\276 okno", nullptr));
        tlacitkoOdesliXml->setText(QCoreApplication::translate("MainWindow", "ode\305\241li na panely", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Odberatele 1.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = seznamOdberatelu->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Adresa", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = seznamOdberatelu->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Struktura", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = seznamOdberatelu->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Interval", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Odberatele V2.2CZ1.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = seznamOdberatelu2->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Adresa", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = seznamOdberatelu2->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Struktura", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = seznamOdberatelu2->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Interval", nullptr));
        lineEdit_ipadresaOdberatele->setText(QCoreApplication::translate("MainWindow", "http://127.0.0.1:48479", nullptr));
        lineEdit_strukturaOdberu->setText(QCoreApplication::translate("MainWindow", "AllData", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "V1.0", nullptr));
        tlacitkoAddsubscriber->setText(QCoreApplication::translate("MainWindow", "P\305\231idat odb\304\233ratele", nullptr));
        tlacitkoRemoveSubscriber->setText(QCoreApplication::translate("MainWindow", "Zrusit odber", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "V2.2CZ1.0", nullptr));
        tlacitkoAddsubscriber_2->setText(QCoreApplication::translate("MainWindow", "P\305\231idat odb\304\233ratele", nullptr));
        tlacitkoRemoveSubscriber_2->setText(QCoreApplication::translate("MainWindow", "Zrusit odber", nullptr));
        label_diagnostika_manual->setText(QCoreApplication::translate("MainWindow", "subscribe diagnostika", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
