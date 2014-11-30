#include "Clock.h"

LARGE_INTEGER Clock::currCounter;
LARGE_INTEGER Clock::ticksPerSecond;
LARGE_INTEGER Clock::counterStart;
bool Clock::isHighResSupported;

void Clock::init(){
	isHighResSupported = QueryPerformanceFrequency(&ticksPerSecond);
	QueryPerformanceCounter(&counterStart);
}

double Clock::getCurrentTime(){
	QueryPerformanceCounter(&currCounter);
	return (double)(currCounter.QuadPart - counterStart.QuadPart) / (double)ticksPerSecond.QuadPart;
}

double Clock::getCurrentTimeMilliseconds(){
	return getCurrentTime() * 1000;
}