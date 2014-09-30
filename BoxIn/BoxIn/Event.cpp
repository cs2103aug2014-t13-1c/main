#include "Event.h"


Event::Event(void)
{
}

Event::Event(std::string _name, std::string _date, std::string _time){
	name = _name;
	date = _date;
	time = _time;
}

Event::~Event(void){
}

std::string Event::getName(){
	return name;
}