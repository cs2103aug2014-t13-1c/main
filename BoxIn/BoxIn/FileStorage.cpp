#include "FileStorage.h"

FileStorage::FileStorage(){
    // non-working constructor
}

FileStorage::FileStorage(std::string filename){
	this->filename = filename;
}

FileStorage::~FileStorage(void){
}

void FileStorage::saveFile(std::vector<Event*> events){
    std::fstream file = std::fstream(filename, std::fstream::out | std::fstream::trunc);
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
        json_spirit::Object eventObj;
        eventObj.push_back(json_spirit::Pair("Name", (*iter)->getName()));
        eventObj.push_back(json_spirit::Pair("Date", (*iter)->getDate()));
        json_spirit::write_formatted(eventObj, file);
    }
    file.close();
}