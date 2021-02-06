#include "hooks/defs.h"
int yeet = 0;
int flick = 0;
int yaw = 100;
bool waslagging = false;
void SendClientTick(BasePlayer* baseplayer) {
	if (!LocalPlayer) return original_sendclienttick(baseplayer);
	if (vars::misc::anti_aim) {
		auto input = read(baseplayer + 0x4C8, uintptr_t);
		auto state = read(input + 0x20, uintptr_t);
		auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
		yeet += vars::misc::anti_aim_speed;
		if (yeet > 999) { // reset number
			yeet = 0;
		}

		if (vars::misc::anti_aim_yaw == 0) {
			yaw = 100;
		}
		if (vars::misc::anti_aim_yaw == 1) {
			yaw = -100;
		}
		write(current + 0x18, Vector3(yaw, yeet, 0), Vector3);
	}
	return original_sendclienttick(baseplayer);
}
Projectile* CreateProjectile(uintptr_t BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
	Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);
	if (vars::weapons::thick_bullet) {
		projectile->thickness(1.f);
	}
	else {
		projectile->thickness(0.1f);
	}
	return projectile;
}
bool CanAttack(void* a1, void* a2) {
	if (vars::misc::can_attack) return true;
	return original_canattack(a1, a2);
}

void UpdateAmbient(uintptr_t TOD_Sky) {
	if (!vars::misc::bright_ambient) {
		return original_updateambient(TOD_Sky);
	}
	//static int cases = 0;
	//static float r = 1.00f, g = 0.00f, b = 1.00f;
	//switch (cases) {
	//case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
	//case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
	//case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }                       // RAINBOW
	//case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
	//default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	//}
	RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
	RenderSettings::set_ambientIntensity(3.f);
	RenderSettings::set_ambientLight(Color({ vars::colors::ambient_color.x, vars::colors::ambient_color.y, vars::colors::ambient_color.z, 1 }));
}
void TraceAll(HitTest* test, uintptr_t traces, uintptr_t layerMask) {
	if (vars::weapons::penetrate) {
		layerMask &= ~LayerMasks::Tree;
		layerMask &= ~LayerMasks::Deployed;
		layerMask &= ~LayerMasks::Water;
	}
	if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(reinterpret_cast<BasePlayer*>(test->HitEntity())->GetSteamID())) {
		layerMask &= ~LayerMasks::Player_Server;
		layerMask &= ~LayerMasks::Player_Model_Rendering;                                           // why no work ?
		layerMask &= ~LayerMasks::Player_Movement;
		layerMask &= ~LayerMasks::AI;
	}
	return original_traceall(test, traces, layerMask); 
}
pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
	if (options->IsFromServer()) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find(xorstr(L"noclip")) != std::wstring::npos || cmd.find(xorstr(L"debugcamera")) != std::wstring::npos || cmd.find(xorstr(L"camspeed")) != std::wstring::npos || cmd.find(xorstr(L"admintime")) != std::wstring::npos) {
			strCommand = nullptr;
		}
	}
	return original_consolerun(options, strCommand, args);
}
Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	Vector3 heliDir = (HeliPrediction(LocalPlayer->get_bone_pos(head)) - LocalPlayer->get_bone_pos(head)).Normalized();
	Vector3 playerDir;
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) {
		playerDir = (Prediction(TargetPlayer) - (LocalPlayer->get_bone_pos(head) + Vector3(0, 1.15, 0))).Normalized();
	}
	else {
		playerDir = (Prediction(TargetPlayer) - LocalPlayer->get_bone_pos(head)).Normalized();
	}
	if (vars::combat::psilent) {
		if (!vars::combat::psilentonkey) {
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

void ClientInput(BasePlayer* baseplayah, DWORD64 ModelState) {
	typedef void(__stdcall* OnLand)(BasePlayer*, float);
	typedef void(__stdcall* DoAttack)(uintptr_t);
	typedef void(__stdcall* set_rayleigh)(float);
	if (vars::misc::rayleigh_changer) {
		((set_rayleigh)(vars::stor::gBase + CO::set_rayleigh))(vars::misc::rayleigh);
	}
	else {
		((set_rayleigh)(vars::stor::gBase + CO::set_rayleigh))(vars::misc::rayleigh);
	}
	if (vars::misc::mass_suicide)
		((OnLand)(vars::stor::gBase + CO::OnLand))(LocalPlayer, -50);
	if (vars::misc::suicide && GetAsyncKeyState(vars::keys::suicide) && LocalPlayer->GetHealth() > 0 && !LocalPlayer->IsMenu())
		((OnLand)(vars::stor::gBase + CO::OnLand))(LocalPlayer, -50);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	if (vars::combat::psilent_autoshoot && vars::stor::closestPlayer != null && vars::combat::psilent && !LocalPlayer->IsMenu()) {
		Item* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 basepr = read(weapon + oHeldEntity, DWORD64);
		DWORD64 mag = read(basepr + 0x2A0, DWORD64);
		int contents = read(mag + 0x1C, int);
		if (contents > 0 && utils::LineOfSight(TargetPlayer->get_bone_pos(head), (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) ? LocalPlayer->get_bone_pos(head) + Vector3(0, 1.15, 0) : LocalPlayer->get_bone_pos(head))) {
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
	typedef void(__stdcall* ClientInput)(BasePlayer*, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (vars::misc::spoof_ladderstate) LocalPlayer->AddFlag(ModelStateFlag::OnLadder);
	if (vars::misc::silent_walk) LocalPlayer->RemoveFlag(ModelStateFlag::OnGround);
}
typedef float(__stdcall* Total)(DWORD64);
typedef int(__stdcall* get_frameCount)();
void DoHitNotify(BaseCombatEntity* entity, HitInfo* info) {
	if (vars::misc::hit_logs) {
		if (entity->IsPlayer()) {
			LogSystem::Log(StringFormat::format(c_wxor(L"Hit %s for %.2f damage"), reinterpret_cast<BasePlayer*>(entity)->GetName(), info->damageTypes()->Total()), 5.f);
		}
	}
	if (vars::misc::custom_hitsound) {
		if (entity->IsPlayer()) {
			PlaySoundA(xorstr("C:\\plusminus\\hit.wav"), NULL, SND_ASYNC);
		}
	}
	else {
		return original_dohitnotify(entity, info);
	}
}
bool get_isHeadshot(DWORD64 hitinfo) {
	if (vars::misc::custom_hitsound) { return false; }
	else { return original_getisheadshot(hitinfo); }
}
void ForcePositionTo(BasePlayer* pl, Vector3 pos) {
	if (GetAsyncKeyState(vars::keys::forcepos)) {}
	else { return original_forcepos(pl, pos); }
}
bool CanHoldItems(void* a1, void* a2) {
	if (vars::weapons::minicopter_aim) return true;
	return original_canholditems(a1, a2);
}
void VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
	if (vars::players::chams) {
		return original_UnregisterFromVisibility(pl, 2.f, true);
	}
	else {
		return original_UnregisterFromVisibility(pl, dist, vis);
	}
}
void SendProjectileAttack(void* a1, void* a2) {
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
std::string C4 = c_xor("C4");
std::string Satchel = c_xor("Satchel");
std::string IncenRocket = c_xor("Incendiary Rocket");
std::string Rocket = c_xor("Rocket");

std::wstring wC4 = xorstr(L"C4");
std::wstring wSatchel = xorstr(L"Satchel");
std::wstring wIncenRocket = xorstr(L"Incendiary Rocket");
std::wstring wRocket = xorstr(L"Rocket");
uintptr_t CreateEffect(pUncStr strPrefab, uintptr_t effect) {
	auto effectName = strPrefab->str;
	auto position = read(effect + 0x5C, Vector3);
	if (vars::visuals::raid_esp && effect && strPrefab->str) {
		switch (RUNTIME_CRC32_W(effectName)) {
		case STATIC_CRC32("assets/prefabs/tools/c4/effects/c4_explosion.prefab"):
			LogSystem::LogExplosion(C4, position);
			LogSystem::Log(StringFormat::format(c_wxor(L"%ls explosion %.2f meters away from you."), wC4.c_str(), Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), position)), 15.f);
			break;
		case STATIC_CRC32("assets/prefabs/weapons/satchelcharge/effects/satchel-charge-explosion.prefab"):
			LogSystem::LogExplosion(Satchel, position);
			LogSystem::Log(StringFormat::format(c_wxor(L"%ls explosion %.2f meters away from you."), wSatchel.c_str(), Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), position)), 15.f);
			break;
		case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion_incendiary.prefab"):
			LogSystem::LogExplosion(IncenRocket, position);
			LogSystem::Log(StringFormat::format(c_wxor(L"%ls explosion %.2f meters away from you."), wIncenRocket.c_str(), Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), position)), 15.f);
			break;
		case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"):
			LogSystem::LogExplosion(Rocket, position);
			LogSystem::Log(StringFormat::format(c_wxor(L"l%s explosion %.2f meters away from you."), wRocket.c_str(), Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), position)), 15.f);
			break;
		}
	}
	return original_createeffect(strPrefab, effect);
}
float GetRandomVelocity(uintptr_t mod) {
	if (vars::stuff::debugtab) {
		//LogSystem::Log(StringFormat::format(c_wxor(L"wep:%d ammo:%d | %.2f"), LocalPlayer->GetActiveWeapon()->GetID(), LocalPlayer->GetActiveWeapon()->LoadedAmmo(), original_getrandomvelocity(mod)), 5.f);
	}
	//LogSystem::Log(StringFormat::format(c_wxor(L"%.2f"), original_getrandomvelocity(mod)), 5.f);
	return vars::weapons::fast_bullets ? original_getrandomvelocity(mod) * 1.3 : original_getrandomvelocity(mod);
}
void AddPunch(uintptr_t a1, Vector3 a2, float duration) {
	if (vars::weapons::no_recoil) {
		a2 *= vars::weapons::recoil_control / 100.f;
	}
	return original_addpunch(a1, a2, duration);
}
Vector2 GetPitchClamp(DWORD64 basemountable) {
	if (vars::misc::unlock_angles) {
		return Vector2(9999, 9999);
	}
	else {
		return original_getpitchclamp(basemountable);
	}
}
Vector2 GetYawClamp(DWORD64 basemountable) {
	if (vars::misc::unlock_angles) {
		return Vector2(9999, 9999);
	}
	else {
		return original_getpitchclamp(basemountable);
	}
}
Vector3 MoveTowards(Vector3 a1, Vector3 a2, float maxDelta) {
	static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
	if (CALLED_BY(ptr, 0x800)) {
		if (vars::weapons::no_recoil) {
			a2 *= vars::weapons::recoil_control / 100.f;
			maxDelta *= vars::weapons::recoil_control / 100.f;
		}
	}
	return original_movetowards(a1, a2, maxDelta);
}
void HandleRunning(void* a1, void* a2, bool wantsRun) {
	if (vars::misc::omnidirectional_sprinting) wantsRun = true;
	return original_handleRunning(a1, a2, wantsRun);
}
void HandleJumping(void* a1, void* a2, bool wantsJump, bool jumpInDirection = false) { // recreated
	if (vars::misc::inf_jump) {
		if (!wantsJump) {
			return;
		}
		typedef void(__stdcall* Jump)(void*, void*, bool);
		((Jump)(vars::stor::gBase + CO::Jump))(a1, a2, jumpInDirection);
	}
	else {
		return original_handleJumping(a1, a2, wantsJump, jumpInDirection);
	}
}
void Play(DWORD64 viewmodel, pUncStr name) {
	if (vars::weapons::remove_attack_anim) {
		static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
		if (!CALLED_BY(ptr, 0x800) || LocalPlayer->GetActiveWeapon()->GetID() == -75944661) {
			return original_viewmodelplay(viewmodel, name);
		}
	}
	else {
		return original_viewmodelplay(viewmodel, name);
	}
}
Vector3 get_position(DWORD64 playereyes) {
	if (vars::misc::long_neck) {
		if (GetAsyncKeyState(vars::keys::longneck)) {
			return Vector3(LocalPlayer->get_bone_pos(head)) + Vector3(0, 1.15, 0);
		}
	}
	return original_geteyepos(playereyes);
}
void __fastcall SetFlying(void* a1, bool a2) {}

