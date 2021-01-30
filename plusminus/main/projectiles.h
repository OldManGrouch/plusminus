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
	if (vars::stuff::debugtab) {
		LogSystem::Log(StringFormat::format(c_wxor(L"bs: %.2f"), read(prdoj->mod() + 0x34, float)), 5.f);
	}
	if (vars::weapons::no_spread) {
		write(prdoj->mod() + 0x38, 0.f, float);
	}
	return original_launch(prdoj);
}
bool __fastcall DoHit(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
	if (test->HitEntity() != null) {
		if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(test->HitEntity()->GetSteamID())) {
			return false;
		}
	}
	return original_dohitt(proj, test, point, norm);
}