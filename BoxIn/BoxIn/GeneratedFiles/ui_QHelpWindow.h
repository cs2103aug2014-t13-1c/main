/********************************************************************************
** Form generated from reading UI file 'QHelpWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHELPWINDOW_H
#define UI_QHELPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHelpWindow
{
public:

    void setupUi(QWidget *QHelpWindow)
    {
        if (QHelpWindow->objectName().isEmpty())
            QHelpWindow->setObjectName(QStringLiteral("QHelpWindow"));
        QHelpWindow->resize(400, 300);

        retranslateUi(QHelpWindow);

        QMetaObject::connectSlotsByName(QHelpWindow);
    } // setupUi

    void retranslateUi(QWidget *QHelpWindow)
    {
        QHelpWindow->setWindowTitle(QApplication::translate("QHelpWindow", "QHelpWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class QHelpWindow: public Ui_QHelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHELPWINDOW_H
