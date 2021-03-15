void EntityThreadLoop() {
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64);

	if (!LocalPlayer::Entity()) return;

	if (vars::players::chams) {
		lol::UpdateChams();
	}
	//if (vars::stuff::testBool) {
	//	uintptr_t playermodel = read(LocalPlayer + oPlayerModel, uintptr_t);
	//	uintptr_t multimesh = read(playermodel + 0x280, uintptr_t);
	//	lol::chams(multimesh, Color(0, 1, 0, 1));
	//}

	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
	for (int i = 0; i <= EntityCount; i++) {
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64); if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64); if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
		char* buff = name->stub;
		DWORD64 ent = read(Object + 0x28, UINT64);
		if (reinterpret_cast<BaseEntity*>(ent)->IsDestroyed()) {
			continue;
		}
		Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
		DWORD64 active = read(weapon + oHeldEntity, DWORD64);
		char* classname = weapon->ClassName();

		bool weaponmelee = weapon && classname && (strcmp(classname, xorstr("BaseMelee")) || strcmp(classname, xorstr("Jackhammer")));
		if (strstr(buff, xorstr("player.prefab"))) {
			BasePlayer* lol = (BasePlayer*)ent;

			if (vars::players::chams && lol) {
				if (lol->GetHealth() > 0) {
					uintptr_t playermodel = read(ent + oPlayerModel, uintptr_t);
					uintptr_t multimesh = read(playermodel + 0x280, uintptr_t);
					if (!lol->HasFlags(16)) {
						if (LocalPlayer::Entity()->is_teammate(lol->GetSteamID())) {
							lol::chams(multimesh, Color(0, 1, 0, 1));
						}
						else {
							lol::chams(multimesh, Color(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
						}
					}
					else if (lol->HasFlags(16) && !vars::players::sleeperignore) {
						lol::chams(multimesh, Color(1, 0.5, 0, 1));
					}
				}
			}
			if (vars::misc::auto_revive || vars::misc::insta_revive) {
				UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
				if (vars::misc::auto_revive && (BasePlayer*)ent && lol->HasFlags(64) && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
					lol::PickupPlayer((BasePlayer*)ent);
				}
				if (vars::misc::insta_revive && (BasePlayer*)ent && lol->HasFlags(64) && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f && LocalPlayer::Entity()->GetKeyState(Button::USE)
					&& read(LocalPlayer::Entity() + 0x4E8, uintptr_t) == ent) {
					lol::PickupPlayer((BasePlayer*)ent);
				}
			}
			if (vars::combat::silent_melee && weaponmelee && Math::Distance_3D(lol->get_bone_pos(head), LocalPlayer::Entity()->get_bone_pos(head)) <= 3.5f) {
				f_object target = f_object::get_melee_target((BasePlayer*)ent, active);
				lol::do_attack(target, active, true);
			}
		}
		else if (vars::misc::auto_grade && strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("BuildingBlock"))
			&& !strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("Door"))
			&& !strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("Deployable"))
			&& !strstr(buff, xorstr("furnace"))
			&& !strstr(buff, xorstr("bars"))
			&& !strstr(buff, xorstr("gates.external.high.stone.prefab"))
			&& !strstr(buff, xorstr("gates.external.high.wood.prefab"))
			&& !strstr(buff, xorstr("wall.external.high.stone.prefab"))
			&& !strstr(buff, xorstr("wall.external.high.wood.prefab"))
			)
		{
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
			if (Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) >= 3.f) { continue; }
			if (vars::misc::auto_grade) {
				lol::AutoGrade(ent);
			}
		}
		else if (vars::misc::auto_pickup && strstr(buff, xorstr("/collectable/"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
			if (Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				utils::ServerRPC(ent, Str(xorstr(L"Pickup")));
			}
		}
		else if (vars::misc::annoyer && strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("Door"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
			if (ent && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				lol::SpamKnock(ent);
			}
		}
	}
}