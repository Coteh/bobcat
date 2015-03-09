#pragma once
#include "IFileWriter.h"

namespace bobcat {

	namespace FileIO {

		class FileWriter : public IFileWriter {
		public:
			FileWriter();
			virtual void writeToFile(std::string _filePath, std::vector<std::string> _data);
			virtual void writeToFile(std::string _filePath, std::string _line);
			virtual void appendToFile(std::string _filePath, std::string _line);
			virtual ~FileWriter();
		};

	};

}