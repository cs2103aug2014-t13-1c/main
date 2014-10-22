//@author A0111994B
#include "DisplayFeed.h"

DisplayFeed::DisplayFeed(QWidget *parent, std::string field)
	: QListWidget(parent)
{
	this->logic = logic;
    displayFieldMap = setupMap();
    this->field = displayFieldMap[field];
	setBorder();
	show();
}


DisplayFeed::~DisplayFeed(void){
}

std::map<std::string, DisplayField> DisplayFeed::setupMap(){
    std::map<std::string, DisplayField> m;
    m["Name"] = Name;
    m["Date"] = Date;
    m["Time"] = Time;
    m["Place"] = Place;
    return m;
}

void DisplayFeed::setBorder(){
	setFrameShape(QFrame::NoFrame);
    setUniformItemSizes(true);
}

void DisplayFeed::refresh(std::vector<Event*> *thingsToInclude){
	clear();
	for(std::vector<Event*>::iterator iter = thingsToInclude->begin(); iter != thingsToInclude->end(); iter++){		
		assert(*iter!=NULL && "Null event floating around in storage?");
        std::string itemText;
        switch(field){
        case Name :
            itemText = (*iter)->getName();
            break;
        case Date :
            itemText = (*iter)->getDate();
            break;
        case Time :
            itemText = (*iter)->getTime();
            break;
        case Place :
            itemText = (*iter)->getLocation();
            break;
        }
		QEventStore *item = new QEventStore(this, *iter);
		item->setText(QString(itemText.c_str()));
		addItem(item);
	}
}
