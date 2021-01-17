typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

typedef bool(__fastcall* dohit)(Projectile*, uintptr_t, Vector3, Vector3);
inline dohit original_dohit;

typedef void(__fastcall* domovement)(Projectile*, float);
inline domovement original_domovement;

typedef float(__fastcall* RustPause)(float);
void __fastcall Launch(Projectile* prdoj) {

	uintptr_t mod = prdoj->mod();
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	float shpeed = GetBulletSpeed(tar, ammo);
	write(prdoj + 0x28, GetGravity(ammo), float);
	write(prdoj + 0x114, false, bool);
	if (!shpeed) shpeed = 250.f;
	if (Weapons::FastBullet) {
		write(mod + 0x34, shpeed * 1.3, float);
	}
	else {
		write(mod + 0x34, shpeed, float);
	}
	((RustPause)(Storage::gBase + 0x434D70))(Global::testFloat);
	return original_launch(prdoj);
}
typedef float(__fastcall* ValueS)(uint32_t);
bool __fastcall DoHit(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
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
		write(projectileRicochet + 0x30, (TargetPlayer->GetBoneByID(head) - LocalPlayer->GetBoneByID(head)) * Global::testFloat, Vector3);
		write(projectileRicochet + 0x3C, norm, Vector3);
		write(projectileRicochet + 0x48, proj->traveledTime(), float);
		typedef void(__stdcall* RPC)(DWORD64, Str, DWORD64, DWORD64);
		((RPC)read(rpcricho, DWORD64))((DWORD64)proj, Str(xorstr(L"OnProjectileRicochet")), projectileRicochet, rpcricho);
		//proj->sentPosition(proj->currentPosition());
	}
	proj->seed(num);
	return flag;
}