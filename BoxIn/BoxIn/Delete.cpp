#include "Delete.h"


Delete::Delete(std::string input){
	std::vector<std::string> words = splitWords(input);
	int indexDate = indexOf(words, KEYWORD_DATE);
	name = extractField(words, POSITION_FIRST_WORD, indexDate);
    date = extractField(words, indexDate, words.size());
	event = NULL;
}


Delete::~Delete(void){
}

std::string Delete::execute(std::vector<Event*> &events){
	bool found = false;
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			event = *iter;
			events.erase(iter);
			found = true;
			break;
		}
	}
	if(found){
		return event->getName() + " has been deleted!";
	}else{
		return "No item matching " + name + " found.";
	}
}

std::string Delete::undo(std::vector<Event*> &events){
	assert(event != NULL);
	events.push_back(event);
	event = NULL;
	return event->getName() + " has been reinstated!";
}