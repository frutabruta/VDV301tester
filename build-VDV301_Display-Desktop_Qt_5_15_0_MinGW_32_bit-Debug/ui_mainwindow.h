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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiontestPolozka;
    QAction *actionstahnoutXML;
    QAction *action;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *Llinka;
    QLabel *Lcil;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QLabel *sipka;
    QVBoxLayout *verticalLayout_2;
    QLabel *Lnacestna4;
    QLabel *Lnacestna3;
    QLabel *Lnacestna2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Lnacestna1;
    QLabel *label_6;
    QPushButton *refreshTlac;
    QMenuBar *menuBar;
    QMenu *menunacti;
    QMenu *menukonec;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(834, 484);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actiontestPolozka = new QAction(MainWindow);
        actiontestPolozka->setObjectName(QString::fromUtf8("actiontestPolozka"));
        actionstahnoutXML = new QAction(MainWindow);
        actionstahnoutXML->setObjectName(QString::fromUtf8("actionstahnoutXML"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Llinka = new QLabel(centralWidget);
        Llinka->setObjectName(QString::fromUtf8("Llinka"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Llinka->sizePolicy().hasHeightForWidth());
        Llinka->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(30);
        Llinka->setFont(font);
        Llinka->setAutoFillBackground(false);

        horizontalLayout->addWidget(Llinka);

        Lcil = new QLabel(centralWidget);
        Lcil->setObjectName(QString::fromUtf8("Lcil"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Lcil->sizePolicy().hasHeightForWidth());
        Lcil->setSizePolicy(sizePolicy2);
        Lcil->setFont(font);
        Lcil->setAutoFillBackground(false);

        horizontalLayout->addWidget(Lcil);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sipka = new QLabel(centralWidget);
        sipka->setObjectName(QString::fromUtf8("sipka"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sipka->sizePolicy().hasHeightForWidth());
        sipka->setSizePolicy(sizePolicy3);
        sipka->setMaximumSize(QSize(50, 16777215));
        QFont font1;
        font1.setPointSize(70);
        sipka->setFont(font1);
        sipka->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(sipka);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Lnacestna4 = new QLabel(centralWidget);
        Lnacestna4->setObjectName(QString::fromUtf8("Lnacestna4"));
        sizePolicy.setHeightForWidth(Lnacestna4->sizePolicy().hasHeightForWidth());
        Lnacestna4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(20);
        Lnacestna4->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna4);

        Lnacestna3 = new QLabel(centralWidget);
        Lnacestna3->setObjectName(QString::fromUtf8("Lnacestna3"));
        sizePolicy.setHeightForWidth(Lnacestna3->sizePolicy().hasHeightForWidth());
        Lnacestna3->setSizePolicy(sizePolicy);
        Lnacestna3->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna3);

        Lnacestna2 = new QLabel(centralWidget);
        Lnacestna2->setObjectName(QString::fromUtf8("Lnacestna2"));
        sizePolicy.setHeightForWidth(Lnacestna2->sizePolicy().hasHeightForWidth());
        Lnacestna2->setSizePolicy(sizePolicy);
        Lnacestna2->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Lnacestna1 = new QLabel(centralWidget);
        Lnacestna1->setObjectName(QString::fromUtf8("Lnacestna1"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Lnacestna1->sizePolicy().hasHeightForWidth());
        Lnacestna1->setSizePolicy(sizePolicy4);
        Lnacestna1->setFont(font);
        Lnacestna1->setScaledContents(false);

        horizontalLayout_2->addWidget(Lnacestna1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);

        horizontalLayout_2->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_2);

        refreshTlac = new QPushButton(centralWidget);
        refreshTlac->setObjectName(QString::fromUtf8("refreshTlac"));

        verticalLayout->addWidget(refreshTlac);


        horizontalLayout_4->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 834, 22));
        menuBar->setNativeMenuBar(false);
        menunacti = new QMenu(menuBar);
        menunacti->setObjectName(QString::fromUtf8("menunacti"));
        menukonec = new QMenu(menuBar);
        menukonec->setObjectName(QString::fromUtf8("menukonec"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy6);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menunacti->menuAction());
        menuBar->addAction(menukonec->menuAction());
        menunacti->addAction(actiontestPolozka);
        menunacti->addAction(actionstahnoutXML);
        menunacti->addAction(action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiontestPolozka->setText(QCoreApplication::translate("MainWindow", "testPolozka", nullptr));
        actionstahnoutXML->setText(QCoreApplication::translate("MainWindow", "stahnoutXML", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        Llinka->setText(QCoreApplication::translate("MainWindow", "741", nullptr));
        Lcil->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#3465a4;\">Sportovni hala</span></p></body></html>", nullptr));
        sipka->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        Lnacestna4->setText(QCoreApplication::translate("MainWindow", "Dalsi 3", nullptr));
        Lnacestna3->setText(QCoreApplication::translate("MainWindow", "Dalsi 2", nullptr));
        Lnacestna2->setText(QCoreApplication::translate("MainWindow", "Dalsi 1", nullptr));
        Lnacestna1->setText(QCoreApplication::translate("MainWindow", "PristiZastavka", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        refreshTlac->setText(QCoreApplication::translate("MainWindow", "refresh", nullptr));
        menunacti->setTitle(QCoreApplication::translate("MainWindow", "nacti", nullptr));
        menukonec->setTitle(QCoreApplication::translate("MainWindow", "konec", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
