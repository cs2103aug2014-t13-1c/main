//@author A0111994B
#include "SimpleStorage.h"
#include "boost\date_time\gregorian\gregorian.hpp"

SimpleStorage::SimpleStorage(){
    file = FileStorage(BOXIN_DATA_FILENAME);
    try{
        events = file.readFile();
    }catch(std::exception &e){
        // exists in case file does not exist, then events can just be an empty vector
    }
    sortCriteria = CriteriaTime;
}

SimpleStorage::~SimpleStorage(){
}

bool idxComp(Event* item1, Event* item2){
    return item1->getIdx() < item2->getIdx();
}

bool alphaComp(Event* item1, Event* item2){
    if(item1->getName() == item2->getName()){return idxComp(item1, item2);}
    return item1->getName() <= item2->getName();
}

bool startTimeComp(Event* item1, Event* item2){
    if(item1->getStartDate().empty() && item2->getStartDate().empty()){return alphaComp(item1, item2);}
    else if(item1->getStartDate().empty()){return true;}
    else if(item2->getStartDate().empty()){return false;}
    boost::gregorian::date date1 = boost::gregorian::date(boost::gregorian::from_simple_string(item1->getStartDate()));
    boost::gregorian::date date2 = boost::gregorian::date(boost::gregorian::from_simple_string(item2->getStartDate()));
    if(date1==date2 && item1->getStartTime()==item2->getStartTime()){return alphaComp(item1, item2);}
    return (date1 < date2) || (item1->getStartTime() <= item2->getStartTime() && date1 == date2);
}

bool endTimeComp(Event* item1, Event* item2){
    if(item1->getEndDate().empty() && item2->getEndDate().empty()){return startTimeComp(item1, item2);}
    else if(item1->getEndDate().empty()){return true;}
    else if(item2->getEndDate().empty()){return false;}
    boost::gregorian::date date1 = boost::gregorian::date(boost::gregorian::from_simple_string(item1->getEndDate()));
    boost::gregorian::date date2 = boost::gregorian::date(boost::gregorian::from_simple_string(item2->getEndDate()));
    if(date1==date2 && item1->getEndTime()==item2->getEndTime()){return startTimeComp(item1, item2);}
    return (date1 < date2) || (item1->getEndTime() <= item2->getEndTime() && date1 == date2);
}

std::vector<Event*> SimpleStorage::getEvents(){
    return events;
}

void SimpleStorage::pushStack(Action* action){
    actionStack.push(action);
}

Action* SimpleStorage::popLastAction(){
    if(actionStack.empty()){throw std::exception("Nothing to undo");}
    Action* action = actionStack.top();
    actionStack.pop();
    return action;
}

void SimpleStorage::sortEvents(){
    std::stable_sort(events.begin(), events.end(), alphaComp);
    std::stable_sort(events.begin(), events.end(), startTimeComp);
    std::stable_sort(events.begin(), events.end(), endTimeComp);
    switch(sortCriteria){
    case CriteriaTime:
        break;
    }
    for(unsigned int i = 0; i < events.size(); i++){
        events[i]->setIdx(i+1);
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
    sortEvents();
    return feedback;
}

void SimpleStorage::saveFile(){
    file.saveFile(events);
}