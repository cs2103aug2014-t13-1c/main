//@author A0111994
#pragma once
#include <QObject>
#include "qlistwidget.h"
#include "Event.h"
#include "assert.h"

class QEventStore :
	public QObject, public QListWidgetItem
{
	Q_OBJECT
public:
	QEventStore(QWidget* parent, Event* event);
	~QEventStore(void);
	Event* getEvent();
private:
	Event *event;
};

