#pragma once

#include <string>

class Event{
public:
	Event(void);
	Event(std::string _name, std::string _date, std::string _time);
	~Event(void);
	std::string getName();
private:
	std::string name;
	std::string date;
	std::string time;
};

