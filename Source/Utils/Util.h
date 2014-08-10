#pragma once

#include <string>

class Util
{
public:
	/// Returns true if T1 is of type T2, use with caution, dynamic casts are relatively slow.
	template<class T1, class T2> static bool isOfType();
	/// Sleeps current thread.
	static void sleep(int ms);
	/// Delay thread with computation, allows higher precision than sleep.
	static void busyWait(float ms);
	static void print(std::string text);
	static void pressToContinue();
};

template<class T1, class T2>
bool Util::isOfType()
{
	return dynamic_cast<T2*>(&T1()) != 0;
}
