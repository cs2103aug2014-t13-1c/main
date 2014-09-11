#ifndef BOXIN_H
#define BOXIN_H

#include <QMainWindow>
#include <QString>
#include <qlistview.h>
#include "ui_BoxIn.h"


class BoxIn : public QMainWindow
{
	Q_OBJECT

public:
	explicit BoxIn(QWidget *parent = 0);
	~BoxIn();

private:
	Ui::BoxInClass ui;

private slots:
	void commandLineReturnPressed();
	void buttonExitClicked();
};

#endif // BOXIN_H
