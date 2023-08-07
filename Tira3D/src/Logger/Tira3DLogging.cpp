#include "Tira3DLogging.h"
#include <string>

void Tira3DLogging::LogToConsole(const char* text) {
	std::cout << text << std::endl;
}

void Tira3DLogging::LogToConsole(std::string string) {
	std::cout << string << std::endl;
}

//Translates common error codes to error words
//Better than memorizing the number that comes up
std::string TryGetErrorMessage(unsigned int err) {
	switch (err) {
	case 1281:
		return "INVALID_VALUE";
	case 1282:
		return "INVALID_OPERATION";
	case 1280:
		return "INVALID_ENUM";
	default:
		return std::to_string(err);
	}
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (unsigned int error = glGetError()) {
		std::cout << "[OpenGL Error] (" << TryGetErrorMessage(error) << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}