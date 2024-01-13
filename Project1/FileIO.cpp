#include "stdafx.h"
#include "FileIO.h"

FileIO::FileIO()
{
	file = nullptr;
	file_c = nullptr;
}

FileIO::~FileIO()
{
	if (file) file->close();
	if (file_c) fclose(file_c);
}

bool FileIO::SmartOpen(const std::string fileName, std::ios_base::openmode mode)
{
	try{
		file->open(fileName, mode);
		if (!file->is_open()) throw std::runtime_error("[ERROR] 파일 open 실패 (fstream* file)");
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << endl;
		return error;
	}
	return success;
}

bool FileIO::SmartOpen(const char* filename, const char* mode)
{
	try {
		file_c = fopen(filename, mode);
		if (!file_c) throw std::runtime_error("[ERROR] 파일 open 실패 (FILE* file_c)");
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << endl;
		return error;
	}
	return success;
}
