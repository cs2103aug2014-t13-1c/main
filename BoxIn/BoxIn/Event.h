#pragma once

#include <string>
#include <map>
#include "SimpleParser.h"
#include "TimeParser.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

static const std::string FIELD_NAME = "name";
static const std::string FIELD_LOCATION = "place";
static const std::string FIELD_START_DATE = "sdate";
static const std::string FIELD_END_DATE = "edate";
static const std::string FIELD_START_TIME = "stime";
static const std::string FIELD_END_TIME = "etime";

const static std::string NULL_DATE_TIME = "not-a-date-time";
const static std::string NULL_TIME = "00:00";

enum Field {
	FieldName = 1,
	FieldStartDate,
    FieldEndDate,
	FieldStartTime,
    FieldEndTime,
	FieldLocation
};

class Event{
public:
	Event();
	Event(std::string name, std::string date, std::string time);
	Event(std::string name, std::string location, std::string sdate, std::string edate, std::string stime, std::string etime, int idx, bool recent);
	~Event();
	Event* copy();

	std::map<std::string, Field> setupMap();

	std::string getName();
	std::string getStartDate();
    std::string getEndDate();
	std::string getStartTime();
    std::string getEndTime();
	std::string getLocation();
	void editField(std::string field, std::string newValue);
	void setName(std::string newName);
	void setStartDate(std::string newDate);
    void setEndDate(std::string newDate);
	void setStartTime(std::string newTime);
    void setEndTime(std::string newTime);
	void setLocation(std::string newLocation);
    int getIdx();
    boost::posix_time::ptime getPosixStartTime();
    boost::posix_time::ptime getPosixEndTime();
    void setIdx(int newIdx);
    void removeRecent();
    bool isRecent();
    std::string repr(); // for testing purposes
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
	boost::gregorian::date sdate;
    boost::gregorian::date edate;
	boost::posix_time::ptime stime;
    boost::posix_time::ptime etime;
    std::string nonformattime;
	std::string location;
    SimpleParser parser;
    TimeParser timeParser;
    int idx;
    bool recent;
	/*
	std::string _description;
	std::string _category;
	int _priority;
	bool _isFinish;
	*/
};
