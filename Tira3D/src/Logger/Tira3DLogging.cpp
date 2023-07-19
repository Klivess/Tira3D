#include "Tira3DLogging.h"

void Tira3DLogging::LogToConsole(const char* text) {
	std::cout << text << std::endl;
}

void Tira3DLogging::LogToConsole(std::string string) {
	std::cout << string << std::endl;
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}