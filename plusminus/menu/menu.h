#include <vector>
#include <algorithm>
bool applied = false;
namespace menu {
	struct TabInfo {
		ImRect bb;
		unsigned int index;
	};
	ImVec2 cursor_pos = { 0,0 };
	ImFont* title_font = nullptr, * tabs_font = nullptr, * menu_font = nullptr;
	static int tab_index = 0;
	static float border_bang = 1.0f;
	static int old_tab_index = 0;
	std::vector<TabInfo> tabs_info;

	void apply_fonts() { // C:\\Windows\\Fonts\\Tahoma.ttf
		ImGuiIO& io = ImGui::GetIO();
		title_font = io.Fonts->AddFontFromFileTTF("", 24);
		tabs_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16);
		menu_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
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
	void style() {
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
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
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
		colors[ImGuiCol_TabButton] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
		colors[ImGuiCol_TabButtonHovered] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
		colors[ImGuiCol_TabButtonActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
		colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	}

	static const char* psilent_targeting[]{
		"Players",
		"Helicopter",
	};
	static const char* healthbar_style[]{
		"Left Side",
		"Bottom",
	};
	static const char* npc_healthbar_style[]{
		"Left Side",
		"Bottom",
	};
	static const char* building_grade[]{
		"Twig",
		"Wood",
		"Stone",
		"Metal",
		"HQM",
	};
	static const char* npc_box_style[]{
		"Normal",
		"Cornered",
	};
	static const char* box_style[]{
		"Normal",
		"Cornered",
		"3D",
	};
	static const char* anti_aim_yaw[]{
		"Down",
		"Up",
	};
	static const char* target_tracer_pos[]{
		"Classic",
		"Middle",
	};
	static const char* tracer_pos[]{
		"Classic",
		"Middle",
	};
	bool tab_info_already_exist(std::vector<TabInfo> infos, unsigned int index) {
		for (int i = 0; i < infos.size(); i++)
			if (infos[i].index == index) return true;

		return false;
	}
	void TabBorderAnim(unsigned int current_tab, unsigned int old_tab) {
		if (tabs_info.size() > 0) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;
			auto& style = ImGui::GetStyle();
			auto old_tab_rect = tabs_info[old_tab].bb;
			auto tab_rect = tabs_info[current_tab].bb;
			auto tab_min = old_tab_rect.Min + (tab_rect.Min - old_tab_rect.Min) * border_bang;
			auto tab_max = old_tab_rect.Max + (tab_rect.Max - old_tab_rect.Max) * border_bang;
			window->DrawList->AddRectFilled(tab_min, tab_max, ImColor(110, 110, 110, 255), style.FrameRounding, ImDrawCornerFlags_All);
		}

	}
	IMGUI_API bool TabButton(const char* label, const ImVec2& size_arg, unsigned int index, ImGuiButtonFlags flags = 0) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
			flags |= ImGuiButtonFlags_Repeat;
		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

		// Render
		const ImU32 col = ImGui::GetColorU32((hovered && held) ? ImGuiCol_TabButtonActive : hovered ? ImGuiCol_TabButtonHovered : ImGuiCol_TabButton);
		const ImU32 border_col = ImGui::GetColorU32((hovered && held) ? ImGui::GetColorU32(ImVec4(1, 1, 1, 0.7)) : hovered ? ImColor(110, 110, 110, 115) : ImGui::GetColorU32(ImVec4(1, 1, 1, 0.0)));
		window->DrawList->AddRectFilled(bb.Min, bb.Max, border_col, style.FrameRounding, ImDrawCornerFlags_All);
		ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
		if (!tab_info_already_exist(tabs_info, index)) {
			TabInfo tab_info;
			tab_info.bb = bb;
			tab_info.index = index;
			tabs_info.push_back(tab_info);
		}

