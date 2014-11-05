#include "Event.h"


Event::Event(){
	fieldMap = setupMap();
    recent = false;
    done = false;
}

//@author A0111994B
/*
* Constructor for the Event class
* If the end time / date is before the start time / date, we only keep the end
* This assumes that the end time is more important than the start
*/
Event::Event(std::string name, std::string location, std::string sdate, std::string edate, std::string stime, std::string etime, int idx, bool recent){
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
	this->name = name;
    this->sdate = getDateFromInput(sdate, stime);
    this->edate = getDateFromInput(edate, etime, sdate);
    this->stime = getTimeFromInput(this->sdate, stime);
    this->etime = getTimeFromInput(this->edate, etime);
    if(etime<stime){
        this->sdate = boost::gregorian::date();
        this->stime = boost::posix_time::ptime();
    }
	this->location = location;
    this->idx = idx;
    this->recent = recent;
    this->done = false;
	fieldMap = setupMap();
}

Event::Event(std::string name, std::string location, std::string sdate, std::string edate, std::string stime, std::string etime, int idx, bool recent, bool done){
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
	this->name = name;
    this->sdate = getDateFromInput(sdate, stime);
    this->edate = getDateFromInput(edate, etime, sdate);
    this->stime = getTimeFromInput(this->sdate, stime);
    this->etime = getTimeFromInput(this->edate, etime);
    if(etime<stime){
        this->sdate = boost::gregorian::date();
        this->stime = boost::posix_time::ptime();
    }
	this->location = location;
    this->idx = idx;
    this->recent = recent;
    this->done = done;
	fieldMap = setupMap();
}

Event::~Event(){
}

Event* Event::copy(){
	return new Event(name, location, to_iso_string(sdate), to_iso_string(edate), getStartTime(), getEndTime(), idx, true, done);
}

std::map<std::string, Field> Event::setupMap(){
	std::map<std::string, Field> fieldMap;
	fieldMap[FIELD_NAME] = FieldName;
	fieldMap[FIELD_START_DATE] = FieldStartDate;
    fieldMap[FIELD_END_DATE] = FieldEndDate;
	fieldMap[FIELD_START_TIME] = FieldStartTime;
	fieldMap[FIELD_END_TIME] = FieldEndTime;
    fieldMap[FIELD_LOCATION] = FieldLocation;
    fieldMap[FIELD_DONE] = FieldDone;
	return fieldMap;
}

std::string Event::getName(){
	return name;
}

std::string Event::getStartDate(){
    if(sdate != boost::gregorian::date(boost::gregorian::not_a_date_time)){return boost::gregorian::to_simple_string(sdate);}
    return "";
}

std::string Event::getEndDate(){
    if(edate != boost::gregorian::date(boost::gregorian::not_a_date_time)){return boost::gregorian::to_simple_string(edate);}
    return "";
}

std::string Event::getStartTime(){
    if(stime != boost::posix_time::ptime(boost::posix_time::not_a_date_time)){return boost::posix_time::to_iso_extended_string(stime).substr(11,5);}
    return "";
}

std::string Event::getEndTime(){
    if(etime != boost::posix_time::ptime(boost::posix_time::not_a_date_time)){return boost::posix_time::to_iso_extended_string(etime).substr(11,5);}
    return "";
}

std::string Event::getLocation(){
	return location;
}

int Event::getIdx(){
    return idx;
}

void Event::editField(std::string field, std::string newValue){
	switch(fieldMap[field]){
		case FieldName :
			setName(newValue);
			break;
		case FieldStartDate :
			setStartDate(newValue);
			break;
        case FieldEndDate :
            setEndDate(newValue);
            break;
        case FieldStartTime :
            setStartTime(newValue);
            break;
		case FieldEndTime :
			setEndTime(newValue);
			break;
		case FieldLocation :
			setLocation(newValue);
            break;
        case FieldDone :
            setDone(!done);
            break;
	}
}

void Event::setName(std::string newName){
	name = newName;
}

