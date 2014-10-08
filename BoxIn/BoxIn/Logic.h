#pragma once

#include "Add.h"
#include "Delete.h"
#include "Edit.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

static const std::string USER_COMMAND_ADD = "add";
static const std::string USER_COMMAND_DELETE = "delete";
static const std::string USER_COMMAND_EDIT = "edit";
static const std::string USER_COMMAND_EXIT = "exit";
static const std::string USER_COMMAND_UNDO = "undo";

enum CommandType {
	CommandAdd = 1,
	CommandDelete,
	CommandEdit,
	CommandUndo,
	CommandExit
};


class Logic{
private:
	std::vector<Event*> events;
	std::map<std::string, CommandType> stringToCommand;

public:
	Logic();
	~Logic();

	void setupMap();
	std::string handleUserInput(std::string input);

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

