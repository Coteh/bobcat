#pragma once
#include "IFileReader.h"
#include <fstream>

namespace bobcat {

	namespace FileIO {

		class FileReader : public IFileReader{
		public:
			FileReader();
			virtual ~FileReader();
			virtual std::vector<std::string> readFromFile(std::string _fileName);
			virtual std::string readFromFileAsString(std::string _fileName);
		};

	};

}