/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_21;
    QTabWidget *tabWidget_hlavni;
    QWidget *tab_palPC;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *bocniMenu;
    QPushButton *pushButton_menu_linkospoj;
    QPushButton *pushButton_menu_turnus;
    QPushButton *pushButton_menu_jizda;
    QPushButton *pushButton_menu_oznameni;
    QPushButton *pushButton_menu_fullscreen;
    QPushButton *pushButton_menu_quit;
    QStackedWidget *stackedWidget_palPc;
    QWidget *page_jizda;
    QGridLayout *gridLayout_3;
    QHBoxLayout *displej_hor_layout;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_aktLinka;
    QLabel *label_aktSpoj;
    QTableWidget *tableWidgetNasledujiciZastavky;
    QHBoxLayout *horizontalLayout_18;
    QRadioButton *radioButton_singleDoorOpen;
    QRadioButton *radioButton_allDoorsClosed;
    QRadioButton *radioButton_doorsOpen;
    QRadioButton *radioButton_singleDoorCloser;
    QVBoxLayout *verticalLayout_sipky;
    QPushButton *pushButton_jizda_sipkaZpetSkok;
    QPushButton *pushButton_jizda_sipkaZpet;
    QPushButton *pushButton_jizda_sipkaDal;
    QPushButton *pushButton_jizda_sipkaDalSkok;
    QLabel *popisek;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_jizda_beforeStop;
    QPushButton *pushButton_jizda_atStop;
    QPushButton *pushButton_jizda_afterStop;
    QPushButton *pushButton_jizda_betweenStop;
    QLabel *locationStateIndicator;
    QPushButton *pushButton_jizda_IBIS;
    QWidget *page_linkaspoj;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_prikaz;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *polelinky;
    QLineEdit *polespoje;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QListWidget *listLinek;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QListWidget *listSpoje;
    QCheckBox *checkBox;
    QWidget *page_turnus;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_16;
    QFormLayout *formLayout_2;
    QLabel *label_16;
    QLineEdit *poleLinkyTurnus;
    QLineEdit *poleSpojeTurnus;
    QLabel *label_17;
    QVBoxLayout *verticalLayout_19;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_MpvTurnusy;
    QPushButton *pushButton_turnus_prikaz;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_18;
    QListWidget *listKmenovychLinek;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_20;
    QListWidget *listPoradi;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_19;
    QListWidget *listTurnusSpoje;
    QWidget *page_oznameni;
    QHBoxLayout *horizontalLayout_23;
    QTableWidget *tableWidget_oznameni;
    QWidget *tab_moznosti;
    QHBoxLayout *horizontalLayout_10;
    QTabWidget *tabWidget_moznosti;
    QWidget *tab_moznosti_nast;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_14;
    QDateEdit *dateEdit;
    QPushButton *pushButton_nast_dnes;
    QCalendarWidget *calendarWidget;
    QVBoxLayout *verticalLayoutvstupniData;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_cestaXml;
    QPushButton *pushButton_nast_truncate;
    QPushButton *pushButton_nast_xmlVyberCestu;
    QPushButton *pushButton_nast_nactiXMLropid;
    QProgressBar *progressBar_importXml;
    QLabel *label_diagnostika_sql;
    QVBoxLayout *verticalLayoutseriovyPort;
    QLabel *label_7;
    QLineEdit *lineEdit_jmenoPortu;
    QPushButton *pushButton_nast_nastavPort;
    QPushButton *pushButton_nast_odesliPrikaz;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_12;
    QLabel *label_build;
    QWidget *tab_moznosti_manual;
    QGridLayout *gridLayout_8;
    QLabel *label_diagnostika_manual;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_11;
    QTableWidget *seznamOdberatelu;
    QLabel *label_15;
    QTableWidget *seznamOdberatelu2;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton_manual_removeSubscriber_2;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButton_manual_removeSubscriber;
    QPushButton *pushButton_manual_addsubscriber;
    QPushButton *pushButton_manual_addsubscriber_2;
    QLineEdit *lineEdit_strukturaOdberu;
    QLineEdit *lineEdit_ipadresaOdberatele;
    QVBoxLayout *verticalLayout_28;
    QLabel *label_10;
    QPlainTextEdit *plainTextEditCustomXml;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *pushButton_manual_odesliXml;
    QPushButton *pushButton_manual_smazOkno;
    QWidget *tab_moznosti_zarizeni;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget_seznamZarizeni;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *tab_test;
    QHBoxLayout *horizontalLayout_5;
    QFormLayout *formLayout_3;
    QVBoxLayout *verticalLayout_21;
    QPushButton *pushButton_menu2_sluzby;
    QPushButton *pushButton_menu2_prubehTestu;
    QPushButton *pushButton_menu2_rezerva;
    QPushButton *pushButton_menu2_fullscreen;
    QPushButton *pushButton_menu2_quit;
    QStackedWidget *stackedWidget_testy;
    QWidget *page_prubehTestu;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pushButton_test1;
    QPushButton *pushButton_test2;
    QPushButton *pushButton_test3;
    QPushButton *pushButton_test4;
    QHBoxLayout *horizontalLayout_15;
    QTableWidget *tableWidgetCastiTestu;
    QVBoxLayout *verticalLayout_22;
    QPushButton *pushButton_startTest;
    QPushButton *pushButton_stopTest;
    QWidget *page_prepinaceSluzby;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_nazevSluzby;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButton_ON1;
    QRadioButton *radioButton_OFF1;
    QVBoxLayout *verticalLayout_26;
    QLabel *label_nazevSluzby_2;
    QHBoxLayout *horizontalLayout_16;
    QRadioButton *radioButton_ON2;
    QRadioButton *radioButton_OFF2;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_nazevSluzby_3;
    QHBoxLayout *horizontalLayout_17;
    QRadioButton *radioButton_ON3;
    QRadioButton *radioButton_OFF3;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_nazevSluzby_4;
    QHBoxLayout *horizontalLayout_19;
    QRadioButton *radioButton_ON4;
    QRadioButton *radioButton_OFF4;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 100));
        MainWindow->setMaximumSize(QSize(2000, 2000));
        MainWindow->setStyleSheet(QString::fromUtf8("padding: 0px;margin: 0px;"));
        MainWindow->setAnimated(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_21 = new QHBoxLayout(centralWidget);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        tabWidget_hlavni = new QTabWidget(centralWidget);
        tabWidget_hlavni->setObjectName(QString::fromUtf8("tabWidget_hlavni"));
        QFont font;
        font.setPointSize(20);
        tabWidget_hlavni->setFont(font);
        tabWidget_hlavni->setStyleSheet(QString::fromUtf8("margin=0px; padding= 0 px;"));
        tabWidget_hlavni->setTabPosition(QTabWidget::North);
        tabWidget_hlavni->setTabShape(QTabWidget::Rounded);
        tab_palPC = new QWidget();
        tab_palPC->setObjectName(QString::fromUtf8("tab_palPC"));
        tab_palPC->setStyleSheet(QString::fromUtf8("padding: 0px; margin:0px;"));
        horizontalLayout_4 = new QHBoxLayout(tab_palPC);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_9->setContentsMargins(0, -1, -1, -1);
        bocniMenu = new QVBoxLayout();
        bocniMenu->setSpacing(6);
        bocniMenu->setObjectName(QString::fromUtf8("bocniMenu"));
        bocniMenu->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton_menu_linkospoj = new QPushButton(tab_palPC);
        pushButton_menu_linkospoj->setObjectName(QString::fromUtf8("pushButton_menu_linkospoj"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_menu_linkospoj->sizePolicy().hasHeightForWidth());
        pushButton_menu_linkospoj->setSizePolicy(sizePolicy2);
        pushButton_menu_linkospoj->setMinimumSize(QSize(0, 0));
        pushButton_menu_linkospoj->setMaximumSize(QSize(200, 200));
        QFont font1;
        font1.setPointSize(15);
        pushButton_menu_linkospoj->setFont(font1);
        pushButton_menu_linkospoj->setCheckable(true);
        pushButton_menu_linkospoj->setChecked(true);
        pushButton_menu_linkospoj->setAutoExclusive(true);

        bocniMenu->addWidget(pushButton_menu_linkospoj);

        pushButton_menu_turnus = new QPushButton(tab_palPC);
        pushButton_menu_turnus->setObjectName(QString::fromUtf8("pushButton_menu_turnus"));
        sizePolicy2.setHeightForWidth(pushButton_menu_turnus->sizePolicy().hasHeightForWidth());
        pushButton_menu_turnus->setSizePolicy(sizePolicy2);
        pushButton_menu_turnus->setMinimumSize(QSize(0, 0));
        pushButton_menu_turnus->setMaximumSize(QSize(200, 200));
        pushButton_menu_turnus->setFont(font1);
        pushButton_menu_turnus->setCheckable(true);
        pushButton_menu_turnus->setChecked(false);
        pushButton_menu_turnus->setAutoExclusive(true);

        bocniMenu->addWidget(pushButton_menu_turnus);

        pushButton_menu_jizda = new QPushButton(tab_palPC);
        pushButton_menu_jizda->setObjectName(QString::fromUtf8("pushButton_menu_jizda"));
        sizePolicy2.setHeightForWidth(pushButton_menu_jizda->sizePolicy().hasHeightForWidth());
        pushButton_menu_jizda->setSizePolicy(sizePolicy2);
        pushButton_menu_jizda->setMinimumSize(QSize(0, 0));
        pushButton_menu_jizda->setMaximumSize(QSize(200, 200));
        pushButton_menu_jizda->setFont(font1);
        pushButton_menu_jizda->setCheckable(true);
        pushButton_menu_jizda->setAutoExclusive(true);

        bocniMenu->addWidget(pushButton_menu_jizda);

        pushButton_menu_oznameni = new QPushButton(tab_palPC);
        pushButton_menu_oznameni->setObjectName(QString::fromUtf8("pushButton_menu_oznameni"));
        sizePolicy2.setHeightForWidth(pushButton_menu_oznameni->sizePolicy().hasHeightForWidth());
        pushButton_menu_oznameni->setSizePolicy(sizePolicy2);
        pushButton_menu_oznameni->setMinimumSize(QSize(0, 0));
        pushButton_menu_oznameni->setMaximumSize(QSize(200, 200));
        QFont font2;
        font2.setPointSize(15);
        font2.setKerning(true);
        pushButton_menu_oznameni->setFont(font2);
        pushButton_menu_oznameni->setAutoDefault(false);
        pushButton_menu_oznameni->setFlat(false);

        bocniMenu->addWidget(pushButton_menu_oznameni);

        pushButton_menu_fullscreen = new QPushButton(tab_palPC);
        pushButton_menu_fullscreen->setObjectName(QString::fromUtf8("pushButton_menu_fullscreen"));
        sizePolicy2.setHeightForWidth(pushButton_menu_fullscreen->sizePolicy().hasHeightForWidth());
        pushButton_menu_fullscreen->setSizePolicy(sizePolicy2);
        pushButton_menu_fullscreen->setMinimumSize(QSize(0, 0));
        pushButton_menu_fullscreen->setMaximumSize(QSize(200, 200));
        pushButton_menu_fullscreen->setFont(font1);
        pushButton_menu_fullscreen->setCheckable(true);
        pushButton_menu_fullscreen->setAutoExclusive(false);

        bocniMenu->addWidget(pushButton_menu_fullscreen);

        pushButton_menu_quit = new QPushButton(tab_palPC);
        pushButton_menu_quit->setObjectName(QString::fromUtf8("pushButton_menu_quit"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_menu_quit->sizePolicy().hasHeightForWidth());
        pushButton_menu_quit->setSizePolicy(sizePolicy3);
        pushButton_menu_quit->setMaximumSize(QSize(200, 200));
        QPalette palette;
        pushButton_menu_quit->setPalette(palette);
        pushButton_menu_quit->setFont(font1);

        bocniMenu->addWidget(pushButton_menu_quit);


        horizontalLayout_9->addLayout(bocniMenu);

        stackedWidget_palPc = new QStackedWidget(tab_palPC);
        stackedWidget_palPc->setObjectName(QString::fromUtf8("stackedWidget_palPc"));
        stackedWidget_palPc->setEnabled(true);
        sizePolicy3.setHeightForWidth(stackedWidget_palPc->sizePolicy().hasHeightForWidth());
        stackedWidget_palPc->setSizePolicy(sizePolicy3);
        stackedWidget_palPc->setMinimumSize(QSize(150, 0));
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
        stackedWidget_palPc->setPalette(palette1);
        stackedWidget_palPc->setStyleSheet(QString::fromUtf8("margin:0px;\n"
"padding: 0 px;"));
        page_jizda = new QWidget();
        page_jizda->setObjectName(QString::fromUtf8("page_jizda"));
        gridLayout_3 = new QGridLayout(page_jizda);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        displej_hor_layout = new QHBoxLayout();
        displej_hor_layout->setSpacing(6);
        displej_hor_layout->setObjectName(QString::fromUtf8("displej_hor_layout"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_aktLinka = new QLabel(page_jizda);
        label_aktLinka->setObjectName(QString::fromUtf8("label_aktLinka"));
        label_aktLinka->setFont(font1);

        horizontalLayout_8->addWidget(label_aktLinka);

        label_aktSpoj = new QLabel(page_jizda);
        label_aktSpoj->setObjectName(QString::fromUtf8("label_aktSpoj"));
        label_aktSpoj->setFont(font1);

        horizontalLayout_8->addWidget(label_aktSpoj);


        verticalLayout_13->addLayout(horizontalLayout_8);

        tableWidgetNasledujiciZastavky = new QTableWidget(page_jizda);
        if (tableWidgetNasledujiciZastavky->columnCount() < 5)
            tableWidgetNasledujiciZastavky->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetNasledujiciZastavky->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetNasledujiciZastavky->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignTrailing|Qt::AlignVCenter);
        tableWidgetNasledujiciZastavky->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetNasledujiciZastavky->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetNasledujiciZastavky->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetNasledujiciZastavky->setObjectName(QString::fromUtf8("tableWidgetNasledujiciZastavky"));
        tableWidgetNasledujiciZastavky->setMinimumSize(QSize(0, 0));
        tableWidgetNasledujiciZastavky->setFont(font);
        tableWidgetNasledujiciZastavky->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetNasledujiciZastavky->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetNasledujiciZastavky->horizontalHeader()->setVisible(false);
        tableWidgetNasledujiciZastavky->verticalHeader()->setVisible(false);

        verticalLayout_13->addWidget(tableWidgetNasledujiciZastavky);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        radioButton_singleDoorOpen = new QRadioButton(page_jizda);
        radioButton_singleDoorOpen->setObjectName(QString::fromUtf8("radioButton_singleDoorOpen"));
        QFont font3;
        font3.setPointSize(12);
        radioButton_singleDoorOpen->setFont(font3);

        horizontalLayout_18->addWidget(radioButton_singleDoorOpen);

        radioButton_allDoorsClosed = new QRadioButton(page_jizda);
        radioButton_allDoorsClosed->setObjectName(QString::fromUtf8("radioButton_allDoorsClosed"));
        radioButton_allDoorsClosed->setFont(font3);

        horizontalLayout_18->addWidget(radioButton_allDoorsClosed);

        radioButton_doorsOpen = new QRadioButton(page_jizda);
        radioButton_doorsOpen->setObjectName(QString::fromUtf8("radioButton_doorsOpen"));
        radioButton_doorsOpen->setFont(font3);

        horizontalLayout_18->addWidget(radioButton_doorsOpen);

        radioButton_singleDoorCloser = new QRadioButton(page_jizda);
        radioButton_singleDoorCloser->setObjectName(QString::fromUtf8("radioButton_singleDoorCloser"));
        radioButton_singleDoorCloser->setFont(font3);

        horizontalLayout_18->addWidget(radioButton_singleDoorCloser);


        verticalLayout_13->addLayout(horizontalLayout_18);


        displej_hor_layout->addLayout(verticalLayout_13);

        verticalLayout_sipky = new QVBoxLayout();
        verticalLayout_sipky->setSpacing(6);
        verticalLayout_sipky->setObjectName(QString::fromUtf8("verticalLayout_sipky"));
        verticalLayout_sipky->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton_jizda_sipkaZpetSkok = new QPushButton(page_jizda);
        pushButton_jizda_sipkaZpetSkok->setObjectName(QString::fromUtf8("pushButton_jizda_sipkaZpetSkok"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_jizda_sipkaZpetSkok->sizePolicy().hasHeightForWidth());
        pushButton_jizda_sipkaZpetSkok->setSizePolicy(sizePolicy4);
        pushButton_jizda_sipkaZpetSkok->setMinimumSize(QSize(0, 50));
        QFont font4;
        font4.setPointSize(14);
        pushButton_jizda_sipkaZpetSkok->setFont(font4);

        verticalLayout_sipky->addWidget(pushButton_jizda_sipkaZpetSkok);

        pushButton_jizda_sipkaZpet = new QPushButton(page_jizda);
        pushButton_jizda_sipkaZpet->setObjectName(QString::fromUtf8("pushButton_jizda_sipkaZpet"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_jizda_sipkaZpet->sizePolicy().hasHeightForWidth());
        pushButton_jizda_sipkaZpet->setSizePolicy(sizePolicy5);
        pushButton_jizda_sipkaZpet->setMaximumSize(QSize(100, 16777215));
        pushButton_jizda_sipkaZpet->setFont(font4);

        verticalLayout_sipky->addWidget(pushButton_jizda_sipkaZpet);

        pushButton_jizda_sipkaDal = new QPushButton(page_jizda);
        pushButton_jizda_sipkaDal->setObjectName(QString::fromUtf8("pushButton_jizda_sipkaDal"));
        sizePolicy5.setHeightForWidth(pushButton_jizda_sipkaDal->sizePolicy().hasHeightForWidth());
        pushButton_jizda_sipkaDal->setSizePolicy(sizePolicy5);
        pushButton_jizda_sipkaDal->setMinimumSize(QSize(70, 0));
        pushButton_jizda_sipkaDal->setMaximumSize(QSize(100, 16777215));
        pushButton_jizda_sipkaDal->setFont(font4);

        verticalLayout_sipky->addWidget(pushButton_jizda_sipkaDal);

        pushButton_jizda_sipkaDalSkok = new QPushButton(page_jizda);
        pushButton_jizda_sipkaDalSkok->setObjectName(QString::fromUtf8("pushButton_jizda_sipkaDalSkok"));
        pushButton_jizda_sipkaDalSkok->setEnabled(true);
        sizePolicy4.setHeightForWidth(pushButton_jizda_sipkaDalSkok->sizePolicy().hasHeightForWidth());
        pushButton_jizda_sipkaDalSkok->setSizePolicy(sizePolicy4);
        pushButton_jizda_sipkaDalSkok->setMinimumSize(QSize(0, 50));
        pushButton_jizda_sipkaDalSkok->setFont(font4);

        verticalLayout_sipky->addWidget(pushButton_jizda_sipkaDalSkok);

        popisek = new QLabel(page_jizda);
        popisek->setObjectName(QString::fromUtf8("popisek"));
        QFont font5;
        font5.setPointSize(24);
        popisek->setFont(font5);
        popisek->setTextFormat(Qt::PlainText);
        popisek->setAlignment(Qt::AlignCenter);

        verticalLayout_sipky->addWidget(popisek);


        displej_hor_layout->addLayout(verticalLayout_sipky);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetNoConstraint);
        pushButton_jizda_beforeStop = new QPushButton(page_jizda);
        pushButton_jizda_beforeStop->setObjectName(QString::fromUtf8("pushButton_jizda_beforeStop"));
        sizePolicy2.setHeightForWidth(pushButton_jizda_beforeStop->sizePolicy().hasHeightForWidth());
        pushButton_jizda_beforeStop->setSizePolicy(sizePolicy2);
        pushButton_jizda_beforeStop->setFont(font);
        pushButton_jizda_beforeStop->setCheckable(true);
        pushButton_jizda_beforeStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(pushButton_jizda_beforeStop);

        pushButton_jizda_atStop = new QPushButton(page_jizda);
        pushButton_jizda_atStop->setObjectName(QString::fromUtf8("pushButton_jizda_atStop"));
        sizePolicy2.setHeightForWidth(pushButton_jizda_atStop->sizePolicy().hasHeightForWidth());
        pushButton_jizda_atStop->setSizePolicy(sizePolicy2);
        pushButton_jizda_atStop->setFont(font);
        pushButton_jizda_atStop->setCheckable(true);
        pushButton_jizda_atStop->setChecked(true);
        pushButton_jizda_atStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(pushButton_jizda_atStop);

        pushButton_jizda_afterStop = new QPushButton(page_jizda);
        pushButton_jizda_afterStop->setObjectName(QString::fromUtf8("pushButton_jizda_afterStop"));
        sizePolicy2.setHeightForWidth(pushButton_jizda_afterStop->sizePolicy().hasHeightForWidth());
        pushButton_jizda_afterStop->setSizePolicy(sizePolicy2);
        pushButton_jizda_afterStop->setFont(font);
        pushButton_jizda_afterStop->setCheckable(true);
        pushButton_jizda_afterStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(pushButton_jizda_afterStop);

        pushButton_jizda_betweenStop = new QPushButton(page_jizda);
        pushButton_jizda_betweenStop->setObjectName(QString::fromUtf8("pushButton_jizda_betweenStop"));
        sizePolicy2.setHeightForWidth(pushButton_jizda_betweenStop->sizePolicy().hasHeightForWidth());
        pushButton_jizda_betweenStop->setSizePolicy(sizePolicy2);
        QFont font6;
        font6.setPointSize(18);
        pushButton_jizda_betweenStop->setFont(font6);
        pushButton_jizda_betweenStop->setCheckable(true);
        pushButton_jizda_betweenStop->setAutoExclusive(true);

        verticalLayout_5->addWidget(pushButton_jizda_betweenStop);

        locationStateIndicator = new QLabel(page_jizda);
        locationStateIndicator->setObjectName(QString::fromUtf8("locationStateIndicator"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(locationStateIndicator->sizePolicy().hasHeightForWidth());
        locationStateIndicator->setSizePolicy(sizePolicy6);

        verticalLayout_5->addWidget(locationStateIndicator);

        pushButton_jizda_IBIS = new QPushButton(page_jizda);
        pushButton_jizda_IBIS->setObjectName(QString::fromUtf8("pushButton_jizda_IBIS"));
        pushButton_jizda_IBIS->setFont(font6);

        verticalLayout_5->addWidget(pushButton_jizda_IBIS);


        displej_hor_layout->addLayout(verticalLayout_5);


        gridLayout_3->addLayout(displej_hor_layout, 2, 0, 1, 1);

        stackedWidget_palPc->addWidget(page_jizda);
        page_linkaspoj = new QWidget();
        page_linkaspoj->setObjectName(QString::fromUtf8("page_linkaspoj"));
        gridLayout_2 = new QGridLayout(page_linkaspoj);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox_2 = new QCheckBox(page_linkaspoj);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setFont(font);

        gridLayout_2->addWidget(checkBox_2, 2, 0, 1, 1);

        pushButton_prikaz = new QPushButton(page_linkaspoj);
        pushButton_prikaz->setObjectName(QString::fromUtf8("pushButton_prikaz"));
        sizePolicy3.setHeightForWidth(pushButton_prikaz->sizePolicy().hasHeightForWidth());
        pushButton_prikaz->setSizePolicy(sizePolicy3);
        pushButton_prikaz->setFont(font);

        gridLayout_2->addWidget(pushButton_prikaz, 5, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
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
        polelinky->setFont(font);
        polelinky->setAutoFillBackground(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, polelinky);

        polespoje = new QLineEdit(page_linkaspoj);
        polespoje->setObjectName(QString::fromUtf8("polespoje"));
        polespoje->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, polespoje);

        label_2 = new QLabel(page_linkaspoj);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);


        verticalLayout_7->addLayout(formLayout);


        gridLayout_2->addLayout(verticalLayout_7, 1, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_8 = new QLabel(page_linkaspoj);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

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
        label_9->setFont(font1);

        verticalLayout_9->addWidget(label_9);

        listSpoje = new QListWidget(page_linkaspoj);
        listSpoje->setObjectName(QString::fromUtf8("listSpoje"));
        listSpoje->setFont(font);

        verticalLayout_9->addWidget(listSpoje);


        horizontalLayout_7->addLayout(verticalLayout_9);


        gridLayout_2->addLayout(horizontalLayout_7, 0, 2, 7, 1);

        checkBox = new QCheckBox(page_linkaspoj);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font);

        gridLayout_2->addWidget(checkBox, 3, 0, 1, 1);

        stackedWidget_palPc->addWidget(page_linkaspoj);
        page_turnus = new QWidget();
        page_turnus->setObjectName(QString::fromUtf8("page_turnus"));
        gridLayout_4 = new QGridLayout(page_turnus);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_16 = new QLabel(page_turnus);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_16);

        poleLinkyTurnus = new QLineEdit(page_turnus);
        poleLinkyTurnus->setObjectName(QString::fromUtf8("poleLinkyTurnus"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush12);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush17(QColor(0, 0, 0, 128));
        brush17.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush17);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        QBrush brush18(QColor(0, 0, 0, 128));
        brush18.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush18);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        QBrush brush19(QColor(0, 0, 0, 128));
        brush19.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush19);
#endif
        poleLinkyTurnus->setPalette(palette3);
        poleLinkyTurnus->setFont(font);
        poleLinkyTurnus->setAutoFillBackground(false);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, poleLinkyTurnus);

        poleSpojeTurnus = new QLineEdit(page_turnus);
        poleSpojeTurnus->setObjectName(QString::fromUtf8("poleSpojeTurnus"));
        poleSpojeTurnus->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, poleSpojeTurnus);

        label_17 = new QLabel(page_turnus);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_17);


        verticalLayout_16->addLayout(formLayout_2);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        checkBox_4 = new QCheckBox(page_turnus);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setFont(font);

        verticalLayout_19->addWidget(checkBox_4);

        checkBox_MpvTurnusy = new QCheckBox(page_turnus);
        checkBox_MpvTurnusy->setObjectName(QString::fromUtf8("checkBox_MpvTurnusy"));
        checkBox_MpvTurnusy->setFont(font);
        checkBox_MpvTurnusy->setIconSize(QSize(16, 16));

        verticalLayout_19->addWidget(checkBox_MpvTurnusy);

        pushButton_turnus_prikaz = new QPushButton(page_turnus);
        pushButton_turnus_prikaz->setObjectName(QString::fromUtf8("pushButton_turnus_prikaz"));
        sizePolicy3.setHeightForWidth(pushButton_turnus_prikaz->sizePolicy().hasHeightForWidth());
        pushButton_turnus_prikaz->setSizePolicy(sizePolicy3);
        pushButton_turnus_prikaz->setFont(font);

        verticalLayout_19->addWidget(pushButton_turnus_prikaz);


        verticalLayout_16->addLayout(verticalLayout_19);


        gridLayout_4->addLayout(verticalLayout_16, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_18 = new QLabel(page_turnus);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font1);

        verticalLayout_17->addWidget(label_18);

        listKmenovychLinek = new QListWidget(page_turnus);
        listKmenovychLinek->setObjectName(QString::fromUtf8("listKmenovychLinek"));
        listKmenovychLinek->setFont(font);

        verticalLayout_17->addWidget(listKmenovychLinek);


        horizontalLayout_12->addLayout(verticalLayout_17);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_20 = new QLabel(page_turnus);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);

        verticalLayout_20->addWidget(label_20);

        listPoradi = new QListWidget(page_turnus);
        listPoradi->setObjectName(QString::fromUtf8("listPoradi"));
        listPoradi->setFont(font);

        verticalLayout_20->addWidget(listPoradi);


        horizontalLayout_12->addLayout(verticalLayout_20);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_19 = new QLabel(page_turnus);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font1);

        verticalLayout_18->addWidget(label_19);

        listTurnusSpoje = new QListWidget(page_turnus);
        listTurnusSpoje->setObjectName(QString::fromUtf8("listTurnusSpoje"));
        listTurnusSpoje->setFont(font);

        verticalLayout_18->addWidget(listTurnusSpoje);


        horizontalLayout_12->addLayout(verticalLayout_18);


        gridLayout_4->addLayout(horizontalLayout_12, 0, 1, 3, 1);

        stackedWidget_palPc->addWidget(page_turnus);
        page_oznameni = new QWidget();
        page_oznameni->setObjectName(QString::fromUtf8("page_oznameni"));
        horizontalLayout_23 = new QHBoxLayout(page_oznameni);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        tableWidget_oznameni = new QTableWidget(page_oznameni);
        if (tableWidget_oznameni->columnCount() < 5)
            tableWidget_oznameni->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget_oznameni->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_oznameni->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_oznameni->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_oznameni->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_oznameni->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidget_oznameni->setObjectName(QString::fromUtf8("tableWidget_oznameni"));
        QFont font7;
        font7.setPointSize(30);
        font7.setBold(false);
        font7.setWeight(50);
        tableWidget_oznameni->setFont(font7);
        tableWidget_oznameni->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_23->addWidget(tableWidget_oznameni);

        stackedWidget_palPc->addWidget(page_oznameni);

        horizontalLayout_9->addWidget(stackedWidget_palPc);


        horizontalLayout_4->addLayout(horizontalLayout_9);

        tabWidget_hlavni->addTab(tab_palPC, QString());
        tab_moznosti = new QWidget();
        tab_moznosti->setObjectName(QString::fromUtf8("tab_moznosti"));
        horizontalLayout_10 = new QHBoxLayout(tab_moznosti);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        tabWidget_moznosti = new QTabWidget(tab_moznosti);
        tabWidget_moznosti->setObjectName(QString::fromUtf8("tabWidget_moznosti"));
        tabWidget_moznosti->setEnabled(true);
        tabWidget_moznosti->setFont(font3);
        tab_moznosti_nast = new QWidget();
        tab_moznosti_nast->setObjectName(QString::fromUtf8("tab_moznosti_nast"));
        horizontalLayout_20 = new QHBoxLayout(tab_moznosti_nast);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        dateEdit = new QDateEdit(tab_moznosti_nast);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        sizePolicy3.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy3);
        dateEdit->setFont(font);

        verticalLayout_14->addWidget(dateEdit);

        pushButton_nast_dnes = new QPushButton(tab_moznosti_nast);
        pushButton_nast_dnes->setObjectName(QString::fromUtf8("pushButton_nast_dnes"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(pushButton_nast_dnes->sizePolicy().hasHeightForWidth());
        pushButton_nast_dnes->setSizePolicy(sizePolicy7);
        pushButton_nast_dnes->setFont(font);

        verticalLayout_14->addWidget(pushButton_nast_dnes);

        calendarWidget = new QCalendarWidget(tab_moznosti_nast);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        sizePolicy3.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy3);
        calendarWidget->setMinimumSize(QSize(100, 0));
        calendarWidget->setFirstDayOfWeek(Qt::Monday);
        calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        verticalLayout_14->addWidget(calendarWidget);


        horizontalLayout_6->addLayout(verticalLayout_14);

        verticalLayoutvstupniData = new QVBoxLayout();
        verticalLayoutvstupniData->setSpacing(6);
        verticalLayoutvstupniData->setObjectName(QString::fromUtf8("verticalLayoutvstupniData"));
        label_6 = new QLabel(tab_moznosti_nast);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        verticalLayoutvstupniData->addWidget(label_6);

        label_4 = new QLabel(tab_moznosti_nast);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(200, 16777215));

        verticalLayoutvstupniData->addWidget(label_4);

        label_cestaXml = new QLabel(tab_moznosti_nast);
        label_cestaXml->setObjectName(QString::fromUtf8("label_cestaXml"));
        label_cestaXml->setMaximumSize(QSize(200, 16777215));

        verticalLayoutvstupniData->addWidget(label_cestaXml);

        pushButton_nast_truncate = new QPushButton(tab_moznosti_nast);
        pushButton_nast_truncate->setObjectName(QString::fromUtf8("pushButton_nast_truncate"));
        sizePolicy2.setHeightForWidth(pushButton_nast_truncate->sizePolicy().hasHeightForWidth());
        pushButton_nast_truncate->setSizePolicy(sizePolicy2);
        pushButton_nast_truncate->setMinimumSize(QSize(0, 0));
        pushButton_nast_truncate->setFont(font);

        verticalLayoutvstupniData->addWidget(pushButton_nast_truncate);

        pushButton_nast_xmlVyberCestu = new QPushButton(tab_moznosti_nast);
        pushButton_nast_xmlVyberCestu->setObjectName(QString::fromUtf8("pushButton_nast_xmlVyberCestu"));
        pushButton_nast_xmlVyberCestu->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton_nast_xmlVyberCestu->sizePolicy().hasHeightForWidth());
        pushButton_nast_xmlVyberCestu->setSizePolicy(sizePolicy2);
        pushButton_nast_xmlVyberCestu->setMinimumSize(QSize(0, 0));
        pushButton_nast_xmlVyberCestu->setFont(font);

        verticalLayoutvstupniData->addWidget(pushButton_nast_xmlVyberCestu);

        pushButton_nast_nactiXMLropid = new QPushButton(tab_moznosti_nast);
        pushButton_nast_nactiXMLropid->setObjectName(QString::fromUtf8("pushButton_nast_nactiXMLropid"));
        pushButton_nast_nactiXMLropid->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton_nast_nactiXMLropid->sizePolicy().hasHeightForWidth());
        pushButton_nast_nactiXMLropid->setSizePolicy(sizePolicy2);
        pushButton_nast_nactiXMLropid->setMinimumSize(QSize(0, 0));
        pushButton_nast_nactiXMLropid->setFont(font);

        verticalLayoutvstupniData->addWidget(pushButton_nast_nactiXMLropid);

        progressBar_importXml = new QProgressBar(tab_moznosti_nast);
        progressBar_importXml->setObjectName(QString::fromUtf8("progressBar_importXml"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(progressBar_importXml->sizePolicy().hasHeightForWidth());
        progressBar_importXml->setSizePolicy(sizePolicy8);
        progressBar_importXml->setValue(0);

        verticalLayoutvstupniData->addWidget(progressBar_importXml);

        label_diagnostika_sql = new QLabel(tab_moznosti_nast);
        label_diagnostika_sql->setObjectName(QString::fromUtf8("label_diagnostika_sql"));

        verticalLayoutvstupniData->addWidget(label_diagnostika_sql);


        horizontalLayout_6->addLayout(verticalLayoutvstupniData);

        verticalLayoutseriovyPort = new QVBoxLayout();
        verticalLayoutseriovyPort->setSpacing(6);
        verticalLayoutseriovyPort->setObjectName(QString::fromUtf8("verticalLayoutseriovyPort"));
        label_7 = new QLabel(tab_moznosti_nast);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy9(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy9);
        label_7->setFont(font);

        verticalLayoutseriovyPort->addWidget(label_7);

        lineEdit_jmenoPortu = new QLineEdit(tab_moznosti_nast);
        lineEdit_jmenoPortu->setObjectName(QString::fromUtf8("lineEdit_jmenoPortu"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(lineEdit_jmenoPortu->sizePolicy().hasHeightForWidth());
        lineEdit_jmenoPortu->setSizePolicy(sizePolicy10);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        lineEdit_jmenoPortu->setPalette(palette4);

        verticalLayoutseriovyPort->addWidget(lineEdit_jmenoPortu);

        pushButton_nast_nastavPort = new QPushButton(tab_moznosti_nast);
        pushButton_nast_nastavPort->setObjectName(QString::fromUtf8("pushButton_nast_nastavPort"));
        sizePolicy8.setHeightForWidth(pushButton_nast_nastavPort->sizePolicy().hasHeightForWidth());
        pushButton_nast_nastavPort->setSizePolicy(sizePolicy8);
        pushButton_nast_nastavPort->setMinimumSize(QSize(0, 80));
        pushButton_nast_nastavPort->setFont(font);

        verticalLayoutseriovyPort->addWidget(pushButton_nast_nastavPort);

        pushButton_nast_odesliPrikaz = new QPushButton(tab_moznosti_nast);
        pushButton_nast_odesliPrikaz->setObjectName(QString::fromUtf8("pushButton_nast_odesliPrikaz"));
        sizePolicy8.setHeightForWidth(pushButton_nast_odesliPrikaz->sizePolicy().hasHeightForWidth());
        pushButton_nast_odesliPrikaz->setSizePolicy(sizePolicy8);
        pushButton_nast_odesliPrikaz->setMinimumSize(QSize(0, 80));
        pushButton_nast_odesliPrikaz->setFont(font);

        verticalLayoutseriovyPort->addWidget(pushButton_nast_odesliPrikaz);


        horizontalLayout_6->addLayout(verticalLayoutseriovyPort);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_12 = new QLabel(tab_moznosti_nast);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);

        horizontalLayout_2->addWidget(label_12);

        label_build = new QLabel(tab_moznosti_nast);
        label_build->setObjectName(QString::fromUtf8("label_build"));
        label_build->setFont(font3);

        horizontalLayout_2->addWidget(label_build);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_20->addLayout(verticalLayout_3);

        tabWidget_moznosti->addTab(tab_moznosti_nast, QString());
        tab_moznosti_manual = new QWidget();
        tab_moznosti_manual->setObjectName(QString::fromUtf8("tab_moznosti_manual"));
        gridLayout_8 = new QGridLayout(tab_moznosti_manual);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_diagnostika_manual = new QLabel(tab_moznosti_manual);
        label_diagnostika_manual->setObjectName(QString::fromUtf8("label_diagnostika_manual"));
        QFont font8;
        font8.setPointSize(16);
        label_diagnostika_manual->setFont(font8);

        gridLayout_8->addWidget(label_diagnostika_manual, 10, 4, 1, 1);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_11 = new QLabel(tab_moznosti_manual);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_11->addWidget(label_11);

        seznamOdberatelu = new QTableWidget(tab_moznosti_manual);
        if (seznamOdberatelu->columnCount() < 3)
            seznamOdberatelu->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        seznamOdberatelu->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        seznamOdberatelu->setObjectName(QString::fromUtf8("seznamOdberatelu"));

        verticalLayout_11->addWidget(seznamOdberatelu);

        label_15 = new QLabel(tab_moznosti_manual);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout_11->addWidget(label_15);

        seznamOdberatelu2 = new QTableWidget(tab_moznosti_manual);
        if (seznamOdberatelu2->columnCount() < 3)
            seznamOdberatelu2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        seznamOdberatelu2->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        seznamOdberatelu2->setObjectName(QString::fromUtf8("seznamOdberatelu2"));

        verticalLayout_11->addWidget(seznamOdberatelu2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pushButton_manual_removeSubscriber_2 = new QPushButton(tab_moznosti_manual);
        pushButton_manual_removeSubscriber_2->setObjectName(QString::fromUtf8("pushButton_manual_removeSubscriber_2"));
        pushButton_manual_removeSubscriber_2->setFont(font8);

        gridLayout_7->addWidget(pushButton_manual_removeSubscriber_2, 3, 1, 1, 1);

        label_13 = new QLabel(tab_moznosti_manual);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_7->addWidget(label_13, 1, 0, 1, 1);

        label_14 = new QLabel(tab_moznosti_manual);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_7->addWidget(label_14, 1, 1, 1, 1);

        pushButton_manual_removeSubscriber = new QPushButton(tab_moznosti_manual);
        pushButton_manual_removeSubscriber->setObjectName(QString::fromUtf8("pushButton_manual_removeSubscriber"));
        pushButton_manual_removeSubscriber->setFont(font8);

        gridLayout_7->addWidget(pushButton_manual_removeSubscriber, 3, 0, 1, 1);

        pushButton_manual_addsubscriber = new QPushButton(tab_moznosti_manual);
        pushButton_manual_addsubscriber->setObjectName(QString::fromUtf8("pushButton_manual_addsubscriber"));
        pushButton_manual_addsubscriber->setFont(font8);

        gridLayout_7->addWidget(pushButton_manual_addsubscriber, 2, 0, 1, 1);

        pushButton_manual_addsubscriber_2 = new QPushButton(tab_moznosti_manual);
        pushButton_manual_addsubscriber_2->setObjectName(QString::fromUtf8("pushButton_manual_addsubscriber_2"));
        pushButton_manual_addsubscriber_2->setFont(font8);

        gridLayout_7->addWidget(pushButton_manual_addsubscriber_2, 2, 1, 1, 1);

        lineEdit_strukturaOdberu = new QLineEdit(tab_moznosti_manual);
        lineEdit_strukturaOdberu->setObjectName(QString::fromUtf8("lineEdit_strukturaOdberu"));

        gridLayout_7->addWidget(lineEdit_strukturaOdberu, 0, 1, 1, 1);

        lineEdit_ipadresaOdberatele = new QLineEdit(tab_moznosti_manual);
        lineEdit_ipadresaOdberatele->setObjectName(QString::fromUtf8("lineEdit_ipadresaOdberatele"));

        gridLayout_7->addWidget(lineEdit_ipadresaOdberatele, 0, 0, 1, 1);


        verticalLayout_10->addLayout(gridLayout_7);


        verticalLayout_11->addLayout(verticalLayout_10);


        gridLayout_8->addLayout(verticalLayout_11, 8, 0, 3, 3);

        verticalLayout_28 = new QVBoxLayout();
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        label_10 = new QLabel(tab_moznosti_manual);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_28->addWidget(label_10);

        plainTextEditCustomXml = new QPlainTextEdit(tab_moznosti_manual);
        plainTextEditCustomXml->setObjectName(QString::fromUtf8("plainTextEditCustomXml"));

        verticalLayout_28->addWidget(plainTextEditCustomXml);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        pushButton_manual_odesliXml = new QPushButton(tab_moznosti_manual);
        pushButton_manual_odesliXml->setObjectName(QString::fromUtf8("pushButton_manual_odesliXml"));
        pushButton_manual_odesliXml->setFont(font);

        horizontalLayout_22->addWidget(pushButton_manual_odesliXml);

        pushButton_manual_smazOkno = new QPushButton(tab_moznosti_manual);
        pushButton_manual_smazOkno->setObjectName(QString::fromUtf8("pushButton_manual_smazOkno"));
        pushButton_manual_smazOkno->setFont(font);

        horizontalLayout_22->addWidget(pushButton_manual_smazOkno);


        verticalLayout_28->addLayout(horizontalLayout_22);


        gridLayout_8->addLayout(verticalLayout_28, 8, 4, 1, 1);

        tabWidget_moznosti->addTab(tab_moznosti_manual, QString());
        tab_moznosti_zarizeni = new QWidget();
        tab_moznosti_zarizeni->setObjectName(QString::fromUtf8("tab_moznosti_zarizeni"));
        tab_moznosti_zarizeni->setEnabled(true);
        horizontalLayout = new QHBoxLayout(tab_moznosti_zarizeni);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget_seznamZarizeni = new QTableWidget(tab_moznosti_zarizeni);
        if (tableWidget_seznamZarizeni->columnCount() < 7)
            tableWidget_seznamZarizeni->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_seznamZarizeni->setHorizontalHeaderItem(6, __qtablewidgetitem22);
        tableWidget_seznamZarizeni->setObjectName(QString::fromUtf8("tableWidget_seznamZarizeni"));
        tableWidget_seznamZarizeni->setEnabled(true);

        horizontalLayout->addWidget(tableWidget_seznamZarizeni);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(tab_moznosti_zarizeni);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(tab_moznosti_zarizeni);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(tab_moznosti_zarizeni);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout);

        tabWidget_moznosti->addTab(tab_moznosti_zarizeni, QString());

        horizontalLayout_10->addWidget(tabWidget_moznosti);

        tabWidget_hlavni->addTab(tab_moznosti, QString());
        tab_test = new QWidget();
        tab_test->setObjectName(QString::fromUtf8("tab_test"));
        horizontalLayout_5 = new QHBoxLayout(tab_test);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        pushButton_menu2_sluzby = new QPushButton(tab_test);
        pushButton_menu2_sluzby->setObjectName(QString::fromUtf8("pushButton_menu2_sluzby"));
        sizePolicy2.setHeightForWidth(pushButton_menu2_sluzby->sizePolicy().hasHeightForWidth());
        pushButton_menu2_sluzby->setSizePolicy(sizePolicy2);
        pushButton_menu2_sluzby->setMinimumSize(QSize(0, 0));
        pushButton_menu2_sluzby->setMaximumSize(QSize(200, 200));
        pushButton_menu2_sluzby->setFont(font1);
        pushButton_menu2_sluzby->setCheckable(true);
        pushButton_menu2_sluzby->setChecked(true);
        pushButton_menu2_sluzby->setAutoExclusive(true);

        verticalLayout_21->addWidget(pushButton_menu2_sluzby);

        pushButton_menu2_prubehTestu = new QPushButton(tab_test);
        pushButton_menu2_prubehTestu->setObjectName(QString::fromUtf8("pushButton_menu2_prubehTestu"));
        sizePolicy2.setHeightForWidth(pushButton_menu2_prubehTestu->sizePolicy().hasHeightForWidth());
        pushButton_menu2_prubehTestu->setSizePolicy(sizePolicy2);
        pushButton_menu2_prubehTestu->setMinimumSize(QSize(0, 0));
        pushButton_menu2_prubehTestu->setMaximumSize(QSize(200, 200));
        pushButton_menu2_prubehTestu->setFont(font1);
        pushButton_menu2_prubehTestu->setCheckable(true);
        pushButton_menu2_prubehTestu->setChecked(true);
        pushButton_menu2_prubehTestu->setAutoExclusive(true);

        verticalLayout_21->addWidget(pushButton_menu2_prubehTestu);

        pushButton_menu2_rezerva = new QPushButton(tab_test);
        pushButton_menu2_rezerva->setObjectName(QString::fromUtf8("pushButton_menu2_rezerva"));
        sizePolicy2.setHeightForWidth(pushButton_menu2_rezerva->sizePolicy().hasHeightForWidth());
        pushButton_menu2_rezerva->setSizePolicy(sizePolicy2);
        pushButton_menu2_rezerva->setMinimumSize(QSize(0, 0));
        pushButton_menu2_rezerva->setMaximumSize(QSize(200, 200));
        pushButton_menu2_rezerva->setFont(font1);
        pushButton_menu2_rezerva->setCheckable(true);
        pushButton_menu2_rezerva->setChecked(false);
        pushButton_menu2_rezerva->setAutoExclusive(true);

        verticalLayout_21->addWidget(pushButton_menu2_rezerva);

        pushButton_menu2_fullscreen = new QPushButton(tab_test);
        pushButton_menu2_fullscreen->setObjectName(QString::fromUtf8("pushButton_menu2_fullscreen"));
        sizePolicy2.setHeightForWidth(pushButton_menu2_fullscreen->sizePolicy().hasHeightForWidth());
        pushButton_menu2_fullscreen->setSizePolicy(sizePolicy2);
        pushButton_menu2_fullscreen->setMinimumSize(QSize(0, 0));
        pushButton_menu2_fullscreen->setMaximumSize(QSize(200, 200));
        pushButton_menu2_fullscreen->setFont(font1);
        pushButton_menu2_fullscreen->setCheckable(true);
        pushButton_menu2_fullscreen->setAutoExclusive(false);

        verticalLayout_21->addWidget(pushButton_menu2_fullscreen);

        pushButton_menu2_quit = new QPushButton(tab_test);
        pushButton_menu2_quit->setObjectName(QString::fromUtf8("pushButton_menu2_quit"));
        sizePolicy3.setHeightForWidth(pushButton_menu2_quit->sizePolicy().hasHeightForWidth());
        pushButton_menu2_quit->setSizePolicy(sizePolicy3);
        pushButton_menu2_quit->setMaximumSize(QSize(200, 200));
        QPalette palette5;
        pushButton_menu2_quit->setPalette(palette5);
        pushButton_menu2_quit->setFont(font1);

        verticalLayout_21->addWidget(pushButton_menu2_quit);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, verticalLayout_21);

        stackedWidget_testy = new QStackedWidget(tab_test);
        stackedWidget_testy->setObjectName(QString::fromUtf8("stackedWidget_testy"));
        page_prubehTestu = new QWidget();
        page_prubehTestu->setObjectName(QString::fromUtf8("page_prubehTestu"));
        gridLayout_5 = new QGridLayout(page_prubehTestu);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        pushButton_test1 = new QPushButton(page_prubehTestu);
        pushButton_test1->setObjectName(QString::fromUtf8("pushButton_test1"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(pushButton_test1->sizePolicy().hasHeightForWidth());
        pushButton_test1->setSizePolicy(sizePolicy11);
        pushButton_test1->setMinimumSize(QSize(0, 0));
        pushButton_test1->setMaximumSize(QSize(16777215, 50));
        pushButton_test1->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_test1);

        pushButton_test2 = new QPushButton(page_prubehTestu);
        pushButton_test2->setObjectName(QString::fromUtf8("pushButton_test2"));
        sizePolicy11.setHeightForWidth(pushButton_test2->sizePolicy().hasHeightForWidth());
        pushButton_test2->setSizePolicy(sizePolicy11);
        pushButton_test2->setMaximumSize(QSize(16777215, 50));
        pushButton_test2->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_test2);

        pushButton_test3 = new QPushButton(page_prubehTestu);
        pushButton_test3->setObjectName(QString::fromUtf8("pushButton_test3"));
        sizePolicy11.setHeightForWidth(pushButton_test3->sizePolicy().hasHeightForWidth());
        pushButton_test3->setSizePolicy(sizePolicy11);
        pushButton_test3->setMaximumSize(QSize(16777215, 50));
        pushButton_test3->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_test3);

        pushButton_test4 = new QPushButton(page_prubehTestu);
        pushButton_test4->setObjectName(QString::fromUtf8("pushButton_test4"));
        sizePolicy11.setHeightForWidth(pushButton_test4->sizePolicy().hasHeightForWidth());
        pushButton_test4->setSizePolicy(sizePolicy11);
        pushButton_test4->setMaximumSize(QSize(16777215, 50));
        pushButton_test4->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_test4);


        gridLayout_5->addLayout(horizontalLayout_13, 0, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        tableWidgetCastiTestu = new QTableWidget(page_prubehTestu);
        if (tableWidgetCastiTestu->columnCount() < 3)
            tableWidgetCastiTestu->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidgetCastiTestu->setHorizontalHeaderItem(0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidgetCastiTestu->setHorizontalHeaderItem(1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidgetCastiTestu->setHorizontalHeaderItem(2, __qtablewidgetitem25);
        tableWidgetCastiTestu->setObjectName(QString::fromUtf8("tableWidgetCastiTestu"));

        horizontalLayout_15->addWidget(tableWidgetCastiTestu);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        pushButton_startTest = new QPushButton(page_prubehTestu);
        pushButton_startTest->setObjectName(QString::fromUtf8("pushButton_startTest"));
        sizePolicy2.setHeightForWidth(pushButton_startTest->sizePolicy().hasHeightForWidth());
        pushButton_startTest->setSizePolicy(sizePolicy2);
        pushButton_startTest->setFont(font1);

        verticalLayout_22->addWidget(pushButton_startTest);

        pushButton_stopTest = new QPushButton(page_prubehTestu);
        pushButton_stopTest->setObjectName(QString::fromUtf8("pushButton_stopTest"));
        sizePolicy2.setHeightForWidth(pushButton_stopTest->sizePolicy().hasHeightForWidth());
        pushButton_stopTest->setSizePolicy(sizePolicy2);
        pushButton_stopTest->setFont(font1);

        verticalLayout_22->addWidget(pushButton_stopTest);


        horizontalLayout_15->addLayout(verticalLayout_22);


        gridLayout_5->addLayout(horizontalLayout_15, 1, 0, 1, 1);

        stackedWidget_testy->addWidget(page_prubehTestu);
        page_prepinaceSluzby = new QWidget();
        page_prepinaceSluzby->setObjectName(QString::fromUtf8("page_prepinaceSluzby"));
        gridLayout_6 = new QGridLayout(page_prepinaceSluzby);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        label_nazevSluzby = new QLabel(page_prepinaceSluzby);
        label_nazevSluzby->setObjectName(QString::fromUtf8("label_nazevSluzby"));
        label_nazevSluzby->setFont(font1);

        verticalLayout_24->addWidget(label_nazevSluzby);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        radioButton_ON1 = new QRadioButton(page_prepinaceSluzby);
        radioButton_ON1->setObjectName(QString::fromUtf8("radioButton_ON1"));
        radioButton_ON1->setMaximumSize(QSize(16777206, 16777215));
        radioButton_ON1->setFont(font1);
        radioButton_ON1->setIconSize(QSize(30, 30));

        horizontalLayout_14->addWidget(radioButton_ON1);

        radioButton_OFF1 = new QRadioButton(page_prepinaceSluzby);
        radioButton_OFF1->setObjectName(QString::fromUtf8("radioButton_OFF1"));
        radioButton_OFF1->setFont(font1);
        radioButton_OFF1->setIconSize(QSize(90, 90));

        horizontalLayout_14->addWidget(radioButton_OFF1);


        verticalLayout_24->addLayout(horizontalLayout_14);


        gridLayout_6->addLayout(verticalLayout_24, 0, 0, 1, 1);

        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        label_nazevSluzby_2 = new QLabel(page_prepinaceSluzby);
        label_nazevSluzby_2->setObjectName(QString::fromUtf8("label_nazevSluzby_2"));
        label_nazevSluzby_2->setFont(font1);

        verticalLayout_26->addWidget(label_nazevSluzby_2);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        radioButton_ON2 = new QRadioButton(page_prepinaceSluzby);
        radioButton_ON2->setObjectName(QString::fromUtf8("radioButton_ON2"));
        radioButton_ON2->setMaximumSize(QSize(16777206, 16777215));
        radioButton_ON2->setFont(font1);
        radioButton_ON2->setIconSize(QSize(30, 30));

        horizontalLayout_16->addWidget(radioButton_ON2);

        radioButton_OFF2 = new QRadioButton(page_prepinaceSluzby);
        radioButton_OFF2->setObjectName(QString::fromUtf8("radioButton_OFF2"));
        radioButton_OFF2->setFont(font1);
        radioButton_OFF2->setIconSize(QSize(90, 90));

        horizontalLayout_16->addWidget(radioButton_OFF2);


        verticalLayout_26->addLayout(horizontalLayout_16);


        gridLayout_6->addLayout(verticalLayout_26, 1, 0, 1, 1);

        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        label_nazevSluzby_3 = new QLabel(page_prepinaceSluzby);
        label_nazevSluzby_3->setObjectName(QString::fromUtf8("label_nazevSluzby_3"));
        label_nazevSluzby_3->setFont(font1);

        verticalLayout_27->addWidget(label_nazevSluzby_3);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        radioButton_ON3 = new QRadioButton(page_prepinaceSluzby);
        radioButton_ON3->setObjectName(QString::fromUtf8("radioButton_ON3"));
        radioButton_ON3->setMaximumSize(QSize(16777206, 16777215));
        radioButton_ON3->setFont(font1);
        radioButton_ON3->setIconSize(QSize(30, 30));
        radioButton_ON3->setAutoExclusive(true);

        horizontalLayout_17->addWidget(radioButton_ON3);

        radioButton_OFF3 = new QRadioButton(page_prepinaceSluzby);
        radioButton_OFF3->setObjectName(QString::fromUtf8("radioButton_OFF3"));
        radioButton_OFF3->setFont(font1);
        radioButton_OFF3->setIconSize(QSize(90, 90));

        horizontalLayout_17->addWidget(radioButton_OFF3);


        verticalLayout_27->addLayout(horizontalLayout_17);


        gridLayout_6->addLayout(verticalLayout_27, 2, 0, 1, 1);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        label_nazevSluzby_4 = new QLabel(page_prepinaceSluzby);
        label_nazevSluzby_4->setObjectName(QString::fromUtf8("label_nazevSluzby_4"));
        label_nazevSluzby_4->setFont(font1);

        verticalLayout_25->addWidget(label_nazevSluzby_4);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        radioButton_ON4 = new QRadioButton(page_prepinaceSluzby);
        radioButton_ON4->setObjectName(QString::fromUtf8("radioButton_ON4"));
        radioButton_ON4->setMaximumSize(QSize(16777206, 16777215));
        radioButton_ON4->setFont(font1);
        radioButton_ON4->setIconSize(QSize(30, 30));

        horizontalLayout_19->addWidget(radioButton_ON4);

        radioButton_OFF4 = new QRadioButton(page_prepinaceSluzby);
        radioButton_OFF4->setObjectName(QString::fromUtf8("radioButton_OFF4"));
        radioButton_OFF4->setFont(font1);
        radioButton_OFF4->setIconSize(QSize(90, 90));

        horizontalLayout_19->addWidget(radioButton_OFF4);


        verticalLayout_25->addLayout(horizontalLayout_19);


        gridLayout_6->addLayout(verticalLayout_25, 3, 0, 1, 1);

        stackedWidget_testy->addWidget(page_prepinaceSluzby);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, stackedWidget_testy);


        horizontalLayout_5->addLayout(formLayout_3);

        tabWidget_hlavni->addTab(tab_test, QString());

        horizontalLayout_21->addWidget(tabWidget_hlavni);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton_menu_linkospoj, pushButton_menu_turnus);
        QWidget::setTabOrder(pushButton_menu_turnus, pushButton_menu_jizda);
        QWidget::setTabOrder(pushButton_menu_jizda, pushButton_menu_fullscreen);
        QWidget::setTabOrder(pushButton_menu_fullscreen, pushButton_menu_quit);
        QWidget::setTabOrder(pushButton_menu_quit, pushButton_jizda_sipkaDal);
        QWidget::setTabOrder(pushButton_jizda_sipkaDal, listLinek);
        QWidget::setTabOrder(listLinek, listSpoje);
        QWidget::setTabOrder(listSpoje, pushButton_prikaz);
        QWidget::setTabOrder(pushButton_prikaz, polelinky);
        QWidget::setTabOrder(polelinky, poleLinkyTurnus);
        QWidget::setTabOrder(poleLinkyTurnus, poleSpojeTurnus);
        QWidget::setTabOrder(poleSpojeTurnus, checkBox_4);
        QWidget::setTabOrder(checkBox_4, listKmenovychLinek);
        QWidget::setTabOrder(listKmenovychLinek, listPoradi);
        QWidget::setTabOrder(listPoradi, listTurnusSpoje);
        QWidget::setTabOrder(listTurnusSpoje, pushButton_menu2_sluzby);
        QWidget::setTabOrder(pushButton_menu2_sluzby, pushButton_menu2_rezerva);
        QWidget::setTabOrder(pushButton_menu2_rezerva, pushButton_menu2_fullscreen);
        QWidget::setTabOrder(pushButton_menu2_fullscreen, pushButton_menu2_quit);
        QWidget::setTabOrder(pushButton_menu2_quit, polespoje);
        QWidget::setTabOrder(polespoje, radioButton_OFF1);
        QWidget::setTabOrder(radioButton_OFF1, radioButton_ON1);
        QWidget::setTabOrder(radioButton_ON1, radioButton_ON2);
        QWidget::setTabOrder(radioButton_ON2, radioButton_OFF2);
        QWidget::setTabOrder(radioButton_OFF2, radioButton_ON3);
        QWidget::setTabOrder(radioButton_ON3, radioButton_OFF3);

        retranslateUi(MainWindow);

        tabWidget_hlavni->setCurrentIndex(0);
        stackedWidget_palPc->setCurrentIndex(0);
        tabWidget_moznosti->setCurrentIndex(0);
        stackedWidget_testy->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VDV301 Tester", nullptr));
        pushButton_menu_linkospoj->setText(QCoreApplication::translate("MainWindow", "Linka\n"
"/spoj", nullptr));
        pushButton_menu_turnus->setText(QCoreApplication::translate("MainWindow", "Turnus", nullptr));
        pushButton_menu_jizda->setText(QCoreApplication::translate("MainWindow", "J\303\255zda", nullptr));
        pushButton_menu_oznameni->setText(QCoreApplication::translate("MainWindow", "spec. \n"
"hl\303\241\305\241en\303\255", nullptr));
        pushButton_menu_fullscreen->setText(QCoreApplication::translate("MainWindow", "Fullscr.", nullptr));
        pushButton_menu_quit->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        label_aktLinka->setText(QCoreApplication::translate("MainWindow", "Linka", nullptr));
        label_aktSpoj->setText(QCoreApplication::translate("MainWindow", "Spoj", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetNasledujiciZastavky->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "jmeno", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetNasledujiciZastavky->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "index", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetNasledujiciZastavky->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "cas", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetNasledujiciZastavky->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "znam", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetNasledujiciZastavky->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "p\303\241sma", nullptr));
        radioButton_singleDoorOpen->setText(QCoreApplication::translate("MainWindow", "SingleDoorOpen", nullptr));
        radioButton_allDoorsClosed->setText(QCoreApplication::translate("MainWindow", "AllDoorsClosed", nullptr));
        radioButton_doorsOpen->setText(QCoreApplication::translate("MainWindow", "DoorsOpen", nullptr));
        radioButton_singleDoorCloser->setText(QCoreApplication::translate("MainWindow", "SingleDoorClosed", nullptr));
        pushButton_jizda_sipkaZpetSkok->setText(QCoreApplication::translate("MainWindow", "\342\226\262\n"
"\342\226\262", nullptr));
        pushButton_jizda_sipkaZpet->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        pushButton_jizda_sipkaDal->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        pushButton_jizda_sipkaDalSkok->setText(QCoreApplication::translate("MainWindow", "\342\226\274\n"
"\342\226\274", nullptr));
        popisek->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_jizda_beforeStop->setText(QCoreApplication::translate("MainWindow", "Before\n"
"Stop", nullptr));
        pushButton_jizda_atStop->setText(QCoreApplication::translate("MainWindow", "At\n"
"Stop", nullptr));
        pushButton_jizda_afterStop->setText(QCoreApplication::translate("MainWindow", "After\n"
"Stop", nullptr));
        pushButton_jizda_betweenStop->setText(QCoreApplication::translate("MainWindow", "Between\n"
"Stop", nullptr));
        locationStateIndicator->setText(QCoreApplication::translate("MainWindow", "locationState", nullptr));
        pushButton_jizda_IBIS->setText(QCoreApplication::translate("MainWindow", "IBIS", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "StopRequested", nullptr));
        pushButton_prikaz->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Linka</span></p></body></html>", nullptr));
        polelinky->setText(QCoreApplication::translate("MainWindow", "100952", nullptr));
        polespoje->setText(QCoreApplication::translate("MainWindow", "1001", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Spoj", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Seznam linek", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Seznam spoj\305\257", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "MPV p\305\231estupy", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Linka</span></p></body></html>", nullptr));
        poleLinkyTurnus->setText(QCoreApplication::translate("MainWindow", "100952", nullptr));
        poleSpojeTurnus->setText(QCoreApplication::translate("MainWindow", "1001", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Spoj", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "StopRequested", nullptr));
        checkBox_MpvTurnusy->setText(QCoreApplication::translate("MainWindow", "MPV p\305\231estupy", nullptr));
        pushButton_turnus_prikaz->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Kmenov\303\241 linka", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Po\305\231ad\303\255", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Spoje", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_oznameni->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "N\303\241zev", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_oznameni->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "AnnouncementType", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_oznameni->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Nadpis", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_oznameni->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "MP3", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_oznameni->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Text", nullptr));
        tabWidget_hlavni->setTabText(tabWidget_hlavni->indexOf(tab_palPC), QCoreApplication::translate("MainWindow", "PalPC", nullptr));
        pushButton_nast_dnes->setText(QCoreApplication::translate("MainWindow", "DNES", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Vstupn\303\255 data", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "cesta k souboru", nullptr));
        label_cestaXml->setText(QCoreApplication::translate("MainWindow", "cesta_obsah", nullptr));
        pushButton_nast_truncate->setText(QCoreApplication::translate("MainWindow", "Vymazat DB", nullptr));
        pushButton_nast_xmlVyberCestu->setText(QCoreApplication::translate("MainWindow", "XML cesta", nullptr));
        pushButton_nast_nactiXMLropid->setText(QCoreApplication::translate("MainWindow", "na\304\215ten\303\255 XML", nullptr));
        label_diagnostika_sql->setText(QCoreApplication::translate("MainWindow", "Diagnostick\303\275 \305\231\303\241dek importu dat", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "S\303\251riov\303\275 port IBIS", nullptr));
        lineEdit_jmenoPortu->setText(QCoreApplication::translate("MainWindow", "ttyUSB0", nullptr));
        pushButton_nast_nastavPort->setText(QCoreApplication::translate("MainWindow", "nastav port", nullptr));
        pushButton_nast_odesliPrikaz->setText(QCoreApplication::translate("MainWindow", "ode\305\241li\n"
" testovac\303\255 p\305\231\303\255kaz", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "build", nullptr));
        label_build->setText(QCoreApplication::translate("MainWindow", "cisloBuildu", nullptr));
        tabWidget_moznosti->setTabText(tabWidget_moznosti->indexOf(tab_moznosti_nast), QCoreApplication::translate("MainWindow", "Nast.", nullptr));
        label_diagnostika_manual->setText(QCoreApplication::translate("MainWindow", "subscribe diagnostika", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Odberatele 1.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = seznamOdberatelu->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Adresa", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = seznamOdberatelu->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Struktura", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = seznamOdberatelu->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Interval", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Odberatele V2.2CZ1.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = seznamOdberatelu2->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Adresa", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = seznamOdberatelu2->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Struktura", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = seznamOdberatelu2->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Interval", nullptr));
        pushButton_manual_removeSubscriber_2->setText(QCoreApplication::translate("MainWindow", "Zrusit odber", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "V1.0", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "V2.2CZ1.0", nullptr));
        pushButton_manual_removeSubscriber->setText(QCoreApplication::translate("MainWindow", "Zrusit odber", nullptr));
        pushButton_manual_addsubscriber->setText(QCoreApplication::translate("MainWindow", "P\305\231idat odb\304\233ratele", nullptr));
        pushButton_manual_addsubscriber_2->setText(QCoreApplication::translate("MainWindow", "P\305\231idat odb\304\233ratele", nullptr));
        lineEdit_strukturaOdberu->setText(QCoreApplication::translate("MainWindow", "AllData", nullptr));
        lineEdit_ipadresaOdberatele->setText(QCoreApplication::translate("MainWindow", "http://127.0.0.1:48479", nullptr));
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
        pushButton_manual_odesliXml->setText(QCoreApplication::translate("MainWindow", "odeslat\n"
" na panely", nullptr));
        pushButton_manual_smazOkno->setText(QCoreApplication::translate("MainWindow", "vymazat\n"
" okno", nullptr));
        tabWidget_moznosti->setTabText(tabWidget_moznosti->indexOf(tab_moznosti_manual), QCoreApplication::translate("MainWindow", "Manual", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_seznamZarizeni->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "DeviceClass", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_seznamZarizeni->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_seznamZarizeni->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Hostname", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_seznamZarizeni->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_seznamZarizeni->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "port", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_seznamZarizeni->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "serviceName", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_seznamZarizeni->horizontalHeaderItem(6);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "verze", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget_moznosti->setTabText(tabWidget_moznosti->indexOf(tab_moznosti_zarizeni), QCoreApplication::translate("MainWindow", "Detekce za\305\231\303\255zen\303\255", nullptr));
        tabWidget_hlavni->setTabText(tabWidget_hlavni->indexOf(tab_moznosti), QCoreApplication::translate("MainWindow", "Mo\305\276nosti", nullptr));
        pushButton_menu2_sluzby->setText(QCoreApplication::translate("MainWindow", "Slu\305\276by", nullptr));
        pushButton_menu2_prubehTestu->setText(QCoreApplication::translate("MainWindow", "Pr\305\257beh\n"
" testu", nullptr));
        pushButton_menu2_rezerva->setText(QCoreApplication::translate("MainWindow", "xx", nullptr));
        pushButton_menu2_fullscreen->setText(QCoreApplication::translate("MainWindow", "Fullscr.", nullptr));
        pushButton_menu2_quit->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        pushButton_test1->setText(QCoreApplication::translate("MainWindow", "Vzorov\303\275 test", nullptr));
        pushButton_test2->setText(QCoreApplication::translate("MainWindow", "Test odberu", nullptr));
        pushButton_test3->setText(QCoreApplication::translate("MainWindow", "Test Bonjour", nullptr));
        pushButton_test4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidgetCastiTestu->horizontalHeaderItem(0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "N\303\241zev \304\215\303\241sti testu", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidgetCastiTestu->horizontalHeaderItem(1);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Pr\305\257b\304\233h", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidgetCastiTestu->horizontalHeaderItem(2);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "V\303\275sledek", nullptr));
        pushButton_startTest->setText(QCoreApplication::translate("MainWindow", "Spustit\n"
" test", nullptr));
        pushButton_stopTest->setText(QCoreApplication::translate("MainWindow", "Zastavit\n"
"test", nullptr));
        label_nazevSluzby->setText(QCoreApplication::translate("MainWindow", "Customer Informaton Service 2.2CZ1.0", nullptr));
        radioButton_ON1->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        radioButton_OFF1->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        label_nazevSluzby_2->setText(QCoreApplication::translate("MainWindow", "DeviceManagementService 1.0", nullptr));
        radioButton_ON2->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        radioButton_OFF2->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        label_nazevSluzby_3->setText(QCoreApplication::translate("MainWindow", "TicketValidationService 2.2CZ1.0", nullptr));
        radioButton_ON3->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        radioButton_OFF3->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        label_nazevSluzby_4->setText(QCoreApplication::translate("MainWindow", "Customer Informaton Service 1.0", nullptr));
        radioButton_ON4->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        radioButton_OFF4->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        tabWidget_hlavni->setTabText(tabWidget_hlavni->indexOf(tab_test), QCoreApplication::translate("MainWindow", "Testov\303\241n\303\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
