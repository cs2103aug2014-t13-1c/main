//@author A0111994B
#include "DisplayFeed.h"

DisplayFeed::DisplayFeed(QWidget *parent) : QListWidget(parent){
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

/*
* Takes in a vector of event pointers to the things to display
* Converts their respective elements to text and links the event to QEventStore
* Creates the textual representation and displays it
*/
void DisplayFeed::refresh(std::vector<Event*> *thingsToInclude){
	clear();
	for(std::vector<Event*>::iterator iter = thingsToInclude->begin(); iter != thingsToInclude->end(); iter++){		
		assert(*iter!=NULL && "Null event floating around in storage?");
		QEventStore *item = new QEventStore(this, *iter);
        std::string itemText = formatEvent(*iter);
		item->setText(QString(itemText.c_str()));
		addItem(item);
	}
    setItemColors();
}

/*
* Goes through all the items in the display
* Sets colors based on status
* New - Purple
* Overdue and undone - Red
* The rest alternate between grey and black
*/
void DisplayFeed::setItemColors(){
    QBrush gray(QColor(100, 100, 100));
    for(unsigned int i = 0; i < count(); i++){
        Event* event = dynamic_cast<QEventStore*>(item(i))->getEvent();
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        if(event->isRecent()){
            item(i)->setForeground(Qt::darkMagenta);
            dynamic_cast<QEventStore*>(item(i))->getEvent()->removeRecent();
        }else if((event->getPosixStartTime() < now || event->getPosixEndTime() < now) && !event->getDone()){
            // only undone and overdue tasks to be in red
            item(i)->setForeground(Qt::red);
        }else if(i % 2 == 1){
            item(i)->setForeground(gray);
        }else{
            item(i)->setForeground(Qt::black);
        }
    }
}

/*
* Pads up a string to spaces number of characters with whitespace
* Strings above the max length are truncated with one spare whitespace
*/
std::string DisplayFeed::pad(std::string str, int spaces){
    if(str.empty()){return str;}
    while(str.size() < spaces){
        str += " ";
    }
    if(str.size() > spaces){return str.substr(0, spaces - 1) + " ";}
    return str;
}

/*
* Converts a date to today / tomorrow if it happens to match those dates
*/
std::string DisplayFeed::reprDate(std::string date){
    if(date == to_simple_string(boost::gregorian::day_clock::local_day())){date = "Today";}
    else if(date == to_simple_string(boost::gregorian::day_clock::local_day()+boost::gregorian::date_duration(1))){date = "Tomorrow";}
    return date;
}

/*
* Formats data from a event into a uniformly spaced manner for display
*/
std::string DisplayFeed::formatEvent(Event* event){
    
    std::string index = boost::lexical_cast<std::string>((event)->getIdx());
    std::string name = event->getName();
    std::string place = event->getLocation();
    std::string startDate = reprDate(event->getStartDate());
    std::string startTime = event->getStartTime();
    std::string endDate = reprDate(event->getEndDate());
    std::string endTime = event->getEndTime();
    std::string filler = "";
    if(endDate == startDate){endDate = "";}
    if(startTime == NULL_TIME){startTime = "";}
    if(endTime == NULL_TIME){endTime = "";}
    if(!(endDate.empty() && endTime.empty()) && !(startDate.empty() && startTime.empty())){filler = "to ";}
    if(place.empty()){place = "-";}
    return pad(index, PadSizes::INDEX) + pad(name, PadSizes::NAME) + pad(place, PadSizes::PLACE) +pad(startDate, PadSizes::DATE) + pad(startTime, PadSizes::TIME) + filler + pad(endDate, PadSizes::DATE) + pad(endTime, PadSizes::TIME);
}
