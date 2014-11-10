//@author A0111994B
#include "FileStorage.h"

FileStorage::FileStorage(){
    // non-working constructor
}

FileStorage::FileStorage(std::string filename){
	this->filename = filename;
}

FileStorage::~FileStorage(void){
}

/*
* Takes in a vector of events
* Converts each event into an json object and stores it on an array
* Writes the array into the file
*/
void FileStorage::saveFile(std::vector<Event*> events){
    std::fstream file = std::fstream(filename, std::fstream::out | std::fstream::trunc);
    json_spirit::Array eventArray;
    for(std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); iter++){
        writeEvent(eventArray, *iter);
    }
    write_formatted(eventArray, file);
    file.close();
}

/*
* Converts an event into a json_spirit Object
* Copying all information about that event
* Pushes the object onto the array passed in
*/
void FileStorage::writeEvent(json_spirit::Array &eventArray, Event* event){
    json_spirit::Object eventObj;
    eventObj.push_back(json_spirit::Pair(TAG_NAME, event->getName()));
    eventObj.push_back(json_spirit::Pair(TAG_START_DATE, event->getStartDate()));
    eventObj.push_back(json_spirit::Pair(TAG_END_DATE, event->getEndDate()));
    eventObj.push_back(json_spirit::Pair(TAG_START_TIME, event->getStartTime()));
    eventObj.push_back(json_spirit::Pair(TAG_END_TIME, event->getEndTime()));
    eventObj.push_back(json_spirit::Pair(TAG_PLACE, event->getLocation()));
    eventObj.push_back(json_spirit::Pair(TAG_DONE, event->getDone()));
    eventArray.push_back(eventObj);
}

/*
* Collects the array from the json file
* Reads individual events and pushes them onto a vector
* Returns the vector of event pointers
*/
std::vector<Event*> FileStorage::readFile(){
    std::fstream file = std::fstream(filename, std::fstream::in);
    json_spirit::Value value;
    std::vector<Event*> events;
    read(file, value);
    const json_spirit::Array& eventArray = value.get_array();
    for(unsigned int i = 0; i < eventArray.size(); i++){
        events.push_back(readEvent(eventArray[i].get_obj(), i + 1));
    }
    return events;
}

Event* FileStorage::readEvent(const json_spirit::Object& obj, unsigned int idx){
    Event *event = new Event;
    for(json_spirit::Object::size_type i = 0; i != obj.size(); i++){
        const json_spirit::Pair &pair = obj[i];
        const std::string &name = pair.name_;
        const json_spirit::Value &value = pair.value_;
        if(name == TAG_NAME){event->setName(value.get_str());}
        else if(name == TAG_START_DATE){event->setStartDate(value.get_str());}
        else if(name == TAG_END_DATE){event->setEndDate(value.get_str());}
        else if(name == TAG_START_TIME){event->setStartTime(value.get_str());}
        else if(name == TAG_END_TIME){event->setEndTime(value.get_str());}
        else if(name == TAG_PLACE){event->setLocation(value.get_str());}
        else if(name == TAG_DONE){event->setDone(value.get_bool());}
        else{assert(false&&"Json file corrupted");}
    }
    event->setIdx(idx);
    return event;
}
