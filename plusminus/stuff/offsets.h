
namespace CO {
	auto PropertyToId = 0x14DFB10;
	auto set_grassDistance = 0x667AB0;
	auto VisUpdateUsingCulling = 0x2AA2E0;
	auto SetInt = 0x1398010;
	auto SetColor = 0x1397C20;
	auto get_shader = 0x1398A80;
	auto get_material = 0x14DD870;
	auto get_Renderers = 0x324770;
	auto ShaderFind = 0x14DF9F0;
	auto OnLand = 0x29D0B0; // BasePlayer->OnLand
	auto get_position = 0x6237E0; // playereyes->get_position
	auto IsBeingHacked = 0x2FB350;
	auto IsFullyHacked = 0x417CC0;
	auto ForceToPos = 0x295E30;
	auto LateUpdate = 0xA1F340; // protected void LateUpdate() { } || TOD_Sky
	auto set_rayleigh = 0x673C80;
	auto BasePlayer = 0x29BF798; // BasePlayer_TypeInfo
	auto AssistPlayer = 0x29C9F0; // public void Menu_AssistPlayer(BasePlayer player) { }
	auto Launch = 0x2B1F00; // internal void Launch() { }
	auto KnockDoor = 0x463850; // public void Menu_KnockDoor(BasePlayer player) { }
	auto OpenDoor = 0x4638D0; // public void Menu_OpenDoor(BasePlayer player) { }
	auto OpenHatch = 0x463920; // public void Menu_ToggleHatch(BasePlayer player) { }
	auto IsHidden = 0x284A60; // public class StashContainer : StorageContainer
	auto get_isHeadshot = 0x41F690; // public bool get_isHeadshot() { }
	auto DoHitNotify = 0x2E7C20; // public void DoHitNotify(HitInfo info) { }
	auto GetSkinColor = 0x348E60; // internal Color GetSkinColor(float skinNumber) { }
	auto StartAttackCooldown = 0x2DD660; // protected void StartAttackCooldown(float cooldown) { }
	auto ProcessAttack = 0x281E70; // protected virtual void ProcessAttack(HitTest hit) { }
	auto get_transform = 0x145E370; // public Transform get_transform() { } | UnityEngine::Component
	auto HitTest = 0x29BEE10; // HitTest_TypeInfo
	auto get_time = 0x14E8310; // public static float get_time() { }
	auto ServerRPC = 0x2F4310;
	auto TraceAll = 0x5F33D0; // public static void TraceAll(HitTest test, List<TraceInfo> traces, int layerMask = -5) { }
	auto BaseNetworkable = 0x29BF3E0; // BaseNetworkable_TypeInfo
	auto SendProjectileAttack = 0x2A6510; // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	auto GetModifiedAimConeDirection = 0x788A40; // public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
	auto set_flying = 0x17DCEB0; // public void set_flying(bool value) { } 
	auto CanAttack = 0x28EE70; // public bool CanAttack() { }
	auto SendClientTick = 0x2A5E50; // internal void SendClientTick() { }
	auto HandleRunning = 0x6CDD10; // private void HandleRunning(ModelState state, bool wantsRun) { }
	auto HandleJumping = 0x6CDBF0;
	auto CreateProjectile = 0x58A450; // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	auto CanHoldItems = 0x2855A0; // public virtual bool CanHoldItems() { }
	auto Run = 0x1B88400; // public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	auto DoMovement = 0x2B0440; // private void DoMovement(float deltaTime) { }
	auto DoHit = 0x2AFD30; // private bool DoHit(HitTest test, Vector3 point, Vector3 normal) { }
	auto ClientInput = 0x290AC0; // internal virtual void ClientInput(InputState state) { }
	auto ConvarGraphics = 0x29BE5D0; // ConVar.Graphics_TypeInfo
	auto TODSky = 0x29C1238;// TOD_Sky_TypeInfo
	namespace utils {
		auto ClosestPoint = 0x2EB360; // public Vector3 ClosestPoint(Vector3 position) { }
		auto GetWorldVelocity = 0x2EF410; // public Vector3 GetWorldVelocity() { }
		auto InverseTransformPoint = 0x1AB1E50; // public Vector3 InverseTransformPoint(Vector3 position) { }
		auto LineOfSight = 0x3B73C0; // public static bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask, float padding = 0) { }
		auto FindBone = 0x2EC690; // public virtual Transform FindBone(string strName) { }
		namespace StringPool {
			auto Get = 0x6B20B0; // public static uint Get(string str) { }
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
#define oDisplayName 0x650// protected string _displayName
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