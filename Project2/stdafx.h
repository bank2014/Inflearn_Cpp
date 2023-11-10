#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <cassert>

#include <vector>
#include <queue>
#include <array>

#include <cmath>
#include <thread>
#include <random>
#include <memory>

using byte = unsigned __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

enum class CollisionType {
    None,
    Partial,
    Full
};