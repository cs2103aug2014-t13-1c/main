//@author A0111994
#pragma once
#include "action.h"

class Delete :
	public Action
{
private:
	Event *event;
	std::string name;
	std::string date;
    SimpleParser parser;
public:
	Delete(std::string input);
	~Delete(void);
	std::string execute(std::vector<Event*> &events);
	std::string undo(std::vector<Event*> &events);
};

