#pragma once
#include "boost\date_time\gregorian\gregorian.hpp"
#include <map>
#include <string>

static const std::string CURRENT_CENTURY = "20";
static const int lenDDMMYY = 6;
static const int lenYYYYMMDD = 8;
static const int lenYYYY_MMM_DD = 11;
static const std::string LEGIT_NUMBERS = "0123456789-/";


enum DateFormat{
    DDMMYY = 1,
    YYYYMMDD,
    YYYY_MMM_DD,
    TextDateFormat,
    FormatNotRecognised
};

class SimpleParser
{
public:
    SimpleParser(void);
    ~SimpleParser(void);
    boost::gregorian::date convertToDate(std::string date);
    void setupMap();
private:
    std::map<std::string, std::string> monthMap;
    DateFormat matchFormat(std::string date);
    bool isNumericalFormat(std::string date);
};
