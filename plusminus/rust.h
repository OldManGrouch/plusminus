using ptr_t = uint64_t;
enum UnmanagedCallingConvention {
	UnmanagedCdecl,
	UnmanagedStdcall,
	UnmanagedFastcall,
};

template<typename t_Function>
class UnmanagedPointer {
public:

	template<typename... t_FunctionParameters>
	auto operator()(t_FunctionParameters... params) {
		using result_type = decltype(std::declval<t_Function>()(std::declval<t_FunctionParameters>()...));
		using function_cdecl_ptr_t = result_type(__cdecl*)(t_FunctionParameters...);
		using function_stdcall_ptr_t = result_type(__stdcall*)(t_FunctionParameters...);
		using function_fastcall_ptr_t = result_type(_fastcall*)(t_FunctionParameters...);

		switch (this->m_CallingConvention) {
		case UnmanagedCdecl:
			return reinterpret_cast<function_cdecl_ptr_t>(this->m_Address)(params...);
		case UnmanagedStdcall:
			return reinterpret_cast<function_stdcall_ptr_t>(this->m_Address)(params...);
		case UnmanagedFastcall:
			return reinterpret_cast<function_fastcall_ptr_t>(this->m_Address)(params...);
		}
	}

	UnmanagedPointer(ptr_t dwAddress, UnmanagedCallingConvention unmCallingConvention) {
		this->m_Address = dwAddress;
		this->m_CallingConvention = unmCallingConvention;
	}
private:
	ptr_t m_Address;
	UnmanagedCallingConvention m_CallingConvention;
};

#define STATIC_FUNCTION(method_path,name,ta) static inline UnmanagedPointer<ta> name = { METHOD(method_path), UnmanagedStdcall }
class ItemModProjectile {
public:
	FIELD("Assembly-CSharp::ItemModProjectile::numProjectiles", numProjectiles, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocitySpread", projectileVelocitySpread, float);
	float GetRandomVelocity() {
		typedef float(__fastcall* randomvelocity)(ItemModProjectile*);
		return ((randomvelocity)(vars::stor::gBase + CO::GetRandomVelocity))(this);
	}
};
class BaseEntity {
public:
	bool isClient() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_isClient(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(uintptr_t)>(off)((uintptr_t)this);
	}
	Vector3 GetWorldVelocity() {
		if (!this) return Vector3(0.f, 0.f, 0.f);
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetWorldVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
};
class RenderSettings {
public:
	enum class AmbientMode {
		Skybox,
		Trilight,
		Flat,
		Custom
	};
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientMode(Rendering.AmbientMode): Void", set_ambientMode, void(AmbientMode));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientIntensity(Single): Void", set_ambientIntensity, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientLight(Color): Void", set_ambientLight, void(Color));
};
class BaseCombatEntity : public BaseEntity {
public:
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
	FIELD("Assembly-CSharp::BaseCombatEntity::_health", health, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
};
class Type {
public:
	static Type* GetType() {
		static auto off = METHOD("mscorlib::System::Type::GetType(String): Type");

		return reinterpret_cast<Type * (__cdecl*)(Str)>(off)(Str(L"ItemModProjectile, Assembly-CSharp"));
	}
};
class Component {
public:
	template<typename T = Component>
	T* GetComponent(Type* type) {
		if (!this || !type) return nullptr;

		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponent(Type): Component");

		return reinterpret_cast<T * (__fastcall*)(Component*, Type*)>(off)(this, type);
	}
};
class ItemDefinition : public Component {
public:
	FIELD("Assembly-CSharp::ItemDefinition::itemid", itemid, int);
};
class BaseProjectile /*: public AttackEntity*/ {
public:
	class Magazine {
	public:
		FIELD("Assembly-CSharp::Magazine::ammoType", ammoType, ItemDefinition*);
	};
	FIELD("Assembly-CSharp::BaseProjectile::primaryMagazine", primaryMagazine, Magazine*);
	FIELD("Assembly-CSharp::BaseProjectile::projectileVelocityScale", projectileVelocityScale, float);
};

class DamageTypeList {
public:
	enum class DamageType {
		Generic,
		Hunger,
		Thirst,
		Cold,
		Drowned,
		Heat,
		Bleeding,
		Poison,
		Suicide,
		Bullet,
		Slash,
		Blunt,
		Fall,
		Radiation,
		Bite,
		Stab,
		Explosion,
		RadiationExposure,
		ColdExposure,
		Decay,
		ElectricShock,
		Arrow,
		AntiVehicle,
		Collision,
		Fun_Water,
		LAST
	};
	float Total() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Rust::DamageTypeList::Total(): Single");
		return reinterpret_cast<float(__fastcall*)(DamageTypeList*)>(off)(this);
	}
};
class HitInfo {
public:
	FIELD("Assembly-CSharp::HitInfo::Initiator", Initiator, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::WeaponPrefab", WeaponPrefab, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::DoHitEffects", DoHitEffects, bool);
	FIELD("Assembly-CSharp::HitInfo::DoDecals", DoDecals, bool);
	FIELD("Assembly-CSharp::HitInfo::IsPredicting", IsPredicting, bool);
	FIELD("Assembly-CSharp::HitInfo::UseProtection", UseProtection, bool);
	FIELD("Assembly-CSharp::HitInfo::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitInfo::HitEntity", HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::HitBone", HitBone, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitMaterial", HitMaterial, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPositionWorld", HitPositionWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitPositionLocal", HitPositionLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalWorld", HitNormalWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalLocal", HitNormalLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointStart", PointStart, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointEnd", PointEnd, Vector3);
	FIELD("Assembly-CSharp::HitInfo::ProjectileID", ProjectileID, int);
	FIELD("Assembly-CSharp::HitInfo::ProjectileDistance", ProjectileDistance, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileVelocity", ProjectileVelocity, Vector3);
	FIELD("Assembly-CSharp::HitInfo::damageTypes", damageTypes, DamageTypeList*);
};
class PlayerEyes {
public:
	Quaternion get_rotation() {
		typedef Quaternion(__stdcall* get_rotation)(PlayerEyes*);
		Quaternion result = ((get_rotation)(vars::stor::gBase + CO::get_rotation))(this);
		return result;
	}
};
class BasePlayer : public BaseCombatEntity {
public:
	PlayerEyes* eyes() { return read(this + 0x600, PlayerEyes*); }

