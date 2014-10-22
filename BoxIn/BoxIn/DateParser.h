#pragma once
#include "boost\date_time\gregorian\gregorian.hpp"
#include <map>
#include <string>

static const std::string CURRENT_CENTURY = "20";

class DateParser
{
public:
    DateParser(void);
    ~DateParser(void);
    boost::gregorian::date convertToDate(std::string date);
    void setupMap();
private:
    std::map<std::string, std::string> monthMap;
};
