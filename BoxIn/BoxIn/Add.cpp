//@author A0111994

#include "Add.h"

/*
* Extracts the relevant info about the event to be added using the parser
* Creates the event and holds it
*
*/
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

/*
* Adds the event held by the Add command to the vector of events given
* Sets the index to the last event (will be sorted internally by the storage and
* reassigned the appropriate index)
*/
std::string Add::execute(std::vector<Event*> &events){
	events.push_back(event);
    event->setIdx(events.size());
	return event->getName() + " has been added!";
}

std::string Add::undo(std::vector<Event*> &events){
    deleteEvent(events, event);
	return event->getName() + " was deleted";
}