void hk_(void* Function, void** Original, void* Detour, bool autoEnable = true) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) { std::cout << (xorstr("Failed to initialize MinHook")) << std::endl; return; }
	MH_CreateHook(Function, Detour, Original);
	if (autoEnable)
		MH_EnableHook(Function);
}
inline void InitHook() {
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::set_flying), (void**)&original_setflying, SetFlying);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::SendProjectileAttack), (void**)&original_sendprojectileattack, SendProjectileAttack);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CanAttack), (void**)&original_canattack, CanAttack);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::SendClientTick), (void**)&original_sendclienttick, SendClientTick);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::HandleRunning), (void**)&original_handleRunning, HandleRunning);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::HandleJumping), (void**)&original_handleJumping, HandleJumping);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, GetModifiedAimConeDirection);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CreateProjectile), (void**)&original_create_projectile, CreateProjectile);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CanHoldItems), (void**)&original_canholditems, CanHoldItems);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Run), (void**)&original_consolerun, Run);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::CreateEffect), (void**)&original_createeffect, CreateEffect);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_position), (void**)&original_geteyepos, get_position);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Play), (void**)&original_viewmodelplay, Play);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetPitchClamp), (void**)&original_getpitchclamp, GetPitchClamp);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetYawClamp), (void**)&original_getyawclamp, GetYawClamp);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::VisUpdateUsingCulling), (void**)&original_UnregisterFromVisibility, VisUpdateUsingCulling);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::TraceAll), (void**)&original_traceall, TraceAll);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::GetRandomVelocity), (void**)&original_getrandomvelocity, GetRandomVelocity);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::AddPunch), (void**)&original_addpunch, AddPunch);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::MoveTowards), (void**)&original_movetowards, MoveTowards);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::Launch), (void**)&original_launch, Launch);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::UpdateAmbient), (void**)&original_updateambient, UpdateAmbient);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ClientInput), (void**)&original_clientinput, ClientInput);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::DoHitNotify), (void**)&original_dohitnotify, DoHitNotify);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::get_isHeadshot), (void**)&original_getisheadshot, get_isHeadshot);
	hk_((void*)(uintptr_t)(GetModBase(xorstr(L"GameAssembly.dll")) + CO::ForceToPos), (void**)&original_forcepos, ForcePositionTo);
}