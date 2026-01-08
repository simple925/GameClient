#pragma once


// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Directx11 라이브러리
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// STL 자료구조
#include <vector>
#include <list>
#include <map>
using namespace std;

// 상대경로
#include "resource.h"
#include "global.h"
