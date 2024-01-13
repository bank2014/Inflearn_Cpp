#include "stdafx.h"
#include "Student.h"

uint32 Student::studentCount = 0;

Student::Student()
{
	id = 0;
	kor = 0;
	eng = 0;
	math = 0;
	avg = 0.0f;
	total = 0;
	++studentCount;
}

Student::Student(std::string _name, uint32 _id, uint32 _kor, uint32 _eng, uint32 _math)
	: Human(_name), id(_id), kor(_kor), eng(_eng), math(_math) 
{
	CalTotalAndAvg();
	++studentCount;
}

Student::Student(
	std::string _name,
	std::function<uint32()> id_func,
	std::function<uint32()> kor_func,
	std::function<uint32()> eng_func,
	std::function<uint32()> math_func)
	: Human(_name)
{
	id = id_func();
	kor = kor_func();
	eng = eng_func();
	math = math_func();
	CalTotalAndAvg();
	++studentCount;
}

void Student::Init()
{
}

void Student::Print() const
{
	cout 
		<< std::left << std::setw(14) << id		
		<< std::left << std::setw(14) << name	
		<< std::left << std::setw(8) << kor	
		<< std::left << std::setw(8) << eng	
		<< std::left << std::setw(8) << math	
		<< std::left << std::setw(8) << total
		<< std::left << std::setw(8) << avg << endl;
}

void Student::CalTotalAndAvg() 
{
  total = kor + eng + math;
  avg = total / 3.0f;
}

void Student::Serialize(FILE* file_out) const
{
	size_t size = name.size();
	fwrite(&size, sizeof(size_t), 1, file_out);
	fwrite(name.c_str(), sizeof(char), size, file_out);
	fwrite(&id, sizeof(id), 1, file_out);
	fwrite(&kor, sizeof(kor), 1, file_out);
	fwrite(&eng, sizeof(eng), 1, file_out);
	fwrite(&math, sizeof(math), 1, file_out);
}

void Student::Deserialize(FILE* file_in)
{
	size_t size = 0;
	fread(&size, sizeof(size), 1, file_in);
	char* strBuffer = new char[size];
	fread(strBuffer, sizeof(char), size, file_in);
	name.assign(strBuffer, size);
	delete[] strBuffer;
	fread(&id, sizeof(id), 1, file_in);
	fread(&kor, sizeof(kor), 1, file_in);
	fread(&eng, sizeof(eng), 1, file_in);
	fread(&math, sizeof(math), 1, file_in);

	CalTotalAndAvg();	
}
