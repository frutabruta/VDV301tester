/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *prepinadloStran;
    QWidget *page;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *NazevVysledku;
    QPushButton *pripojeniTlacitko;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *polelinky;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *polespoje;
    QPushButton *prikaztlacitko;
    QHBoxLayout *horizontalLayout;
    QLabel *popisek;
    QVBoxLayout *verticalLayout;
    QPushButton *pridatTlacitko;
    QPushButton *ubratTlacitko;
    QLabel *prikazovyvysledek;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *sipkaNahoru;
    QPushButton *sipkaDolu;
    QPushButton *quitTlacitko;
    QPushButton *tlacitkoNavic;
    QPushButton *tlacitkoIBIS;
    QVBoxLayout *verticalLayout_5;
    QPushButton *BeforeStop;
    QPushButton *AtStop_2;
    QPushButton *AfterStop;
    QPushButton *BetweenStop;
    QLabel *locationStateIndicator;
    QPushButton *tlacitkoNastaveni;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_7;
    QListWidget *listSpoje;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QListWidget *listLinek;
    QWidget *page_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *tlacitkoUlozDoSQL;
    QPushButton *tlacitkoNactiXMLropid;
    QPushButton *tlacitkoSQL;
    QPushButton *tlacitkoZpet;
    QPushButton *tlacitkoTruncate;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *tlacitkoNastavPort;
    QPushButton *tlacitkoOdesliPrikaz;
    QLineEdit *lineEdit_jmenoPortu;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_4;
    QLineEdit *lineEditSqlServer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 480));
        MainWindow->setMaximumSize(QSize(800, 480));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setAutoFillBackground(false);
        prepinadloStran = new QStackedWidget(centralWidget);
        prepinadloStran->setObjectName(QStringLiteral("prepinadloStran"));
        prepinadloStran->setEnabled(true);
        prepinadloStran->setGeometry(QRect(0, 0, 811, 471));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(52, 101, 164, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 127, 191, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(106, 106, 159, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(42, 42, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(56, 56, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
   //     palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        QBrush brush9(QColor(255, 255, 255, 128));
        brush9.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        QBrush brush10(QColor(85, 85, 127, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        QBrush brush11(QColor(255, 255, 255, 128));
        brush11.setStyle(Qt::NoBrush);
      //  palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
        prepinadloStran->setPalette(palette);
        prepinadloStran->setStyleSheet(QStringLiteral("/*background-color:rgb(52, 101, 164); */"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        horizontalLayoutWidget_2 = new QWidget(page);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 300, 481, 115));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 20, -1);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        NazevVysledku = new QLabel(horizontalLayoutWidget_2);
        NazevVysledku->setObjectName(QStringLiteral("NazevVysledku"));

        verticalLayout_2->addWidget(NazevVysledku);

        pripojeniTlacitko = new QPushButton(horizontalLayoutWidget_2);
        pripojeniTlacitko->setObjectName(QStringLiteral("pripojeniTlacitko"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pripojeniTlacitko->sizePolicy().hasHeightForWidth());
        pripojeniTlacitko->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(pripojeniTlacitko);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        polelinky = new QLineEdit(horizontalLayoutWidget_2);
        polelinky->setObjectName(QStringLiteral("polelinky"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush12(QColor(127, 127, 127, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush12);
        QBrush brush13(QColor(170, 170, 170, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush14(QColor(0, 0, 0, 128));
        brush14.setStyle(Qt::NoBrush);
    //    palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        QBrush brush15(QColor(0, 0, 0, 128));
        brush15.setStyle(Qt::NoBrush);
     //   palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        QBrush brush16(QColor(0, 0, 0, 128));
        brush16.setStyle(Qt::NoBrush);
        //palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush16);
        polelinky->setPalette(palette1);
        polelinky->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(polelinky);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        polespoje = new QLineEdit(horizontalLayoutWidget_2);
        polespoje->setObjectName(QStringLiteral("polespoje"));

        horizontalLayout_4->addWidget(polespoje);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout_3);

        prikaztlacitko = new QPushButton(horizontalLayoutWidget_2);
        prikaztlacitko->setObjectName(QStringLiteral("prikaztlacitko"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(prikaztlacitko->sizePolicy().hasHeightForWidth());
        prikaztlacitko->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(prikaztlacitko);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        popisek = new QLabel(horizontalLayoutWidget_2);
        popisek->setObjectName(QStringLiteral("popisek"));
        QFont font;
        font.setPointSize(24);
        popisek->setFont(font);
        popisek->setTextFormat(Qt::PlainText);
        popisek->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(popisek);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        pridatTlacitko = new QPushButton(horizontalLayoutWidget_2);
        pridatTlacitko->setObjectName(QStringLiteral("pridatTlacitko"));
        pridatTlacitko->setEnabled(true);
        sizePolicy1.setHeightForWidth(pridatTlacitko->sizePolicy().hasHeightForWidth());
        pridatTlacitko->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(14);
        pridatTlacitko->setFont(font1);

        verticalLayout->addWidget(pridatTlacitko);

        ubratTlacitko = new QPushButton(horizontalLayoutWidget_2);
        ubratTlacitko->setObjectName(QStringLiteral("ubratTlacitko"));
        sizePolicy1.setHeightForWidth(ubratTlacitko->sizePolicy().hasHeightForWidth());
        ubratTlacitko->setSizePolicy(sizePolicy1);
        ubratTlacitko->setFont(font1);

        verticalLayout->addWidget(ubratTlacitko);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(horizontalLayout);

        prikazovyvysledek = new QLabel(page);
        prikazovyvysledek->setObjectName(QStringLiteral("prikazovyvysledek"));
        prikazovyvysledek->setGeometry(QRect(10, 10, 571, 291));
        QFont font2;
        font2.setPointSize(33);
        prikazovyvysledek->setFont(font2);
        prikazovyvysledek->setAutoFillBackground(false);
        prikazovyvysledek->setStyleSheet(QLatin1String("background-color:rgb(32, 74, 135);\n"
"color: rgb(238, 238, 236);"));
        prikazovyvysledek->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(580, 10, 211, 281));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        sipkaNahoru = new QPushButton(horizontalLayoutWidget);
        sipkaNahoru->setObjectName(QStringLiteral("sipkaNahoru"));
        sizePolicy2.setHeightForWidth(sipkaNahoru->sizePolicy().hasHeightForWidth());
        sipkaNahoru->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(sipkaNahoru);

        sipkaDolu = new QPushButton(horizontalLayoutWidget);
        sipkaDolu->setObjectName(QStringLiteral("sipkaDolu"));
        sizePolicy1.setHeightForWidth(sipkaDolu->sizePolicy().hasHeightForWidth());
        sipkaDolu->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(sipkaDolu);

        quitTlacitko = new QPushButton(horizontalLayoutWidget);
        quitTlacitko->setObjectName(QStringLiteral("quitTlacitko"));
        sizePolicy2.setHeightForWidth(quitTlacitko->sizePolicy().hasHeightForWidth());
        quitTlacitko->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(quitTlacitko);

        tlacitkoNavic = new QPushButton(horizontalLayoutWidget);
        tlacitkoNavic->setObjectName(QStringLiteral("tlacitkoNavic"));

        verticalLayout_4->addWidget(tlacitkoNavic);

        tlacitkoIBIS = new QPushButton(horizontalLayoutWidget);
        tlacitkoIBIS->setObjectName(QStringLiteral("tlacitkoIBIS"));

        verticalLayout_4->addWidget(tlacitkoIBIS);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        BeforeStop = new QPushButton(horizontalLayoutWidget);
        BeforeStop->setObjectName(QStringLiteral("BeforeStop"));
        sizePolicy1.setHeightForWidth(BeforeStop->sizePolicy().hasHeightForWidth());
        BeforeStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(BeforeStop);

        AtStop_2 = new QPushButton(horizontalLayoutWidget);
        AtStop_2->setObjectName(QStringLiteral("AtStop_2"));
        sizePolicy1.setHeightForWidth(AtStop_2->sizePolicy().hasHeightForWidth());
        AtStop_2->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(AtStop_2);

        AfterStop = new QPushButton(horizontalLayoutWidget);
        AfterStop->setObjectName(QStringLiteral("AfterStop"));
        sizePolicy1.setHeightForWidth(AfterStop->sizePolicy().hasHeightForWidth());
        AfterStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(AfterStop);

        BetweenStop = new QPushButton(horizontalLayoutWidget);
        BetweenStop->setObjectName(QStringLiteral("BetweenStop"));
        sizePolicy1.setHeightForWidth(BetweenStop->sizePolicy().hasHeightForWidth());
        BetweenStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(BetweenStop);

        locationStateIndicator = new QLabel(horizontalLayoutWidget);
        locationStateIndicator->setObjectName(QStringLiteral("locationStateIndicator"));

        verticalLayout_5->addWidget(locationStateIndicator);

        tlacitkoNastaveni = new QPushButton(horizontalLayoutWidget);
        tlacitkoNastaveni->setObjectName(QStringLiteral("tlacitkoNastaveni"));

        verticalLayout_5->addWidget(tlacitkoNastaveni);


        horizontalLayout_5->addLayout(verticalLayout_5);

        verticalLayoutWidget_2 = new QWidget(page);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(490, 300, 160, 128));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_6->addWidget(radioButton);

        radioButton_2 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout_6->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout_6->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_6->addWidget(radioButton_4);

        verticalLayoutWidget_3 = new QWidget(page);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(650, 330, 160, 124));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        listSpoje = new QListWidget(verticalLayoutWidget_3);
        listSpoje->setObjectName(QStringLiteral("listSpoje"));

        verticalLayout_7->addWidget(listSpoje);

        checkBox = new QCheckBox(verticalLayoutWidget_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_7->addWidget(checkBox);

        checkBox_2 = new QCheckBox(verticalLayoutWidget_3);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_7->addWidget(checkBox_2);

        listLinek = new QListWidget(page);
        listLinek->setObjectName(QStringLiteral("listLinek"));
        listLinek->setGeometry(QRect(657, 298, 141, 31));
        prepinadloStran->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayoutWidget = new QWidget(page_2);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(280, 110, 311, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tlacitkoUlozDoSQL = new QPushButton(gridLayoutWidget);
        tlacitkoUlozDoSQL->setObjectName(QStringLiteral("tlacitkoUlozDoSQL"));

        gridLayout->addWidget(tlacitkoUlozDoSQL, 0, 2, 1, 1);

        tlacitkoNactiXMLropid = new QPushButton(gridLayoutWidget);
        tlacitkoNactiXMLropid->setObjectName(QStringLiteral("tlacitkoNactiXMLropid"));

        gridLayout->addWidget(tlacitkoNactiXMLropid, 0, 1, 1, 1);

        tlacitkoSQL = new QPushButton(gridLayoutWidget);
        tlacitkoSQL->setObjectName(QStringLiteral("tlacitkoSQL"));

        gridLayout->addWidget(tlacitkoSQL, 0, 0, 1, 1);

        tlacitkoZpet = new QPushButton(gridLayoutWidget);
        tlacitkoZpet->setObjectName(QStringLiteral("tlacitkoZpet"));

        gridLayout->addWidget(tlacitkoZpet, 1, 0, 1, 1);

        tlacitkoTruncate = new QPushButton(gridLayoutWidget);
        tlacitkoTruncate->setObjectName(QStringLiteral("tlacitkoTruncate"));

        gridLayout->addWidget(tlacitkoTruncate, 1, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(page_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(160, 250, 401, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tlacitkoNastavPort = new QPushButton(gridLayoutWidget_2);
        tlacitkoNastavPort->setObjectName(QStringLiteral("tlacitkoNastavPort"));

        gridLayout_2->addWidget(tlacitkoNastavPort, 0, 0, 1, 1);

        tlacitkoOdesliPrikaz = new QPushButton(gridLayoutWidget_2);
        tlacitkoOdesliPrikaz->setObjectName(QStringLiteral("tlacitkoOdesliPrikaz"));

        gridLayout_2->addWidget(tlacitkoOdesliPrikaz, 1, 0, 1, 1);

        lineEdit_jmenoPortu = new QLineEdit(gridLayoutWidget_2);
        lineEdit_jmenoPortu->setObjectName(QStringLiteral("lineEdit_jmenoPortu"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        lineEdit_jmenoPortu->setPalette(palette2);

        gridLayout_2->addWidget(lineEdit_jmenoPortu, 0, 1, 1, 1);

        verticalLayoutWidget = new QWidget(page_2);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(90, 40, 160, 80));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_8->addWidget(label_4);

        lineEditSqlServer = new QLineEdit(verticalLayoutWidget);
        lineEditSqlServer->setObjectName(QStringLiteral("lineEditSqlServer"));

        verticalLayout_8->addWidget(lineEditSqlServer);

        prepinadloStran->addWidget(page_2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(false);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        prepinadloStran->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Stav p\305\231ipojen\303\255:", nullptr));
        NazevVysledku->setText(QApplication::translate("MainWindow", "stav pripojeni", nullptr));
        pripojeniTlacitko->setText(QApplication::translate("MainWindow", "SQL Connect", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Linka</span></p></body></html>", nullptr));
        polelinky->setText(QApplication::translate("MainWindow", "100952", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Spoj", nullptr));
        polespoje->setText(QApplication::translate("MainWindow", "1001", nullptr));
        prikaztlacitko->setText(QApplication::translate("MainWindow", "POTVRDIT", nullptr));
        popisek->setText(QApplication::translate("MainWindow", "0", nullptr));
        pridatTlacitko->setText(QApplication::translate("MainWindow", "P\305\231idat", nullptr));
        ubratTlacitko->setText(QApplication::translate("MainWindow", "Ubrat", nullptr));
        prikazovyvysledek->setText(QApplication::translate("MainWindow", "seznam zastavek", nullptr));
        sipkaNahoru->setText(QApplication::translate("MainWindow", "\342\226\262", nullptr));
        sipkaDolu->setText(QApplication::translate("MainWindow", "\342\226\274", nullptr));
        quitTlacitko->setText(QApplication::translate("MainWindow", "QUIT", nullptr));
        tlacitkoNavic->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
        tlacitkoIBIS->setText(QApplication::translate("MainWindow", "IBIS", nullptr));
        BeforeStop->setText(QApplication::translate("MainWindow", "BeforeStop", nullptr));
        AtStop_2->setText(QApplication::translate("MainWindow", "AtStop", nullptr));
        AfterStop->setText(QApplication::translate("MainWindow", "AfterStop", nullptr));
        BetweenStop->setText(QApplication::translate("MainWindow", "BetweenStop", nullptr));
        locationStateIndicator->setText(QApplication::translate("MainWindow", "locationState", nullptr));
        tlacitkoNastaveni->setText(QApplication::translate("MainWindow", "nastaveni", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "DoorsOpen", nullptr));
        radioButton_2->setText(QApplication::translate("MainWindow", "AllDoorsClosed", nullptr));
        radioButton_3->setText(QApplication::translate("MainWindow", "SingleDoorOpen", nullptr));
        radioButton_4->setText(QApplication::translate("MainWindow", "SingleDoorClosed", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "MPV p\305\231estupy", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "StopRequested", nullptr));
        tlacitkoUlozDoSQL->setText(QApplication::translate("MainWindow", "ulozDoSQL", nullptr));
        tlacitkoNactiXMLropid->setText(QApplication::translate("MainWindow", "nactiXML", nullptr));
        tlacitkoSQL->setText(QApplication::translate("MainWindow", "pripojSQL", nullptr));
        tlacitkoZpet->setText(QApplication::translate("MainWindow", "zpet", nullptr));
        tlacitkoTruncate->setText(QApplication::translate("MainWindow", "TRUNCATE", nullptr));
        tlacitkoNastavPort->setText(QApplication::translate("MainWindow", "nastav \304\215\303\255slo portu", nullptr));
        tlacitkoOdesliPrikaz->setText(QApplication::translate("MainWindow", "odesliPrikaz", nullptr));
        lineEdit_jmenoPortu->setText(QApplication::translate("MainWindow", "ttyUSB0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Adresa SQL serveru", nullptr));
        lineEditSqlServer->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
