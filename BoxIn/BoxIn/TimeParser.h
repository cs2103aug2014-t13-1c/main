//@author A0111994
#pragma once
#include "boost\date_time\posix_time\posix_time.hpp"
#include "boost\date_time\gregorian\gregorian.hpp"

static const int SIZE_HHMM = 4;
static const int SIZE_HH_MM = 5;
static const int SIZE_EMPTY = 0;

class TimeParser
{
public:
    TimeParser(void);
    ~TimeParser(void);
    boost::posix_time::ptime convertToTime(boost::gregorian::date date, std::string time);
};
