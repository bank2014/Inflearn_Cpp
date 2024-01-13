#pragma once

class FileIO
{
public:
	std::fstream* file; // C++ style
	FILE* file_c;				// C style

public:
	FileIO();
	~FileIO();

	bool	SmartOpen(const std::string fileName, std::ios_base::openmode mode);
	bool	SmartOpen(const char* filename, const char* mode);
};
