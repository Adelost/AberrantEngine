#include <Utils/Console.h>
#include <Utils/LeakDetection.h>

#include "TestUtils.h"
#include "TestSimulation.h"


#define CATCH_CONFIG_RUNNER
#include <Catch/include/catch.hpp>

#include <Utils/Array.h>
using namespace ae;

int main()
{
	LeakDetection::enable();

	Array<int> foo;

	Catch::Session().run();

	Console::pressToContinue();

	return 0;
}