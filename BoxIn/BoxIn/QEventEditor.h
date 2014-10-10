#pragma once
#include "qwidget.h"
#include "Event.h"

class QEventEditor :
	public QWidget
{
public:
	QEventEditor(Event* event, QWidget *parent = 0);
	~QEventEditor(void);
};

