//@author A0111994B

#include "Add.h"


Add::Add(std::string input){
	std::string name = parser.getField(input, TypeName);
    std::string date = parser.getField(input, TypeDate);
    std::string time = parser.getField(input, TypeTime);
    std::string location = parser.getField(input, TypePlace);
	event = new Event(name, location, date, time, 0);
}

Add::~Add(void){
}

std::string Add::execute(std::vector<Event*> &events){
	events.push_back(event);
    event->setIdx(events.size());
	return event->getName() + " has been added!";
}

std::string Add::undo(std::vector<Event*> &events){
	// stub
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == event){
			events.erase(iter);
			break;
		}
	}
	return event->getName() + " was deleted";
}