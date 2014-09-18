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

	void add(std::string stuff);

	std::vector<Event*> getEvents();
};

