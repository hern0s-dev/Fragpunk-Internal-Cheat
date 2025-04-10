#pragma once
#include "stdafx.h"

inline HRESULT(*PresentOriginal)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
inline HRESULT(*ResizeOriginal)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;



namespace renderer_data {
	inline IDXGISwapChain* swapChain = nullptr;
	inline ID3D11Device* device = nullptr;
	inline HWND game_wnd{ NULL };
	inline ID3D11DeviceContext* immediateContext = nullptr;
	inline ID3D11RenderTargetView* renderTargetView = nullptr;
	inline bool draw = true;
	inline uint32_t screenshot_count = 0;
}
namespace Fonts {
	inline ImFont* Tahoma = nullptr;
	inline ImFont* Pixel = nullptr;
	inline ImFont* BloomingElegant = nullptr;
}
class Render {
	Render();
public:
	static HRESULT PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
	static HRESULT ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	static void SetupFonts();
};
