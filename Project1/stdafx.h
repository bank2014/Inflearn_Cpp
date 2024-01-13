#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <functional>
#include <limits>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

using byte = unsigned char;
using int32 = __int32;
using int64 = __int64;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

enum Status : bool {
	success = false,
	error = true
};
