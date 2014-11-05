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
    dayMap[Days::MONDAY] = boost::date_time::Monday;
    dayMap[Days::TUESDAY] = boost::date_time::Tuesday;
    dayMap[Days::WEDNESDAY] = boost::date_time::Wednesday;
    dayMap[Days::THURSDAY] = boost::date_time::Thursday;
    dayMap[Days::FRIDAY] = boost::date_time::Friday;
    dayMap[Days::SATURDAY] = boost::date_time::Saturday;
    dayMap[Days::SUNDAY] = boost::date_time::Sunday;
}

/*
* Returns the value belonging to the field given by InfoType
* as per extracted from an input string
*/
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

/*
* Converts a string to a date
* Can accept DDMMYY, YYYYMMDD, YYYY_Mon_DD formats
* As well as special strings such as today, tomorrow, and days of the week
* Returns the date as a boost::gregorian::date
*/
boost::gregorian::date SimpleParser::convertToDate(std::string date){
    std::string year, month, day;
    boost::gregorian::date today;
    try{
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
            case DayOfWeek :
                today = boost::gregorian::day_clock::local_day();
                while(today.day_of_week() != dayMap[date]){
                    today = today + boost::gregorian::days(1);
                }
                return today;
                break;
            case Today :
                return boost::gregorian::day_clock::local_day();
                break;
            case Tomorrow :
                return boost::gregorian::day_clock::local_day() + boost::gregorian::days(1);
                break;
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

/*
* Identifies the format of a string
* Returns FormatNotRecognised if it does not match any format
*/
DateFormat SimpleParser::matchFormat(std::string date){
    if(isDayOfWeek(date)){return DayOfWeek;}
    else if(isToday(date)){return Today;}
    else if(isTomorrow(date)){return Tomorrow;}
    else if(date.size()==lenDDMMYY && isInteger(date)){return DDMMYY;}
    else if(date.size()==lenYYYYMMDD && isInteger(date)){return YYYYMMDD;}
    else if(date.size()==lenYYYY_MMM_DD && isNumericalFormat(date)){return YYYY_MMM_DD;}
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
    if(num.empty()){return false;}
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

bool SimpleParser::isDayOfWeek(std::string day){
    return (day == Days::MONDAY || day == Days::TUESDAY || day == Days::WEDNESDAY || day == Days::THURSDAY || day == Days::FRIDAY || day == Days::SATURDAY || day == Days::SUNDAY);
}

bool SimpleParser::isToday(std::string day){
    return day == Days::TODAY;
}

bool SimpleParser::isTomorrow(std::string day){
    return day == Days::TOMORROW;
}