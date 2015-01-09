#pragma once
#include "vgl.h"

namespace bobcat {

	struct Shader {
	public:
		GLuint shaderProgram, mvpLoc, lightingLoc, texSamplerLoc, colorLoc;
		GLint posAttrib, normAttrib, texAttrib, colAttrib;
		std::string name;
	};

}