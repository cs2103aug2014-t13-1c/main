#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "DateParser.h"
#include "DateParser.cpp"
#include "Event.h"
#include "Event.cpp"
#include "SimpleStorage.h"
#include "SimpleStorage.cpp"
#include "FileStorage.h"
#include "FileStorage.cpp"
#include "json_spirit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoxInUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(DateParserTestDDMMYY)
		{
		    DateParser* parse = new DateParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("010204")));
        }
        TEST_METHOD(DateParserYYYYMMDD){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("20040201")));
        }
        TEST_METHOD(DateParserYYYYMMMDD){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("2004-Feb-01")));
		}
        TEST_METHOD(DateParserNonsense){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("nonsense")));
		}
        TEST_METHOD(DateParser13Month){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("011314")));
		}
        TEST_METHOD(DateParser32Day){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("320114")));
		}
        TEST_METHOD(DateParserIllegalMonthInTextFormat){
            DateParser* parse = new DateParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("2014-Wut-12")));
		}
        TEST_METHOD(DateComparer){
            Event *event1 = new Event("Earlier","","010204","");
            Event *event2 = new Event("Later","","311299","");
            Assert::AreEqual(true, timeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithFirstInvalid){
            Event *event1 = new Event("Earlier","","asdfzx","");
            Event *event2 = new Event("Later","","311299","");
            Assert::AreEqual(true, timeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithSecondInvalid){
            Event *event1 = new Event("Earlier","","010204","");
            Event *event2 = new Event("Later","","supyo","");
            Assert::AreEqual(false, timeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithBothInvalid){
            Event *event1 = new Event("Earlier","","hi","");
            Event *event2 = new Event("Later","","supyo","");
            Assert::AreEqual(true, timeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithBothEqual){
            Event *event1 = new Event("Earlier","","010101","");
            Event *event2 = new Event("Later","","010101","");
            Assert::AreEqual(true, timeComp(event1, event2));
        }
	};
}