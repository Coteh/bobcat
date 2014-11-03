#pragma once
#include <string>

class IModelReader {
public:
	virtual void readModel(std::string _fileName) = 0;
	virtual ~IModelReader(){};
};

