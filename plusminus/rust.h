class ItemModProjectile {
public:
	FIELD("Assembly-CSharp::Projectile::projectileSpread", projectileSpread, float);
	FIELD("Assembly-CSharp::Projectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::Projectile::projectileVelocitySpread", projectileVelocitySpread, float);
};
class Projectile {
public:
	FIELD("Assembly-CSharp::Projectile::initialVelocity", initialVelocity, Vector3);
	FIELD("Assembly-CSharp::Projectile::drag", drag, float);
	FIELD("Assembly-CSharp::Projectile::gravityModifier", gravityModifier, float);
	FIELD("Assembly-CSharp::Projectile::thickness", thickness, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::mod", mod, ItemModProjectile*);
	FIELD("Assembly-CSharp::Projectile::remainInWorld", remainInWorld, bool);
	FIELD("Assembly-CSharp::Projectile::stickProbability", stickProbability, float);
	FIELD("Assembly-CSharp::Projectile::breakProbability", breakProbability, float);
	FIELD("Assembly-CSharp::Projectile::conditionLoss", conditionLoss, float);
	FIELD("Assembly-CSharp::Projectile::ricochetChance", ricochetChance, float);
	FIELD("Assembly-CSharp::Projectile::penetrationPower", penetrationPower, float);
	FIELD("Assembly-CSharp::Projectile::invisible", invisible, bool);
	FIELD("Assembly-CSharp::Projectile::currentPosition", currentPosition, Vector3);

	/*Vector3 initialVelocity() { return read(this + 0x18, Vector3); }
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
	void swimRandom(float a) { write(this + 0x1A0, a, float); }*/
};