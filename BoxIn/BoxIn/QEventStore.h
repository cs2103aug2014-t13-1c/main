#pragma once
#include <QObject>
#include "qlistwidget.h"
#include "Event.h"

class QEventStore :
	public QObject, public QListWidgetItem
{
	Q_OBJECT
public:
	QEventStore(QWidget* parent, Event* event);
	~QEventStore(void);
	QString repr();
	Event* getEvent();
private:
	Event *event;
};