		return pressed;
	}
	IMGUI_API bool Tab(unsigned int index, const char* label, int* selected, float width = 0) {
		if (TabButton(label, ImVec2(width, 30), index)) {
			border_bang = 0.0f;
			old_tab_index = *selected;
			*selected = index;
		}
		return *selected == index;
	}

	void combat() {
		HelpCheckbox(xorstr("Always Headshot"), &vars::combat::always_headshot, xorstr("Even if you hit a person in the body, the bullet will teleport to the head."));
		HelpCheckbox(xorstr("Always Heli Weakspot"), &vars::combat::always_heli_rotor, xorstr("If you hit any part of the helicopter, the bullet will teleport to the weakspot (rotor)."));
		HelpCheckbox(xorstr("Silent Melee"), &vars::combat::silent_melee, xorstr("Will automatically hit people next to you with a melee weapon in your hand."));
		HelpCheckbox(xorstr("pSilent"), &vars::combat::psilent, xorstr("Bullets will just fly to the target."));
		if (vars::combat::psilent) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("pSilent Targeting"), &vars::combat::psilenttarget, psilent_targeting, IM_ARRAYSIZE(psilent_targeting));
			ImGui::PopItemWidth();
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
		HelpCheckbox(xorstr("Visualize Prediction"), &vars::combat::visualize_prediction, xorstr("Shows a little red circle indicating where the prediction is predicting."));
		ImGui::Checkbox(xorstr("Visualize Targeting Fov"), &vars::combat::visualize_fov);
		ImGui::Checkbox(xorstr("Body Aim"), &vars::combat::bodyaim);
		ImGui::SliderFloat(xorstr("Targeting Fov"), &vars::combat::fov, 20.f, 1000.f);
		ImGui::SliderFloat(xorstr("Max Targeting Distance"), &vars::combat::range, 0.f, 400.f);
		Hotkey(xorstr("Lock Target"), &vars::keys::locktarget, ImVec2(120.f, 0));
		ImGui::Checkbox(xorstr("Ignore Players"), &vars::combat::ignore_players);
		ImGui::Checkbox(xorstr("Ignore Heli"), &vars::combat::ignore_heli);
		ImGui::Checkbox(xorstr("Ignore NPC's"), &vars::combat::ignore_npc);
		ImGui::Checkbox(xorstr("Ignore Teammates"), &vars::combat::ignore_team);
		ImGui::Checkbox(xorstr("Ignore Sleeping"), &vars::combat::ignore_sleepers);
	}
	void weapons() {
		ImGui::Checkbox(xorstr("No Recoil"), &vars::weapons::no_recoil);
		if (vars::weapons::no_recoil) {
			ImGui::SliderFloat(xorstr("Recoil"), &vars::weapons::recoil_control, 0.f, 100.f);
		}
		ImGui::Checkbox(xorstr("No Spread"), &vars::weapons::no_spread);
		ImGui::Checkbox(xorstr("No Sway"), &vars::weapons::no_sway);
		ImGui::Checkbox(xorstr("No Attack Animation"), &vars::weapons::remove_attack_anim);
		ImGui::Checkbox(xorstr("Rapid Fire"), &vars::weapons::rapid_fire);
		ImGui::Checkbox(xorstr("Force Automatic"), &vars::weapons::automatic);
		ImGui::Checkbox(xorstr("Thick Bullets"), &vars::weapons::thick_bullet);
		ImGui::Checkbox(xorstr("Faster Bullets"), &vars::weapons::fast_bullets);
		HelpCheckbox(xorstr("Minicopter Aim"), &vars::weapons::minicopter_aim, xorstr("Allows you to hold items on minicopters."));
		ImGui::Checkbox(xorstr("EokaTap"), &vars::weapons::eokatap);
		ImGui::Checkbox(xorstr("FastBow"), &vars::weapons::fastbow);
		HelpCheckbox(xorstr("Penetrate"), &vars::weapons::penetrate, xorstr("Allows you to shoot through deployables, trees."));
		HelpCheckbox(xorstr("Spoof Hit Distance"), &vars::weapons::spoof_hitdistance, xorstr("Flex with big meters."));
		if (vars::weapons::spoof_hitdistance) {
			ImGui::SliderFloat(xorstr("Distance"), &vars::weapons::hitdistance, 1000.f, 10000.f);
		}
	}
	void players() {
		ImGui::Checkbox(xorstr("Name"), &vars::players::name);
		ImGui::Checkbox(xorstr("Box"), &vars::players::box);
		if (vars::players::box) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Box Style"), &vars::players::boxstyle, box_style, IM_ARRAYSIZE(box_style));
			ImGui::PopItemWidth();
		}
		ImGui::Checkbox(xorstr("Fill Box"), &vars::players::fillbox);
		ImGui::Checkbox(xorstr("Skeleton"), &vars::players::skeleton);
		ImGui::Checkbox(xorstr("Health and Distance"), &vars::players::healthdist);
		ImGui::Checkbox(xorstr("Healthbar"), &vars::players::healthbar);
		if (vars::players::healthbar) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Healthbar Style"), &vars::players::healthbarstyle, healthbar_style, IM_ARRAYSIZE(healthbar_style));
			ImGui::PopItemWidth();
		}
		ImGui::Checkbox(xorstr("Weapon"), &vars::players::weapon);
		ImGui::Checkbox(xorstr("Tracers"), &vars::players::tracers);
		if (vars::players::tracers) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Tracer Position"), &vars::players::tracers_pos, tracer_pos, IM_ARRAYSIZE(tracer_pos));
			ImGui::PopItemWidth();
		}
		HelpCheckbox(xorstr("Target Tracers"), &vars::players::targetline, xorstr("Shows a line to the targeted player."));
		if (vars::players::targetline) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Target Tracer Position"), &vars::players::targetline_pos, target_tracer_pos, IM_ARRAYSIZE(target_tracer_pos));
			ImGui::PopItemWidth();
		}
		HelpCheckbox(xorstr("Chams"), &vars::players::chams, xorstr("Colors player models and their clothes")); ImGui::SameLine(); ImGui::ColorButton(xorstr("Chams##Color"), vars::colors::chams);
		if (vars::players::chams) {
			ImGui::Checkbox(xorstr("XQZ Chams"), &vars::players::chams_xqz);
		}
		//HelpCheckbox(xorstr("Target Belt / Clothes"), &vars::players::belt, xorstr("Shows the targeted player's belt and clothing."));
		ImGui::Checkbox(xorstr("Ignore Sleepers"), &vars::players::sleeperignore);
	}
	void npc() {
		ImGui::Checkbox(xorstr("Name "), &vars::npc::name);
		ImGui::Checkbox(xorstr("Box "), &vars::npc::box);
		if (vars::npc::box) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Box Style "), &vars::npc::boxstyle, npc_box_style, IM_ARRAYSIZE(npc_box_style));
			ImGui::PopItemWidth();
		}
		ImGui::Checkbox(xorstr("Fill Box "), &vars::npc::fillbox);
		ImGui::Checkbox(xorstr("Skeleton "), &vars::npc::skeleton);
		ImGui::Checkbox(xorstr("Health and Distance "), &vars::npc::healthdist);
		ImGui::Checkbox(xorstr("Healthbar "), &vars::npc::healthbar);
		if (vars::npc::healthbar) {
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Healthbar Style "), &vars::npc::healthbarstyle, npc_healthbar_style, IM_ARRAYSIZE(npc_healthbar_style));
			ImGui::PopItemWidth();
		}
		ImGui::Checkbox(xorstr("Weapon "), &vars::npc::weapon);
		ImGui::Checkbox(xorstr("Tracers "), &vars::npc::tracers);
		ImGui::ColorButton(xorstr("Npc##Color"), vars::colors::npc_esp); ImGui::SameLine(); ImGui::Text(xorstr("NPC Color"));
	}
	void visuals() {
		
		ImGui::Checkbox(xorstr("Raids"), &vars::visuals::raid_esp);
		ImGui::Checkbox(xorstr("Patrol Heli"), &vars::visuals::patrol_heli);
		ImGui::Checkbox(xorstr("Bradley APC"), &vars::visuals::bradley_apc);
		ImGui::Checkbox(xorstr("Default Crosshair"), &vars::crosshair::default);
		ImGui::Checkbox(xorstr("Custom Crosshair"), &vars::crosshair::custom);
		if (vars::crosshair::custom) {
			ImGui::SliderFloat(xorstr("Gap"), &vars::crosshair::gap, 0.f, 50.f);
			ImGui::SliderFloat(xorstr("Length"), &vars::crosshair::length, 0.f, 50.f);
			ImGui::Checkbox(xorstr("Dot"), &vars::crosshair::dot);
		}
		if (ImGui::CollapsingHeader(xorstr("Radar"))) {
			ImGui::Checkbox(xorstr("Radar "), &vars::visuals::radar_);
			if (vars::visuals::radar_) {
				ImGui::SliderFloat(xorstr("Size"), &vars::visuals::radar::size, 5.f, 400.f);
				ImGui::SliderFloat(xorstr("Range"), &vars::visuals::radar::range, 5.f, 400.f);
			}
		}
		if (ImGui::CollapsingHeader(xorstr("Ores"))) {
			ImGui::Checkbox(xorstr("Ore Path"), &vars::ores::closest_ore);
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
			ImGui::Checkbox(xorstr("Hemp"), &vars::visuals::other::hemp);
			ImGui::Checkbox(xorstr("Corpses"), &vars::visuals::other::corpse);
			ImGui::Checkbox(xorstr("Stashes"), &vars::visuals::other::stash);
			ImGui::Checkbox(xorstr("Dropped / World items"), &vars::visuals::other::dropped_items);
			if (vars::visuals::other::corpse || vars::visuals::other::stash || vars::visuals::other::hemp || vars::visuals::other::dropped_items) {
				ImGui::SliderFloat(xorstr("Misc ESP Distance"), &vars::visuals::other::draw_distance, 5.f, 400.f);
				ImGui::Checkbox(xorstr("Show Distance    "), &vars::visuals::other::show_distance);
			}
		}
	}
	void misc() {
		ImGui::SliderFloat(xorstr("Fov"), &vars::misc::fov, 30.f, 130.f);
		Hotkey(xorstr("Remove Position Forcing"), &vars::keys::forcepos, ImVec2(200.f, 0));
		Hotkey(xorstr("Zoom"), &vars::keys::zoom, ImVec2(200.f, 0));
		HelpCheckbox(xorstr("On Ladder"), &vars::misc::spoof_ladderstate, xorstr("Looks funny and can be used to walk silently."));
		HelpCheckbox(xorstr("Anti-Aim"), &vars::misc::anti_aim, xorstr("Makes you look like you're spinning on other people's screens."));
		if (vars::misc::anti_aim) {
			ImGui::SliderInt(xorstr("Spin Speed"), &vars::misc::anti_aim_speed, 1, 50);
			ImGui::PushItemWidth(100);
			ImGui::Combo(xorstr("Yaw"), &vars::misc::anti_aim_yaw, anti_aim_yaw, IM_ARRAYSIZE(anti_aim_yaw));
			ImGui::PopItemWidth();
			ImGui::Checkbox(xorstr("Indicator"), &vars::misc::anti_aim_indicator);
		}
		HelpCheckbox(xorstr("Weapon Spam"), &vars::misc::weapon_spam, xorstr("Spams the shit out of your weapon's attack animation, everyone can see and hear it (very loud)."));
		HelpCheckbox(xorstr("Flyhack Indicator"), &vars::misc::flyhack_indicator, xorstr("Shows you how much you can flyhack before getting kicked."));
		HelpCheckbox(xorstr("Jesus"), &vars::misc::jesus, xorstr("Allows you to walk on water."));
		HelpCheckbox(xorstr("Walker"), &vars::misc::walker, xorstr("Allows you to walk through trees and players without any resistance."));
		HelpCheckbox(xorstr("Faster Healing"), &vars::misc::faster_healing, xorstr("Allows you to heal faster than usual, no need to spam mouse to heal - you can just hold it down."));
		HelpCheckbox(xorstr("FakeLag"), &vars::misc::fake_lag, xorstr("Makes it looks like you're lagging on other people's screens."));
		HelpCheckbox(xorstr("FakeAdmin"), &vars::misc::fakeadmin, xorstr("Allows you to use certain admin-only commands like 'debugcamera' and 'noclip'. Note: bypasses rustberg's and arabrust's anti-fakeadmin. If you can't move in debugcamera, type 'camspeed 1' in console."));
		HelpCheckbox(xorstr("Annoyer"), &vars::misc::annoyer, xorstr("Annoy anyone that has a door on their base."));
		HelpCheckbox(xorstr("Shoot Anywhere"), &vars::misc::can_attack, xorstr("Allows you to shoot anywhere."));
		HelpCheckbox(xorstr("Omni-Sprint"), &vars::misc::omnidirectional_sprinting, xorstr("Allows you to sprint in any direction."));
		HelpCheckbox(xorstr("Suicide"), &vars::misc::suicide, xorstr("Intantly kills you with fall damage, can be used to quickly respawn. Be careful with this."));
		if (vars::misc::suicide) {
			Hotkey(xorstr("Suicide Key"), &vars::keys::suicide, ImVec2(200.f, 0));
		}
		HelpCheckbox(xorstr("Mass Suicide"), &vars::misc::mass_suicide, xorstr("Intantly kills you with fall damage, can be used to troll / annoy people. Be careful with this."));
		ImGui::Checkbox(xorstr("No Fall Damage"), &vars::misc::no_fall);
		ImGui::Checkbox(xorstr("Spiderman"), &vars::misc::spiderman);
		HelpCheckbox(xorstr("Infinite Jump"), &vars::misc::inf_jump, xorstr("Allows you to infinitely jump, beware of flyhack."));
		HelpCheckbox(xorstr("Long Neck"), &vars::misc::long_neck, xorstr("Makes your neck longer, can be used to shoot over certain structures."));
		if (vars::misc::long_neck) {
			Hotkey(xorstr("Long Neck Key"), &vars::keys::longneck, ImVec2(200.f, 0));
		}
		HelpCheckbox(xorstr("InstaRevive"), &vars::misc::insta_revive, xorstr("Instantly picks a downed person."));
		ImGui::Checkbox(xorstr("Gravity"), &vars::misc::gravity);
		if (vars::misc::gravity) {
			ImGui::SliderFloat(xorstr("Gravity Value"), &vars::misc::gravity_modifier, 0.f, 10.f);
			Hotkey(xorstr("Gravity Key"), &vars::keys::gravitykey, ImVec2(120.f, 0));
		}
		if (ImGui::CollapsingHeader(xorstr("Aesthetics"))) {
			HelpCheckbox(xorstr("HitLogs"), &vars::misc::hit_logs, xorstr("Shows logs on players you hit."));
			HelpCheckbox(xorstr("BetterJump"), &vars::misc::better_jump, xorstr("Makes your jumps smoother."));
			HelpCheckbox(xorstr("Custom Hitsound"), &vars::misc::custom_hitsound, xorstr("When you hit a player, your custom hitsound will play. Make a new folder in C disk called 'plusminus', and put your hitsound inside of there. It has to be in a .wav format and called 'hit'"));
			HelpCheckbox(xorstr("Rayleigh Changer"), &vars::misc::rayleigh_changer, xorstr("Makes your sky look pretty when day."));
			if (vars::misc::rayleigh_changer) {
				ImGui::SliderFloat(xorstr("Rayleigh Amount"), &vars::misc::rayleigh, 1.f, 50.f);
			}
			HelpCheckbox(xorstr("Bright Ambient"), &vars::misc::bright_ambient, xorstr("Nightmode, fullbright, whatever you want to call it."));
			ImGui::SameLine(); ImGui::ColorButton(xorstr("Ambient##Color"), vars::colors::ambient_color);
			ImGui::Checkbox(xorstr("Custom Time"), &vars::misc::custom_time);
			if (vars::misc::custom_time) {
				ImGui::SliderFloat(xorstr("Time"), &vars::misc::time, 0.f, 12.f);
			}
		}
		if (ImGui::CollapsingHeader(xorstr("Automation"))) {
			HelpCheckbox(xorstr("FarmBot"), &vars::misc::farmbot, xorstr("Automatically walks to nearest ore."));
			HelpCheckbox(xorstr("Auto Farm Barrels"), &vars::misc::auto_farm_barrel, xorstr("Will automatically hit barrels when you are close to them with a melee weapon"));
			HelpCheckbox(xorstr("Auto Farm Ores"), &vars::misc::auto_farm_ore, xorstr("Will automatically hit ore hotspots when you are close to them with a melee weapon"));
			HelpCheckbox(xorstr("Auto Farm Trees"), &vars::misc::auto_farm_tree, xorstr("Will automatically hit trees when you are close to them with a melee weapon, hit the tree to start automatically hitting it. Keep in mind, you need to have line of sight with the hitmarker!"));
			HelpCheckbox(xorstr("Auto Collect"), &vars::misc::auto_pickup, xorstr("Automatically collects collectables that are close."));
			HelpCheckbox(xorstr("Auto Revive"), &vars::misc::auto_revive, xorstr("Automatically assists / revives downed players that are next to you."));
			if (vars::misc::auto_revive) {
				ImGui::Checkbox(xorstr("Revive Teammates Only"), &vars::misc::revive_team_only);
			}
			HelpCheckbox(xorstr("Auto Upgrade"), &vars::misc::auto_grade, xorstr("Will automatically upgrade any building blocks near you. Doesn't require a hammer."));
			if (vars::misc::auto_grade) {
				ImGui::PushItemWidth(100);
				ImGui::Combo(xorstr("Building Grade"), &vars::misc::grade_, building_grade, IM_ARRAYSIZE(building_grade));
				ImGui::PopItemWidth();
			}
		}
	}
	void other() {
		ImGui::InputText("", vars::stuff::ConfigName, 0x100);
		if (ImGui::Button(xorstr("Save Config"), ImVec2(100.f, 0))) {
			config.Save();
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Load Config"), ImVec2(100.f, 0))) {
			config.Load();
		}
		ImGui::Checkbox(xorstr("Developer Mode [don't touch]"), &vars::stuff::debugtab);
		if (vars::stuff::debugtab) {
			ImGui::SliderFloat(xorstr("float"), &vars::stuff::testFloat, 0.f, 500.f);
			ImGui::Checkbox(xorstr("bool"), &vars::stuff::testBool);
			ImGui::SliderInt(xorstr("int"), &vars::stuff::testInt, 0, 100);
			ImGui::InputText(xorstr("char"), vars::stuff::testChar, 0x100);
		}
		ImGui::Checkbox(xorstr("Panic"), &vars::stuff::Panic);
	}
}
void DrawMenu() {
	menu::style();
	switch (menu::tab_index) {
	case 5:
		ImGui::SetNextWindowSize(ImVec2(500, 550));
		break;
	default:
		ImGui::SetNextWindowSize(ImVec2(500, 0));
		break;
	}
	if (ImGui::Begin("##menu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)) {
		menu::cursor_pos = ImGui::GetCursorPosDD();
		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImVec2(118, ImGui::GetWindowHeight()), ImColor(51, 51, 51, 128), ImGui::GetStyle().FrameRounding, ImDrawCornerFlags_All);
		ImGui::Columns(2, nullptr, false);
		{
			if (menu::border_bang < 1.0f) menu::border_bang = std::clamp(menu::border_bang + 1.0f / 0.15f * ImGui::GetIO().DeltaTime, 0.0f, 1.0f);
			menu::TabBorderAnim(menu::tab_index, menu::old_tab_index);
			menu::tabs_info.clear();
			ImGui::PushFont(menu::tabs_font);

			menu::Tab(0, (xorstr("Combat")), &menu::tab_index, 100);
			menu::Tab(1, (xorstr("Weapons")), &menu::tab_index, 100);
			menu::Tab(2, (xorstr("Players")), &menu::tab_index, 100);
			menu::Tab(3, (xorstr("NPC's")), &menu::tab_index, 100);
			menu::Tab(4, (xorstr("Visuals")), &menu::tab_index, 100);
			menu::Tab(5, (xorstr("Misc")), &menu::tab_index, 100);
			menu::Tab(6, (xorstr("Other")), &menu::tab_index, 100);
			ImGui::PopFont();
		}
		ImGui::NextColumn();
		ImGui::SetColumnOffset(1, 117);
		{
			ImGui::PushFont(menu::menu_font);
			switch (menu::tab_index) {
			case 0:
				menu::combat();
				break;
			case 1:
				menu::weapons();
				break;
			case 2:
				menu::players();
				break;
			case 3:
				menu::npc();
				break;
			case 4:
				menu::visuals();
				break;
			case 5:
				menu::misc();
				break;
			case 6:
				menu::other();
				break;
			}
			ImGui::PopFont();
		}
	} ImGui::End();
}