#include "Logic.h"


Logic::Logic(){
	setupMap();
}

Logic::~Logic(){
}

void Logic::setupMap(){
	stringToCommand[USER_COMMAND_ADD] = CommandAdd;
	stringToCommand[USER_COMMAND_DELETE] = CommandDelete;
	stringToCommand[USER_COMMAND_EDIT] = CommandEdit;
	stringToCommand[USER_COMMAND_UNDO] = CommandUndo;
	stringToCommand[USER_COMMAND_EXIT] = CommandExit;
	stringToCommand[USER_COMMAND_SEARCH] = CommandSearch;
}

std::vector<std::string> Logic::splitWords(std::string input){
	std::vector<std::string> words;
	boost::algorithm::split(words, input, boost::algorithm::is_any_of(WHITESPACE), boost::algorithm::token_compress_on);
	return words;
}

std::string Logic::handleUserInput(std::string input){
	std::vector<std::string> words = splitWords(input);
	std::string firstWord = words[POSITION_FIRST_WORD];
	std::string feedback = "Done!";
	Action *action = NULL;
	switch(stringToCommand[firstWord]){
		case CommandAdd :
			action = new Add(input);
			break;
		case CommandDelete :
			action = new Delete(input);
			break;
		case CommandEdit :
			action = new Edit(input);
			break;
		case CommandExit :
			break;
		case CommandUndo :
			break;
		case CommandSearch :
			action = new Search(input);
			storage.execute(action);
			action = NULL;
			break;
		default :
			feedback = "Command is not recognised";
			break;
	}
	if(action != NULL){
		feedback = storage.execute(action);
	}
	return feedback;
}

std::vector<Event*> Logic::getEvents(){
	return storage.getEvents();
}
