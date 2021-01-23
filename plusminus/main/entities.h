bool mfound = false;
using namespace otherEsp;
void FindMatrix() {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = read(dwGameObjectManager, DWORD64);
	if (!ObjMgr) return;
	UINT64 end = read(ObjMgr, UINT64);
	for (UINT64 Obj = read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = read(Obj + 0x8, UINT64)) {
		UINT64 GameObject = read(Obj + 0x10, UINT64);
		WORD Tag = read(GameObject + 0x54, WORD);
		if (Tag == 5) {
			UINT64 ObjClass = read(GameObject + 0x30, UINT64);
			UINT64	Entity = read(ObjClass + 0x18, UINT64);
			pViewMatrix = (Matrix4x4*)(Entity + 0x2E4); // 0xDC
			mfound = true;
			return;
		}
	}
}
bool notreelos = false;
void EntityLoop() {
	float FOV = Combat::Fov, CurFOV;
	bool LP_isValid = false;
	if (!pViewMatrix || !mfound) {
		FindMatrix();
	}
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(Storage::gBase + CO::BaseNetworkable, DWORD64);
	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	Renderer::String(Vector2(100, 55), xorstr(L"plusminus.space"), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true);
	if (Storage::closestHeli != NULL && Storage::closestHeliObj != NULL) {
		Vector3 heliPos = read(Storage::closestHeliObj + 0x90, Vector3);
		int heliX = heliPos.x;
		int heliY = heliPos.y;
		int heliZ = heliPos.z;
		std::wstring heliPosition = L"patrol heli: " + std::to_wstring(heliX) + L" " + std::to_wstring(heliY) + L" " + std::to_wstring(heliZ);
		Renderer::String(Vector2(100, 85), heliPosition.c_str(), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true);
	}
	else { Renderer::String(Vector2(100, 85), xorstr(L"patrol heli: NULL"), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true); }
	if (Storage::closestPlayer) {
		auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
		Vector3 playerPos = TargetPlayer->GetBoneByID(head);
		int playerX = playerPos.x;
		int playerY = playerPos.y;
		int playerZ = playerPos.z;
		std::wstring playerPosition = L"player: " + std::to_wstring(playerX) + L" " + std::to_wstring(playerY) + L" " + std::to_wstring(playerZ);
		Renderer::String(Vector2(100, 100), playerPosition.c_str(), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true);
	}
	else { Renderer::String(Vector2(100, 100), xorstr(L"player: NULL"), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true); }
	if (LocalPlayer) {
		Vector3 localPos = LocalPlayer->GetBoneByID(head);
		int localX = localPos.x;
		int localY = localPos.y;
		int localZ = localPos.z;
		std::wstring localPosition = L"local: " + std::to_wstring(localX) + L" " + std::to_wstring(localY) + L" " + std::to_wstring(localZ);
		Renderer::String(Vector2(100, 115), localPosition.c_str(), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true);
	}
	else { Renderer::String(Vector2(100, 115), xorstr(L"local: NULL"), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true); }

	

	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
	for (int i = 0; i <= EntityCount; i++) {
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64); if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64); if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
		char* buff = name->stub;
		DWORD64 ent = read(Object + 0x28, UINT64);
		BaseProjectile* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 active = read(weapon + oHeldEntity, DWORD64);
		char* classname = weapon->ClassName();
		bool weaponmelee = weapon && classname && (m_strcmp(classname, xorstr("BaseMelee")) || m_strcmp(classname, xorstr("Jackhammer")));
		BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
		if (strstr(buff, xorstr("Local"))) {
			Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + 0x4A8, DWORD64)) continue;
			if (Player != LocalPlayer) {
				mfound = false;
			}
			LocalPlayer = Player;
			LP_isValid = true;

		}
		if (strstr(buff, xorstr("player.prefab")) || (strstr(buff, xorstr("scientist"))) && (!strstr(buff, xorstr("prop")) && !strstr(buff, xorstr("corpse")))) {
			
			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + 0x4A8, DWORD64)) continue;
			
			if (PlayerEsp::skeleton && !Player->IsNpc()) {
				if (!Player->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(Player->GetSteamID())) {
						Skeleton(Player, D2D1::ColorF::LimeGreen);
					}
					else {
						if (Player->GetHealth() < 0.2) {
							Skeleton(Player, D2D1::ColorF::Red);
						}
						else {
							Skeleton(Player, D2D1::ColorF::White);
						}
					}
				}
				else if (Player->HasFlags(16) && !PlayerEsp::sleeperignore) {
					Skeleton(Player, D2D1::ColorF::Orange);
				}
			}
			else if (BotsEsp::skeleton && Player->IsNpc()) {
				Skeleton(Player, D2D1::ColorF::Yellow);
			}

			if (!Player->IsNpc()) {
				if (!Player->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(Player->GetSteamID())) {
						ESP(Player, LocalPlayer, D2D1::ColorF::LimeGreen);
					}
					else {
						if (Player->GetHealth() < 0.2) {
							ESP(Player, LocalPlayer, D2D1::ColorF::Red);
						}
						else {
							ESP(Player, LocalPlayer, D2D1::ColorF::White);
						}
					}
				}
				else {
					ESP(Player, LocalPlayer, D2D1::ColorF::Orange);
				}
			}
			else if (Player->IsNpc()) {
				NPCESP(Player, LocalPlayer, D2D1::ColorF::Yellow);
			}

			if (Combat::IgnoreSleepers && Player->HasFlags(16)) continue;
			if (Combat::IgnoreNpc && Player->IsNpc()) continue;
			if (Combat::IgnoreTeam && LocalPlayer->IsTeamMate(Player->GetSteamID())) continue;
			if (Player->GetBoneByID(head).x == 0 || Player->GetBoneByID(head).y == 0 || Player->GetBoneByID(head).z == 0) continue;
			if (Combat::IgnorePlayers) continue;
			if (Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Combat::Range) continue;

			if (FOV > (CurFOV = GetFov(Player, BoneList(Global::BoneToAim))) && !Player->IsDead() && !Combat::LockTarget) {
				FOV = CurFOV; Storage::closestPlayer = (uintptr_t)Player;
			}

		}
		if (strstr(buff, xorstr("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab"))) {
			uintptr_t BaseObject = read(ObjectClass + 0x30, uintptr_t);
			uintptr_t BaseEntity = read(BaseObject + 0x18, uintptr_t);
			BaseHelicopter* Helicopter = (BaseHelicopter*)read(BaseEntity + 0x28, DWORD64);
			uintptr_t Transform = read(BaseObject + 0x8, uintptr_t);
			uintptr_t VisualState = read(Transform + 0x38, uintptr_t);
			float health = Helicopter->GetHealth();
			float maxhealth = 10000.f;
			Vector3 pos = read(VisualState + 0x90, Vector3);
			Vector2 screenPos;
			if (utils::w2s(pos, screenPos)) {
				wchar_t buffer[256];
				wchar_t buffera[256];
				if (Visuals::PatrolHeli) {
					swprintf(buffer, xorstr(L"Helicopter [%dm]"), (int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos));
					swprintf(buffera, xorstr(L"[%dHP]"), (int)health);
					Renderer::String(screenPos, buffer, D2D1::ColorF(0.5f, 0.54f, 1.f), true, true);
					Renderer::String(screenPos + Vector2(0, 15), buffera, D2D1::ColorF(0.5f, 0.54f, 1.f), true, true);
					Renderer::FillRectangle(Vector2{ screenPos - Vector2(30, 0) + Vector2(0, 25) }, Vector2{ 60 * (health / maxhealth), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
					Renderer::Rectangle(Vector2{ screenPos - Vector2(30, 0) + Vector2(0, 25) }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
				}
				if (health > 0.2 && !Combat::IgnoreHeli) {
					if ((FOV > (CurFOV = GetFovHeli(pos)))) {
						FOV = CurFOV; Storage::closestHeli = (uintptr_t)Helicopter; Storage::closestHeliObj = VisualState;
					}
				}
			}
		}
		
		if (Misc::AutoCollect && m_strstr(buff, xorstr("/collectable/"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				PickupItem(ent);
			}
		}
		//BaseProjectile* weapon = LocalPlayer->GetActiveWeapon(); // get active item
		if (weapon->GetID() == 1079279582 || weapon->GetID() == -2072273936) {
			//Test();
		}
		otherEsp::bradley(ObjectClass, Object, buff);
		otherEsp::corpse(ObjectClass, Object, buff);
		otherEsp::tc(ObjectClass, Object, buff);
		otherEsp::sleepingbag(ObjectClass, Object, buff);
		otherEsp::bed(ObjectClass, Object, buff);
		otherEsp::stash(ObjectClass, Object, buff);
		otherEsp::hackablecrate(ObjectClass, Object, buff);
		otherEsp::world(ObjectClass, Object, buff);
		//otherEsp::explo(ObjectClass, Object, buff);
		if (Ores::showCollectables) {
			miscvis(ObjectClass, buff, Ores::Stone, Ores::showDistance, Ores::oreDrawDistance, xorstr("stone-collectable.prefab"), xorstr(L"Stone Collectable"), D2D1::ColorF::Gray);
			miscvis(ObjectClass, buff, Ores::Sulfur, Ores::showDistance, Ores::oreDrawDistance, xorstr("sulfur-collectable.prefab"), xorstr(L"Sulfur Collectable"), D2D1::ColorF::Gold);
			miscvis(ObjectClass, buff, Ores::Metal, Ores::showDistance, Ores::oreDrawDistance, xorstr("metal-collectable.prefab"), xorstr(L"Metal Collectable"), D2D1::ColorF::SaddleBrown);
		}
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Ores::Stone, Ores::showDistance, Ores::oreDrawDistance, xorstr("stone-ore.prefab"), xorstr(L"Stone Ore"), D2D1::ColorF::Gray);
		miscvis(ObjectClass, buff, Ores::Sulfur, Ores::showDistance, Ores::oreDrawDistance, xorstr("sulfur-ore.prefab"), xorstr(L"Sulfur Ore"), D2D1::ColorF::Gold);
		miscvis(ObjectClass, buff, Ores::Metal, Ores::showDistance, Ores::oreDrawDistance, xorstr("metal-ore.prefab"), xorstr(L"Metal Ore"), D2D1::ColorF::SaddleBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Crates::Supply, Visuals::Crates::crateDistance, Visuals::Crates::drawCrateDistance, xorstr("supply_drop.prefab"), xorstr(L"Airdrop"), D2D1::ColorF::DarkCyan);
		miscvis(ObjectClass, buff, Visuals::Crates::Heli, Visuals::Crates::crateDistance, Visuals::Crates::drawCrateDistance, xorstr("heli_crate.prefab"), xorstr(L"Heli Crate"), D2D1::ColorF::DarkGreen);
		miscvis(ObjectClass, buff, Visuals::Crates::Bradley, Visuals::Crates::crateDistance, Visuals::Crates::drawCrateDistance, xorstr("bradley_crate.prefab"), xorstr(L"Bradley Crate"), D2D1::ColorF::GreenYellow);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Vehicles::Minicopter, Visuals::Vehicles::vehicleDistance, Visuals::Vehicles::drawVehicleDistance, xorstr("minicopter.entity.prefab"), xorstr(L"Minicopter"), D2D1::ColorF::Blue);
		miscvis(ObjectClass, buff, Visuals::Vehicles::ScrapHeli, Visuals::Vehicles::vehicleDistance, Visuals::Vehicles::drawVehicleDistance, xorstr("scraptransporthelicopter.prefab"), xorstr(L"Scrap Heli"), D2D1::ColorF::DarkBlue);
		miscvis(ObjectClass, buff, Visuals::Vehicles::Boat, Visuals::Vehicles::vehicleDistance, Visuals::Vehicles::drawVehicleDistance, xorstr("rowboat.prefab"), xorstr(L"Boat"), D2D1::ColorF::LightBlue);
		miscvis(ObjectClass, buff, Visuals::Vehicles::RHIB, Visuals::Vehicles::vehicleDistance, Visuals::Vehicles::drawVehicleDistance, xorstr("rhib.prefab"), xorstr(L"RHIB"), D2D1::ColorF::LightCyan);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Turrets::AutoTurret, Visuals::Turrets::trapDistance, Visuals::Turrets::drawTrapDistance, xorstr("autoturret_deployed.prefab"), xorstr(L"Auto Turret"), D2D1::ColorF::Orange);
		miscvis(ObjectClass, buff, Visuals::Turrets::FlameTurret, Visuals::Turrets::trapDistance, Visuals::Turrets::drawTrapDistance, xorstr("flameturret.deployed.prefab"), xorstr(L"Flame Turret"), D2D1::ColorF::DarkOrange);
		miscvis(ObjectClass, buff, Visuals::Turrets::ShotgunTurret, Visuals::Turrets::trapDistance, Visuals::Turrets::drawTrapDistance, xorstr("guntrap.deployed.prefab"), xorstr(L"Shotgun Trap"), D2D1::ColorF::DimGray);
		miscvis(ObjectClass, buff, Visuals::Turrets::Landmine, Visuals::Turrets::trapDistance, Visuals::Turrets::drawTrapDistance, xorstr("landmine.prefab"), xorstr(L"Landmine"), D2D1::ColorF::BlueViolet);
		miscvis(ObjectClass, buff, Visuals::Turrets::BearTrap, Visuals::Turrets::trapDistance, Visuals::Turrets::drawTrapDistance, xorstr("beartrap.prefab"), xorstr(L"Beartrap"), D2D1::ColorF::Brown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Other::Hemp, Visuals::Other::otherDistance, Visuals::Other::drawOtherDistance, xorstr("hemp-collectable.prefab"), xorstr(L"Hemp"), D2D1::ColorF::LimeGreen);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Base::Boxes, Visuals::Base::baseDistance, Visuals::Base::drawBaseDistance, xorstr("box.wooden.large.prefab"), xorstr(L"Box"), D2D1::ColorF::RosyBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, Visuals::Animals::Bear, Visuals::Animals::animalDistance, Visuals::Animals::drawAnimalDistance, xorstr("bear.prefab"), xorstr(L"Bear"), D2D1::ColorF::SaddleBrown);
		miscvis(ObjectClass, buff, Visuals::Animals::Wolf, Visuals::Animals::animalDistance, Visuals::Animals::drawAnimalDistance, xorstr("agents/wolf/wolf.prefab"), xorstr(L"Wolf"), D2D1::ColorF::LightSlateGray);
		miscvis(ObjectClass, buff, Visuals::Animals::Pig, Visuals::Animals::animalDistance, Visuals::Animals::drawAnimalDistance, xorstr("boar.prefab"), xorstr(L"Pig"), D2D1::ColorF::DarkRed);
		miscvis(ObjectClass, buff, Visuals::Animals::Chicken, Visuals::Animals::animalDistance, Visuals::Animals::drawAnimalDistance, xorstr("agents/chicken/chicken.prefab"), xorstr(L"Chicken"), D2D1::ColorF::YellowGreen);
		miscvis(ObjectClass, buff, Visuals::Animals::Deer, Visuals::Animals::animalDistance, Visuals::Animals::drawAnimalDistance, xorstr("agents/horse/horse.prefab"), xorstr(L"Horse"), D2D1::ColorF::SandyBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, true, false, 2000.f, Global::testChar, xorstr(L"TESTITEM"), D2D1::ColorF::LimeGreen);
	}
	static DWORD64 GOM = 0;
	if (!GOM) GOM = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", xorstr("xxx????xx"), xorstr(L"UnityPlayer.dll")), 7);
	DWORD64 manager = read(GOM, DWORD64); if (!manager) return;
	for (DWORD64 object = read(manager + 0x8, DWORD64); (object && (object != read(manager, DWORD64))); object = read(object + 0x8, DWORD64)) {
		DWORD64 gameobject = read(object + 0x10, DWORD64);
		WORD tag = read(gameobject + 0x54, WORD);
		if (tag == 6 || tag == 5 || tag == 20011) {
			DWORD64 objectclass = read(gameobject + 0x30, DWORD64);
			DWORD64	entity = read(objectclass + 0x18, DWORD64);
			if (tag == 20011 && Misc::CustomTime) {
				DWORD64 dome = read(entity + 0x28, DWORD64);
				DWORD64 todCycle = read(dome + 0x38, DWORD64);
				write(todCycle + 0x10, Misc::Time, float);
			}
		}
	}
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	/*targeting shit*/
	if (TargetPlayer->GetBoneByID(head).x == 0 || TargetPlayer->GetBoneByID(head).y == 0 || TargetPlayer->GetBoneByID(head).z == 0) {
		Storage::closestPlayer = NULL;
	}
	if (TargetPlayer->IsNpc() && Combat::IgnoreNpc) {
		Storage::closestPlayer = NULL;
	}
	if (TargetPlayer->HasFlags(16) && Combat::IgnoreSleepers) {
		Storage::closestPlayer = NULL;
	}
	if (LocalPlayer->IsTeamMate(TargetPlayer->GetSteamID()) && Combat::IgnoreTeam) {
		Storage::closestPlayer = NULL;
	}
	if (TargetPlayer->GetHealth() < 0.2) {
		Combat::LockTarget = false;
		Storage::closestPlayer = NULL;
	}
	if ((int)ceil(read(Storage::closestHeli + 0x20C, float)) < 0.2) {
		Storage::closestHeli = NULL;
		Storage::closestHeliObj = NULL;
	}
	if (Combat::IgnorePlayers) {
		Storage::closestPlayer = NULL;
	}
	if (Combat::IgnoreHeli) {
		Storage::closestHeli = NULL;
		Storage::closestHeliObj = NULL;
	}
	if (read(Storage::closestHeliObj + 0x90, Vector3).y > 1500 || read(Storage::closestHeliObj + 0x90, Vector3).y < -1500) {
		Storage::closestHeli = NULL;
		Storage::closestHeliObj = NULL;
	}
	if (LP_isValid) {
		Aim((BasePlayer*)Storage::closestPlayer);
	}
	else LocalPlayer = nullptr;
}

