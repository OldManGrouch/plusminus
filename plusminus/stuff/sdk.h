//game structs
const unsigned short Crc16Table[256] = {
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

enum BoneList : int {
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};
enum class CursorLockMode {
	None = 0,
	Locked = 1,
	Confined = 2
};
enum PlayerFlags : int {
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};
enum class layer : uint32_t {
	Default = 0,
	TransparentFX = 1,
	Ignore_Raycast = 2,
	Reserved1 = 3,
	Water = 4,
	UI = 5,
	Reserved2 = 6,
	Reserved3 = 7,
	Deployed = 8,
	Ragdoll = 9,
	Invisible = 10,
	AI = 11,
	PlayerMovement = 12,
	Vehicle_Detailed = 13,
	Game_Trace = 14,
	Vehicle_World = 15,
	World = 16,
	Player_Server = 17,
	Trigger = 18,
	Player_Model_Rendering = 19,
	Physics_Projectile = 20,
	Construction = 21,
	Construction_Socket = 22,
	Terrain = 23,
	Transparent = 24,
	Clutter = 25,
	Debris = 26,
	Vehicle_Large = 27,
	Prevent_Movement = 28,
	Prevent_Building = 29,
	Tree = 30,
	Unused2 = 31
};
enum LayerMasks : int {
	Default = 1,
	TransparentFX = 2,
	Ignore_Raycast = 4,
	Reserved1 = 8,
	Water = 16,
	UI = 32,
	Reserved2 = 64,
	Reserved3 = 128,
	Deployed = 256,
	Ragdoll = 512,
	Invisible = 1024,
	AI = 2048,
	Player_Movement = 4096,
	Vehicle_Detailed = 8192,
	Game_Trace = 16384,
	Vehicle_World = 32768,
	World = 65536,
	Player_Server = 131072,
	Trigger = 262144,
	Player_Model_Rendering = 524288,
	Physics_Projectile = 1048576,
	Construction = 2097152,
	Construction_Socket = 4194304,
	Terrain = 8388608,
	Transparent = 16777216,
	Clutter = 33554432,
	Debris = 67108864,
	Vehicle_Large = 134217728,
	Prevent_Movement = 268435456,
	Prevent_Building = 536870912,
	Tree = 1073741824,
	//Unused2 = -2147483648,
};
namespace ModelStateFlag {
	int Ducked = 1;
	int Jumped = 2;
	int OnGround = 4;
	int Sleeping = 8;
	int Sprinting = 16;
	int OnLadder = 32;
	int Flying = 64;
	int Aiming = 128;
	int Prone = 256;
	int Mounted = 512;
	int Relaxed = 1024;
	int OnPhone = 2048;
}
typedef struct _UncStr {
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;
class ConsoleOptions {
public:
	bool IsFromServer() { return read(this + 0x6, bool); }
};
class BaseProjectile {
private:
	unsigned short CRC(unsigned char* pcBlock, unsigned short len) {
		unsigned short crc = 0xFFFF;
		while (len--)
			crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];
		return crc;
	}
public:
	int GetID() {
		DWORD64 Info = read((DWORD64)this + 0x20, DWORD64); // public ItemDefinition info;
		int ID = read(Info + 0x18, int); // public int itemid;
		return ID;
	}
	char* ClassName() {
		return (char*)read(read(read(this + oHeldEntity, DWORD64), DWORD64) + 0x10, DWORD64);
	}
	Weapon Info() {
		int ID = GetID();
		for (Weapon k : info) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon{ 0 };
	}
	wchar_t* GetShortName(int* len) {
		DWORD64 Info = read(this + oItemDefinition, DWORD64);
		pUncStr Str = ((pUncStr)read(Info + oShortname, DWORD64));
		int leng = read(Str + 0x10, int);
		if (!leng) return nullptr;
		if (len)*len = leng;
		return Str->str;
	}
	wchar_t* GetShortNameName() {
		DWORD64 Info = read(this + oItemDefinition, DWORD64);
		pUncStr Str = ((pUncStr)read(Info + oShortname, DWORD64));
		return Str->str;
	}
	int LoadedAmmo() {
		const auto Held = read(this + oHeldEntity, DWORD64);
		if (Held <= 0)
			return 0;
		const auto Magazine = read(Held + oPrimaryMagazine, DWORD64);
		if (Magazine <= 0 || Magazine == 0x3F000000) {
			return 0;
		}
		const auto ammoType = read(Magazine + 0x20, DWORD64);
		if (ammoType <= 0 || ammoType == 0x3F000000) {
			return 0;
		}
		const int ammo = read(ammoType + 0x18, int);
		return ammo;
	}
	wchar_t* GetName() {
		DWORD64 Info = read(this + oItemDefinition, DWORD64);
		DWORD64 DispName = read(Info + oDisplayname, DWORD64);
		pUncStr Str = ((pUncStr)read(DispName + 0x18, DWORD64)); // default
		if (!Str) return nullptr; return Str->str;
	}
	int GetCount() {
		return read(this + 0x30, int);
	}
	int GetUID() {
		return read(this + oUID, int);
	}
	
	void RapidFire() {
		if (vars::weapons::rapid_fire) {
			DWORD64 heldentity = read(this + oHeldEntity, DWORD64);
			write(heldentity + oRepeatDelay, 0.09f, float);
		}
	}
	void NoSway() {
		DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
		if (vars::weapons::no_sway) {
			write(Heldd + 0x2B8, 0.f, float);
			write(Heldd + 0x2BC, 0.f, float);
		}
	}
	void NoRecoil() {
		DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
		DWORD64 recoil = read(Heldd + oRecoil, DWORD64);
		if (vars::weapons::no_recoil) {
			write(recoil + oRecoilYawMin, 0.f, float);
			write(recoil + oRecoilYawMax, 0.f, float);
			write(recoil + oRecoilPitchMin, 0.f, float);
			write(recoil + oRecoilPitchMax, 0.f, float);
		}
	}
	void SetAutomatic() {
		if (vars::weapons::automatic) {
			DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
			write(Heldd + oAutomatic, 1, bool);
		}
	}
	void SetBulletSpeed() {
		DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
		if (vars::weapons::fast_bullets) {
			write(Heldd + 0x26C, 1.4, float);
		}
		else {
			write(Heldd + 0x26C, 1, float);
		}
	}
	void FastBow() {
		if (vars::weapons::fastbow) {
			DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
			write(Heldd + oAttackReady, 1, bool);
			write(Heldd + oArrowBack, 1.f, float);
		}
	}
	void EokaTap() {
		if (vars::weapons::eokatap) {
			DWORD64 Heldd = read(this + oHeldEntity, DWORD64);
			write(Heldd + oSuccessFraction, 1.f, float);
			write(Heldd + oDidSparkThisFrame, true, bool);
		}
	}
};
class BaseEntity {
public:
	bool HasFlags(int Flg) {
		return (read(this + 0x2C, int) & Flg);
	}
};
class BaseHelicopter {
public:
	float GetHealth() {
		return read(this + oHealth, float);
	}
};
class BasePlayer {
public:
	Vector3 GetPosition(DWORD64 transform) {
		if (!transform) return Vector3{ 0.f, 0.f, 0.f };
		{
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
			static auto get_position = reinterpret_cast<void(__fastcall*)(DWORD64, Vector3&)>(std::uint64_t(GetModuleHandleA("UnityPlayer.dll")) + 0xDD2160); // 
			get_position(transform, pos);
			return pos;
		}
	}
	
	DWORD64 GetTransform(int bone) {
		DWORD64 player_model = read(this + 0x118, DWORD64);// public Model model;_public class BaseEntity : BaseNetworkable, IProvider, ILerpTarget, IPrefabPreProcess // TypeDefIndex: 8714
		DWORD64 boneTransforms = read(player_model + 0x48, DWORD64);//public Transform[] boneTransforms;
		DWORD64 BoneValue = read(boneTransforms + 0x20 + bone * 0x8, DWORD64);
		return read(BoneValue + 0x10, DWORD64);
	}
	ULONG64 GrabTransform(int bone) {
		DWORD64 entity_model = read(this + 0x118, DWORD64);
		DWORD64 bone_dict = read(entity_model + 0x48, DWORD64);
		DWORD64 BoneValue = read(bone_dict + 0x20 + bone * 0x8, DWORD64);
		return BoneValue;
	}
	float GetHealth() {
		return read(this + oHealth, float);
	}
	void SetFov() {
		auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x18, vars::misc::fov, float);
	}
	void PatchCamspeed() {
		auto klass = read(vars::stor::gBase + 0x29BF240, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x2C, 1.f, float);
	}
	const wchar_t* GetName() {
		pUncStr Str = ((pUncStr)(read(this + oDisplayName, DWORD64)));
		if (!Str) return L""; return Str->str;
	}
	Vector3 GetVelocity() {
		DWORD64 PlayerModel = read(this + oPlayerModel, DWORD64);
		return read(PlayerModel + oNewVelocity, Vector3);
	}
	bool HasFlags(int Flg) {
		return (read(this + oPlayerFlags, int) & Flg);
	}
	Vector3 GetBoneByID(BoneList BoneID) {
		return GetPosition(GetTransform(BoneID));
	}
	bool IsNpc() {
		DWORD64 PlayerModel = read(this + oPlayerModel, DWORD64);
		return read(PlayerModel + oIsNpc, bool);
	}
	int GetTeamSize() {
		DWORD64 ClientTeam = read(this + oClientTeam, DWORD64);
		DWORD64 members = read(ClientTeam + 0x28, DWORD64);//private ListHashSet<ILOD> members; //public PlayerInventory inventory; // 0x28 ���  public List<PlayerTeam.TeamMember> members; // 0x28
		return read(members + 0x18, DWORD64);
	}
	DWORD64 GetTeammateByPos(int Id) {
		DWORD64 ClientTeam = read(this + 0x540, DWORD64);
		DWORD64 members = read(ClientTeam + 0x30, DWORD64);
		DWORD64 List = read(members + 0x10, DWORD64);
		DWORD64 player = read(List + 0x20 + (Id * 0x8), DWORD64);
		return read(player + 0x20, DWORD64);
	}
	bool IsTeamMate(DWORD64 SteamID) {
		bool ret = false;
		for (int i = 0; i < 8; i++) {
			if (GetTeammateByPos(i) == SteamID) {
				ret = true;
				break;
			}
		}
		return ret;
	}
	bool IsDead() {
		if (!this) return true;
		return read(this + oLifeState, bool);;
	}
	bool IsSleeping() {
		if (!this) return false;
		return HasFlags(Sleeping);
	}
	DWORD64 GetSteamID() {
		return read(this + oUserID, DWORD64);
	}
	bool IsMenu() {
		if (!this) return true;
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		return !(read(Input + oKeyFocus, bool));
	}
	void SetVA(const Vector2& VA) {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		write(Input + oBodyAngles, VA, Vector2);
	}
	void AddFlag(int flag) {
		DWORD64 mstate = read(this + oModelState, DWORD64);
		int flags = read(mstate + 0x24, int);
		write(mstate + 0x24, flags |= flag, int);
	}
	void RemoveFlag(int flag) {
		DWORD64 mstate = read(this + 0x588, DWORD64);
		int flags = read(mstate + 0x24, int);
		write(mstate + 0x24, flags &= ~flag, int);
	}
	void SetRA() {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		Vector2 RA = read(Input + oRecoilAngles, Vector2);
		write(Input + oRecoilAngles, Vector2(RA.x * vars::weapons::control_x, RA.y * vars::weapons::control_x), Vector2);
	}
	Vector2 GetVA() {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		return read(Input + oBodyAngles, Vector2);
	}
	bool GetKeyState(ButtonS b) {
		DWORD64 InputState = read(read(this + oPlayerInput, DWORD64) + oState, DWORD64);
		DWORD64 Cur = read(InputState + 0x10, DWORD64);
		if (!Cur) return false;
		int btn = read(Cur + 0x14, int);
		return ((btn & (int)b) == (int)b);
	}
	Vector2 GetRA() {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		return read(Input + oRecoilAngles, Vector2);
	}
	BaseProjectile* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + oInventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64);
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (BaseProjectile*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	BaseProjectile* GetActiveWeapon() {
		int ActUID = read(this + oClActiveItem, int);
		if (!ActUID) return nullptr;
		BaseProjectile* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->GetUID())
				return ActiveWeapon;
		return nullptr;
	}
	float Time() {
		return read(this + oLastSentTickTime, float);
	}
	void FakeAdmin() {
		int Flags = read(this + oPlayerFlags, int);
		write(this + oPlayerFlags, (Flags |= 4), int);
	}
	void WalkWater() {
		DWORD64 Movement = read(this + oMovement, DWORD64);
		static bool x13C = read(Movement + 0x13C, bool);
		static float xB8 = read(Movement + 0xB8, float);
		static float x74 = read(Movement + 0x74, float);
		static float x78 = read(Movement + 0x78, float);
		//if (this->GetBoneByID(l_foot).y <= 0) {
			write(Movement + 0x130, 1, bool); // private bool grounded;
		//}
	}
	void SpiderMan() {
		INT64 Movement = read(this + oMovement, UINT64);
		write(Movement + oGroundAngle, 0.f, float);
		write(Movement + oGroundAngleNew, 0.f, float);
	}
	void NoSway() {
		write(this + oClothingAccuracyBonus, 1.f, float);
	}
	void SetGravity(float val) {
		DWORD64 Movement = read(this + oMovement, DWORD64);
		write(Movement + oGravityMultiplier, val, float);
	}
};
class ItemModProjectile {
public:
	float projectileSpread() { return read(this + 0x30, float); }
	float projectileVelocity() { return read(this + 0x34, float); }
	float projectileVelocitySpread() { return read(this + 0x38, float); }
	bool useCurve() { return read(this + 0x3C, float); }

