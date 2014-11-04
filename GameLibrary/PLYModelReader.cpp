#include <algorithm>
#include <iostream>
#include <sstream>
#include "PLYModelReader.h"

PLYModelReader::PLYModelReader() {
}

PLYModelReader::~PLYModelReader() {
}

/*Process File
* Processes the PLY file
and removes any blank lines and/or comment lines
*/
void PLYModelReader::readModel(std::string _fileName){
	//Contents of the model file
	fileContents = std::vector<std::string>(readFromFile(_fileName));

	//Iterate through it, and remove any blank lines or comment lines
	fileContents.erase(
		std::remove_if(fileContents.begin(),
		fileContents.end(),
		[](std::string line) { return line.find(PLY_COMMENT_STRING) != std::string::npos || line.find_first_not_of(' ') == std::string::npos; }));

	//Iterator for the model file vector
	fileIterator = fileContents.begin();

	//First, check if it's a PLY file 
	//by reading the first line for its magic number: "ply"
	if (*fileIterator != PLY_MAGIC_NUMBER){
		throw "Error: This file isn't a PLY Model Format!";
	}
	++fileIterator; //increment the iterator

	//Next, get the PLY format
	//Sorry my checking is harsh!
	std::string fmtIterStr = *fileIterator;
	/*if (!fmtIterStr.find(PLY_FORMAT_STRING)){
		throw "Error: This PLY file doesn't specify the format";
	}*/
	if (fmtIterStr == std::string(PLY_FORMAT_STRING) + (" ascii 1.0")){
		plyFormat = PLY_FILE_FORMAT::ASCII_1_0;
	} else if (fmtIterStr == std::string(PLY_FORMAT_STRING) + (" binary_little_endian 1.0")){
		plyFormat = PLY_FILE_FORMAT::BINARY_LITTLE_ENDIAN_1_0;
	} else if (fmtIterStr == std::string(PLY_FORMAT_STRING) + (" binary_big_endian 1.0")){
		plyFormat = PLY_FILE_FORMAT::BINARY_BIG_ENDIAN_1_0;
	}

	//Now to iterate through the remaining lines and figure out which model data we need
	int numVertices = 0, numFaces = 0, vertLineCounter = 0, faceLineCounter = 0;
	plyReadStage = PLY_READ_STAGE::HEADER;
	std::string line;
	for (++fileIterator; fileIterator != fileContents.end() || plyReadStage == PLY_READ_STAGE::NONE; ++fileIterator){
		line = *fileIterator;
		switch (plyReadStage) {
			case PLYModelReader::HEADER:
				if (line.find(std::string(PLY_ELEMENT_STRING)) != std::string::npos){
					std::istringstream iss(line);
					std::vector<std::string> linesSplit;
					while (std::getline(iss, line, ' ')){
						linesSplit.push_back(line);
					}
					if (linesSplit[1] == "vertex"){
						try{
							numVertices = ::atoi(linesSplit[2].c_str());
						} catch (...) {
							numVertices = 0;
						}
						vertices.reserve(numVertices * 3);
					} else if (linesSplit[1] == "face"){
						try{
							numFaces = ::atoi(linesSplit[2].c_str());
						} catch (...) {
							numFaces = 0;
						}
						indiceCountData.reserve(numFaces);
					}
				}else if (line.find(std::string(PLY_END_HEADER_STRING)) != std::string::npos){
					plyReadStage = PLY_READ_STAGE::VERTICES;
				}
				break;
			case PLYModelReader::VERTICES:{
				//Now get the vertices!
				std::istringstream iss(line);
				std::vector<GLfloat> vertFloats;
				while (std::getline(iss, line, ' ')){
					try{
						vertFloats.push_back(std::stof(line));
					} catch (...){
						vertFloats.push_back(0.0f);
					}
				}
				for (int i = 0; i < 3; i++){
					vertices.push_back(vertFloats[i]);
				}
				vertLineCounter++;
				if (vertLineCounter >= numVertices){
					plyReadStage = PLY_READ_STAGE::INDICES;
				}
				break;
			}
			case PLYModelReader::INDICES:
				//Now get the faces!
				if (faceLineCounter < numVertices){
					std::istringstream iss(line);
					std::vector<int> faceInts;
					while (std::getline(iss, line, ' ')){
						try{
							faceInts.push_back(::atoi(line.c_str()));
						} catch (...){
							faceInts.push_back(0);
						}
					}
					//The first interger in an indice line is the amount of integers on that line following the inital integer that will be added in
					//(Please correct me if I'm wrong)
					int amtOfIndices = faceInts[0];
					indiceCountData.push_back(amtOfIndices);
					int amtOfValuesOnLine = (amtOfIndices > 0) ? amtOfIndices + 1 : 0;
					//Now let's gather up the rest of the integers we will need!
					for (int i = 1; i < amtOfValuesOnLine; i++){
						indices.push_back(faceInts[i]);
					}
					faceLineCounter++;
				} else{
					plyReadStage = PLY_READ_STAGE::NONE;
				}
				break;
		}
	}
}

std::pair<std::vector<GLfloat>, std::vector<GLuint>> PLYModelReader::getModelData(){
	return std::make_pair(vertices, indices);
}

std::vector<int> PLYModelReader::getIndiceCountData(){
	return indiceCountData;
}