//@author A0111994

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
#include "Logic.h"
#include "Logic.cpp"
#include "Action.h"
#include "Action.cpp"
#include "Add.h"
#include "Add.cpp"
#include "Delete.h"
#include "Delete.cpp"
#include "Edit.h"
#include "Edit.cpp"
#include "Search.h"
#include "Search.cpp"
#include "Mark.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoxInUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
        // System level tests
        TEST_METHOD(TestAdd){
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            Event *expected = new Event("something","","","","","",1, false);
            Event *actual = logic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
            file.close();
        }
        TEST_METHOD(TestEdit){
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            Event *expected = new Event("something","here","","","","",1, false);
            logic.handleUserInput("edit something field place here");
            Event *actual = logic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
            file.close();
        }
        TEST_METHOD(TestDelete){
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            logic.handleUserInput("delete something");
            unsigned int expected = 0;
            Assert::AreEqual(expected, logic.getEvents().size());
            file.close();
        }
        TEST_METHOD(TestUndo){
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            logic.handleUserInput("undo");
            unsigned int expected = 0;
            Assert::AreEqual(expected, logic.getEvents().size());
            file.close();
        }
        TEST_METHOD(TestUndoForEdit){
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            Event *expected = new Event("something","","","","","",1, false);
            logic.handleUserInput("edit something field place here");
            logic.handleUserInput("undo");
            Event *actual = logic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
            file.close();
        }

        // Tests for the parser
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

        // Tests for date comparison functions (TDD)
        TEST_METHOD(DateComparer){
            Event *event1 = new Event("Earlier","","","010204","","",0,false);
            Event *event2 = new Event("Later","","","311299","","",0,false);
            Assert::AreEqual(true, endTimeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithFirstInvalid){
            Event *event1 = new Event("Earlier","","","asdfzx","","",0,false);
            Event *event2 = new Event("Later","","","311299","","",0,false);
            Assert::AreEqual(true, endTimeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithSecondInvalid){
            Event *event1 = new Event("Earlier","","","010204","","",0,false);
            Event *event2 = new Event("Later","","","supyo","","",0,false);
            Assert::AreEqual(false, endTimeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithBothInvalid){
            Event *event1 = new Event("Earlier","","","hi","","",0,false);
            Event *event2 = new Event("Later","","","supyo","","",0,false);
            Assert::AreEqual(true, endTimeComp(event1, event2));
        }
        TEST_METHOD(DateCompareWithBothEqual){
            Event *event1 = new Event("Earlier","","","010101","","",0,false);
            Event *event2 = new Event("Later","","","010101","","",0,false);
            Assert::AreEqual(true, endTimeComp(event1, event2));
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
        TEST_METHOD(ExtractName){
            SimpleParser parser;
            std::string expected = "Something over the rainbow";
            std::string ans = parser.getField("add Something over the rainbow sdate 010101", TypeName);
            Assert::AreEqual(expected, ans);
        }
        TEST_METHOD(ExtractDate){
            SimpleParser parser;
            std::string date = parser.getField("add something edate 010204",TypeEndDate);
            std::string ans = "010204";
            Assert::AreEqual(ans, date);
        }
        TEST_METHOD(ExtractWeirdName){
            SimpleParser parser;
            std::string expected = "date with you";
            std::string ans = parser.getField("delete .date with you", TypeName);
            Assert::AreEqual(expected, ans);
        }
        /*
		TEST_METHOD(Storagetest1)
		{
			FileStorage = new File;
			File test("hello.txt");
			test.appendToLineEntry("date", "010204");
			test.appendToLineEntry("start", "1200");
			Assert::IsTrue();
		}
		TEST_METHOD(Storagetest2)
		{
			FileStorage = new File;
			File test("hello.txt");
			test.determineType();
			string errorStr = "Invalid Entry";
		}

		TEST_MODULE_INITIALIZE(ModuleInitialize)
		{
			Logger::WriteMessage("In Module Initialize");
		}

		TEST_MODULE_CLEANUP(ModuleCleanup)
		{
			 Logger::WriteMessage("In Module Cleanup");
		}
        */
        
	};
}