	void projectileSpread(float a) { write(this + 0x30, a, float); }
	void projectileVelocity(float a) { write(this + 0x34, a, float); }
	void projectileVelocitySpread(float a) { write(this + 0x38, a, float); }
	void useCurve(bool a) { write(this + 0x3C, a, float); }
};
class HitTest {
public:
	Ray AttackRay() { return read(this + 0x14, Ray); }
	float Radius() { return read(this + 0x2C, float); }
	float Forgiveness() { return read(this + 0x30, float); }
	float MaxDistance() { return read(this + 0x34, float); }
	uintptr_t RayHit() { return read(this + 0x38, uintptr_t); }
	bool MultiHit() { return read(this + 0x64, bool); }
	bool BestHit() { return read(this + 0x65, bool); }
	bool DidHit() { return read(this + 0x66, bool); }
	BasePlayer* HitEntity() { return read(this + 0x88, BasePlayer*); }
};
class Projectile {
public:
	Vector3 initialVelocity() { return read(this + 0x18, Vector3); }
	float drag() { return read(this + 0x24, float); }
	float gravityModifier() { return read(this + 0x28, float); }
	float thickness() { return read(this + 0x2C, float); }
	float initialDistance() { return read(this + 0x30, float); }
	bool remainInWorld() { return read(this + 0x34, bool); }
	float stickProbability() { return read(this + 0x38, float); }
	float breakProbability() { return read(this + 0x3C, float); }
	float conditionLoss() { return read(this + 0x40, float); }
	float ricochetChance() { return read(this + 0x44, float); }
	float penetrationPower() { return read(this + 0x48, float); }
	uintptr_t damageProperties() { return read(this + 0x50, uintptr_t); }
	uintptr_t damageDistances() { return read(this + 0x58, uintptr_t); }
	uintptr_t damageMultipliers() { return read(this + 0x60, uintptr_t); }
	uintptr_t rendererToScale() { return read(this + 0x70, uintptr_t); }
	uintptr_t firstPersonRenderer() { return read(this + 0x78, uintptr_t); }
	bool createDecals() { return read(this + 0x80, bool); }
	bool doDefaultHitEffects() { return read(this + 0x81, bool); }
	uintptr_t flybySound() { return read(this + 0x88, uintptr_t); }
	float flybySoundDistance() { return read(this + 0x90, float); }
	uintptr_t closeFlybySound() { return read(this + 0x98, uintptr_t); }
	float closeFlybyDistance() { return read(this + 0xA0, float); }
	float tumbleSpeed() { return read(this + 0xA4, float); }
	Vector3 tumbleAxis() { return read(this + 0xA8, Vector3); }
	Vector3 swimScale() { return read(this + 0xB4, Vector3); }
	Vector3 swimSpeed() { return read(this + 0xC0, Vector3); }
	BasePlayer* owner() { return (BasePlayer*)read(this + 0xD0, uintptr_t); }
	uintptr_t sourceWeaponPrefab() { return read(this + 0xD8, uintptr_t); }
	uintptr_t sourceProjectilePrefab() { return read(this + 0xE0, uintptr_t); }
	ItemModProjectile* mod() { return read(this + 0xE8, ItemModProjectile*); }
	int projectileID() { return read(this + 0xF0, int); }
	uint32_t seed() { return read(this + 0xF4, uint32_t); }
	bool clientsideEffect() { return read(this + 0xF8, bool); }
	bool clientsideAttack() { return read(this + 0xF9, bool); }
	float integrity() { return read(this + 0xFC, float); }
	float maxDistance() { return read(this + 0x100, float); }
	uintptr_t modifier() { return read(this + 0x104, uintptr_t); }
	bool invisible() { return read(this + 0x114, bool); }
	Vector3 currentVelocity() { return read(this + 0x118, Vector3); }
	Vector3 currentPosition() { return read(this + 0x124, Vector3); }
	float traveledDistance() { return read(this + 0x130, float); }
	float traveledTime() { return read(this + 0x134, float); }
	float launchTime() { return read(this + 0x138, float); }
	Vector3 sentPosition() { return read(this + 0x13C, Vector3); }
	Vector3 previousPosition() { return read(this + 0x148, Vector3); }
	Vector3 previousVelocity() { return read(this + 0x154, Vector3); }
	float previousTraveledTime() { return read(this + 0x160, float); }
	bool isRicochet() { return read(this + 0x164, bool); }
	bool isRetiring() { return read(this + 0x165, bool); }
	bool flybyPlayed() { return read(this + 0x166, bool); }
	bool wasFacingPlayer() { return read(this + 0x167, bool); }
	uintptr_t flybyPlane() { return read(this + 0x168, uintptr_t); }
	Ray flybyRay() { return read(this + 0x178, Ray); }
	uintptr_t cleanupAction() { return read(this + 0x190, uintptr_t); }
	HitTest* hitTest() { return read(this + 0x198, HitTest*); }
	float swimRandom() { return read(this + 0x1A0, float); }

