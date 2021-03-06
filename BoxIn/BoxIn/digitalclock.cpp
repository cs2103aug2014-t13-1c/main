//@author A0111994B
#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent)
	: QLCDNumber(parent)
{
	ui.setupUi(this);
	setSegmentStyle(Filled);
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();
    resize(WIDTH_TIMER, HEIGHT_TIMER);
}

DigitalClock::~DigitalClock(){
}

void DigitalClock::showTime(){
	QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    text = flashColon(text, time);
    display(text);
}

QString DigitalClock::flashColon(QString text, QTime time){
	if ((time.second() % 2) == 0){
        text[2] = ' ';
	}
	return text;
}


