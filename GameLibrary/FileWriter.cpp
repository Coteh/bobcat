#include "FileWriter.h"
#include <iostream>
#include <fstream>

using namespace bobcat;
using namespace FileIO;

FileWriter::FileWriter() {
}

FileWriter::~FileWriter() {
}

void FileWriter::writeToFile(std::string _fileName, std::vector<std::string> _data){
	std::ofstream file;
	file.open(_fileName);
	for (size_t i = 0; i < _data.size(); i++){
		file << _data[i];
	}
	file.close();
}

void FileWriter::writeToFile(std::string _fileName, std::string _line){
	std::ofstream file;
	file.open(_fileName);
	file << _line;
	file.close();
}

void FileWriter::appendToFile(std::string _fileName, std::string _line){
	std::ofstream file;
	file.open(_fileName, std::ios_base::app);
	file << _line;
	file.close();
}