#pragma once

#include <string>

/// Time measuring class, useful when profiling code
class StopWatch
{
public:
	StopWatch();

	void start();
	void pause();
	void resume();

	void printTime();
	void printTime(std::string label);

	float time();
	int timeMs();
	float timeMsFloat();
	float pausedTime();
	bool isPaused();

private:
	__int64 cpuTime();
	__int64 cpuPauseTime();

	__int64 m_cpuTime;
	__int64 m_cpuPause;
	bool m_paused;
};