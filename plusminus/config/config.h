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
		file = szPath + Global::ConfigName + ".cfg";

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
		file = szPath + Global::ConfigName + ".cfg";
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
		SetupValue(Combat::HitboxOverride, false, c_xor("Combat"), c_xor("HitboxOverride"));
		SetupValue(Combat::HeadshotPercentage, 100, c_xor("Combat"), c_xor("HeadshotPercentage"));
		SetupValue(Combat::AlwaysHeliHotspot, false, c_xor("Combat"), c_xor("AlwaysHeliHotspot"));
		SetupValue(Weapons::SilentMelee, false, c_xor("Combat"), c_xor("SilentMelee"));
		SetupValue(Combat::pSilent, false, c_xor("Combat"), c_xor("pSilent"));
		SetupValue(Combat::pSilentTargeting, 0, c_xor("Combat"), c_xor("pSilentTargeting"));
		SetupValue(Combat::Activate, false, c_xor("Combat"), c_xor("Aimbot"));
		SetupValue(Combat::Smooth, false, c_xor("Combat"), c_xor("Smooth"));
		SetupValue(Combat::Smoothing, 1, c_xor("Combat"), c_xor("Smoothing"));
		SetupValue(Combat::DrawFov, false, c_xor("Combat"), c_xor("DrawFov"));
		SetupValue(Combat::Fov, 100.f, c_xor("Combat"), c_xor("Fov"));
		SetupValue(Combat::Range, 300.f, c_xor("Combat"), c_xor("Range"));
		SetupValue(Combat::IgnoreSleepers, false, c_xor("Combat"), c_xor("IgnoreSleepers"));
		SetupValue(Combat::IgnoreTeam, false, c_xor("Combat"), c_xor("IgnoreTeam"));
		SetupValue(Combat::IgnoreNpc, false, c_xor("Combat"), c_xor("IgnoreNpc"));
		SetupValue(Combat::IgnoreHeli, false, c_xor("Combat"), c_xor("IgnoreHeli"));

		SetupValue(Weapons::NoRecoil, false, c_xor("Weapon"), c_xor("NoRecoil"));
		SetupValue(Weapons::LegitNoRecoil, false, c_xor("Weapon"), c_xor("NoRecoil"));
		SetupValue(Weapons::AntiSpread, false, c_xor("Weapon"), c_xor("NoSpread"));
		SetupValue(Weapons::NoSway, false, c_xor("Weapon"), c_xor("NoSway"));
		SetupValue(Weapons::NoRicochet, false, c_xor("Weapon"), c_xor("NoRicochet"));
		SetupValue(Weapons::RapidFire, false, c_xor("Weapon"), c_xor("RapidFire"));
		SetupValue(Weapons::Automatic, false, c_xor("Weapon"), c_xor("Automatic"));
		SetupValue(Weapons::FatBullet, false, c_xor("Weapon"), c_xor("ThickBullets"));
		SetupValue(Weapons::FastBullet, false, c_xor("Weapon"), c_xor("CBSM"));
		SetupValue(Weapons::canHoldItems, false, c_xor("Weapon"), c_xor("Minicopter Aim"));
		SetupValue(Weapons::SuperEoka, false, c_xor("Weapon"), c_xor("EokaTap"));
		SetupValue(Weapons::SuperBow, false, c_xor("Weapon"), c_xor("FastBow"));
		SetupValue(Weapons::Penetrate, false, c_xor("Weapon"), c_xor("Penetrate"));
		SetupValue(Weapons::SpoofHitDistance, false, c_xor("Weapon"), c_xor("SpoofHitDistance"));
		
		SetupValue(PlayerEsp::name, false, c_xor("Players"), c_xor("name"));
		SetupValue(PlayerEsp::box, false, c_xor("Players"), c_xor("box"));
		SetupValue(PlayerEsp::boxstyle, 0, c_xor("NPCs"), c_xor("boxstyle"));
		SetupValue(PlayerEsp::fillbox, false, c_xor("Players"), c_xor("fillbox"));
		SetupValue(PlayerEsp::skeleton, false, c_xor("Players"), c_xor("skeleton"));
		SetupValue(PlayerEsp::healthdist, false, c_xor("Players"), c_xor("healthdist"));
		SetupValue(PlayerEsp::healthbar, false, c_xor("Players"), c_xor("healthbar"));
		SetupValue(PlayerEsp::healthbarstyle, 0, c_xor("NPCs"), c_xor("healthbarstyle"));
		SetupValue(PlayerEsp::weapon, false, c_xor("Players"), c_xor("weapon"));
		SetupValue(PlayerEsp::tracers, false, c_xor("Players"), c_xor("tracers"));
		SetupValue(PlayerEsp::chams, false, c_xor("Players"), c_xor("chams"));
		SetupValue(PlayerEsp::targetline, false, c_xor("Players"), c_xor("targetline"));
		SetupValue(PlayerEsp::belt, false, c_xor("Players"), c_xor("belt"));
		SetupValue(PlayerEsp::beltx, 300.f, c_xor("Players"), c_xor("beltx"));
		SetupValue(PlayerEsp::belty, 300.f, c_xor("Players"), c_xor("belty"));
		SetupValue(PlayerEsp::sleeperignore, false, c_xor("Players"), c_xor("sleeperignore"));

		SetupValue(BotsEsp::name, false, c_xor("NPCs"), c_xor("name"));
		SetupValue(BotsEsp::box, false, c_xor("NPCs"), c_xor("box"));
		SetupValue(BotsEsp::boxstyle, 0, c_xor("NPCs"), c_xor("boxstyle"));
		SetupValue(BotsEsp::fillbox, false, c_xor("NPCs"), c_xor("fillbox"));
		SetupValue(BotsEsp::skeleton, false, c_xor("NPCs"), c_xor("skeleton"));
		SetupValue(BotsEsp::healthdist, false, c_xor("NPCs"), c_xor("healthdist"));
		SetupValue(BotsEsp::healthbar, false, c_xor("NPCs"), c_xor("healthbar"));
		SetupValue(BotsEsp::healthbarstyle, 0, c_xor("NPCs"), c_xor("healthbarstyle"));
		SetupValue(BotsEsp::weapon, false, c_xor("NPCs"), c_xor("weapon"));
		SetupValue(BotsEsp::tracers, false, c_xor("NPCs"), c_xor("tracers"));
		
		SetupValue(Misc::SexyFuckingFovValue, 90.f, c_xor("Misc"), c_xor("SexyFuckingFovValue"));
		SetupValue(Misc::SilentWalk, false, c_xor("Misc"), c_xor("SilentWalk"));
		SetupValue(Misc::Flyhack, false, c_xor("Misc"), c_xor("SpoofOnLadder"));
		SetupValue(Misc::AntiAim, false, c_xor("Misc"), c_xor("AntiAim"));
		SetupValue(Misc::FakeLag, false, c_xor("Misc"), c_xor("FakeLag"));
		SetupValue(Misc::FakeAdmin, false, c_xor("Misc"), c_xor("FakeAdmin"));
		SetupValue(Misc::Annoyer, false, c_xor("Misc"), c_xor("Annoyer"));
		SetupValue(Weapons::jumpAim, false, c_xor("Misc"), c_xor("ShootAnywhere"));
		SetupValue(Misc::omniSprint, false, c_xor("Misc"), c_xor("OmniSprint"));
		SetupValue(Misc::SpiderMan, false, c_xor("Misc"), c_xor("SpiderMan"));
		SetupValue(Misc::LongNeck, false, c_xor("Misc"), c_xor("LongNeck"));
		SetupValue(Misc::InfiniteJump, false, c_xor("Misc"), c_xor("InfiniteJump"));
		SetupValue(Misc::CustomHitsound, false, c_xor("Misc"), c_xor("CustomHitsound"));
		SetupValue(Misc::AutoCollect, false, c_xor("Misc"), c_xor("AutoCollect"));
		SetupValue(Misc::AutoAssist, false, c_xor("Misc"), c_xor("AutoAssist"));
		SetupValue(Misc::InstaRevive, false, c_xor("Misc"), c_xor("InstaRevive"));
		SetupValue(Misc::AssistTeamOnly, false, c_xor("Misc"), c_xor("AssistTeamOnly"));
		SetupValue(Weapons::SilentOre, false, c_xor("Misc"), c_xor("SilentOre"));
		SetupValue(Weapons::SilentTree, false, c_xor("Misc"), c_xor("SilentTree"));
		SetupValue(Misc::CustomAmbient, false, c_xor("Misc"), c_xor("CustomAmbient"));
		SetupValue(Misc::Rayleigh, false, c_xor("Misc"), c_xor("Rayleigh"));
		SetupValue(Misc::RayleighAmount, false, c_xor("Misc"), c_xor("RayleighAmount"));
		SetupValue(Misc::CustomTime, false, c_xor("Misc"), c_xor("CustomTime"));
		SetupValue(Misc::Time, 10.f, c_xor("Misc"), c_xor("Time"));
		SetupValue(Misc::Gravity, false, c_xor("Misc"), c_xor("Gravity"));
		SetupValue(Misc::GravityModifier, 0.f, c_xor("Misc"), c_xor("GravityModifier"));

		SetupValue(Ores::Stone, false, c_xor("ores"), c_xor("stone"));
		SetupValue(Ores::Sulfur, false, c_xor("ores"), c_xor("sulfur"));
		SetupValue(Ores::Metal, false, c_xor("ores"), c_xor("metal"));
		SetupValue(Ores::oreDrawDistance, 300.f, c_xor("ores"), c_xor("oreDrawDistance"));
		SetupValue(Ores::showCollectables, false, c_xor("ores"), c_xor("showCollectables"));

		SetupValue(Visuals::PatrolHeli, false, c_xor("visuals"), c_xor("PatrolHeli"));
		SetupValue(Visuals::Vehicles::Minicopter, false, c_xor("visuals"), c_xor("Minicopter"));
		SetupValue(Visuals::Vehicles::ScrapHeli, false, c_xor("visuals"), c_xor("ScrapHeli"));
		SetupValue(Visuals::Vehicles::Boat, false, c_xor("visuals"), c_xor("Boat"));
		SetupValue(Visuals::Vehicles::RHIB, false, c_xor("visuals"), c_xor("RHIB"));
		SetupValue(Visuals::Vehicles::vehicleDistance, false, c_xor("visuals"), c_xor("vehicleDistance"));
		SetupValue(Visuals::Vehicles::drawVehicleDistance, 300.f, c_xor("visuals"), c_xor("drawVehicleDistance"));
		SetupValue(Visuals::Turrets::AutoTurret, false, c_xor("visuals"), c_xor("AutoTurret"));
		SetupValue(Visuals::Turrets::FlameTurret, false, c_xor("visuals"), c_xor("FlameTurret"));
		SetupValue(Visuals::Turrets::ShotgunTurret, false, c_xor("visuals"), c_xor("ShotgunTurret"));
		SetupValue(Visuals::Turrets::Landmine, false, c_xor("visuals"), c_xor("Landmine"));
		SetupValue(Visuals::Turrets::BearTrap, false, c_xor("visuals"), c_xor("BearTrap"));
		SetupValue(Visuals::Turrets::trapDistance, false, c_xor("visuals"), c_xor("trapDistance"));
		SetupValue(Visuals::Turrets::drawTrapDistance, 300.f, c_xor("visuals"), c_xor("drawTrapDistance"));
		SetupValue(Visuals::Other::Corpse, false, c_xor("visuals"), c_xor("Corpse"));
		SetupValue(Visuals::Other::Stash, false, c_xor("visuals"), c_xor("Stash"));
		SetupValue(Visuals::Other::Hemp, false, c_xor("visuals"), c_xor("Hemp"));
		SetupValue(Visuals::Other::otherDistance, false, c_xor("visuals"), c_xor("otherDistance"));
		SetupValue(Visuals::Other::drawOtherDistance, 300.f, c_xor("visuals"), c_xor("drawOtherDistance"));
		SetupValue(Visuals::Crates::Supply, false, c_xor("visuals"), c_xor("Supply"));
		SetupValue(Visuals::Crates::Chinook, false, c_xor("visuals"), c_xor("Chinook"));
		SetupValue(Visuals::Crates::Heli, false, c_xor("visuals"), c_xor("Heli"));
		SetupValue(Visuals::Crates::Bradley, false, c_xor("visuals"), c_xor("Bradley"));
		SetupValue(Visuals::BradleyTank, false, c_xor("visuals"), c_xor("BradleyTank"));
		SetupValue(Visuals::Crates::crateDistance, false, c_xor("visuals"), c_xor("Hemp"));
		SetupValue(Visuals::Crates::drawCrateDistance, 300.f, c_xor("visuals"), c_xor("otherDistance"));

		SetupValue(Keys::lockTarget, 0x4A, c_xor("Keys"), c_xor("LockTarget"));
		SetupValue(Keys::aimKey, 0x58, c_xor("Keys"), c_xor("aimKey"));
		SetupValue(Keys::gravityKey, 0x04, c_xor("Keys"), c_xor("gravityKey"));
		SetupValue(Keys::forcepos, 0x4E, c_xor("Keys"), c_xor("froc"));
		SetupValue(Keys::pSilent, 0x50, c_xor("Keys"), c_xor("pSilent"));
		SetupValue(Keys::neck, 0x4D, c_xor("Keys"), c_xor("neck"));

		SetupValue(Crosshair::Default, false, c_xor("Crosshair"), c_xor("Default"));
		SetupValue(Crosshair::Custom, false, c_xor("Crosshair"), c_xor("Custom"));
		SetupValue(Crosshair::Gap, 5.f, c_xor("Crosshair"), c_xor("Gap"));
		SetupValue(Crosshair::Length, 5.f, c_xor("Crosshair"), c_xor("Length"));
		SetupValue(Crosshair::Dot, false, c_xor("Crosshair"), c_xor("Dot"));
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;