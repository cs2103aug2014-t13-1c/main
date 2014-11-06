//@author A0111994
#include "TimeParser.h"


TimeParser::TimeParser(void){
}


TimeParser::~TimeParser(void){
}

boost::posix_time::ptime TimeParser::convertToTime(boost::gregorian::date date, std::string time){
    if(time.size() == SIZE_HHMM){
        int hours = stoi(time.substr(0,2));
        int minutes = stoi(time.substr(2,2));
        return boost::posix_time::ptime(date, boost::posix_time::time_duration(hours, minutes, 0));
    }else if(time.size() == SIZE_EMPTY){
        boost::posix_time::ptime time = boost::posix_time::ptime(date, boost::posix_time::time_duration(0, 0, 0));
        return time;
    }else{
        return boost::posix_time::ptime(date, boost::posix_time::time_duration(stoi(time.substr(0,2)), stoi(time.substr(3,2)),0));
    }
}
