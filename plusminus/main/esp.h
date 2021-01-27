namespace otherEsp {
	void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, D2D1::ColorF color) {
		if (boolean) {
			if (strstr(buff, substring)) {
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				Vector2 screen_Pos;
				if (utils::w2s(utils::GetEntityPosition(gameObject), screen_Pos)) {
					if ((int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), utils::GetEntityPosition(gameObject)) <= drawDistance) {
						wchar_t distance[64];
						_swprintf(distance, L"[%d m]", (int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), utils::GetEntityPosition(gameObject)));
						wchar_t text[64];
						_swprintf(text, targettext);
						Renderer::String({ screen_Pos.x, screen_Pos.y }, text, color, true, true);
						if (showDistance) {
							Renderer::String(screen_Pos + Vector2(0, 15), distance, color, true, true);
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
				DWORD64 bradley = read(Object + 0x28, DWORD64);
				Vector3 pos = utils::GetEntityPosition(object);
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				int health = read(bradley + oHealth, float);
				Vector2 screen;
				if (utils::w2s(pos, screen)) {
					wchar_t buffer[256];
					wchar_t buffera[256];
					swprintf(buffer, xorstr(L"Bradley APC [%dm]"), (int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos));
					swprintf(buffera, xorstr(L"[%d HP]"), health);
					if (health > 0.2) {
						Renderer::String(screen, buffer, D2D1::ColorF::Red, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					wchar_t cName[0x100];
					wchar_t cDist[0x100];
					auto* corpsename = reinterpret_cast<pUncStr>(read(corpse + 0x2A8, DWORD64));
					_swprintf(cName, xorstr(L"Corpse | %s"), corpsename->str);
					Renderer::String({ screen.x, screen.y }, cName, D2D1::ColorF::Firebrick, true, true);
					if (vars::visuals::other::show_distance) {
						_swprintf(cDist, xorstr(L"[%d m]"), distance);
						Renderer::String(screen + Vector2(0, 15), cDist, D2D1::ColorF::Firebrick, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					wchar_t TCName[0x100];
					wchar_t TCDist[0x100];
					int upkeep = read(cupboard + 0x500, float);
					_swprintf(TCName, xorstr(L"Tool Cupboard | %d min."), upkeep);
					Renderer::String({ screen.x, screen.y }, TCName, D2D1::ColorF::YellowGreen, true, true);
					if (vars::visuals::base::show_distance) {
						_swprintf(TCDist, xorstr(L"[%d m]"), distance);
						Renderer::String(screen + Vector2(0, 15), TCDist, D2D1::ColorF::YellowGreen, true, true);
					}
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					wchar_t bagName[0x100];
					wchar_t bagDist[0x100];
					auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x410, DWORD64));
					_swprintf(bagName, xorstr(L"Sleeping Bag | %s"), bagname->str);
					Renderer::String({ screen.x, screen.y }, bagName, D2D1::ColorF::Olive, true, true);
					if (vars::visuals::base::show_distance) {
						_swprintf(bagDist, xorstr(L"[%d m]"), distance);
						Renderer::String(screen + Vector2(0, 15), bagDist, D2D1::ColorF::Olive, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
					wchar_t bagName[0x100];
					wchar_t bagDist[0x100];
					auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x410, DWORD64));
					_swprintf(bagName, xorstr(L"Bed | %s"), bagname->str);
					Renderer::String({ screen.x, screen.y }, bagName, D2D1::ColorF::OliveDrab, true, true);
					if (vars::visuals::base::show_distance) {
						_swprintf(bagDist, xorstr(L"[%d m]"), distance);
						Renderer::String(screen + Vector2(0, 15), bagDist, D2D1::ColorF::OliveDrab, true, true);
					}
				}
			}
		}
	}
	void explo(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (strstr(buff, xorstr("c4_explosion.prefab"))) {
			DWORD64 object = read(ObjectClass + 0x30, DWORD64);
			Vector3 pos = utils::GetEntityPosition(object);
			int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
			Vector2 screen;
			if (utils::w2s(pos, screen)) {
				wchar_t explosionc4[0x100];
				_swprintf(explosionc4, xorstr(L"C4 Explosion [%d]"), distance);
				Renderer::String({ screen.x, screen.y }, explosionc4, D2D1::ColorF::Red, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					wchar_t sName[0x100];
					wchar_t sNameH[0x100];
					wchar_t sDist[0x100];
					_swprintf(sNameH, xorstr(L"Stash [Hidden]"));
					_swprintf(sName, xorstr(L"Stash"));
					if (((IsHidden)(vars::stor::gBase + CO::IsHidden))(stash)) {
						Renderer::String({ screen.x, screen.y }, sNameH, D2D1::ColorF::Yellow, true, true);
					}
					else {
						Renderer::String({ screen.x, screen.y }, sName, D2D1::ColorF::Yellow, true, true);
					}
					if (vars::visuals::other::show_distance) {
						_swprintf(sDist, xorstr(L"[%d m]"), distance);
						Renderer::String(screen + Vector2(0, 15), sDist, D2D1::ColorF::Yellow, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen)) {
					wchar_t crateName[0x100];
					wchar_t crateDist[0x100];
					uintptr_t timerText = read(crate + 0x440, uintptr_t);
					auto* m_Text = reinterpret_cast<pUncStr>(read(timerText + 0xD0, DWORD64));
					D2D1::ColorF color = D2D1::ColorF::OrangeRed;
					if (!((IsFullyHacked)(vars::stor::gBase + CO::IsFullyHacked))(crate)) {
						if (((IsBeingHacked)(vars::stor::gBase + CO::IsBeingHacked))(crate)) {
							color = D2D1::ColorF::LightGoldenrodYellow;
							_swprintf(crateName, xorstr(L"Chinook Crate | %s"), m_Text->str);
						}
						else {
							color = D2D1::ColorF::OrangeRed;
							_swprintf(crateName, xorstr(L"Chinook Crate"));
						}
					}
					else {
						color = D2D1::ColorF::LightSeaGreen;
						_swprintf(crateName, xorstr(L"Chinook Crate [Open]"));
					}
					Renderer::String({ screen.x, screen.y }, crateName, color, true, true);
					_swprintf(crateDist, xorstr(L"[%d m]"), distance);
					Renderer::String(screen + Vector2(0, 15), crateDist, color, true, true);
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
				int distance = Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
					wchar_t itemName[0x100];
					wchar_t itemDist[0x100];
					uintptr_t Item = read(item + 0x150, uintptr_t);
					uintptr_t itemDefinition = read(Item + 0x20, uintptr_t);
					uintptr_t displayName = read(itemDefinition + 0x28, uintptr_t);
					auto* english = reinterpret_cast<pUncStr>(read(displayName + 0x18, DWORD64)); // get name of item
					int amount = read(Item + 0x30, int);

					_swprintf(itemName, xorstr(L"%s [%d]"), english->str, amount);
					std::wstring eng = std::wstring(english->str);
					if (!(eng.find(xorstr(L"Arrow")) != std::wstring::npos) && !(eng.find(xorstr(L"Nails")) != std::wstring::npos)) {
						Renderer::String({ screen.x, screen.y }, itemName, D2D1::ColorF::BlanchedAlmond, true, true);
						if (vars::visuals::other::show_distance) {
							_swprintf(itemDist, xorstr(L"[%d m]"), distance);
							Renderer::String(screen + Vector2(0, 15), itemDist, D2D1::ColorF::BlanchedAlmond, true, true);
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
		if (!utils::w2s(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
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
inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color) {
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
inline void Box3D(BasePlayer* player) {
	CBounds bounds = CBounds();

	IsDucked ducked = (IsDucked)(vars::stor::gBase + 0x29A930);
	if (ducked(player)) {
		bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasFlags(PlayerFlags::Wounded) || player->HasFlags(PlayerFlags::Sleeping)) {
			bounds.center = player->GetBoneByID(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}
	
	float y = Math::EulerAngles(player->GetRotationByID(head)).y;
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
	if (utils::w2s(frontTopLeft, frontTopLeft_2d) && utils::w2s(frontTopRight, frontTopRight_2d) && utils::w2s(frontBottomLeft, frontBottomLeft_2d) &&
		utils::w2s(frontBottomRight, frontBottomRight_2d) && utils::w2s(backTopLeft, backTopLeft_2d) && utils::w2s(backTopRight, backTopRight_2d) &&
		utils::w2s(backBottomLeft, backBottomLeft_2d) && utils::w2s(backBottomRight, backBottomRight_2d)) {

		Renderer::Line(frontTopLeft_2d, frontTopRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontTopRight_2d, frontBottomRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, frontBottomLeft_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, frontTopLeft_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(backTopLeft_2d, backTopRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(backTopRight_2d, backBottomRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(backBottomRight_2d, backBottomLeft_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(backBottomLeft_2d, backTopLeft_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontTopLeft_2d, backTopLeft_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontTopRight_2d, backTopRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, backBottomRight_2d, D2D1::ColorF::White, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, backBottomLeft_2d, D2D1::ColorF::White, 1.5f, true);
	}
}
void ESP(BasePlayer* BP, BasePlayer* LP, D2D1::ColorF color) {
	if (vars::players::sleeperignore && BP->HasFlags(16)) return;
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->GetBoneByID(r_foot), tempFeetR) && utils::w2s(BP->GetBoneByID(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (utils::w2s(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
				if (vars::players::fillbox) {
					if ((int)BP->GetHealth() > 0) {
						if (LocalPlayer->IsTeamMate(BP->GetSteamID())) {
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
						//Renderer::FillGradientRoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, color, 5.f, 5.f);
					}
					if (vars::players::boxstyle == 1) {
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
					}
					if (vars::players::boxstyle == 2) {
						Box3D(BP);
					}
				}
				if (vars::players::name) {
					wchar_t name[64];
					_swprintf(name, L"%s", BP->GetName());
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f }, name, color, true, true);
					CurPos += 15;
				}
				if (vars::players::weapon) {
					const wchar_t* ActiveWeaponName;
					BaseProjectile* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon) {
						ActiveWeaponName = L"---";
					}
					else {
						ActiveWeaponName = ActWeapon->GetName();
					}
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f }, ActiveWeaponName, color, true, true);
					CurPos += 15;
				}
				if (vars::players::healthdist) {
					wchar_t s[64];
					_swprintf(s, L"[%dM] [%dHP]", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)), (int)BP->GetHealth());
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f }, s, color, true, true);
					CurPos += 15;
				}
				if (vars::players::healthbar) {
					int health = (int)BP->GetHealth();
					float maxheal = 100.f;
					if (vars::players::healthbarstyle == 0) {
						if ((int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201) {
							if ((int)BP->GetHealth() <= 33) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)BP->GetHealth() >= 67) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							Renderer::Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (vars::players::healthbarstyle == 1) {
						if ((int)BP->GetHealth() <= 33) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 67) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Renderer::Rectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 60, 6 }, D2D1::ColorF::Black, 0.5f);
					}
				}
				if (vars::players::tracers && !BP->HasFlags(16)) {
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 200.f);
					if ((int)BP->GetHealth() > 0) {
						Renderer::Line(startPos, tempHead, color, 0.5f);
					}
				}
			}
		}
	}
}
void NPCESP(BasePlayer* BP, BasePlayer* LP, D2D1::ColorF color) {
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->GetBoneByID(r_foot), tempFeetR) && utils::w2s(BP->GetBoneByID(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));
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
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f }, L"NPC", color, true, true);
					CurPos2 += 15;
				}
				if (vars::npc::weapon) {
					const wchar_t* ActiveWeaponName;
					BaseProjectile* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon) {
						ActiveWeaponName = L"---";
					}
					else {
						ActiveWeaponName = ActWeapon->GetName();
					}
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f }, ActiveWeaponName, color, true, true);
					CurPos2 += 15;
				}
				if (vars::npc::healthdist) {
					wchar_t s[64];
					_swprintf(s, L"[%dM] [%dHP]", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)), (int)BP->GetHealth());
					Renderer::String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f }, s, color, true, true);
					CurPos2 += 15;
				}
				if (vars::npc::healthbar) {
					int health = (int)BP->GetHealth();
					float maxheal = 150.f;
					if (vars::npc::healthbarstyle == 0) {
						if ((int)Math::Calc3D_Dist(LocalPlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201) {
							if ((int)BP->GetHealth() <= 33) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)BP->GetHealth() >= 67) {
								Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							Renderer::Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (vars::npc::healthbarstyle == 1) {
						if ((int)BP->GetHealth() <= 33) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66) {
							Renderer::FillRectangle(Vector2{ middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos }, Vector2{ 60 * (health / maxheal), 6 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 67) {
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