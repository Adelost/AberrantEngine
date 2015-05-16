#include "TestUtils.h"
//#include "TestSimulation.h"

#include <Utils/Console.h>
#include <Utils/LeakDetection.h>
#include <Utils/UnitTest.h>

int main()
{
	using namespace ae;
	LeakDetection::enable();
	UnitTests::run();
	Console::pressToContinue();
	return 0;
}

//#include <Utils/tests.h>
//#include <Utils/Console.h>
//#include <Utils/LeakDetection.h>
//
//int main()
//{
//	using namespace ae;
//	LeakDetection::enable();
//	runTests();
//	Console::pressToContinue();
//	return 0;
//}