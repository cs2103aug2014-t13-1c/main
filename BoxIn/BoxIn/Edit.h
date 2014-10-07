#pragma once
#include "action.h"
class Edit :
	public Action
{
private:
	Event* oldEvent;
	Event* newEvent;
	std::string name;
	std::string date;
	std::string field;
	std::string newValue;
public:
	Edit(std::string input);
	~Edit(void);
	std::string execute(std::vector<Event*> &events);
	std::string undo(std::vector<Event*> &events);
};

