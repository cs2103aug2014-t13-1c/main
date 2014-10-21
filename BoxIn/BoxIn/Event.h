#pragma once

#include <string>
#include <map>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

static const std::string FIELD_NAME = "name";
static const std::string FIELD_LOCATION = "place";
static const std::string FIELD_DATE = "date";
static const std::string FIELD_TIME = "time";

enum Field {
	FieldName = 1,
	FieldDate,
	FieldTime,
	FieldLocation
};

class Event{
public:
	Event();
	Event(std::string name, std::string date, std::string time);
	Event(std::string name, std::string location, std::string date, std::string time);
	~Event();
	Event* copy();

	std::map<std::string, Field> setupMap();

	std::string getName();
	std::string getDate();
	std::string getTime();
	std::string getLocation();
	void editField(std::string field, std::string newValue);
	void setName(std::string newName);
	void setDate(std::string newDate);
	void setTime(std::string newTime);
	void setLocation(std::string newLocation);
	std::string repr();
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
	std::map<std::string, Field> fieldMap;
	std::string name;
	boost::gregorian::date date;
	boost::posix_time::ptime time;
	// std::string date;
	// std::string time;
	std::string location;
	/*
	std::string _name;
	std::string _description;
	std::string _category;
	int _priority;
	bool _isFinish;
	*/
};
