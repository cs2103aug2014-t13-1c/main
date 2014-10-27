#pragma once
#include "Event.h"
#include <vector>
#include <stack>
#include <Add.h>
#include <Delete.h>
#include <Edit.h>
#include "FileStorage.h"
#include <algorithm>
#include "CommonFunctions.h"

enum SortCriteria{
    CriteriaTime = 1,
    CriteriaPriority,
    CriteriaName
};

bool alphaComp(Event* item1, Event* item2);
bool timeComp(Event* item1, Event* item2);
//bool priorityComp(Event* item1, Event* item2); // not yet implemented

class SimpleStorage{
private:
    std::vector<Event*> events;
    std::stack<Action*> actionStack;
    FileStorage file;
    SortCriteria sortCriteria;
    // always use alphabetical as secondary sort

public:
	SimpleStorage();
	~SimpleStorage();

    std::vector<Event*> getEvents();
    
    void pushStack(Action* action);
    Action* popLastAction();

    void sortEvents();

    std::string execute(Action* action);
    std::string undo(Action* action);
    
    void saveFile();
};

