#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QLCDNumber>
#include "ui_digitalclock.h"
#include <qtimer.h>
#include <QTime>

static const int REFRESH_TIME = 1000;
static const int WIDTH_TIMER = 100;
static const int HEIGHT_TIMER = 50;

class DigitalClock : public QLCDNumber
{
	Q_OBJECT

public:
	DigitalClock(QWidget *parent = 0);
	~DigitalClock();

private:
	Ui::DigitalClock ui;
	QString flashColon(QString text, QTime time);

private slots:
	void showTime();
};

#endif // DIGITALCLOCK_H
