#include "Util.h"

#include <chrono> // sleep_for
#include <iostream>
#include <thread>

#include "StopWatch.h"

void Util::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Util::busyWait(float ms)
{
	StopWatch timer;
	while (timer.timeMsFloat() < ms)
	{
		// Do nothing
	}
}

void Util::print(std::string text)
{
	std::cout << text << std::endl;
}

void Util::pressToContinue()
{
	std::cout << "Press any key to continue . . ." << std::endl;
	std::cin.ignore();
}