	void initialVelocity(Vector3 a) { write(this + 0x18, a, Vector3); }
	void drag(float a) { write(this + 0x24, a, float); }
	void gravityModifier(float a) { write(this + 0x28, a, float); }
	void thickness(float a) { write(this + 0x2C, a, float); }
	void initialDistance(float a) { write(this + 0x30, a, float); }
	void remainInWorld(bool a) { write(this + 0x34, a, bool); }
	void stickProbability(float a) { write(this + 0x38, a, float); }
	void breakProbability(float a) { write(this + 0x3C, a, float); }
	void conditionLoss(float a) { write(this + 0x40, a, float); }
	void ricochetChance(float a) { write(this + 0x44, a, float); }
	void penetrationPower(float a) { write(this + 0x48, a, float); }
	void damageProperties(uintptr_t a) { write(this + 0x50, a, uintptr_t); }
	void damageDistances(uintptr_t a) { write(this + 0x58, a, uintptr_t); }
	void damageMultipliers(uintptr_t a) { write(this + 0x60, a, uintptr_t); }
	void rendererToScale(uintptr_t a) { write(this + 0x70, a, uintptr_t); }
	void firstPersonRenderer(uintptr_t a) { write(this + 0x78, a, uintptr_t); }
	void createDecals(bool a) { write(this + 0x80, a, bool); }
	void doDefaultHitEffects(bool a) { write(this + 0x81, a, bool); }
	void flybySound(uintptr_t a) { write(this + 0x88, a, uintptr_t); }
	void flybySoundDistance(float a) { write(this + 0x90, a, float); }
	void closeFlybySound(uintptr_t a) { write(this + 0x98, a, uintptr_t); }
	void closeFlybyDistance(float a) { write(this + 0xA0, a, float); }
	void tumbleSpeed(float a) { write(this + 0xA4, a, float); }
	void tumbleAxis(Vector3 a) { write(this + 0xA8, a, Vector3); }
	void swimScale(Vector3 a) { write(this + 0xB4, a, Vector3); }
	void swimSpeed(Vector3 a) { write(this + 0xC0, a, Vector3); }
	void owner(uintptr_t a) { write(this + 0xD0, a, uintptr_t); }
	void sourceWeaponPrefab(uintptr_t a) { write(this + 0xD8, a, uintptr_t); }
	void sourceProjectilePrefab(uintptr_t a) { write(this + 0xE0, a, uintptr_t); }
	void mod(uintptr_t a) { write(this + 0xE8, a, uintptr_t); }
	void projectileID(uint32_t a) { write(this + 0xF0, a, uint32_t); }
	void seed(uint32_t a) { write(this + 0xF4, a, uint32_t); }
	void clientsideEffect(bool a) { write(this + 0xF8, a, bool); }
	void clientsideAttack(bool a) { write(this + 0xF9, a, bool); }
	void integrity(float a) { write(this + 0xFC, a, float); }
	void maxDistance(float a) { write(this + 0x100, a, float); }
	void modifier(uintptr_t a) { write(this + 0x104, a, uintptr_t); }
	void invisible(bool a) { write(this + 0x114, a, bool); }
	void currentVelocity(Vector3 a) { write(this + 0x118, a, Vector3); }
	void currentPosition(Vector3 a) { write(this + 0x124, a, Vector3); }
	void traveledDistance(float a) { write(this + 0x130, a, float); }
	void traveledTime(float a) { write(this + 0x134, a, float); }
	void launchTime(float a) { write(this + 0x138, a, float); }
	void sentPosition(Vector3 a) { write(this + 0x13C, a, Vector3); }
	void previousPosition(Vector3 a) { write(this + 0x148, a, Vector3); }
	void previousVelocity(Vector3 a) { write(this + 0x154, a, Vector3); }
	void previousTraveledTime(float a) { write(this + 0x160, a, float); }
	void isRicochet(bool a) { write(this + 0x164, a, bool); }
	void isRetiring(bool a) { write(this + 0x165, a, bool); }
	void flybyPlayed(bool a) { write(this + 0x166, a, bool); }
	void wasFacingPlayer(bool a) { write(this + 0x167, a, bool); }
	void flybyPlane(uintptr_t a) { write(this + 0x168, a, uintptr_t); }
	void flybyRay(Ray a) { write(this + 0x178, a, Ray); }
	void cleanupAction(uintptr_t a) { write(this + 0x190, a, uintptr_t); }
	void hitTest(uintptr_t a) { write(this + 0x198, a, uintptr_t); }
	void swimRandom(float a) { write(this + 0x1A0, a, float); }

