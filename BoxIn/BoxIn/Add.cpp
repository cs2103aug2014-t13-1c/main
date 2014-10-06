#include "Add.h"


Add::Add(std::string input){
	std::vector<std::string> words = splitWords(input);
	
	int indexLocation = indexOf(words, KEYWORD_LOCATION);
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexTime = indexOf(words, KEYWORD_TIME);

	name = extractField(words, POSITION_FIRST_WORD, indexLocation);
	location = extractField(words, indexLocation, indexDate);
	date = extractField(words, indexDate, indexTime);
	time = extractField(words, indexTime, words.size());
}

Add::~Add(void){
}

std::string Add::execute(std::vector<Event*> &events){
	Event *event = new Event(name, location, date, time);
	events.push_back(event);
	return "Success!";
}

std::string Add::undo(std::vector<Event*>&){
	// stub
	return "";
}