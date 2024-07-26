#ifndef __CONSOLE_HANDLER_H__
#define __CONSOLE_HANDLER_H__

#include <cstdint>
#include <iostream>
#include <string>

namespace ConsoleHandler {

	void consoleSetTextColor(uint8_t colorId);
	void consoleResetColor();

	void consolePrintMessage(std::string message);
	void consolePrintColor(std::string message, const uint8_t colorId);
	void consolePrintErr(std::string message);
}


#endif