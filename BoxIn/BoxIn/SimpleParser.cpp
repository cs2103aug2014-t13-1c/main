#include "SimpleParser.h"


SimpleParser::SimpleParser(void){
    setupMaps();
}


SimpleParser::~SimpleParser(void){
}

void SimpleParser::setupMaps(){
    keywordMap[TypeName] = "name";
    keywordMap[TypeStartDate] = "sdate";
    keywordMap[TypeEndDate] = "edate";
    keywordMap[TypeStartTime] = "stime";
    keywordMap[TypeEndTime] = "etime";
    keywordMap[TypePlace] = "place";
    keywordMap[TypeField] = "field";
    keywordMap[TypeNewValue] = "field";
    monthMap["Jan"] = "01";
    monthMap["Feb"] = "02";
    monthMap["Mar"] = "03";
    monthMap["Apr"] = "04";
    monthMap["May"] = "05";
    monthMap["Jun"] = "06";
    monthMap["Jul"] = "07";
    monthMap["Aug"] = "08";
    monthMap["Sep"] = "09";
    monthMap["Oct"] = "10";
    monthMap["Nov"] = "11";
    monthMap["Dec"] = "12";
}

std::string SimpleParser::getField(std::string input, InfoType info){
    std::string keyword = keywordMap[info];
    std::stringstream stream(input);
    bool found = false;
    std::string command;
    stream >> command;
    if(info == TypeCommand){
        return command;
    }
    if(info != TypeName){
        while(stream){
            std::string currentWord;
            stream >> currentWord;
            if(currentWord == keyword){
                found = true;
                break;
            }
        }
        if(!found){return "";}
    }
    std::string result;
    if(info == TypeField){
        std::string res;
        stream >> res;
        return res;
    }else if(info == TypeNewValue){
        std::string wasteWord;
        stream >> wasteWord;
    }
    while(stream){
        std::string currentWord;
        stream >> currentWord;
        if(isKeyword(currentWord)){
            break;
        }
        result = result + removeEscapeChar(currentWord) + " ";
    }
    return removeWhitespace(result);
}

boost::gregorian::date SimpleParser::convertToDate(std::string date){
    std::string year, month, day;
    try{
        if(isNumericalFormat(date)){
            switch(matchFormat(date)){
            case DDMMYY :
                year = CURRENT_CENTURY + date.substr(4, 2);
                month = date.substr(2, 2);
                day = date.substr(0, 2);
                return boost::gregorian::date(boost::gregorian::from_undelimited_string(year + month + day));
                break;
            case YYYYMMDD :
                year = date.substr(0, 4);
                month = date.substr(4, 2);
                day = date.substr(6, 2);
                return boost::gregorian::date(boost::gregorian::from_undelimited_string(year + month + day));
                break;
            case FormatNotRecognised:
                return boost::gregorian::date();
            }
        }
        year = date.substr(0, 4);
        month = monthMap[date.substr(5, 3)];
        day = date.substr(9, 2);
        return boost::gregorian::date(boost::gregorian::from_undelimited_string(year + month + day));
    }catch(std::exception &e){
        return boost::gregorian::date();
    }
    return boost::gregorian::date();
}

DateFormat SimpleParser::matchFormat(std::string date){
    if(date.size()==lenDDMMYY){return DDMMYY;}
    else if(date.size()==lenYYYYMMDD){return YYYYMMDD;}
    else if(date.size()==lenYYYY_MMM_DD){return YYYY_MMM_DD;}
    else{return FormatNotRecognised;}
}

bool SimpleParser::isNumericalFormat(std::string date){
    for(std::string::iterator iter = date.begin(); iter != date.end(); iter++){
        bool found = false;
        for(unsigned int i = 0; i < LEGIT_DATE_NUMBERS.size(); i++){
            if(*iter == LEGIT_DATE_NUMBERS[i]){
                found = true;
            }
        }
        if(!found){
            return false;
        }
    }
    return true;
}

bool SimpleParser::isInteger(std::string num){
    for(std::string::iterator iter = num.begin(); iter != num.end(); iter++){
        bool found = false;
        for(unsigned int i = 0; i < LEGIT_NUMBERS.size(); i++){
            if(*iter == LEGIT_NUMBERS[i]){
                found = true;
            }
        }
        if(!found){
            return false;
        }
    }
    if(stoi(num)<1){return false;}
    return true;
}

bool SimpleParser::isKeyword(std::string word){
    for(unsigned int i = 0; i < KEYWORDS.size(); i++){
        if(word == KEYWORDS[i]){return true;}
    }
    return false;
}

std::string SimpleParser::removeEscapeChar(std::string word){
    if(word[0]=='.'){return word.substr(1, word.size() - 1);}
    return word;
}

std::string SimpleParser::removeWhitespace(std::string text){
    if(text.empty()){return text;}
    if(text[text.size()-1] == ' '){return removeWhitespace(text.substr(0, text.size() - 1));}
    return text;
}