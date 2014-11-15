#pragma once
#include <GL\glew.h>
#include "IModelReader.h"
#include "FileReader.h"

#define PLY_MAGIC_NUMBER "ply"
#define PLY_FORMAT_STRING "format"
#define PLY_COMMENT_STRING "comment"
#define PLY_ELEMENT_STRING "element"
#define PLY_PROPERTY_STRING "property"
#define PLY_END_HEADER_STRING "end_header"

class IPLYProperty{
public:
	virtual std::string getName() = 0;
	virtual void setName(std::string _name) = 0;
};

template <class T>
class PLYProperty : public IPLYProperty{
private:
	std::string name;
	std::vector<T> data;
public:
	PLYProperty(std::string _name){
		setName(_name);
	}
	~PLYProperty(){
		data.clear();
		std::vector<T> clearVec;
		clearVec.swap(data);
	}
	inline virtual std::string getName(){
		return name;
	}
	inline virtual void setName(std::string _name){
		name = _name;
	}
	inline std::vector<T> getData(){
		return data;
	}
	inline void addData(T _data){
		data.push_back(_data);
	}
	inline void addData(std::vector<T> _data){
		for (int i = 0; i < _data.size(); i++){
			addData(_data[i]);
		}
	}
};

class PLYModelReader : public IModelReader, public FileReader {
private:
	typedef std::vector<std::string> PlyFormatStorage;
	PlyFormatStorage fileContents;
	PlyFormatStorage::iterator fileIterator;
	enum PLY_FILE_FORMAT{
		ASCII_1_0 = 0,
		BINARY_LITTLE_ENDIAN_1_0 = 1,
		BINARY_BIG_ENDIAN_1_0 = 2
	};
	PLY_FILE_FORMAT plyFormat;
	enum PLY_READ_STAGE{
		NONE = 0,
		HEADER = 1,
		VERTICES = 2,
		INDICES = 4
	};
	PLY_READ_STAGE plyReadStage;
	enum PLY_HEADER_VARIABLE_INIT_STAGE{
		NO_VARS = 0,
		VERTEX_VARS = 1,
		INDICE_VARS = 2
	};
	PLY_HEADER_VARIABLE_INIT_STAGE headerInitStage;
	int numVertices;
	std::vector<GLuint> indices;
	std::vector<int> indiceCountData;
	std::vector<IPLYProperty*> propVec;
	bool isFirstTime;
	void clearVectors();
public:
	PLYModelReader();
	virtual ~PLYModelReader();
	virtual void readModel(std::string _fileName);
	std::vector<GLfloat> getVertexData(std::string _variableName);
	std::vector<GLfloat> getVertices(std::string _xName, std::string _yName, std::string _zName);
	std::vector<GLfloat> getVertices(std::string _xName, std::string _yName);
	std::vector<GLfloat> getAllVertexData();
	std::vector<GLuint> getIndices();
	std::vector<int> getIndiceCountData();
};

