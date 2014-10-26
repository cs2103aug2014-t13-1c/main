#pragma once

#include "json_spirit.h"
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"
#include <iostream>

static const std::string TAG_NAME = "Name";
static const std::string TAG_DATE = "Date";
static const std::string TAG_TIME = "Time";
static const std::string TAG_PLACE = "Place";

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

