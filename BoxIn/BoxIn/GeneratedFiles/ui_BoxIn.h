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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
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
    QLineEdit *commandLine;
    QLabel *commandLabel;
    QListWidget *displayFeedToday;
    QLabel *feedbackBox;
    QPushButton *buttonExit;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *todayLabel;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoxInClass)
    {
        if (BoxInClass->objectName().isEmpty())
            BoxInClass->setObjectName(QStringLiteral("BoxInClass"));
        BoxInClass->resize(800, 600);
        BoxInClass->setMinimumSize(QSize(800, 600));
        BoxInClass->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setItalic(false);
        BoxInClass->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("BoxIn.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        BoxInClass->setWindowIcon(icon);
        BoxInClass->setWindowOpacity(1);
        centralWidget = new QWidget(BoxInClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        commandLine = new QLineEdit(centralWidget);
        commandLine->setObjectName(QStringLiteral("commandLine"));
        commandLine->setGeometry(QRect(60, 490, 800, 20));
        commandLabel = new QLabel(centralWidget);
        commandLabel->setObjectName(QStringLiteral("commandLabel"));
        commandLabel->setGeometry(QRect(0, 490, 60, 20));
        displayFeedToday = new QListWidget(centralWidget);
        displayFeedToday->setObjectName(QStringLiteral("displayFeedToday"));
        displayFeedToday->setGeometry(QRect(20, 40, 180, 250));
        displayFeedToday->setUniformItemSizes(true);
        feedbackBox = new QLabel(centralWidget);
        feedbackBox->setObjectName(QStringLiteral("feedbackBox"));
        feedbackBox->setGeometry(QRect(0, 460, 800, 20));
        feedbackBox->setAlignment(Qt::AlignCenter);
        feedbackBox->setIndent(0);
        buttonExit = new QPushButton(centralWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        buttonExit->setGeometry(QRect(0, 520, 800, 20));
        buttonExit->setMaximumSize(QSize(800, 16777215));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(220, 40, 180, 250));
        listWidget_2 = new QListWidget(centralWidget);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(420, 40, 180, 250));
        todayLabel = new QLabel(centralWidget);
        todayLabel->setObjectName(QStringLiteral("todayLabel"));
        todayLabel->setGeometry(QRect(20, 20, 180, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 20, 180, 20));
        BoxInClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoxInClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        BoxInClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoxInClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoxInClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoxInClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoxInClass->setStatusBar(statusBar);

        retranslateUi(BoxInClass);

        QMetaObject::connectSlotsByName(BoxInClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoxInClass)
    {
        BoxInClass->setWindowTitle(QApplication::translate("BoxInClass", "BoxIn v0.1", 0));
        commandLabel->setText(QApplication::translate("BoxInClass", "  Command:", 0));
        feedbackBox->setText(QApplication::translate("BoxInClass", "Welcome to BoxIn v0.1", 0));
        buttonExit->setText(QApplication::translate("BoxInClass", "Exit", 0));
        todayLabel->setText(QApplication::translate("BoxInClass", "<html><head/><body><p align=\"center\">Today</p></body></html>", 0));
        label->setText(QApplication::translate("BoxInClass", "<html><head/><body><p align=\"center\">Upcoming</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class BoxInClass: public Ui_BoxInClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXIN_H
