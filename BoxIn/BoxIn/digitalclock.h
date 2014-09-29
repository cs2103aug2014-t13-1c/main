#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QLCDNumber>
#include "ui_digitalclock.h"
#include <qtimer.h>
#include <QTime>

class DigitalClock : public QLCDNumber
{
	Q_OBJECT

public:
	DigitalClock(QWidget *parent = 0);
	~DigitalClock();

private:
	Ui::DigitalClock ui;
	void showTime();
};

#endif // DIGITALCLOCK_H
