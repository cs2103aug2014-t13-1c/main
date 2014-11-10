//@author A0111994B
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

namespace PadSizes{
    static const int INDEX = 5;
    static const int NAME = 49;
    static const int PLACE = 21;
    static const int DATE = 13;
    static const int TIME = 6;
};

class DisplayFeed : public QListWidget{
	Q_OBJECT
public:
	DisplayFeed(QWidget *parent);
	~DisplayFeed(void);

	void setBorder();
	void refresh(std::vector<Event*> *thingsToInclude);
    void setItemColors();
    std::string pad(std::string str, int spaces);
    std::string reprDate(std::string date);
    std::string formatEvent(Event* event);
};

#endif // DisplayFeed.h

