#include <iostream>
#include "../vendor/glew.h"
#include "../vendor/glfw3.h"
#pragma once


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

//__debugbreak is compiler specific!!! will rewrite this in the future
//works on Visual Studio
#define ASSERT(x) if (!(x)) __debugbreak()

//wrap every single GL reference/call in GLCall().
//do NOT wrap GLFW calls.
#define GLCall(x)                \
    GLClearError();              \
    x;                           \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


class Tira3DLogging
{
public:
	static void LogToConsole(const char* text);
	static void LogToConsole(std::string string);
	static void LogToConsole(int num);
};

