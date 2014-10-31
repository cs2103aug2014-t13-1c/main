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
        std::string index = boost::lexical_cast<std::string>((*iter)->getIdx());
        std::string name = (*iter)->getName();
        std::string place = (*iter)->getLocation();
        std::string startDate = reprDate((*iter)->getStartDate());
        std::string startTime = (*iter)->getStartTime();
        std::string endDate = reprDate((*iter)->getEndDate());
        std::string endTime = (*iter)->getEndTime();
		QEventStore *item = new QEventStore(this, *iter);
        std::string itemText = formatEvent(index, name, place, startDate, startTime, endDate, endTime);
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
        if(event->isRecent()){
            item(i)->setForeground(Qt::darkMagenta);
            dynamic_cast<QEventStore*>(item(i))->getEvent()->removeRecent();
        }else if(event->getPosixStartTime() < now || event->getPosixEndTime() < now){
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
    if(str.size() > spaces){return str.substr(0, spaces - 1) + " ";}
    return str;
}

std::string DisplayFeed::reprDate(std::string date){
    if(date == to_simple_string(boost::gregorian::day_clock::local_day())){date = "Today";}
    else if(date == to_simple_string(boost::gregorian::day_clock::local_day()+boost::gregorian::date_duration(1))){date = "Tomorrow";}
    return date;
}

std::string DisplayFeed::formatEvent(std::string index, std::string name, std::string place, std::string startDate, std::string startTime, std::string endDate, std::string endTime){
    std::string filler = "";
    if(endDate == startDate){endDate = "";}
    if(startTime == NULL_TIME){startTime = "";}
    if(endTime == NULL_TIME){endTime = "";}
    if(!(endDate.empty() && endTime.empty()) && !(startDate.empty() && startTime.empty())){filler = "to ";}
    if(place.empty()){place = "-";}
    return pad(index, 5) + pad(name, 49) + pad(place, 21) +pad(startDate, 13) + pad(startTime, 6) + filler + pad(endDate, 13) + pad(endTime, 6);
}