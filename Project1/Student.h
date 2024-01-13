#pragma once
#include "Human.h"
#include "FileIO.h"

class Student final : public Human
{
public:
	uint32 id;
	uint32 kor;
	uint32 eng;
	uint32 math;
	uint32 total;
	float avg;
	static uint32 studentCount;

public:
	Student();
	Student(std::string _name, uint32 _id, uint32 _kor, uint32 _eng, uint32 _math);
	Student(
		std::string _name,
		std::function<uint32()> id_func,
		std::function<uint32()> kor_func,
		std::function<uint32()> eng_func,
		std::function<uint32()> math_func);

	~Student() { --studentCount; }

	void Init() override;

	void Print() const;
	void CalTotalAndAvg();
	void Serialize(FILE* file_out) const;
	void Deserialize(FILE* file_in);
};
