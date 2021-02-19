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
	if (weapon->GetID() == 442886268) {
		weapon->SetAutomatic();
		DWORD64 heldentity = read(weapon + oHeldEntity, DWORD64);
		write(heldentity + oRepeatDelay, 0.01f, float);
		return;
	}
	
}
float w_last_syringe = 0.f;
void MiscFuncs() {
	if (w_last_syringe = 0.f) {
		w_last_syringe = LocalPlayer->Time();
	}
	Item* weapon = LocalPlayer->GetActiveWeapon();
	if ((weapon->GetID() == 1079279582 || weapon->GetID() == -2072273936) && vars::misc::faster_healing) {
		DWORD64 Held = read(weapon + oHeldEntity, DWORD64);
		bool deployed = read(Held + 0x188, bool);
		float curtime = LocalPlayer->Time();
		if (LocalPlayer->GetKeyState(ButtonS::FIRE_PRIMARY) && deployed && curtime > w_last_syringe + 0.7f) {
			reinterpret_cast<void(_stdcall*)(DWORD64, Str)>(vars::stor::gBase + CO::ServerRPC)(Held, Str(xorstr(L"UseSelf")));
			w_last_syringe = curtime;
		}
	}
	if (vars::misc::gravity) {
		if (GetAsyncKeyState(vars::keys::gravitykey))
			LocalPlayer->SetGravity(vars::misc::gravity_modifier);
		else LocalPlayer->SetGravity(2.5f);
	}
	if (GetAsyncKeyState(vars::keys::zoom)) {
		LocalPlayer->SetFov(10.f);
	}
	else {
		LocalPlayer->SetFov(vars::misc::fov);
	}
	if (vars::misc::spiderman) {
		ULONG64 Movement = read(LocalPlayer + oMovement, ULONG64);
		write(Movement + 0xB8, 0.f, float);
	}
	LocalPlayer->PatchCamspeed();
	if (vars::misc::fakeadmin)
		LocalPlayer->FakeAdmin();
}
