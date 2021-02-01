void WeaponPatch() {
	Item* weapon = LocalPlayer->GetActiveWeapon();
	if (weapon == nullptr) return;
	
	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info();
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == -2) {
		weapon->NoSway();
		weapon->FastBow();
		return;
	}
	if (target.category == 3) {
		weapon->NoSway();
		weapon->RapidFire();
		return;
	}
	if (target.category == 2) {
		weapon->NoSway();
		weapon->RapidFire();
		weapon->SetAutomatic();
		return;
	}
	if (target.category == -1) {
		weapon->NoSway();
		weapon->EokaTap();
		return;
	}
	
}
float w_last_syringe = 0.f;
void MiscFuncs() {
	Item* weapon = LocalPlayer->GetActiveWeapon(); // get active item
	if ((weapon->GetID() == 1079279582 || weapon->GetID() == -2072273936) && vars::misc::faster_healing) { // check item thru id
		DWORD64 Held = read(weapon + oHeldEntity, DWORD64); // get held entity
		write(Held + 0x278, 1.f, float); // disable animation cause it tries using the syringe and gives violations
		bool deployed = read(Held + 0x188, bool); // check if is deployed
		float curtime = LocalPlayer->Time();
		if (LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY) && deployed && curtime > w_last_syringe + 0.7f) { // check if fire button is down and if the timer has reached a specific number
			typedef void(__stdcall* ServerRPC)(DWORD64, Str); // define server rpc
			((ServerRPC)(vars::stor::gBase + CO::ServerRPC))(Held, Str(xorstr(L"UseSelf"))); // call serverrpc
			w_last_syringe = curtime;
		}
	}
	if (vars::misc::gravity) {
		if (GetAsyncKeyState(vars::keys::gravitykey))
			LocalPlayer->SetGravity(vars::misc::gravity_modifier);
		else LocalPlayer->SetGravity(2.5f);
	}
	LocalPlayer->SetFov();
	LocalPlayer->PatchCamspeed();
	if (vars::misc::spiderman)
		LocalPlayer->SpiderMan();
	if (vars::misc::fakeadmin)
		LocalPlayer->FakeAdmin();
}
