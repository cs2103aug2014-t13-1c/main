/********************************************************************************
** Form generated from reading UI file 'BoxIn.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOXIN_H
#define UI_BOXIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoxInClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *buttonExit;
    QLineEdit *commandLine;
    QLabel *label;
    QListWidget *displayFeed;
    QLabel *feedbackBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoxInClass)
    {
        if (BoxInClass->objectName().isEmpty())
            BoxInClass->setObjectName(QStringLiteral("BoxInClass"));
        BoxInClass->resize(600, 400);
        centralWidget = new QWidget(BoxInClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 320, 601, 25));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonExit = new QPushButton(gridLayoutWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));

        gridLayout->addWidget(buttonExit, 0, 0, 1, 1);

        commandLine = new QLineEdit(centralWidget);
        commandLine->setObjectName(QStringLiteral("commandLine"));
        commandLine->setGeometry(QRect(60, 300, 541, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 300, 61, 16));
        displayFeed = new QListWidget(centralWidget);
        displayFeed->setObjectName(QStringLiteral("displayFeed"));
        displayFeed->setGeometry(QRect(0, 0, 601, 271));
        feedbackBox = new QLabel(centralWidget);
        feedbackBox->setObjectName(QStringLiteral("feedbackBox"));
        feedbackBox->setGeometry(QRect(0, 270, 601, 31));
        BoxInClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoxInClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        BoxInClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoxInClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoxInClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoxInClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoxInClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(BoxInClass);

        QMetaObject::connectSlotsByName(BoxInClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoxInClass)
    {
        BoxInClass->setWindowTitle(QApplication::translate("BoxInClass", "BoxIn", 0));
        buttonExit->setText(QApplication::translate("BoxInClass", "Exit", 0));
        label->setText(QApplication::translate("BoxInClass", "  Command:", 0));
        feedbackBox->setText(QApplication::translate("BoxInClass", "<html><head/><body><p align=\"center\">Welcome to Task Manager v0.1</p></body></html>", 0));
        menuFile->setTitle(QApplication::translate("BoxInClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class BoxInClass: public Ui_BoxInClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXIN_H
