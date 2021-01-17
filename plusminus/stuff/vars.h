HANDLE handle2;
bool init, show = true;
#define null NULL
namespace vars {

}
namespace Global
{
	bool wasinvalid = false;
	Str donePlayer = nullptr;
	int doneHits = 0;
	float doneDamage = 0.f;

	int testInt = 0;
	float testFloat = 1.f;
	char testChar[0x100] = "testyvesty";
	bool debugtab = false;
	int RetardDivideFactor = 0;
	bool Panic = false;
	int ScreenHigh = 0;
	int ScreenWidth = 0;
	float BoneToAim = 0.5;
	char ConfigName[0x100] = "cfg";
	
}
namespace Keys
{
	int neck = { 0x4D };
	int forcepos{ 0x4E };
	int pSilent{ 0x50 }; // P key
	int lockTarget{ 0x4A };
	int aimKey{ 0x58 }; // VK_RMOUSE
	int gravityKey{ 0x04 };
	int walkonWaterKey{ 0x06 };
}
namespace Storage
{
	uintptr_t chamsShader = NULL;
	uintptr_t gBase = NULL;
	uintptr_t uBase = NULL;
	uintptr_t closestPlayer = NULL;
	uintptr_t closestHeli = NULL;
	uintptr_t closestHeliObj = NULL;
}
namespace Combat
{
	bool magicbollet = false;
	bool pSilentOnKey = false;
	bool AlwaysHeliHotspot = false;
	bool HitboxOverride = false;
	bool pSilent = false;
	int pSilentTargeting = 0;
	bool Activate = false;
	bool Smooth = false;
	int Smoothing = 1;
	
	int HeadshotPercentage = false;
	float Range = 300.f;
	float Fov = 100.f;
	bool DrawFov = false;
	bool LockTarget = false;
	bool IgnorePlayers = false;
	bool IgnoreHeli = false;
	bool IgnoreSleepers = false;
	bool IgnoreTeam = true;
	bool IgnoreNpc = false;
}

namespace Weapons
{
	bool SilentMelee = false;
	bool FastBullet = false;
	float FastBulletMultiplier = 1.f;
	bool SilentOre = false;
	bool SilentTree = false;
	bool Penetrate = false;
	bool canHoldItems = false;
	bool SpoofHitDistance = false;
	float HitDistance = 100.f;
	bool LongHand = false;
	bool NoRicochet = false;
	bool NoRecoil = false;
	bool LegitNoRecoil = false;
	float controlX = 0.f;
	float controlY = 0.f;
	float NoRecoilPercentage = 1.f;
	bool AntiSpread = false;
	bool Automatic = false;
	bool FatBullet = false;
	bool NoSway = false;
	bool RapidFire = false;
	bool SuperBow = false;
	bool SuperEoka = false;
	bool jumpAim = false;
}
namespace Radar {
	bool Enable = false;
	float Size = 300.f;
	float Range = 300.f;
	float x = 200.f;
	float y = 200.f;
}
namespace PlayerEsp
{
	bool chams = false;
	bool belt = false;
	float beltx = 50.f;
	float belty = 50.f;
	bool box = false;
	int boxstyle = 0;
	bool skeleton = false;
	bool name = false;
	bool healthdist = false;
	bool healthbar = false;
	int healthbarstyle = 0;
	bool weapon = false;
	bool sleeperignore = false;
	bool tracers = false;
	bool targetline = false;
	bool fillbox = false;
}
namespace BotsEsp
{
	bool box = false;
	int boxstyle = false;
	bool skeleton = false;
	bool name = false;
	bool healthdist = false;
	bool healthbar = false;
	int healthbarstyle = 0;
	bool weapon = false;
	bool tracers = false;
	bool fillbox = false;
}

namespace Ores
{
	bool showCollectables = false;
	bool Stone = false;
	bool Sulfur = false;
	bool Metal = false;
	bool showDistance = false;
	float oreDrawDistance = 300.f;
}
namespace Visuals
{
	bool BradleyTank = false;
	bool PatrolHeli = false;

