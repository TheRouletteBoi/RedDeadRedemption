#pragma once
#include "Util/TimeHelpers.hpp"
#include "RDR/Enums.hpp"
#include "Natives.hpp"
#include "Scriptglobal.hpp"
#include "NativeMemory.hpp"

using ActorCreationHandler = void(*)(Actor&);

static const char* spawnActorsNameList[] = {
   "Zebra", "Zombie Horse",
   "Coach 01", "Stagecoach Gatling 01",
   "Canoe 01", "MineCart 01",
   "Truck", "Car",
   "Grizzly Bear", 
   "Pig", "Chicken"
};

static const eActor spawnActorsTypeList[] = {
   ACTOR_RIDEABLE_ANIMAL_MEX_Mule04, ACTOR_UN_HORSE, 
   ACTOR_VEHICLE_Coach01, ACTOR_VEHICLE_StagecoachGatling01,
   ACTOR_VEHICLE_Canoe01, ACTOR_VEHICLE_TRAIN_MineCart01, 
   ACTOR_VEHICLE_Truck01, ACTOR_VEHICLE_Car01,
   ACTOR_ANIMAL_NOR_SuperGrizzlyBear02,
   ACTOR_ANIMAL_Pig01, ACTOR_ANIMAL_Chicken01
};

static const char* skinChangerNameList[] = {
   "Jack", "Daughter 02"
};

static const eActor skinChangerTypeList[] = {
   ACTOR_PLAYER_JACK, ACTOR_COMPANION_Daughter02
};

class Helpers
{
public:
   void OnUpdate();
   bool IsVehicleAvailable();
   Actor GetLocalVehicle();
   Actor GetLocalActor();
   Vector3 GetPlayerPosition(Player slot);
   Vector3 GetActorPosition(Actor actor);
   void SetActorInvulnerable(Actor actor, bool toggle);
   void SetNeverWanted();
   void GiveWeapons(Actor actor);
   void SetInfiniteDeadEye(bool toggle);
   const char* GetPlayerName(Player player);
   bool RequestActor(Actor actorId);
   void CreateActorCallback(eActor actorId, Vector3 position, ActorCreationHandler handler);
   void UpdateActorCreationCallbacks();
   void SetNewSkin(eActor actorId);
   void DeleteActorsInPlayerLayout();




public:
   // Common
   Actor m_localActor{};
   Actor m_localVehicle{};
   Actor m_localEntity{};

   // Player Options
   bool m_Invulnerability{};
   bool m_NeverWanted{};

   // Weapon Options
   bool m_InfiniteDeadeye{};

   // Create Actor
   eActor m_createActorType{};
   ActorCreationHandler m_createActorHandler{};
   uint64_t m_createActorTimeout{};
   bool m_createActorActivate{};
   Vector3 m_createActorPosition{};

   // Skin Changer
   int skinChangerindex{};

   // Mount Options
   int spawnActorsindex{};

   // Protections
   bool m_ExplosionProtection{};
};

extern Helpers g_Helper;
extern Player g_SelectedPlayer;