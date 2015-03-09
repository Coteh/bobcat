#pragma once
#include <string>
#include <vector>

namespace bobcat {

	namespace FileIO {

		/**
		* Abstract class that all file readers must derive from and use.
		*/
		class IFileReader{
		public:
			/**
			* Read from file.
			* @param _filePath Path of the file to read.
			* @return A STL vector containing contents of the file.
			*/
			virtual std::vector<std::string> readFromFile(std::string _filePath) = 0;

			/**
			* Read from file and return a string of the file contents.
			* @param _filePath Path of the file to read.
			* @return A STL string containing contents of the file.
			*/
			virtual std::string readFromFileAsString(std::string _filePath) = 0;

			virtual ~IFileReader(){};
		};

	};

}