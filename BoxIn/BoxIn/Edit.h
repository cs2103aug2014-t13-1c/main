#pragma once
#include "action.h"
class Edit :
	public Action
{
protected:
	Event* oldEvent;
	Event* newEvent;
	std::string name;
	std::string date;
	std::string field;
	std::string newValue;
    SimpleParser parser;
public:
    Edit();
	Edit(std::string input);
	~Edit(void);
	std::string execute(std::vector<Event*> &events);
	std::string undo(std::vector<Event*> &events);
    void deleteEvent(std::vector<Event*> &events, Event* event);
    Event* findEventByIdx(int idx, std::vector<Event*> &events);
    Event* findEventByNameAndEndDate(std::string name, std::string endDate, std::vector<Event*> &events);
};

