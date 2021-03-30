extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		show = !show;
	}
	if (GetAsyncKeyState(vars::keys::locktarget) & 1) {
		vars::combat::lock_target = !vars::combat::lock_target;
	}

	return CallWindowProcA(original_windowproc, hWnd, uMsg, wParam, lParam);
}
HRESULT resize_hook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	Renderer::ResetCanvas( );

	if (render_target_view) render_target_view->Release( );

	if (immediate_context) immediate_context->Release( );
	if (device) device->Release( );

	device = nullptr;

	return resize_original(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
HRESULT present_hook(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags) {
	if (!device) {
		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&immediate_context);
		ID3D11Texture2D* renderTarget = nullptr;
		swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
		device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
		renderTarget->Release( );
		ImGui::CreateContext( );
		ImGui_ImplWin32_Init(game_window);
		ImGui_ImplDX11_Init(device, immediate_context);
		Renderer::InitRender(swapChain);
		menu::style( );
		Beep(500, 100);
		config.Initialize( );
	}

	immediate_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	immediate_context->RSGetViewports(&vps, &viewport);
	screen_size = {viewport.Width, viewport.Height};
	screen_center = {viewport.Width / 2.0f, viewport.Height / 2.0f};
	vars::stuff::ScreenHeight = viewport.Height;
	vars::stuff::ScreenWidth = viewport.Width;
	if (!vars::stuff::Panic) {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (Renderer::NewFrame(swapChain)) {
			pre_draw();
			Renderer::EndFrame( );
		}

		if (show) {
			DrawMenu();
		}
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	else {
		config.Initialize( );
		vars::misc::fov = 90.f;
		MH_DisableHook(MH_ALL_HOOKS);
	}
	return present_original(swapChain, SyncInterval, Flags);
}
void Start( ) {
	vars::stor::gBase = (DWORD64)GetModuleHandleA(xorstr("GameAssembly.dll"));
	vars::stor::uBase = (DWORD64)GetModuleHandleA(xorstr("UnityPlayer.dll"));
	il2cpp::init();

	while (!game_window) {
		EnumWindows([ ](HWND hWnd, LPARAM lParam) -> BOOL {
			DWORD pid = 0;
			GetWindowThreadProcessId(hWnd, &pid);
			if (pid == GetCurrentProcessId( )) {
				*reinterpret_cast<HWND*>(lParam) = hWnd;
				return FALSE;
			}

			return TRUE;
			}, reinterpret_cast<LPARAM>(&game_window));
	}

	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	auto featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd = {0};
	ZeroMemory(&sd, sizeof sd);
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = game_window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBoxW(0, xorstr(L"Failed to create D3D11 device and swap chain"), xorstr(L"Failure"), MB_ICONERROR);
	}
	else {
		auto table = *reinterpret_cast<PVOID**>(swapChain);
		present_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(table[ 8 ]);
		resize_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT)>(table[ 13 ]);

		context->Release( );
		device->Release( );
		swapChain->Release( );

		original_windowproc = (WNDPROC)SetWindowLongPtrW(game_window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

		DetourTransactionBegin( );
		DetourUpdateThread(GetCurrentThread( ));
		DetourAttach(&(LPVOID&)present_original, (PBYTE)present_hook);
		DetourTransactionCommit( );

		DetourTransactionBegin( );
		DetourUpdateThread(GetCurrentThread( ));
		DetourAttach(&(LPVOID&)resize_original, (PBYTE)resize_hook);
		DetourTransactionCommit( );
	}
}