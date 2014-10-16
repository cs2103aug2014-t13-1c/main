#pragma once
#include "action.h"

class Search :
	public Action
{
public:
	Search(std::string input);
	~Search(void);
	std::string execute();
	std::string undo();
private:
	std::string criteria;
};

