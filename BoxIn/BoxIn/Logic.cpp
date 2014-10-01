#include "Logic.h"


Logic::Logic(void)
{
}


Logic::~Logic(void)
{
}

void Logic::add(std::string input){
	Event *event = new Event("Tutorial", "123456", "1100");
	events.push_back(event);
}

void delete(std::string intput){
	//logic code
}

void undo(){
	//Logic code
	events.pop_back();
}

void edit(std::string input){
	//logic code
}

void reset(){
	//logic code
	events.clear();
}

std::vector<Event*> Logic::getEvents(){
	return events;
}
