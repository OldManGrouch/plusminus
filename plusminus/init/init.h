void InitCheat() {
	auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	Vector2 kek = Renderer::CanvasSize();
	vars::stuff::ScreenWidth = kek.x;
	vars::stuff::ScreenHeight = kek.y;
	float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
	if (vars::crosshair::default) {
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys + 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys + 4 }, D2D1::ColorF::White, 0.7f);

		Renderer::Line(Vector2{ xs + 4, ys + 4 }, Vector2{ xs + 4 + 4, ys + 4 + 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs + 4, ys - 4 }, Vector2{ xs + 4 + 4, ys - 4 - 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs - 4, ys - 4 }, Vector2{ xs - 4 - 4, ys - 4 - 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs - 4, ys + 4 }, Vector2{ xs - 4 - 4, ys + 4 + 4 }, D2D1::ColorF::Black, 0.7f);
	}
	if (vars::crosshair::custom) {
		if (vars::crosshair::dot) {
			Renderer::Circle(Vector2{ xs, ys }, D2D1::ColorF::White, 1.f, 0.7f);
		}
		Renderer::Line(Vector2{ xs + vars::crosshair::gap, ys }, Vector2{ xs + vars::crosshair::gap + vars::crosshair::length, ys }, D2D1::ColorF::White, 0.7f); // right
		Renderer::Line(Vector2{ xs - vars::crosshair::gap, ys }, Vector2{ xs - vars::crosshair::gap - vars::crosshair::length, ys }, D2D1::ColorF::White, 0.7f); // left
		Renderer::Line(Vector2{ xs , ys - vars::crosshair::gap }, Vector2{ xs , ys - vars::crosshair::gap - vars::crosshair::length }, D2D1::ColorF::White, 0.7f); // up
		Renderer::Line(Vector2{ xs , ys + vars::crosshair::gap }, Vector2{ xs , ys + vars::crosshair::gap + vars::crosshair::length }, D2D1::ColorF::White, 0.7f); // down

		// TO-DO proper crosshair that isnt seethrough with filled rectangles (autism 101)
	}
	if (vars::combat::visualize_fov) {
		Renderer::Circle(Vector2{ xs, ys }, D2D1::ColorF::White, vars::combat::fov, 1.f);
	}
	float FOV = vars::combat::fov, CurFOV;
	if (vars::stor::closestPlayer != NULL) {
		if (FOV < (CurFOV = GetFov(TargetPlayerA, BoneList(vars::stuff::BoneToAim))) && !vars::combat::lock_target) {
			vars::stor::closestPlayer = NULL;
		}
	}
	if (vars::stor::closestHeli != NULL && vars::stor::closestHeliObj != NULL) {
		Vector3 pos = read(vars::stor::closestHeliObj + 0x90, Vector3);
		if (FOV < (CurFOV = GetFovHeli(pos))) {
			vars::stor::closestHeli = NULL; vars::stor::closestHeliObj = NULL;
		}
	}
	// yeet
	
	//printf("%ls \n", vars::stuff::dlldirectory.c_str());
	if (vars::combat::lock_target) {
		wchar_t trgt[64];
		if (vars::stor::closestPlayer != NULL) {
			_swprintf(trgt, xorstr(L"Target Locked: %s"), TargetPlayerA->GetName());
		}
		Renderer::String(Vector2{ xs, ys - 50 }, trgt, D2D1::ColorF::PaleVioletRed, true, true);
	}
	if (vars::stor::closestPlayer != NULL && vars::players::targetline) {
		static float screenX = GetSystemMetrics(SM_CXSCREEN);
		static float screenY = GetSystemMetrics(SM_CYSCREEN);
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if (!(TargetPlayerA->GetBoneByID(spine1).x == 0 && TargetPlayerA->GetBoneByID(spine1).y == 0 && TargetPlayerA->GetBoneByID(spine1).z == 0)) {
			if (utils::w2s(TargetPlayerA->GetBoneByID(head), ScreenPos))
				Renderer::Line(startPos, ScreenPos, D2D1::ColorF::Red, 1.f);
		}
	}
	//DoIcon();
	if (vars::stor::closestHeli != NULL && vars::visuals::patrol_heli) {
		static float screenX = GetSystemMetrics(SM_CXSCREEN);
		static float screenY = GetSystemMetrics(SM_CYSCREEN);
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if ((int)ceil(read(vars::stor::closestHeli + 0x20C, float)) > 0.2f) {
			if (utils::w2s(read(vars::stor::closestHeliObj + 0x90, Vector3), ScreenPos)) Renderer::Line(startPos, ScreenPos, D2D1::ColorF(0.3f, 0.34f, 1.f), 1.f);
		}

	}
	if (vars::combat::fov > (kek.y - 3)) { vars::combat::fov = (kek.y - 3); } // limit fov
	if (vars::misc::fov < 30) { vars::misc::fov = 80; } // limit graph fov
	if (vars::combat::smooth_factor <= 0) { vars::combat::smooth_factor = 1; }
	if (vars::weapons::hitdistance < 300) { vars::weapons::hitdistance = 300; }
	/*static int cases = 0;
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	switch (cases) {
	case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }                       // RAINBOW
	case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}*/
	if (vars::stor::closestPlayer != NULL && !TargetPlayerA->playerModel()->IsNpc() && vars::players::belt) {
		const float Height = 275.f;
		const float Width = 150.f;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= vars::players::beltx && p.x <= vars::players::beltx + Width) {
				if (p.y >= vars::players::belty && p.y <= vars::players::belty + Height) {
					if (GetAsyncKeyState(VK_LBUTTON)) {
						vars::players::beltx = p.x - (Width / 2);
						vars::players::belty = p.y - (Height / 2);
					}
				}
			}
		}
		Renderer::FillRectangle({ vars::players::beltx, vars::players::belty }, { Width, Height }, D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f));
		Renderer::Rectangle({ vars::players::beltx, vars::players::belty }, { Width, Height }, D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f));
		Renderer::String({ vars::players::beltx + (Width / 2), vars::players::belty + 10 }, TargetPlayerA->GetName(), D2D1::ColorF::White, true, true);
		Renderer::Line({ vars::players::beltx, vars::players::belty + 20 }, { vars::players::beltx + Width, vars::players::belty + 20 }, D2D1::ColorF::White, 1);
		float Pos = 0;
		for (int i = 0; i < 6; i++) {
			Item* ActWeapon = TargetPlayerA->GetWeaponInfo(i);
			if (ActWeapon) {
				const wchar_t* ActiveItem = ActWeapon->GetName();
				if (ActiveItem) {
					if (wcslen(ActiveItem) < 20) {
						wchar_t itemName[0x100];
						_swprintf(itemName, xorstr(L"%s [%d]"), ActiveItem, ActWeapon->GetCount());
						Renderer::String({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos }, itemName, D2D1::ColorF::White, true, true);
					}
				}
			}
			else {
				Renderer::String({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos }, xorstr(L"-----"), D2D1::ColorF::White, true, true);
			}
			Pos += 15;
		}
		Renderer::FillRectangle(Vector2{ vars::players::beltx + (Width / 2) - 40, vars::players::belty + 135 }, Vector2{ 80 * (TargetPlayerA->health() / 100.f), 10 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
		Renderer::Rectangle(Vector2{ vars::players::beltx + (Width / 2) - 40, vars::players::belty + 135 }, Vector2{ 80, 10 }, D2D1::ColorF::White, 0.5f);
		float cPos = 125;
		for (int i = 0; i < 7; i++) {
			Item* ActWeapon = TargetPlayerA->GetClothesInfo(i);
			if (ActWeapon) {
				const wchar_t* ActiveItem = ActWeapon->GetName();
				if (ActiveItem) {
					if (wcslen(ActiveItem) < 20) {
						wchar_t itemName[0x100];
						_swprintf(itemName, xorstr(L"%s"), ActiveItem);
						Renderer::String({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + cPos }, itemName, D2D1::ColorF::White, true, true);
					}
				}
			}
			else {
				Renderer::String({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + cPos }, xorstr(L"-----"), D2D1::ColorF::White, true, true);
			}
			cPos += 15;
		}
	}
	EntityLoop();
}