#pragma once

#include "json_spirit.h"
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"

class FileStorage
{
public:
	FileStorage(std::string filename);
	~FileStorage(void);
	void saveFile(std::vector<Event*>);
	std::vector<Event*> readFile();
private:
	std::string filename;
};

