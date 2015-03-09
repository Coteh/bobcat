#pragma once
#include <string>
#include <vector>

namespace bobcat {

	namespace FileIO {

		/**
		* Abstract class that all file writers must derive from and use.
		*/
		class IFileWriter{
		public:
			/**
			* Write to file.
			* @param _filePath Path of file to write to.
			* @param _data STL vector of STL string data to write to file.
			*/
			virtual void writeToFile(std::string _filePath, std::vector<std::string> _data) = 0;

			/**
			* Write to file.
			* @note Will empty out contents that already exist on file and begin writing in a clean slate.
			* Use appendToFile instead if you would like to just add on to the existing file contents.
			* @param _filePath Path of file to write to.
			* @param _line STL string of data to write to file.
			*/
			virtual void writeToFile(std::string _filePath, std::string _line) = 0;

			/**
			* Write to file, keeping intact its contents.
			* @param _filePath Path of file to write to.
			* @param _line STL string of data to write to file.
			*/
			virtual void appendToFile(std::string _filePath, std::string _line) = 0;

			virtual ~IFileWriter(){};
		};

	};

}