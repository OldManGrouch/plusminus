class Target {
public:
	bool valid;
	BasePlayer* entity;
	Vector3 position;
	float dist = 10000.f;
	float realdist = 0.f;
	float fov = 10000.f;

	bool operator<(const Target& b) {
		if (fov == 10000.f) {
			return this->dist < b.dist;
		}
		else {
			return this->fov < b.fov;
		}
	}

	Target() {
		this->valid = false;
		this->fov = 10000.f;
	}
	Target(Vector3 target) {
		this->valid = false;
		this->position = target;
	}
};

DWORD64 oPlayerList = 0;
float GetFov(Vector2 Pos) {
	return Math::Calc2D_Dist(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), Pos);
}
float GetFov(BasePlayer* Entity) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->GetBoneByID(neck), ScreenPos)) return 1000.f;
	return GetFov(ScreenPos);
}
float GetFov(Vector3 Pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(Pos, ScreenPos)) return 1000.f;
	return GetFov(ScreenPos);
}
Target FindAimTarget(Vector3 from, bool sortByFov, bool silent, float maxdist = vars::combat::range, float silent_traveldist = 0.f, bool visible = false) {
	Target lowest = Target();

	if (!oPlayerList) {
		DWORD64 val = read(vars::stor::gBase + CO::BasePlayer, DWORD64);
		DWORD64 st = read(val + 0xB8, DWORD64);
		oPlayerList = read(st + 0x8, DWORD64);
	}
	UINT64 ClientEntities_values = read(oPlayerList + 0x28, UINT64);
	if (!ClientEntities_values) return lowest;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	UINT64 EntityBuffer = read(ClientEntities_values + 0x18, UINT64);
	for (int i = 0; i <= EntityCount; i++)
	{
		BasePlayer* Player = (BasePlayer*)read(EntityBuffer + 0x20 + (i * 0x8), UINT64);
		if (Player->GetHealth() < 0.2) continue;
		if (vars::combat::ignore_sleepers && Player->HasFlags(16)) continue;
		if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(Player->GetSteamID())) continue;
		if (vars::combat::ignore_npc && Player->IsNpc()) continue;
		if (vars::combat::ignore_players) continue;

		Vector3 pos = Player->GetBoneByID(neck);
		Target res = Target();
		res.valid = true;
		float dst = Math::Calc3D_Dist(from, pos);
		res.realdist = dst;
		dst += silent_traveldist;
		res.dist = dst;
		res.entity = Player;
		res.position = pos;
		if (res < lowest) lowest = res;
	}
	return lowest;
}
Target FindProjectileTarget(Vector3 from, float traveldist) {
	return FindAimTarget(from, false, true, vars::combat::range, traveldist);
}

float MaxMeleeDist(DWORD64 melee, bool localplayer) {
	float pad = 0.1f;
	typedef float(__stdcall* RetF)();
	float time = ((RetF)(vars::stor::gBase + CO::get_time))();

	float desyncTime = max(time - LocalPlayer->Time() - 0.0325f, 0.f);
	float res = pad + desyncTime * 5.5f;
	if (localplayer) {
		res += (1.5f * read(melee + 0x278, float)); //maxDistance
	}
	return max(res, 0.05f);
}
Target TargetMeleeTest(BasePlayer* Player, DWORD64 melee) {
	Target res = Target();

	if (Player->GetHealth() < 0.2) return res;
	if (vars::combat::ignore_npc && Player->IsNpc()) return res;
	if (vars::combat::ignore_sleepers && Player->HasFlags(16)) return res;
	if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(Player->GetSteamID())) return res;
	typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);

	Vector3 prepos = Player->GetBoneByID(BoneList::head/*we dont care about bone*/);

	Vector3 closest_entity = ((CPoint)(vars::stor::gBase + CO::utils::ClosestPoint))(LocalPlayer, prepos);
	Vector3 closest_local = ((CPoint)(vars::stor::gBase + CO::utils::ClosestPoint))(Player, closest_entity);
	float disttoentity = MaxMeleeDist(melee, false);
	float distfromlocal = MaxMeleeDist(melee, true);

	float maxdist = distfromlocal + disttoentity;

	float realdist = (closest_local - closest_entity).Length();

	if (realdist > maxdist) return res;

	Vector3 target;
	if (realdist <= disttoentity) {
		target = closest_entity;
	}
	else {
		Vector3 dir = (closest_entity - closest_local).Normalized();
		target = closest_local + dir * disttoentity;
	}
	res.valid = utils::LineOfSight(closest_local, target);
	if (!res.valid) return res;

	Vector3 lppos = LocalPlayer->GetBoneByID(neck);
	res.valid = utils::LineOfSight(lppos, target);
	if (!res.valid) return res;

	res.dist = realdist;
	res.entity = Player;
	res.position = target;
	return res;
}

