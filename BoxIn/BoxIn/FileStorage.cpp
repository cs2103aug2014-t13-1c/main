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
    json_spirit::Array eventArray;
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
        writeEvent(eventArray, *iter);
    }
    write_formatted(eventArray, file);
    file.close();
}

void FileStorage::writeEvent(json_spirit::Array &eventArray, Event* event){
    json_spirit::Object eventObj;
    eventObj.push_back(json_spirit::Pair(TAG_NAME, event->getName()));
    eventObj.push_back(json_spirit::Pair(TAG_DATE, event->getDate()));
    eventObj.push_back(json_spirit::Pair(TAG_TIME, event->getTime()));
    eventObj.push_back(json_spirit::Pair(TAG_PLACE, event->getLocation()));

    eventArray.push_back(eventObj);
}

std::vector<Event*> FileStorage::readFile(){
    std::fstream file = std::fstream(filename, std::fstream::in);
    json_spirit::Value value;
    std::vector<Event*> events;
    read(file, value);
    const json_spirit::Array& eventArray = value.get_array();
    for(unsigned int i = 0; i < eventArray.size(); i++){
        events.push_back(readEvent(eventArray[i].get_obj()));
    }
    return events;
}

Event* FileStorage::readEvent(const json_spirit::Object& obj){
    Event *event = new Event;
    for(json_spirit::Object::size_type i = 0; i != obj.size(); i++){
        const json_spirit::Pair &pair = obj[i];
        const std::string &name = pair.name_;
        const json_spirit::Value &value = pair.value_;
        if(name == TAG_NAME){event->setName(value.get_str());}
        else if(name == TAG_DATE){event->setDate(value.get_str());}
        else if(name == TAG_TIME){event->setTime(value.get_str());}
        else if(name == TAG_PLACE){event->setLocation(value.get_str());}
        else{assert(false&&"Json file corrupted");}
    }
    return event;
}