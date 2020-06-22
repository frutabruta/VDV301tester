/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(834, 484);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actiontestPolozka = new QAction(MainWindow);
        actiontestPolozka->setObjectName(QStringLiteral("actiontestPolozka"));
        actionstahnoutXML = new QAction(MainWindow);
        actionstahnoutXML->setObjectName(QStringLiteral("actionstahnoutXML"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Llinka = new QLabel(centralWidget);
        Llinka->setObjectName(QStringLiteral("Llinka"));
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
        Lcil->setObjectName(QStringLiteral("Lcil"));
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
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        sipka = new QLabel(centralWidget);
        sipka->setObjectName(QStringLiteral("sipka"));
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
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Lnacestna4 = new QLabel(centralWidget);
        Lnacestna4->setObjectName(QStringLiteral("Lnacestna4"));
        sizePolicy.setHeightForWidth(Lnacestna4->sizePolicy().hasHeightForWidth());
        Lnacestna4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(20);
        Lnacestna4->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna4);

        Lnacestna3 = new QLabel(centralWidget);
        Lnacestna3->setObjectName(QStringLiteral("Lnacestna3"));
        sizePolicy.setHeightForWidth(Lnacestna3->sizePolicy().hasHeightForWidth());
        Lnacestna3->setSizePolicy(sizePolicy);
        Lnacestna3->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna3);

        Lnacestna2 = new QLabel(centralWidget);
        Lnacestna2->setObjectName(QStringLiteral("Lnacestna2"));
        sizePolicy.setHeightForWidth(Lnacestna2->sizePolicy().hasHeightForWidth());
        Lnacestna2->setSizePolicy(sizePolicy);
        Lnacestna2->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Lnacestna1 = new QLabel(centralWidget);
        Lnacestna1->setObjectName(QStringLiteral("Lnacestna1"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Lnacestna1->sizePolicy().hasHeightForWidth());
        Lnacestna1->setSizePolicy(sizePolicy4);
        Lnacestna1->setFont(font);
        Lnacestna1->setScaledContents(false);

        horizontalLayout_2->addWidget(Lnacestna1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);

        horizontalLayout_2->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_2);

        refreshTlac = new QPushButton(centralWidget);
        refreshTlac->setObjectName(QStringLiteral("refreshTlac"));

        verticalLayout->addWidget(refreshTlac);


        horizontalLayout_4->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 834, 22));
        menuBar->setNativeMenuBar(false);
        menunacti = new QMenu(menuBar);
        menunacti->setObjectName(QStringLiteral("menunacti"));
        menukonec = new QMenu(menuBar);
        menukonec->setObjectName(QStringLiteral("menukonec"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
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
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actiontestPolozka->setText(QApplication::translate("MainWindow", "testPolozka", Q_NULLPTR));
        actionstahnoutXML->setText(QApplication::translate("MainWindow", "stahnoutXML", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "QUIT", Q_NULLPTR));
        Llinka->setText(QApplication::translate("MainWindow", "741", Q_NULLPTR));
        Lcil->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#3465a4;\">Sportovni hala</span></p></body></html>", Q_NULLPTR));
        sipka->setText(QApplication::translate("MainWindow", "\342\206\221", Q_NULLPTR));
        Lnacestna4->setText(QApplication::translate("MainWindow", "Dalsi 3", Q_NULLPTR));
        Lnacestna3->setText(QApplication::translate("MainWindow", "Dalsi 2", Q_NULLPTR));
        Lnacestna2->setText(QApplication::translate("MainWindow", "Dalsi 1", Q_NULLPTR));
        Lnacestna1->setText(QApplication::translate("MainWindow", "PristiZastavka", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "STOP", Q_NULLPTR));
        refreshTlac->setText(QApplication::translate("MainWindow", "refresh", Q_NULLPTR));
        menunacti->setTitle(QApplication::translate("MainWindow", "nacti", Q_NULLPTR));
        menukonec->setTitle(QApplication::translate("MainWindow", "konec", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
