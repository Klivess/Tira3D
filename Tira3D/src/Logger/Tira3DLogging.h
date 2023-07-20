#include <iostream>
#include <string>
#include "GL/glew.h"
#include "glfw3.h"
#pragma once


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

//__debugbreak is compiler specific!!! will rewrite this in the future
//works on Visual Studio
#define ASSERT(x) if(!(x)) __debugbreak();

//wrap every single OpenGL reference/call in GLCall().
#define GLCall(x) GLClearError(); Tira3DLogging::LogToConsole(#x);\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));


class Tira3DLogging
{
public:
	static void LogToConsole(const char* text);
	static void LogToConsole(std::string string);
};

