using namespace ImGui;
ImFont* font_main;
ImFont* font_menu;
void apply_fonts() {
	ImGui::CreateContext();

	font_main = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 18);
	font_menu = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12);
}
void HelpMarker(const char* desc) {
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
void HelpCheckbox(const char* desc, bool* v, const char* helptext) { ImGui::Checkbox(desc, v); ImGui::SameLine(); HelpMarker(helptext); }
VOID ImGUI_Style() {
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	style->FrameRounding = 0.f;
	style->ChildRounding = 0.f;
	style->GrabRounding = 0.f;
	style->PopupRounding = 0.f;
	style->TabRounding = 0.f;
	style->WindowRounding = 0.f;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
}
#include <mutex>

void Menu() {
	ImGUI_Style();
	if (ImGui::Begin("plusminus", &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize)) {
		ImGui::PushFont(font_main);
		ImGui::SetWindowPos(ImVec2(500, 250), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(500, 600), ImGuiCond_Once);
		static int tabb = 0;
		if (ImGui::Button(xorstr("Combat"))) {
			tabb = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Weapons"))) {
			tabb = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Players"))) {
			tabb = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("NPC's"))) {
			tabb = 3;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Other Visuals"))) {
			tabb = 4;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Misc"))) {
			tabb = 5;
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Other"))) {
			tabb = 6;
		}
		ImGui::Separator();
		switch (tabb) {
		case 0:
			HelpCheckbox(xorstr("Hitbox Override"), &Combat::HitboxOverride, xorstr("Even if you hit a person in the body, the bullet will teleport to the head (depending on the headshot percentage)."));
			if (Combat::HitboxOverride) {
				Combat::AlwaysHeliHotspot = false;
				ImGui::SliderInt(xorstr("Headshot Percentage"), &Combat::HeadshotPercentage, 0, 100);
			}
			HelpCheckbox(xorstr("Always Heli Weakspot"), &Combat::AlwaysHeliHotspot, xorstr("If you hit any part of the helicopter, the bullet will teleport to the weakspot (rotor)."));
			if (Combat::AlwaysHeliHotspot) { Combat::HitboxOverride = false; }
			HelpCheckbox(xorstr("Silent Melee"), &Weapons::SilentMelee, xorstr("Will automatically hit people next to you with a melee weapon in your hand."));
			ImGui::Checkbox("magicbollet", &Combat::magicbollet);
			HelpCheckbox(xorstr("pSilent"), &Combat::pSilent, xorstr("Bullets will just fly to the target."));
			if (Combat::pSilent) {
				const char* items[] = { "Players", "Helicopter" };
				static const char* current_item = NULL;

				if (ImGui::BeginCombo("pSilent Targeting", current_item)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (current_item == "Players") {
					Combat::pSilentTargeting = 0;
				}
				if (current_item == "Helicopter") {
					Combat::pSilentTargeting = 1;
				}
				ImGui::Checkbox(xorstr("On Key"), &Combat::pSilentOnKey);
				if (Combat::pSilentOnKey) {
					Hotkey(xorstr("pSilent Key"), &Keys::pSilent, ImVec2(120.f, 0));
				}
			}
			ImGui::Checkbox(xorstr("Activate Aimbot"), &Combat::Activate);
			if (Combat::Activate) {
				ImGui::Checkbox(xorstr("Smooth"), &Combat::Smooth);
				if (Combat::Smooth) {
					ImGui::SliderInt(xorstr("Smoothing"), &Combat::Smoothing, 1, 50);
				}
				Hotkey(xorstr("AimKey"), &Keys::aimKey, ImVec2(120.f, 0));
			}
			ImGui::Checkbox(xorstr("Visualize Targeting Fov"), &Combat::DrawFov);
			ImGui::SliderFloat(xorstr("Targeting Fov"), &Combat::Fov, 20.f, 1000.f);
			ImGui::SliderFloat(xorstr("Max Targeting Distance"), &Combat::Range, 0.f, 400.f);
			Hotkey(xorstr("Lock Target"), &Keys::lockTarget, ImVec2(120.f, 0));
			ImGui::Checkbox(xorstr("Ignore Players"), &Combat::IgnorePlayers);
			ImGui::Checkbox(xorstr("Ignore Heli"), &Combat::IgnoreHeli);
			ImGui::Checkbox(xorstr("Ignore NPC's"), &Combat::IgnoreNpc);
			ImGui::Checkbox(xorstr("Ignore Teammates"), &Combat::IgnoreTeam);
			ImGui::Checkbox(xorstr("Ignore Sleeping"), &Combat::IgnoreSleepers);
			break;
		case 1:
			ImGui::Checkbox(xorstr("Rage No Recoil"), &Weapons::NoRecoil);
			ImGui::Checkbox(xorstr("Legit No Recoil"), &Weapons::LegitNoRecoil);
			if (Weapons::LegitNoRecoil) {
				ImGui::SliderFloat(xorstr("X Control"), &Weapons::controlX, 0.f, 1.f);
				ImGui::SliderFloat(xorstr("Y Control"), &Weapons::controlY, 0.f, 1.f);
			}
			ImGui::Checkbox(xorstr("No Spread"), &Weapons::AntiSpread);
			ImGui::Checkbox(xorstr("No Sway"), &Weapons::NoSway);
			ImGui::Checkbox(xorstr("No Ricochet"), &Weapons::NoRicochet);
			ImGui::Checkbox(xorstr("Rapid Fire"), &Weapons::RapidFire);
			ImGui::Checkbox(xorstr("Force Automatic"), &Weapons::Automatic);
			ImGui::Checkbox(xorstr("Thick Bullets"), &Weapons::FatBullet);
			ImGui::Checkbox(xorstr("Faster Bullets"), &Weapons::FastBullet);
			HelpCheckbox(xorstr("Minicopter Aim"), &Weapons::canHoldItems, xorstr("Allows you to hold items on minicopters."));
			ImGui::Checkbox(xorstr("EokaTap"), &Weapons::SuperEoka);
			ImGui::Checkbox(xorstr("FastBow"), &Weapons::SuperBow);
			HelpCheckbox(xorstr("Penetrate"), &Weapons::Penetrate, xorstr("Allows you to shoot through deployables, trees."));
			ImGui::Checkbox(xorstr("Spoof Hit Distance"), &Weapons::SpoofHitDistance);
			break;
		case 2:
			ImGui::Checkbox(xorstr("Name"), &PlayerEsp::name);
			ImGui::Checkbox(xorstr("Box"), &PlayerEsp::box);
			if (PlayerEsp::box) {
				const char* items[] = { "Normal", "Cornered" };
				static const char* current_item = NULL;

				if (ImGui::BeginCombo("Box Type", current_item)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (current_item == "Normal") {
					PlayerEsp::boxstyle = 0;
				}
				if (current_item == "Cornered") {
					PlayerEsp::boxstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Fill Box"), &PlayerEsp::fillbox);
			ImGui::Checkbox(xorstr("Skeleton"), &PlayerEsp::skeleton);
			ImGui::Checkbox(xorstr("Health and Distance"), &PlayerEsp::healthdist);
			ImGui::Checkbox(xorstr("Healthbar"), &PlayerEsp::healthbar);
			if (PlayerEsp::healthbar) {
				const char* items[] = { "Left side", "Bottom" };
				static const char* current_item = NULL;

				if (ImGui::BeginCombo("Healthbar Type", current_item)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (current_item == "Left side") {
					PlayerEsp::healthbarstyle = 0;
				}
				if (current_item == "Bottom") {
					PlayerEsp::healthbarstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Weapon"), &PlayerEsp::weapon);
			ImGui::Checkbox(xorstr("Tracers"), &PlayerEsp::tracers);
			HelpCheckbox(xorstr("Skin Chams"), &PlayerEsp::chams, xorstr("Either enable this in the menu before entering a server, or enable in game and kill someone / wait."));
			HelpCheckbox(xorstr("Target Tracers"), &PlayerEsp::targetline, xorstr("Shows a line to the targeted player."));
			HelpCheckbox(xorstr("Target Belt"), &PlayerEsp::belt, xorstr("Shows the targeted player's belt."));
			ImGui::Checkbox(xorstr("Ignore Sleepers"), &PlayerEsp::sleeperignore);
			break;
		case 3:
			ImGui::Checkbox(xorstr("Name "), &BotsEsp::name);
			ImGui::Checkbox(xorstr("Box "), &BotsEsp::box);
			if (BotsEsp::box) {
				const char* items[] = { "Normal ", "Cornered " };
				static const char* current_item = NULL;

				if (ImGui::BeginCombo("Box Type ", current_item)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (current_item == "Normal ") {
					BotsEsp::boxstyle = 0;
				}
				if (current_item == "Cornered ") {
					BotsEsp::boxstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Fill Box "), &BotsEsp::fillbox);
			ImGui::Checkbox(xorstr("Skeleton "), &BotsEsp::skeleton);
			ImGui::Checkbox(xorstr("Health and Distance "), &BotsEsp::healthdist);
			ImGui::Checkbox(xorstr("Healthbar "), &BotsEsp::healthbar);
			if (BotsEsp::healthbar) {
				const char* items[] = { "Left side ", "Bottom " };
				static const char* current_item = NULL;

				if (ImGui::BeginCombo("Healthbar Type ", current_item)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (current_item == "Left side ") {
					BotsEsp::healthbarstyle = 0;
				}
				if (current_item == "Bottom ") {
					BotsEsp::healthbarstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Weapon "), &BotsEsp::weapon);
			ImGui::Checkbox(xorstr("Tracers "), &BotsEsp::tracers);
			break;
		case 4:
			ImGui::Checkbox(xorstr("Default Crosshair"), &Crosshair::Default);
			ImGui::Checkbox(xorstr("Custom Crosshair"), &Crosshair::Custom);
			if (Crosshair::Custom) {
				ImGui::SliderFloat(xorstr("Gap"), &Crosshair::Gap, 0.f, 50.f);
				ImGui::SliderFloat(xorstr("Length"), &Crosshair::Length, 0.f, 50.f);
				ImGui::Checkbox(xorstr("Dot"), &Crosshair::Dot);
			}
			if (ImGui::CollapsingHeader(xorstr("Ores"))) {
				ImGui::Checkbox(xorstr("Stone"), &Ores::Stone);
				ImGui::Checkbox(xorstr("Sulfur"), &Ores::Sulfur);
				ImGui::Checkbox(xorstr("Metal"), &Ores::Metal);
				if (Ores::Sulfur || Ores::Stone || Ores::Metal) {
					ImGui::SliderFloat(xorstr("Ore ESP Distance"), &Ores::oreDrawDistance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Collectables"), &Ores::showCollectables);
					ImGui::Checkbox(xorstr("Show Distance"), &Ores::showDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Animals"))) {
				ImGui::Checkbox(xorstr("Bears"), &Visuals::Animals::Bear);
				ImGui::Checkbox(xorstr("Pigs"), &Visuals::Animals::Pig);
				ImGui::Checkbox(xorstr("Wolfs"), &Visuals::Animals::Wolf);
				ImGui::Checkbox(xorstr("Horses"), &Visuals::Animals::Deer);
				ImGui::Checkbox(xorstr("Chickens"), &Visuals::Animals::Chicken);
				if (Visuals::Animals::Bear || Visuals::Animals::Pig || Visuals::Animals::Wolf || Visuals::Animals::Deer || Visuals::Animals::Chicken) {
					ImGui::SliderFloat(xorstr("Animal ESP Distance"), &Visuals::Animals::drawAnimalDistance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance      "), &Visuals::Animals::animalDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Crates"))) {
				ImGui::Checkbox(xorstr("Chinook Crates"), &Visuals::Crates::Chinook);
				ImGui::Checkbox(xorstr("Airdrops"), &Visuals::Crates::Supply);
				ImGui::Checkbox(xorstr("Heli Crates"), &Visuals::Crates::Heli);
				ImGui::Checkbox(xorstr("Bradley Crates"), &Visuals::Crates::Bradley);
				if (Visuals::Crates::Supply || Visuals::Crates::Bradley || Visuals::Crates::Heli) {
					ImGui::SliderFloat(xorstr("Crate ESP Distance"), &Visuals::Crates::drawCrateDistance, 5.f, 3000.f);
					ImGui::Checkbox(xorstr("Show Distance "), &Visuals::Crates::crateDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Vehicles"))) {
				ImGui::Checkbox(xorstr("Minicopters"), &Visuals::Vehicles::Minicopter);
				ImGui::Checkbox(xorstr("Scrap Helis"), &Visuals::Vehicles::ScrapHeli);
				ImGui::Checkbox(xorstr("Boats"), &Visuals::Vehicles::Boat);
				ImGui::Checkbox(xorstr("RHIB's"), &Visuals::Vehicles::RHIB);
				if (Visuals::Vehicles::Minicopter || Visuals::Vehicles::ScrapHeli || Visuals::Vehicles::Boat || Visuals::Vehicles::RHIB) {
					ImGui::SliderFloat(xorstr("Vehicle ESP Distance"), &Visuals::Vehicles::drawVehicleDistance, 5.f, 3000.f);
					ImGui::Checkbox(xorstr("Show Distance  "), &Visuals::Vehicles::vehicleDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Traps"))) {
				ImGui::Checkbox(xorstr("Auto Turrets"), &Visuals::Turrets::AutoTurret);
				ImGui::Checkbox(xorstr("Flame Turrets"), &Visuals::Turrets::FlameTurret);
				ImGui::Checkbox(xorstr("Shotgun Traps"), &Visuals::Turrets::ShotgunTurret);
				ImGui::Checkbox(xorstr("Landmines"), &Visuals::Turrets::Landmine);
				ImGui::Checkbox(xorstr("Beartraps"), &Visuals::Turrets::BearTrap);
				if (Visuals::Turrets::AutoTurret || Visuals::Turrets::FlameTurret || Visuals::Turrets::ShotgunTurret || Visuals::Turrets::Landmine || Visuals::Turrets::BearTrap) {
					ImGui::SliderFloat(xorstr("Trap ESP Distance"), &Visuals::Turrets::drawTrapDistance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance   "), &Visuals::Turrets::trapDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Base"))) {
				ImGui::Checkbox(xorstr("Tool Cupboards"), &Visuals::Base::TC);
				ImGui::Checkbox(xorstr("Sleeping Bags"), &Visuals::Base::SleepingBag);
				ImGui::Checkbox(xorstr("Beds"), &Visuals::Base::Bed);
				ImGui::Checkbox(xorstr("Boxes"), &Visuals::Base::Boxes);
				if (Visuals::Base::TC || Visuals::Base::SleepingBag || Visuals::Base::Bed || Visuals::Base::Boxes) {
					ImGui::SliderFloat(xorstr("Base ESP Distance"), &Visuals::Base::drawBaseDistance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance     "), &Visuals::Base::baseDistance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Misc "))) {
				ImGui::Checkbox(xorstr("Patrol Heli"), &Visuals::PatrolHeli);
				ImGui::Checkbox(xorstr("Bradley APC"), &Visuals::BradleyTank);
				ImGui::Checkbox(xorstr("Hemp"), &Visuals::Other::Hemp);
				ImGui::Checkbox(xorstr("Corpses"), &Visuals::Other::Corpse);
				ImGui::Checkbox(xorstr("Stashes"), &Visuals::Other::Stash);
				ImGui::Checkbox(xorstr("Dropped / World items"), &Visuals::Other::DroppedItems);
				if (Visuals::Other::Corpse || Visuals::Other::Stash || Visuals::Other::Hemp || Visuals::Other::DroppedItems) {
					ImGui::SliderFloat(xorstr("Misc ESP Distance"), &Visuals::Other::drawOtherDistance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance    "), &Visuals::Other::otherDistance);
				}
			}
			break;
		case 5:
			ImGui::SliderFloat(xorstr("Fov"), &Misc::SexyFuckingFovValue, 30.f, 130.f);
			Hotkey(xorstr("Remove Position Forcing"), &Keys::forcepos, ImVec2(200.f, 0));
			HelpCheckbox(xorstr("Silent Walk"), &Misc::SilentWalk, xorstr("You're like flying with noclip, but on the ground... But you're not flying."));
			HelpCheckbox(xorstr("Spoof OnLadder"), &Misc::Flyhack, xorstr("Spoofs OnLadder state to true (looks funny and can be used to flyhack up buildings without getting kicked)"));
			HelpCheckbox(xorstr("Anti-Aim"), &Misc::AntiAim, xorstr("Makes you look like you're spinning on other people's screens."));
			if (Misc::AntiAim) {
				ImGui::SliderInt(xorstr("Anti-Aim spin speed"), &Misc::AntiAimSpeed, 1, 50);
			}
			HelpCheckbox(xorstr("Faster Healing"), &Misc::FastHeal, xorstr("Allows you to heal faster than usual, no need to spam mouse to heal - you can just hold it down."));
			HelpCheckbox(xorstr("FakeLag"), &Misc::FakeLag, xorstr("Makes it looks like you're lagging on other people's screens."));
			HelpCheckbox(xorstr("FakeAdmin"), &Misc::FakeAdmin, xorstr("Allows you to use certain admin-only commands like 'debugcamera' and 'noclip'. Note: bypasses rustberg's and arabrust's anti-fakeadmin. If you can't move in debugcamera, type 'camspeed 1' in console."));
			HelpCheckbox(xorstr("Annoyer"), &Misc::Annoyer, xorstr("Annoy anyone that has a door on their base."));
			HelpCheckbox(xorstr("Shoot Anywhere"), &Weapons::jumpAim, xorstr("Allows you to shoot anywhere."));
			HelpCheckbox(xorstr("Omni-Sprint"), &Misc::omniSprint, xorstr("Allows you to sprint in any direction."));
			HelpCheckbox(xorstr("Suicide"), &Misc::Suicide, xorstr("Intantly kills you with fall damage, can be used to quickly respawn or to just annoy someone (it makes a LOT of noise). Be careful using this."));
			ImGui::Checkbox(xorstr("Spiderman"), &Misc::SpiderMan);
			HelpCheckbox(xorstr("Infinite Jump"), &Misc::InfiniteJump, xorstr("Allows you to infinitely jump, beware of flyhack."));
			HelpCheckbox(xorstr("Long Neck"), &Misc::LongNeck, xorstr("Makes your neck longer, can be used to shoot over certain structures."));
			if (Misc::LongNeck) {
				Hotkey(xorstr("Long Neck Key"), &Keys::neck, ImVec2(200.f, 0));
			}
			HelpCheckbox(xorstr("InstaRevive"), &Misc::InstaRevive, xorstr("Instantly picks a downed person."));
			HelpCheckbox(xorstr("Custom Hitsound"), &Misc::CustomHitsound, xorstr("When you hit a player, your custom hitsound will play. Make a new folder in C disk called 'plusminus', and put your hitsound inside of there. It has to be in a .wav format and called 'hit'"));
			HelpCheckbox(xorstr("AutoCollect"), &Misc::AutoCollect, xorstr("Automatically collects collectables that are close."));
			HelpCheckbox(xorstr("AutoRevive"), &Misc::AutoAssist, xorstr("Automatically assists / revives downed players that are next to you."));
			if (Misc::AutoAssist) {
				ImGui::Checkbox(xorstr("Revive Teammates Only"), &Misc::AssistTeamOnly);
			}
			HelpCheckbox(xorstr("Auto Farm Ores"), &Weapons::SilentOre, xorstr("Will automatically hit ore hotspots when you are close to them with a melee weapon"));
			HelpCheckbox(xorstr("Auto Farm Trees"), &Weapons::SilentTree, xorstr("Will automatically hit trees when you are close to them with a melee weapon, hit the tree to start automatically hitting it. Keep in mind, you need to have line of sight with the hitmarker!"));
			HelpCheckbox(xorstr("Rayleigh Changer"), &Misc::Rayleigh, xorstr("Makes your sky look pretty when day."));
			if (Misc::Rayleigh) {
				ImGui::SliderFloat(xorstr("Rayleigh Amount"), &Misc::RayleighAmount, 1.f, 50.f);
			}
			HelpCheckbox(xorstr("Bright Ambient"), &Misc::CustomAmbient, xorstr("Nightmode, fullbright, whatever you want to call it."));
			ImGui::Checkbox(xorstr("Custom Time"), &Misc::CustomTime);
			if (Misc::CustomTime) {
				ImGui::SliderFloat(xorstr("Time"), &Misc::Time, 0.f, 12.f);
			}
			ImGui::Checkbox(xorstr("Gravity"), &Misc::Gravity);
			if (Misc::Gravity) {
				ImGui::SliderFloat(xorstr("Gravity Value"), &Misc::GravityModifier, 0.f, 10.f);
				Hotkey(xorstr("Gravity Key"), &Keys::gravityKey, ImVec2(120.f, 0));
			}
			break;
		case 6:
			ImGui::InputText("", Global::ConfigName, 0x100);
			if (ImGui::Button(xorstr("Save Config"), ImVec2(100.f, 0))) {
				config.Save();
			}
			ImGui::SameLine();
			if (ImGui::Button(xorstr("Load Config"), ImVec2(100.f, 0))) {
				config.Load();
			}
			ImGui::Separator();
			if (ImGui::Checkbox(xorstr("Developer Mode [don't touch]"), &Global::debugtab)) {
				ImGui::SliderFloat(xorstr("float"), &Global::testFloat, 0.f, 50.f);
				ImGui::SliderInt(xorstr("int"), &Global::testInt, 0, 20);
				ImGui::InputText(xorstr("char"), Global::testChar, 0x100);
			}
			ImGui::Checkbox(xorstr("Panic"), &Global::Panic);
			break;
		}
		ImGui::PopFont();
		ImGui::End();
	}
}