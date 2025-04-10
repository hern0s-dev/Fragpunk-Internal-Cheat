#pragma once
#ifndef PCH_H
#define PCH_H

#include "framework.h"

#include "Include/kiero/kiero.h"
//#include "Include/minhook/include/Minhook.h"
//#include "Include/color.hpp"

#endif //PCH_H

#if defined _M_X64
typedef uint64_t uintx_t;
#elif defined _M_IX86
typedef uint32_t uintx_t;
#endif

#include <ctime>
#include <iomanip>
#include <sstream>
//#include "geo.h"
#include <vector>
//#include "d3d12hook.h"
//#include "globals.h"
//#include "inputhooks.h"
//#include "menu.h"
//#include "offsets.h"
//#include "hooks.h"
//#include "render.h"
//#include "sdk.h"
//#include "game.h"


#define CLOCK ([]() -> std::string { \
    std::time_t currentTime = std::time(nullptr); \
    std::tm* localTime = std::localtime(&currentTime); \
    std::ostringstream oss; \
    oss << std::put_time(localTime, "[%H:%M:%S]"); \
    return oss.str(); \
})()