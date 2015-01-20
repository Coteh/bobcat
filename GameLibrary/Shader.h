#pragma once
#include "vgl.h"

namespace bobcat {

	struct Shader {
	public:
		GLuint shaderProgram, modelLoc, viewLoc, projectionLoc, lightingLoc, texSamplerLoc, colorLoc;
		GLint posAttrib, normAttrib, texAttrib, colAttrib;
		std::string name;
	};

}