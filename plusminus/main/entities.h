﻿bool mfound = false;
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
bool inited = false;
float timee = 120.f;
void EntityLoop() {
	if (vars::visuals::radar_) {
		radar::radar_bg();
	}
	LogSystem::Render();
	if (vars::visuals::raid_esp) {
		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince) >= timee) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}
			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;
			if (utils::w2s(explosion.position, explPos)) {
				Renderer::String(
					explPos, 
					StringConverter::ToUnicode(StringFormat::format(c_xor("%s [%dm] [%d]"), 
					explosion.name.c_str(), 
					(int)Math::Calc3D_Dist(explosion.position, LocalPlayer->get_bone_pos(head)), 
					(int)(timee - (get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince)))).c_str(),
					D2D1::ColorF::Red, 
					true, 
					true
				);
			}
		}
	}
	float FOV = vars::combat::fov, CurFOV;
	bool LP_isValid = false;
	typedef uintptr_t(__stdcall* CurrentVersionInfo)();
	typedef int(__stdcall* get_Number)(uintptr_t);
	if (!pViewMatrix || !mfound) {
		
		FindMatrix();
	}
	if (!inited) {
		LogSystem::Log(c_wxor(L"Cheat loaded!"), 5.f);
		inited = true;
	}
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64);
	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	Renderer::String(Vector2(100, 55), xorstr(L"plusminus"), D2D1::ColorF(1.f, 1.f, 1.f, 1.f), true, false);
	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
	for (int i = 0; i <= EntityCount; i++) {
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64); if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64); if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
		char* buff = name->stub;
		DWORD64 ent = read(Object + 0x28, UINT64);
		Item* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 active = read(weapon + oHeldEntity, DWORD64);
		char* classname = weapon->ClassName();
		bool weaponmelee = weapon && classname && (m_strcmp(classname, xorstr("BaseMelee")) || m_strcmp(classname, xorstr("Jackhammer")));
		BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
		if (vars::visuals::radar_) {
			radar::radar_logic(ObjectClass, Object, buff);
		}
		if (strstr(buff, xorstr("Local"))) {
			Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + 0x4A8, DWORD64)) continue;
			if (Player != LocalPlayer) {
				mfound = false;
			}
			LocalPlayer = Player;
			LP_isValid = true;

		}
		if (strstr(buff, xorstr("player.prefab")) || strstr(buff, xorstr("scientist")) && !strstr(buff, xorstr("prop")) && !strstr(buff, xorstr("corpse"))) {
			
			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + 0x4A8, DWORD64)) continue;
			
			if (vars::players::skeleton && !Player->IsNpc()) {
				if (!Player->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(Player->GetSteamID())) {
						Skeleton(Player, D2D1::ColorF::Lime);
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
				else if (Player->HasFlags(16) && !vars::players::sleeperignore) {
					Skeleton(Player, D2D1::ColorF::Orange);
				}
			}
			else if (vars::npc::skeleton && Player->IsNpc()) {
				Skeleton(Player, D2D1::ColorF::Yellow);
			}
			
			if (!Player->IsNpc()) {
				if (!Player->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(Player->GetSteamID())) {
						ESP(Player, LocalPlayer, D2D1::ColorF::Lime);
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

			if (vars::combat::ignore_sleepers && Player->HasFlags(16)) continue;
			if (vars::combat::ignore_npc && Player->IsNpc()) continue;
			if (vars::combat::ignore_team && LocalPlayer->IsTeamMate(Player->GetSteamID())) continue;
			if (Player->get_bone_pos(head).x == 0 || Player->get_bone_pos(head).y == 0 || Player->get_bone_pos(head).z == 0) continue;
			if (vars::combat::ignore_players) continue;
			if (Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), Player->get_bone_pos(head)) > vars::combat::range) continue;

			if (FOV > (CurFOV = GetFov(Player, BoneList(vars::stuff::BoneToAim))) && Player->GetHealth() > 0 && !vars::combat::lock_target) {
				FOV = CurFOV; vars::stor::closestPlayer = (uintptr_t)Player;
			}

		}
		if (strstr(buff, xorstr("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab"))) {
			uintptr_t BaseObject = read(ObjectClass + 0x30, uintptr_t);
			uintptr_t BaseEntity = read(BaseObject + 0x18, uintptr_t);
			uintptr_t Helicopter = read(BaseEntity + 0x28, uintptr_t);
			uintptr_t Transform = read(BaseObject + 0x8, uintptr_t);
			uintptr_t VisualState = read(Transform + 0x38, uintptr_t);
			float health = read(Helicopter + oHealth, float);
			float maxhealth = 10000.f;
			Vector3 pos = read(VisualState + 0x90, Vector3);
			Vector2 screenPos;
			if (utils::w2s(pos, screenPos)) {
				wchar_t buffer[256];
				wchar_t buffera[256];
				if (vars::visuals::patrol_heli) {
					swprintf(buffer, xorstr(L"Helicopter [%dm]"), (int)Math::Calc3D_Dist(LocalPlayer->get_bone_pos(head), pos));
					swprintf(buffera, xorstr(L"[%dHP]"), (int)health);
					Renderer::String(screenPos, buffer, D2D1::ColorF(0.5f, 0.54f, 1.f), true, true);
					Renderer::String(screenPos + Vector2(0, 15), buffera, D2D1::ColorF(0.5f, 0.54f, 1.f), true, true);
					Renderer::FillRectangle(Vector2{ screenPos - Vector2(30, 0) + Vector2(0, 25) }, Vector2{ 60 * (health / maxhealth), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
					Renderer::Rectangle(Vector2{ screenPos - Vector2(30, 0) + Vector2(0, 25) }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
				}
				if (health > 0.2 && !vars::combat::ignore_heli) {
					if ((FOV > (CurFOV = GetFovHeli(pos)))) {
						FOV = CurFOV; vars::stor::closestHeli = (uintptr_t)Helicopter; vars::stor::closestHeliObj = VisualState;
					}
				}
			}
		}
		if (vars::misc::auto_pickup && m_strstr(buff, xorstr("/collectable/"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				PickupItem(ent);
			}
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
		if (vars::ores::show_collectables) {
			miscvis(ObjectClass, buff, vars::ores::stone, vars::ores::show_distance, vars::ores::draw_distance, xorstr("stone-collectable.prefab"), xorstr(L"Stone Collectable"), D2D1::ColorF::Gray);
			miscvis(ObjectClass, buff, vars::ores::sulfur, vars::ores::show_distance, vars::ores::draw_distance, xorstr("sulfur-collectable.prefab"), xorstr(L"Sulfur Collectable"), D2D1::ColorF::Gold);
			miscvis(ObjectClass, buff, vars::ores::metal, vars::ores::show_distance, vars::ores::draw_distance, xorstr("metal-collectable.prefab"), xorstr(L"Metal Collectable"), D2D1::ColorF::SaddleBrown);
		}
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::ores::stone, vars::ores::show_distance, vars::ores::draw_distance, xorstr("stone-ore.prefab"), xorstr(L"Stone Ore"), D2D1::ColorF::Gray);
		miscvis(ObjectClass, buff, vars::ores::sulfur, vars::ores::show_distance, vars::ores::draw_distance, xorstr("sulfur-ore.prefab"), xorstr(L"Sulfur Ore"), D2D1::ColorF::Gold);
		miscvis(ObjectClass, buff, vars::ores::metal, vars::ores::show_distance, vars::ores::draw_distance, xorstr("metal-ore.prefab"), xorstr(L"Metal Ore"), D2D1::ColorF::SaddleBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::crates::supply, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr("supply_drop.prefab"), xorstr(L"Airdrop"), D2D1::ColorF::DarkCyan);
		miscvis(ObjectClass, buff, vars::visuals::crates::heli, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr("heli_crate.prefab"), xorstr(L"Heli Crate"), D2D1::ColorF::DarkGreen);
		miscvis(ObjectClass, buff, vars::visuals::crates::bradley, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr("bradley_crate.prefab"), xorstr(L"Bradley Crate"), D2D1::ColorF::GreenYellow);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::vehicles::minicopter, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr("minicopter.entity.prefab"), xorstr(L"Minicopter"), D2D1::ColorF::Blue);
		miscvis(ObjectClass, buff, vars::visuals::vehicles::scrapheli, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr("scraptransporthelicopter.prefab"), xorstr(L"Scrap Heli"), D2D1::ColorF::DarkBlue);
		miscvis(ObjectClass, buff, vars::visuals::vehicles::boat, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr("rowboat.prefab"), xorstr(L"Boat"), D2D1::ColorF::LightBlue);
		miscvis(ObjectClass, buff, vars::visuals::vehicles::rhib, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr("rhib.prefab"), xorstr(L"RHIB"), D2D1::ColorF::LightCyan);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::turrets::auto_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr("autoturret_deployed.prefab"), xorstr(L"Auto Turret"), D2D1::ColorF::Orange);
		miscvis(ObjectClass, buff, vars::visuals::turrets::flame_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr("flameturret.deployed.prefab"), xorstr(L"Flame Turret"), D2D1::ColorF::DarkOrange);
		miscvis(ObjectClass, buff, vars::visuals::turrets::shotgun_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr("guntrap.deployed.prefab"), xorstr(L"Shotgun Trap"), D2D1::ColorF::DimGray);
		miscvis(ObjectClass, buff, vars::visuals::turrets::landmine, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr("landmine.prefab"), xorstr(L"Landmine"), D2D1::ColorF::BlueViolet);
		miscvis(ObjectClass, buff, vars::visuals::turrets::bear_trap, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr("beartrap.prefab"), xorstr(L"Beartrap"), D2D1::ColorF::Brown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::other::hemp, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, xorstr("hemp-collectable.prefab"), xorstr(L"Hemp"), D2D1::ColorF::LimeGreen);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::base::boxes, vars::visuals::base::show_distance, vars::visuals::base::draw_distance, xorstr("box.wooden.large.prefab"), xorstr(L"Box"), D2D1::ColorF::RosyBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, vars::visuals::animals::bear, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr("bear.prefab"), xorstr(L"Bear"), D2D1::ColorF::SaddleBrown);
		miscvis(ObjectClass, buff, vars::visuals::animals::wolf, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr("agents/wolf/wolf.prefab"), xorstr(L"Wolf"), D2D1::ColorF::LightSlateGray);
		miscvis(ObjectClass, buff, vars::visuals::animals::pig, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr("boar.prefab"), xorstr(L"Pig"), D2D1::ColorF::DarkRed);
		miscvis(ObjectClass, buff, vars::visuals::animals::chicken, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr("agents/chicken/chicken.prefab"), xorstr(L"Chicken"), D2D1::ColorF::YellowGreen);
		miscvis(ObjectClass, buff, vars::visuals::animals::deer, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr("agents/horse/horse.prefab"), xorstr(L"Horse"), D2D1::ColorF::SandyBrown);
		// ---------------------------------------------------------
		miscvis(ObjectClass, buff, true, false, 2000.f, vars::stuff::testChar, xorstr(L"TESTITEM"), D2D1::ColorF::LimeGreen);
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
			if (tag == 20011) {
				DWORD64 dome = read(entity + 0x28, DWORD64); // TOD_Sky
				DWORD64 todCycle = read(dome + 0x38, DWORD64);
				DWORD64 todAtm = read(dome + 0x48, DWORD64);
				DWORD64 todDay = read(dome + 0x50, DWORD64);
				DWORD64 todSun = read(dome + 0x60, DWORD64);
				
				if (vars::misc::custom_time) {
					write(todCycle + 0x10, vars::misc::time, float);
				}
				if (vars::misc::bright_ambient) {
					write(todDay + 0x50, 1.f, float);
					write(todDay + 0x54, 1.f, float);
				}
			}
		}
	}
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	/*targeting shit*/
	if (TargetPlayer->get_bone_pos(head).x == 0 || TargetPlayer->get_bone_pos(head).y == 0 || TargetPlayer->get_bone_pos(head).z == 0) {
		vars::stor::closestPlayer = NULL;
	}
	if (TargetPlayer->IsNpc() && vars::combat::ignore_npc) {
		vars::stor::closestPlayer = NULL;
	}
	if (TargetPlayer->HasFlags(16) && vars::combat::ignore_sleepers) {
		vars::stor::closestPlayer = NULL;
	}
	if (LocalPlayer->IsTeamMate(TargetPlayer->GetSteamID()) && vars::combat::ignore_team) {
		vars::stor::closestPlayer = NULL;
	}
	if (TargetPlayer->GetHealth() < 0.2) {
		vars::combat::lock_target = false;
		vars::stor::closestPlayer = NULL;
	}
	if ((int)ceil(read(vars::stor::closestHeli + 0x20C, float)) < 0.2) {
		vars::stor::closestHeli = NULL;
		vars::stor::closestHeliObj = NULL;
	}
	if (vars::combat::ignore_players) {
		vars::stor::closestPlayer = NULL;
	}
	if (vars::combat::ignore_heli) {
		vars::stor::closestHeli = NULL;
		vars::stor::closestHeliObj = NULL;
	}
	if (read(vars::stor::closestHeliObj + 0x90, Vector3).y > 1500 || read(vars::stor::closestHeliObj + 0x90, Vector3).y < -1500) {
		vars::stor::closestHeli = NULL;
		vars::stor::closestHeliObj = NULL;
	}
	if (LP_isValid) {
		Aim((BasePlayer*)vars::stor::closestPlayer);
	}
	else LocalPlayer = nullptr;
}

