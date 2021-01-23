#include "hooks/defs.h"
int yeet = 0;
bool __fastcall SendClientTick(void* baseplayer) {
	if (Misc::AntiAim) {
		auto input = read(baseplayer + 0x4C8, uintptr_t);
		auto state = read(input + 0x20, uintptr_t);
		auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
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
	// TO-DO: delay shot
	return projectile;
}
inline bool __fastcall CanAttack(void* a1, void* a2) {
	if (Weapons::jumpAim) return true;
	return original_canattack(a1, a2);
}
inline bool __fastcall CanJump(void* a1, void* a2) {
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
	Vector3 playerDir;
	if (Misc::LongNeck && GetAsyncKeyState(Keys::neck)) {
		playerDir = (Prediction(TargetPlayer) - (LocalPlayer->GetBoneByID(head) + Vector3(0, 1.15, 0))).Normalized();
	}
	else {
		playerDir = (Prediction(TargetPlayer) - LocalPlayer->GetBoneByID(head)).Normalized();
	}
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
	if (!baseplayah) return;
	typedef void(__stdcall* set_rayleigh)(float);
	typedef void(__stdcall* set_grassdist)(float);
	typedef void(__stdcall* OnLand)(BasePlayer*, float);
	if (Misc::Rayleigh) {
		((set_rayleigh)(Storage::gBase + CO::set_rayleigh))(Misc::RayleighAmount);
	}
	else {
		((set_rayleigh)(Storage::gBase + CO::set_rayleigh))(1.f);
	}
	if (Misc::Suicide) {
		((OnLand)(Storage::gBase + CO::OnLand))(LocalPlayer, -50);
	}
	if (Misc::RemoveGrass) {
		((set_grassdist)(Storage::gBase + CO::set_grassDistance))(0.f);
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
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Water, !Misc::Jesus);
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Tree, Misc::IgnoreCollision);
	il2cpp::unity::IgnoreLayerCollision(layer::PlayerMovement, layer::AI, Misc::IgnoreCollision);
	WeaponPatch();
	MiscFuncs();
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (Misc::Flyhack) LocalPlayer->AddFlag(ModelStateFlag::OnLadder);
	if (Misc::SilentWalk) LocalPlayer->RemoveFlag(ModelStateFlag::OnGround);
}
void __fastcall DoHitNotify(DWORD64 basecombatentity, DWORD64 hitinfo) {
	if (Misc::CustomHitsound) { PlaySoundA(xorstr("C:\\plusminus\\hit.wav"), NULL, SND_ASYNC); }
	else { return original_dohitnotify(basecombatentity, hitinfo); }
}
bool __fastcall get_isHeadshot(DWORD64 hitinfo) {
	if (Misc::CustomHitsound) { return false; }
	else { return original_getisheadshot(hitinfo); }
}
void __fastcall ForcePositionTo(BasePlayer* pl, Vector3 pos) {
	if (GetAsyncKeyState(Keys::forcepos)) { }
	else { return original_forcepos(pl, pos); }
}
bool __fastcall CanHoldItems(void* a1, void* a2) {
	if (Weapons::canHoldItems) return true;
	return original_canholditems(a1, a2);
}
void __fastcall VendingSound(uintptr_t a1, uintptr_t a2) {
	return;
}
void __fastcall VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
	if (PlayerEsp::chams) {
		return original_UnregisterFromVisibility(pl, 2.f, true);
	}
	else {
		return original_UnregisterFromVisibility(pl, dist, vis);
	}
}
inline void __fastcall SendProjectileAttack(void* a1, void* a2) {
	uintptr_t PlayerAttack = read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	uintptr_t Attack = read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
	if (Weapons::SpoofHitDistance) {
		write(a2 + 0x2C, Weapons::HitDistance, float);
	}
	if (Combat::HitboxOverride || Combat::AlwaysHeliHotspot) {
		if (Combat::HitboxOverride) {
			uint32_t bone;
			if (rand() % 100 < Combat::HeadshotPercentage) { bone = utils::StringPool::Get(Str(xorstr(L"head"))); }
			else { bone = utils::StringPool::Get(Str(xorstr(L"spine4"))); } 
			write(Attack + 0x30, bone, uint32_t); // public uint hitBone;
			write(Attack + 0x64, 16144115, uint32_t); // public uint hitPartID;
		}
		else {
			if (Combat::AlwaysHeliHotspot) {
				int health = (int)ceil(read(Storage::closestHeli + 0x20C, float));
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
	if (Misc::omniSprint) wantsRun = true;
	return original_handleRunning(a1, a2, wantsRun);
}
void __fastcall HandleJumping(void* a1, void* a2, bool wantsJump, bool jumpInDirection = false) { // recreated
	if (Misc::InfiniteJump) {
		if (!wantsJump) {
			return;
		}
		typedef void(__stdcall* Jump)(void*, void*, bool);
		((Jump)(Storage::gBase + 0x6CDFA0))(a1, a2, jumpInDirection);
	}
	else {
		return original_handleJumping(a1, a2, wantsJump, jumpInDirection);
	}
}
Vector3 __fastcall get_position(DWORD64 playereyes) {
	if (Misc::LongNeck) {
		if (GetAsyncKeyState(Keys::neck)) {
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
	//HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + 0x2B0440), (void**)&original_domovement, DoMovement);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::TraceAll), (void**)&original_traceall, TraceAll);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Launch), (void**)&original_launch, Launch);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::LateUpdate), (void**)&original_lateupdate, LateUpdate);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ClientInput), (void**)&original_clientinput, ClientInput);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHitNotify), (void**)&original_dohitnotify, DoHitNotify);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_isHeadshot), (void**)&original_getisheadshot, get_isHeadshot);
	HookFunction((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ForceToPos), (void**)&original_forcepos, ForcePositionTo);
}