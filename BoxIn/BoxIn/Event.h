#pragma once

#include <string>
/* Cannot open library??? Will reinclude once linker fixed
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
*/
class Event{
public:
	Event();
	Event(std::string name, std::string date, std::string time);
	Event(std::string name, std::string location, std::string date, std::string time);
	~Event();
	std::string getName();
	std::string getDate();
	std::string getTime();
	std::string getLocation();
	/*
	std::string getDescription();
	std::string getCategory();
	int getPriority();
	bool getStatus();
	bool setName(std::string);
	bool setPriority(int);
	bool setCategory(std::string);
	bool setDescription(std::string);
	bool setFinish(bool);
	bool contains(std::string);*/
private:
	std::string name;
	// boost::gregorian::date date;
	// boost::posix_time::ptime time;
	std::string date;
	std::string time;
	std::string location;
	/*
	std::string _name;
	std::string _description;
	std::string _category;
	int _priority;
	bool _isFinish;
	*/
};

