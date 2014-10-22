#pragma once

#include "json_spirit.h"
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"
#include <iostream>

class FileStorage
{
public:
    FileStorage();
	FileStorage(std::string filename);
	~FileStorage(void);
	void saveFile(std::vector<Event*>);
    void writeEvent(json_spirit::Array &eventArray, Event* event);
	std::vector<Event*> readFile();
    Event* readEvent(const json_spirit::Object& obj);
private:
	std::string filename;
};

