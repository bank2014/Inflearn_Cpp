#pragma once
#include "Iterator.h"

template <typename T>
class Container {
public:
	virtual ~Container() {}
	virtual Iterator<T>* GetIterator() = 0;
};

