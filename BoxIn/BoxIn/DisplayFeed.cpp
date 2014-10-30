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
            if(itemText == to_simple_string(boost::gregorian::day_clock::local_day())){itemText = "Today";}
            break;
        case EndDate :
            itemText = (*iter)->getEndDate();
            if(itemText == to_simple_string(boost::gregorian::day_clock::local_day())){itemText = "Today";}
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
    setItemColors();
}

void DisplayFeed::setItemColors(){
    QBrush gray(QColor(100, 100, 100));
    for(unsigned int i = 0; i < count(); i++){
        Event* event = dynamic_cast<QEventStore*>(item(i))->getEvent();
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        if(event->getPosixStartTime() < now || event->getPosixEndTime() < now){
            item(i)->setForeground(Qt::red);
        }else if(i % 2 == 1){
            item(i)->setForeground(gray);
        }else{
            item(i)->setForeground(Qt::black);
        }
    }
}