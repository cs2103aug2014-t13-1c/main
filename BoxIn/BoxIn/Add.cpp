#include "Add.h"


Add::Add(std::string input){
	std::vector<std::string> words = splitWords(input);
	
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexTime = indexOf(words, KEYWORD_TIME);
	int indexLocation = indexOf(words, KEYWORD_LOCATION);

	std::string name = extractField(words, POSITION_FIRST_WORD, indexDate);
	std::string date = extractField(words, indexDate, indexTime);
	std::string time = extractField(words, indexTime, indexLocation);
	std::string location = extractField(words, indexLocation, words.size());

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
			break;
		}
	}
	return event->getName() + " was deleted";
}