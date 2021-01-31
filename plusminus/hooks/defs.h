typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
inline SendProjectileAttack_fn original_sendprojectileattack{ };

typedef Projectile* (__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef bool(__fastcall* can_attack_fn)(void*, void*);
inline can_attack_fn original_canattack;

typedef void(__fastcall* clientinput_fn)(DWORD64, DWORD64);
inline clientinput_fn original_clientinput;

typedef void(__fastcall* dohitnotify)(BaseCombatEntity*, HitInfo*);
inline dohitnotify original_dohitnotify;

typedef void(__fastcall* lateupd)(uintptr_t);
inline lateupd original_updateambient;

typedef bool(__fastcall* isheadshot)(DWORD64);
inline isheadshot original_getisheadshot;

typedef void(__fastcall* traceallthing)(uintptr_t, uintptr_t, uintptr_t);
inline traceallthing original_traceall;

typedef float(__fastcall* getrandvel)(uintptr_t);
inline getrandvel original_getrandomvelocity;

typedef void(__fastcall* sendclienttick)(BasePlayer*);
inline sendclienttick original_sendclienttick;

typedef void(__fastcall* UnregisterFromVisibilityS)(BasePlayer*, float, bool);
inline UnregisterFromVisibilityS original_UnregisterFromVisibility;

typedef Vector3(__fastcall* getpos)(DWORD64);
inline getpos original_geteyepos;

typedef void(__fastcall* crrfrawef)(BasePlayer*, Vector3);
inline crrfrawef original_forcepos;

typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
inline modifiedaimconedirection original_aimconedirection;

typedef void(__fastcall* addpunch)(uintptr_t, Vector3, float);
inline addpunch original_addpunch;

typedef uintptr_t(__fastcall* createff)(pUncStr, uintptr_t);
inline createff original_createeffect;

typedef Vector3(__fastcall* movetowards)(Vector3, Vector3, float);
inline movetowards original_movetowards;

typedef uintptr_t(__fastcall* createorupdent)(uintptr_t, uintptr_t, long);
inline createorupdent original_createorupdateentity;

typedef void(__fastcall* glowupd)(uintptr_t);
inline glowupd original_glowupdate;

typedef void(__fastcall* SetFlying_fn)(void*, void*);
inline SetFlying_fn original_setflying{};

typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
inline consoleRun original_consolerun{};

typedef bool(__fastcall* cancan)(void*, void*);
inline cancan original_canholditems;

typedef void(__fastcall* HandleRunning_fn)(void*, void*, bool);
inline HandleRunning_fn original_handleRunning{};

typedef void(__fastcall* handlejumping)(void*, void*, bool, bool);
inline handlejumping original_handleJumping{};