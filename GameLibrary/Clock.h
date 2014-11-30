#pragma once
#include <Windows.h>

namespace Clock{
	extern LARGE_INTEGER currCounter;
	extern LARGE_INTEGER ticksPerSecond;
	extern LARGE_INTEGER counterStart;
	extern bool isHighResSupported;

	void init();

	double getCurrentTime();

	double getCurrentTimeMilliseconds();
}