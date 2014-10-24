#pragma once

#include "action.h"

class Add :
	public Action
{
private:
	Event *event;
    SimpleParser parser;
public:
	Add(std::string input);
	~Add(void);
	std::string execute(std::vector<Event*> &events);
	std::string undo(std::vector<Event*> &events);
};

