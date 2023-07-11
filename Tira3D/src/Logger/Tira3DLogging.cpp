#include "Tira3DLogging.h"

void Tira3DLogging::LogToConsole(const char* text) {
	std::cout << text << std::endl;
}

void Tira3DLogging::LogToConsole(std::string string) {
	std::cout << string << std::endl;
}