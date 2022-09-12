#include "Submenus.hpp"

void PlayerOptionsSubmenu()
{
   g_Menu.title("Player Options");
   g_Menu.option("Skin Changer").submenu(SkinChangerSubmenu);
   g_Menu.option("Invulnerability").toggle(g_Helper.m_Invulnerability, nullptr, [] 
   { 
      g_Helper.SetActorInvulnerable(g_Helper.m_localActor, false); 
   });

   g_Menu.option("Never Wanted").toggle(g_Helper.m_NeverWanted);
}

void SkinChangerSubmenu()
{
   g_Menu.title("Skin Changer");
   g_Menu.option("Skins").scroller(skinChangerNameList, g_Helper.skinChangerindex, ARRAYSIZE(skinChangerNameList) - 1).action(OptionAction::EnterPress, [] 
   {
      g_Helper.SetNewSkin(skinChangerTypeList[g_Helper.skinChangerindex]);
   });
}

void MountOptionsSubmenu()
{
   g_Menu.title("Mount Options");
   g_Menu.option("Infinite Horse Stamina").local(NativeMemory::HasInfiniteHorseStamina()).call(MOUNT::_CHEAT_INFINITE_HORSE_STAMINA, !NativeMemory::HasInfiniteHorseStamina());
   g_Menu.option("Delete Mount").call(LAYOUT::DESTROY_ACTOR, g_Helper.m_localVehicle);

   g_Menu.option("Spawn Mount").scroller(spawnActorsNameList, g_Helper.spawnActorsindex, ARRAYSIZE(spawnActorsNameList) - 1).action(OptionAction::EnterPress, []
   {
      Vector3 pos = g_Helper.GetActorPosition(g_Helper.m_localActor);

      g_Helper.CreateActorCallback(spawnActorsTypeList[g_Helper.spawnActorsindex], pos, [](Actor& actor)
      {
         if (VEHICLE::IS_ACTOR_VEHICLE(actor))
         {
            VEHICLE::SET_VEHICLE_ALLOWED_TO_DRIVE(actor, true);
            VEHICLE::ENABLE_VEHICLE_SEAT(actor, 0, true);
            ACTOR::SET_ACTOR_AUTO_TRANSITION_TO_DRIVER_SEAT(g_Helper.m_localActor, 1);
            VEHICLE::SET_ACTOR_IN_VEHICLE(g_Helper.m_localActor, actor, 0);
            VEHICLE::START_VEHICLE(actor);
            VEHICLE::SET_VEHICLE_ENGINE_RUNNING(actor, true);
         }
         else if (ACTOR::IS_ACTOR_ANIMAL(actor))
         {
            ACTOR::SET_ACTOR_RIDEABLE(actor, true);
            PLAYER::SET_ALLOW_RIDE_BY_PLAYER(actor, true);
            AI::SET_ACTORS_HORSE(g_Helper.m_localActor, actor);
         }

         LAYOUT::RELEASE_ACTOR(actor);

      });

   });
}

void WeaponOptionsSubmenu()
{
   g_Menu.title("Weapon Options");
   g_Menu.option("Give Weapons").action(OptionAction::EnterPress, [] 
   {
      g_Helper.GiveWeapons(g_Helper.m_localActor);
   });

   g_Menu.option("Infinite DeadEye").toggle(g_Helper.m_InfiniteDeadeye).action(OptionAction::EnterPress, [] 
   {
      g_Helper.SetInfiniteDeadEye(g_Helper.m_InfiniteDeadeye);
   });

   g_Menu.option("Explosive Ammo").local(NativeMemory::HasBlazingGuns()).call(FIRE::_CHEAT_BLAZING_GUNS, !NativeMemory::HasBlazingGuns());
}

void TeleportEntity(Actor actor, Vector3 coords)
{
   if (ACTOR::IS_ACTOR_VALID(actor))
      PLAYER::TELEPORT_ACTOR_WITH_HEADING(actor, coords.x, coords.y, coords.z, 0.0f, 1, 1, 1);
}

void TeleportOptionsSubmenu()
{
   g_Menu.title("Teleport Options");
   g_Menu.option("Armadillo").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-2171.0f, 23.0f, 2592.0f));
   g_Menu.option("MacFarlane's Ranch").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-838.0f, 93.0f, 2422.0f));
   g_Menu.option("Casa Madrugada").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-809.0f, 18.0f, 3782.0f));
   g_Menu.option("Black Water").call(TeleportEntity, g_Helper.m_localEntity, Vector3(720.0f, 78.0f, 1400.0f));
   g_Menu.option("Escalera").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-4231.0f, 33.0f, 4487.0f));
   g_Menu.option("Chuparosa").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-2745.0f, 36.0f, 4292.0f));
   g_Menu.option("El Presidio").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-720.0f, 82.0f, 3311.0f));
   g_Menu.option("Gapooth Breach").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-4432.0f, 21.0f, 3200.0f));
}

void SelectedPlayerSubmenu()
{
   g_Menu.title(g_Helper.GetPlayerName(g_SelectedPlayer));
   g_Menu.option("Teleport To").call(TeleportEntity, g_Helper.m_localEntity, g_Helper.GetPlayerPosition(g_SelectedPlayer));
   g_Menu.option("Explode Player").action(OptionAction::EnterPress, [] 
   {
      Vector3 position = g_Helper.GetPlayerPosition(g_SelectedPlayer);
      Vector3 damage = Vector3(20.0f, 20.0f, 20.0f);
      EXPLOSION::_CREATE_EXPLOSION(&position, "ExplosionMedium", 0, &damage, 0);
   });
}

void NetworkPlayersSubmenu()
{
   g_Menu.title("Network Players");

   for (int i = 0; i < MAX_PLAYERS; i++)
   {
      g_Menu.option(g_Helper.GetPlayerName(i));
   }

   if (g_Menu.IsEnterPressed() && PLAYER::IS_SLOT_VALID(g_Menu.m_CurrentOption - 1))
   {
      g_SelectedPlayer = static_cast<Player>(g_Menu.m_CurrentOption - 1);
      g_Menu.ChangeSubmenu(SelectedPlayerSubmenu);
   }
}

void NetworkOptionsSubmenu()
{
   g_Menu.title("Network Options");
   g_Menu.option("Network Players").submenu(NetworkPlayersSubmenu);
   g_Menu.option("Delete Nearby Actors").action(OptionAction::EnterPress, []
   {
      g_Helper.DeleteActorsInPlayerLayout();
   });
}

void DebugOptionsSubmenu()
{
   g_Menu.title("Debug");
   g_Menu.option("Input some text")
   .keyboard([](const std::string& text)
   {
      printf("you have typed %s\n", text.c_str());
   });

   g_Menu.option("Explosion Protection").toggle(g_Helper.m_ExplosionProtection);
}

void MainSubmenu()
{
   g_Menu.title("Main Menu");
   g_Menu.option("Player Options").submenu(PlayerOptionsSubmenu);
   //g_Menu.option("Mount Options").submenu(MountOptionsSubmenu);
   //g_Menu.option("Weapon Options").submenu(WeaponOptionsSubmenu);
   //g_Menu.option("Teleport Options").submenu(TeleportOptionsSubmenu);
   g_Menu.option("Network Options").submenu(NetworkOptionsSubmenu);
   //g_Menu.option("Debug").submenu(DebugOptionsSubmenu);
}