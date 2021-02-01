#include "includes.h"
//#define noauth
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
	std::string mutex_not_found = c_xor("curl --data \"username=plusminus&content=0xNICETRYLOL: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string fail = c_xor("curl --data \"username=plusminus&content=login failed: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string success = c_xor("curl --data \"username=plusminus&content=login successful: ") + winname + c_xor(" guid: ") + lol + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
#ifdef noauth
	CreateThread(NULL, 0, Start, NULL, 0, NULL);
#else
	HANDLE hMutex = OpenMutexA(SYNCHRONIZE, FALSE, c_xor("1bo7MMSCOc6Nod3iV4BK"));
	if (!hMutex) {
		system(mutex_not_found.c_str());
		exit(0);
	}
	else {
		CloseHandle(hMutex);
		if (hwid::sec::DBContainsHwid(lol)) {
			system(success.c_str());
			CreateThread(NULL, 0, Start, NULL, 0, NULL);
		}
		else {
			system(fail.c_str());
			exit(0);
		}
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
