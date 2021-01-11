typedef void(__stdcall* ProcessAttack)(DWORD64, DWORD64);
typedef float(__stdcall* get_time)();
typedef void(__stdcall* StartAttackCooldown)(DWORD64, float);
typedef DWORD64(__stdcall* GetTransform)(DWORD64);
void DoMeleeAttack(Target target, DWORD64 Held, bool transform) {
	if (!target.valid || !Held) return;

	if (read(Held + 0x230, float) >= ((get_time)(Storage::gBase + CO::get_time))()) { return; }
	if (read(Held + 0x23C, float) < read(Held + 0x1D8, float)) { return; }

	DWORD64 staticHitTest = read(Storage::gBase + CO::HitTest, DWORD64); if (!staticHitTest) return;
	DWORD64 newHitTest = il2cpp_object_new(staticHitTest);

	DWORD64 trans; Ray ray = Ray(LocalPlayer->GetBoneByID(neck), (target.position - LocalPlayer->GetBoneByID(neck)).Normalized());
	if (!target.entity) return;
	if (transform) { trans = target.entity->GrabTransform(head); }
	else { trans = utils::GetTransform((DWORD64)target.entity); } if (!trans) return;
	if (!target.entity) return;
	write(newHitTest + 0x34, 1000.f, float);
	write(newHitTest + 0xB0, trans, DWORD64);
	write(newHitTest + 0x14, ray, Ray);
	write(newHitTest + 0x66, true, bool);
	if (!target.entity) return;
	write(newHitTest + 0x88, target.entity, BasePlayer*);
	write(newHitTest + 0x90, utils::TransformToPoint(trans, target.position), Vector3);
	write(newHitTest + 0x9C, Vector3(0, 0, 0), Vector3);
	write(newHitTest + 0x68, read(Held + 0x268, DWORD64), DWORD64);
	if (!target.entity) return;
	((StartAttackCooldown)(Storage::gBase + CO::StartAttackCooldown))(Held, read(Held + 0x1DC, float));
	return ((ProcessAttack)(Storage::gBase + CO::ProcessAttack))(Held, newHitTest);
}
typedef void(__stdcall* set_color)(uintptr_t, Color);
typedef void(__stdcall* set_material)(uintptr_t, uintptr_t);
typedef void(__stdcall* CreateWithShader)(uintptr_t, uintptr_t);
void DoChams(BasePlayer* target) {
	DWORD64 staticmaterial = read(Storage::gBase + 0x29E5330, DWORD64);
	DWORD64 cham = il2cpp_object_new(staticmaterial);
	printf("shaderfind: %s\n", std::to_string(utils::ShaderFind(pUncStr(L"Standard"))));
	((CreateWithShader)(Storage::gBase + 0x1397210))(cham, utils::ShaderFind(pUncStr(L"Standard")));
	((set_color)(Storage::gBase + 0x1398AC0))(cham, Color(1, 0, 0, 1));
	DWORD64 renderer = read(Storage::gBase + 0x299A778, DWORD64);
	((set_material)(Storage::gBase + 0x14DDB70))(renderer, cham);
	//DWORD64 multimesh = read(read(target + oPlayerModel, DWORD64) + 0x280, DWORD64);
	//DWORD64 shared = read(multimesh + 0x48, DWORD64);
	/*typedef void(__stdcall* SetColor)(DWORD64, int, Color);
	typedef int(__stdcall* Prop2ID)(Str);
	int id = ((Prop2ID)(Storage::gBase + 0x14DFB10))(Str(xorstr(L"_Color")));
	((SetColor)(Storage::gBase + 0x1396CE0))(shared, id, Color(1, 0, 0, 1));*/
}
float LastKnock = 0.f; float LastOpen = 0.f; float LastHatch = 0.f;
void SpamKnock(uintptr_t Door) {
	typedef void(__stdcall* DoorFunction)(uintptr_t, BasePlayer*);
	if (LocalPlayer->Time() > LastKnock + 0.5f) {
		((DoorFunction)(Storage::gBase + CO::KnockDoor))(Door, LocalPlayer);
		LastKnock = LocalPlayer->Time();
	}
	if (LocalPlayer->Time() > LastOpen + 0.1f) {
		((DoorFunction)(Storage::gBase + CO::OpenDoor))(Door, LocalPlayer);
		LastOpen = LocalPlayer->Time();
	}
	if (LocalPlayer->Time() > LastHatch + 0.1f) {
		((DoorFunction)(Storage::gBase + CO::OpenHatch))(Door, LocalPlayer);
		LastHatch = LocalPlayer->Time();
	}
}
float LastPickup = 0.f;
void PickupPlayer(BasePlayer* ent) {
	typedef void(__stdcall* AssistPlayer)(BasePlayer*, BasePlayer*);
	if (!LocalPlayer->IsTeamMate(ent->GetSteamID()) && Misc::AssistTeamOnly) return;
	if (LocalPlayer->Time() > LastPickup + 0.5f) {
		((AssistPlayer)(Storage::gBase + CO::AssistPlayer))(ent, LocalPlayer);
		LastPickup = LocalPlayer->Time();
	}
}
void PickupItem(DWORD64 item) {
	typedef void(__stdcall* Pick)(DWORD64, Str);
	return ((Pick)(Storage::gBase + CO::ServerRPC))(item, Str(xorstr(L"Pickup")));
}
float ValueD = 0.f; float MaxValue = 10.f;
void Test() {
	ValueD += 0.02f;
	if (ValueD > MaxValue) {
		ValueD = 0;
		Global::doneHits = 0;
	}
	Renderer::Rectangle(Vector2((Global::ScreenWidth / 2) - 50, Global::ScreenHigh - 200), Vector2(100, 5), D2D1::ColorF::Black, 1.f);
	Renderer::FillRectangle(Vector2((Global::ScreenWidth / 2) - 50, Global::ScreenHigh - 200), Vector2(100 * (ValueD / MaxValue), 5), D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
}