#include "Event.h"


Event::Event(void)
{
}

Event::Event(std::string _name, std::string _date, std::string _time){
	name = _name;
	date = _date;
	time = _time;
}

Event::~Event(void){
}

std::string Event::getName(){
	return name;
}


std::string Event::getDescription() {
    return _description;
}

std::string Event::getCategory() {
    return _category;
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

bool Task::setFinish(bool result) {
     _isDone = result;
     return _isFinish;
}

