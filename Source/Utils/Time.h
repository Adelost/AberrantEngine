#pragma once

namespace ae
{
	/** Utility class to make various things easier. */
	class Time
	{
	public:
		/** Put current thread to sleep. */
		static void sleep(int ms);
		/** Delay thread with computation, allows higher precision than sleep(). */
		static void busyWait(float ms);
	};
}