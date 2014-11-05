#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\date_time\posix_time\posix_time.hpp"

static const std::string KEYWORD_ARRAY[] = {"name", "edate", "etime", "place", "field", "stime", "sdate"};
static const std::vector<std::string> KEYWORDS(KEYWORD_ARRAY, KEYWORD_ARRAY+7);

static const std::string CURRENT_CENTURY = "20";
static const int lenDDMMYY = 6;
static const int lenYYYYMMDD = 8;
static const int lenYYYY_MMM_DD = 11;
static const int LEN_DAY_OF_WEEK = 3;
static const std::string LEGIT_DATE_NUMBERS = "0123456789-/";
static const std::string LEGIT_NUMBERS = "0123456789";

namespace Days{
    static const std::string MONDAY = "monday";
    static const std::string TUESDAY = "tuesday";
    static const std::string WEDNESDAY = "wednesday";
    static const std::string THURSDAY = "thursday";
    static const std::string FRIDAY = "friday";
    static const std::string SATURDAY = "saturday";
    static const std::string SUNDAY = "sunday";
};

enum InfoType{
    TypeCommand = 1,
    TypeName,
    TypeStartDate,
    TypeStartTime,
    TypeEndDate,
    TypeEndTime,
    TypePlace,
    TypeField,
    TypeNewValue
};

// Some formats are not in naming convention to preserve the DDMMYYYY etc in caps
enum DateFormat{
    DDMMYY = 1,
    YYYYMMDD,
    YYYY_MMM_DD,
    TextDateFormat,
    DayOfWeek,
    FormatNotRecognised
};

class SimpleParser
{
private:
    std::map<InfoType, std::string> keywordMap;
    std::map<std::string, std::string> monthMap;
    std::map<std::string, boost::date_time::weekdays> dayMap;
public:
    SimpleParser(void);
    ~SimpleParser(void);
    std::string getField(std::string input, InfoType info);
    void setupMaps();
    bool isKeyword(std::string word);
    bool isInteger(std::string text);

    boost::gregorian::date convertToDate(std::string date);
    DateFormat matchFormat(std::string date);
    bool isNumericalFormat(std::string date);
    bool isDayOfWeek(std::string date);

    std::string removeEscapeChar(std::string word);
    std::string removeWhitespace(std::string text);
};

