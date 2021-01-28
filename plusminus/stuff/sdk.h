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
enum class BuildingGrade {
	None = -1,
	Twigs,
	Wood,
	Stone,
	Metal,
	TopTier,
	Count
};
typedef struct _UncStr {
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;
class ConsoleOptions {
public:
	bool IsFromServer() { return read(this + 0x6, bool); }
};
class Item {
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
	uint32_t ClassNameHash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
	int LoadedAmmo() {
		const auto Held = read(this + oHeldEntity, DWORD64);
		if (Held <= 0) return 0;
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
class BaseHelicopter {
public:
	float GetHealth() {
		return read(this + oHealth, float);
	}
};