typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

typedef bool(__fastcall* dohit)(Projectile*, uintptr_t, Vector3, Vector3);
inline dohit original_dohit;

typedef bool(__fastcall* dohitt)(Projectile*, HitTest*, Vector3, Vector3);
inline dohitt original_dohitt;

typedef void(__fastcall* domovement)(Projectile*, float);
inline domovement original_domovement;

void __fastcall Launch(Projectile* prdoj) {
	Weapon tar = LocalPlayer->GetActiveWeapon()->Info();
	int ammo = LocalPlayer->GetActiveWeapon()->LoadedAmmo();
	prdoj->gravityModifier(GetGravity(ammo));
	prdoj->invisible(false);
	/*float shpeed = GetBulletSpeed(tar, ammo);
	if (!shpeed) shpeed = 250.f;
	if (Weapons::FastBullet) {
		prdoj->mod()->projectileVelocity(shpeed * 1.3);
	}
	else {
		prdoj->mod()->projectileVelocity(shpeed);
	}*/
	printf("%f\n", prdoj->mod()->projectileVelocity());
	if (Weapons::AntiSpread) {
		prdoj->mod()->projectileVelocitySpread(0.f);
	}
	return original_launch(prdoj);
}
void __fastcall DoMovement(Projectile* proj, float delta) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	if (Combat::magicbollet && utils::LineOfSight(TargetPlayer->GetBoneByID(head), proj->currentPosition()) && Storage::closestPlayer != null) {
		proj->currentVelocity((TargetPlayer->GetBoneByID(head) - proj->currentPosition()) * 250.f);
	}
	return original_domovement(proj, delta);
}
bool __fastcall DoHit(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
	uintptr_t gameobject = read(test + 0x70, uintptr_t);
	uintptr_t getgameobject = read(gameobject + 0x10, uintptr_t);
	layer layerr = read(getgameobject + 0x50, layer);

	auto hitent = test->HitEntity();
	if (layerr == layer::Player_Server) {
		if (LocalPlayer->IsTeamMate(hitent->GetSteamID())) {
			write(test + 0x80, hitent, BasePlayer*);
		}
	}
	return original_dohitt(proj, test, point, norm);
}
typedef float(__fastcall* ValueS)(uint32_t);
bool __fastcall DoRicochet(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	Vector3 hitPosition = proj->currentPosition();
	Vector3 inVelocity = proj->currentVelocity();
	bool flag = false;
	uint32_t num = (uint32_t)proj->seed();
	if (test->HitEntity() == null && proj->ricochetChance() > 0.f && ((ValueS)(Storage::gBase + 0x1864350))(num) <= (uint32_t)proj->ricochetChance()) {
		flag = true;
	}
	if (flag) {
		typedef DWORD64(__stdcall* PoolGet)(DWORD64);
		DWORD64 _ricochet = read(Storage::gBase + 0x29A0CA0, DWORD64);
		DWORD64 projectileRicochet = ((PoolGet)(Storage::gBase + 0x8F39B0))(_ricochet);
		DWORD64 rpcricho = read(Storage::gBase + 0x29CC478, DWORD64);
		write(projectileRicochet + 0x14, proj->projectileID(), int);
		write(projectileRicochet + 0x18, hitPosition, Vector3);
		write(projectileRicochet + 0x24, inVelocity, Vector3);
		write(projectileRicochet + 0x30, (TargetPlayer->GetBoneByID(head) - LocalPlayer->GetBoneByID(head)) * 250.f, Vector3);
		write(projectileRicochet + 0x3C, norm, Vector3);
		write(projectileRicochet + 0x48, proj->traveledTime(), float);
		typedef void(__stdcall* RPC)(DWORD64, Str, DWORD64, DWORD64);
		((RPC)read(rpcricho, DWORD64))((DWORD64)proj, Str(xorstr(L"OnProjectileRicochet")), projectileRicochet, rpcricho);
		proj->sentPosition(proj->currentPosition());
	}
	proj->seed(num);
	return flag;
}