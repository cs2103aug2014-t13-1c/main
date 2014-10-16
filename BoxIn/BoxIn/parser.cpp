#include "parser.h"

using namespace std;

Parser::Parser(void){
	string command = "";
	string name = "";
	string location = "";
	string date = "";
	string time = "";
	string index = "";
}

void Parser::setInput(KEYWORD choice){
	switch (choice){
	case ADD:
		command = "Add";
		break;
	case DISPLAY:
		command = "Display";
		break;
	case DELETE:
		command = "Delete";
		break;
	case EDIT:
		command = "Edit";
		break;
	case UNDO:
		command = "Undo";
		break;
	case RESET:
		command = "Reset";
		break;
	default:
		command = "Invalid";
	}
}

string Parser::getCommand(){
	return command;
}

string Parser::getName(){
	return name;
}

string Parser::getLocation(){
	return location;
}

string Parser::getDate(){
	return date;
}

string Parser::getTime(){
	return time;
}

string Parser::getIndex(){
	return index;
}

Parser::KEYWORD Parser::getKeyword(string keyword){
	int i = 0;
	if (boost::iequals(keyword, "Add"))
		i = 1;
	else if (boost::iequals(keyword, "Display"))
		i = 2;
	else if (boost::iequals(keyword, "Delete"))
		i = 3;
	else if (boost::iequals(keyword, "Edit"))
		i = 4;
	else if (boost::iequals(keyword, "Undo"))
		i = 5;
	else if (boost::iequals(keyword, "Reset"))
		i = 6;
	else if (boost::iequals(keyword, "Date"))
		i = 7;
	else if (boost::iequals(keyword, "Time"))
		i = 8;
	else i = 9;
	return KEYWORD(i);
}

string Parser::getFirstWord(string command){
	stringstream str;
	string firstWord;
	str << command;
	str >> firstWord;
	return firstWord;
}

int Parser::getDateIndex(string command){
	int index;
	string date[] = { " today", " tomorrow", " monday",
		" tuesday", " wednesday", " thursday", " friday",
		" saturday", " sunday" };
	for (int i = 0; i < 9; i++){
		index = command.find(date[i]);
	}
	return index;
}

string Parser::editDate(string command){
	int index;
	index = getDateIndex(command);
	command.insert(index + 1, "Date ");
	return command;
}

int Parser::getNextIndex(vector<string>index, int initial){
	int i = 0;
	for (i = initial; i < index.size(); i++){
		if (isKeyword(index[i]))
			break;
	}
	return i;
}

bool Parser::isKeyword(string word){
	bool value = false;
	if (getKeyword(word) != INVALID)
		value = true;
	return value;
}

bool Parser::hasName(){
	if (name == "")
		return false;
	return true;
}

bool Parser::hasLocation(){
	if (location == "")
		return false;
	return true;
}

bool Parser::hasIndex(){
	if (index == "")
		return false;
	return true;
}

bool Parser::hasTime(){
	if (time == "")
		return false;
	return true;
}

bool Parser::hasDate(){
	if (date == "")
		return false;
	return true;
}

bool Parser::canDo(string keyword){
	bool value = false;
	if (boost::iequals(keyword, "Add")){
		if (canAdd())
			value = true;
	}
	else if (boost::iequals(keyword, "Display")){
		if (canDisplay())
			value = true;
	}
	else if (boost::iequals(keyword, "Delete")){
		if (canDelete())
			value = true;
	}
	else if (boost::iequals(keyword, "Edit")){
		if (canEdit())
			value = true;
	}
	else if (boost::iequals(keyword, "Undo"))
		value = true;
	else if (boost::iequals(keyword, "Reset"))
		value = true;
	return value;
}

bool Parser::canAdd(){
	if (isValidName() && isValidTime() && isValidDate())
		return true;
	return false;
}

bool Parser::isValidName(){
	//stub
	return true;
}

bool Parser::isValidTime(){
	//stub
	return true;
}

bool Parser::isValidDate(){
	//stub
	return true;
}

bool Parser::canEdit(){
	bool value = false;
	if (hasName())
		if (isValidName())
			value = true;
	if (hasTime())
		if (isValidTime())
			value = true;
	if (hasDate())
		if (isValidDate())
			value = true;
	if (isValidIndex())
		value = true;
	return value;
}

bool Parser::canDisplay(){
	//stub
	return true;
}

bool Parser::canDelete(){
	if (isValidIndex())
		return true;
	return false;
}

bool Parser::isValidIndex(){
	//stub - (self-note use boost tokenizer)
	return true;
}

void Parser::setEventDetails(Event eventObj){
	name = eventObj.getName();
	location = eventObj.getLocation();
	time = eventObj.getTime();
	date = eventObj.getDate();
}