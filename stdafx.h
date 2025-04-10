#pragma once

#include <stdio.h>
#include <windows.h>
#include "skStr.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>

#include <MinHook.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
//#define LOG(fmt, ...) printf("[>][%s:%d - %s] " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

//#define LOG(fmt, ...) do { \
//    int len = _vscprintf(fmt, ##__VA_ARGS__) + 1; /* Compute required length */ \
//    char* buffer = (char*)malloc(len * sizeof(char)); \
//    if (buffer) { \
//        vsprintf_s(buffer, len, fmt, ##__VA_ARGS__); \
//        printf("%s\n", buffer); \
//        free(buffer); \
//    } \
//} while(0)


static inline void LOG(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int len = _vscprintf(fmt, args) + 1; // Compute required length
    char* buffer = (char*)malloc(len * sizeof(char));
    if (!buffer) return;

    vsprintf_s(buffer, len, fmt, args);
    va_end(args);

    // Print to console
    printf("%s\n", buffer);

    free(buffer);
}