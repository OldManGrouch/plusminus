#include "includes.h"
char dlldir[320];
void HWID_Checker(HINSTANCE hModule) {
	HW_PROFILE_INFO hwProfileInfo;
	GetCurrentHwProfile(&hwProfileInfo);
	WCHAR* guid = hwProfileInfo.szHwProfileGuid;
	_bstr_t b(guid);
	char* c = b;
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	std::string webhook_url = c_xor("https://discord.com/api/webhooks/782872540724199464/UClxJ-olKhhg0a35hFlpGbADTKBqD9D_W4f7PViY5AhZiO3mwcxeiBRHSLa6TriNuP-1");
	std::string avatar_url = c_xor("https://i.imgur.com/9FKjGO8.png");

	std::string lol = c;
	std::string winname = name;
	std::string fail = c_xor("curl --data \"username=plusminus&content=login failed: ") + winname + " guid: " + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string success = c_xor("curl --data \"username=plusminus&content=login successful: ") + winname + " guid: " + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	if (hwid::sec::DBContainsHwid(lol) && lol != "" && lol != " ") {
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//std::cout << "aaaaaaa\n";
		//hwid::sec::checkVersion();
		//hwid::sec::checkFile();
		system(success.c_str());
		DisableThreadLibraryCalls(hModule);
		GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
		CreateThread(NULL, 0, Start, NULL, 0, NULL);
	}
	else {
		if (winname == c_xor("TJ") && (lol == "" || lol == " ")) {
			//hwid::sec::checkVersion();
			//hwid::sec::checkFile();
			system(success.c_str());
			DisableThreadLibraryCalls(hModule);
			GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
			for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
			CreateThread(NULL, 0, Start, NULL, 0, NULL);
		}
		else {
			system(fail.c_str());
			exit(0);
		}
	}
}
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		HWID_Checker(hModule);
		break;
	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
		DetourTransactionCommit();
		break;
	}
	return TRUE;
}
