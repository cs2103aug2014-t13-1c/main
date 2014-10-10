#include "DisplayFeed.h"


DisplayFeed::DisplayFeed(QWidget *parent, int xpos, int ypos, int width, int height, std::string color)
	: QListWidget(parent)
{
	setGeometry(xpos, ypos, width, height);
	setColor(color);
	QObject::connect(this, SIGNAL(itemDoubleClicked(*item)), this, SLOT(editItem(*item)));
	show();
}


DisplayFeed::~DisplayFeed(void){
}

void DisplayFeed::setColor(std::string color){
	color = "background-color: " + color;
	setStyleSheet(QString(color.c_str()));
    setUniformItemSizes(true);
}

void DisplayFeed::editItem(QEventStore *item){

}

void DisplayFeed::refresh(std::vector<Event*> *thingsToInclude){
	clear();
	for(std::vector<Event*>::iterator iter = thingsToInclude->begin(); iter != thingsToInclude->end(); iter++){		
		std::string itemText = (*iter)->repr();
		QEventStore *item = new QEventStore(this, *iter);
		item->setText(QString(item->repr()));
		addItem(item);
	}
}


