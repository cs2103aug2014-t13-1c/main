//@author A0111994B
#include "Search.h"

Search::Search(std::string input){
    criteria = parser.getField(input, TypeName);
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