#include "FileReader.h"

using namespace FileIO;

FileReader::FileReader(){

}

FileReader::~FileReader(){
	
}

std::vector<std::string> FileReader::readFromFile(std::string _fileName){
	std::ifstream file(_fileName);
	std::string readStr;
	std::vector<std::string> fileStrVec;
	while (std::getline(file, readStr)){
		fileStrVec.push_back(readStr);
	}
	file.close();
	return fileStrVec;
}