void EntityThreadLoop() {
	if (!pViewMatrix || !mfound) {
		FindMatrix();
	}
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64);
	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);	for (int i = 0; i <= EntityCount; i++) {
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64); if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64); if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
		char* buff = name->stub;
		DWORD64 ent = read(Object + 0x28, UINT64);
		Item* weapon = LocalPlayer->GetActiveWeapon();
		DWORD64 active = read(weapon + oHeldEntity, DWORD64);
		char* classname = weapon->ClassName();
		
		bool weaponmelee = weapon && classname && (m_strcmp(classname, xorstr("BaseMelee")) || m_strcmp(classname, xorstr("Jackhammer")));
		if (m_strstr(buff, xorstr("player.prefab"))) {
			BasePlayer* lol = (BasePlayer*)ent;
			/*auto act = lol->GetActiveWeapon();
			if (act) {
				auto sprite = il2cpp::game::get_iconSprite(act);
				if (sprite) {
					auto texture = il2cpp::game::get_texture(sprite);
					if (texture) {
						auto rect = il2cpp::game::get_rect(sprite);
						il2cpp::game::set_color(Color(1, 1, 1, 1));
						il2cpp::game::DrawTexture(Rect(lol->get_bone_pos(head).x, lol->get_bone_pos(head).y, rect.wid / 7, rect.hei / 7), texture);
					}
				}
			}*/
			if (vars::players::chams && lol->GetHealth() > 0.2) {
				uintptr_t playermodel = read(ent + oPlayerModel, uintptr_t);
				uintptr_t multimesh = read(playermodel + 0x280, uintptr_t);
				if (!lol->HasFlags(16)) {
					if (LocalPlayer->IsTeamMate(lol->GetSteamID())) {
						DoChams(multimesh, Color(vars::colors::team_esp.x, vars::colors::team_esp.y, vars::colors::team_esp.z, vars::colors::team_esp.w));
					}
					else {
						DoChams(multimesh, Color(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, vars::colors::chams.w));
					}
				}
				else if (lol->HasFlags(16) && !vars::players::sleeperignore) {
					DoChams(multimesh, Color(vars::colors::sleeper_esp.x, vars::colors::sleeper_esp.y, vars::colors::sleeper_esp.z, vars::colors::sleeper_esp.w));
				}
			}
			if (vars::misc::auto_revive || vars::misc::insta_revive) {
				UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
				Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
				if (vars::misc::auto_revive && (BasePlayer*)ent && lol->HasFlags(64) && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
					PickupPlayer((BasePlayer*)ent);
				}
				if (vars::misc::insta_revive && (BasePlayer*)ent && lol->HasFlags(64) && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f && LocalPlayer->GetKeyState(ButtonS::USE)
					&& read(LocalPlayer + 0x4E8, uintptr_t) == ent) {
					PickupPlayer((BasePlayer*)ent);
				}
			}
			if (vars::combat::silent_melee && weaponmelee && Math::Calc3D_Dist(lol->get_bone_pos(head), LocalPlayer->get_bone_pos(head)) <= 3.5f) {
				Target target = TargetMeleeTest((BasePlayer*)ent, active);
				DoMeleeAttack(target, active, true);
			}
		}
		if (vars::misc::auto_farm_ore && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("OreHotSpot"))) {
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
		if (vars::weapons::SilentTree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeEntity"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, Vector3(utils::GetEntityPosition(gameObject).x, LocalPlayer->get_bone_pos(head).y, utils::GetEntityPosition(gameObject).z)) >= 2.f) { continue; }
			bool iskill = read(read(Object + 0x28, uintptr_t) + 0x15C, bool);
			if (!iskill) {
				target.entity = (BasePlayer*)ent;
			}
		}
		if (vars::weapons::SilentTree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeMarker"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) >= 2.f) { continue; }
			target.valid = true;
			target.position = utils::GetEntityPosition(gameObject);
			if (target.entity) {
				DoMeleeAttack(target, active, false);
			}
		}*/
		if (vars::misc::auto_farm_tree && weaponmelee && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("TreeEntity"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) >= 2.f) { continue; }
			Target target = Target();
			target.valid = true;
			target.position = Vector3(utils::GetEntityPosition(gameObject).x, LocalPlayer->get_bone_pos(head).y, utils::GetEntityPosition(gameObject).z);
			target.entity = (BasePlayer*)ent;
			DoMeleeAttack(target, active, false);
		}
		//========================================================================================================================================================================================
		if (vars::misc::annoyer && m_strstr((char*)read(read(ent, DWORD64) + 0x10, DWORD64), xorstr("Door"))) {
			UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
			Vector3 local = utils::ClosestPoint(LocalPlayer, utils::GetEntityPosition(gameObject));
			if (ent && Math::Calc3D_Dist(local, utils::GetEntityPosition(gameObject)) < 3.f) {
				SpamKnock(ent);
			}
		}
	}
}