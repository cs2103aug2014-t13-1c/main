#include "Event.h"


Event::Event(){
	fieldMap = setupMap();
    recent = false;
    done = false;
}

//@author A0111994B
Event::Event(std::string name, std::string location, std::string sdate, std::string edate, std::string stime, std::string etime, int idx, bool recent){
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
	this->name = name;
    if(!sdate.empty() && sdate != NULL_DATE_TIME){this->sdate = parser.convertToDate(sdate);}
    if((sdate.empty() && sdate == NULL_DATE_TIME) && (!stime.empty() && stime != NULL_DATE_TIME)){
        this->sdate = today;
        this->stime = timeParser.convertToTime(today, stime);
    }else if(!stime.empty()){
        this->stime = timeParser.convertToTime(this->sdate, stime);
    }

    if(!edate.empty() && edate != NULL_DATE_TIME){this->edate = parser.convertToDate(edate);}
    if((edate.empty() && edate == NULL_DATE_TIME) && (!etime.empty() && etime != NULL_DATE_TIME)){
        this->edate = today;
        this->etime = timeParser.convertToTime(today, etime);
    }else if(etime!=""){
        this->etime = timeParser.convertToTime(this->edate, etime);
    }
    if(this->stime > this->etime){
        // invalid start, end time pairings, reset start time to nothing and keep start time only
        // since start time is likely to be the more important
        this->edate = boost::gregorian::date();
        this->etime = boost::posix_time::ptime();
    }
    if(!this->sdate.is_special() && stime.empty()){this->stime = timeParser.convertToTime(this->sdate, NULL_TIME);}
    if(!this->edate.is_special() && etime.empty()){this->etime = timeParser.convertToTime(this->edate, NULL_TIME);}
	this->location = location;
    this->idx = idx;
    this->recent = recent;
    done = false;
	fieldMap = setupMap();
}

Event::Event(std::string name, std::string location, std::string sdate, std::string edate, std::string stime, std::string etime, int idx, bool recent, bool done){
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
	this->name = name;
    if(!sdate.empty() && sdate != NULL_DATE_TIME){this->sdate = parser.convertToDate(sdate);}
    if((sdate.empty() || sdate == NULL_DATE_TIME) && (!stime.empty() && stime != NULL_DATE_TIME)){
        this->sdate = today;
        this->stime = timeParser.convertToTime(today, stime);
    }else if(!stime.empty()){
        this->stime = timeParser.convertToTime(this->sdate, stime);
    }

    if(!edate.empty() && edate != NULL_DATE_TIME){this->edate = parser.convertToDate(edate);}
    if((edate.empty() || edate == NULL_DATE_TIME) && (!etime.empty() && etime != NULL_DATE_TIME)){
        this->edate = today;
        this->etime = timeParser.convertToTime(today, etime);
    }else if(etime!=""){
        this->etime = timeParser.convertToTime(this->edate, etime);
    }
    if(this->stime > this->etime){
        // invalid start, end time pairings, reset start time to nothing and keep start time only
        // since start time is likely to be the more important
        this->edate = boost::gregorian::date();
        this->etime = boost::posix_time::ptime();
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

void Event::setStartDate(std::string newDate){
	sdate = parser.convertToDate(newDate);
    stime = timeParser.convertToTime(sdate, getStartTime());
}

void Event::setEndDate(std::string newDate){
	edate = parser.convertToDate(newDate);
    etime = timeParser.convertToTime(edate, getEndTime());
}

void Event::setStartTime(std::string newTime){
    if(sdate.is_special() && !newTime.empty()){sdate = boost::gregorian::day_clock::local_day();}
    stime = timeParser.convertToTime(sdate, newTime);
}

void Event::setEndTime(std::string newTime){
    if(edate.is_special() && !newTime.empty()){edate = boost::gregorian::day_clock::local_day();}
    etime = timeParser.convertToTime(edate, newTime);
}

void Event::setLocation(std::string newLocation){
	location = newLocation;
}

void Event::setIdx(int newIdx){
    idx = newIdx;
}

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