	void SetVA(const Vector2& VA) {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		write(Input + oBodyAngles, VA, Vector2);
	}
	Vector2 GetVA() {
		DWORD64 Input = read(this + oPlayerInput, DWORD64);
		return read(Input + oBodyAngles, Vector2);
	}
	Vector3 GetVelocity() {
		DWORD64 PlayerModel = read(this + oPlayerModel, DWORD64);
		return read(PlayerModel + oNewVelocity, Vector3);
	}
	float GetHealth() {
		return this->health();
	}
	bool IsNpc() {
		DWORD64 PlayerModel = read(this + oPlayerModel, DWORD64);
		return read(PlayerModel + 0x2C0, bool);
	}
	DWORD64 GetSteamID() {
		return read(this + oUserID, DWORD64);
	}
	Quaternion GetRotation(DWORD64 transform) {
		if (!transform) return Quaternion{ 0.f, 0.f, 0.f, 0.0f };
		{
			Quaternion pos = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			static auto get_rotation = reinterpret_cast<void(__fastcall*)(DWORD64, Quaternion&)>(std::uint64_t(GetModuleHandleA("UnityPlayer.dll")) + 0xDD22A0); // 
			get_rotation(transform, pos);
			return pos;
		}
	}
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
	
	
	void SetFov(float val) {
		auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x18, val, float);
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
	Vector3 get_bone_pos(BoneList BoneID) {
		return GetPosition(GetTransform(BoneID));
	}
	Quaternion get_bone_rot(BoneList BoneID) {
		return GetRotation(GetTransform(BoneID));
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
		DWORD64 Movement = read(this + oMovement, DWORD64);
		write(Movement + oGroundAngle, 0.f, float);
		write(Movement + oGroundAngleNew, 0.f, float);
	}
	void SetGravity(float val) {
		DWORD64 Movement = read(this + oMovement, DWORD64);
		write(Movement + oGravityMultiplier, val, float);
	}
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
	uintptr_t mod() { return read(this + 0xE8, uintptr_t); }
	uint32_t projectileID() { return read(this + 0xF0, uint32_t); }
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
	uintptr_t hitTest() { return read(this + 0x198, uintptr_t); }
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
	BaseEntity* HitEntity() { return read(this + 0x88, BaseEntity*); }
	Str* HitMaterial() { return read(this + 0xC0, Str*); }
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
		bool result = ((LOS)(vars::stor::gBase + CO::utils::LineOfSight))(a, b, 2162688 | 8388608 | 2097152, 0.f);
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
