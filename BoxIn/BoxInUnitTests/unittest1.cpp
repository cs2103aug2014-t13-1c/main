#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "Event.h"
#include "Event.cpp"
#include "SimpleStorage.h"
#include "SimpleStorage.cpp"
#include "FileStorage.h"
#include "FileStorage.cpp"
#include "json_spirit.h"
#include "SimpleParser.h"
#include "SimpleParser.cpp"
#include "TimeParser.h"
#include "TimeParser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoxInUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(SimpleParserTestDDMMYY)
		{
		    SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("010204")));
        }
        TEST_METHOD(SimpleParserYYYYMMDD){
            SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("20040201")));
        }
        TEST_METHOD(SimpleParserYYYYMMMDD){
            SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("2004-Feb-01")));
		}
        TEST_METHOD(SimpleParserNonsense){
            SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("nonsense")));
		}
        TEST_METHOD(SimpleParser13Month){
            SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("011314")));
		}
        TEST_METHOD(SimpleParser32Day){
            SimpleParser* parse = new SimpleParser();
            boost::gregorian::date expected;
            Assert::AreEqual(to_iso_string(expected), to_iso_string(parse->convertToDate("320114")));
		}
        TEST_METHOD(SimpleParserIllegalMonthInTextFormat){
            SimpleParser* parse = new SimpleParser();
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
        TEST_METHOD(ExtractCommand){
            SimpleParser parser;
            std::string expected = "add";
            Assert::AreEqual(parser.getField("add",TypeCommand), expected);
        }
        TEST_METHOD(ExtractCommandWithLongerString){
            SimpleParser parser;
            std::string expected = "add";
            Assert::AreEqual(parser.getField("add stuff",TypeCommand), expected);
        }
        TEST_METHOD(ExtractDate){
            SimpleParser parser;
            boost::gregorian::date expected(2004, boost::gregorian::Feb, 1);
            std::string date = parser.getField("add something date 010204",TypeDate);
            std::string ans = "010204";
            Assert::AreEqual(ans, date);
        }
        /*
		TEST_METHOD(Storagetest1)
		{
			FileStorage test("hello.txt");
			test.appendToLineEntry("date", "010204");
			test.appendToLineEntry("start", "1200");
			Assert::IsTrue(test.isDateAndTimeCorrect());
		}
		TEST_METHOD(Storagetest2)
		{
			FileStorage test("hello.txt");
			test.determineType();
			string errorStr = "Invalid Entry";
		}

		TEST_MODULE_INITIALIZE(ModuleInitialize)
		{Logger::WriteMessage("In Module Initialize");}

		TEST_MODULE_CLEANUP(ModuleCleanup)
		{
			 Logger::WriteMessage("In Module Cleanup");
		}
        */
	};
}