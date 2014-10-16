#ifndef DISPLAYFEED_H
#define DISPLAYFEED_H

#include "qlistwidget.h"
#include "Event.h"
#include "QEventStore.h"
#include "QEventEditor.h"
#include "qmessagebox.h"
#include "qlabel.h"
#include "qeventloop.h"
#include "assert.h"

class DisplayFeed : public QListWidget{
	Q_OBJECT
private:
	Logic *logic;
public:
	DisplayFeed(QWidget *parent, int xpos, int ypos, int width, int height, std::string color);
	~DisplayFeed(void);

	void setColor(std::string color);
	void refresh(std::vector<Event*> *thingsToInclude);
};

#endif // DisplayFeed.h

