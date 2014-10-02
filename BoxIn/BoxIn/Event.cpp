#include "Event.h"


Event::Event(){
}

Event::Event(std::string name, std::string location, std::string date, std::string time){
	this->name = name;
	// this->date = boost::gregorian::date(boost::gregorian::from_undelimited_string(date));
	// this->time = boost::posix_time::ptime(this->date, boost::posix_time::time_duration(std::stoi(time.substr(0,2)), std::stoi(time.substr(2,4)), 0));
	this->date = date;
	this->time = time;
	this->location = location;
}

Event::Event(std::string name, std::string date, std::string time){
	this->name = name;
	// this->date = boost::gregorian::date(boost::gregorian::from_undelimited_string(date));
	// this->time = boost::posix_time::ptime(this->date, boost::posix_time::time_duration(std::stoi(time.substr(0,2)), std::stoi(time.substr(2,4)), 0));
	this->date = date;
	this->time = time;
}

Event::~Event(){
}

std::string Event::getName(){
	return name;
}

std::string Event::getDate(){
	return date;
	// return boost::gregorian::to_iso_extended_string(date);
}

std::string Event::getTime(){
	return time;
	// return boost::posix_time::to_iso_extended_string(time);
}

std::string Event::getLocation(){
	return location;
}

void Event::editField(std::string field, std::string newValue){
	if(field == FIELD_NAME){
		setName(newValue);
	}
}

void Event::setName(std::string newName){
	name = newName;
}

void Event::setDate(std::string newDate){
	date = newDate;
}

void Event::setTime(std::string newTime){
	time = newTime;
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