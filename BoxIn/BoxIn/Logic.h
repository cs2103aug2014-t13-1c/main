#pragma once

#include "Add.h"
#include "Delete.h"
#include "Edit.h"
#include "Search.h"
#include "Mark.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include "SimpleStorage.h"

static const std::string USER_COMMAND_ADD = "add";
static const std::string USER_COMMAND_DELETE = "delete";
static const std::string USER_COMMAND_EDIT = "edit";
static const std::string USER_COMMAND_EXIT = "exit";
static const std::string USER_COMMAND_UNDO = "undo";
static const std::string USER_COMMAND_SEARCH = "search";
static const std::string USER_COMMAND_MARK = "mark";
static const std::string USER_COMMAND_FILTER = "view";

enum CommandType {
	CommandAdd = 1,
	CommandDelete,
	CommandEdit,
	CommandUndo,
	CommandExit,
	CommandSearch,
    CommandMark,
    CommandFilter
};

namespace Filter{
    enum FilterType{
        None = 1,
        Done,
        NotDone,
        Upcoming,
        Past
    };

    static const std::string FILTER_NONE = "all";
    static const std::string FILTER_DONE = "done";
    static const std::string FILTER_NOT_DONE = "pending";
    static const std::string FILTER_UPCOMING = "upcoming";
    static const std::string FILTER_PAST = "past";
};

bool checkDone(Event* event, bool mode);
bool checkPast(Event* event, bool mode);

bool isDone(Event* event);
bool isNotDone(Event* event);
bool isPast(Event* event);
bool isFuture(Event* event);

class Logic{
private:
	SimpleStorage storage;
	std::map<std::string, CommandType> stringToCommand;
    std::map<std::string, Filter::FilterType> stringToFilter;
    SimpleParser parser;
    Filter::FilterType filter;

public:
	Logic();
	~Logic();

	void setupMap();
	std::string handleUserInput(std::string input);
	std::vector<std::string> splitWords(std::string input);
	std::vector<Event*> getEvents();

};