/*
* Takes in a string containing the new date
* For all below functions, only modifies if the new entry preserves
* The correct start/end ordering
*/
void Event::setStartDate(std::string newDate){
	boost::gregorian::date date = parser.convertToDate(newDate);
    if(date <= edate || edate.is_special()){
        sdate = date;
        stime = timeParser.convertToTime(sdate, getStartTime());
    }
}

void Event::setEndDate(std::string newDate){
	boost::gregorian::date date = parser.convertToDate(newDate);
    if(date >= sdate || sdate.is_special()){
        edate = date;
        etime = timeParser.convertToTime(edate, getEndTime());
    }
}

void Event::setStartTime(std::string newTime){
    boost::gregorian::date date = sdate;
    if(sdate.is_special() && !newTime.empty()){date = boost::gregorian::day_clock::local_day();}
    boost::posix_time::ptime time = timeParser.convertToTime(sdate, newTime);
    if(time <= etime){
        sdate = date;
        stime = time;
    }
}

void Event::setEndTime(std::string newTime){
    if(edate.is_special() && !newTime.empty()){edate = boost::gregorian::day_clock::local_day();}
    boost::posix_time::ptime time = timeParser.convertToTime(edate, newTime);
    if(time >= stime){
        etime = time;
    }
}

void Event::setLocation(std::string newLocation){
	location = newLocation;
}

void Event::setIdx(int newIdx){
    idx = newIdx;
}

/*
* Gives a textual representation of all data in a event. Used for unit testing
*/
std::string Event::repr(){
    return name + " at " + location + " from " + getStartDate() + ", " + getStartTime() + " to " + getEndDate() + ", " + getEndTime();
}

boost::posix_time::ptime Event::getPosixStartTime(){
    return stime;
}

boost::posix_time::ptime Event::getPosixEndTime(){
    return etime;
}

bool Event::isRecent(){
    return recent;
}

void Event::removeRecent(){
    recent = false;
}

void Event::setDone(bool newValue){
    done = newValue;
}

bool Event::getDone(){
    return done;
}

/*
* Takes in the strings for date and time
* Returns the appropriate date based off date
* Or today's date if a time is specified but a date is not
* This method is overloaded
*/
boost::gregorian::date Event::getDateFromInput(std::string date, std::string time){
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    boost::gregorian::date result;
    if(!date.empty() && date != NULL_DATE_TIME){result = parser.convertToDate(date);}
    else if(!(time.empty() || time == NULL_DATE_TIME)){result = today;}
    return result;
}

/*
* Takes in the strings for date and time and a third input for the default date if not specified
* Returns the appropriate date based off date
* Or the default date if the time is specified but date is not
* This method is overloaded
*/
boost::gregorian::date Event::getDateFromInput(std::string date, std::string time, std::string predate){
    boost::gregorian::date result;
    if(!date.empty() && date != NULL_DATE_TIME){result = parser.convertToDate(date);}
    else if(!(time.empty() || time == NULL_DATE_TIME)){result = parser.convertToDate(predate);}
    return result;
}

/*
* Takes in the date as a boost::gregorian::date and the time as a string
* Returns the matching time or 00:00 when the time is not specified
*/
boost::posix_time::ptime Event::getTimeFromInput(boost::gregorian::date date, std::string time){
    boost::posix_time::ptime result;
    if((time.empty() || time == NULL_DATE_TIME) && !date.is_special()){
        result = timeParser.convertToTime(date, NULL_TIME);
    }else if(!(time.empty() || time == NULL_DATE_TIME)){
        result = timeParser.convertToTime(date, time);
    }
    return result;
}

/*
std::string Event::getDescription() {
    return description;
}

std::string Event::getCategory() {
    return category;
}

std::int Event::getPriority() {
     return _priority;
}

bool Event::setName(string name) {
     _name = name;
     return true;
}

bool Task::setPriority(int value) {
     _priority = value;
     return true;
}


bool Task::setCategory(string cat) {
     _category = cat;
     return true;
}


bool Task::setDescription(string content) {
      _description = content;
      return true;
}

/**
* Method: setFinish-->sets the task as done/undone. returns the final status of the _isDone variable
*/
/*
bool Task::setFinish(bool result) {
     _isDone = result;
     return _isFinish;
}

*/