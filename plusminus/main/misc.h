void WeaponPatch() {
	BaseProjectile* weapon = LocalPlayer->GetActiveWeapon();
	if (weapon == nullptr) return;
	
	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info();
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == 1) {
		Global::RetardDivideFactor = 4;
		weapon->LongHand();
		weapon->FatHand();
		return;
	}
	if (target.category == -2) {
		weapon->SuperBow();
		return;
	}
	if (target.category == 3) {
		weapon->NoRecoil();
		weapon->RapidFire();
		return;
	}
	if (target.category == 2) {
		weapon->NoRecoil();
		weapon->RapidFire();
		weapon->SetAutomatic();
		return;
	}
	if (target.category == -1) {
		weapon->SuperEoka();
		weapon->NoRecoil();
		return;
	}
	DWORD64 basePr = read(weapon + oHeldEntity, DWORD64);
	DWORD64 primMag = read(basePr + 0x2A0, DWORD64);
	DWORD64 type = read(primMag + 0x20, DWORD64);

	DWORD64 itemmod = read(Storage::gBase + 0x299C300, DWORD64);
	typedef DWORD64(__stdcall* GetComponent)(DWORD64, DWORD64);
	DWORD64 itemmodprojectile = ((GetComponent)(Storage::gBase + 0x7FCAB0))(type, itemmod);

	float projectileVelocity = read(itemmodprojectile + 0x34, float);
	printf("%s\n", std::to_string(projectileVelocity));
}
void MiscFuncs() {
	if (Misc::Gravity) {
		if (GetAsyncKeyState(Keys::gravityKey))
			LocalPlayer->SetGravity(Misc::GravityModifier);
		else LocalPlayer->SetGravity(2.5f);
	}
	LocalPlayer->SetFov();
	//LocalPlayer->WalkWater();
	if (Weapons::LegitNoRecoil) {
		LocalPlayer->SetRA();
	}
	if (Misc::SpiderMan)
		LocalPlayer->SpiderMan();
	if (Weapons::NoSway)
		LocalPlayer->NoSway();
	if (Misc::FakeAdmin)
		LocalPlayer->FakeAdmin();
}
