typedef void(__fastcall* domovement)(Projectile*, float);
inline domovement original_domovement;

typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

typedef void(__fastcall* water)(Projectile*, Vector3);
inline water original_iswater;

typedef bool(__fastcall* dohgit)(Projectile*, uintptr_t, Vector3, Vector3);
inline dohgit original_dohit;

void __fastcall Launch(Projectile* proj) {
	uintptr_t mod = proj->mod();
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	float shpeed = GetBulletSpeed(tar, ammo);
	if (!shpeed) shpeed = 250.f;
	if (Weapons::FastBullet) {
		write(mod + 0x34, shpeed * 1.3, float);
	}
	else {
		write(mod + 0x34, shpeed, float);
	}
	return original_launch(proj);
}
typedef float(__stdcall* get_fixedDeltaTime)();
void __fastcall DoMovement(Projectile* skrrt, float deltaTime) { // RIP - 2021/01/09 (?)
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	uintptr_t hitTest = skrrt->hitTest();
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	float shpeed = GetBulletSpeed(active->Info(), active->LoadedAmmo());
	if (!shpeed) shpeed = 250.f;
	if (Combat::MagicBullet && Storage::closestPlayer != null && utils::LineOfSight(skrrt->currentPosition(), TargetPlayer->GetBoneByID(head))) {
		if (skrrt->traveledDistance() >= Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), TargetPlayer->GetBoneByID(head)) / 3) {
			skrrt->currentVelocity((TargetPlayer->GetBoneByID(head) - skrrt->currentPosition()) * shpeed);
		}
	}
	if (Combat::HeliMagicBullet && Storage::closestHeli != null && utils::LineOfSight(skrrt->currentPosition(), read(Storage::closestHeliObj + 0x90, Vector3))) {
		if (skrrt->traveledDistance() >= 150) {
			skrrt->currentVelocity((read(Storage::closestHeliObj + 0x90, Vector3) - skrrt->currentPosition()) * shpeed);
		}
	}
	return original_domovement(skrrt, deltaTime);
}
bool __fastcall DoHitS(Projectile* proj, uintptr_t test, Vector3 point, Vector3 norm) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	if (!oPlayerList) {
		DWORD64 val = read(Storage::gBase + CO::BasePlayer, DWORD64);
		DWORD64 st = read(val + 0xB8, DWORD64);
		oPlayerList = read(st + 0x8, DWORD64);
	}
	UINT64 ClientEntities_values = read(oPlayerList + 0x28, UINT64);
	if (!ClientEntities_values) return false;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	UINT64 EntityBuffer = read(ClientEntities_values + 0x18, UINT64);
	for (int i = 0; i <= EntityCount; i++) {
		BasePlayer* Player = (BasePlayer*)read(EntityBuffer + 0x20 + (i * 0x8), UINT64);
		if (read(test + 0x88, uintptr_t) == (uintptr_t)Player && Combat::silentAim) {
			Str bone = Str(xorstr(L"head"));
			DWORD64 hitTransform = utils::FindBone((DWORD64)TargetPlayer, bone);
			Vector3 hitPoint = utils::TransformToPoint(hitTransform, proj->currentPosition());
			write(test + 0x66, true, bool);
			write(test + 0x88, (DWORD64)TargetPlayer, DWORD64);
			write(test + 0xB0, hitTransform, DWORD64);
			write(test + 0x90, hitPoint, Vector3);
			write(test + 0x9C, hitPoint, Vector3);
		}
	}
	return original_dohit(proj, test, point, norm);
} 