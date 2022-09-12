#include "Helpers.hpp"

Helpers g_Helper;
Player g_SelectedPlayer{};

void Helpers::OnUpdate()
{
   m_localActor = GetLocalActor();

   m_localVehicle = GetLocalVehicle();

   m_localEntity = IsVehicleAvailable() ? GetLocalVehicle() : m_localActor;

   if (m_Invulnerability)
      SetActorInvulnerable(m_localActor, true);

   if (m_NeverWanted)
      SetNeverWanted();


   UpdateActorCreationCallbacks();
}

bool Helpers::IsVehicleAvailable()
{
   return MOUNT::GET_MOUNT(m_localActor) > 0 || VEHICLE::IS_ACTOR_DRIVING_VEHICLE(m_localActor);
}

Actor Helpers::GetLocalVehicle()
{
   Actor vehicle = 0;
   if (MOUNT::GET_MOUNT(m_localActor) > 0)
   {
      vehicle = MOUNT::GET_MOUNT(m_localActor);
   }
   else if (VEHICLE::IS_ACTOR_DRIVING_VEHICLE(m_localActor))
   {
      vehicle = VEHICLE::GET_VEHICLE(m_localActor);
   }

   return vehicle;
}

Actor Helpers::GetLocalActor()
{
   return PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT());
}

Vector3 Helpers::GetPlayerPosition(Player slot)
{
   Vector3 pos{};
   PLAYER::GET_SLOT_POSITION(slot, &pos.x, &pos.y, &pos.z);
   return pos;
}

Vector3 Helpers::GetActorPosition(Actor actor)
{
   Vector3 pos{};
   PLAYER::GET_POSITION(actor, &pos.x, &pos.y, &pos.z);
   return pos;
}

void Helpers::SetActorInvulnerable(Actor actor, bool toggle)
{
   PLAYER::SET_ACTOR_INVULNERABILITY(actor, toggle);
   PLAYER::SET_ACTOR_UNKILLABLE(actor, toggle);
   PLAYER::SET_TOUGH_ACTOR(actor, toggle);
   DECAL::CLEAR_CHARACTER_BLOOD();
}

void Helpers::SetNeverWanted()
{
   HUD::UI_SET_HAS_CHEATED(1);
   ScriptGlobal::Set<int>(26316 + 56 + 0, 4096);
   ScriptGlobal::Set<int>(26316 + 56 + 3, 8192);
   ScriptGlobal::Set<int>(26316 + 56 + 3, 16384);
}

void Helpers::GiveWeapons(Actor actor)
{
   // missing weapons from undead nightmare 
   // TODO: patch native in eboot to bypass undead guns in mp
   // torch             | melee
   // undead bait       | explosive/thrown
   // holy water        | thrown
   // blunderbuss       | shotgun
   // explosive rifle   | sniper Rifles
   // boom bait         | explosive/thrown

   for (int i = 0; i < 50; i++)
   {
      WEAPON::GIVE_WEAPON_TO_ACTOR(actor, i, 1000, 1, 1);
      WEAPON::SET_WEAPON_GOLD(actor, i, true);
   }

   for (int i = 0; i < 13; i++)
   {
      WEAPON::_SET_ACTOR_INFINITE_AMMO_FLAG(actor, i, 1);
   }
}

void Helpers::SetInfiniteDeadEye(bool toggle)
{
   PLAYER::SET_DEADEYE_INVULNERABILITY(m_localActor, toggle);
   PLAYER::SET_DEADEYE_DAMAGE_SCALING(m_localActor, toggle ? 50.0f : 1.0f);
   PLAYER::SET_DEADEYE_REGENERATION_RATE(m_localActor, toggle ? 5.0f : 1.0f, 1);
   PLAYER::SET_DEADEYE_TIMESCALE(m_localActor, 0.1);
   PLAYER::SET_INFINITE_DEADEYE(m_localActor, toggle);
}

const char* Helpers::GetPlayerName(Player player)
{
   const char* name = PLAYER::GET_SLOT_NAME(player);
   if (strcmp(name, "__INVALID__") == 0)
      return "Not Connected";

   return name;
}

bool Helpers::RequestActor(Actor actorId)
{
   if (STREAMING::STREAMING_IS_ACTOR_LOADED(actorId, -1))
   {
      return true;
   }
   else
   {
      STREAMING::STREAMING_REQUEST_ACTOR(actorId, true, false);
   }

   return false;
}

void Helpers::CreateActorCallback(eActor actorId, Vector3 position, ActorCreationHandler handler)
{
   m_createActorType = actorId;
   m_createActorPosition = position;
   m_createActorHandler = handler;
   m_createActorTimeout = get_time_now() + 8000;
   m_createActorActivate = true;
}

void Helpers::UpdateActorCreationCallbacks()
{
   if (m_createActorActivate)
   {
      if (m_createActorHandler == nullptr || m_createActorTimeout < get_time_now())
      {
         m_createActorActivate = false;
         return;
      }
      
      Actor actor = 0;
      if (RequestActor(m_createActorType))
      {
         Vector3 rotation = Vector3(0.0f, 0.f, 0.0f);
         //char actorName[30];
         //snprintf(actorName, sizeof(actorName), "SprxActor_%d", i++);
         actor = LAYOUT::CREATE_ACTOR_IN_LAYOUT(
            LAYOUT::FIND_NAMED_LAYOUT("PlayerLayout"),
            "",
            m_createActorType,
            m_createActorPosition.x, m_createActorPosition.y, m_createActorPosition.z,
            rotation.x, rotation.y, rotation.z);
      }
      

      if (ACTOR::IS_ACTOR_VALID(actor))
      {
         m_createActorHandler(actor);

         m_createActorActivate = false;
      }
   }
}

void Helpers::SetNewSkin(eActor actorId)
{
   Layout layout = LAYOUT::FIND_NAMED_LAYOUT("PlayerLayout");

   Vector3 pos = GetActorPosition(m_localActor);

   Actor actor = LAYOUT::_CREATE_ENUMERATED_PLAYER_ACTOR_IN_LAYOUT(layout, m_localActor, "", actorId, pos.x, pos.y, pos.z, 0.0f, 0.0f, 0.0f, 0);
   ACTORINFO::SET_ACTOR_HEALTH(actor, 500.0f);
}

void Helpers::DeleteActorsInPlayerLayout()
{
   Layout layout = LAYOUT::FIND_NAMED_LAYOUT("PlayerLayout");
   int iterator = LAYOUT::CREATE_OBJECT_ITERATOR(layout);
   LAYOUT::ITERATE_ON_OBJECT_TYPE(iterator, OBJECT_TYPE_Actor);
   LAYOUT::START_OBJECT_ITERATOR(iterator);
   for (int i = 0; i < LAYOUT::GET_NUM_ITERATOR_MATCHES(iterator); i++)
   {
      Actor actor = LAYOUT::OBJECT_ITERATOR_CURRENT(iterator);
      if (actor != m_localActor && !PLAYER::IS_ACTOR_PLAYER(actor))
      {
         LAYOUT::DESTROY_ACTOR(actor);
      }

      LAYOUT::OBJECT_ITERATOR_NEXT(iterator);
   }
   LAYOUT::DESTROY_ITERATOR(iterator);
   LAYOUT::DESTROY_LAYOUT_OBJECTS(LAYOUT::FIND_NAMED_LAYOUT("NetLayout"));
}