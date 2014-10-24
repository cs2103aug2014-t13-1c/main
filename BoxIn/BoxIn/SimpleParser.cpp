#include "SimpleParser.h"


SimpleParser::SimpleParser(void){
    setupMap();
}


SimpleParser::~SimpleParser(void){
}

std::map<InfoType, std::string> SimpleParser::setupMap(){
    keywordMap[TypeName] = "name";
    keywordMap[TypeDate] ="date";
    keywordMap[TypeTime] = "time";
    keywordMap[TypePlace] = "place";
    return keywordMap;
}

std::string SimpleParser::getField(std::string input, InfoType info){
    std::string keyword = keywordMap[info];
}