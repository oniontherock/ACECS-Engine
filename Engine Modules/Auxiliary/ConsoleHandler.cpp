#include "ConsoleHandler.hpp"

#include <Windows.h>

void ConsoleHandler::consoleSetTextColor(uint8_t colorId) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorId);
}
void ConsoleHandler::consoleResetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void ConsoleHandler::consolePrintMessage(std::string message) {
	std::cout << message << std::endl;
}
void ConsoleHandler::consolePrintColor(std::string message, const uint8_t colorId) {
	consoleSetTextColor(colorId);
	consolePrintMessage(message);
	consoleResetColor();
}
void ConsoleHandler::consolePrintErr(std::string message) {
	consolePrintColor("ERROR: " + message, 12);
	consoleResetColor();
}

