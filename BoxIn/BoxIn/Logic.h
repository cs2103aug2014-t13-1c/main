#pragma once

#include <string>
#include <vector>
#include "Event.h"

class Logic{
private:
	std::vector<Event*> events;
public:
	Logic(void);
	~Logic(void);

	void add(std::string input);

	std::vector<Event*> getEvents();
};

