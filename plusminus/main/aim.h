#include <map>
float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
float GetFovHeli(Vector3 pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(pos, ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
// 785728077 -1691396643 51984655
float GetGravity(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.f;
	case -1234735557:
		return 0.75f;
	case 215754713:
		return 0.75f;
	case -1023065463:
		return 0.5f;
	case -2097376851:
		return 0.75f;
	case -1321651331:
		return 1.25f;
	default:
		return 1.f;
	}
}


float GetBulletSpeed(Weapon tar, int ammo)
{
	/*DWORD64 itemmod = read(vars::stor::gBase + 0x299C300, DWORD64);
	if (!itemmod) printf("itemmod == null\n"); return;
	DWORD64 primMag = read(Heldd + 0x2A0, DWORD64);
	DWORD64 type = read(primMag + 0x20, DWORD64);
	typedef DWORD64(__stdcall* GetComponent)(DWORD64, DWORD64);
	DWORD64 itemmodprojectile = ((GetComponent)(vars::stor::gBase + 0x7FCAB0))(type, itemmod);
	if (!itemmodprojectile) printf("itemmodprojectile == null\n"); return;
	float projectileVelocity = read(itemmodprojectile + 0x34, float);
	printf("%s\n", std::to_string(projectileVelocity));*/

	if (ammo == 0) return tar.ammo[0].speed; //melee
	for (Ammo am : tar.ammo) {
		for (int id : am.id) {
			if (id == ammo) {
				return am.speed;
			}
		}
		if (am.id[0] == 0) return am.speed;
	}
	return 250.f;
}
Vector3 HeliPrediction(const Vector3& LP_Pos) {
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	Vector3 TargetedHeli = read(vars::stor::closestHeliObj + 0x90, Vector3) + Vector3(0, 2, 0);
	float Dist = Math::Calc3D_Dist(LP_Pos, TargetedHeli);
	if (Dist > 0.001f) {
		Weapon tar = active->Info();
		int ammo = active->LoadedAmmo();
		float speed;
		if (vars::weapons::fast_bullets) {
			speed = GetBulletSpeed(tar, ammo) * 1.4;
		}
		else {
			speed = GetBulletSpeed(tar, ammo);
		}
		if (!speed && !vars::weapons::fast_bullets) {
			speed = 250.f;
		}
		else if (!speed && vars::weapons::fast_bullets) {
			speed = 250.f * 1.3;
		}
		float gravity = GetGravity(ammo);
		float BulletTime = Dist / speed;
		Vector3 vel;
		if (vars::stor::closestHeli != NULL) {
			vel = utils::GetWorldVelocity(vars::stor::closestHeli);
		}
		else {
			vel = Vector3(0, 0, 0);
		}
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		TargetedHeli += PredictVel;
		TargetedHeli.y += (4.905f * BulletTime * BulletTime) * gravity;
	}
	return TargetedHeli;
}
Vector3 Prediction(BasePlayer* Player) {
	BaseProjectile* active = LocalPlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	Vector3 BonePos = Player->GetBoneByID(head);
	Vector3 Local;
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) { Local = LocalPlayer->GetBoneByID(head) + Vector3(0, 1.15, 0); }
	else { Local = LocalPlayer->GetBoneByID(head); }
	float Dist = Math::Calc3D_Dist(Local, BonePos);
	if (Dist > 0.001f) {
		float speed;
		if (vars::weapons::fast_bullets) {
			speed = GetBulletSpeed(tar, ammo) * 1.4;
		}
		else {
			speed = GetBulletSpeed(tar, ammo);
		}
		if (!speed && !vars::weapons::fast_bullets) {
			speed = 250.f;
		}
		else if (!speed && vars::weapons::fast_bullets) {
			speed = 250.f * 1.3;
		}
		float gravity = GetGravity(ammo);
		float BulletTime = Dist / speed;
		Vector3 vel = Player->GetVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		BonePos += PredictVel;
		BonePos.y += (4.905f * BulletTime * BulletTime) * gravity;
	}
	return BonePos;
}
void Normalize(float& x, float& y) {
	if (x > 180)
		x -= 360;
	else if (x < -180)
		x += 360;

	if (y > 180)
		y -= 360;
	else if (y < -180)
		y += 360;

	if (x < -89)
		x = -89;

	if (x > 89)
		x = 89;

	while (y < -180.0f)
		y += 360.0f;

	while (y > 180.0f)
		y -= 360.0f;
}
void SmoothAngleOld(Vector2 src, Vector2& dst, float factor) {
	Vector2 delta = dst - src;
	Normalize(delta.x, delta.y);
	dst = src + delta / factor;
}
void GoToTarget(BasePlayer* player) {
	Vector3 Local;
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) { Local = LocalPlayer->GetBoneByID(neck) + Vector3(0, 1.15, 0); }
	else { Local = LocalPlayer->GetBoneByID(neck); }
	Vector3 PlayerPos = Prediction(player);
	Vector2 Offset = Math::CalcAngle(Local, PlayerPos);
	Offset -= LocalPlayer->GetVA();
	Normalize(Offset.x, Offset.y);
	SmoothAngleOld(LocalPlayer->GetVA(), Offset, 10);
	auto delta = Offset -= LocalPlayer->GetVA();
	//Offset = LocalPlayer->GetVA() + delta;
	LocalPlayer->SetVA(Offset);
}

void Aim(BasePlayer* AimEntity) {
	if (vars::combat::aimbot && !LocalPlayer->IsTeamMate(AimEntity->GetSteamID())) {
		if (AimEntity && !LocalPlayer->IsMenu()) {
			if (GetAsyncKeyState(vars::keys::aimkey)) GoToTarget(AimEntity);
		}
	}
}