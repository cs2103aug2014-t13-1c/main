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

std::vector<Event*> Logic::getEvents(){
	return events;
}
