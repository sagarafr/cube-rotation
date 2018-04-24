#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "debug.hpp"

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cerr << std::showbase << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "[GL ERROR]" : "[]") << " type [" << std::hex << type << "] severity [" << std::hex << severity << "] message [" << message << "]\n";
}

void debugCallback(void) {
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glDebugMessageCallback(reinterpret_cast<GLDEBUGPROC>(MessageCallback), 0);
}
