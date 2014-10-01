#pragma once

#include "Event.h"

class Logic{
private:
	std::vector<Event*> events;
public:
	Logic(void);
	~Logic(void);

	void add(std::string input);
	void delete(std::string intput);
	void undo();
	void edit(std::string input);
	void reset();

	std::vector<Event*> getEvents();
};

