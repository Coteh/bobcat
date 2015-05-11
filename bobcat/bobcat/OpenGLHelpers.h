#pragma once
#include "External\gl_core_3_3.h"

namespace bobcat {

	/**
	* Static helper functions for OpenGL-related tasks.
	*/
	class OpenGLHelpers {
	public:
		static bool loadOpenGL();
		static void printVersionInfo();
		static void printVersionMajorMinor();
	};

}