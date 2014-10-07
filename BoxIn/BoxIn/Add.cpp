#include "Add.h"


Add::Add(std::string input){
	std::vector<std::string> words = splitWords(input);
	
	int indexLocation = indexOf(words, KEYWORD_LOCATION);
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexTime = indexOf(words, KEYWORD_TIME);

	std::string name = extractField(words, POSITION_FIRST_WORD, indexLocation);
	std::string location  = extractField(words, indexLocation, indexDate);
	std::string date = extractField(words, indexDate, indexTime);
	std::string time = extractField(words, indexTime, words.size());

	event = new Event(name, location, date, time);
}

Add::~Add(void){
}

std::string Add::execute(std::vector<Event*> &events){
	events.push_back(event);
	return event->getName() + " has been added!";
}

std::string Add::undo(std::vector<Event*> &events){
	// stub
	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if(*iter == event){
			events.erase(iter);
		}
	}
	return event->getName() + " was deleted";
}