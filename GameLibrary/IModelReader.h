#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

namespace bobcat {

	/**
	* Abstract class that all model readers must derive from and use.
	* Model readers can load model data from a file and organize all the vertex and indice data
	* together for easy retrieval.
	*/
	class IModelReader {
	public:
		/**
		* Read model from file.
		* @param _fileName Name of model file to read.
		*/
		virtual void readModel(std::string _fileName) = 0;

		/**
		* Get all vertex data from a model file.
		* @return STL vector of GLfloats containing vertex data.
		*/
		virtual std::vector<GLfloat> getAllVertexData() = 0;

		/**
		* Get model indices.
		* @return STL vector of indice GLuints.
		*/
		virtual std::vector<GLuint> getIndices() = 0;

		/**
		* Get indice count data. (which is the amount of vertices represented with each indice)
		* @return STL vector of indice count data.
		*/
		virtual std::vector<int> getIndiceCountData() = 0;

		virtual ~IModelReader(){};
	};

}