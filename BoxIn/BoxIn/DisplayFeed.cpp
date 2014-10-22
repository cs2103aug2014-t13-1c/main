//@author A0111994B
#include "DisplayFeed.h"

DisplayFeed::DisplayFeed(QWidget *parent, int xpos, int ypos, int width, int height, QString color)
	: QListWidget(parent)
{
	assert(xpos >= 0 && ypos >= 0 && height > 0 && width > 0 && "Invalid geometry");
	this->logic = logic;
	setGeometry(xpos, ypos, width, height);
	setColor(color);
	show();
}


DisplayFeed::~DisplayFeed(void){
}

void DisplayFeed::setColor(QString color){
	color = "background-color: " + color;
	setStyleSheet(color);
	setFrameShape(QFrame::NoFrame);
    setUniformItemSizes(true);
}

void DisplayFeed::refresh(std::vector<Event*> *thingsToInclude){
	clear();
	for(std::vector<Event*>::iterator iter = thingsToInclude->begin(); iter != thingsToInclude->end(); iter++){		
		assert(*iter!=NULL && "Null event floating around in storage?");
		std::string itemText = (*iter)->repr();
		QEventStore *item = new QEventStore(this, *iter);
		item->setText(QString(item->repr()));
		addItem(item);
	}
}
