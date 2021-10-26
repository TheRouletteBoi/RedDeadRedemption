#include "Submenus.hpp"

void PlayerOptionsSubmenu()
{
   g_Menu.banner("Player Options");
   g_Menu.option("Skin Changer").submenu(SkinChangerSubmenu).end();
   g_Menu.option("Invulnerability").toggle(g_Helper.m_Invulnerability, nullptr, [] 
   { 
      g_Helper.SetActorInvulnerable(g_Helper.m_localActor, false); 
   }).end();

   g_Menu.option("Never Wanted").toggle(g_Helper.m_NeverWanted).end();
}

void SkinChangerSubmenu()
{
   g_Menu.banner("Skin Changer");
   g_Menu.option("Skins").scroller(skinChangerNameList, g_Helper.skinChangerindex, ARRAYSIZE(skinChangerNameList) - 1).action(OptionAction::EnterPress, [] 
   {
      g_Helper.SetNewSkin(skinChangerTypeList[g_Helper.skinChangerindex]);
   }).end();
}

void MountOptionsSubmenu()
{
   g_Menu.banner("Mount Options");
   g_Menu.option("Infinite Horse Stamina").local(NativeMemory::HasInfiniteHorseStamina()).call(MOUNT::_CHEAT_INFINITE_HORSE_STAMINA, !NativeMemory::HasInfiniteHorseStamina()).end();
   g_Menu.option("Delete").call(LAYOUT::DESTROY_ACTOR, g_Helper.m_localVehicle).end();

   g_Menu.option("Spawn Mount").scroller(spawnActorsNameList, g_Helper.spawnActorsindex, ARRAYSIZE(spawnActorsNameList) - 1).action(OptionAction::EnterPress, []
   {
      Vector3 pos = g_Helper.GetActorPosition(g_Helper.m_localActor);

      g_Helper.CreateActorCallback(spawnActorsTypeList[g_Helper.spawnActorsindex], pos, [](Actor& actor)
      {
         ACTOR::SET_ACTOR_RIDEABLE(actor, true);
         PLAYER::SET_ALLOW_RIDE_BY_PLAYER(actor, true);

         if (VEHICLE::IS_ACTOR_VEHICLE(actor))
         {
            VEHICLE::ENABLE_VEHICLE_SEAT(actor, 0, true);
            VEHICLE::SET_VEHICLE_ALLOWED_TO_DRIVE(actor, true);
            VEHICLE::SET_VEHICLE_ENGINE_RUNNING(actor, true);
            VEHICLE::VEHICLE_SET_HANDBRAKE(actor, false);
            VEHICLE::START_VEHICLE(actor);
            VEHICLE::SET_ACTOR_IN_VEHICLE(g_Helper.m_localActor, actor, 0);
         }
         else if (ACTOR::IS_ACTOR_ANIMAL(actor))
         {

         }

         LAYOUT::RELEASE_ACTOR(actor);

      });

   }).end();
}

void WeaponOptionsSubmenu()
{
   g_Menu.banner("Weapon Options");
   g_Menu.option("Give Weapons").action(OptionAction::EnterPress, [] 
   {
      g_Helper.GiveWeapons(g_Helper.m_localActor);
   }).end();

   g_Menu.option("Infinite DeadEye").toggle(g_Helper.m_InfiniteDeadeye).action(OptionAction::EnterPress, [] 
   {
      g_Helper.SetInfiniteDeadEye(g_Helper.m_InfiniteDeadeye);
   }).end();

   g_Menu.option("Explosive Ammo").local(NativeMemory::HasBlazingGuns()).call(FIRE::_CHEAT_BLAZING_GUNS, !NativeMemory::HasBlazingGuns()).end();
}

void TeleportEntity(Actor actor, Vector3 coords)
{
   if (ACTOR::IS_ACTOR_VALID(actor))
      PLAYER::TELEPORT_ACTOR_WITH_HEADING(actor, coords.x, coords.y, coords.z, 0.0f, 1, 1, 1);
}

void TeleportOptionsSubmenu()
{
   g_Menu.banner("Teleport Options");
   g_Menu.option("Armadillo").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-2171.0f, 23.0f, 2592.0f)).end();
   g_Menu.option("MacFarlane's Ranch").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-838.0f, 93.0f, 2422.0f)).end();
   g_Menu.option("Casa Madrugada").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-809.0f, 18.0f, 3782.0f)).end();
   g_Menu.option("Black Water").call(TeleportEntity, g_Helper.m_localEntity, Vector3(720.0f, 78.0f, 1400.0f)).end();
   g_Menu.option("Escalera").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-4231.0f, 33.0f, 4487.0f)).end();
   g_Menu.option("Chuparosa").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-2745.0f, 36.0f, 4292.0f)).end();
   g_Menu.option("El Presidio").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-720.0f, 82.0f, 3311.0f)).end();
   g_Menu.option("Gapooth Breach").call(TeleportEntity, g_Helper.m_localEntity, Vector3(-4432.0f, 21.0f, 3200.0f)).end();
}

void SelectedPlayerSubmenu()
{
   g_Menu.banner("Network Options");
   g_Menu.option("Teleport To").call(TeleportEntity, g_Helper.m_localEntity, g_Helper.GetPlayerPosition(g_SelectedPlayer)).end();
   g_Menu.option("Explode Player").action(OptionAction::EnterPress, [] 
   {
      Vector3 position = g_Helper.GetPlayerPosition(g_SelectedPlayer);
      Vector3 damage = Vector3(20.0f, 20.0f, 20.0f);
      EXPLOSION::_CREATE_EXPLOSION(&position, "ExplosionMedium", 0, &damage, 0);
   }).end();
}

void NetworkPlayersSubmenu()
{
   g_Menu.banner("Network Players");

   for (int i = 0; i < MAX_PLAYERS; i++)
   {
      g_Menu.option(g_Helper.GetPlayerName(i)).end();
   }

   if (g_Menu.IsEnterPressed() && PLAYER::IS_SLOT_VALID(g_Menu.m_CurrentOption - 1))
   {
      g_SelectedPlayer = static_cast<Player>(g_Menu.m_CurrentOption - 1);
      g_Menu.ChangeSubmenu(SelectedPlayerSubmenu);
   }
}

void NetworkOptionsSubmenu()
{
   g_Menu.banner("Network Options");
   g_Menu.option("Network Players").submenu(NetworkPlayersSubmenu).end();
   g_Menu.option("Delete Nearby Actors").action(OptionAction::EnterPress, []
   {
      g_Helper.DeleteDeadPeds();
   }).end();
}

void DebugOptionsSubmenu()
{
   g_Menu.banner("Debug");
   g_Menu.option("Input some text")
   .keyboard([](const std::string& text)
   {
      printf("you have typed %s\n", text.c_str());
   }).end();

   g_Menu.option("Explosion Protection").toggle(g_Helper.m_ExplosionProtection).end();
}

void MainSubmenu()
{
   g_Menu.banner("RouLetteBoi Menu 1.0");
   g_Menu.option("Player Options").submenu(PlayerOptionsSubmenu).end();
   g_Menu.option("Mount Options").submenu(MountOptionsSubmenu).end();
   g_Menu.option("Weapon Options").submenu(WeaponOptionsSubmenu).end();
   g_Menu.option("Teleport Options").submenu(TeleportOptionsSubmenu).end();
   g_Menu.option("Network Options").submenu(NetworkOptionsSubmenu).end();
   g_Menu.option("Debug").submenu(DebugOptionsSubmenu).end();
}