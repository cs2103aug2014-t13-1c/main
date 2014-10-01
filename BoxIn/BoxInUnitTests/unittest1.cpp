#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "Logic.h"
#include "Logic.cpp"
#include "Event.h"
#include "Event.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoxInUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestVectorToString)
		{
			Logic *l = new Logic();
			std::vector<std::string> vec;
			for(int i = 0; i < 3; i++){
				vec.push_back("hello");
			}
			std::string ans = l->vectorToString(vec);
			std::string expected = "hello hello hello";
			Assert::AreEqual(ans, expected);
		}

	};
}