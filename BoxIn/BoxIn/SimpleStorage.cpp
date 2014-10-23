//@author A0111994B
#include "SimpleStorage.h"
#include "boost\date_time\gregorian\gregorian.hpp"

SimpleStorage::SimpleStorage(){
    file = FileStorage("BoxInData.json");
    try{
        events = file.readFile();
    }
    catch(std::exception &e){
        // exists in case file does not exist, then events can just be an empty vector
    }
    sortCriteria = CriteriaTime;
}

SimpleStorage::~SimpleStorage(){
}

bool alphaComp(Event* item1, Event* item2){
    return item1->getName() <= item2->getName();
}

bool timeComp(Event* item1, Event* item2){
    if(item1->getDate()==""){return true;}
    else if(item2->getDate()==""){return false;}
    boost::gregorian::date date1 = boost::gregorian::date(boost::gregorian::from_simple_string(item1->getDate()));
    boost::gregorian::date date2 = boost::gregorian::date(boost::gregorian::from_simple_string(item2->getDate()));
    return (date1 < date2) || (item1->getTime() <= item2->getTime() && date1 == date2);
}

std::vector<Event*> SimpleStorage::getEvents(){
    return events;
}

void SimpleStorage::pushStack(Action* action){
    actionStack.push(action);
}

Action* SimpleStorage::popLastAction(){
    if(actionStack.empty()){throw "Nothing to undo";}
    Action* action = actionStack.top();
    actionStack.pop();
    return action;
}

void SimpleStorage::addEvent(Event* event){
    events.push_back(event);
}

std::string SimpleStorage::removeEvent(std::string name, std::string date){
    bool found;
    Event *item;
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
		if((*iter)->getDate() == date && (*iter)->getName() == name){
			item = *iter;
			events.erase(iter);
			found = true;
			break;
		}
	}
	if(found){
		return item->getName() + " has been deleted!";
	}else{
		return "No item matching " + name + " found.";
	}
}

void SimpleStorage::sortEvents(){
    std::stable_sort(events.begin(), events.end(), alphaComp);
    std::stable_sort(events.begin(), events.end(), timeComp);
    switch(sortCriteria){
    case CriteriaTime:
        std::stable_sort(events.begin(), events.end(), timeComp);
        break;
    }
}

std::string SimpleStorage::execute(Action* action){
    std::string feedback = action->execute(events);
    pushStack(action);
    sortEvents();
    return feedback;
}

std::string SimpleStorage::undo(Action* action){
    std::string feedback = action->undo(events);
    // sortEvents();
    return feedback;
}

void SimpleStorage::saveFile(){
    file.saveFile(events);
}