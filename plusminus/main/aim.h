#include <map>
float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(Global::ScreenWidth / 2, Global::ScreenHigh / 2), ScreenPos);
}
float GetFovHeli(Vector3 pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(pos, ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(Global::ScreenWidth / 2, Global::ScreenHigh / 2), ScreenPos);
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
	/*DWORD64 itemmod = read(Storage::gBase + 0x299C300, DWORD64);
	if (!itemmod) printf("itemmod == null\n"); return;
	DWORD64 primMag = read(Heldd + 0x2A0, DWORD64);
	DWORD64 type = read(primMag + 0x20, DWORD64);
	typedef DWORD64(__stdcall* GetComponent)(DWORD64, DWORD64);
	DWORD64 itemmodprojectile = ((GetComponent)(Storage::gBase + 0x7FCAB0))(type, itemmod);
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
	Vector3 TargetedHeli = read(Storage::closestHeliObj + 0x90, Vector3) + Vector3(0, 2, 0);
	float Dist = Math::Calc3D_Dist(LP_Pos, TargetedHeli);
	if (Dist > 0.001f) {
		Weapon tar = active->Info();
		int ammo = active->LoadedAmmo();
		float speed;
		if (Weapons::FastBullet) {
			speed = GetBulletSpeed(tar, ammo) * 1.4;
		}
		else {
			speed = GetBulletSpeed(tar, ammo);
		}
		if (!speed && !Weapons::FastBullet) {
			speed = 250.f;
		}
		else if (!speed && Weapons::FastBullet) {
			speed = 250.f * 1.3;
		}
		float gravity = GetGravity(ammo);
		float BulletTime = Dist / speed;
		Vector3 vel;
		if (Storage::closestHeli != NULL) {
			vel = utils::GetWorldVelocity(Storage::closestHeli);
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
	if (Misc::LongNeck && GetAsyncKeyState(Keys::neck)) { Local = LocalPlayer->GetBoneByID(head) + Vector3(0, 1.15, 0); }
	else { Local = LocalPlayer->GetBoneByID(head); }
	float Dist = Math::Calc3D_Dist(Local, BonePos);
	if (Dist > 0.001f) {
		float speed;
		if (Weapons::FastBullet) {
			speed = GetBulletSpeed(tar, ammo) * 1.4;
		}
		else {
			speed = GetBulletSpeed(tar, ammo);
		}
		if (!speed && !Weapons::FastBullet) {
			speed = 250.f;
		}
		else if (!speed && Weapons::FastBullet) {
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
void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}
void GoToTarget(BasePlayer* player) {
	Vector3 Local;
	if (Misc::LongNeck && GetAsyncKeyState(Keys::neck)) { Local = LocalPlayer->GetBoneByID(neck) + Vector3(0, 1.15, 0); }
	else { Local = LocalPlayer->GetBoneByID(neck); }
	Vector3 PlayerPos = Prediction(player);
	Vector2 Offset = Math::CalcAngle(Local, PlayerPos) - LocalPlayer->GetVA();
	Normalize(Offset.y, Offset.x);
	if (Combat::Smooth) {
		Offset.x /= Combat::Smoothing;
		Offset.y /= Combat::Smoothing;
	}
	Vector2 AngleToAim = LocalPlayer->GetVA() + Offset;
	Normalize(AngleToAim.y, AngleToAim.x);
	LocalPlayer->SetVA(AngleToAim);
}

void Aim(BasePlayer* AimEntity) {
	if (Combat::Activate && !LocalPlayer->IsTeamMate(AimEntity->GetSteamID())) {
		if (AimEntity && !LocalPlayer->IsMenu()) {
			if (GetAsyncKeyState(Keys::aimKey)) GoToTarget(AimEntity);
		}
	}
}