#include "hooks/defs.h"
int yeet = 0;
int flick = 0;
int yaw = 100;
using namespace hk_defs;
namespace hk {
	namespace exploit {
		void DoMovement(Projectile* projectile, float deltaTime) {
			if (projectile->isAuthoritative( ) && vars::stuff::testBool) {
				f_object target = f_object::get_closest_object(projectile->currentPosition( ), xorstr("player.prefab"));

				if (target.valid) {
					Vector3 tar = reinterpret_cast<BasePlayer*>(target.entity)->get_bone_pos(head);
					if (utils::LineOfSight(tar, projectile->currentPosition( )) && projectile->traveledDistance( ) >= Math::Distance_3D(projectile->currentPosition( ), LocalPlayer::Entity( )->get_bone_pos(head))) {
						if (!reinterpret_cast<BasePlayer*>(target.entity)->HasFlags(PlayerFlags::Sleeping)) {
							Transform* transform = reinterpret_cast<Transform*>(reinterpret_cast<BasePlayer*>(target.entity)->mono_transform(head));

							HitTest* hitTest = projectile->hitTest( );
							hitTest->DidHit( ) = true;
							hitTest->HitEntity((BaseEntity*)target.entity);
							hitTest->HitTransform( ) = transform;
							//hitTest->HitMaterial() = il2cpp::String::New("Flesh");

							hitTest->HitPoint( ) = transform->InverseTransformPoint(projectile->currentPosition( ));
							hitTest->HitNormal( ) = transform->InverseTransformDirection(projectile->currentPosition( ));

							hitTest->AttackRay( ) = Ray(projectile->currentPosition( ), reinterpret_cast<BasePlayer*>(target.entity)->get_bone_pos(head) - projectile->currentPosition( ));

							projectile->DoHit(hitTest, hitTest->HitPointWorld( ), hitTest->HitNormalWorld( ));
							return;
						}
					}
				}
			}
			return original_domovement(projectile, deltaTime);
		}
		bool Refract(Projectile* prj, uint32_t seed, Vector3 point, Vector3 normal, float resistancePower) {
			if (vars::combat::tree_reflect) {
				Vector3 target = vars::combat::bodyaim ? reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(spine1) : reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head);
				float gravity;
				if (LocalPlayer::Entity( )->GetActiveWeapon( )->GetID( ) == 1540934679 || LocalPlayer::Entity( )->GetActiveWeapon( )->GetID( ) == 1602646136) {
					gravity = 2.f;
				}
				else {
					gravity = GetGravity(LocalPlayer::Entity( )->GetActiveWeapon( )->LoadedAmmo( ));
				}
				a::Prediction(prj->currentPosition( ), target, reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->newVelocity( ), GetBulletSpeed( ), gravity);
				prj->currentVelocity((target - prj->currentPosition( )) * (GetBulletSpeed( ) / 75.f));
				prj->currentPosition(prj->currentPosition( ) + prj->currentVelocity( ).Normalized( ) * 0.001f);
			}
			else {
				return original_refract(prj, seed, point, normal, resistancePower);
			}
		}
	}
	namespace misc {
		void ClientUpdate(BasePlayer* player) {
			lol::cachePlayer(player);

			return original_clientupdate(player);
		}
		void ClientUpdate_Sleeping(BasePlayer* player) {
			if (!vars::players::sleeperignore) {
				lol::cachePlayer(player);
			}

			return original_clientupdate_sleeping(player);
		}
		void Jump(PlayerWalkMovement* playerwalkmovement, ModelState* modelstate, bool indirection) {
			if (vars::misc::better_jump) {
				bool climbing = read(playerwalkmovement + 0x132, bool);
				bool sliding = read(playerwalkmovement + 0x134, bool);
				bool st = (climbing = (sliding = false));

				bool get_jmpd = reinterpret_cast<bool(*)(ModelState*)>(vars::stor::gBase + CO::get_jumped)(modelstate);
				bool st2 = (get_jmpd = true);

				write(playerwalkmovement + 0x130, st, bool);
				write(playerwalkmovement + 0x138, st2, bool);
				write(playerwalkmovement + 0xC0, Time::time( ), float);
				write(playerwalkmovement + 0xA8, null, uintptr_t);

				uintptr_t rigid = read(playerwalkmovement + 0x90, uintptr_t);
				Vector3 targetVel = reinterpret_cast<Vector3(*)(uintptr_t)>(vars::stor::gBase + CO::get_velocity)(rigid);

				reinterpret_cast<void(*)(uintptr_t, Vector3)>(vars::stor::gBase + CO::set_velocity)(rigid, Vector3(targetVel.x, 10, targetVel.z));
			}
			else { return original_jump(playerwalkmovement, modelstate, indirection); }
		}
		void OnLand(BasePlayer* ply, float fVel) {
			if (!vars::misc::no_fall)
				return original_onland(ply, fVel);
		}
		void ForcePositionTo(BasePlayer* pl, Vector3 pos) {
			if (!GetAsyncKeyState(vars::keys::forcepos))
				return original_forcepos(pl, pos);
		}
		void VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
			if (vars::players::chams && vars::players::chams_xqz) {
				return original_UnregisterFromVisibility(pl, 2.f, true);
			}
			else {
				return original_UnregisterFromVisibility(pl, dist, vis);
			}
		}

		GameObject* CreateEffect(pUncStr strPrefab, Effect* effect) {
			auto effectName = strPrefab->str;
			auto position = read(effect + 0x5C, Vector3);
			if (vars::visuals::raid_esp && effect && strPrefab->str && !position.empty( )) {
				switch (RUNTIME_CRC32_W(effectName)) {
				case STATIC_CRC32("assets/prefabs/tools/c4/effects/c4_explosion.prefab"):
					LogSystem::LogExplosion(C4, position);
					LogSystem::Log(StringFormat::format(xorstr(L"%ls explosion %.2f meters away from you."), wC4.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/satchelcharge/effects/satchel-charge-explosion.prefab"):
					LogSystem::LogExplosion(Satchel, position);
					LogSystem::Log(StringFormat::format(xorstr(L"%ls explosion %.2f meters away from you."), wSatchel.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion_incendiary.prefab"):
					LogSystem::LogExplosion(IncenRocket, position);
					LogSystem::Log(StringFormat::format(xorstr(L"%ls explosion %.2f meters away from you."), wIncenRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"):
					LogSystem::LogExplosion(Rocket, position);
					LogSystem::Log(StringFormat::format(xorstr(L"%ls explosion %.2f meters away from you."), wRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				}
			}
			return original_createeffect(strPrefab, effect);
		}
		void HandleRunning(PlayerWalkMovement* a1, ModelState* a2, bool wantsRun) {
			if (vars::misc::omnidirectional_sprinting) {
				//wantsRun = true;
				write(a1 + 0x40, 1.f, float);
				return;
			}
			return original_handleRunning(a1, a2, wantsRun);
		}
		void HandleJumping(PlayerWalkMovement* a1, ModelState* a2, bool wantsJump, bool jumpInDirection = false) { // recreated
			if (vars::misc::inf_jump) {
				if (!wantsJump) {
					return;
				}
				reinterpret_cast<void(_fastcall*)(PlayerWalkMovement*, ModelState*, bool)>(vars::stor::gBase + CO::Jump)(a1, a2, jumpInDirection);
			}
			else {
				return original_handleJumping(a1, a2, wantsJump, jumpInDirection);
			}
		}
		Vector3 get_position(PlayerEyes* playereyes) {
			if (vars::misc::long_neck) {
				if (GetAsyncKeyState(vars::keys::longneck)) {
					return Vector3(LocalPlayer::Entity( )->get_bone_pos(head)) + Vector3(0, 1.15, 0);
				}
			}
			return original_geteyepos(playereyes);
		}
		void __fastcall SetFlying(ModelState* a1, bool a2) { }
		void SendClientTick(BasePlayer* baseplayer) {
			if (!baseplayer) return original_sendclienttick(baseplayer);
			if (vars::misc::anti_aim) {
				auto input = read(baseplayer + 0x4C8, uintptr_t);
				auto state = read(input + 0x20, uintptr_t);
				auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
				yeet += vars::misc::anti_aim_speed;
				if (yeet >= 999) { // reset number
					yeet = 0;
				}
				if (vars::misc::anti_aim_yaw == 0) {
					yaw = 100;
				}
				if (vars::misc::anti_aim_yaw == 1) {
					yaw = -100;
				}
				write(current + 0x18, Vector3(yaw, yeet, 0), Vector3);
			}
			return original_sendclienttick(baseplayer);
		}
		void DoFixedUpdate(PlayerWalkMovement* movement, ModelState* modelstate) {
			float speed = (read(movement + 0x136, bool) /*swim*/ || read(movement + 0x44, float) /* crouch */ > 0.5f) ? 1.7f : (read(movement + 0x138, bool) /*jump*/ ? 8.f : 5.5f);
			if (vars::misc::farmbot) {
				Vector3 vel = read(movement + 0x34, Vector3);
				f_object closest = f_object::get_closest_object(LocalPlayer::Entity( )->get_bone_pos(head), xorstr("ore.prefab"));
				if (closest.valid && vel.Length( ) > 0.f) {
					Vector3 direction = (closest.position - LocalPlayer::Entity( )->get_bone_pos(head)).Normalized( ) * speed;
					write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
				}
			}
			original_dofixedupdate(movement, modelstate);
		}

		void ClientInput(BasePlayer* baseplayah, ModelState* ModelState) {
			vars::stuff::anti_aim_ = yeet;
			if (!baseplayah) return original_clientinput(baseplayah, ModelState);
			if (!baseplayah->IsValid( )) return original_clientinput(baseplayah, ModelState);

			if (vars::misc::rayleigh_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			if (vars::misc::mass_suicide) {
				reinterpret_cast<void(_fastcall*)(BasePlayer*, float)>(vars::stor::gBase + CO::OnLand)(LocalPlayer::Entity( ), -50);
			}
			if (vars::misc::suicide && GetAsyncKeyState(vars::keys::suicide) && LocalPlayer::Entity( )->GetHealth( ) > 0 && !LocalPlayer::Entity( )->IsMenu( )) {
				reinterpret_cast<void(_fastcall*)(BasePlayer*, float)>(vars::stor::gBase + CO::OnLand)(LocalPlayer::Entity( ), -50);
			}
			if (vars::combat::psilent_autoshoot && vars::stor::closestPlayer != null && vars::combat::psilent && !LocalPlayer::Entity( )->IsMenu( )) {
				auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
				Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
				DWORD64 basepr = weapon->entity( );
				DWORD64 mag = read(basepr + 0x2A0, DWORD64);
				int contents = read(mag + 0x1C, int);
				if (basepr && weapon && contents > 0 && utils::LineOfSight(TargetPlayer->get_bone_pos(head),
					(vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) ? LocalPlayer::Entity( )->get_bone_pos(head) + Vector3(0, 1.15, 0) : LocalPlayer::Entity( )->get_bone_pos(head))) {

				}
			}
			
			if (vars::misc::flyhack_indicator) {
				CheckFlyhack( );
			}
			Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
			DWORD64 active = weapon->entity( );
			char* classname = weapon->ClassName( );
			bool weaponmelee = weapon && classname && (strcmp(classname, xorstr("BaseMelee")) || strcmp(classname, xorstr("Jackhammer")));
			if (active && vars::misc::weapon_spam) {
				if (GetAsyncKeyState(vars::keys::weaponspam) && !LocalPlayer::Entity( )->IsMenu( )) {
					reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr(L"")));
				}
			}

			lol::auto_farm_loop(weaponmelee, active);
			game_thread_loop( );
			if (vars::misc::fake_lag) {
				write(LocalPlayer::Entity( ) + 0x5C8, 0.4f, float);
			}
			else {
				write(LocalPlayer::Entity( ) + 0x5C8, 0.05f, float);
			}

			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Water, !vars::misc::jesus);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Tree, vars::misc::walker);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::AI, vars::misc::walker);

			weapon_set( );
			misc_set( );

			original_clientinput(baseplayah, ModelState);

			if (vars::misc::spoof_ladderstate) {
				LocalPlayer::Entity( )->add_modelstate_flag(ModelStateFlag::OnLadder);
			}
			if (vars::misc::farmbot) {
				LocalPlayer::Entity( )->add_modelstate_flag(ModelStateFlag::Sprinting);
			}
		}
		void UpdateAmbient(TOD_Sky* TOD_Sky) {
			uintptr_t cycle = read(TOD_Sky + 0x38, uintptr_t);
			if (vars::misc::custom_time) {
				write(cycle + 0x10, vars::misc::time, float);
			}

			if (!vars::misc::bright_ambient) {
				return original_updateambient(TOD_Sky);
			}
			RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
			RenderSettings::set_ambientIntensity(6.f);
			RenderSettings::set_ambientLight(Color({vars::colors::ambient_color.x, vars::colors::ambient_color.y, vars::colors::ambient_color.z, 1}));
		}
		pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
			if (options->IsFromServer( )) {
				std::wstring cmd = std::wstring(strCommand->str);
				if (cmd.find(xorstr(L"noclip")) != std::wstring::npos || cmd.find(xorstr(L"debugcamera")) != std::wstring::npos || cmd.find(xorstr(L"camspeed")) != std::wstring::npos || cmd.find(xorstr(L"admintime")) != std::wstring::npos) {
					strCommand = nullptr;
				}
			}
			return original_consolerun(options, strCommand, args);
		}
		void DoHitNotify(BaseCombatEntity* entity, HitInfo* info) {
			if (entity->IsPlayer( )) {
				if (vars::misc::hit_logs) {
					LogSystem::Log(StringFormat::format(xorstr(L"Hit %s in %s for %.2f damage"), reinterpret_cast<BasePlayer*>(entity)->_displayName( ), utils::StringPool::Get(info->HitBone( ))->buffer, info->damageTypes( )->Total( )), 5.f);
				}
				if (vars::misc::custom_hitsound) {
					PlaySoundA(xorstr("C:\\plusminus\\hit.wav"), NULL, SND_ASYNC);
					return;
				}
				if (vars::combat::always_headshot) {
					reinterpret_cast<void(*)(Str, GameObject*)>(vars::stor::gBase + CO::EffectRun)(
						Str(xorstr(L"assets/bundled/prefabs/fx/headshot_2d.prefab")),
						LocalPlayer::Entity( )->eyes( )->gameObject( ));
					return;
				}
			}


			return original_dohitnotify(entity, info);
		}
		bool get_isHeadshot(HitInfo* hitinfo) {
			if (vars::misc::custom_hitsound) {
				return false;
			}
			if (vars::combat::always_headshot) {
				return false;
			}
			return original_getisheadshot(hitinfo);
		}
		void Play(ViewModel* viewmodel, pUncStr name) {
			if (vars::weapons::remove_attack_anim) {
				static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
				if (!CALLED_BY(ptr, 0x296) || LocalPlayer::Entity( )->GetActiveWeapon( )->GetID( ) == -75944661) {
					return original_viewmodelplay(viewmodel, name);
				}
			}
			else {
				return original_viewmodelplay(viewmodel, name);
			}
		}
	}
	namespace combat {
		float GetRandomVelocity(ItemModProjectile* mod) {
			return vars::weapons::fast_bullets ? original_getrandomvelocity(mod) * 1.3 : original_getrandomvelocity(mod);
		}
		void AddPunch(HeldEntity* a1, Vector3 a2, float duration) {
			if (vars::weapons::no_recoil) {
				a2 *= vars::weapons::recoil_control / 100.f;
			}
			return original_addpunch(a1, a2, duration);
		}
		Vector3 MoveTowards(Vector3 a1, Vector3 a2, float maxDelta) {
			static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
			if (CALLED_BY(ptr, 0x800)) {
				if (vars::weapons::no_recoil) {
					a2 *= vars::weapons::recoil_control / 100.f;
					maxDelta *= vars::weapons::recoil_control / 100.f;
				}
			}
			return original_movetowards(a1, a2, maxDelta);
		}
		bool DoHit(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
			if (prj->isAuthoritative( )) {
				if (vars::combat::ignore_team) {
					if (test->HitEntity( ) != null) {
						if (test->HitEntity( )->IsValid( )) {
							if (LocalPlayer::Entity( )->is_teammate(reinterpret_cast<BasePlayer*>(test->HitEntity( ))->userID( ))) {
								if (reinterpret_cast<BaseCombatEntity*>(test->HitEntity( ))->IsPlayer( )) {
									return false;
								}
							}
						}
					}
				}
				if (vars::combat::tree_reflect) {
					if (test->HitEntity( ) != null) {
						if (!reinterpret_cast<BaseCombatEntity*>(test->HitEntity( ))->IsPlayer( )) {
							prj->penetrationPower(35.f);
						}
					}
				}
				if (vars::weapons::penetrate) {
					if (test->HitEntity( ) != null) {
						if (test->HitEntity( )->IsValid( )) {
							BaseCombatEntity* lol = reinterpret_cast<BaseCombatEntity*>(test->HitEntity( ));
							if (vars::stuff::testInt == 2) {
								printf(xorstr("%s \n"), lol->ClassName( ));
							}
							if (lol->ClassNameHash( ) == STATIC_CRC32("CargoShip") || lol->ClassNameHash( ) == STATIC_CRC32("BaseOven")
								|| lol->ClassNameHash( ) == STATIC_CRC32("TreeEntity") || lol->ClassNameHash( ) == STATIC_CRC32("OreResourceEntity")
								|| lol->ClassNameHash( ) == STATIC_CRC32("CH47HelicopterAIController") || lol->ClassNameHash( ) == STATIC_CRC32("MiniCopter")
								|| lol->ClassNameHash( ) == STATIC_CRC32("BoxStorage") || lol->ClassNameHash( ) == STATIC_CRC32("Workbench")
								|| lol->ClassNameHash( ) == STATIC_CRC32("VendingMachine") || lol->ClassNameHash( ) == STATIC_CRC32("Barricade")
								|| lol->ClassNameHash( ) == STATIC_CRC32("BuildingPrivlidge") || lol->ClassNameHash( ) == STATIC_CRC32("LootContainer")
								|| lol->ClassNameHash( ) == STATIC_CRC32("HackableLockedCrate") || lol->ClassNameHash( ) == STATIC_CRC32("ResourceEntity")
								|| lol->ClassNameHash( ) == STATIC_CRC32("RidableHorse") || lol->ClassNameHash( ) == STATIC_CRC32("MotorRowboat")
								|| lol->ClassNameHash( ) == STATIC_CRC32("ScrapTransportHelicopter") || lol->ClassNameHash( ) == STATIC_CRC32("JunkPile")
								|| lol->ClassNameHash( ) == STATIC_CRC32("MiningQuarry") || lol->ClassNameHash( ) == STATIC_CRC32("WaterCatcher")) {
								return false;
							}
						}
					}
				}
				//if (!test->HitPoint( ).empty( ) && !test->AttackRay( ).origin.empty()) {
				//	LogSystem::AddTracer(test->AttackRay( ).origin, test->HitPoint( ));
				//}
			}
			return original_dohit(prj, test, point, normal);
		}
		void Launch(Projectile* prdoj) {
			prdoj->invisible(false);

			if (vars::weapons::no_spread) {
				write(prdoj->mod( ) + 0x38, 0.f, float);
			}
			return original_launch(prdoj);
		}
		bool CanHoldItems(BaseMountable* a1) {
			if (vars::weapons::minicopter_aim) return true;
			return original_canholditems(a1);
		}
		void SendProjectileAttack(BasePlayer* a1, PlayerProjectileAttack* a2) {
			uintptr_t PlayerAttack = read(a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
			uintptr_t Attack = read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
			uint32_t hitID = read(Attack + 0x2C, uint32_t);
			if (vars::weapons::spoof_hitdistance) {
				write(a2 + 0x2C, vars::weapons::hitdistance, float);
			}
			if (vars::combat::always_headshot || vars::combat::always_heli_rotor) {
				BaseCombatEntity* entity = BaseNetworkable::clientEntities( )->Find<BaseCombatEntity*>(hitID);
				if (vars::combat::always_headshot) {
					if (entity->IsPlayer( )) {
						uint32_t bone = utils::StringPool::Get(xorstr("head"));
						write(Attack + 0x30, bone, uint32_t);
					}
				}
				if (vars::combat::always_heli_rotor) {
					if (entity->ClassNameHash( ) == STATIC_CRC32("BaseHelicopter")) {
						int health = (int)ceil(read(vars::stor::closestHeli + 0x20C, float));
						if (health <= 5000) {
							write(Attack + 0x30, utils::StringPool::Get(xorstr("tail_rotor_col")), uint32_t);
						}
						else {
							write(Attack + 0x30, utils::StringPool::Get(xorstr("engine_col")), uint32_t);
						}
					}
				}
			}
			return original_sendprojectileattack(a1, a2);
		}
		bool CanAttack(BasePlayer* a1) {
			if (vars::misc::can_attack)
				return true;
			return original_canattack(a1);
		}
		Projectile* CreateProjectile(BaseProjectile* BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
			Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);

			if (vars::weapons::thick_bullet) {
				projectile->thickness(0.4f);
			}
			else {
				projectile->thickness(0.1f);
			}
			return projectile;
		}
		Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
			BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			Vector3 Local = LocalPlayer::Entity( )->eyes( )->get_position( );

			Vector3 heli_target = reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform( )->position( ) + Vector3(0, 1.5, 0);
			Vector3 target = vars::combat::bodyaim ? TargetPlayer->get_bone_pos(spine1) : TargetPlayer->get_bone_pos(head);

			float gravity;
			if (LocalPlayer::Entity( )->GetActiveWeapon( )->GetID( ) == 1540934679 || LocalPlayer::Entity( )->GetActiveWeapon( )->GetID( ) == 1602646136) {
				gravity = 1.9f;
			}
			else {
				gravity = GetGravity(LocalPlayer::Entity( )->GetActiveWeapon( )->LoadedAmmo( ));
			}

			a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity( ), GetBulletSpeed( ), gravity);
			a::Prediction(Local, target, TargetPlayer->newVelocity( ), GetBulletSpeed( ), gravity);

			Vector3 heliDir = (heli_target - Local).Normalized( );
			Vector3 playerDir = (target - Local).Normalized( );

			if (vars::combat::psilent) {
				if (!vars::combat::psilentonkey) {
					if (vars::combat::psilenttarget == 0 && vars::stor::closestPlayer != NULL) {
						inputVec = playerDir;
					}
					if (vars::combat::psilenttarget == 1 && vars::stor::closestHeli != NULL) {
						inputVec = heliDir;
					}
				}
				else {
					if (GetAsyncKeyState(vars::keys::psilent)) {
						if (vars::combat::psilenttarget == 0 && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilenttarget == 1 && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
				}
			}
			if (vars::weapons::no_spread) {
				aimCone = 0.f;
			}
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
	}

}
void hk_(void* Function, void** Original, void* Detour) {
	if (MH_Initialize( ) != MH_OK && MH_Initialize( ) != MH_ERROR_ALREADY_INITIALIZED) {
		MessageBox(0, xorstr(L"big error message sk4ddu"), 0, 0);
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}

void hk__( ) {
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::set_flying), (void**)&original_setflying, hk::misc::SetFlying);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendProjectileAttack), (void**)&original_sendprojectileattack, hk::combat::SendProjectileAttack);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanAttack), (void**)&original_canattack, hk::combat::CanAttack);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendClientTick), (void**)&original_sendclienttick, hk::misc::SendClientTick);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::HandleRunning), (void**)&original_handleRunning, hk::misc::HandleRunning);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::HandleJumping), (void**)&original_handleJumping, hk::misc::HandleJumping);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, hk::combat::GetModifiedAimConeDirection);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanHoldItems), (void**)&original_canholditems, hk::combat::CanHoldItems);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Run), (void**)&original_consolerun, hk::misc::Run);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateProjectile), (void**)&original_create_projectile, hk::combat::CreateProjectile);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateEffect), (void**)&original_createeffect, hk::misc::CreateEffect);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_position), (void**)&original_geteyepos, hk::misc::get_position);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Play), (void**)&original_viewmodelplay, hk::misc::Play);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::VisUpdateUsingCulling), (void**)&original_UnregisterFromVisibility, hk::misc::VisUpdateUsingCulling);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetRandomVelocity), (void**)&original_getrandomvelocity, hk::combat::GetRandomVelocity);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::AddPunch), (void**)&original_addpunch, hk::combat::AddPunch);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::MoveTowards), (void**)&original_movetowards, hk::combat::MoveTowards);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Refract), (void**)&original_refract, hk::exploit::Refract);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoMovement), (void**)&original_domovement, hk::exploit::DoMovement);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Launch), (void**)&original_launch, hk::combat::Launch);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoFixedUpdate), (void**)&original_dofixedupdate, hk::misc::DoFixedUpdate);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate), (void**)&original_clientupdate, hk::misc::ClientUpdate);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate_Sleeping), (void**)&original_clientupdate_sleeping, hk::misc::ClientUpdate_Sleeping);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHit), (void**)&original_dohit, hk::combat::DoHit);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + 0x897620), (void**)&original_walking, hk::misc::Movement_Walking);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::UpdateAmbient), (void**)&original_updateambient, hk::misc::UpdateAmbient);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Jump), (void**)&original_jump, hk::misc::Jump);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientInput), (void**)&original_clientinput, hk::misc::ClientInput);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHitNotify), (void**)&original_dohitnotify, hk::misc::DoHitNotify);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_isHeadshot), (void**)&original_getisheadshot, hk::misc::get_isHeadshot);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ForceToPos), (void**)&original_forcepos, hk::misc::ForcePositionTo);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::OnLand), (void**)&original_onland, hk::misc::OnLand);
}