#ifndef BOXIN_H
#define BOXIN_H

#include <QMainWindow>
#include <QString>
#include <qlistview.h>
#include "ui_BoxIn.h"

static const int HEIGHT_WINDOW = 600;
static const int WIDTH_WINDOW = 400;

static const int HEIGHT_BUFFER = 10;

static const int HEIGHT_SMALL = 20;
static const int HEIGHT_LARGE = 450;

static const int WIDTH_LABEL = 60;

class BoxIn : public QMainWindow
{
	Q_OBJECT

public:
	explicit BoxIn(QWidget *parent = 0);
	~BoxIn();

private:
	Ui::BoxInClass ui;
	void setComponentSizes();
	void linkEvents();

private slots:
	void commandLineReturnPressed();
	void buttonExitClicked();
};

#endif // BOXIN_H
