//@author A0111994B
#include "Edit.h"

Edit::Edit(std::string input){
	std::vector<std::string> words = splitWords(input);
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexField = indexOf(words, KEYWORD_FIELD);
	if(indexField != words.size()){field = words[indexField + 1];}
	name = extractField(words, POSITION_FIRST_WORD, indexDate);
    date = to_iso_string(dateParser.convertToDate(extractField(words, indexDate, indexField)));
    if(date == to_iso_string(boost::gregorian::date())){date = "";}
	newValue = extractField(words, indexField + 1, words.size());
}


Edit::~Edit(void){
}

std::string Edit::execute(std::vector<Event*> &events){
	bool success = false;
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
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