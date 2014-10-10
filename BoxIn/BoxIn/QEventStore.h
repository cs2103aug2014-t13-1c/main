#pragma once
#include "qlistwidget.h"
#include "Event.h"

class QEventStore :
	public QListWidgetItem
{
public:
	QEventStore(QWidget* parent, Event* event);
	~QEventStore(void);
	QString repr();
private:
	Event *event;
};

