//@author A0111994B
#include "DisplayFeed.h"

DisplayFeed::DisplayFeed(QWidget *parent, DisplayField field)
	: QListWidget(parent)
{
	this->logic = logic;
    this->field = field;
	setBorder();
    setFont(QFont("Courier New", 9));
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
        std::string filler = "";
        std::string index = boost::lexical_cast<std::string>((*iter)->getIdx());
        std::string name = (*iter)->getName();
        std::string startDate = (*iter)->getStartDate();
        if(startDate == to_simple_string(boost::gregorian::day_clock::local_day())){startDate = "Today";}
        std::string endDate = (*iter)->getEndDate();
        if(endDate == to_simple_string(boost::gregorian::day_clock::local_day())){endDate = "Today";}
        if(endDate == startDate){endDate = "";}
        std::string startTime = (*iter)->getStartTime();
        if(startTime == "00:00"){startTime = "";}
        std::string endTime = (*iter)->getEndTime();
        if(endTime == "00:00"){endTime = "";}
        if(!(endDate.empty() && endTime.empty()) && !(startDate.empty() && startTime.empty())){filler = "to ";}
        std::string place = (*iter)->getLocation();
        if(place.empty()){place = "-";}
		QEventStore *item = new QEventStore(this, *iter);
        std::string itemText = pad(index, 5) + pad(name, 49) + pad(place, 21) +pad(startDate, 13) + pad(startTime, 6) + filler + pad(endDate, 13) + pad(endTime, 6);
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

std::string DisplayFeed::pad(std::string str, int spaces){
    if(str.empty()){return str;}
    while(str.size() < spaces){
        str += " ";
    }
    if(str.size() > spaces){return str.substr(0, spaces - 1);}
    return str;
}