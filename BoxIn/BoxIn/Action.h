#pragma once

#include <string>
#include <Event.h>
#include <vector>
#include <boost\algorithm\string.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <SimpleParser.h>

static const std::string KEYWORD_LOCATION = "place";
static const std::string KEYWORD_DATE = "date";
static const std::string KEYWORD_TIME = "time";
static const std::string KEYWORD_FIELD = "field";

static const int POSITION_FIRST_WORD = 0;
static const std::string WHITESPACE = " ";

class Action{
public:
	Action(void);
	~Action(void);
	virtual std::string execute(std::vector<Event*>&);
	virtual std::string undo(std::vector<Event*>&);

	std::vector<std::string> splitWords(std::string input);
	int indexOf(std::vector<std::string> words, std::string toFind);
	std::string vectorToString(std::vector<std::string> vec);
	std::string extractField(std::vector<std::string> words, int startPos, int endPos);
private:
    SimpleParser parser;
};

