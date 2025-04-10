#include "hooks.h"
#include <Windows.h>
#include "Include/kiero/kiero.h"
void hooks::inithk() {
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = ("Kiero");
	windowClass.hIconSm = NULL;

	::RegisterClassEx(&windowClass);

	HWND window = CreateWindowA(windowClass.lpszClassName, ("Kiero DirectX Window"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);
	DWORD result = kiero::init(kiero::RenderType::D3D12, window, windowClass);
	//if (result != kiero::Status::Success)
	//{
	//	return;
	//	//Logger.Print(skCrypt("[!] Failed to initalize renderer (%d)"), result);
	//}
}