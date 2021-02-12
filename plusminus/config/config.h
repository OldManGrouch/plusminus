#include <string>
#include <vector>
#include <Windows.h>
template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
public:
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "C:\\ProgramData\\";
		Setup();
	}

	void Save()
	{
		std::string file;
		file = szPath + vars::stuff::ConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Load()
	{
		std::string file;
		file = szPath + vars::stuff::ConfigName + ".cfg";
		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[32] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name)
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name)
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name)
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}

	void Setup()
	{
		SetupValue(vars::combat::hitbox_override, false, c_xor("Combat"), c_xor("HitboxOverride"));
		SetupValue(vars::combat::hs_percentage, 100, c_xor("Combat"), c_xor("HeadshotPercentage"));
		SetupValue(vars::combat::always_heli_rotor, false, c_xor("Combat"), c_xor("AlwaysHeliHotspot"));
		SetupValue(vars::combat::silent_melee, false, c_xor("Combat"), c_xor("SilentMelee"));
		SetupValue(vars::combat::psilent, false, c_xor("Combat"), c_xor("pSilent"));
		SetupValue(vars::combat::psilentonkey, false, c_xor("Combat"), c_xor("pSilentOnKey"));
		SetupValue(vars::combat::psilenttarget, 0, c_xor("Combat"), c_xor("pSilentTargeting"));
		SetupValue(vars::combat::aimbot, false, c_xor("Combat"), c_xor("Aimbot"));
		SetupValue(vars::combat::smooth, false, c_xor("Combat"), c_xor("Smooth"));
		SetupValue(vars::combat::smooth_factor, 1, c_xor("Combat"), c_xor("Smoothing"));
		SetupValue(vars::combat::visualize_fov, false, c_xor("Combat"), c_xor("DrawFov"));
		SetupValue(vars::combat::fov, 100.f, c_xor("Combat"), c_xor("Fov"));
		SetupValue(vars::combat::range, 300.f, c_xor("Combat"), c_xor("Range"));
		SetupValue(vars::combat::ignore_sleepers, false, c_xor("Combat"), c_xor("IgnoreSleepers"));
		SetupValue(vars::combat::ignore_team, false, c_xor("Combat"), c_xor("IgnoreTeam"));
		SetupValue(vars::combat::ignore_npc, false, c_xor("Combat"), c_xor("IgnoreNpc"));
		SetupValue(vars::combat::ignore_heli, false, c_xor("Combat"), c_xor("IgnoreHeli"));

		SetupValue(vars::weapons::no_recoil, false, c_xor("Weapon"), c_xor("NoRecoil"));
		SetupValue(vars::weapons::recoil_control, 100.f, c_xor("Weapon"), c_xor("RecoilControl"));
		SetupValue(vars::weapons::no_spread, false, c_xor("Weapon"), c_xor("NoSpread"));
		SetupValue(vars::weapons::no_sway, false, c_xor("Weapon"), c_xor("NoSway"));
		SetupValue(vars::weapons::remove_attack_anim, false, c_xor("Weapon"), c_xor("NoAttackAnim"));
		SetupValue(vars::weapons::rapid_fire, false, c_xor("Weapon"), c_xor("RapidFire"));
		SetupValue(vars::weapons::automatic, false, c_xor("Weapon"), c_xor("Automatic"));
		SetupValue(vars::weapons::thick_bullet, false, c_xor("Weapon"), c_xor("ThickBullets"));
		SetupValue(vars::weapons::fast_bullets, false, c_xor("Weapon"), c_xor("CBSM"));
		SetupValue(vars::weapons::minicopter_aim, false, c_xor("Weapon"), c_xor("Minicopter Aim"));
		SetupValue(vars::weapons::eokatap, false, c_xor("Weapon"), c_xor("EokaTap"));
		SetupValue(vars::weapons::fastbow, false, c_xor("Weapon"), c_xor("FastBow"));
		SetupValue(vars::weapons::penetrate, false, c_xor("Weapon"), c_xor("Penetrate"));
		SetupValue(vars::weapons::spoof_hitdistance, false, c_xor("Weapon"), c_xor("SpoofHitDistance"));
		SetupValue(vars::weapons::hitdistance, 300.f, c_xor("Weapon"), c_xor("HitDistance"));
		
		SetupValue(vars::players::name, false, c_xor("Players"), c_xor("name"));
		SetupValue(vars::players::box, false, c_xor("Players"), c_xor("box"));
		SetupValue(vars::players::boxstyle, 0, c_xor("Players"), c_xor("boxstyle"));
		SetupValue(vars::players::fillbox, false, c_xor("Players"), c_xor("fillbox"));
		SetupValue(vars::players::skeleton, false, c_xor("Players"), c_xor("skeleton"));
		SetupValue(vars::players::healthdist, false, c_xor("Players"), c_xor("healthdist"));
		SetupValue(vars::players::healthbar, false, c_xor("Players"), c_xor("healthbar"));
		SetupValue(vars::players::healthbarstyle, 0, c_xor("Players"), c_xor("healthbarstyle"));
		SetupValue(vars::players::weapon, false, c_xor("Players"), c_xor("weapon"));
		SetupValue(vars::players::tracers, false, c_xor("Players"), c_xor("tracers"));
		SetupValue(vars::players::chams, false, c_xor("Players"), c_xor("chams"));
		SetupValue(vars::players::targetline, false, c_xor("Players"), c_xor("targetline"));
		SetupValue(vars::players::belt, false, c_xor("Players"), c_xor("belt"));
		SetupValue(vars::players::beltx, 300.f, c_xor("Players"), c_xor("beltx"));
		SetupValue(vars::players::belty, 300.f, c_xor("Players"), c_xor("belty"));
		SetupValue(vars::players::sleeperignore, false, c_xor("Players"), c_xor("sleeperignore"));

		SetupValue(vars::npc::name, false, c_xor("NPCs"), c_xor("name"));
		SetupValue(vars::npc::box, false, c_xor("NPCs"), c_xor("box"));
		SetupValue(vars::npc::boxstyle, 0, c_xor("NPCs"), c_xor("boxstyle"));
		SetupValue(vars::npc::fillbox, false, c_xor("NPCs"), c_xor("fillbox"));
		SetupValue(vars::npc::skeleton, false, c_xor("NPCs"), c_xor("skeleton"));
		SetupValue(vars::npc::healthdist, false, c_xor("NPCs"), c_xor("healthdist"));
		SetupValue(vars::npc::healthbar, false, c_xor("NPCs"), c_xor("healthbar"));
		SetupValue(vars::npc::healthbarstyle, 0, c_xor("NPCs"), c_xor("healthbarstyle"));
		SetupValue(vars::npc::weapon, false, c_xor("NPCs"), c_xor("weapon"));
		SetupValue(vars::npc::tracers, false, c_xor("NPCs"), c_xor("tracers"));
		
		SetupValue(vars::misc::fov, 90.f, c_xor("Misc"), c_xor("SexyFuckingFovValue"));
		SetupValue(vars::misc::silent_walk, false, c_xor("Misc"), c_xor("SilentWalk"));
		SetupValue(vars::misc::spoof_ladderstate, false, c_xor("Misc"), c_xor("SpoofOnLadder"));
		SetupValue(vars::misc::anti_aim, false, c_xor("Misc"), c_xor("AntiAim"));
		SetupValue(vars::misc::anti_aim_speed, 25, c_xor("Misc"), c_xor("AntiAimSpeed"));
		SetupValue(vars::misc::anti_aim_yaw, 0, c_xor("Misc"), c_xor("AntiAimYaw"));
		SetupValue(vars::misc::anti_aim_indicator, false, c_xor("Misc"), c_xor("AntiAimIndicator"));
		SetupValue(vars::misc::hit_logs, false, c_xor("Misc"), c_xor("HitLogs"));
		SetupValue(vars::misc::faster_healing, false, c_xor("Misc"), c_xor("FastHeal"));
		SetupValue(vars::misc::fake_lag, false, c_xor("Misc"), c_xor("FakeLag"));
		SetupValue(vars::misc::fakeadmin, false, c_xor("Misc"), c_xor("FakeAdmin"));
		SetupValue(vars::misc::annoyer, false, c_xor("Misc"), c_xor("Annoyer"));
		SetupValue(vars::misc::suicide, false, c_xor("Misc"), c_xor("Suicide"));
		SetupValue(vars::misc::no_fall, false, c_xor("Misc"), c_xor("NoFall"));
		SetupValue(vars::misc::can_attack, false, c_xor("Misc"), c_xor("ShootAnywhere"));
		SetupValue(vars::misc::omnidirectional_sprinting, false, c_xor("Misc"), c_xor("OmniSprint"));
		SetupValue(vars::misc::long_neck, false, c_xor("Misc"), c_xor("LongNeck"));
		SetupValue(vars::misc::walker, false, c_xor("Misc"), c_xor("IgnoreCollision"));
		SetupValue(vars::misc::jesus, false, c_xor("Misc"), c_xor("Jesus"));
		SetupValue(vars::misc::inf_jump, false, c_xor("Misc"), c_xor("InfiniteJump"));
		SetupValue(vars::misc::better_jump, false, c_xor("Misc"), c_xor("BetterJump"));
		SetupValue(vars::misc::custom_hitsound, false, c_xor("Misc"), c_xor("CustomHitsound"));
		SetupValue(vars::misc::auto_pickup, false, c_xor("Misc"), c_xor("AutoCollect"));
		SetupValue(vars::misc::auto_revive, false, c_xor("Misc"), c_xor("AutoAssist"));
		SetupValue(vars::misc::insta_revive, false, c_xor("Misc"), c_xor("InstaRevive"));
		SetupValue(vars::misc::revive_team_only, false, c_xor("Misc"), c_xor("AssistTeamOnly"));
		SetupValue(vars::misc::auto_farm_ore, false, c_xor("Misc"), c_xor("SilentOre"));
		SetupValue(vars::misc::auto_farm_tree, false, c_xor("Misc"), c_xor("SilentTree"));
		SetupValue(vars::misc::bright_ambient, false, c_xor("Misc"), c_xor("CustomAmbient"));
		SetupValue(vars::misc::rayleigh_changer, false, c_xor("Misc"), c_xor("Rayleigh"));
		SetupValue(vars::misc::rayleigh, 1.f, c_xor("Misc"), c_xor("RayleighAmount"));
		SetupValue(vars::misc::custom_time, false, c_xor("Misc"), c_xor("CustomTime"));
		SetupValue(vars::misc::time, 10.f, c_xor("Misc"), c_xor("Time"));
		SetupValue(vars::misc::gravity, false, c_xor("Misc"), c_xor("Gravity"));
		SetupValue(vars::misc::gravity_modifier, 0.f, c_xor("Misc"), c_xor("GravityModifier"));

		SetupValue(vars::ores::stone, false, c_xor("ores"), c_xor("stone"));
		SetupValue(vars::ores::sulfur, false, c_xor("ores"), c_xor("sulfur"));
		SetupValue(vars::ores::metal, false, c_xor("ores"), c_xor("metal"));
		SetupValue(vars::ores::draw_distance, 300.f, c_xor("ores"), c_xor("oreDrawDistance"));
		SetupValue(vars::ores::show_distance, false, c_xor("ores"), c_xor("showCollectables"));

		SetupValue(vars::visuals::radar_, false, c_xor("visuals"), c_xor("Radar"));
		SetupValue(vars::visuals::raid_esp, false, c_xor("visuals"), c_xor("Raids"));
		SetupValue(vars::visuals::patrol_heli, false, c_xor("visuals"), c_xor("PatrolHeli"));
		SetupValue(vars::visuals::vehicles::minicopter, false, c_xor("visuals"), c_xor("Minicopter"));
		SetupValue(vars::visuals::vehicles::scrapheli, false, c_xor("visuals"), c_xor("ScrapHeli"));
		SetupValue(vars::visuals::vehicles::boat, false, c_xor("visuals"), c_xor("Boat"));
		SetupValue(vars::visuals::vehicles::rhib, false, c_xor("visuals"), c_xor("RHIB"));
		SetupValue(vars::visuals::vehicles::show_distance, false, c_xor("visuals"), c_xor("vehicleDistance"));
		SetupValue(vars::visuals::vehicles::draw_distance, 300.f, c_xor("visuals"), c_xor("drawVehicleDistance"));
		SetupValue(vars::visuals::turrets::auto_turret, false, c_xor("visuals"), c_xor("AutoTurret"));
		SetupValue(vars::visuals::turrets::flame_turret, false, c_xor("visuals"), c_xor("FlameTurret"));
		SetupValue(vars::visuals::turrets::shotgun_turret, false, c_xor("visuals"), c_xor("ShotgunTurret"));
		SetupValue(vars::visuals::turrets::landmine, false, c_xor("visuals"), c_xor("Landmine"));
		SetupValue(vars::visuals::turrets::bear_trap, false, c_xor("visuals"), c_xor("BearTrap"));
		SetupValue(vars::visuals::turrets::show_distance, false, c_xor("visuals"), c_xor("trapDistance"));
		SetupValue(vars::visuals::turrets::draw_distance, 300.f, c_xor("visuals"), c_xor("drawTrapDistance"));
		SetupValue(vars::visuals::other::corpse, false, c_xor("visuals"), c_xor("Corpse"));
		SetupValue(vars::visuals::other::stash, false, c_xor("visuals"), c_xor("Stash"));
		SetupValue(vars::visuals::other::hemp, false, c_xor("visuals"), c_xor("Hemp"));
		SetupValue(vars::visuals::other::show_distance, false, c_xor("visuals"), c_xor("otherDistance"));
		SetupValue(vars::visuals::other::draw_distance, 300.f, c_xor("visuals"), c_xor("drawOtherDistance"));
		SetupValue(vars::visuals::crates::supply, false, c_xor("visuals"), c_xor("Supply"));
		SetupValue(vars::visuals::crates::chinook, false, c_xor("visuals"), c_xor("Chinook"));
		SetupValue(vars::visuals::crates::heli, false, c_xor("visuals"), c_xor("Heli"));
		SetupValue(vars::visuals::crates::bradley, false, c_xor("visuals"), c_xor("Bradley"));
		SetupValue(vars::visuals::bradley_apc, false, c_xor("visuals"), c_xor("BradleyTank"));
		SetupValue(vars::visuals::crates::show_distance, false, c_xor("visuals"), c_xor("Hemp"));
		SetupValue(vars::visuals::crates::draw_distance, 300.f, c_xor("visuals"), c_xor("otherDistance"));

		SetupValue(vars::keys::locktarget, 0x4A, c_xor("Keys"), c_xor("LockTarget"));
		SetupValue(vars::keys::aimkey, 0x58, c_xor("Keys"), c_xor("aimKey"));
		SetupValue(vars::keys::gravitykey, 0x04, c_xor("Keys"), c_xor("gravityKey"));
		SetupValue(vars::keys::forcepos, 0x4E, c_xor("Keys"), c_xor("froc"));
		SetupValue(vars::keys::suicide, 0x5A, c_xor("Keys"), c_xor("suicide"));
		SetupValue(vars::keys::psilent, 0x50, c_xor("Keys"), c_xor("pSilent"));
		SetupValue(vars::keys::longneck, 0x4D, c_xor("Keys"), c_xor("neck"));

		SetupValue(vars::crosshair::default, false, c_xor("Crosshair"), c_xor("Default"));
		SetupValue(vars::crosshair::custom, false, c_xor("Crosshair"), c_xor("Custom"));
		SetupValue(vars::crosshair::gap, 5.f, c_xor("Crosshair"), c_xor("Gap"));
		SetupValue(vars::crosshair::length, 5.f, c_xor("Crosshair"), c_xor("Length"));
		SetupValue(vars::crosshair::dot, false, c_xor("Crosshair"), c_xor("Dot"));

		SetupValue(indicator_x, 100.f, c_xor("a"), c_xor("x"));
		SetupValue(indicator_y, 100.f, c_xor("a"), c_xor("y"));

		SetupValue(vars::visuals::radar::x, 100.f, c_xor("b"), c_xor("x"));
		SetupValue(vars::visuals::radar::y, 100.f, c_xor("b"), c_xor("y"));
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;