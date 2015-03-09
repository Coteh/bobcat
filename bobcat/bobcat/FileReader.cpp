#include "FileReader.h"

using namespace bobcat;
using namespace FileIO;

FileReader::FileReader(){

}

FileReader::~FileReader(){
	
}

std::vector<std::string> FileReader::readFromFile(std::string _filePath){
	std::ifstream file(_filePath);
	std::string readStr;
	std::vector<std::string> fileStrVec;
	while (std::getline(file, readStr)){
		fileStrVec.push_back(readStr);
	}
	file.close();
	return fileStrVec;
}

std::string FileReader::readFromFileAsString(std::string _filePath){
	std::vector<std::string> fileVec = readFromFile(_filePath);
	std::string retStr;
	for (size_t i = 0; i < fileVec.size(); i++){
		retStr.append(fileVec[i]);
	}
	return retStr;
}