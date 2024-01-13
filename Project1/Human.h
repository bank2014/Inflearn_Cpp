#pragma once
#include "Object.h"

class Human : public Object {
public:
	std::string name;

public:
	Human() : name("N/A"){} 
	Human(std::string _name) : name(_name){}
	virtual ~Human() {}

	void Init() override;
};