//@author A0111994
#pragma once

#include "json_spirit.h"
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"
#include <iostream>

static const std::string TAG_NAME = "Name";
static const std::string TAG_START_DATE = "Start_Date";
static const std::string TAG_END_DATE = "End_Date";
static const std::string TAG_START_TIME = "Start_Time";
static const std::string TAG_END_TIME = "End_Time";
static const std::string TAG_PLACE = "Place";
static const std::string TAG_DONE = "Done";

class FileStorage
{
public:
    FileStorage();
	FileStorage(std::string filename);
	~FileStorage(void);
	void saveFile(std::vector<Event*>);
    void writeEvent(json_spirit::Array &eventArray, Event* event);
	std::vector<Event*> readFile();
    Event* readEvent(const json_spirit::Object& obj, unsigned int idx);
private:
	std::string filename;
};

