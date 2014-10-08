#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <boost\algorithm\string.hpp>
#include "Event.h"

using namespace std;

class Parser{
private:
	string command;
	string name;
	string location;
	string date;
	string time;
	string index;

	enum KEYWORD{
		ADD=1, DISPLAY, DELETE, EDIT, UNDO, RESET, DATE, TIME, INVALID
	};
	
public:
	Parser(void);
	void setInput(KEYWORD);
	bool isKeyword(string);
	string getCommand();
	string getName();
	string getLocation();
	string getDate();
	string getTime();
	string getIndex();
	KEYWORD getKeyword(string);
	string getFirstWord(string);
	int getDateIndex(string);
	string editDate(string);
	int getNextIndex(vector<string>, int);

	bool hasName();
	bool hasLocation();
	bool hasIndex();
	bool hasTime();
	bool hasDate();
	bool canDo(string);
	bool canAdd();
	bool canEdit();
	bool isValidName();
	bool isValidTime();
	bool isValidDate();
	bool canDisplay();
	bool canDelete();
	bool isValidIndex();

	void setEventDetails(Event);

	~Parser(void);
};