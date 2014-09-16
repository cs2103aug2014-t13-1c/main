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
    QLineEdit *commandLine;
    QLabel *commandLabel;
    QListWidget *displayFeed;
    QLabel *feedbackBox;
    QPushButton *buttonExit;
    QMenuBar *menuBar;
    QMenu *menuFile;
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
        displayFeed = new QListWidget(centralWidget);
        displayFeed->setObjectName(QStringLiteral("displayFeed"));
        displayFeed->setGeometry(QRect(0, 0, 191, 251));
        feedbackBox = new QLabel(centralWidget);
        feedbackBox->setObjectName(QStringLiteral("feedbackBox"));
        feedbackBox->setGeometry(QRect(0, 460, 800, 20));
        feedbackBox->setAlignment(Qt::AlignCenter);
        feedbackBox->setIndent(0);
        buttonExit = new QPushButton(centralWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        buttonExit->setGeometry(QRect(0, 520, 800, 20));
        buttonExit->setMaximumSize(QSize(800, 16777215));
        BoxInClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoxInClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
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
        BoxInClass->setWindowTitle(QApplication::translate("BoxInClass", "BoxIn v0.1", 0));
        commandLabel->setText(QApplication::translate("BoxInClass", "  Command:", 0));
        feedbackBox->setText(QApplication::translate("BoxInClass", "Welcome to BoxIn v0.1", 0));
        buttonExit->setText(QApplication::translate("BoxInClass", "Exit", 0));
        menuFile->setTitle(QApplication::translate("BoxInClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class BoxInClass: public Ui_BoxInClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXIN_H
