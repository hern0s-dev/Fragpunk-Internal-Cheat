#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <cstdio>
#include <cstdint>

#include <winternl.h>
#include <dwmapi.h>

#include <dxgi1_4.h>
#pragma comment(lib, "d3d12.lib")

#include <d3d12.h>

//#include "Include/imgui/imgui.h"
//#include "Include/imgui/imgui_impl_win32.h"
//#include "Include/imgui/imgui_impl_dx12.h"

#pragma comment(lib,"Dwmapi.lib")