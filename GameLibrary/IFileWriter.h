#pragma once
#include <string>
#include <vector>

namespace FileIO {

	class IFileWriter{
	public:
		virtual void writeToFile(std::string _fileName, std::vector<std::string> _data) = 0;
		virtual void writeToFile(std::string _fileName, std::string _line) = 0;
		virtual void appendToFile(std::string _fileName, std::string _line) = 0;
		virtual ~IFileWriter(){};
	};

};