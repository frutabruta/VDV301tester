/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
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
    QVBoxLayout *verticalLayout_5;
    QPushButton *BeforeStop;
    QPushButton *AtStop_2;
    QPushButton *AfterStop;
    QPushButton *BetweenStop;
    QLabel *locationStateIndicator;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QWidget *page_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
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
        centralWidget->setAutoFillBackground(false);
        prepinadloStran = new QStackedWidget(centralWidget);
        prepinadloStran->setObjectName(QString::fromUtf8("prepinadloStran"));
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        prepinadloStran->setPalette(palette);
        prepinadloStran->setStyleSheet(QString::fromUtf8("background-color:rgb(52, 101, 164);"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayoutWidget_2 = new QWidget(page);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 300, 481, 115));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 20, -1);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        NazevVysledku = new QLabel(horizontalLayoutWidget_2);
        NazevVysledku->setObjectName(QString::fromUtf8("NazevVysledku"));

        verticalLayout_2->addWidget(NazevVysledku);

        pripojeniTlacitko = new QPushButton(horizontalLayoutWidget_2);
        pripojeniTlacitko->setObjectName(QString::fromUtf8("pripojeniTlacitko"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pripojeniTlacitko->sizePolicy().hasHeightForWidth());
        pripojeniTlacitko->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(pripojeniTlacitko);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        polelinky = new QLineEdit(horizontalLayoutWidget_2);
        polelinky->setObjectName(QString::fromUtf8("polelinky"));

        horizontalLayout_2->addWidget(polelinky);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        polespoje = new QLineEdit(horizontalLayoutWidget_2);
        polespoje->setObjectName(QString::fromUtf8("polespoje"));

        horizontalLayout_4->addWidget(polespoje);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout_3);

        prikaztlacitko = new QPushButton(horizontalLayoutWidget_2);
        prikaztlacitko->setObjectName(QString::fromUtf8("prikaztlacitko"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(prikaztlacitko->sizePolicy().hasHeightForWidth());
        prikaztlacitko->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(prikaztlacitko);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        popisek = new QLabel(horizontalLayoutWidget_2);
        popisek->setObjectName(QString::fromUtf8("popisek"));
        QFont font;
        font.setPointSize(24);
        popisek->setFont(font);
        popisek->setTextFormat(Qt::PlainText);
        popisek->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(popisek);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        pridatTlacitko = new QPushButton(horizontalLayoutWidget_2);
        pridatTlacitko->setObjectName(QString::fromUtf8("pridatTlacitko"));
        pridatTlacitko->setEnabled(true);
        sizePolicy1.setHeightForWidth(pridatTlacitko->sizePolicy().hasHeightForWidth());
        pridatTlacitko->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(14);
        pridatTlacitko->setFont(font1);

        verticalLayout->addWidget(pridatTlacitko);

        ubratTlacitko = new QPushButton(horizontalLayoutWidget_2);
        ubratTlacitko->setObjectName(QString::fromUtf8("ubratTlacitko"));
        sizePolicy1.setHeightForWidth(ubratTlacitko->sizePolicy().hasHeightForWidth());
        ubratTlacitko->setSizePolicy(sizePolicy1);
        ubratTlacitko->setFont(font1);

        verticalLayout->addWidget(ubratTlacitko);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(horizontalLayout);

        prikazovyvysledek = new QLabel(page);
        prikazovyvysledek->setObjectName(QString::fromUtf8("prikazovyvysledek"));
        prikazovyvysledek->setGeometry(QRect(10, 10, 571, 291));
        QFont font2;
        font2.setPointSize(33);
        prikazovyvysledek->setFont(font2);
        prikazovyvysledek->setAutoFillBackground(false);
        prikazovyvysledek->setStyleSheet(QString::fromUtf8("background-color:rgb(32, 74, 135);\n"
"color: rgb(238, 238, 236);"));
        prikazovyvysledek->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(600, 10, 191, 291));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        sipkaNahoru = new QPushButton(horizontalLayoutWidget);
        sipkaNahoru->setObjectName(QString::fromUtf8("sipkaNahoru"));
        sizePolicy2.setHeightForWidth(sipkaNahoru->sizePolicy().hasHeightForWidth());
        sipkaNahoru->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(sipkaNahoru);

        sipkaDolu = new QPushButton(horizontalLayoutWidget);
        sipkaDolu->setObjectName(QString::fromUtf8("sipkaDolu"));
        sizePolicy1.setHeightForWidth(sipkaDolu->sizePolicy().hasHeightForWidth());
        sipkaDolu->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(sipkaDolu);

        quitTlacitko = new QPushButton(horizontalLayoutWidget);
        quitTlacitko->setObjectName(QString::fromUtf8("quitTlacitko"));
        sizePolicy2.setHeightForWidth(quitTlacitko->sizePolicy().hasHeightForWidth());
        quitTlacitko->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(quitTlacitko);

        tlacitkoNavic = new QPushButton(horizontalLayoutWidget);
        tlacitkoNavic->setObjectName(QString::fromUtf8("tlacitkoNavic"));

        verticalLayout_4->addWidget(tlacitkoNavic);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        BeforeStop = new QPushButton(horizontalLayoutWidget);
        BeforeStop->setObjectName(QString::fromUtf8("BeforeStop"));
        sizePolicy1.setHeightForWidth(BeforeStop->sizePolicy().hasHeightForWidth());
        BeforeStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(BeforeStop);

        AtStop_2 = new QPushButton(horizontalLayoutWidget);
        AtStop_2->setObjectName(QString::fromUtf8("AtStop_2"));
        sizePolicy1.setHeightForWidth(AtStop_2->sizePolicy().hasHeightForWidth());
        AtStop_2->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(AtStop_2);

        AfterStop = new QPushButton(horizontalLayoutWidget);
        AfterStop->setObjectName(QString::fromUtf8("AfterStop"));
        sizePolicy1.setHeightForWidth(AfterStop->sizePolicy().hasHeightForWidth());
        AfterStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(AfterStop);

        BetweenStop = new QPushButton(horizontalLayoutWidget);
        BetweenStop->setObjectName(QString::fromUtf8("BetweenStop"));
        sizePolicy1.setHeightForWidth(BetweenStop->sizePolicy().hasHeightForWidth());
        BetweenStop->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(BetweenStop);

        locationStateIndicator = new QLabel(horizontalLayoutWidget);
        locationStateIndicator->setObjectName(QString::fromUtf8("locationStateIndicator"));

        verticalLayout_5->addWidget(locationStateIndicator);


        horizontalLayout_5->addLayout(verticalLayout_5);

        verticalLayoutWidget_2 = new QWidget(page);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(490, 300, 160, 112));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_6->addWidget(radioButton);

        radioButton_2 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_6->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_6->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(verticalLayoutWidget_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_6->addWidget(radioButton_4);

        verticalLayoutWidget_3 = new QWidget(page);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(650, 330, 160, 80));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(verticalLayoutWidget_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_7->addWidget(checkBox);

        checkBox_2 = new QCheckBox(verticalLayoutWidget_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_7->addWidget(checkBox_2);

        prepinadloStran->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayoutWidget = new QWidget(page_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(490, 70, 299, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        prepinadloStran->addWidget(page_2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 800, 22));
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

        prepinadloStran->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Stav p\305\231ipojen\303\255:", nullptr));
        NazevVysledku->setText(QCoreApplication::translate("MainWindow", "stav pripojeni", nullptr));
        pripojeniTlacitko->setText(QCoreApplication::translate("MainWindow", "SQL Connect", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Linka</span></p></body></html>", nullptr));
        polelinky->setText(QCoreApplication::translate("MainWindow", "820741", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Spoj", nullptr));
        polespoje->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        prikaztlacitko->setText(QCoreApplication::translate("MainWindow", "POTVRDIT", nullptr));
        popisek->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pridatTlacitko->setText(QCoreApplication::translate("MainWindow", "P\305\231idat", nullptr));
        ubratTlacitko->setText(QCoreApplication::translate("MainWindow", "Ubrat", nullptr));
        prikazovyvysledek->setText(QCoreApplication::translate("MainWindow", "seznam zastavek", nullptr));
        sipkaNahoru->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        sipkaDolu->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        quitTlacitko->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        tlacitkoNavic->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
        BeforeStop->setText(QCoreApplication::translate("MainWindow", "BeforeStop", nullptr));
        AtStop_2->setText(QCoreApplication::translate("MainWindow", "AtStop", nullptr));
        AfterStop->setText(QCoreApplication::translate("MainWindow", "AfterStop", nullptr));
        BetweenStop->setText(QCoreApplication::translate("MainWindow", "BetweenStop", nullptr));
        locationStateIndicator->setText(QCoreApplication::translate("MainWindow", "locationState", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "DoorsOpen", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "AllDoorsClosed", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "SingleDoorOpen", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "SingleDoorClosed", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "MPV p\305\231estupy", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "StopRequested", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
