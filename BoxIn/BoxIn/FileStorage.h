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
	std::vector<Event*> readFile();
private:
	std::string filename;
};

