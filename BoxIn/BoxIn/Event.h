#pragma once

#include "CommonFunctions.h"

class Event{
public:
	Event(void);
	Event(std::string _name, std::string _date, std::string _time);
	~Event(void);
	std::string getName();
	std::string getName();
	std::string getDescription();
	std::string getCategory();
	int getPriority();
	bool getStatus();
	bool setName(std::string);
	bool setPriority(int);
	bool setCategory(std::string);
	bool setDescription(std::string);
	bool setFinish(bool);
	bool contains(std::string);
private:
	std::string name;
	std::string date;
	std::string time;
	std::string _name;
	std::string _description;
	std::string _category;
	int _priority;
	bool _isFinish;

};

