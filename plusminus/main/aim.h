#include <map>
namespace a {
	double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
		double pitch = (Vector3::my_atan2(height, DepthPlayerTarget));
		double BulletVelocityXY = velocity * Vector3::my_cos(pitch);
		double Time = DepthPlayerTarget / BulletVelocityXY;
		double TotalVerticalDrop = (0.4905f * gravity * Time * Time);
		return TotalVerticalDrop * 10;
	}
#define powFFFFFFFFFFFFFFFFFFFFFF(n) (n)*(n)
	void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {
		float Dist = Math::Distance_3D(target, local);
		float BulletTime = Dist / bulletspeed;

		Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;

		Vector3 PredictVel = vel * BulletTime;

		target += PredictVel;

		double height = target.y - local.y;
		Vector3 dir = target - local;
		float DepthPlayerTarget = Vector3::my_sqrt(powFFFFFFFFFFFFFFFFFFFFFF(dir.x) + powFFFFFFFFFFFFFFFFFFFFFF(dir.z));

		float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity);

		target.y += drop;
	}
	Vector3 get_aim_point(float speed, float gravity) {
		Vector3 ret = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head);
		Prediction(LocalPlayer->get_bone_pos(head), ret, reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetVelocity(), speed, gravity);
		return ret;
	}
}
float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->get_bone_pos(Bone), ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
float GetFovHeli(Vector3 pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(pos, ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
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
float GetBulletSpeed() {
	Item* active = LocalPlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * 1.3 : tar.ammo[0].speed; //melee
	for (Ammo am : tar.ammo) {
		for (int id : am.id) {
			if (id == ammo) {
				return vars::weapons::fast_bullets ? am.speed * 1.3 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
			}
		}
		if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * 1.3 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
	}
	return vars::weapons::fast_bullets ? 250.f * 1.3 : 250.f;
}
void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}
void do_aimbot(BasePlayer* player) {
	Vector3 local = LocalPlayer->get_bone_pos(head);
	Vector3 target = player->get_bone_pos(head);
	a::Prediction(local, target, player->GetVelocity(), GetBulletSpeed(), GetGravity(LocalPlayer->GetActiveWeapon()->LoadedAmmo()));
	Vector2 Offset = Math::CalcAngle(local, target) - LocalPlayer->GetVA();
	Normalize(Offset.y, Offset.x);
	Vector2 AngleToAim = LocalPlayer->GetVA() + Offset;
	Normalize(AngleToAim.y, AngleToAim.x);
	LocalPlayer->SetVA(AngleToAim);
}