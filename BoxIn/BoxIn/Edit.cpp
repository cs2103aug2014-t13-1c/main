//@author A0111994B
#include "Edit.h"

Edit::Edit(){
}

Edit::Edit(std::string input){
    name = parser.getField(input, TypeName);
    date = to_simple_string(parser.convertToDate(parser.getField(input, TypeEndDate)));
    field = parser.getField(input, TypeField);
    newValue = parser.getField(input, TypeNewValue);
    if(date == to_simple_string(boost::gregorian::date())){date = "";}
}


Edit::~Edit(void){
}

/*
* Searches the event vector for the matching event and deletes it, storing it for undoing
* Makes a deep copy of the event and edits the field to change
* Adds the new event into the vector
* Can be found either by index or by end date
*/
std::string Edit::execute(std::vector<Event*> &events){
	bool success = false;
    if(field.empty()){return "Missing field key word";}
    if(parser.isInteger(name)){oldEvent = findEventByIdx(stoi(name), events);}
    else{oldEvent = findEventByNameAndEndDate(name, date, events);}
    if(oldEvent != NULL){deleteEvent(events, oldEvent);}
	if(oldEvent != NULL){
		newEvent = oldEvent->copy();
		newEvent->editField(field, newValue);
		events.push_back(newEvent);
		return newEvent->getName() + " has been edited!";
	}else{
		return "No item matching " + name + " found.";
	}
}

/*
* Searches the event vector for the previously created event
* Deletes it and adds the stored old event back
*/
std::string Edit::undo(std::vector<Event*> &events){
	assert(oldEvent != NULL);
	assert(newEvent != NULL);
	deleteEvent(events, newEvent);
	events.push_back(oldEvent);
	return oldEvent->getName() + " has been un-edited!";
}

void Edit::deleteEvent(std::vector<Event*> &events, Event* event){
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == event){
			events.erase(iter);
			break;
		}
	}
}

Event* Edit::findEventByIdx(int idx, std::vector<Event*> &events){
    Event* event = NULL;
    if(stoi(name) <= events.size() && stoi(name) > 0){
        std::vector<Event*>::iterator iter = events.begin() + stoi(name) - 1;
        event = *iter;
    }
    return event;
}

Event* Edit::findEventByNameAndEndDate(std::string name, std::string endDate, std::vector<Event*> &events){
    Event* event = NULL;
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
	    if((*iter)->getEndDate() == endDate && (*iter)->getName() == name){
    		event = *iter;
            break;
    	}
    }
    return event;
}