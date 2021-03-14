
namespace CO {
	auto Refract = 0x8B06E0;
	auto SendSignalBroadcast = 0x3B5690;
	auto Magnitude2D = 0x1CAA460;
	auto GetJumpHeight = 0x2FFE40;
	auto MathfAbs = 0x17A9CC0;
	auto MathfMax = 0x17AA890;
	auto GetHeight = 0x2FF670;
	auto GetRadius = 0x301400;
	auto CheckCapsule = 0x2068580; // public static bool CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, QueryTriggerInteraction queryTriggerInteraction) { }
	auto EffectRun = 0x938830;
	auto RebuildAll = 0xAC72C0;
	auto GetMaxSpeed = 0x2FFFE0;
	auto DoFixedUpdate = 0x8943D0;
	auto CanAffordUpgrade = 0x52FC80;
	auto CanChangeToGrade = 0x52FE50;
	auto IsUpgradeBlocked = 0x532140;
	auto get_jumped = 0x1C265A0;
	auto get_velocity = 0x206CD90;
	auto set_velocity = 0x206D2B0;
	auto get_rotation = 0xAB9FA0;
	auto Play = 0x9733B0; // ViewModel
	auto GetRandomVelocity = 0x817AF0;
	auto Client = 0x2FF90D8; // ConVar.Client_TypeInfo
	auto CreateEffect = 0x929740;
	auto UpgradeToGrade = 0x533420;
	auto AddPunch = 0x7A36B0;
	auto MoveTowards = 0x1F82890;
	auto Jump = 0x8965D0;
	auto Total = 0x5F38D0;
	auto IsDucked = 0x3036C0;
	auto PropertyToId = 0x186BA20;
	auto VisUpdateUsingCulling = 0x312EF0;
	auto SetInt = 0x17A9020;
	auto SetColor = 0x17A8C30;
	auto set_shader = 0x17A9C20;
	auto get_shader = 0x17A9A90;
	auto get_material = 0x1869750;
	auto get_Renderers = 0x3DDF90;
	auto ShaderFind = 0x186B900;
	auto OnLand = 0x305D70; // BasePlayer->OnLand
	auto get_position = 0xAB9C50; // playereyes->get_position
	auto IsBeingHacked = 0x2E2340;
	auto IsFullyHacked = 0x2E2B90;
	auto ForceToPos = 0x2FE970;
	auto UpdateAmbient = 0xC39C30; // protected void UpdateAmbient() { } || TOD_Sky
	auto set_rayleigh = 0x7E8360;
	auto BasePlayer = 0x2FF96F0; // BasePlayer_TypeInfo
	auto AssistPlayer = 0x3056B0; // public void Menu_AssistPlayer(BasePlayer player) { }
	auto Launch = 0x8B0030; // internal void Launch() { }
	auto KnockDoor = 0x920A10; // public void Menu_KnockDoor(BasePlayer player) { }
	auto OpenDoor = 0x920A90; // public void Menu_OpenDoor(BasePlayer player) { }
	auto OpenHatch = 0x920AE0; // public void Menu_ToggleHatch(BasePlayer player) { }
	auto IsHidden = 0x2ED5B0; // public class StashContainer : StorageContainer
	auto get_isHeadshot = 0x7A8C60; // public bool get_isHeadshot() { }
	auto DoHitNotify = 0x3A92D0; // public void DoHitNotify(HitInfo info) { }
	auto StartAttackCooldown = 0x39EA60; // protected void StartAttackCooldown(float cooldown) { }
	auto ProcessAttack = 0x2EAA20; // protected virtual void ProcessAttack(HitTest hit) { }
	auto get_transform = 0x1795940; // public Transform get_transform() { } | UnityEngine::Component
	auto HitTest = 0x2FF8958; // HitTest_TypeInfo
	auto ServerRPC = 0x3B5C90;
	auto TraceAll = 0xBEF600; // public static void TraceAll(HitTest test, List<TraceInfo> traces, int layerMask = -5) { }
	auto BaseNetworkable = 0x2FF92B0; // BaseNetworkable_TypeInfo
	auto SendProjectileAttack = 0x30F180; // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	auto GetModifiedAimConeDirection = 0x984350; // public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
	auto set_flying = 0x1C26670; // public void set_flying(bool value) { } 
	auto CanAttack = 0x2F79B0; // public bool CanAttack() { }
	auto SendClientTick = 0x30EAC0; // internal void SendClientTick() { }
	auto HandleRunning = 0x896340; // private void HandleRunning(ModelState state, bool wantsRun) { }
	auto HandleJumping = 0x896220;
	auto CreateProjectile = 0x72EF20; // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	auto CanHoldItems = 0x2EE0F0; // public virtual bool CanHoldItems() { }
	auto Run = 0x20790B0; // public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	auto DoMovement = 0x8AE570; // private void DoMovement(float deltaTime) { }
	auto DoHit = 0x8ADE60; // private bool DoHit(HitTest test, Vector3 point, Vector3 normal) { }
	auto ClientInput = 0x2F9600; // internal virtual void ClientInput(InputState state) { }
	auto ConvarGraphics = 0x2FF7FE0; // ConVar.Graphics_TypeInfo
	namespace utils {
		auto ClosestPoint = 0x3ACAD0; // public Vector3 ClosestPoint(Vector3 position) { }
		auto GetWorldVelocity = 0x3B0B90; // public Vector3 GetWorldVelocity() { }
		auto InverseTransformPoint = 0x1F7D4B0; // public Vector3 InverseTransformPoint(Vector3 position) { }
		auto LineOfSight = 0x5BBB40; // public static bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask, float padding = 0) { }
		auto FindBone = 0x3ADE00; // public virtual Transform FindBone(string strName) { }
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