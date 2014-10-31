//@author A0111994B

#include "Add.h"


Add::Add(std::string input){
	std::string name = parser.getField(input, TypeName);
    std::string startDate = parser.getField(input, TypeStartDate);
    std::string endDate = parser.getField(input, TypeEndDate);
    std::string startTime = parser.getField(input, TypeStartTime);
    std::string endTime = parser.getField(input, TypeEndTime);
    std::string location = parser.getField(input, TypePlace);
	event = new Event(name, location, startDate, endDate, startTime, endTime, 0, true);
}

Add::~Add(void){
}

std::string Add::execute(std::vector<Event*> &events){
	events.push_back(event);
    event->setIdx(events.size());
	return event->getName() + " has been added!";
}

std::string Add::undo(std::vector<Event*> &events){
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == event){
			events.erase(iter);
			break;
		}
	}
	return event->getName() + " was deleted";
}