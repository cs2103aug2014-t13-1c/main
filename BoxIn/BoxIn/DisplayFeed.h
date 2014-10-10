#pragma once
#include "qlistwidget.h"
#include "Event.h"
#include "QEventStore.h"

class DisplayFeed :
	public QListWidget
{
public:
	DisplayFeed(QWidget *parent, int xpos, int ypos, int width, int height, std::string color);
	~DisplayFeed(void);

	void setColor(std::string color);
	void refresh(std::vector<Event*> *thingsToInclude);
public slots:
	void editItem(QEventStore *item);
};

