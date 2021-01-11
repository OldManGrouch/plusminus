typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
inline SendProjectileAttack_fn original_sendprojectileattack{ };

typedef Projectile*(__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef bool(__fastcall* can_attack_fn)(void*, void*);
inline can_attack_fn original_canattack;

typedef void(__fastcall* clientinput_fn)(DWORD64, DWORD64);
inline clientinput_fn original_clientinput;

typedef void(__fastcall* dohitnotify)(DWORD64, DWORD64);
inline dohitnotify original_dohitnotify;

typedef void(__fastcall* lateupd)(uintptr_t);
inline lateupd original_lateupdate;

typedef bool(__fastcall* isheadshot)(DWORD64);
inline isheadshot original_getisheadshot;

typedef void(__fastcall* forcepos)(BasePlayer*, Vector3);
inline forcepos original_forcepos;

typedef void(__fastcall* traceallthing)(uintptr_t, uintptr_t, uintptr_t);
inline traceallthing original_traceall;

typedef bool(__fastcall* sendclienttick)(void*);
inline sendclienttick original_sendclienttick;

typedef DWORD64(__fastcall* getskincolor)(DWORD64, float);
inline getskincolor original_getskincolor;

typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
inline modifiedaimconedirection original_aimconedirection;

typedef void(__fastcall* SetFlying_fn)(void*, void*);
inline SetFlying_fn original_setflying{};

typedef void(__fastcall* setskinproperties)(DWORD64, DWORD64);
inline setskinproperties original_setskinproperties;

typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
inline consoleRun original_consolerun{};

typedef bool(__fastcall* cancan)(void*, void*);
inline cancan original_canholditems;

typedef void(__fastcall* doattt)(uintptr_t);
inline doattt original_doattack;

typedef void(__fastcall* HandleRunning_fn)(void*, void*, bool);
inline HandleRunning_fn original_handleRunning{};
int yeet = 0;
bool __fastcall SendClientTick(void* baseplayer) {
	if (Misc::AntiAim) {
		auto input = read(baseplayer + 0x4C8, uintptr_t);
		if (!input) {
			return original_sendclienttick(baseplayer);
		}
		auto state = read(input + 0x20, uintptr_t);
		if (!state) {
			return original_sendclienttick(baseplayer);
		}
		auto current = read(state + 0x10, uintptr_t);
		if (!current) {
			return original_sendclienttick(baseplayer);
		}
		yeet += Misc::AntiAimSpeed;
		if (yeet >= 999) {
			yeet = 0;
		}
		write(current + 0x18, Vector3(100, yeet, 0), Vector3);
	}
	return original_sendclienttick(baseplayer);
}
inline Projectile* __fastcall CreateProjectile(void* BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
	Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);
	 
	if (Weapons::FatBullet) {
		projectile->thickness(1.f);
	}
	else {
		projectile->thickness(0.1f);
	}
	if (Weapons::NoRicochet) {
		projectile->ricochetChance(0.f);
	}
	if (Weapons::SpoofHitDistance) {
		projectile->traveledDistance(10000.f);
	}
	// TO-DO: delay shot
	return projectile;
}
inline bool __fastcall CanAttack(void* a1, void* a2) {
	if (Weapons::jumpAim) return true;
	return original_canattack(a1, a2);
}
void __fastcall LateUpdate(uintptr_t TOD_Sky) {
	typedef void(__stdcall* updamb)(uintptr_t);
	if (Misc::CustomAmbient) {
		auto night = read(TOD_Sky + 0x58, DWORD64);
		write(night + 0x50, 6.f, float);
	}
	return original_lateupdate(TOD_Sky);
}
void __fastcall TraceAll(uintptr_t test, uintptr_t traces, uintptr_t layerMask) {
	if (Weapons::Penetrate) {
		layerMask &= ~Tree;
		layerMask &= ~Deployed;
		layerMask &= ~Water;
	}
	return original_traceall(test, traces, layerMask);
}
typedef void(__stdcall* SetColor)(DWORD64, Str, Color);
typedef void(__stdcall* SetFloat)(DWORD64, Str, float);
void __fastcall SetSkinProperties(DWORD64 playermodel, DWORD64 materialpropblock) {
	
	if (!PlayerEsp::chams) {
		return original_setskinproperties(playermodel, materialpropblock);
	}
	else {
		((SetColor)(Storage::gBase + 0x1396C80))(materialpropblock, Str(L"_Color"), Color(1, 0, 0, 1));
		((SetFloat)(Storage::gBase + 0x1396D80))(materialpropblock, Str(L"niggamoment"), 58931.f);
	}
}
typedef void(__stdcall* CreateWithShader)(uintptr_t, uintptr_t);
typedef void(__stdcall* set_color)(uintptr_t, Color);
DWORD64 __fastcall GetSkinColor(DWORD64 skinset, float skinNumber) {
	DWORD64 color = original_getskincolor(skinset, skinNumber);

	/*DWORD64 staticMaterial = read(Storage::gBase + 0x29E5330, DWORD64);
	if (staticMaterial) {
		DWORD64 newMaterial = il2cpp_object_new(staticMaterial); 
		if (newMaterial) {
			((CreateWithShader)(Storage::gBase + 0x1397210))(newMaterial, utils::ShaderFind(Str(L"Transparent/Diffuse")));
			((set_color)(Storage::gBase + 0x1398AC0))(newMaterial, Color(1, 0, 0, 1));
			write(skinset + 0x70, newMaterial, uintptr_t);
		}
	}*/
	

	
	if (PlayerEsp::chams) {
		write(color + 0x0, 255.f, float);
		write(color + 0x4, 0.f, float);
		write(color + 0x8, 0.f, float);
		write(color + 0xC, 0.5f, float);
	}
	return color;
}
pUncStr __fastcall Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
	if (options->IsFromServer()) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find(xorstr(L"noclip")) != std::wstring::npos || cmd.find(xorstr(L"debugcamera")) != std::wstring::npos || cmd.find(xorstr(L"camspeed")) != std::wstring::npos || cmd.find(xorstr(L"admintime")) != std::wstring::npos) {
			strCommand = nullptr;
		}
	}
	return original_consolerun(options, strCommand, args);
}
Vector3 __fastcall GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	Vector3 heliDir = (HeliPrediction(LocalPlayer->GetBoneByID(head)) - LocalPlayer->GetBoneByID(head)).Normalized();
	Vector3 playerDir = (Prediction(LocalPlayer->GetBoneByID(head), TargetPlayer) - LocalPlayer->GetBoneByID(head)).Normalized();
	if (Combat::pSilent) {
		if (!Combat::pSilentOnKey) {
			if (Combat::pSilentTargeting == 0 && Storage::closestPlayer != NULL) {
				inputVec = playerDir;
			}
			if (Combat::pSilentTargeting == 1 && Storage::closestHeli != NULL && Storage::closestHeliObj != NULL) {
				inputVec = heliDir;
			}
		}
		else {
			if (GetAsyncKeyState(Keys::pSilent)) {
				if (Combat::pSilentTargeting == 0 && Storage::closestPlayer != NULL) {
					inputVec = playerDir;
				}
				if (Combat::pSilentTargeting == 1 && Storage::closestHeli != NULL && Storage::closestHeliObj != NULL) {
					inputVec = heliDir;
				}
			}
		}
	}
	if (Weapons::AntiSpread) {
		aimCone = 0.f;
	}
	return original_aimconedirection(aimCone, inputVec, anywhereInside);
}
bool waslagging = false;
void __fastcall ClientInput(DWORD64 baseplayah, DWORD64 ModelState) {
	typedef void(__stdcall* set_rayleigh)(float);
	if (Misc::Rayleigh) {
		((set_rayleigh)(Storage::gBase + CO::set_rayleigh))(Misc::RayleighAmount);
	}
	else {
		((set_rayleigh)(Storage::gBase + CO::set_rayleigh))(1.f);
	}
	EntityThreadLoop();
	if (!waslagging && Misc::FakeLag) {
		write(LocalPlayer + 0x5C8, 0.4f, float);
		waslagging = true;
	}
	else if (waslagging && !Misc::FakeLag) {
		write(LocalPlayer + 0x5C8, 0.05f, float);
		waslagging = false;
	}

	WeaponPatch();
	MiscFuncs();
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (Misc::Flyhack) LocalPlayer->AddFlag(ModelStateFlag::OnLadder);
	if (Misc::SilentWalk) LocalPlayer->RemoveFlag(ModelStateFlag::OnGround);
}
void __fastcall DoHitNotify(DWORD64 basecombatentity, DWORD64 hitinfo) {
	typedef float(__stdcall* Total)(uintptr_t);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	if (!oPlayerList) {
		DWORD64 val = read(Storage::gBase + CO::BasePlayer, DWORD64);
		DWORD64 st = read(val + 0xB8, DWORD64);
		oPlayerList = read(st + 0x8, DWORD64);
	}
	UINT64 ClientEntities_values = read(oPlayerList + 0x28, UINT64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	UINT64 EntityBuffer = read(ClientEntities_values + 0x18, UINT64);
	for (int i = 0; i <= EntityCount; i++) {
		BasePlayer* Player = (BasePlayer*)read(EntityBuffer + 0x20 + (i * 0x8), UINT64);
		if ((BasePlayer*)read(hitinfo + 0x40, uintptr_t) == Player) {
			Global::doneHits += 1;
			Global::doneDamage = ((Total)(Storage::gBase + 0x417960))(read(hitinfo + 0xC8, uintptr_t));
			Global::donePlayer = Player->GetName();
			if (Misc::CustomHitsound) {
				PlaySoundA(xorstr("C:\\plusminus\\hit.wav"), NULL, SND_ASYNC);
			}
			else { return original_dohitnotify(basecombatentity, hitinfo); }
		}
		else { return original_dohitnotify(basecombatentity, hitinfo); }
	}
}
void __fastcall ForcePositionTo(BasePlayer* pl, Vector3 pos) {
	uintptr_t movement = read(pl + 0x4D0, uintptr_t);
	if (GetAsyncKeyState(Keys::forcepos)) { }
	else {
		return original_forcepos(pl, pos);
	}
}
bool __fastcall get_isHeadshot(DWORD64 hitinfo) {
	if (Misc::CustomHitsound) { return false; }
	else { return original_getisheadshot(hitinfo); }
}
bool __fastcall CanHoldItems(void* a1, void* a2) {
	if (Weapons::canHoldItems) return true;
	return original_canholditems(a1, a2);
}
inline void __fastcall SendProjectileAttack(void* a1, void* a2) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	uintptr_t PlayerAttackA = read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	//printf("called spa\n");
	write(a2 + 0x20, Vector3(0, 0, 0), Vector3);
	uintptr_t AttackA = read(PlayerAttackA + 0x18, uintptr_t); // public Attack attack;
	if (Combat::silentAim || Combat::heliSilent) {
		if (Storage::closestPlayer != NULL && Combat::silentAim) {
			uint32_t bone;
			if (rand() % 100 < Combat::HeadshotPercentage) { bone = utils::StringPool::Get(Str(xorstr(L"head"))); }
			else { bone = utils::StringPool::Get(Str(xorstr(L"spine4"))); } 
			write(AttackA + 0x30, bone, uint32_t); /*public uint hitBone;*/
			write(AttackA + 0x64, 16144115, uint32_t); // public uint hitPartID;
		}
		else {
			if (Storage::closestHeli != NULL && Combat::heliSilent) {
				int health = (int)ceil(read(Storage::closestHeli + 0x20C, float));
				if (health <= 5000) {
					write(AttackA + 0x30, 224139191, uint32_t); // public uint hitBone;
				}
				else {
					write(AttackA + 0x30, 2699525250, uint32_t); // public uint hitBone;
				}
			}
		}
	}
	return original_sendprojectileattack(a1, a2);
}
void __fastcall HandleRunning(void* a1, void* a2, bool wantsRun) {
	if (Misc::omniSprint) wantsRun = true;
	return original_handleRunning(a1, a2, wantsRun);
}
void __fastcall SetFlying(void* a1, void* a2) {}
typedef void(__stdcall* BeginCycle)(uintptr_t);
typedef void(__stdcall* LaunchProjectile)(uintptr_t);
typedef void(__stdcall* UpdateAmmoDisplay)(uintptr_t);
typedef void(__stdcall* ShotFired)(uintptr_t);
typedef void(__stdcall* DidAttackClientside)(uintptr_t);
typedef void(__stdcall* DryFire)(uintptr_t);
typedef bool(__stdcall* HasAttackCooldown)(uintptr_t);
typedef void(__stdcall* Play)(uintptr_t, Str);
void __fastcall DoAttack(uintptr_t baseproj) {
	if (!LocalPlayer) { return; }

	if (read(baseproj + 0x270, bool) == false) {
		if (!LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY)) {
			return;
		}
	}
	else {
		if (!LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY)) {
			write(baseproj + 0x330, true);
		}
		if (read(baseproj + 0x330, bool) == false || !LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY)) {
			return;
		}
	}
	if (read(baseproj + 0x2EE, bool) == true && read(baseproj + 0x2EF, bool) == true) {
		((BeginCycle)(Storage::gBase + 0x58A050))(baseproj);
		return;
	}
	if (((HasAttackCooldown)(Storage::gBase + 0x2DD4B0))(baseproj)) { return; }

	if (read(baseproj + 0x270, bool) == true) {
		write(baseproj + 0x330, true);
	}
	int contents = read(read(baseproj + 0x2A0, uintptr_t) + 0x1C, int);
	if (contents <= 0) {
		if (LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY)) {
			((DryFire)(Storage::gBase + 0x58B360))(baseproj);
		}
		return;
	}
	if (read(baseproj + 0x180, uintptr_t)) {
		((Play)(Storage::gBase + 0x5C3600))(read(baseproj + 0x180, uintptr_t), Str(L"attack"));
	}
	((LaunchProjectile)(Storage::gBase + 0x58E570))(baseproj);
	((UpdateAmmoDisplay)(Storage::gBase + 0x590560))(baseproj);
	((ShotFired)(Storage::gBase + 0x58FD00))(baseproj);
	((DidAttackClientside)(Storage::gBase + 0x58A5E0))(baseproj);
	if (read(baseproj + 0x2EE, bool) == false) {
		((BeginCycle)(Storage::gBase + 0x58A050))(baseproj);
		return;
	}
	write(baseproj + 0x2EF, true, bool);
}
void HookFunction(void* Function, void** Original, void* Detour, bool autoEnable = true) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) { std::cout << (xorstr("Failed to initialize MinHook")) << std::endl; return; }
	MH_CreateHook(Function, Detour, Original);
	if (autoEnable)
		MH_EnableHook(Function);
}
inline void InitHook() {
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::set_flying), (void**)&original_setflying, SetFlying);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::SendProjectileAttack), (void**)&original_sendprojectileattack, SendProjectileAttack);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CanAttack), (void**)&original_canattack, CanAttack);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::SendClientTick), (void**)&original_sendclienttick, SendClientTick);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::HandleRunning), (void**)&original_handleRunning, HandleRunning);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, GetModifiedAimConeDirection);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CreateProjectile), (void**)&original_create_projectile, CreateProjectile);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CanHoldItems), (void**)&original_canholditems, CanHoldItems);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Run), (void**)&original_consolerun, Run);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetSkinColor), (void**)&original_getskincolor, GetSkinColor);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::TraceAll), (void**)&original_traceall, TraceAll);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + 0x2B1580), (void**)&original_domovement, DoMovement);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Launch), (void**)&original_launch, Launch);
	//HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + 0x58A5F0), (void**)&original_doattack, DoAttack);
	//HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHit), (void**)&original_dohit, DoHitS);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::LateUpdate), (void**)&original_lateupdate, LateUpdate);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ClientInput), (void**)&original_clientinput, ClientInput);
	//HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + 0x6313C0), (void**)&original_setskinproperties, SetSkinProperties);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHitNotify), (void**)&original_dohitnotify, DoHitNotify);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_isHeadshot), (void**)&original_getisheadshot, get_isHeadshot);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ForceToPos), (void**)&original_forcepos, ForcePositionTo);
}