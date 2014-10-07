#pragma once
#include "action.h"

class Delete :
	public Action
{
private:
	Event *event;
	std::string name;
	std::string date;
public:
	Delete(std::string input);
	~Delete(void);
	std::string execute(std::vector<Event*>&);
	std::string undo(std::vector<Event*>&);
};

