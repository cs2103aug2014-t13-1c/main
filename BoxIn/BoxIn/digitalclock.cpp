#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent)
	: QLCDNumber(parent)
{
	ui.setupUi(this);
	setSegmentStyle(Filled);

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(REFRESH_TIME);

    showTime();

    resize(WIDTH_TIMER, HEIGHT_TIMER);
}

DigitalClock::~DigitalClock(){
}

void DigitalClock::showTime(){
	QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0){
        text[2] = ' ';
	}
    display(text);
}


