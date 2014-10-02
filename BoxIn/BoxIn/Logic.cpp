#include "Logic.h"


Logic::Logic(){
}


Logic::~Logic(){
}

std::vector<std::string> Logic::splitWords(std::string input){
	std::vector<std::string> words;
	boost::algorithm::split(words, input, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);
	return words;
}

int Logic::indexOf(std::vector<std::string> words, std::string toFind){
	return std::distance(words.begin(), std::find(words.begin(), words.end(), toFind));
}

std::string Logic::vectorToString(std::vector<std::string> vec){
	std::string result = "";
	for(std::vector<std::string>::iterator iter = vec.begin(); iter != vec.end(); iter++){
		result = result + *iter + " ";
	}
	return result.substr(0, result.length() - 1);
}

std::string Logic::extractField(std::vector<std::string> words, int startPos, int endPos){
	std::vector<std::string> result(endPos - startPos - 1);
	std::copy(words.begin() + startPos + 1, words.begin() + endPos, result.begin());
	return vectorToString(result);
}

void Logic::add(std::string input){
	std::vector<std::string> words = splitWords(input);
	
	int indexLocation = indexOf(words, KEYWORD_LOCATION);
	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexTime = indexOf(words, KEYWORD_TIME);

	std::string name = extractField(words, POSITION_FIRST_WORD, indexLocation);
	std::string location = extractField(words, indexLocation, indexDate);
	std::string date = extractField(words, indexDate, indexTime);
	std::string time = extractField(words, indexTime, words.size());
	
	Event *event = new Event(name, location, date, time);
	events.push_back(event);
}

void Logic::del(std::string input){
	std::vector<std::string> words = splitWords(input);

	int indexDate = indexOf(words, KEYWORD_DATE);

	std::string name = extractField(words, POSITION_FIRST_WORD, indexDate);
	std::string date = extractField(words, indexDate, words.size());

	for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			events.erase(iter);
			break;
		}
	}
}

void Logic::undo(){
	//To be implemented. Use secondary storage structure
}

void Logic::edit(std::string input){
	std::vector<std::string> words = splitWords(input);

	int indexDate = indexOf(words, KEYWORD_DATE);
	int indexField = indexOf(words, KEYWORD_FIELD);

	std::string name = extractField(words, POSITION_FIRST_WORD, indexDate);
	std::string date = extractField(words, indexDate, indexField);
	std::string newValue = extractField(words, indexField + 1, words.size());

	for(std::vector<Event*>::iterator iter = events.begin(); iter!= events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			(*iter)->editField(words[indexField + 1], newValue);
		}
	}
	
}

void Logic::reset(){
	//logic code
	events.clear();
}

std::vector<Event*> Logic::getEvents(){
	return events;
}
