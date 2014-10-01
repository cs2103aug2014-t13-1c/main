#include "Logic.h"


Logic::Logic(void)
{
}


Logic::~Logic(void)
{
}

std::vector<std::string> Logic::splitWords(std::string input){
	std::vector<std::string> words;
	return boost::algorithm::split(words, input, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);
}

int Logic::indexOf(std::vector<std::string> words, std::string toFind){
	return std::distance(words.begin(), std::find(words.begin(), words.end(), toFind));
}

void Logic::add(std::string input){
	Event *event = new Event("Tutorial", "123456", "1100");
	std::vector<std::string> words = splitWords(input);
	
	int indexLocation = indexOf(words, KEYWORD_LOCATION);
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexTime = indexOf(words, KEYWORD_TIME);

	events.push_back(event);
}

void Logic::del(std::string input){
	//logic code
}

void Logic::undo(){
	//Logic code
	events.pop_back();
}

void Logic::edit(std::string input){
	//logic code
}

void Logic::reset(){
	//logic code
	events.clear();
}

std::vector<Event*> Logic::getEvents(){
	return events;
}
