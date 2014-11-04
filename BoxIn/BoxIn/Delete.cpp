//@author A0111994B
#include "Delete.h"

Delete::Delete(std::string input){
    name = parser.getField(input, TypeName);
    date = to_simple_string(parser.convertToDate(parser.getField(input, TypeEndDate)));
	if(date == to_simple_string(boost::gregorian::date())){date = "";}
	event = NULL;
}


Delete::~Delete(void){
}

/*
* Searches the event vector for the matching event and removes it
* Stores the original event for undoing later on
*/
std::string Delete::execute(std::vector<Event*> &events){
	bool found = false;
    if(parser.isInteger(name)){
        if(stoi(name) <= events.size()){
            std::vector<Event*>::iterator iter = events.begin() + stoi(name) - 1;
            event = *iter;
            events.erase(iter);
            found=true;
        }else{
            return "No item matching " + name + " found.";
        }
    }else{
    	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
            if((*iter)->getEndDate() == date && (*iter)->getName() == name){
	    		event = *iter;
    			events.erase(iter);
			    found = true;
			    break;
		    }
	    }
    }
	if(found){
		return event->getName() + " has been deleted!";
	}else{
		return "No item matching " + name + " found.";
	}
}

/*
* Adds the previously deleted event pointer back to the vector of events
*/
std::string Delete::undo(std::vector<Event*> &events){
	assert(event != NULL);
	events.push_back(event);
	return event->getName() + " has been reinstated!";
}