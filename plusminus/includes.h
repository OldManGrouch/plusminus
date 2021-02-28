#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS
#define ALLOC_CONS 0
#define StrA
#define StrW
//#define rusticaland
#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <string>
#include <codecvt>
#include <locale>
#include <emmintrin.h>
#include "winternl.h"
#include <iostream>
#include <fstream>
#include "stuff/offsets.h"
#include "crc32.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <thread>
#include "stuff/xorstr.hpp"
#include <comdef.h>

#include "menu/imgui/imgui.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#include <Lmcons.h>
#include "stuff/hwid.h"

#include "stuff/mem.h"
#include "stuff/structs.h"
#include "stuff/math.h"
#include "stuff/vars.h"
#include "main/weapons.h"
#include "stuff/sdk.h"
#include "stuff/il2cpp.h"

#include "rust.h"
#include "main/targeting.h"
#include <d3d11.h>
#include "init/d3defs.h"
#include "rendering/rendering.h"
#include "framework.h"
#include "menu/imgui/imgui_impl_win32.h"
#include "menu/imgui/imgui_impl_dx11.h"
#include "menu/imgui/imgui_internal.h"
#include "menu/imgui/imgui_elements.h"
#include "hooks/minhook/include/MinHook.h"
#include "logsystem.h"
#include "main/aim.h"
#include "main/misc.h"
#include "main/lol.h"
#include "main/esp.h"

#include "main/entities.h"
#include "hooks/hooks.hpp"


#include "init/init.h"
#include "config/config.h"
#include "menu/menu.h"
#include "init/present.h"
#pragma comment(lib, "urlmon.lib")
#include <d3d11.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")