void EntityThreadLoop() {
	if (!pViewMatrix || !mfound) {
		FindMatrix();
	}
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(Storage::gBase + CO::BaseNetworkable, DWORD64);
	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
	/*if (show) {
		game::set_lockstate(CursorLockMode::None);
	}*/
	for (int i = 0; i <= EntityCount; i++) {
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64); if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64); if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
		char* buff = name->stub;
		DWORD64 ent = read(Object + 0x28, UINT64);
		BaseProjectile* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 active = read(weapon + oHeldEntity, DWORD64);
		char* classname = weapon->ClassName();
		bool weaponmelee = weapon && classname && (m_strcmp(classname, xorstr("BaseMelee")) || m_strcmp(classname, xorstr("Jackhammer")));
		if (m_strstr(buff, xorstr("player.prefab"))) {
			if (yeetus) {
				typedef void(__stdcall* Pick)(DWORD64, Str);
				((Pick)(Storage::gBase + CO::ServerRPC))(ent, Str(xorstr(L"BuyItem")));
				yeetus = false;
			}
			BasePlayer* lol = (BasePlayer*)ent;
			if (PlayerEsp::chams && lol->GetHealth() > 0.2) {
				uintptr_t playermodel = read(ent + oPlayerModel, uintptr_t);
				uintptr_t multimesh = read(playermodel + 0x280, uintptr_t);
				if (!lol->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(lol->GetSteamID())) {
						DoChams(multimesh, Color(0, 1, 0, 1));
					}
					else {
						DoChams(multimesh, Color(1, 0, 0, 1));
					}
				}
				else if (lol->HasFlags(16) && !PlayerEsp::sleeperignore) {
					DoChams(multimesh, Color(1, 0.5, 0, 1));
				}
			}
			if (Misc::AutoAssist || Misc::InstaRevive) {
				UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
				Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
				if (Misc::AutoAssist && (BasePlayer*)ent && lol->HasFlags(64) && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
					PickupPlayer((BasePlayer*)ent);
				}
				if (Misc::InstaRevive && (BasePlayer*)ent && lol->HasFlags(64) && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f && LocalPlayer->GetKeyState(ButtonS::USE) 
					&& read(LocalPlayer + 0x4E8, uintptr_t) == ent) {
					PickupPlayer((BasePlayer*)ent);
				}
			}
			if (Weapons::SilentMelee && weaponmelee) {
				Target target = TargetMeleeTest((BasePlayer*)ent, active);
				DoMeleeAttack(target, active, true);
			}
		}
		if (Weapons::SilentOre && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("OreHotSpot"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) >= 3.f) { continue; }
			Target target = Target();
			target.valid = true;
			target.position = utils::GetEntityPosition(gameObject);
			target.entity = (BasePlayer*)ent;
			DoMeleeAttack(target, active, false);
		}
		//========================================================================================================================================================================================
		/*Target target = Target();
		if (Weapons::SilentTree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeEntity"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, Vector3(utils::GetEntityPosition(gameObject).x, LocalPlayer->GetBoneByID(head).y, utils::GetEntityPosition(gameObject).z)) >= 2.f) { continue; }
			bool iskill = read(read(Object + 0x28, uintptr_t) + 0x15C, bool);
			if (!iskill) {
				target.entity = (BasePlayer*)ent;
			}
		}
		if (Weapons::SilentTree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeMarker"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) >= 2.f) { continue; }
			target.valid = true;
			target.position = utils::GetEntityPosition(gameObject);
			if (target.entity) {
				DoMeleeAttack(target, active, false);
			}
		}*/
		if (Weapons::SilentTree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeEntity"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) >= 2.f) { continue; }
			Target target = Target();
			target.valid = true;
			target.position = Vector3(utils::GetEntityPosition(gameObject).x, LocalPlayer->GetBoneByID(head).y, utils::GetEntityPosition(gameObject).z);
			target.entity = (BasePlayer*)ent;
			DoMeleeAttack(target, active, false);
		}
		//========================================================================================================================================================================================
		if (Misc::Annoyer && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("Door"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (ent && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				SpamKnock(ent);
			}
		}
	}
}