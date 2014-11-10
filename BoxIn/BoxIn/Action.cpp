//@author A0111994B

#include "Action.h"

Action::Action(void){
}


Action::~Action(void){
}

std::string Action::execute(std::vector<Event*>&){
	// stub
	return "";
}

std::string Action::undo(std::vector<Event*>&){
	// stub
	return "";
}

//deletes the event 
void Action::deleteEvent(std::vector<Event*> &events, Event* event){
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == event){
			events.erase(iter);
			break;
		}
	}
}

//search through the indexes to find a specific index through search
Event* Action::findEventByIdx(int idx, std::vector<Event*> &events){
    Event* event = NULL;
    if(idx <= events.size() && idx > 0){
        std::vector<Event*>::iterator iter = events.begin() + idx - 1;
        event = *iter;
    }
    return event;
}

//searching the indes by inputs of name and end date 
Event* Action::findEventByNameAndEndDate(std::string name, std::string endDate, std::vector<Event*> &events){
    Event* event = NULL;
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
	    if((*iter)->getEndDate() == endDate && (*iter)->getName() == name){
    		event = *iter;
            break;
    	}
    }
    return event;
}

/*
std::vector<std::string> Action::splitWords(std::string input){
	std::vector<std::string> words;
	boost::algorithm::split(words, input, boost::algorithm::is_any_of(WHITESPACE), boost::algorithm::token_compress_on);
	return words;
}

int Action::indexOf(std::vector<std::string> words, std::string toFind){
	return std::distance(words.begin(), std::find(words.begin(), words.end(), toFind));
}

std::string Action::vectorToString(std::vector<std::string> vec){
	std::string result = "";
	for(std::vector<std::string>::iterator iter = vec.begin(); iter != vec.end(); iter++){
		result = result + *iter + " ";
	}
	return result.substr(0, result.length() - 1);
}

std::string Action::extractField(std::vector<std::string> words, int startPos, int endPos){
	if(endPos - startPos < 1){
		return "";
	}else{
		std::vector<std::string> result(endPos - startPos - 1);
		assert(startPos >= 0 && "Invalid start position");
		assert(endPos <= words.size() && "Invalid end position");
		std::copy(words.begin() + startPos + 1, words.begin() + endPos, result.begin());
		return vectorToString(result);
	}
}
*/