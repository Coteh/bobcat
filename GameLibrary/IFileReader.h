#pragma once
#include <string>
#include <vector>

namespace FileIO {

	class IFileReader{
	public:
		virtual std::vector<std::string> readFromFile(std::string _fileName) = 0;
		virtual ~IFileReader(){};
	};

};