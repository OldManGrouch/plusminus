class ItemModProjectile {
public:
	FIELD("Assembly-CSharp::ItemModProjectile::projectileSpread", projectileSpread, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocitySpread", projectileVelocitySpread, float);
};
class PlayerInput {
public:
	FIELD("Assembly-CSharp::PlayerInput::bodyAngles", bodyAngles, Vector2);
};
class Projectile {
public:
	FIELD("Assembly-CSharp::Projectile::gravityModifier", gravityModifier, float);
	FIELD("Assembly-CSharp::Projectile::thickness", thickness, float);
	FIELD("Assembly-CSharp::Projectile::mod", mod, ItemModProjectile*);
	FIELD("Assembly-CSharp::Projectile::ricochetChance", ricochetChance, float);
	FIELD("Assembly-CSharp::Projectile::invisible", invisible, bool);
	FIELD("Assembly-CSharp::Projectile::currentPosition", currentPosition, Vector3);
};
class BaseMovement {
public:
	FIELD("Assembly-CSharp::BaseMovement::bodyAngles", bodyAngles, Vector2);
};
class PlayerWalkMovement : public BaseMovement {
public:
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngle", groundAngle, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngleNew", groundAngleNew, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::gravityMultiplier", gravityMultiplier, float);
};
class Object {
public:
};
class Component : public Object {
public:
};
class BaseNetworkable : public Component {
public:
};
class BaseEntity : public BaseNetworkable {

public:
};
class BaseCombatEntity : public BaseEntity {
public:
	FIELD("Assembly-CSharp::BaseCombatEntity::_health", health, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
};
class BaseHelicopter : public BaseCombatEntity {
public:

};
class PlayerModel {
public:
	FIELD("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField", IsNpc, bool);
	FIELD("Assembly-CSharp::PlayerModel::newVelocity", NewVelocity, Vector3);
	Vector3 newVelocity() {
		if (!this) return Vector3(0.f, 0.f, 0.f);
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::newVelocity");
		return *reinterpret_cast<Vector3*>(this + off);
	}
	bool isNpc() {
		if (!this) return false;
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}
};
class BasePlayer : public BaseCombatEntity {
public:
	FIELD("Assembly-CSharp::BasePlayer::userID", userID, uint64_t);
	FIELD("Assembly-CSharp::BasePlayer::input", input, PlayerInput*);
	FIELD("Assembly-CSharp::BasePlayer::movement", movement, PlayerWalkMovement*);
	FIELD("Assembly-CSharp::BasePlayer::playerModel", playerModel, PlayerModel*);
	Vector3 GetPosition(DWORD64 transform) {
		if (!transform) return Vector3{ 0.f, 0.f, 0.f };
		{
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
			static auto get_position = reinterpret_cast<void(__fastcall*)(DWORD64, Vector3&)>(std::uint64_t(GetModuleHandleA("UnityPlayer.dll")) + 0xDD2160); // 
			get_position(transform, pos);
			return pos;
		}
	}
	typedef Quaternion(__stdcall* get_rotation)(DWORD64);
	Quaternion GetRotation(DWORD64 transform) {
		if (!transform) return Quaternion();
		get_rotation original = (get_rotation)(vars::stor::gBase + CO::get_rotation);
		Quaternion res = original(transform);
		return res;
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
	const char* ClassName() {
		if (!this) return "";
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	bool IsPlayer() {
		if (!this) return false;

		return !strcmp(this->ClassName(), xorstr("BasePlayer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayerApex")) ||
			!strcmp(this->ClassName(), xorstr("NPCMurderer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayer")) ||
			!strcmp(this->ClassName(), xorstr("HumanNPC")) ||
			!strcmp(this->ClassName(), xorstr("Scientist")) ||
			!strcmp(this->ClassName(), xorstr("HTNPlayer"));
	}
	void SetFov() {
		auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x18, vars::misc::fov, float);
	}
	void PatchCamspeed() {
		auto klass = read(vars::stor::gBase + CO::Client, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x2C, 1.f, float);
	}
	const wchar_t* GetName() {
		pUncStr Str = ((pUncStr)(read(this + oDisplayName, DWORD64)));
		if (!Str) return L""; return Str->str;
	}
	bool HasFlags(int Flg) {
		return (read(this + oPlayerFlags, int) & Flg);
	}
	Vector3 GetBoneByID(BoneList BoneID) {
		return GetPosition(GetTransform(BoneID));
	}
	Quaternion GetRotationByID(BoneList BoneID) {
		return GetRotation(GrabTransform(BoneID));
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
	
	bool IsMenu() {
		if (!this) return true;
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		return !(read(Input + oKeyFocus, bool));
	}
	void AddFlag(int flag) {
		DWORD64 mstate = read(this + oModelState, DWORD64);
		int flags = read(mstate + 0x24, int);
		write(mstate + 0x24, flags |= flag, int);
	}
	void RemoveFlag(int flag) {
		DWORD64 mstate = read(this + 0x588, DWORD64);
		int flags = read(mstate + 0x24, int);
		write(mstate + 0x24, flags &= flag, int);
	}
	bool GetKeyState(ButtonS b) {
		DWORD64 InputState = read(read(this + oPlayerInput, DWORD64) + oState, DWORD64);
		DWORD64 Cur = read(InputState + 0x10, DWORD64);
		if (!Cur) return false;
		int btn = read(Cur + 0x14, int);
		return ((btn & (int)b) == (int)b);
	}
	Item* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + oInventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64); // containerBelt
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	Item* GetClothesInfo(int Id) {
		DWORD64 Inventory = read(this + oInventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x30, DWORD64); // containerWear
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	Item* GetActiveWeapon() {
		int ActUID = read(this + oClActiveItem, int);
		if (!ActUID) return nullptr;
		Item* ActiveWeapon;
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
	void SpiderMan() {
		this->movement()->groundAngle() = 0.f;
		this->movement()->groundAngleNew() = 0.f;
	}
	void SetGravity(float val) {
		this->movement()->gravityMultiplier() = val;
	}
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
