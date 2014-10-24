#pragma once

#include "Add.h"
#include "Delete.h"
#include "Edit.h"
#include "Search.h"
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

enum CommandType {
	CommandAdd = 1,
	CommandDelete,
	CommandEdit,
	CommandUndo,
	CommandExit,
	CommandSearch
};


class Logic{
private:
	SimpleStorage storage;
	std::map<std::string, CommandType> stringToCommand;
    SimpleParser parser;

public:
	Logic();
	~Logic();

	void setupMap();
	std::string handleUserInput(std::string input);
	std::vector<std::string> splitWords(std::string input);
	std::vector<Event*> getEvents();
};

