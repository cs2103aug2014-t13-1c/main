//@author A0111994B
#include "SimpleStorage.h"

SimpleStorage::SimpleStorage(){
    file = FileStorage("BoxInData.json");
    events = file.readFile();
    sortCriteria = Time;
}

SimpleStorage::~SimpleStorage(){
}

bool alphaComp(Event* item1, Event* item2){
    return item1->getName() <= item2->getName();
}

bool timeComp(Event* item1, Event* item2){
    return item1->getDate() < item2->getDate() || (item1->getTime() <= item2->getTime() && item1->getDate() == item2->getDate());
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
    sortEvents();
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
    std::sort(events.begin(), events.end(), alphaComp);
    switch(sortCriteria){
    case Time:
        std::sort(events.begin(), events.end(), timeComp);
        break;
    }
}

std::string SimpleStorage::execute(Action* action){
    std::string feedback = action->execute(events);
    pushStack(action);
    return feedback;
}

std::string SimpleStorage::undo(Action* action){
    std::string feedback = action->undo(events);
    return feedback;
}

void SimpleStorage::saveFile(){
    file.saveFile(events);
}