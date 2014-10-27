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
#include <boost/lexical_cast.hpp>

enum DisplayField{
    Name = 1,
    StartDate,
    EndDate,
    StartTime,
    EndTime,
    Place,
    Index
};

class DisplayFeed : public QListWidget{
	Q_OBJECT
private:
	Logic *logic;
    std::map<std::string, DisplayField> displayFieldMap;
    DisplayField field;
    
public:
	DisplayFeed(QWidget *parent, DisplayField field);
	~DisplayFeed(void);

	void setBorder();
	void refresh(std::vector<Event*> *thingsToInclude);
    std::map<std::string, DisplayField> setupMap();
};

#endif // DisplayFeed.h

