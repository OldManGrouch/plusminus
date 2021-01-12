typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

typedef bool(__fastcall* dohit)(Projectile*, uintptr_t, Vector3, Vector3);
inline dohit original_dohit;

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
bool __fastcall DoHit(Projectile* proj, uintptr_t test, Vector3 point, Vector3 norm) {
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	float shpeed = GetBulletSpeed(active->Info(), active->LoadedAmmo());
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	if (Storage::closestPlayer != null) {
		proj->currentVelocity((TargetPlayer->GetBoneByID(head) - proj->currentPosition()) * shpeed);
	}
	return original_dohit(proj, test, point, norm);
}