#include "Event.h"


Event::Event(){
	fieldMap = setupMap();
}

//@author A0111994B
Event::Event(std::string name, std::string location, std::string date, std::string time){
	this->name = name;
    if(date!=""){this->date = dateParser.convertToDate(date);}
    if(time!=""){this->time = boost::posix_time::ptime(this->date, boost::posix_time::time_duration(std::stoi(time.substr(0,2)), std::stoi(time.substr(2,4)), 0));}
	this->location = location;
	fieldMap = setupMap();
}

Event::Event(std::string name, std::string date, std::string time){
	// this->name = name;
	// this->date = boost::gregorian::date(boost::gregorian::from_undelimited_string(date));
	// this->time = boost::posix_time::ptime(this->date, boost::posix_time::time_duration(std::stoi(time.substr(0,2)), std::stoi(time.substr(2,4)), 0));
	// this->date = date;
	// this->time = time;
	// fieldMap = setupMap();
}

Event::~Event(){
}

Event* Event::copy(){
	return new Event(name, location, to_iso_string(date), to_iso_string(time).substr(9,12));
}

std::map<std::string, Field> Event::setupMap(){
	std::map<std::string, Field> fieldMap;
	fieldMap[FIELD_NAME] = FieldName;
	fieldMap[FIELD_DATE] = FieldDate;
	fieldMap[FIELD_TIME] = FieldTime;
	fieldMap[FIELD_LOCATION] = FieldLocation;
	return fieldMap;
}

std::string Event::repr(){
	std::string rep = name;
	if(location != ""){rep = rep + " at " + location;}
	if(date != boost::gregorian::date(boost::gregorian::not_a_date_time)){rep = rep + " on " + to_iso_extended_string(date);}
    if(time != boost::posix_time::ptime(boost::posix_time::not_a_date_time)){rep = rep + " at " + to_iso_extended_string(time) + "hrs";}
	return rep;
}

std::string Event::getName(){
	return name;
}

std::string Event::getDate(){
    if(date != boost::gregorian::date(boost::gregorian::not_a_date_time)){return boost::gregorian::to_simple_string(date);}
    return "";
}

std::string Event::getTime(){
    if(time != boost::posix_time::ptime(boost::posix_time::not_a_date_time)){return boost::posix_time::to_iso_extended_string(time).substr(11,16);}
    return "";
}

std::string Event::getLocation(){
	return location;
}

void Event::editField(std::string field, std::string newValue){
	switch(fieldMap[field]){
		case FieldName :
			setName(newValue);
			break;
		case FieldDate:
			setDate(newValue);
			break;
		case FieldTime :
			setTime(newValue);
			break;
		case FieldLocation :
			setLocation(newValue);
	}
}

void Event::setName(std::string newName){
	name = newName;
}

void Event::setDate(std::string newDate){
	date = dateParser.convertToDate(newDate);
}

void Event::setTime(std::string newTime){
	time = boost::posix_time::ptime(this->date, boost::posix_time::time_duration(std::stoi(newTime.substr(0,2)), std::stoi(newTime.substr(2,4)), 0));
}

void Event::setLocation(std::string newLocation){
	location = newLocation;
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