#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\date_time\posix_time\posix_time.hpp"

static const std::string KEYWORD_ARRAY[] = {"name", "date", "time", "place", "field"};
static const std::vector<std::string> KEYWORDS(KEYWORD_ARRAY, KEYWORD_ARRAY+5);

static const std::string CURRENT_CENTURY = "20";
static const int lenDDMMYY = 6;
static const int lenYYYYMMDD = 8;
static const int lenYYYY_MMM_DD = 11;
static const std::string LEGIT_NUMBERS = "0123456789-/";

enum InfoType{
    TypeCommand = 1,
    TypeName,
    TypeDate,
    TypeTime,
    TypePlace,
    TypeField,
    TypeNewValue
};

enum DateFormat{
    DDMMYY = 1,
    YYYYMMDD,
    YYYY_MMM_DD,
    TextDateFormat,
    FormatNotRecognised
};

class SimpleParser
{
private:
    std::map<InfoType, std::string> keywordMap;
    std::map<std::string, std::string> monthMap;
public:
    SimpleParser(void);
    ~SimpleParser(void);
    std::string getField(std::string input, InfoType info);
    void setupMaps();
    bool isKeyword(std::string word);

    boost::gregorian::date convertToDate(std::string date);
    DateFormat matchFormat(std::string date);
    bool isNumericalFormat(std::string date);

    std::string removeEscapeChar(std::string word);
    std::string removeWhitespace(std::string text);
};

