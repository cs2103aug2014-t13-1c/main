#pragma once

#include "Event.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <vector>

static std::string KEYWORD_LOCATION = "place";
static std::string KEYWORD_DATE = "date";
static std::string KEYWORD_TIME = "time";

class Logic{
private:
	std::vector<Event*> events;
public:
	Logic();
	~Logic();

	std::vector<std::string> splitWords(std::string input);
	int indexOf(std::vector<std::string> words, std::string toFind);
	std::string vectorToString(std::vector<std::string> vec);
	std::string extractField(std::vector<std::string> words, int startPos, int endPos);

	void add(std::string input);
	void del(std::string input);
	void undo();
	void edit(std::string input);
	void reset();

	std::vector<Event*> getEvents();
};

