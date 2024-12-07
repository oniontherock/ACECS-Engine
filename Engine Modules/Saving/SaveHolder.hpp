#ifndef __SAVE_HOLDER_H__
#define __SAVE_HOLDER_H__

#include "../Auxiliary/ConsoleHandler.hpp"
#include <fstream>
#include <ios>
#include <string>

// class for holding some low level saving related stuff, like the file streams, the save file name,
// and some functions that do the most basic "save" operations, like "fileWrite << obj", and "fileRead >> obj".
class SaveHolder {

	// name of the
	static std::string saveFileName;
	
	static std::ofstream fileWriter;
	static std::ifstream fileReader;

public:
	
	static void saveFileNameSet(std::string nameNew);

	static void fileWriterOpen();
	static void fileWriterClose();

	static void fileReaderOpen();
	static void fileReaderClose();

	template <typename T>
	static void objectSave(T& obj) {

		try {
			if (!fileWriter.is_open()) {
				throw "fileWriter is not open!";
			}

			fileWriter << obj;
		}
		catch (std::string e) {
			ConsoleHandler::consolePrintErr("Save failed! Reason: " + e);
			return;
		}
	}
	template <typename T>
	static void objectLoad(T& obj) {
		try {
			if (!fileReader.is_open()) {
				throw "fileReader is not open!";
			}

			fileReader >> obj;
		}
		catch (std::string e) {
			ConsoleHandler::consolePrintErr("Load failed! Reason: " + e);
			return;
		}
	}
};

#endif