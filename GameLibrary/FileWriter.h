#pragma once
#include "IFileWriter.h"
#include <iostream>
#include <fstream>

namespace FileIO {

	class FileWriter : public IFileWriter {
	public:
		FileWriter();
		virtual void writeToFile(std::string _fileName, std::vector<std::string> _data);
		virtual void writeToFile(std::string _fileName, std::string _line);
		virtual void appendToFile(std::string _fileName, std::string _line);
		virtual ~FileWriter();
	};

};