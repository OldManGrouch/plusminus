
namespace CO {
	auto GetYawClamp = 0x2EDD60;
	auto GetPitchClamp = 0x2EDD30;
	auto Play = 0x48A2E0; // ViewModel
	auto DoAttack = 0x76F300; // BaseProjectile->
	auto get_frameCount = 0x1F70130;
	auto GetRandomVelocity = 0x4DEFA0;
	auto Client = 0x2FC3DF0; // ConVar.Client_TypeInfo
	auto CreateEffect = 0x872EA0;
	auto UpgradeToGrade = 0x462B70;
	auto CreateOrUpdateEntity = 0x6DDC70;
	auto AddPunch = 0x514AA0;
	auto MoveTowards = 0x1F76B60;
	auto Jump = 0xB36A50;
	auto Total = 0x3D45B0;
	auto IsDucked = 0x302720;
	auto PropertyToId = 0x1831DC0;
	auto VisUpdateUsingCulling = 0x311FE0;
	auto SetInt = 0x1742C30;
	auto SetColor = 0x1742840;
	auto get_shader = 0x17436A0;
	auto get_material = 0x182FAF0;
	auto get_Renderers = 0x3F07C0;
	auto ShaderFind = 0x1831CA0;
	auto OnLand = 0x304E60; // BasePlayer->OnLand
	auto get_position = 0x6C44F0; // playereyes->get_position
	auto IsBeingHacked = 0x2E1340;
	auto IsFullyHacked = 0x2E1B90;
	auto ForceToPos = 0x2FD9D0;
	auto UpdateAmbient = 0xC3ABB0; // protected void UpdateAmbient() { } || TOD_Sky
	auto set_rayleigh = 0x7FEDD0;
	auto BasePlayer = 0x2FC4408; // BasePlayer_TypeInfo
	auto AssistPlayer = 0x3047A0; // public void Menu_AssistPlayer(BasePlayer player) { }
	auto Launch = 0x53A0C0; // internal void Launch() { }
	auto KnockDoor = 0x86AC70; // public void Menu_KnockDoor(BasePlayer player) { }
	auto OpenDoor = 0x86ACF0; // public void Menu_OpenDoor(BasePlayer player) { }
	auto OpenHatch = 0x86AD40; // public void Menu_ToggleHatch(BasePlayer player) { }
	auto IsHidden = 0x2EC610; // public class StashContainer : StorageContainer
	auto get_isHeadshot = 0x51A050; // public bool get_isHeadshot() { }
	auto DoHitNotify = 0x3C2530; // public void DoHitNotify(HitInfo info) { }
	auto GetSkinColor = 0x43B120; // internal Color GetSkinColor(float skinNumber) { }
	auto StartAttackCooldown = 0x3B7CD0; // protected void StartAttackCooldown(float cooldown) { }
	auto ProcessAttack = 0x2E9A20; // protected virtual void ProcessAttack(HitTest hit) { }
	auto get_transform = 0x172F550; // public Transform get_transform() { } | UnityEngine::Component
	auto HitTest = 0x2FC3670; // HitTest_TypeInfo
	auto get_time = 0x1F70250; // public static float get_time() { }
	auto ServerRPC = 0x3CEE10;
	auto TraceAll = 0x93DD30; // public static void TraceAll(HitTest test, List<TraceInfo> traces, int layerMask = -5) { }
	auto BaseNetworkable = 0x2FC3FC8; // BaseNetworkable_TypeInfo
	auto SendProjectileAttack = 0x30E270; // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	auto GetModifiedAimConeDirection = 0x9159C0; // public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
	auto set_flying = 0x1C58240; // public void set_flying(bool value) { } 
	auto CanAttack = 0x2F6A10; // public bool CanAttack() { }
	auto SendClientTick = 0x30DBB0; // internal void SendClientTick() { }
	auto HandleRunning = 0xB367C0; // private void HandleRunning(ModelState state, bool wantsRun) { }
	auto HandleJumping = 0xB366A0;
	auto CreateProjectile = 0x76F160; // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	auto CanHoldItems = 0x2ED150; // public virtual bool CanHoldItems() { }
	auto Run = 0x204C360; // public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	auto DoMovement = 0x538600; // private void DoMovement(float deltaTime) { }
	auto DoHit = 0x537EF0; // private bool DoHit(HitTest test, Vector3 point, Vector3 normal) { }
	auto ClientInput = 0x2F8660; // internal virtual void ClientInput(InputState state) { }
	auto ConvarGraphics = 0x2FC2CF8; // ConVar.Graphics_TypeInfo
	auto TODSky = 0x2FC61F8;// TOD_Sky_TypeInfo
	namespace utils {
		auto ClosestPoint = 0x3C5C60; // public Vector3 ClosestPoint(Vector3 position) { }
		auto GetWorldVelocity = 0x3C9D10; // public Vector3 GetWorldVelocity() { }
		auto InverseTransformPoint = 0x1F71780; // public Vector3 InverseTransformPoint(Vector3 position) { }
		auto LineOfSight = 0x503110; // public static bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask, float padding = 0) { }
		auto FindBone = 0x3C6F90; // public virtual Transform FindBone(string strName) { }
		namespace StringPool {
			auto Get = 0x8EECB0; // public static uint Get(string str) { }
		}
	}
	void init() {

	}
}
namespace COS {
	auto GetYawClamp = 0x2EDD60;
	auto GetPitchClamp = 0x2EDD30;
	auto Play = 0x48A2E0; // ViewModel
	auto get_frameCount = 0x1F70950;
	auto GetRandomVelocity = 0x4DEFA0;
	auto Client = 0x2FC3E30; // ConVar.Client_TypeInfo
	auto CreateEffect = 0x8736C0;
	auto UpgradeToGrade = 0x462B70;
	auto CreateOrUpdateEntity = 0x6DE490;
	auto AddPunch = 0x514AA0;
	auto MoveTowards = 0x1F77380;
	auto Jump = 0xB37270;
	auto Total = 0x3D45B0;
	auto IsDucked = 0x302720;
	auto PropertyToId = 0x18325E0;
	auto VisUpdateUsingCulling = 0x311FE0;
	auto SetInt = 0x1743450;
	auto SetColor = 0x1743060;
	auto get_shader = 0x1743EC0;
	auto get_material = 0x1830310;
	auto get_Renderers = 0x3F07C0;
	auto ShaderFind = 0x18324C0;
	auto OnLand = 0x304E60; // BasePlayer->OnLand
	auto get_position = 0x6C4D10; // playereyes->get_position
	auto IsBeingHacked = 0x2E1340;
	auto IsFullyHacked = 0x2E1B90;
	auto ForceToPos = 0x2FD9D0;
	auto UpdateAmbient = 0xC3B3D0; // protected void UpdateAmbient() { } || TOD_Sky
	auto set_rayleigh = 0x7FF5F0;
	auto BasePlayer = 0x2FC4448; // BasePlayer_TypeInfo
	auto AssistPlayer = 0x3047A0; // public void Menu_AssistPlayer(BasePlayer player) { }
	auto Launch = 0x53A0C0; // internal void Launch() { }
	auto KnockDoor = 0x86B490; // public void Menu_KnockDoor(BasePlayer player) { }
	auto OpenDoor = 0x86B510; // public void Menu_OpenDoor(BasePlayer player) { }
	auto OpenHatch = 0x86B560; // public void Menu_ToggleHatch(BasePlayer player) { }
	auto IsHidden = 0x2EC610; // public class StashContainer : StorageContainer
	auto get_isHeadshot = 0x51A050; // public bool get_isHeadshot() { }
	auto DoHitNotify = 0x3C2530; // public void DoHitNotify(HitInfo info) { }
	auto GetSkinColor = 0x43B120; // internal Color GetSkinColor(float skinNumber) { }
	auto StartAttackCooldown = 0x3B7CD0; // protected void StartAttackCooldown(float cooldown) { }
	auto ProcessAttack = 0x2E9A20; // protected virtual void ProcessAttack(HitTest hit) { }
	auto get_transform = 0x172FD70; // public Transform get_transform() { } | UnityEngine::Component
	auto HitTest = 0x2FC36B0; // HitTest_TypeInfo
	auto get_time = 0x1F70A70; // public static float get_time() { }
	auto ServerRPC = 0x3CEE10;
	auto TraceAll = 0x93E550; // public static void TraceAll(HitTest test, List<TraceInfo> traces, int layerMask = -5) { }
	auto BaseNetworkable = 0x2FC4010; // BaseNetworkable_TypeInfo
	auto SendProjectileAttack = 0x30E270; // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	auto GetModifiedAimConeDirection = 0x9161E0; // public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
	auto set_flying = 0x1C58A60; // public void set_flying(bool value) { } 
	auto CanAttack = 0x2F6A10; // public bool CanAttack() { }
	auto SendClientTick = 0x30DBB0; // internal void SendClientTick() { }
	auto HandleRunning = 0xB36FE0; // private void HandleRunning(ModelState state, bool wantsRun) { }
	auto HandleJumping = 0xB36EC0;
	auto CreateProjectile = 0x76F980; // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	auto CanHoldItems = 0x2ED150; // public virtual bool CanHoldItems() { }
	auto Run = 0x204CB80; // public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	auto DoMovement = 0x538600; // private void DoMovement(float deltaTime) { }
	auto DoHit = 0x537EF0; // private bool DoHit(HitTest test, Vector3 point, Vector3 normal) { }
	auto ClientInput = 0x2F8660; // internal virtual void ClientInput(InputState state) { }
	auto ConvarGraphics = 0x2FC2D38; // ConVar.Graphics_TypeInfo
	namespace utils {
		auto ClosestPoint = 0x3C5C60; // public Vector3 ClosestPoint(Vector3 position) { }
		auto GetWorldVelocity = 0x3C9D10; // public Vector3 GetWorldVelocity() { }
		auto InverseTransformPoint = 0x1F71FA0; // public Vector3 InverseTransformPoint(Vector3 position) { }
		auto LineOfSight = 0x503110; // public static bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask, float padding = 0) { }
		auto FindBone = 0x3C6F90; // public virtual Transform FindBone(string strName) { }
		namespace StringPool {
			auto Get = 0x8EF4D0; // public static uint Get(string str) { }
		}
	}
	void init() {

	}
}
#pragma once
#define oState 0x20//public InputState state;
#define oPlayerInput 0x4C8// public PlayerInput input;
#define oModelState 0x588// public ModelState modelState;
#define oPlayerModel 0x4A8// public PlayerModel playerModel;
#define oIsNpc 0x2C0// private bool <IsNpc>k__BackingField;
#define oPlayerFlags 0x5F8// public BasePlayer.PlayerFlags playerFlags;
#define oUserID 0x640// public ulong userID;
#define oDisplayName 0x658// protected string _displayName
#define oClientTickInterval 0x5C8// public float clientTickInterval;
#define oClActiveItem 0x570// private uint clActiveItem; 
#define oInventory 0x608// public PlayerInventory inventory;
#define oMovement 0x4D0// public BaseMovement movement;
#define oThickness 0x2C// public float thickness;
#define oInstances 0x0// private static List<TOD_Sky> instances;
#define oCycle 0x38// public TOD_CycleParameters Cycle;
#define oHour 0x10// public float Hour;
#define oGroundAngle 0xB4// private float groundAngle;
#define oGroundAngleNew 0xB8// private float groundAngleNew;
#define oGravityMultiplier 0x74// public float gravityMultiplier;
#define oFlying 0x13C// private bool flying;
#define oGravityMultiplierSwimming 0x78// public float gravityMultiplierSwimming;
#define oShortname 0x20// public string shortname;
#define oDisplayname 0x28// public Translate.Phrase displayName;
#define oID 0x18// public int itemid;
#define oUID 0x28// public uint uid;
#define oItemDefinition 0x20// public ItemDefinition info;
#define oHeldEntity 0x98// private EntityRef heldEntity;
#define oSmoothVelocity 0x1FC// private Vector3 newVelocity
#define oVisible 0x248// internal bool visible;
#define oPrimaryMagazine 0x2A0// public BaseProjectile.Magazine primaryMagazine;
#define oNetworkable 0x50// public Networkable net;
#define oPunches 0x148// protected List<HeldEntity.PunchEntry> _punches;
#define oNetworkId 0x10//public uint ID;
#define oAttack 0x18// public Attack attack;
#define oHitID 0x2C// public uint hitID;
#define oHitPartID 0x64// public uint hitPartID;
#define oSuccessFraction 0x340// public float successFraction;
#define oDidSparkThisFrame 0x350// private bool _didSparkThisFrame;
#define oHitBone 0x30// public uint hitBone;  ?//HitInfo 
#define oHitMaterialID 0x68// public uint hitMaterialID;
#define oPlayerAttack 0x18// public PlayerAttack playerAttack;
#define oAttack 0x18// public Attack attack;
#define oRepeatDelay 0x1DC// public float repeatDelay;
#define oHitNormalWorld 0x4C// public Vector3 hitNormalWorld; ?//public class Attack : IDisposable, Pool.IPooled, IProto 
#define oLifeState 0x204// public BaseCombatEntity.LifeState lifestate; 
#define oHealth 0x20C// private float _health;
#define oKeyFocus 0x94// private bool hasKeyFocus;
#define oBodyAngles 0x3C// private Vector3 bodyAngles;
#define oStancePenalty 0x304//private float stancePenalty;
#define oAimconePenalty 0x308//private float aimconePenalty;
#define oAimCone 0x2D0//public float aimCone;
#define oHipAimCone 0x2D4//public float hipAimCone;
#define oAimconePenaltyPerShot 0x2D8//public float aimconePenaltyPerShot;
#define oRecoil 0x2C0 // public RecoilProperties recoil;
#define oRecoilYawMin 0x18 // public float recoilYawMin;
#define oRecoilYawMax 0x1C // public float recoilYawMax;
#define oRecoilPitchMin 0x20 // public float recoilPitchMin;
#define oRecoilPitchMax 0x24 // public float recoilPitchMax;
#define oADSScale 0x30 // public float ADSScale; 
#define oMovementPenalty 0x34 // public float movementPenalty;
#define oAutomatic 0x270 // public bool automatic;
#define oSuccessFraction 0x340 // public float successFraction;
#define oAttackReady 0x340 // protected bool attackReady;
#define oArrowBack 0x344 // private float arrowBack;
#define oHornOrigin 0x1C8 // public GameObject hornOrigin;
#define oMaxDistance 0x278 // public float maxDistance;
#define oAttackRadius 0x27C//public float attackRadius;
#define oBlockSprintOnAttack 0x281//public bool blockSprintOnAttack;
#define oNewVelocity 0x1FC // private Vector3 newVelocity;
#define oLastSentTickTime 0x5CC // private float lastSentTickTime;
#define oClientTeam 0x540 // public PlayerTeam clientTeam
#define oRecoilAngles 0x64// public Vector3 recoilAngles;
#define oInventory 0x608// public PlayerInventory inventory;
#define oClothingAccuracyBonus 0x6BC// public float clothingAccuracyBonus;