#pragma once
#include <Windows.h>

namespace bobcat {

	/**
	* Namespace containing methods that can access the system clock and determine elapsed time.
	*/
	namespace Clock {
		/**
		* Initialize game clock.
		*/
		void init();

		/**
		* Get current time in seconds.
		* @return Double value representing time in seconds.
		*/
		double getCurrentTime();

		/**
		* Get current time in milliseconds.
		* @return Double value representing time in milliseconds.
		*/
		double getCurrentTimeMilliseconds();
	}

}