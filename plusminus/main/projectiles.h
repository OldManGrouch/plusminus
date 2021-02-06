typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch;

typedef bool(__fastcall* dohit)(Projectile*, HitTest*, Vector3, Vector3);
inline dohit original_dohit;

typedef void(__fastcall* domovement)(Projectile*, float);
inline domovement original_domovement;

void __fastcall Launch(Projectile* prdoj) {
	Weapon tar = LocalPlayer->GetActiveWeapon()->Info();
	int ammo = LocalPlayer->GetActiveWeapon()->LoadedAmmo();
	prdoj->gravityModifier(GetGravity(ammo));
	prdoj->invisible(false);
	if (vars::weapons::no_spread) {
		write(prdoj->mod() + 0x38, 0.f, float);
	}
	return original_launch(prdoj);
}
typedef float(__stdcall* Clamp01)(float);
typedef bool(__stdcall* IsWaterMaterial)(Str*);
typedef uintptr_t(__stdcall* PoolGetPlayerProjectileAttack)();
typedef void(__stdcall* SendProjectileAttackC)(BasePlayer*, uintptr_t);
typedef uintptr_t(__stdcall* PoolGetPlayerAttack)();
bool __fastcall DoHit(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);

	if (vars::stuff::testBool) {
		bool result = false;
		uint32_t num = proj->seed();

		uintptr_t playerProjectileAttack = ((PoolGetPlayerProjectileAttack)(vars::stor::gBase + 0x2F9FF10))();
		write(playerProjectileAttack + 0x18, ((PoolGetPlayerAttack)(vars::stor::gBase + 0x2FA01C0))(), uintptr_t); // playerAttack
		write(read(playerProjectileAttack + 0x18, uintptr_t) + 0x18, test->BuildAttackMessage(), uintptr_t); // playerAttack->attack
		write(read(playerProjectileAttack + 0x18, uintptr_t) + 0x20, proj->projectileID(), uintptr_t); // playerAttack->projectileID
		if (test->HitEntity() == null && ((IsWaterMaterial)(vars::stor::gBase + 0x539F90))(test->HitMaterial()) && vars::stor::closestPlayer != null) {
			proj->currentVelocity((TargetPlayer->get_bone_pos(head) - proj->currentPosition()) * 10.f);
			proj->currentPosition(proj->currentPosition() + (proj->currentVelocity().Normalized() * 0.001f));
			proj->integrity(((Clamp01)(vars::stor::gBase + 0x1743C40))(proj->integrity() - 0.1f));
			result = true;
		}
		if (LocalPlayer && proj->owner() == LocalPlayer) {
			write(playerProjectileAttack + 0x20, proj->currentVelocity(), Vector3); // playerAttack
			write(playerProjectileAttack + 0x2C, proj->traveledDistance(), float); // playerAttack
			write(playerProjectileAttack + 0x30, proj->traveledTime(), float); // playerAttack
			((SendProjectileAttackC)(vars::stor::gBase + CO::SendProjectileAttack))(proj->owner(), playerProjectileAttack);
			proj->sentPosition(proj->currentPosition());
		}
		return result;
	}
	else {
		return original_dohit(proj, test, point, norm);
	}
}