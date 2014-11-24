#pragma once
#include "IFileReader.h"
#include <fstream>

namespace FileIO {

	class FileReader : public IFileReader{
	public:
		FileReader();
		virtual ~FileReader();
		virtual std::vector<std::string> readFromFile(std::string _fileName);
	};

};