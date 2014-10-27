//@author A0111994B
#include "DisplayFeed.h"

DisplayFeed::DisplayFeed(QWidget *parent, DisplayField field)
	: QListWidget(parent)
{
	this->logic = logic;
    this->field = field;
	setBorder();
	show();
}


DisplayFeed::~DisplayFeed(void){
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
        case StartDate :
            itemText = (*iter)->getStartDate();
            break;
        case EndDate :
            itemText = (*iter)->getEndDate();
            break;
        case StartTime :
            itemText = (*iter)->getStartTime();
            break;
        case EndTime :
            itemText = (*iter)->getEndTime();
            break;
        case Place :
            itemText = (*iter)->getLocation();
            break;
        case Index :
            itemText = boost::lexical_cast<std::string>((*iter)->getIdx());
            break;
        }
		QEventStore *item = new QEventStore(this, *iter);
		item->setText(QString(itemText.c_str()));
		addItem(item);
	}
}
