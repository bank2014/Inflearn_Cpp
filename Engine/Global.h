#pragma once
#pragma warning(disable:4099)
#define _CRT_SECURE_NO_WARNINGS

#include <array>
#include <vector>
#include <map>
#include <unordered_map> 
#include <queue>

#include <string>
#include <memory>
#include <chrono>
#include <tchar.h>
#include <algorithm>
#include <sstream>
#include <filesystem>

// D3D11
#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DirectXTex.h"	
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")	
#pragma comment (lib, "DirectXTex.lib")
#pragma comment (lib, "Engine.lib")

// dx write, dx2d
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// fmod
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment( lib, "fmod_vc.lib")

#define ASSERT_HR(hr) (assert(SUCCEEDED(hr)))

#define T_PI (3.141592f)
#define T_EPSILON ( 0.0001f)
#define RadianToDegree(radian) ( radian *( 180.0f / T_PI))
#define DegreeToRadian(degree) ( degree *( T_PI / 180.0f))
#define randstep(fmin, fmax) ((float)fmin+((float)fmax-(float)fmin)* rand() / RAND_MAX)

using namespace DirectX;
using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::make_unique;
using std::make_shared;
using std::wstring;

typedef std::basic_string<TCHAR>    STR;
typedef std::basic_string<wchar_t>  WSTR;

inline static std::string wtm(const std::wstring& wstr)
{
    if (wstr.empty())
        return std::string();

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], sizeNeeded, nullptr, nullptr);
    return str;
}

inline static std::wstring mtw(const std::string& str)
{
    if (str.empty())
        return std::wstring();

    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
    std::wstring wstr(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], sizeNeeded);
    return wstr;
}

inline static void T_Debug(const WCHAR* msg)
{
#ifdef _DEBUG
    OutputDebugString(msg);
#endif
}
