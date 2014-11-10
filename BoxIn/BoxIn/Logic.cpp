//@author A0111994B
#include "Logic.h"


Logic::Logic(){
	setupMap();
    filter = Filter::None;
}

Logic::~Logic(){
}

/*different commands
*put the commands into different commands 
*calls out the different commands using the paarser later on*/

void Logic::setupMap(){
	stringToCommand[USER_COMMAND_ADD] = CommandAdd;
	stringToCommand[USER_COMMAND_DELETE] = CommandDelete;
	stringToCommand[USER_COMMAND_EDIT] = CommandEdit;
	stringToCommand[USER_COMMAND_UNDO] = CommandUndo;
	stringToCommand[USER_COMMAND_EXIT] = CommandExit;
	stringToCommand[USER_COMMAND_SEARCH] = CommandSearch;
    stringToCommand[USER_COMMAND_UNDO] = CommandUndo;
    stringToCommand[USER_COMMAND_MARK] = CommandMark;
    stringToCommand[USER_COMMAND_FILTER] = CommandFilter;
    stringToCommand[USER_COMMAND_HELP] = CommandHelp;

    stringToFilter[Filter::FILTER_NONE] = Filter::None;
    stringToFilter[Filter::FILTER_DONE] = Filter::Done;
    stringToFilter[Filter::FILTER_NOT_DONE] = Filter::NotDone;
    stringToFilter[Filter::FILTER_PAST] = Filter::Past;
    stringToFilter[Filter::FILTER_UPCOMING] = Filter::Upcoming;
}
/*
std::vector<std::string> Logic::splitWords(std::string input){
	std::vector<std::string> words;
	boost::algorithm::split(words, input, boost::algorithm::is_any_of(WHITESPACE), boost::algorithm::token_compress_on);
	return words;
}
*/

/*
* Extracts the first word from the user command and creates the appropriate
* Command type and executes it, also pushing undo-able commands onto the stack
* Then saves the file to the json file
*/
std::string Logic::handleUserInput(std::string input){
	std::string firstWord = parser.getField(input, TypeCommand);
	std::string feedback = "Done!";
	Action *action = NULL;
    QHelpWindow* help = new QHelpWindow();
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
            try{
                action = storage.popLastAction();
                feedback = storage.undo(action);
                delete action;
                action = NULL;
            }catch(std::exception &e){
                feedback = "Nothing to undo";
            }
			break;
		case CommandSearch :
			action = new Search(input);
			storage.execute(action);
			action = NULL;
			break;
        case CommandMark :
            action = new Mark(input);
            break;
        case CommandFilter :
            filter = stringToFilter[parser.getField(input, TypeName)];
            break;
        case CommandHelp :
            help->show();
            feedback = "";
            break;
		default :
			feedback = "Command is not recognised";
			break;
	}
	if(action != NULL){
		feedback = storage.execute(action);
	}
    storage.saveFile();
	return feedback;
}

/*
* Returns the vector of events in storage that fulfill the filter criteria
* The default filter is None
*/
std::vector<Event*> Logic::getEvents(){
    std::vector<Event*> events = storage.getEvents();
    std::vector<Event*> filteredEvents;
    switch(filter){
    case Filter::None :
	    filteredEvents = events;
        break;
    case Filter::Done :
        std::copy_if(events.begin(), events.end(), std::back_inserter(filteredEvents), isDone);
        break;
    case Filter::NotDone :
        std::copy_if(events.begin(), events.end(), std::back_inserter(filteredEvents), isNotDone);
        break;
    case Filter::Past :
        std::copy_if(events.begin(), events.end(), std::back_inserter(filteredEvents), isPast);
        break;
    case Filter::Upcoming :
        std::copy_if(events.begin(), events.end(), std::back_inserter(filteredEvents), isFuture);
        break;
    default :
        filteredEvents = events;
        break;
    }
    return filteredEvents;
}

bool checkDone(Event* event, bool mode){    
    if(mode){return event->getDone();}
    else{return !event->getDone();}
}

bool checkPast(Event* event, bool mode){
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    bool res = (event->getPosixStartTime() < now || event->getPosixEndTime() < now);
     if(mode){return res;}
    else{return !res;}
}

//marks if each event is done or not and if it is complete
bool isDone(Event* event){
    return checkDone(event, true);
}

bool isNotDone(Event* event){
    return checkDone(event, false);
}

bool isPast(Event* event){
    return checkPast(event, true);
}

bool isFuture(Event* event){
    return checkPast(event, false);
}
