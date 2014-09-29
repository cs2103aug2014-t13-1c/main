/********************************************************************************
** Form generated from reading UI file 'digitalclock.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITALCLOCK_H
#define UI_DIGITALCLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>

QT_BEGIN_NAMESPACE

class Ui_DigitalClock
{
public:

    void setupUi(QLCDNumber *DigitalClock)
    {
        if (DigitalClock->objectName().isEmpty())
            DigitalClock->setObjectName(QStringLiteral("DigitalClock"));
        DigitalClock->resize(400, 300);

        retranslateUi(DigitalClock);

        QMetaObject::connectSlotsByName(DigitalClock);
    } // setupUi

    void retranslateUi(QLCDNumber *DigitalClock)
    {
        DigitalClock->setWindowTitle(QApplication::translate("DigitalClock", "DigitalClock", 0));
    } // retranslateUi

};

namespace Ui {
    class DigitalClock: public Ui_DigitalClock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITALCLOCK_H
