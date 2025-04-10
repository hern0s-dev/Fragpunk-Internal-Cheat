

#include "features.h"

#include "fonts.h"
#include "menu.h"
void Render::SetupFonts() {
	//auto io = ImGui::GetIO();
	//Fonts::BloomingElegant = io.Fonts->AddFontFromMemoryTTF(BloomingElegantData, sizeof(BloomingElegantData), 20.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
 //   Fonts::Pixel = io.Fonts->AddFontFromMemoryTTF(SmallestPixelData, sizeof(SmallestPixelData), 10.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

	//ImFontConfig font_config;
	//font_config.PixelSnapH = false;
	//font_config.FontDataOwnedByAtlas = false;
	//font_config.OversampleH = 5;
	//font_config.OversampleV = 5;
	//font_config.RasterizerMultiply = 1.2f;

	//static const ImWchar ranges[] = {

	//	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	//	0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
	//	0x2DE0, 0x2DFF, // Cyrillic Extended-A
	//	0xA640, 0xA69F, // Cyrillic Extended-B
	//	0xE000, 0xE226, // icons
	//	0,
	//};

	//font_config.GlyphRanges = ranges;
	//Fonts::Tahoma = io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\tahoma.ttf"), 14.f, &font_config, ranges);
	//io.Fonts->AddFontDefault();


	//float baseFontSize = 16.0f;
	//float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

	//static constexpr ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	//ImFontConfig iconsConfig;
	//iconsConfig.MergeMode = true;
	//iconsConfig.PixelSnapH = true;
	//iconsConfig.GlyphMinAdvanceX = iconFontSize;

	//font_awesome_16px = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeCompressed_compressed_data, FontAwesomeCompressed_compressed_size, 16.f, &iconsConfig, iconsRanges);

	//iconsConfig.MergeMode = false; // Merge icon font to the previous font if you want to have both icons and text
	//iconsConfig.GlyphMinAdvanceX = 17.5f;
	//font_awesome_17px = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeCompressed_compressed_data, FontAwesomeCompressed_compressed_size, 17.5f, &iconsConfig, iconsRanges);

	//io.IniFilename = NULL;

	//ImGui::GetStyle().WindowBorderSize = 0.f;
	//ImGui::GetStyle().FrameBorderSize = 0.f;



	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	Fonts::BloomingElegant = io.Fonts->AddFontFromMemoryTTF(BloomingElegantData, sizeof(BloomingElegantData), 17.5f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

	float baseFontSize = 17.5f;
	float iconFontSize = baseFontSize * 2.0f / 10.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

	static constexpr ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig iconsConfig;
	iconsConfig.PixelSnapH = true;
	iconsConfig.MergeMode = true; // Merge icon font to the previous font if you want to have both icons and text
	iconsConfig.GlyphMinAdvanceX = iconFontSize;
	font_awesome_17px = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeCompressed_compressed_data, FontAwesomeCompressed_compressed_size, 17.5f, &iconsConfig, iconsRanges);

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;
	static const ImWchar ranges[] = {

	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
	0x2DE0, 0x2DFF, // Cyrillic Extended-A
	0xA640, 0xA69F, // Cyrillic Extended-B
	0xE000, 0xE226, // icons
	0,
	};
	font_config.GlyphRanges = ranges;
	font_tahoma = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\tahoma.ttf", 13.0f, &font_config, ranges);
	Fonts::Pixel = io.Fonts->AddFontFromMemoryTTF(SmallestPixelData, sizeof(SmallestPixelData), 10.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

	io.Fonts->AddFontDefault();

	//io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	io.IniFilename = NULL;

	ImGui::GetStyle().WindowBorderSize = 0.f;
	ImGui::GetStyle().FrameBorderSize = 0.f;

	io.Fonts->Build();
};

HRESULT Render::PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	static bool init = false;
	if (!init) {

		if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&renderer_data::device)))
		{
			renderer_data::swapChain = swapChain;
			renderer_data::device->GetImmediateContext(&renderer_data::immediateContext);
			DXGI_SWAP_CHAIN_DESC sd;
			swapChain->GetDesc(&sd);
			renderer_data::game_wnd = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (!pBackBuffer) return PresentOriginal(swapChain, syncInterval, flags);
			renderer_data::device->CreateRenderTargetView(pBackBuffer, NULL, &renderer_data::renderTargetView);
			pBackBuffer->Release();
			//Data::oWndProc = (WNDPROC)SetWindowLongPtr(game_wnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

			ImGui::CreateContext();
			ImGui::StyleColorsDark();
			Render::SetupFonts();

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(renderer_data::game_wnd);
			ImGui_ImplDX11_Init(renderer_data::device, renderer_data::immediateContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			inputhook::Init(sd.OutputWindow);
			init = true;
			//LOG("PresentHook initialized.");
		}
	}

	if (GetAsyncKeyState(VK_INSERT) & 0x1) {   // Menu hotkey
		ShowMenu ? ShowMenu = false : ShowMenu = true;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (renderer_data::draw)
	{
		ImGui::GetMouseCursor();
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		ImGui::GetIO().WantCaptureMouse = ShowMenu;
		ImGui::GetIO().MouseDrawCursor = ShowMenu;

		features::main::run();
		if (ShowMenu)
		{
			if (MainMenu->Begin("MFX"))
			{
				MainMenu->End();
			};
		}
		

	}
	static bool showB = TRUE;
	//ImGui::ShowDemoWindow(&showB);


	ImGui::EndFrame();
	ImGui::Render();

	renderer_data::immediateContext->OMSetRenderTargets(1, &renderer_data::renderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return PresentOriginal(swapChain, syncInterval, flags);
}


HRESULT Render::ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	if (renderer_data::renderTargetView)
	{
		renderer_data::immediateContext->OMSetRenderTargets(0, 0, 0);
		renderer_data::renderTargetView->Release();
	}
	auto result = ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);

	ID3D11Texture2D* pBuffer;
	HRESULT pSwapChainBuffer = renderer_data::swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	if (!pBuffer) return result;
	if (pSwapChainBuffer != S_OK)
	{
		// Perform error handling here!
		//LOG("ResizeHook failed. pBuffer was null.");
	}

	HRESULT pDeviceRenderTarget = renderer_data::device->CreateRenderTargetView(pBuffer, NULL, &renderer_data::renderTargetView);
	if (pDeviceRenderTarget != S_OK)
	{
		// Perform error handling here!
		//LOG("ResizeHook failed. pDeviceRenderTarget was null.");
	}

	// Release buffer
	pBuffer->Release();

	// Set Rendertarget
	renderer_data::immediateContext->OMSetRenderTargets(1, &renderer_data::renderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	renderer_data::immediateContext->RSSetViewports(1, &vp);
	//LOG("ResizeHook finished.");
	return result;
}