	bool DoHit(uintptr_t hitTest, Vector3 point, Vector3 normal) {
		typedef bool(__stdcall* DoHitCall)(Projectile*, uintptr_t, Vector3, Vector3);
		printf("called dohit\n");
		return ((DoHitCall)(vars::stor::gBase + CO::DoHit))(this, hitTest, point, normal);
	}
	void Retire() {
		typedef void(__stdcall* Retire)(Projectile*);
		((Retire)(vars::stor::gBase + 0x2B2AE0))(this);
	}
};
Matrix4x4* pViewMatrix = nullptr;
BasePlayer* LocalPlayer = nullptr;
namespace utils {
	bool w2s(const Vector3& EntityPos, Vector2& ScreenPos) {
		if (!pViewMatrix) return false;
		Vector3 TransVec = Vector3(pViewMatrix->_14, pViewMatrix->_24, pViewMatrix->_34);
		Vector3 RightVec = Vector3(pViewMatrix->_11, pViewMatrix->_21, pViewMatrix->_31);
		Vector3 UpVec = Vector3(pViewMatrix->_12, pViewMatrix->_22, pViewMatrix->_32);
		float w = Math::Dot(TransVec, EntityPos) + pViewMatrix->_44;
		if (w < 0.098f) return false;
		float y = Math::Dot(UpVec, EntityPos) + pViewMatrix->_42;
		float x = Math::Dot(RightVec, EntityPos) + pViewMatrix->_41;
		ScreenPos = Vector2((vars::stuff::ScreenWidth / 2) * (1.f + x / w), (vars::stuff::ScreenHeight / 2) * (1.f - y / w));
		return true;
	}
	Vector3 GetEntityPosition(std::uint64_t entity) {
		uintptr_t plyVis = read(entity + 0x8, uintptr_t); if (!plyVis) return { 0,0,0 };
		uintptr_t visualState = read(plyVis + 0x38, uintptr_t); if (!visualState) return { 0,0,0 };
		return read(visualState + 0x90, Vector3);
	}
	Vector3 ClosestPoint(BasePlayer* player, Vector3 vec) {
		typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
		Vector3 result = ((CPoint)(vars::stor::gBase + CO::utils::ClosestPoint))(player, vec);
		return result;
	}
	Vector3 GetWorldVelocity(uintptr_t entity) {
		typedef Vector3(__stdcall* GetWorldVelocity)(uintptr_t);
		Vector3 result = ((GetWorldVelocity)(vars::stor::gBase + CO::utils::GetWorldVelocity))(entity);
		return result;
	}
	Vector3 TransformToPoint(DWORD64 Transform, Vector3 CurPos) {
		typedef Vector3(__stdcall* ITP)(DWORD64, Vector3);
		Vector3 result = ((ITP)(vars::stor::gBase + CO::utils::InverseTransformPoint))(Transform, CurPos);
		return result;
	}
	bool LineOfSight(Vector3 a, Vector3 b) {
		typedef bool(__stdcall* LOS)(Vector3, Vector3, int, float);
		bool result = ((LOS)(vars::stor::gBase + CO::utils::LineOfSight))(a, b, 2162688 | 8388608, 0.f);
		return result;
	}
	DWORD64 FindBone(DWORD64 TargetEntity, Str TargetBone) {
		typedef DWORD64(__stdcall* FindBone)(DWORD64, Str);
		DWORD64 result = ((FindBone)(vars::stor::gBase + CO::utils::FindBone))(TargetEntity, TargetBone);
		return result;
	}
	DWORD64 GetTransform(DWORD64 entity) {
		typedef DWORD64(__stdcall* GetTransform)(DWORD64);
		DWORD64 result = ((GetTransform)(vars::stor::gBase + CO::get_transform))(entity);
		return result;
	}
	uintptr_t ShaderFind(Str name) {
		typedef uintptr_t(__stdcall* ShaderFind)(Str);
		uintptr_t result = ((ShaderFind)(vars::stor::gBase + CO::ShaderFind))(name);
		return result;
	}
	namespace StringPool {
		uint32_t Get(Str str) {
			typedef uint32_t(__stdcall* Get)(Str);
			uint32_t result = ((Get)(vars::stor::gBase + CO::utils::StringPool::Get))(str);
			return result;
		}
	}
}
