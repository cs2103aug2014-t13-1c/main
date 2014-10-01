#pragma once

#include "Event.h"
#include <boost/algorithm/string.hpp>

static std::string KEYWORD_LOCATION = "place";
static std::string KEYWORD_DATE = "date";
static std::string KEYWORD_TIME = "time";

class Logic{
private:
	std::vector<Event*> events;
public:
	Logic(void);
	~Logic(void);

	std::vector<std::string> splitWords(std::string input);
	int indexOf(std::vector<std::string> words, std::string toFind);

	void add(std::string input);
	void del(std::string input);
	void undo();
	void edit(std::string input);
	void reset();

	std::vector<Event*> getEvents();
};

