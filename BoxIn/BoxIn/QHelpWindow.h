//@author A0111994
#ifndef QHELPWINDOW_H
#define QHELPWINDOW_H

#include "qwidget.h"
#include "ui_QHelpWindow.h"
#include "qcombobox.h"
#include "qtextedit.h"
#include "qstring.h"

namespace HelpOptions{
    static const QString GENERAL = "General";
    static const QString ADD = "Add";
    static const QString DELETE = "Delete";
    static const QString EDIT = "Edit";
    static const QString MARK = "Mark";
    static const QString VIEW = "View";
    static const QString UNDO = "Undo";
}

class QHelpWindow : public QWidget{
    Q_OBJECT

public:
    QHelpWindow(QWidget *parent = 0);
    ~QHelpWindow();

public slots:
    void changed(QString option);
    void setupSelector();

private:
    Ui::QHelpWindow ui;
    QComboBox* selector;
    QTextEdit* display;
};

#endif // QHELPWINDOW_H
