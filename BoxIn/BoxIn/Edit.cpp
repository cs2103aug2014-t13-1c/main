#include "Edit.h"


Edit::Edit(std::string input){
	// do something with parser here
	std::vector<std::string> words = splitWords(input);

	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexField = indexOf(words, KEYWORD_FIELD);

	field = words[indexField + 1];
	name = extractField(words, POSITION_FIRST_WORD, indexDate);
	date = extractField(words, indexDate, indexField);
	newValue = extractField(words, indexField + 1, words.size());
}


Edit::~Edit(void){
}

std::string Edit::execute(std::vector<Event*> &events){
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			oldEvent = *iter;
			events.erase(iter);
			break;
		}
	}

	newEvent = oldEvent->copy();
	newEvent->editField(field, newValue);
	events.push_back(newEvent);

	return newEvent->getName() + " has been edited!";	
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
	oldEvent = NULL;
	newEvent = NULL;
	return events[events.size()-1]->getName() + " has been un-edited!";
}