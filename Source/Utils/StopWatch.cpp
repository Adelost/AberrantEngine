#include "StopWatch.h"

#include "Math.h"
#include "StaticCall.h"

#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <windows.h>

namespace
{
	double s_secsPerCpuCount;
	__int64 currentCpuTime()
	{
		__int64 c;
		QueryPerformanceCounter((LARGE_INTEGER*)&c);
		return c;
	}
	double secsPerCpuCount()
	{
		__int64 countsPerSecs;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecs);
		return 1.0 / (double)countsPerSecs;
	}
	float cpuTimeToSecs(__int64 cpuTime)
	{
		double secs = cpuTime * s_secsPerCpuCount;
		return static_cast<float>(secs);
	}
}

STATIC_CALL(
    // Frequency need only be queried upon application
    // initialization, and the result can be cached.
    s_secsPerCpuCount = secsPerCpuCount();
);

StopWatch::StopWatch()
{
	m_paused = false;

	start();
}

void StopWatch::start()
{
	resume();
	m_cpuTime = currentCpuTime();
}

void StopWatch::pause()
{
	if (!isPaused())
	{
		m_cpuPause = currentCpuTime();
		m_paused = true;
	}
}

void StopWatch::resume()
{
	if (m_paused)
	{
		m_cpuTime += cpuPauseTime();
		m_paused = false;
	}
}

float StopWatch::time()
{
	return cpuTimeToSecs(cpuTime());
}

float StopWatch::pausedTime()
{
	return cpuTimeToSecs(cpuPauseTime());
}

float StopWatch::timeMsFloat()
{
	return time() * 1000;
}

int StopWatch::timeMs()
{
	return Math::round(time() * 1000);
}

void StopWatch::printTime()
{
	std::cout << timeMs() << " ms" << std::endl;
}

void StopWatch::printTime(std::string label)
{
	std::cout << label << ":\t" << timeMs() << " ms" << std::endl;
}

bool StopWatch::isPaused()
{
	return m_paused;
}

__int64 StopWatch::cpuTime()
{
	__int64 time = currentCpuTime() - m_cpuTime;

	// Compensate for paused time
	time -= cpuPauseTime();

	return time;
}

__int64 StopWatch::cpuPauseTime()
{
	if (isPaused())
		return currentCpuTime() - m_cpuPause;
	return 0;
}
