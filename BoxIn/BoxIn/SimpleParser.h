#pragma once

#include <string>
#include <sstream>
#include <map>

enum InfoType{
    TypeCommand = 1,
    TypeName,
    TypeDate,
    TypeTime,
    TypePlace
};

class SimpleParser
{
private:
    std::map<InfoType, std::string> keywordMap;
public:
    SimpleParser(void);
    ~SimpleParser(void);
    std::string getField(std::string input, InfoType info);
    std::map<InfoType, std::string> setupMap();
};

