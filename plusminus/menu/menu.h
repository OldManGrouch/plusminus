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
			HelpCheckbox(xorstr("Hitbox Override"), &vars::combat::hitbox_override, xorstr("Even if you hit a person in the body, the bullet will teleport to the head (depending on the headshot percentage)."));
			if (vars::combat::hitbox_override) {
				vars::combat::always_heli_rotor = false;
				ImGui::SliderInt(xorstr("Headshot Percentage"), &vars::combat::hs_percentage, 0, 100);
			}
			HelpCheckbox(xorstr("Always Heli Weakspot"), &vars::combat::always_heli_rotor, xorstr("If you hit any part of the helicopter, the bullet will teleport to the weakspot (rotor)."));
			if (vars::combat::always_heli_rotor) { vars::combat::hitbox_override = false; }
			HelpCheckbox(xorstr("Silent Melee"), &vars::combat::silent_melee, xorstr("Will automatically hit people next to you with a melee weapon in your hand."));
			//ImGui::Checkbox(xorstr("magic bolet"), &vars::combat::magicbollet);
			HelpCheckbox(xorstr("pSilent"), &vars::combat::psilent, xorstr("Bullets will just fly to the target."));
			if (vars::combat::psilent) {
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
					vars::combat::psilenttarget = 0;
				}
				if (current_item == "Helicopter") {
					vars::combat::psilenttarget = 1;
				}
				ImGui::Checkbox(xorstr("Autoshoot"), &vars::combat::psilent_autoshoot);
				ImGui::Checkbox(xorstr("On Key"), &vars::combat::psilentonkey);
				if (vars::combat::psilentonkey) {
					Hotkey(xorstr("pSilent Key"), &vars::keys::psilent, ImVec2(120.f, 0));
				}
			}
			ImGui::Checkbox(xorstr("Memory Aim"), &vars::combat::aimbot);
			if (vars::combat::aimbot) {
				//ImGui::Checkbox(xorstr("Smooth"), &vars::combat::Smooth);
				if (vars::combat::smooth) {
					ImGui::SliderInt(xorstr("Smoothing"), &vars::combat::smooth_factor, 1, 50);
				}
				Hotkey(xorstr("Aiming Key"), &vars::keys::aimkey, ImVec2(120.f, 0));
			}
			ImGui::Checkbox(xorstr("Visualize Targeting Fov"), &vars::combat::visualize_fov);
			ImGui::SliderFloat(xorstr("Targeting Fov"), &vars::combat::fov, 20.f, 1000.f);
			ImGui::SliderFloat(xorstr("Max Targeting Distance"), &vars::combat::range, 0.f, 400.f);
			Hotkey(xorstr("Lock Target"), &vars::keys::locktarget, ImVec2(120.f, 0));
			ImGui::Checkbox(xorstr("Ignore Players"), &vars::combat::ignore_players);
			ImGui::Checkbox(xorstr("Ignore Heli"), &vars::combat::ignore_heli);
			ImGui::Checkbox(xorstr("Ignore NPC's"), &vars::combat::ignore_npc);
			ImGui::Checkbox(xorstr("Ignore Teammates"), &vars::combat::ignore_team);
			ImGui::Checkbox(xorstr("Ignore Sleeping"), &vars::combat::ignore_sleepers);
			break;
		case 1:
			ImGui::Checkbox(xorstr("Rage No Recoil"), &vars::weapons::no_recoil);
			ImGui::Checkbox(xorstr("Legit No Recoil"), &vars::weapons::legit_norecoil);
			if (vars::weapons::legit_norecoil) {
				ImGui::SliderFloat(xorstr("X Control"), &vars::weapons::control_y, 0.f, 1.f);
				ImGui::SliderFloat(xorstr("Y Control"), &vars::weapons::control_x, 0.f, 1.f);
			}
			ImGui::Checkbox(xorstr("No Spread"), &vars::weapons::no_recoil);
			ImGui::Checkbox(xorstr("No Sway"), &vars::weapons::no_sway);
			ImGui::Checkbox(xorstr("No Ricochet"), &vars::weapons::no_ricochet);
			ImGui::Checkbox(xorstr("Rapid Fire"), &vars::weapons::rapid_fire);
			ImGui::Checkbox(xorstr("Force Automatic"), &vars::weapons::automatic);
			ImGui::Checkbox(xorstr("Thick Bullets"), &vars::weapons::thick_bullet);
			ImGui::Checkbox(xorstr("Faster Bullets"), &vars::weapons::fast_bullets);
			HelpCheckbox(xorstr("Minicopter Aim"), &vars::weapons::minicopter_aim, xorstr("Allows you to hold items on minicopters."));
			ImGui::Checkbox(xorstr("EokaTap"), &vars::weapons::eokatap);
			ImGui::Checkbox(xorstr("FastBow"), &vars::weapons::fastbow);
			HelpCheckbox(xorstr("Penetrate"), &vars::weapons::penetrate, xorstr("Allows you to shoot through deployables, trees."));
			HelpCheckbox(xorstr("Spoof Hit Distance"), &vars::weapons::spoof_hitdistance, xorstr("You can use this to make enemies think you were closer than you actually were or just flex with big meters."));
			if (vars::weapons::spoof_hitdistance) {
				ImGui::SliderFloat(xorstr("Distance"), &vars::weapons::hitdistance, 0.f, 10000.f);
			}
			break;
		case 2:
			ImGui::Checkbox(xorstr("Name"), &vars::players::name);
			ImGui::Checkbox(xorstr("Box"), &vars::players::box);
			if (vars::players::box) {
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
					vars::players::boxstyle = 0;
				}
				if (current_item == "Cornered") {
					vars::players::boxstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Fill Box"), &vars::players::fillbox);
			ImGui::Checkbox(xorstr("Skeleton"), &vars::players::skeleton);
			ImGui::Checkbox(xorstr("Health and Distance"), &vars::players::healthdist);
			ImGui::Checkbox(xorstr("Healthbar"), &vars::players::healthbar);
			if (vars::players::healthbar) {
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
					vars::players::healthbarstyle = 0;
				}
				if (current_item == "Bottom") {
					vars::players::healthbarstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Weapon"), &vars::players::weapon);
			ImGui::Checkbox(xorstr("Tracers"), &vars::players::tracers);
			HelpCheckbox(xorstr("Chams"), &vars::players::chams, xorstr("Colors player models and their clothes through walls."));
			HelpCheckbox(xorstr("Target Tracers"), &vars::players::targetline, xorstr("Shows a line to the targeted player."));
			HelpCheckbox(xorstr("Target Belt"), &vars::players::belt, xorstr("Shows the targeted player's belt."));
			ImGui::Checkbox(xorstr("Ignore Sleepers"), &vars::players::sleeperignore);
			break;
		case 3:
			ImGui::Checkbox(xorstr("Name "), &vars::npc::name);
			ImGui::Checkbox(xorstr("Box "), &vars::npc::box);
			if (vars::npc::box) {
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
					vars::npc::boxstyle = 0;
				}
				if (current_item == "Cornered ") {
					vars::npc::boxstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Fill Box "), &vars::npc::fillbox);
			ImGui::Checkbox(xorstr("Skeleton "), &vars::npc::skeleton);
			ImGui::Checkbox(xorstr("Health and Distance "), &vars::npc::healthdist);
			ImGui::Checkbox(xorstr("Healthbar "), &vars::npc::healthbar);
			if (vars::npc::healthbar) {
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
					vars::npc::healthbarstyle = 0;
				}
				if (current_item == "Bottom ") {
					vars::npc::healthbarstyle = 1;
				}
			}
			ImGui::Checkbox(xorstr("Weapon "), &vars::npc::weapon);
			ImGui::Checkbox(xorstr("Tracers "), &vars::npc::tracers);
			break;
		case 4:
			ImGui::Checkbox(xorstr("Default Crosshair"), &vars::crosshair::default);
			ImGui::Checkbox(xorstr("Custom Crosshair"), &vars::crosshair::custom);
			if (vars::crosshair::custom) {
				ImGui::SliderFloat(xorstr("Gap"), &vars::crosshair::gap, 0.f, 50.f);
				ImGui::SliderFloat(xorstr("Length"), &vars::crosshair::length, 0.f, 50.f);
				ImGui::Checkbox(xorstr("Dot"), &vars::crosshair::dot);
			}
			if (ImGui::CollapsingHeader(xorstr("Ores"))) {
				ImGui::Checkbox(xorstr("Stone"), &vars::ores::stone);
				ImGui::Checkbox(xorstr("Sulfur"), &vars::ores::sulfur);
				ImGui::Checkbox(xorstr("Metal"), &vars::ores::metal);
				if (vars::ores::sulfur || vars::ores::stone || vars::ores::metal) {
					ImGui::SliderFloat(xorstr("Ore ESP Distance"), &vars::ores::draw_distance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Collectables"), &vars::ores::show_collectables);
					ImGui::Checkbox(xorstr("Show Distance"), &vars::ores::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Animals"))) {
				ImGui::Checkbox(xorstr("Bears"), &vars::visuals::animals::bear);
				ImGui::Checkbox(xorstr("Pigs"), &vars::visuals::animals::pig);
				ImGui::Checkbox(xorstr("Wolfs"), &vars::visuals::animals::wolf);
				ImGui::Checkbox(xorstr("Horses"), &vars::visuals::animals::deer);
				ImGui::Checkbox(xorstr("Chickens"), &vars::visuals::animals::chicken);
				if (vars::visuals::animals::bear || vars::visuals::animals::pig || vars::visuals::animals::wolf || vars::visuals::animals::deer || vars::visuals::animals::chicken) {
					ImGui::SliderFloat(xorstr("Animal ESP Distance"), &vars::visuals::animals::draw_distance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance      "), &vars::visuals::animals::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Crates"))) {
				ImGui::Checkbox(xorstr("Chinook Crates"), &vars::visuals::crates::chinook);
				ImGui::Checkbox(xorstr("Airdrops"), &vars::visuals::crates::supply);
				ImGui::Checkbox(xorstr("Heli Crates"), &vars::visuals::crates::heli);
				ImGui::Checkbox(xorstr("Bradley Crates"), &vars::visuals::crates::bradley);
				if (vars::visuals::crates::supply || vars::visuals::crates::bradley || vars::visuals::crates::heli) {
					ImGui::SliderFloat(xorstr("Crate ESP Distance"), &vars::visuals::crates::draw_distance, 5.f, 3000.f);
					ImGui::Checkbox(xorstr("Show Distance "), &vars::visuals::crates::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Vehicles"))) {
				ImGui::Checkbox(xorstr("Minicopters"), &vars::visuals::vehicles::minicopter);
				ImGui::Checkbox(xorstr("Scrap Helis"), &vars::visuals::vehicles::scrapheli);
				ImGui::Checkbox(xorstr("Boats"), &vars::visuals::vehicles::boat);
				ImGui::Checkbox(xorstr("RHIB's"), &vars::visuals::vehicles::rhib);
				if (vars::visuals::vehicles::minicopter || vars::visuals::vehicles::scrapheli || vars::visuals::vehicles::boat || vars::visuals::vehicles::rhib) {
					ImGui::SliderFloat(xorstr("Vehicle ESP Distance"), &vars::visuals::vehicles::draw_distance, 5.f, 3000.f);
					ImGui::Checkbox(xorstr("Show Distance  "), &vars::visuals::vehicles::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Traps"))) {
				ImGui::Checkbox(xorstr("Auto Turrets"), &vars::visuals::turrets::auto_turret);
				ImGui::Checkbox(xorstr("Flame Turrets"), &vars::visuals::turrets::flame_turret);
				ImGui::Checkbox(xorstr("Shotgun Traps"), &vars::visuals::turrets::shotgun_turret);
				ImGui::Checkbox(xorstr("Landmines"), &vars::visuals::turrets::landmine);
				ImGui::Checkbox(xorstr("Beartraps"), &vars::visuals::turrets::bear_trap);
				if (vars::visuals::turrets::auto_turret || vars::visuals::turrets::flame_turret || vars::visuals::turrets::shotgun_turret || vars::visuals::turrets::landmine || vars::visuals::turrets::bear_trap) {
					ImGui::SliderFloat(xorstr("Trap ESP Distance"), &vars::visuals::turrets::draw_distance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance   "), &vars::visuals::turrets::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Base"))) {
				ImGui::Checkbox(xorstr("Tool Cupboards"), &vars::visuals::base::tc);
				ImGui::Checkbox(xorstr("Sleeping Bags"), &vars::visuals::base::sleeping_bag);
				ImGui::Checkbox(xorstr("Beds"), &vars::visuals::base::bed);
				ImGui::Checkbox(xorstr("Boxes"), &vars::visuals::base::boxes);
				if (vars::visuals::base::tc || vars::visuals::base::sleeping_bag || vars::visuals::base::bed || vars::visuals::base::boxes) {
					ImGui::SliderFloat(xorstr("Base ESP Distance"), &vars::visuals::base::draw_distance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance     "), &vars::visuals::base::show_distance);
				}
			}
			if (ImGui::CollapsingHeader(xorstr("Misc "))) {
				ImGui::Checkbox(xorstr("Patrol Heli"), &vars::visuals::patrol_heli);
				ImGui::Checkbox(xorstr("Bradley APC"), &vars::visuals::bradley_apc);
				ImGui::Checkbox(xorstr("Hemp"), &vars::visuals::other::hemp);
				ImGui::Checkbox(xorstr("Corpses"), &vars::visuals::other::corpse);
				ImGui::Checkbox(xorstr("Stashes"), &vars::visuals::other::stash);
				ImGui::Checkbox(xorstr("Dropped / World items"), &vars::visuals::other::dropped_items);
				if (vars::visuals::other::corpse || vars::visuals::other::stash || vars::visuals::other::hemp || vars::visuals::other::dropped_items) {
					ImGui::SliderFloat(xorstr("Misc ESP Distance"), &vars::visuals::other::draw_distance, 5.f, 400.f);
					ImGui::Checkbox(xorstr("Show Distance    "), &vars::visuals::other::show_distance);
				}
			}
			break;
		case 5:
			ImGui::SliderFloat(xorstr("Fov"), &vars::misc::fov, 30.f, 130.f);
			Hotkey(xorstr("Remove Position Forcing"), &vars::keys::forcepos, ImVec2(200.f, 0));
			HelpCheckbox(xorstr("Silent Walk"), &vars::misc::silent_walk, xorstr("You're like flying with noclip, but on the ground... But you're not flying."));
			HelpCheckbox(xorstr("Spoof OnLadder"), &vars::misc::spoof_ladderstate, xorstr("Looks funny and can be used to flyhack up buildings without getting kicked."));
			HelpCheckbox(xorstr("Anti-Aim"), &vars::misc::anti_aim, xorstr("Makes you look like you're spinning on other people's screens."));
			if (vars::misc::anti_aim) {
				ImGui::SliderInt(xorstr("Anti-Aim spin speed"), &vars::misc::anti_aim_speed, 1, 50);
			}
			HelpCheckbox(xorstr("Jesus"), &vars::misc::jesus, xorstr("Allows you to walk on water."));
			HelpCheckbox(xorstr("Walker"), &vars::misc::walker, xorstr("Allows you to walk through trees and players without any resistance."));
			HelpCheckbox(xorstr("Faster Healing"), &vars::misc::faster_healing, xorstr("Allows you to heal faster than usual, no need to spam mouse to heal - you can just hold it down."));
			HelpCheckbox(xorstr("FakeLag"), &vars::misc::fake_lag, xorstr("Makes it looks like you're lagging on other people's screens."));
			HelpCheckbox(xorstr("FakeAdmin"), &vars::misc::fakeadmin, xorstr("Allows you to use certain admin-only commands like 'debugcamera' and 'noclip'. Note: bypasses rustberg's and arabrust's anti-fakeadmin. If you can't move in debugcamera, type 'camspeed 1' in console."));
			HelpCheckbox(xorstr("Annoyer"), &vars::misc::annoyer, xorstr("Annoy anyone that has a door on their base."));
			HelpCheckbox(xorstr("Shoot Anywhere"), &vars::misc::can_attack, xorstr("Allows you to shoot anywhere."));
			HelpCheckbox(xorstr("Omni-Sprint"), &vars::misc::omnidirectional_sprinting, xorstr("Allows you to sprint in any direction."));
			HelpCheckbox(xorstr("Suicide"), &vars::misc::suicide, xorstr("Intantly kills you with fall damage, can be used to quickly respawn or to just annoy someone (it makes a LOT of noise). Be careful using this."));
			ImGui::Checkbox(xorstr("Spiderman"), &vars::misc::spiderman);
			HelpCheckbox(xorstr("Infinite Jump"), &vars::misc::inf_jump, xorstr("Allows you to infinitely jump, beware of flyhack."));
			HelpCheckbox(xorstr("Long Neck"), &vars::misc::long_neck, xorstr("Makes your neck longer, can be used to shoot over certain structures."));
			if (vars::misc::long_neck) {
				Hotkey(xorstr("Long Neck Key"), &vars::keys::longneck, ImVec2(200.f, 0));
			}
			HelpCheckbox(xorstr("InstaRevive"), &vars::misc::insta_revive, xorstr("Instantly picks a downed person."));
			HelpCheckbox(xorstr("Custom Hitsound"), &vars::misc::custom_hitsound, xorstr("When you hit a player, your custom hitsound will play. Make a new folder in C disk called 'plusminus', and put your hitsound inside of there. It has to be in a .wav format and called 'hit'"));
			HelpCheckbox(xorstr("AutoCollect"), &vars::misc::auto_pickup, xorstr("Automatically collects collectables that are close."));
			HelpCheckbox(xorstr("AutoRevive"), &vars::misc::auto_revive, xorstr("Automatically assists / revives downed players that are next to you."));
			if (vars::misc::auto_revive) {
				ImGui::Checkbox(xorstr("Revive Teammates Only"), &vars::misc::revive_team_only);
			}
			HelpCheckbox(xorstr("Auto Farm Ores"), &vars::misc::auto_farm_ore, xorstr("Will automatically hit ore hotspots when you are close to them with a melee weapon"));
			HelpCheckbox(xorstr("Auto Farm Trees"), &vars::misc::auto_farm_tree, xorstr("Will automatically hit trees when you are close to them with a melee weapon, hit the tree to start automatically hitting it. Keep in mind, you need to have line of sight with the hitmarker!"));
			HelpCheckbox(xorstr("Rayleigh Changer"), &vars::misc::rayleigh_changer, xorstr("Makes your sky look pretty when day."));
			if (vars::misc::rayleigh_changer) {
				ImGui::SliderFloat(xorstr("Rayleigh Amount"), &vars::misc::rayleigh, 1.f, 50.f);
			}
			HelpCheckbox(xorstr("Bright Ambient"), &vars::misc::bright_ambient, xorstr("Nightmode, fullbright, whatever you want to call it."));
			ImGui::Checkbox(xorstr("Custom Time"), &vars::misc::custom_time);
			if (vars::misc::custom_time) {
				ImGui::SliderFloat(xorstr("Time"), &vars::misc::time, 0.f, 12.f);
			}
			ImGui::Checkbox(xorstr("Gravity"), &vars::misc::gravity);
			if (vars::misc::gravity_modifier) {
				ImGui::SliderFloat(xorstr("Gravity Value"), &vars::misc::gravity_modifier, 0.f, 10.f);
				Hotkey(xorstr("Gravity Key"), &vars::keys::gravitykey, ImVec2(120.f, 0));
			}
			///if (ImGui::Button(xorstr("crasher master"), ImVec2(100.f, 0))) {
			//	yeetus = true;
			//}
			break;
		case 6:
			ImGui::InputText("", vars::stuff::ConfigName, 0x100);
			if (ImGui::Button(xorstr("Save Config"), ImVec2(100.f, 0))) {
				config.Save();
			}
			ImGui::SameLine();
			if (ImGui::Button(xorstr("Load Config"), ImVec2(100.f, 0))) {
				config.Load();
			}
			ImGui::Separator();
			if (ImGui::Checkbox(xorstr("Developer Mode [don't touch]"), &vars::stuff::debugtab)) {
				ImGui::SliderFloat(xorstr("float"), &vars::stuff::testFloat, 0.f, 200.f);
				ImGui::Checkbox(xorstr("bool"), &vars::stuff::testBool);
				ImGui::SliderInt(xorstr("int"), &vars::stuff::testInt, 0, 100);
				ImGui::InputText(xorstr("char"), vars::stuff::testChar, 0x100);
			}
			ImGui::Checkbox(xorstr("Panic"), &vars::stuff::Panic);
			break;
		}
		ImGui::PopFont();
		ImGui::End();
	}
}