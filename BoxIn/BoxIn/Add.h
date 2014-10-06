#pragma once

#include "action.h"

class Add :
	public Action
{
private:
	std::string name;
	std::string location;
	std::string date;
	std::string time;
public:
	Add(std::string input);
	~Add(void);
	std::string execute(std::vector<Event*>&);
	std::string undo(std::vector<Event*>&);
};

