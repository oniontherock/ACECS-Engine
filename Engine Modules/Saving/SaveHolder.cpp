#include "SaveHolder.hpp"

std::string SaveHolder::saveFileName = "save.dat";

std::ofstream SaveHolder::fileWriter{};
std::ifstream SaveHolder::fileReader{};

void SaveHolder::saveFileNameSet(std::string nameNew) {

	try {
		if (fileWriter.is_open()) {
			throw "Writer";
		}
		if (fileReader.is_open()) {
			throw "Reader";
		}

		saveFileName = nameNew;
	}
	catch (std::string e) {
		ConsoleHandler::consolePrintErr("Save file name changed while file" + e + " is open! Please close before changing save file");
		return;
	}
}

void SaveHolder::fileWriterOpen() {
	fileWriter.open(saveFileName, std::ios::out | std::ios::binary);

	if (!fileWriter) {
		ConsoleHandler::consolePrintErr("Save file failed to open");
	}
}
void SaveHolder::fileWriterClose() {
	fileWriter.close();
}

void SaveHolder::fileReaderOpen() {
	fileReader.open(saveFileName, std::ios::in | std::ios::binary);

	if (!fileWriter) {
		ConsoleHandler::consolePrintErr("Save file failed to open");
	}
}
void SaveHolder::fileReaderClose() {
	fileReader.close();
}
