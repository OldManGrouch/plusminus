typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
inline SendProjectileAttack_fn original_sendprojectileattack{ };

typedef Projectile* (__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef bool(__fastcall* can_attack_fn)(void*, void*);
inline can_attack_fn original_canattack;

typedef void(__fastcall* clientinput_fn)(DWORD64, DWORD64);
inline clientinput_fn original_clientinput;

typedef void(__fastcall* dohitnotify)(DWORD64, DWORD64);
inline dohitnotify original_dohitnotify;

typedef void(__fastcall* setskinproperties)(DWORD64, DWORD64);
inline setskinproperties original_setskinproperties;

typedef void(__fastcall* lateupd)(uintptr_t);
inline lateupd original_lateupdate;

typedef bool(__fastcall* isheadshot)(DWORD64);
inline isheadshot original_getisheadshot;

typedef void(__fastcall* traceallthing)(uintptr_t, uintptr_t, uintptr_t);
inline traceallthing original_traceall;

typedef bool(__fastcall* sendclienttick)(void*);
inline sendclienttick original_sendclienttick;

typedef DWORD64(__fastcall* getskincolor)(DWORD64, float);
inline getskincolor original_getskincolor;

typedef void(__fastcall* crrfrawef)(BasePlayer*, Vector3);
inline crrfrawef original_forcepos;

typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
inline modifiedaimconedirection original_aimconedirection;

typedef void(__fastcall* SetFlying_fn)(void*, void*);
inline SetFlying_fn original_setflying{};

typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
inline consoleRun original_consolerun{};

typedef bool(__fastcall* cancan)(void*, void*);
inline cancan original_canholditems;

typedef void(__fastcall* HandleRunning_fn)(void*, void*, bool);
inline HandleRunning_fn original_handleRunning{};