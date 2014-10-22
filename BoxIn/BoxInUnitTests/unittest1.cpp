#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "DateParser.h"
#include "DateParser.cpp"

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

	};
}