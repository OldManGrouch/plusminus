namespace radar {
	//float range = vars::visuals::radar::range/*161.1f*/;
	//float size = vars::visuals::radar::size/*121.5f*/;

	void do_dot(DWORD64 ObjectClass, DWORD64 Object, char* buff, char* target, D2D1::ColorF clr) {
		Vector3 local = LocalPlayer::Entity()->get_bone_pos(head);
		if (strstr(buff, target)) {
			uintptr_t BaseObject = read(ObjectClass + 0x30, uintptr_t);
			uintptr_t Transform = read(BaseObject + 0x8, uintptr_t);
			uintptr_t VisualState = read(Transform + 0x38, uintptr_t);
			Vector3 pos = read(VisualState + 0x90, Vector3);
			float y = local.x - pos.x;
			float x = local.z - pos.z;

			float dist = Math::Distance_3D(local, pos);
			Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity()->eyes()->get_rotation());
			float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
			float PointPos_X = dist * cos(num * 0.0174532924f);
			float PointPos_Y = dist * sin(num * 0.0174532924f);
			PointPos_X = PointPos_X * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;
			PointPos_Y = PointPos_Y * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;

			float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
			float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;

			Vector2 point = Vector2(vars::visuals::radar::x + vars::visuals::radar::size / 2.f + PointPos_X, vars::visuals::radar::y + vars::visuals::radar::size / 2.f + PointPos_Y);
			if (Math::Distance_2D(point, Vector2(mid_x, mid_y)) < vars::visuals::radar::size) {
				Renderer::FillCircle(point, clr, 2.5f);
			}
		}
	}
	void radar_bg() {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= mid_x - vars::visuals::radar::size && p.x <= mid_x + vars::visuals::radar::size) {
				if (p.y >= mid_y - vars::visuals::radar::size && p.y <= mid_y + vars::visuals::radar::size) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						vars::visuals::radar::x = p.x - (vars::visuals::radar::size / 2);
						vars::visuals::radar::y = p.y - (vars::visuals::radar::size / 2);
					}
				}
			}
		}
		Renderer::FillCircle(Vector2(mid_x, mid_y), D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f), vars::visuals::radar::size);
		Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f), vars::visuals::radar::size);
		Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF::Red, 2.5f);
	}
	void radar_logic(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		if (LocalPlayer::Entity()) {
			Vector3 local = LocalPlayer::Entity()->get_bone_pos(head);
			if (strstr(buff, xorstr("player.prefab")) || strstr(buff, xorstr("scientist")) && !strstr(buff, xorstr("prop")) && !strstr(buff, xorstr("corpse"))) {
				BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
				if (!read(Player + 0x4A8, DWORD64)) return;
				Vector3 ply = Player->get_bone_pos(head);
				float dist = Math::Distance_3D(local, ply);
				float y = local.x - ply.x;
				float x = local.z - ply.z;

				Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity()->eyes()->get_rotation()/*pViewMatrix->GetRotation()*/);
				float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
				float PointPos_X = dist * cos(num * 0.0174532924f);
				float PointPos_Y = dist * sin(num * 0.0174532924f);
				PointPos_X = PointPos_X * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;
				PointPos_Y = PointPos_Y * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;

				Vector2 point = Vector2(vars::visuals::radar::x + vars::visuals::radar::size / 2.f + PointPos_X, vars::visuals::radar::y + vars::visuals::radar::size / 2.f + PointPos_Y);

				if (Math::Distance_2D(point, Vector2(mid_x, mid_y)) < vars::visuals::radar::size) {
					if (!Player->IsNpc()) {
						if (!Player->HasFlags(PlayerFlags::Sleeping)) {
							if (LocalPlayer::Entity()->is_teammate(Player->GetSteamID())) {
								Renderer::FillCircle(point, D2D1::ColorF::Lime, 2.5f);
							}
							else {
								if (Player->health() <= 0) {
									Renderer::FillCircle(point, D2D1::ColorF::Red, 2.5f);
								}
								else {
									Renderer::FillCircle(point, D2D1::ColorF::White, 2.5f);
								}
							}
						}
						else if (Player->HasFlags(PlayerFlags::Sleeping) && !vars::players::sleeperignore) {
							Renderer::FillCircle(point, D2D1::ColorF::Orange, 2.5f);
						}
					}
					else if (Player->IsNpc() && (vars::npc::box || vars::npc::name || vars::npc::tracers || vars::npc::healthbar)) {
						Renderer::FillCircle(point, D2D1::ColorF::Yellow, 2.5f);
					}
				}
			}
			if (vars::visuals::patrol_heli) {
				do_dot(ObjectClass, Object, buff, xorstr("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab"), D2D1::ColorF(0.5f, 0.54f, 1.f));
			}
		}
	}
}
namespace otherEsp {
	void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, D2D1::ColorF color) {
		if (boolean) {
			if (strstr(buff, substring)) {
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				Vector2 screen_Pos;
				if (utils::w2s(utils::GetEntityPosition(gameObject), screen_Pos)) {
					if ((int)Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), utils::GetEntityPosition(gameObject)) <= drawDistance) {
						//wchar_t distance[64];
						//_swprintf(distance, L"[%.2f m]", Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), utils::GetEntityPosition(gameObject)));
						//wchar_t text[64];
						//_swprintf(text, targettext);
						//Renderer::String({ screen_Pos.x, screen_Pos.y }, text, color, true, true);
						Renderer::Text({screen_Pos.x, screen_Pos.y}, color, xorstr(L"%s"), targettext);
						if (showDistance) {
							//Renderer::String(screen_Pos + Vector2(0, 15), distance, color, true, true);
							Renderer::Text(screen_Pos + Vector2(0, 15), color, xorstr(L"[%.2f m]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), utils::GetEntityPosition(gameObject)));
						}
					}
				}
			}
		}
	}
	void bradley(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::bradley_apc) {
			if (strstr(buff, xorstr("bradleyapc.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				BaseCombatEntity* bradley = read(Object + 0x28, BaseCombatEntity*);
				Vector3 pos = utils::GetEntityPosition(object);
				int distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				float health = bradley->health( );
				Vector2 screen;
				if (utils::w2s(pos, screen)) {
					//wchar_t buffer[256];
					//wchar_t buffera[256];
					//swprintf(buffer, xorstr(L"Bradley APC [%.2fm]"), Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos));
					//swprintf(buffera, xorstr(L"[%.2f HP]"), health);
					if (health > 0) {
						//Renderer::String(screen, buffer, D2D1::ColorF::Red, true, true);
						Renderer::Text(screen, D2D1::ColorF::Red, xorstr(L"Bradley APC [%.2fm]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos));

						Renderer::FillRectangle(Vector2{ screen - Vector2(30, 0) + Vector2(0, 15) }, Vector2{ 60 * (health / 1000.f), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						Renderer::Rectangle(Vector2{ screen - Vector2(30, 0) + Vector2(0, 15) }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
						//Renderer::String(screen + Vector2(0, 15), buffera, D2D1::ColorF::Red, true, true);
					}
				}
			}
		}
	}
	void corpse(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::other::corpse) {
			if (strstr(buff, xorstr("player_corpse.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 corpse = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					//wchar_t cName[0x100];
					//wchar_t cDist[0x100];
					auto* corpsename = reinterpret_cast<pUncStr>(read(corpse + 0x2A8, DWORD64));
					//_swprintf(cName, xorstr(L"Corpse | %s"), corpsename->str);
					//Renderer::String({ screen.x, screen.y }, cName, D2D1::ColorF::Firebrick, true, true);
					Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Firebrick, xorstr(L"Corpse | %s"), corpsename->str);
					if (vars::visuals::other::show_distance) {
						//_swprintf(cDist, xorstr(L"[%.2f m]"), distance);
						//Renderer::String(screen + Vector2(0, 15), cDist, D2D1::ColorF::Firebrick, true, true);
						Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Firebrick, xorstr(L"[%.2f m]"), distance);
					}
				}
			}
		}
	}
	void tc(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::tc) {
			if (strstr(buff, xorstr("cupboard.tool.deployed.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 cupboard = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					int pos = 15;
					//wchar_t TCName[0x100];
					//wchar_t TCDist[0x100];
					int upkeep = read(cupboard + 0x558, float);
					
					//_swprintf(TCName, xorstr(L"Tool Cupboard | %d hours"), upkeep / 60);
					//Renderer::String({ screen.x, screen.y }, TCName, D2D1::ColorF::YellowGreen, true, true);
					Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::YellowGreen, xorstr(L"Tool Cupboard | %d hours"), upkeep / 60);
					if (vars::visuals::base::show_distance) {
						//_swprintf(TCDist, xorstr(L"[%.2f m]"), distance);
						//Renderer::String(screen + Vector2(0, 15), TCDist, D2D1::ColorF::YellowGreen, true, true);
						Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::YellowGreen, xorstr(L"[%.2f m]"), distance);
						pos += 15;
					}
					uintptr_t authedPly = read(cupboard + 0x568, uintptr_t);
					List<PlayerNameID*>* authedPly_list = read(authedPly + 0x10, List<PlayerNameID*>*);
					authedPly_list->for_each([&](PlayerNameID* authorizedPlayer, int32_t idx) {
						if (authorizedPlayer) {
							auto user = authorizedPlayer->username();
							Renderer::String(screen + Vector2(0, pos), user, D2D1::ColorF::YellowGreen, true, true);
							pos += 15;
						}
						});
				}
			}
		}
	}
	void sleepingbag(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::sleeping_bag) {
			if (strstr(buff, xorstr("sleepingbag_leather_deployed.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 bag = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					//wchar_t bagName[0x100];
					//wchar_t bagDist[0x100];
					auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x410, DWORD64));
					//_swprintf(bagName, xorstr(L"Sleeping Bag | %s"), bagname->str);
					//Renderer::String({ screen.x, screen.y }, bagName, D2D1::ColorF::Olive, true, true);
					Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Olive, xorstr(L"Sleeping Bag | %s"), bagname->str);
					if (vars::visuals::base::show_distance) {
						//_swprintf(bagDist, xorstr(L"[%.2f m]"), distance);
						//Renderer::String(screen + Vector2(0, 15), bagDist, D2D1::ColorF::Olive, true, true);
						Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Olive, xorstr(L"[%.2f m]"), distance);
					}
				}
			}
		}
	}
	void bed(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::bed) {
			if (strstr(buff, xorstr("bed_deployed.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 bag = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					//wchar_t bagName[0x100];
					//wchar_t bagDist[0x100];
					auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x410, DWORD64));
					//_swprintf(bagName, xorstr(L"Bed | %s"), bagname->str);
					//Renderer::String({ screen.x, screen.y }, bagName, D2D1::ColorF::OliveDrab, true, true);
					Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OliveDrab, xorstr(L"Bed | %s"), bagname->str);
					if (vars::visuals::base::show_distance) {
						//_swprintf(bagDist, xorstr(L"[%.2f m]"), distance);
						//Renderer::String(screen + Vector2(0, 15), bagDist, D2D1::ColorF::OliveDrab, true, true);
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OliveDrab, xorstr(L"[%.2f m]"), distance);
					}
				}
			}
		}
	}
	void stash(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsHidden)(uintptr_t);
		if (vars::visuals::other::stash) {
			if (strstr(buff, xorstr("small_stash_deployed.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 stash = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					//wchar_t sName[0x100];
					//wchar_t sNameH[0x100];
					//wchar_t sDist[0x100];
					//_swprintf(sNameH, xorstr(L"Stash [Hidden]"));
					//_swprintf(sName, xorstr(L"Stash"));
					if (((IsHidden)(vars::stor::gBase + CO::IsHidden))(stash)) {
						//Renderer::String({ screen.x, screen.y }, sNameH, D2D1::ColorF::Yellow, true, true);
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Yellow, xorstr(L"Stash [Hidden]"));
					}
					else {
						//Renderer::String({ screen.x, screen.y }, sName, D2D1::ColorF::Yellow, true, true);
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Yellow, xorstr(L"Stash [Open]"));
					}
					if (vars::visuals::other::show_distance) {
						//_swprintf(sDist, xorstr(L"[%.2f m]"), distance);
						//Renderer::String(screen + Vector2(0, 15), sDist, D2D1::ColorF::Yellow, true, true);
						Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Yellow, xorstr(L"[%.2f m]"), distance);
					}
				}
			}
		}
	}
	void hackablecrate(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsBeingHacked)(uintptr_t);
		typedef bool(__stdcall* IsFullyHacked)(uintptr_t);
		if (vars::visuals::crates::chinook) {
			if (strstr(buff, xorstr("codelockedhackablecrate.prefab"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 crate = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen)) {
					//wchar_t crateName[0x100];
					//wchar_t crateDist[0x100];
					uintptr_t timerText = read(crate + 0x440, uintptr_t);
					auto* m_Text = reinterpret_cast<pUncStr>(read(timerText + 0xD0, DWORD64));
					D2D1::ColorF color = D2D1::ColorF::OrangeRed;
					if (!((IsFullyHacked)(vars::stor::gBase + CO::IsFullyHacked))(crate)) {
						if (((IsBeingHacked)(vars::stor::gBase + CO::IsBeingHacked))(crate)) {
							color = D2D1::ColorF::LightGoldenrodYellow;
							//_swprintf(crateName, xorstr(L"Chinook Crate | %s"), m_Text->str);
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::LightGoldenrodYellow, xorstr(L"Chinook Crate | %s"), m_Text->str);
						}
						else {
							color = D2D1::ColorF::OrangeRed;
							//_swprintf(crateName, xorstr(L"Chinook Crate"));
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OrangeRed, xorstr(L"Chinook Crate"));
						}
					}
					else {
						color = D2D1::ColorF::LightSeaGreen;
						//_swprintf(crateName, xorstr(L"Chinook Crate [Open]"));
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::LightSeaGreen, xorstr(L"Chinook Crate [Open]"));
					}
					//Renderer::String({ screen.x, screen.y }, crateName, color, true, true);
					//_swprintf(crateDist, xorstr(L"[%.2f m]"), distance);
					//Renderer::String(screen + Vector2(0, 15), crateDist, color, true, true);
					Renderer::Text({screen.x, screen.y}, color, xorstr(L"[%.2f m]"), distance);
				}
			}
		}
	}
	void world(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef uintptr_t(__stdcall* GetItem)(uintptr_t);
		if (vars::visuals::other::dropped_items) {
			if (strstr(buff, xorstr("world"))) {
				DWORD64 object = read(ObjectClass + 0x30, DWORD64);
				DWORD64 item = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					//wchar_t itemName[0x100];
					//wchar_t itemDist[0x100];
					uintptr_t Item = read(item + 0x150, uintptr_t);
					uintptr_t itemDefinition = read(Item + 0x20, uintptr_t);
					uintptr_t displayName = read(itemDefinition + 0x28, uintptr_t);
					auto* english = reinterpret_cast<pUncStr>(read(displayName + 0x18, DWORD64)); // get name of item
					int amount = read(Item + 0x30, int);

					//_swprintf(itemName, xorstr(L"%s [x%d]"), english->str, amount);
					std::wstring eng = std::wstring(english->str);
					if (!(eng.find(xorstr(L"Arrow")) != std::wstring::npos) && !(eng.find(xorstr(L"Nails")) != std::wstring::npos)) {
						//Renderer::String({ screen.x, screen.y }, itemName, D2D1::ColorF::BlanchedAlmond, true, true);
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::BlanchedAlmond, xorstr(L"%s [x%d]"), english->str, amount);
						if (vars::visuals::other::show_distance) {
							//_swprintf(itemDist, xorstr(L"[%.2f m]"), distance);
							//Renderer::String(screen + Vector2(0, 15), itemDist, D2D1::ColorF::BlanchedAlmond, true, true);
							Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::BlanchedAlmond, xorstr(L"[%.2f m]"), distance);
						}
					}
				}
			}
		}
	}
}
void Skeleton(BasePlayer* BasePlayer, D2D1::ColorF color) {
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!utils::w2s(BasePlayer->get_bone_pos(Bones[j]), BonesPos[j]))
			return;
	}
	for (int j = 0; j < 15; j += 3) {
		Renderer::Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, color, 1.5f, true);
		Renderer::Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, color, 1.5f, true);
	}
	Renderer::Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, color, 1.5f, true);
	Renderer::Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, color, 1.5f, true);
	Renderer::Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, color, 1.5f, true);
	Renderer::Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, color, 1.5f, true);
}
void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color) {
	Renderer::Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, color);
	Renderer::Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, color);

	Renderer::Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, color);
	Renderer::Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, color);

	Renderer::Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, color);
	Renderer::Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);

	Renderer::Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, color);
	Renderer::Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Renderer::Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);
}
typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, D2D1::ColorF color) {
	CBounds bounds = CBounds();

	IsDucked ducked = (IsDucked)(vars::stor::gBase + CO::IsDucked);
	if (ducked(player)) {
		bounds.center = player->get_bone_pos(l_foot).midPoint(player->get_bone_pos(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasFlags(PlayerFlags::Wounded) || player->HasFlags(PlayerFlags::Sleeping)) {
			bounds.center = player->get_bone_pos(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = player->get_bone_pos(l_foot).midPoint(player->get_bone_pos(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}
	
	float y = Math::EulerAngles(player->eyes()->get_rotation()).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);

	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (utils::w2s(frontTopLeft, frontTopLeft_2d) && 
		utils::w2s(frontTopRight, frontTopRight_2d) && 
		utils::w2s(frontBottomLeft, frontBottomLeft_2d) &&
		utils::w2s(frontBottomRight, frontBottomRight_2d) && 
		utils::w2s(backTopLeft, backTopLeft_2d) && 
		utils::w2s(backTopRight, backTopRight_2d) &&
		utils::w2s(backBottomLeft, backBottomLeft_2d) && 
		utils::w2s(backBottomRight, backBottomRight_2d)) {

		Renderer::Line(frontTopLeft_2d, frontTopRight_2d, color, 1.5f, true);
		Renderer::Line(frontTopRight_2d, frontBottomRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, frontBottomLeft_2d, color, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, frontTopLeft_2d, color, 1.5f, true);
		Renderer::Line(backTopLeft_2d, backTopRight_2d, color, 1.5f, true);
		Renderer::Line(backTopRight_2d, backBottomRight_2d, color, 1.5f, true);
		Renderer::Line(backBottomRight_2d, backBottomLeft_2d, color, 1.5f, true);
		Renderer::Line(backBottomLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Renderer::Line(frontTopLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Renderer::Line(frontTopRight_2d, backTopRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, backBottomRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, backBottomLeft_2d, color, 1.5f, true);
	}
}
void ESP(BasePlayer* BP, BasePlayer* LP, D2D1::ColorF color) {
	if (vars::players::sleeperignore && BP->HasFlags(PlayerFlags::Sleeping)) return;
	if (!BP) return;
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->get_bone_pos(r_foot), tempFeetR) && utils::w2s(BP->get_bone_pos(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->get_bone_pos(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->get_bone_pos(l_foot).midPoint(BP->get_bone_pos(r_foot));
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (utils::w2s(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
				if (vars::players::fillbox) {
					if ((int)BP->health() > 0) {
						if (LocalPlayer::Entity()->is_teammate(BP->GetSteamID())) {
							Renderer::FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0.f, 0.4f, 0.f, 0.4f));
						}
						else {
							Renderer::FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
						}
					}
				}
				if (vars::players::box) {
					if (vars::players::boxstyle == 0) {
						Renderer::Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF::Black, 3.f);
						Renderer::Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, color);
						//Renderer::FillGradientRoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, color, 5.f, 5.f);d
					}
					if (vars::players::boxstyle == 1) {
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
					}
					if (vars::players::boxstyle == 2) {
						Box3D(BP, color);
					}
				}
				if (vars::players::name) { 
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f }, BP->_displayName(), color, true, true);
					CurPos += 15;
				}
				if (vars::players::weapon) {
					if (BP->health() > 0) {
						Item* weapon = BP->GetActiveWeapon();
						//wchar_t name[64];
						//if (!weapon) {
						//	_swprintf(name, L"---");
						//}
						//else {
						//	_swprintf(name, L"%s [x%d]", weapon->get_name(), weapon->count());
						//}
						//Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f }, name, color, true, true);
						if (weapon) {
							Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f}, color, xorstr(L"%s [x%d]"), weapon->get_name( ), weapon->count( ));
							CurPos += 15;
						}
					}
				}
				if (vars::players::healthdist) {
					//wchar_t s[64];
					//_swprintf(s, L"[%.2fM] [%dHP]", Math::Distance_3D(LP->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health());
					//Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f }, s, color, true, true);
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f}, color, xorstr(L"[%.2fM] [%dHP]"), Math::Distance_3D(LP->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health( ));
					CurPos += 15;
				}
				if (vars::players::healthbar) {
					int health = (int)BP->health();
					float maxheal = 100.f;
					if (vars::players::healthbarstyle == 0) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), BP->get_bone_pos(head)) < 201) {
							if ((int)BP->health() <= 33) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)BP->health() >= 67) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							Renderer::Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (vars::players::healthbarstyle == 1) {
						if ((int)BP->health() <= 33) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->health() >= 67) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Renderer::Rectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
					}
				}
				if (vars::players::tracers && !BP->HasFlags(PlayerFlags::Sleeping)) {
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					static Vector2 startPos;
					if (vars::players::tracers_pos == 0) {
						startPos = Vector2(screenX / 2.f, screenY - 200.f);
					}
					if (vars::players::tracers_pos == 1) {
						startPos = Vector2(screenX / 2, screenY / 2);
					}
					if ((int)BP->health() > 0) {
						Renderer::Line(startPos, tempHead, color, 0.5f);
					}
				}
			}
		}
	}
}
void NPCESP(BasePlayer* BP, BasePlayer* LP, D2D1::ColorF color) {
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->get_bone_pos(r_foot), tempFeetR) && utils::w2s(BP->get_bone_pos(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->get_bone_pos(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->get_bone_pos(l_foot).midPoint(BP->get_bone_pos(r_foot));
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (utils::w2s(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
				if (vars::npc::fillbox) {
					Renderer::FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
				}
				if (vars::npc::box) {
					if (vars::npc::boxstyle == 0) {
						Renderer::Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF::Black, 3.f);
						Renderer::Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, color);
					}
					if (vars::npc::boxstyle == 1) {
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
					}
				}
				if (vars::npc::name) {
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f }, xorstr(L"NPC"), color, true, true);
					CurPos2 += 15;
				}
				if (vars::npc::weapon) {
					const wchar_t* ActiveWeaponName;
					Item* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->get_name();
					if (!ActWeapon) {
						ActiveWeaponName = xorstr(L"---");
					}
					else {
						ActiveWeaponName = ActWeapon->get_name();
					}
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f }, ActiveWeaponName, color, true, true);
					CurPos2 += 15;
				}
				if (vars::npc::healthdist) {
					//wchar_t s[64];
					//_swprintf(s, L"[%.2fM] [%dHP]", Math::Distance_3D(LP->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health());
					//Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f }, s, color, true, true);
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f}, color, xorstr(L"[%.2fM] [%dHP]"), Math::Distance_3D(LP->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health( ));
					CurPos2 += 15;
				}
				if (vars::npc::healthbar) {
					int health = (int)BP->health();
					float maxheal = 150.f;
					if (vars::npc::healthbarstyle == 0) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), BP->get_bone_pos(head)) < 201) {
							if ((int)BP->health() <= 33) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)BP->health() >= 67) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							Renderer::Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (vars::npc::healthbarstyle == 1) {
						if ((int)BP->health() <= 33) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->health() >= 67) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Renderer::Rectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
					}
				}
				if (vars::npc::tracers) {
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 200.f);
					Renderer::Line(startPos, tempHead, color, 0.5f);
				}
			}
		}
	}
}