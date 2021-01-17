void InitCheat() {
	auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
	Vector2 kek = Renderer::CanvasSize();
	Global::ScreenWidth = kek.x;
	Global::ScreenHigh = kek.y;
	float xs = Global::ScreenWidth / 2, ys = Global::ScreenHigh / 2;
	if (Crosshair::Default) {
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys + 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys + 4 }, D2D1::ColorF::White, 0.7f);

		Renderer::Line(Vector2{ xs + 4, ys + 4 }, Vector2{ xs + 4 + 4, ys + 4 + 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs + 4, ys - 4 }, Vector2{ xs + 4 + 4, ys - 4 - 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs - 4, ys - 4 }, Vector2{ xs - 4 - 4, ys - 4 - 4 }, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{ xs - 4, ys + 4 }, Vector2{ xs - 4 - 4, ys + 4 + 4 }, D2D1::ColorF::Black, 0.7f);
	}
	if (Crosshair::Custom) {
		if (Crosshair::Dot) {
			Renderer::Circle(Vector2{ xs, ys }, D2D1::ColorF::White, 1.f, 0.7f);
		}
		Renderer::Line(Vector2{ xs + Crosshair::Gap, ys }, Vector2{ xs + Crosshair::Gap + Crosshair::Length, ys }, D2D1::ColorF::White, 0.7f); // right
		Renderer::Line(Vector2{ xs - Crosshair::Gap, ys }, Vector2{ xs - Crosshair::Gap - Crosshair::Length, ys }, D2D1::ColorF::White, 0.7f); // left
		Renderer::Line(Vector2{ xs , ys - Crosshair::Gap }, Vector2{ xs , ys - Crosshair::Gap - Crosshair::Length }, D2D1::ColorF::White, 0.7f); // up
		Renderer::Line(Vector2{ xs , ys + Crosshair::Gap }, Vector2{ xs , ys + Crosshair::Gap + Crosshair::Length }, D2D1::ColorF::White, 0.7f); // down

		//Renderer::FillRectangle(Vector2{xs + Crosshair::Gap, ys}, Vector2{}) // TO-DO
	}
	if (Combat::DrawFov) {
		Renderer::Circle(Vector2{ xs, ys }, D2D1::ColorF::White, Combat::Fov, 1.f);
	}
	float FOV = Combat::Fov, CurFOV;
	if (Storage::closestPlayer != NULL) {
		if (FOV < (CurFOV = GetFov(TargetPlayerA, BoneList(Global::BoneToAim))) && !Combat::LockTarget) {
			Storage::closestPlayer = NULL;
		}
	}
	if (Storage::closestHeli != NULL && Storage::closestHeliObj != NULL) {
		Vector3 pos = read(Storage::closestHeliObj + 0x90, Vector3);
		if (FOV < (CurFOV = GetFovHeli(pos))) {
			Storage::closestHeli = NULL; Storage::closestHeliObj = NULL;
		}
	}
	if (Combat::LockTarget) {
		wchar_t trgt[64];
		if (Storage::closestPlayer != NULL) {
			_swprintf(trgt, xorstr(L"Target Locked: %s"), TargetPlayerA->GetName());
		}
		else {
			_swprintf(trgt, xorstr(L"Target Locked."));
		}
		Renderer::String(Vector2{ xs, ys - 50 }, trgt, D2D1::ColorF::PaleVioletRed, true, true);
	}
	if (Storage::closestPlayer != NULL && PlayerEsp::targetline) {
		static float screenX = GetSystemMetrics(SM_CXSCREEN);
		static float screenY = GetSystemMetrics(SM_CYSCREEN);
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if (!(TargetPlayerA->GetBoneByID(spine1).x == 0 && TargetPlayerA->GetBoneByID(spine1).y == 0 && TargetPlayerA->GetBoneByID(spine1).z == 0)) {
			if (utils::w2s(TargetPlayerA->GetBoneByID(head), ScreenPos))
				Renderer::Line(startPos, ScreenPos, D2D1::ColorF::Red, 1.f);
		}
	}
	
	if (Storage::closestHeli != NULL && Visuals::PatrolHeli) {
		static float screenX = GetSystemMetrics(SM_CXSCREEN);
		static float screenY = GetSystemMetrics(SM_CYSCREEN);
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if ((int)ceil(read(Storage::closestHeli + 0x20C, float)) > 0.2f) {
			if (utils::w2s(read(Storage::closestHeliObj + 0x90, Vector3), ScreenPos)) Renderer::Line(startPos, ScreenPos, D2D1::ColorF(0.3f, 0.34f, 1.f), 1.f);
		}

	}
	if (Combat::Fov > (kek.y - 3)) { Combat::Fov = (kek.y - 3); } // limit fov
	if (Misc::SexyFuckingFovValue < 30) { Misc::SexyFuckingFov = 80; } // limit graph fov
	if (Combat::Smoothing <= 0) { Combat::Smoothing = 1; }

	/*static int cases = 0;
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	switch (cases) {
	case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }                       // RAINBOW
	case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}*/
	if (Storage::closestPlayer != NULL && !TargetPlayerA->IsNpc() && PlayerEsp::belt) {
		const float Height = 170.f;
		const float Width = 150.f;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= PlayerEsp::beltx && p.x <= PlayerEsp::beltx + Width) {
				if (p.y >= PlayerEsp::belty && p.y <= PlayerEsp::belty + Height) {
					if (GetAsyncKeyState(VK_LBUTTON)) {
						PlayerEsp::beltx = p.x - (Width / 2);
						PlayerEsp::belty = p.y - (Height / 2);
					}
				}
			}
		}
		Renderer::FillRectangle({ PlayerEsp::beltx, PlayerEsp::belty }, { Width, Height }, D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f));
		Renderer::Rectangle({ PlayerEsp::beltx, PlayerEsp::belty }, { Width, Height }, D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f));
		Renderer::String({ PlayerEsp::beltx + (Width / 2), PlayerEsp::belty + 10 }, TargetPlayerA->GetName(), D2D1::ColorF::White, true, true);
		Renderer::Line({ PlayerEsp::beltx, PlayerEsp::belty + 20 }, { PlayerEsp::beltx + Width, PlayerEsp::belty + 20 }, D2D1::ColorF::White, 1);
		float Pos = 0;
		for (int i = 0; i < 6; i++) {
			BaseProjectile* ActWeapon = TargetPlayerA->GetWeaponInfo(i);
			if (ActWeapon) {
				const wchar_t* ActiveItem = ActWeapon->GetName();
				if (ActiveItem) {
					if (wcslen(ActiveItem) < 20) {
						wchar_t itemName[0x100];
						_swprintf(itemName, xorstr(L"%s [%d]"), ActiveItem, ActWeapon->GetCount());
						Renderer::String({ PlayerEsp::beltx + (Width / 2), PlayerEsp::belty + 40 + Pos }, itemName, D2D1::ColorF::White, true, true);
					}
				}
			}
			else {
				Renderer::String({ PlayerEsp::beltx + (Width / 2), PlayerEsp::belty + 40 + Pos }, xorstr(L"-----"), D2D1::ColorF::White, true, true);
			}
			Pos += 15;
		}
		Renderer::FillRectangle(Vector2{ PlayerEsp::beltx + (Width / 2) - 40, PlayerEsp::belty + 135 }, Vector2{ 80 * (TargetPlayerA->GetHealth() / 100.f), 10 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
		Renderer::Rectangle(Vector2{ PlayerEsp::beltx + (Width / 2) - 40, PlayerEsp::belty + 135 }, Vector2{ 80, 10 }, D2D1::ColorF::White, 0.5f);
	}
	EntityLoop();
}