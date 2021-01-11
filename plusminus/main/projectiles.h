typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

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