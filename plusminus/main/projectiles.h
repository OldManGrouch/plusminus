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
	if (vars::weapons::no_spread) {
		prdoj->mod()->projectileVelocitySpread(0.f);
	}
	return original_launch(prdoj);
}
float count = 0.f;
void __fastcall DoMovement(Projectile* proj, float delta) {
	HitTest* hitTest = proj->hitTest();
	typedef bool(__stdcall* DoHitCall)(Projectile*, HitTest*, Vector3, Vector3);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	if (vars::combat::magicbollet && Math::Calc3D_Dist(proj->currentPosition(), TargetPlayer->GetBoneByID(head)) <= 5.f && vars::stor::closestPlayer != null) {
		DWORD64 _spa = read(vars::stor::gBase + 0x29A0CE0, DWORD64);
		DWORD64 rpc_send = read(vars::stor::gBase + 0x29CC4B0, DWORD64);
		typedef DWORD64(__stdcall* PoolGet)(DWORD64);
		DWORD64 projectileAttack = ((PoolGet)(vars::stor::gBase + 0x8F39B0))(_spa);
		write(projectileAttack + 0x20, proj->currentVelocity(), Vector3);
		write(projectileAttack + 0x2C, proj->traveledDistance(), float);
		write(projectileAttack + 0x30, proj->traveledTime(), float);
		typedef void(__stdcall* SendProjectileAttack)(BasePlayer*, DWORD64);
		if (count <= 50.f) {
			printf("called thurererer");
			((SendProjectileAttack)(vars::stor::gBase + CO::SendProjectileAttack))(LocalPlayer, projectileAttack);
			count += 1.f;
		}
		else {
			Str bone = Str(xorstr(L"head"));
			DWORD64 hitTransform = utils::FindBone((DWORD64)TargetPlayer, bone);
			Vector3 hitPoint = utils::TransformToPoint(hitTransform, proj->currentPosition());
			write(hitTest + 0x66, true, bool);
			write(hitTest + 0x88, (DWORD64)TargetPlayer, DWORD64);
			write(hitTest + 0xB0, hitTransform, DWORD64);
			write(hitTest + 0x90, hitPoint, Vector3);
			write(hitTest + 0x9C, hitPoint, Vector3);
			if (vars::stor::closestPlayer != NULL && utils::LineOfSight(TargetPlayer->GetBoneByID(head), proj->currentPosition())) {
				((DoHitCall)(vars::stor::gBase + CO::DoHit))(proj, hitTest, proj->currentPosition(), proj->currentPosition());
				count = 0.f;
			}
		}
	}
	return original_domovement(proj, delta);
}
bool __fastcall DoHit(Projectile* proj, HitTest* test, Vector3 point, Vector3 norm) {
	if (test->HitEntity() != null) {
		if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(test->HitEntity()->GetSteamID())) {
			return false;
		}
	}
	return original_dohitt(proj, test, point, norm);
}