	namespace Base {
		bool TC = false;
		bool SleepingBag = false;
		bool Bed = false;
		bool Boxes = false;
		bool baseDistance = false;
		float drawBaseDistance = 300.f;
	}
	namespace Vehicles {
		bool Minicopter = false;
		bool ScrapHeli = false;
		bool Boat = false;
		bool RHIB = false;
		bool vehicleDistance = false;
		float drawVehicleDistance = 300.f;
	}
	namespace Turrets {
		bool AutoTurret = false;
		bool FlameTurret = false;
		bool ShotgunTurret = false;
		bool Landmine = false;
		bool BearTrap = false;
		bool trapDistance = false;
		float drawTrapDistance = 300.f;
	}
	namespace Other {
		bool DroppedItems = false;
		bool Corpse = false;
		bool Stash = false;
		bool Hemp = false;
		bool otherDistance = false;
		float drawOtherDistance = 300.f;
	}
	namespace Crates {
		bool Supply = false;
		bool Chinook = false;
		bool Heli = false;
		bool Bradley = false;
		bool crateDistance = false;
		float drawCrateDistance = 300.f;
	}
	namespace Animals {
		bool Bear = false;
		bool Pig = false;
		bool Chicken = false;
		bool Wolf = false;
		bool Deer = false;
		bool animalDistance = false;
		float drawAnimalDistance = 300.f;
	}
}
namespace ColorsNShit
{
	float playercolors[4] = { 1,1,1,1 };
	float invisplayercolors[4] = { 1,0,0,1 };
	float sleepercolors[4] = { 1,0.5,0,1 };
	float crosshairfovcolors[4] = { 1,1,1,1 };
	float botcolors[4] = { 1,1,0,1 };
	float teamcolors[4] = { 0,1,0,1 };

	float stoneore[4] = { 0.78, 0.78 ,0.78 , 1 };
	float sulfurore[4] = { 1, 0.78 ,0.13 , 1 };
	float metalore[4] = { 0.54, 0.19 ,0 , 1 };

	float patrolhelicopter[4] = { 0.27 , 0.27 , 1 , 1 };
	float airdrop[4] = { 0 , 0.20 , 0.43 , 1 };
	float chinook[4] = { 0.34 , 0 , 0 , 1 };
	float minicopter[4] = { 0.5 , 0.45 , 0 , 1 };
	float scrapheli[4] = { 0 , 0.5 , 0 , 1 };
	float boat[4] = { 0 , 0.8 , 0.8 , 1 };
	float rhib[4] = { 0.34 , 0.34 , 0.34 , 1 };
	float turret[4] = { 1 , 0.34 , 0 , 1 };
	float flame[4] = { 1 , 0.78 , 0 , 1 };
	float shotgun[4] = { 0.61 , 0.68 , 1 , 1 };
	float landmine[4] = { 0 , 0 , 1 , 1 };
	float beartrap[4] = { 0.32 , 0 , 0.65 , 1 };
	float hemp[4] = { 0.56 , 1 , 0.34 , 1 };
	float corpse[4] = { 0.5 , 0.21 , 0.34 , 1 };
	float stash[4] = { 0 , 0.5 , 0 , 1 };


	float fovsegments = 15;
	float boxRoundness = 0;
}

namespace Misc
{
	bool Suicide = false;
	bool LongNeck = false;
	bool InfiniteJump = false;
	bool HitLogs = false;
	bool InstaRevive = false;
	bool Rayleigh = false;
	float RayleighAmount = 10.f;
	bool AutoAssist = false;
	bool AssistTeamOnly = false;
	bool Annoyer = false;
	bool CustomAmbient = false;
	bool AutoCollect = false;
	bool Flyhack = false;
	bool AntiAim = false;
	int AntiAimSpeed = 10;
	bool FakeLag = false;
	bool SilentWalk = false;
	bool SexyFuckingFov = false;
	float SexyFuckingFovValue = 90.f;
	bool Gravity = false;
	float GravityModifier = 0.f;
	bool CustomHitsound = false;
	bool SpiderMan = false;
	bool WalkOnWater = false;
	bool omniSprint = false;
	bool FakeAdmin = false;
	bool CustomTime = false;
	float Time = 10.0f;
}
namespace Crosshair {
	bool Default = false;
	bool Custom = false;
	
	bool Dot = false;
	float Gap = 5.f;
	float Length = 5.f;
}