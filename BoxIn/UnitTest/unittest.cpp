#include "unittest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
UnitTest::UnitTest(){
}

UnitTest::~UnitTest(){
}

//@author A0111994
int a = 1;

int& foo(){ // just to generate the reference to integer
    return a;
}

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
        // System level tests
        TEST_METHOD(TestAddFloating){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            Event *expected = new Event("something","","","","","",1, false);
            Event *actual = logic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
            file.close();
        }
        TEST_METHOD(TestAddWithEndDate){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something edate 311214");
            Event *actual = logic.getEvents()[0];
            std::string expected = "something at  from ,  to 2014-Dec-31, 00:00";
            Assert::AreEqual(expected, actual->repr());
            file.close();
        }
        TEST_METHOD(TestAddWithStartDate){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something sdate 311214");
            Event *actual = logic.getEvents()[0];
            std::string expected = "something at  from 2014-Dec-31, 00:00 to , ";
            Assert::AreEqual(expected, actual->repr());
            file.close();
        }
        TEST_METHOD(TestAddInvalidDatePair){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something sdate 311214 edate 301214");
            Event *actual = logic.getEvents()[0];
            std::string expected = "something at  from ,  to 2014-Dec-30, 00:00";
            Assert::AreEqual(expected, actual->repr());
            file.close();
        }
        TEST_METHOD(TestEdit){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
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
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            logic.handleUserInput("delete something");
            unsigned int expected = 0;
            Assert::AreEqual(expected, logic.getEvents().size());
            file.close();
        }
        TEST_METHOD(TestUndoForAdd){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            logic.handleUserInput("undo");
            unsigned int expected = 0;
            Assert::AreEqual(expected, logic.getEvents().size());
            file.close();
        }
        TEST_METHOD(TestUndoForEdit){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
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
        TEST_METHOD(TestUndoForDelete){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something");
            logic.handleUserInput("delete something");
            logic.handleUserInput("undo");
            Event *expected = new Event("something","","","","","",1, false);
            Event *actual = logic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
            file.close();
        }
        // Tests for the parsers
		TEST_METHOD(SimpleParserTestDDMMYY){
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

        // FileStorage Tests
        TEST_METHOD(ReadFile){
            int& argc = foo();
            char** argv;
            QApplication app(argc, argv);
            std::fstream file = std::fstream("BoxInData.json", std::fstream::out | std::fstream::trunc);
            Logic logic;
            logic.handleUserInput("add something etime 2359");
            Logic anotherLogic;
            Assert::AreEqual(logic.getEvents().size(), anotherLogic.getEvents().size());
            Event* expected = logic.getEvents()[0];
            Event* actual = anotherLogic.getEvents()[0];
            Assert::AreEqual(expected->repr(), actual->repr());
        }
    };
};
