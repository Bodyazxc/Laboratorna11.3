#include "pch.h"
#include "CppUnitTest.h"
#include "../Laboratorna11.3/Laboratorna11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest113
{
	TEST_CLASS(UnitTest113)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            
            string test_file = "test_phone_numbers.txt";
            ofstream f(test_file);
            f << "12345\n";
            f << "67890\n";
            f << "11111\n";
            f.close();

            
            string phone_to_search = "67890";
            string line;
            bool found = false;

            ifstream file(test_file);
            while (getline(file, line)) {
                if (line == phone_to_search) {
                    found = true;
                    break;
                }
            }

            
            Assert::IsTrue(found);

            
		}
	};
}
