#include "Clock.h"

namespace Clock{
	//Private variables are within this anonymous namespace
	namespace{
		LARGE_INTEGER currCounter;
		LARGE_INTEGER ticksPerSecond;
		LARGE_INTEGER counterStart;
		bool isHighResSupported;
	}

	void init(){
		isHighResSupported = QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&counterStart);
	}

	double getCurrentTime(){
		QueryPerformanceCounter(&currCounter);
		return (double)(currCounter.QuadPart - counterStart.QuadPart) / (double)ticksPerSecond.QuadPart;
	}

	double getCurrentTimeMilliseconds(){
		return getCurrentTime() * 1000;
	}
}