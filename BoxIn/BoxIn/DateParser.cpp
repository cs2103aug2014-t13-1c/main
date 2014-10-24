#include "DateParser.h"

DateParser::DateParser(void){
    setupMap();
}

DateParser::~DateParser(void){
}

boost::gregorian::date DateParser::convertToDate(std::string date){
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
            case YYYY_MMM_DD :
                // assuming iso_extended_string format YYYY-MMM-DD
                year = date.substr(0, 4);
                month = monthMap[date.substr(5, 3)];
                day = date.substr(9, 2);
                return boost::gregorian::date(boost::gregorian::from_undelimited_string(year + month + day));
                break;
            case FormatNotRecognised:
                return boost::gregorian::date();
            }
        }
    }catch(std::exception &e){
        return boost::gregorian::date();
    }
    return boost::gregorian::date();
}

void DateParser::setupMap(){
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

DateFormat DateParser::matchFormat(std::string date){
    if(date.size()==lenDDMMYY){return DDMMYY;}
    else if(date.size()==lenYYYYMMDD){return YYYYMMDD;}
    else if(date.size()==lenYYYY_MMM_DD){return YYYY_MMM_DD;}
    else{return FormatNotRecognised;}
}

bool DateParser::isNumericalFormat(std::string date){
    for(std::string::iterator iter = date.begin(); iter != date.end(); iter++){
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
    return true;
}