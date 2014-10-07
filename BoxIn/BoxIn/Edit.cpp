#include "Edit.h"


Edit::Edit(std::string input){
	// do something with parser here
	name = "something";
	date = "something";
	field = "something";
	newValue = "something";
	oldEvent = NULL;
	newEvent = NULL;
}


Edit::~Edit(void){
}

std::string Edit::execute(std::vector<Event*> &events){
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			oldEvent = *iter;
			events.erase(iter);
		}
	}

	newEvent = oldEvent->copy();
	newEvent->editField(field, newValue);

	return newEvent->getName() + " has been edited!";	
}

std::string Edit::undo(std::vector<Event*> &events){
	assert(oldEvent != NULL);
	assert(newEvent != NULL);
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == newEvent){
			events.erase(iter);
		}
	}
	events.push_back(oldEvent);
	oldEvent = NULL;
	newEvent = NULL;
	return events[events.size()-1]->getName() + " has been un-edited!";
}