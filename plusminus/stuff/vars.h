HANDLE handle2;
bool init, show = true;
bool yeetus = false;
#define null NULL
namespace vars {
	namespace stuff {
		uintptr_t tree = 0;
		int anti_aim_ = 0;
		std::wstring dlldirectory;
		bool debugtab = false;
		int testInt = 0;
		float testFloat = 270.f;
		bool testBool = false;
		char testChar[0x100] = "testyvesty";
		bool Panic = false;
		int ScreenHeight = 0;
		int ScreenWidth = 0;
		float BoneToAim = 0.5;
		char ConfigName[0x100] = "cfg";
	}
	namespace keys {
		int zoom = { 0x42 };
		int suicide = { 0x5A };
		int longneck = { 0x4D };
		int forcepos{ 0x4E };
		int psilent{ 0x50 }; // P key
		int locktarget{ 0x4A };
		int aimkey{ 0x58 }; // VK_RMOUSE
		int gravitykey{ 0x04 };
	}
	namespace stor {
		uintptr_t gBase = NULL;
		uintptr_t closestPlayer = NULL;
		uintptr_t closestHeli = NULL;
		uintptr_t closestHeliObj = NULL;
	}
	namespace combat {
		bool tree_reflect = false;
		bool magicbollet = false;
		bool always_heli_rotor = false;
		bool hitbox_override = false;
		int hs_percentage = 50;
		bool silent_melee = false;
		bool psilent = false;
		bool psilent_autoshoot = false;
		bool psilentonkey = false;
		int psilenttarget = 0;
		bool aimbot = false;
		bool smooth = false;
		int smooth_factor = 1;

		float range = 300.f;
		float fov = 100.f;
		bool visualize_fov = false;
		bool lock_target = false;
		bool ignore_players = false;
		bool ignore_heli = false;
		bool ignore_sleepers = false;
		bool ignore_team = true;
		bool ignore_npc = false;
	}
	namespace weapons {
		bool no_recoil = false;
		float recoil_control = 100.f;
		bool fast_bullets = false;
		bool penetrate = false;
		bool minicopter_aim = false;
		bool spoof_hitdistance = false;
		float hitdistance = 100.f;
		bool remove_attack_anim = false;
		bool no_spread = false;
		bool automatic = false;
		bool thick_bullet = false;
		bool no_sway = false;
		bool rapid_fire = false;
		bool fastbow = false;
		bool eokatap = false;
		
	}
	namespace players {
		bool chams = false;
		bool chams_xqz = false;
		bool belt = false;
		float beltx = 50.f;
		float belty = 50.f;
		bool box = false;
		int boxstyle = 0;
		bool skeleton = false;
		bool name = false;
		bool healthdist = false;
		bool healthbar = false;
		int healthbarstyle = 0;
		bool weapon = false;
		bool sleeperignore = false;
		bool tracers = false;
		int tracers_pos = 0;
		bool targetline = false;
		int targetline_pos = 0;
		bool fillbox = false;
	}
	namespace npc {
		bool box = false;
		int boxstyle = false;
		bool skeleton = false;
		bool name = false;
		bool healthdist = false;
		bool healthbar = false;
		int healthbarstyle = 0;
		bool weapon = false;
		bool tracers = false;
		bool fillbox = false;
	}
	namespace ores {
		bool show_collectables = false;
		bool stone = false;
		bool sulfur = false;
		bool metal = false;
		bool show_distance = false;
		float draw_distance = 300.f;
	}
	namespace visuals {
		bool raid_esp = false;
		bool bradley_apc = false;
		bool patrol_heli = false;
		bool radar_ = false;
		namespace radar {
			float x = 300.f;
			float y = 300.f;
		}
		namespace base {
			bool tc = false;
			bool sleeping_bag = false;
			bool bed = false;
			bool boxes = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace vehicles {
			bool minicopter = false;
			bool scrapheli = false;
			bool boat = false;
			bool rhib = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace turrets {
			bool auto_turret = false;
			bool flame_turret = false;
			bool shotgun_turret = false;
			bool landmine = false;
			bool bear_trap = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace other {
			bool dropped_items = false;
			bool corpse = false;
			bool stash = false;
			bool hemp = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace crates {
			bool supply = false;
			bool chinook = false;
			bool heli = false;
			bool bradley = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace animals {
			bool bear = false;
			bool pig = false;
			bool chicken = false;
			bool wolf = false;
			bool deer = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
	}
	namespace misc	{
		bool spiderman = false;
		bool better_jump = false;
		bool no_fall = false;
		bool anti_aim_indicator = false;
		bool hit_logs = false;
		bool auto_farm_ore = false;
		bool auto_farm_tree = false;
		bool can_attack = false;
		bool jesus = false;
		bool walker = false;
		bool auto_grade = false;
		int grade_ = 0;
		bool faster_healing = false;
		bool suicide = false;
		bool mass_suicide = false;
		bool long_neck = false;
		bool inf_jump = false;
		bool insta_revive = false;
		bool auto_revive = false;
		bool revive_team_only = false;
		bool rayleigh_changer = false;
		float rayleigh = 10.f;
		bool annoyer = false;
		bool bright_ambient = false;
		bool auto_pickup = false;
		bool spoof_ladderstate = false;
		bool anti_aim = false;
		int anti_aim_speed = 10;
		int anti_aim_yaw = false;
		bool fake_lag = false;
		bool silent_walk = false;
		float fov = 90.f;
		bool gravity = false;
		float gravity_modifier = 0.f;
		bool custom_hitsound = false;
		bool omnidirectional_sprinting = false;
		bool fakeadmin = false;
		bool custom_time = false;
		float time = 10.0f;
	}
	namespace crosshair {
		bool default = false;

		bool custom = false;
		bool dot = false;
		float gap = 5.f;
		float length = 5.f;
	}
	namespace colors {
		ImVec4 player_esp = { 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 team_esp = { 0.f, 1.0f, 0.f, 1.0f };
		ImVec4 dead_esp = { 1.0f, 0.f, 0.f, 1.0f };
		ImVec4 sleeper_esp = { 1.0f, 0.5f, 0.f, 1.0f };
		ImVec4 chams = { 1.0f, 0.f, 0.f, 1.0f };

		ImVec4 npc_esp = { 1.0f, 1.0f, 0.f, 1.0f };

		ImVec4 ambient_color = { 0.8f, 0.8f, 0.8f, 0.8f };
	}
}