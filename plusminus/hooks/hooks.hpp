#include "hooks/defs.h"
int yeet = 0;
bool __fastcall SendClientTick(void* baseplayer) {
	if (vars::misc::anti_aim) {
		auto input = read(baseplayer + 0x4C8, uintptr_t);
		auto state = read(input + 0x20, uintptr_t);
		auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
		yeet += vars::misc::anti_aim_speed;
		if (yeet >= 999) {
			yeet = 0;
		}
		write(current + 0x18, Vector3(100, yeet, 0), Vector3);
	}
	return original_sendclienttick(baseplayer);
}
inline Projectile* __fastcall CreateProjectile(void* BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
	Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);
	 
	if (vars::weapons::thick_bullet) {
		projectile->thickness(1.f);
	}
	else {
		projectile->thickness(0.1f);
	}
	if (vars::weapons::no_ricochet) {
		projectile->ricochetChance(0.f);
	}
	// TO-DO: delay shot
	return projectile;
}
inline bool __fastcall CanAttack(void* a1, void* a2) {
	if (vars::misc::can_attack) return true;
	return original_canattack(a1, a2);
}
void __fastcall LateUpdate(uintptr_t TOD_Sky) {
	typedef void(__stdcall* updamb)(uintptr_t);
	if (vars::misc::bright_ambient) {
		auto night = read(TOD_Sky + 0x58, DWORD64);
		write(night + 0x50, 6.f, float);
	}
	return original_lateupdate(TOD_Sky);
}
void __fastcall TraceAll(uintptr_t test, uintptr_t traces, uintptr_t layerMask) {
	if (vars::weapons::penetrate) {
		layerMask &= ~Tree;
		layerMask &= ~Deployed;
		layerMask &= ~Water;
	}
	return original_traceall(test, traces, layerMask);
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
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	Vector3 heliDir = (HeliPrediction(LocalPlayer->GetBoneByID(head)) - LocalPlayer->GetBoneByID(head)).Normalized();
	Vector3 playerDir;
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) {
		playerDir = (Prediction(TargetPlayer) - (LocalPlayer->GetBoneByID(head) + Vector3(0, 1.15, 0))).Normalized();
	}
	else {
		playerDir = (Prediction(TargetPlayer) - LocalPlayer->GetBoneByID(head)).Normalized();
	}
	if (vars::combat::psilent) {
		if (!vars::combat::psilent) {
			if (vars::combat::psilenttarget == 0 && vars::stor::closestPlayer != NULL) {
				inputVec = playerDir;
			}
			if (vars::combat::psilenttarget == 1 && vars::stor::closestHeli != NULL && vars::stor::closestHeliObj != NULL) {
				inputVec = heliDir;
			}
		}
		else {
			if (GetAsyncKeyState(vars::keys::psilent)) {
				if (vars::combat::psilenttarget == 0 && vars::stor::closestPlayer != NULL) {
					inputVec = playerDir;
				}
				if (vars::combat::psilenttarget == 1 && vars::stor::closestHeli != NULL && vars::stor::closestHeliObj != NULL) {
					inputVec = heliDir;
				}
			}
		}
	}
	if (vars::weapons::no_spread) {
		aimCone = 0.f;
	}
	return original_aimconedirection(aimCone, inputVec, anywhereInside);
}
bool waslagging = false;
void __fastcall ClientInput(DWORD64 baseplayah, DWORD64 ModelState) {
	if (!baseplayah) return;
	typedef void(__stdcall* set_rayleigh)(float);
	typedef void(__stdcall* OnLand)(BasePlayer*, float);
	typedef void(__stdcall* DoAttack)(uintptr_t);
	if (vars::misc::rayleigh_changer) {
		((set_rayleigh)(vars::stor::gBase + CO::set_rayleigh))(vars::misc::rayleigh_changer);
	}
	else {
		((set_rayleigh)(vars::stor::gBase + CO::set_rayleigh))(1.f);
	}
	if (vars::misc::suicide) {
		((OnLand)(vars::stor::gBase + CO::OnLand))(LocalPlayer, -50);
	}
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	if (vars::combat::psilent_autoshoot && vars::stor::closestPlayer != null && vars::combat::psilent) {
		BaseProjectile* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 basepr = read(weapon + oHeldEntity, DWORD64);
		DWORD64 mag = read(basepr + 0x2A0, DWORD64);
		int contents = read(mag + 0x1C, int);
		if (contents > 0 && utils::LineOfSight(TargetPlayer->GetBoneByID(head), (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) ? LocalPlayer->GetBoneByID(head) + Vector3(0, 1.15, 0) : LocalPlayer->GetBoneByID(head))) {
			INPUT    Input = { 0 };
			// left down 
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));

			// left up
			::ZeroMemory(&Input, sizeof(INPUT));
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}
	EntityThreadLoop();
	if (!waslagging && vars::misc::fake_lag) {
		write(LocalPlayer + 0x5C8, 0.4f, float);
		waslagging = true;
	}
	else if (waslagging && !vars::misc::fake_lag) {
		write(LocalPlayer + 0x5C8, 0.05f, float);
		waslagging = false;
	}
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Water, !vars::misc::jesus);
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Tree, vars::misc::walker);
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::AI, vars::misc::walker);
	WeaponPatch();
	MiscFuncs();
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (vars::misc::spoof_ladderstate) LocalPlayer->AddFlag(ModelStateFlag::OnLadder);
	if (vars::misc::silent_walk) LocalPlayer->RemoveFlag(ModelStateFlag::OnGround);
}
void __fastcall DoHitNotify(DWORD64 basecombatentity, DWORD64 hitinfo) {
	if (vars::misc::custom_hitsound) { PlaySoundA(xorstr("C:\\plusminus\\hit.wav"), NULL, SND_ASYNC); }
	else { return original_dohitnotify(basecombatentity, hitinfo); }
}
bool __fastcall get_isHeadshot(DWORD64 hitinfo) {
	if (vars::misc::custom_hitsound) { return false; }
	else { return original_getisheadshot(hitinfo); }
}
void __fastcall ForcePositionTo(BasePlayer* pl, Vector3 pos) {
	if (GetAsyncKeyState(vars::keys::forcepos)) { }
	else { return original_forcepos(pl, pos); }
}
bool __fastcall CanHoldItems(void* a1, void* a2) {
	if (vars::weapons::minicopter_aim) return true;
	return original_canholditems(a1, a2);
}
void __fastcall VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
	if (vars::players::chams) {
		return original_UnregisterFromVisibility(pl, 2.f, true);
	}
	else {
		return original_UnregisterFromVisibility(pl, dist, vis);
	}
}
inline void __fastcall SendProjectileAttack(void* a1, void* a2) {
	uintptr_t PlayerAttack = read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	uintptr_t Attack = read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
	if (vars::weapons::spoof_hitdistance) {
		write(a2 + 0x2C, vars::weapons::hitdistance, float);
	}
	if (vars::combat::hitbox_override || vars::combat::always_heli_rotor) {
		if (vars::combat::hitbox_override) {
			uint32_t bone;
			if (rand() % 100 < vars::combat::hs_percentage) { bone = utils::StringPool::Get(Str(xorstr(L"head"))); }
			else { bone = utils::StringPool::Get(Str(xorstr(L"spine4"))); } 
			write(Attack + 0x30, bone, uint32_t); // public uint hitBone;
			write(Attack + 0x64, 16144115, uint32_t); // public uint hitPartID;
		}
		else {
			if (vars::combat::always_heli_rotor) {
				int health = (int)ceil(read(vars::stor::closestHeli + 0x20C, float));
				if (health <= 5000) {
					write(Attack + 0x30, 224139191, uint32_t); // public uint hitBone;
				}
				else {
					write(Attack + 0x30, 2699525250, uint32_t); // public uint hitBone;
				}
			}
		}
	}
	return original_sendprojectileattack(a1, a2);
}
void __fastcall HandleRunning(void* a1, void* a2, bool wantsRun) {
	if (vars::misc::omnidirectional_sprinting) wantsRun = true;
	return original_handleRunning(a1, a2, wantsRun);
}
void __fastcall HandleJumping(void* a1, void* a2, bool wantsJump, bool jumpInDirection = false) { // recreated
	if (vars::misc::inf_jump) {
		if (!wantsJump) {
			return;
		}
		typedef void(__stdcall* Jump)(void*, void*, bool);
		((Jump)(vars::stor::gBase + 0x6CDFA0))(a1, a2, jumpInDirection);
	}
	else {
		return original_handleJumping(a1, a2, wantsJump, jumpInDirection);
	}
}
Vector3 __fastcall get_position(DWORD64 playereyes) {
	if (vars::misc::long_neck) {
		if (GetAsyncKeyState(vars::keys::longneck)) {
			return Vector3(LocalPlayer->GetBoneByID(head)) + Vector3(0, 1.15, 0);
		}
	}
	return original_geteyepos(playereyes);
}
void __fastcall SetFlying(void* a1, void* a2) {}

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
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::HandleJumping), (void**)&original_handleJumping, HandleJumping);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, GetModifiedAimConeDirection);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CreateProjectile), (void**)&original_create_projectile, CreateProjectile);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CanHoldItems), (void**)&original_canholditems, CanHoldItems);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Run), (void**)&original_consolerun, Run);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_position), (void**)&original_geteyepos, get_position);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::VisUpdateUsingCulling), (void**)&original_UnregisterFromVisibility, VisUpdateUsingCulling);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHit), (void**)&original_dohitt, DoHit);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::TraceAll), (void**)&original_traceall, TraceAll);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Launch), (void**)&original_launch, Launch);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::LateUpdate), (void**)&original_lateupdate, LateUpdate);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ClientInput), (void**)&original_clientinput, ClientInput);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHitNotify), (void**)&original_dohitnotify, DoHitNotify);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_isHeadshot), (void**)&original_getisheadshot, get_isHeadshot);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ForceToPos), (void**)&original_forcepos, ForcePositionTo);
}