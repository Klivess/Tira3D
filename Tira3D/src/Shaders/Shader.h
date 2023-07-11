#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "GL/glew.h"
#include "glfw3.h"

using namespace std;

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};
#pragma once
class Shader
{
public:
	static ShaderProgramSource ParseShader(const std::string& filepath);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

