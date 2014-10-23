#pragma once
#include "boost\date_time\posix_time\posix_time.hpp"
#include "boost\date_time\gregorian\gregorian.hpp"

class TimeParser
{
public:
    TimeParser(void);
    ~TimeParser(void);
    boost::posix_time::ptime convertToTime(boost::gregorian::date date, std::string time);
};

