#include "OpenGLHelpers.h"
#include <stdio.h>

using namespace bobcat;

void OpenGLHelpers::printVersionInfo() {
	printf("============================================================\n");
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("============================================================\n\n");
}

void OpenGLHelpers::printVersionMajorMinor(){
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("============================================================\n");
	printf("GL MAJOR Version: %d\n", major);
	printf("GL MINOR Version: %d\n", minor);
	printf("============================================================\n\n");
}