#include "FileWriter.h"

using namespace FileIO;

FileWriter::FileWriter() {
}

void FileWriter::writeToFile(std::string _fileName, std::vector<std::string> _data){
	std::ofstream file;
	file.open(_fileName);
	for (int i = 0; i < _data.size(); i++){
		file << _data[i];
	}
	file.close();
}

FileWriter::~FileWriter() {
}
