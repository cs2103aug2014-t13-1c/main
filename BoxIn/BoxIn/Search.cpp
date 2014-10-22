//@author A0111994B
#include "Search.h"

Search::Search(std::string input){
	std::vector<std::string> words = splitWords(input);
	criteria = extractField(words, POSITION_FIRST_WORD, words.size());
}


Search::~Search(void){
}

std::string Search::execute(){
	return "";
}

std::string Search::undo(){
	// will never be called
	return "";
}