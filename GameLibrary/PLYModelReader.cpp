#include <algorithm>
#include <iostream>
#include <sstream>
#include "PLYModelReader.h"

using namespace bobcat;

PLYModelReader::PLYModelReader() {
	isFirstTime = true;
}

PLYModelReader::~PLYModelReader() {
	clearVectors();
}

void PLYModelReader::clearVectors(){
	indices.clear();
	std::vector<GLuint> clearVec;
	clearVec.swap(indices);
	indiceCountData.clear();
	std::vector<int> clearVec2;
	clearVec2.swap(indiceCountData);
	propVec.clear();
	std::vector<IPLYProperty*> clearVec3;
	clearVec3.swap(propVec);
}

/*Process File
* Processes the PLY file
and removes any blank lines and/or comment lines
*/
void PLYModelReader::readModel(std::string _fileName){
	//Is it the first time reading a model with PLY Model Reader?
	if (!isFirstTime){
		//If not, clear all the data out from previous read
		clearVectors();
	}
	isFirstTime = false;
	//Contents of the model file
	fileContents = std::vector<std::string>(readFromFile(_fileName));

	if (fileContents.size() == 0){
		//file not read, throw an error
		throw "Could not load file!";
	}

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
	numVertices = 0;
	int numFaces = 0, vertLineCounter = 0, faceLineCounter = 0;
	plyReadStage = PLY_READ_STAGE::HEADER;
	headerInitStage = PLY_HEADER_VARIABLE_INIT_STAGE::NO_VARS;
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
						//vertices.reserve(numVertices * 3);
						headerInitStage = PLY_HEADER_VARIABLE_INIT_STAGE::VERTEX_VARS;
					} else if (linesSplit[1] == "face"){
						try{
							numFaces = ::atoi(linesSplit[2].c_str());
						} catch (...) {
							numFaces = 0;
						}
						indiceCountData.reserve(numFaces);
						headerInitStage = PLY_HEADER_VARIABLE_INIT_STAGE::INDICE_VARS;
					}
				} else if (line.find(std::string(PLY_PROPERTY_STRING)) != std::string::npos){
					//Only deal with vertex variables for now because I have no clue how to deal with the indices/face variables
					if (headerInitStage == PLY_HEADER_VARIABLE_INIT_STAGE::VERTEX_VARS){
						//First word is "property", words in the middle are data types, last word is the name of the variable
						//We will figure out a data type to use and then create a PLY property object for it, and give it its name
						std::istringstream iss(line);
						std::vector<std::string> linesSplit;
						while (std::getline(iss, line, ' ')){
							linesSplit.push_back(line);
						}
						//Just do GLfloats for now (so not needing the middle words for now)
						PLYProperty<GLfloat>* propy = new PLYProperty<GLfloat>(linesSplit.back());
						propVec.push_back(propy);
					}
				} else if (line.find(std::string(PLY_END_HEADER_STRING)) != std::string::npos){
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
				for (size_t i = 0; i < propVec.size(); i++){
					try{
						if (propVec[i]->getName() == "red" || propVec[i]->getName() == "blue" || propVec[i]->getName() == "green"){
							vertFloats[i] /= 255.0f; //divide the color by 255 so OpenGL will read it
						}
						((PLYProperty<GLfloat>*)propVec[i])->addData(vertFloats[i]);
					} catch (...){
						((PLYProperty<GLfloat>*)propVec[i])->addData(0.0f);
					}
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

std::vector<GLfloat> PLYModelReader::getVertexData(std::string _variableName){
	try{
		for (size_t i = 0; i < propVec.size(); i++){
			if (propVec[i]->getName() == _variableName){
				return ((PLYProperty<GLfloat>*)propVec[i])->getData();
			}
		}
	} catch (...){
		std::cout << "Could not retrieve model data for variable " << _variableName;
	}
	return std::vector<GLfloat>();
}

std::vector<GLfloat> PLYModelReader::getVertices(std::string _xName, std::string _yName, std::string _zName){
	//Will grab x, y, and z variables and concatenate them together
	//then return that
	std::vector<GLfloat> vertexData;
	const int NUM_PROPS = 3;
	vertexData.reserve(numVertices * NUM_PROPS);
	std::vector<GLfloat> verts[NUM_PROPS];
	//Getting the collections
	verts[0] = getVertexData(_xName);
	verts[1] = getVertexData(_yName);
	verts[2] = getVertexData(_zName);
	for (int i = 0; i < NUM_PROPS; i++){
		if (verts[i].size() <= 0){
			verts[i] = std::vector<GLfloat>(numVertices, 0);
		}
	}
	//Adding them all up
	for (int i = 0; i < numVertices; i++){
		for (int j = 0; j < NUM_PROPS; j++){
			vertexData.push_back(verts[j][i]);
		}
	}
	//Return the bundled up vertex data
	return vertexData;
}

std::vector<GLfloat> PLYModelReader::getVertices(std::string _xName, std::string _yName){
	//Will grab x and y variables and concatenate them together
	//then return that
	std::vector<GLfloat> vertexData;
	const int NUM_PROPS = 2;
	vertexData.reserve(numVertices * NUM_PROPS);
	std::vector<GLfloat> verts[NUM_PROPS];
	//Getting the collections
	verts[0] = getVertexData(_xName);
	verts[1] = getVertexData(_yName);
	for (int i = 0; i < NUM_PROPS; i++){
		if (verts[i].size() <= 0){
			verts[i] = std::vector<GLfloat>(numVertices, 0);
		}
	}
	//Adding them all up
	for (int i = 0; i < numVertices; i++){
		for (int j = 0; j < NUM_PROPS; j++){
			vertexData.push_back(verts[j][i]);
		}
	}
	//Return the bundled up vertex data
	return vertexData;
}

std::vector<GLfloat> PLYModelReader::getAllVertexData(){
	/*Will grab ALL variables and concatenate them together
	  then return that*/
	//Initalizing the vertexData vector that we will return
	std::vector<GLfloat> vertexData;
	//Reserve it for numVertices * size of propVec amount of data
	vertexData.reserve(numVertices * propVec.size());
	//Create a vector of GLfloat vectors that will be used to store copies of each
	//vert datas on the propVec vector
	std::vector<std::vector<GLfloat>> vertsVec;
	//Give it a size of propVec's size
	vertsVec.resize(propVec.size());
	//Getting the collections and saving each piece of data
	for (size_t i = 0; i < vertsVec.size(); i++){
		vertsVec[i] = getVertexData(propVec[i]->getName());
	}
	//Now we will set up the vertexData vector by
	//adding up all vert datas line by line
	for (int i = 0; i < numVertices; i++){
		for (size_t j = 0; j < vertsVec.size(); j++){
			vertexData.push_back(vertsVec[j][i]);
		}
	}
	//Return the bundled up vertex data
	return vertexData;
}

std::vector<GLuint> PLYModelReader::getIndices(){
	return indices;
}

std::vector<int> PLYModelReader::getIndiceCountData(){
	return indiceCountData;
}