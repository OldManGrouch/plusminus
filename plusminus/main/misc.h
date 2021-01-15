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
void MiscFuncs() {
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
