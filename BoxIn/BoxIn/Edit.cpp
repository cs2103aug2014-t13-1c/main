//@author A0111994B
#include "Edit.h"

Edit::Edit(std::string input){
    name = parser.getField(input, TypeName);
    date = to_simple_string(parser.convertToDate(parser.getField(input, TypeEndDate)));
    field = parser.getField(input, TypeField);
    newValue = parser.getField(input, TypeNewValue);
    if(date == to_simple_string(boost::gregorian::date())){date = "";}
}


Edit::~Edit(void){
}

std::string Edit::execute(std::vector<Event*> &events){
	bool success = false;
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getEndDate() == date && (*iter)->getName() == name){
			oldEvent = *iter;
			events.erase(iter);
			success = true;
			break;
		}
	}
	if(success){
		newEvent = oldEvent->copy();
		newEvent->editField(field, newValue);
		events.push_back(newEvent);
		return newEvent->getName() + " has been edited!";
	}else{
		return "No item matching " + name + " found.";
	}
}

std::string Edit::undo(std::vector<Event*> &events){
	assert(oldEvent != NULL);
	assert(newEvent != NULL);
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == newEvent){
			events.erase(iter);
			break;
		}
	}
	events.push_back(oldEvent);
	return oldEvent->getName() + " has been un-edited!";
}