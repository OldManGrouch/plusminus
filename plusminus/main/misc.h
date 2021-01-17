void WeaponPatch() {
	BaseProjectile* weapon = LocalPlayer->GetActiveWeapon();
	if (weapon == nullptr) return;
	
	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info();
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == 1) {
		weapon->NoSway();
		weapon->LongHand();
		weapon->FatHand();
		return;
	}
	if (target.category == -2) {
		weapon->NoSway();
		weapon->SuperBow();
		return;
	}
	if (target.category == 3) {
		weapon->NoSway();
		weapon->NoRecoil();
		weapon->RapidFire();
		return;
	}
	if (target.category == 2) {
		weapon->NoSway();
		weapon->NoRecoil();
		weapon->RapidFire();
		weapon->SetAutomatic();
		return;
	}
	if (target.category == -1) {
		weapon->NoSway();
		weapon->SuperEoka();
		weapon->NoRecoil();
		return;
	}
	
}
float aa = 0.f;
void MiscFuncs() {
	aa += 0.1f; // count the timer up
	BaseProjectile* weapon = LocalPlayer->GetActiveWeapon(); // get active item
	if ((weapon->GetID() == 1079279582 || weapon->GetID() == -2072273936) && Misc::FastHeal) { // check item thru id
		DWORD64 Held = read(weapon + oHeldEntity, DWORD64); // get held entity
		write(Held + 0x278, 1.f, float); // disable animation cause it tries using the syringe and gives violations
		bool deployed = read(Held + 0x188, bool); // check if is deployed
		if (LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY) && aa >= 21.f) { // check if fire button is down and if the timer has reached a specific number
			typedef void(__stdcall* ServerRPC)(DWORD64, Str); // define server rpc
			((ServerRPC)(Storage::gBase + CO::ServerRPC))(Held, Str(xorstr(L"UseSelf"))); // call serverrpc
			aa = 0.f; // reset the timer
		}
	}
	if (Misc::Gravity) {
		if (GetAsyncKeyState(Keys::gravityKey))
			LocalPlayer->SetGravity(Misc::GravityModifier);
		else LocalPlayer->SetGravity(2.5f);
	}
	LocalPlayer->SetFov();
	LocalPlayer->PatchCamspeed();
	//LocalPlayer->WalkWater();
	if (Weapons::LegitNoRecoil) {
		LocalPlayer->SetRA();
	}
	if (Misc::SpiderMan)
		LocalPlayer->SpiderMan();
	if (Misc::FakeAdmin)
		LocalPlayer->FakeAdmin();
}
