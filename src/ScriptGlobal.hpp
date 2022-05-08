#pragma once
#include <stdint.h>
#include "Game.hpp"

class ScriptGlobal
{
public:
   enum GlobalIndexToName
   {
      Global_LocalPlayerActor = 34573,
      Global_LocalPlayerPosition = 34574,
      Global_LocalSlot = 29006,
      Global_Money = 3391,
      Global_DeadEyePoints = 25986,
      Global_CurrentRegionLayout = 30616,
      Global_RankLevel = 83864,
      Global_StatIndices = 35278,
      Global_StatsArrayInts = 34581, // increase/decrease set
      Global_StatsArray2 = 49205,
      Global_NetPlayersData = 76943,
      Global_MyNetPlayerData = 78480,
      Global_CurrentSavedModel = 13038,
      Global_bGameProgression = 3365,
      Global_gmp_cpchallenges = 55869,
      Global_MP_UNLOCKDATA = 84364,
      Global_MP_GoldenWeapon = 83823,
      Global_SC_LeaderBoardData = 87412,
      Global_SC_Challenges = 84611,
      Global_PVPChallenges = 22796,
      Global_MPAmbientMissions = 3084,
      Global_iLastInsertedCollectible = 62336,
      Global_ShopColletibleLookup = 61639,
      Global_bIsFreshStart = 3364,
      Global_ResetData = 34165,
      Global_MP_SavedTitle = 76886,
      Global_MP_SavedHorseAEName = 76870,
      Global_MP_MPLAW_Layout = 79341,
      Global_MP_MPLAW_holdingSet = 78577,
      Global_MPScratchLayout = 79342,
      Global_MP_OpenedPickupSet = 83590,
      Global_MP_SavedPlayerAEName = 76854,
      Global_bGraveGunDialogPlayed = 3415,
      Global_aNetUnlockState = 26055,
      Global_aQuestTrackedHash = 76694,
      Global_aCompletedQuestListInfo = 76695,
      Global_aQuestData = 76542,
      Global_aQuestListInfo = 76543,
      Global_aHerbs = 9975,
      Global_aRegionBlipHelp = 26031,
      Global_aRegionBlipsData = 8723,
      Global_TutorialOne = 76846,
      Global_TutorialTwo = 76847,
      Global_TutorialThree = 76848,
      Global_TutorialFour = 76849,
      Global_iSaveLoadFlags = 63095,
      Global_PlayerCamp = 63084,
      Global_eSurvivalismSkill = 62998,
      Global_AmbientMissions = 49310,
      Global_Regions = 29008,
      Global_RegionSector = 29155,
      Global_bShopAmmoAvailability = 62459,
      Global_bShopItemAvailability = 62378,
      Global_bShopWeaponAvailability = 62337,
      Global_HuntedOutfit = 28180,
      Global_Inventory = 28260,
      Global_WornOutfit = 28178,
      Global_NewOutfit = 28179,
      Global_Outfits = 27774,
      Global_BountyHunterStruct = 26303,
      Global_bStartTreasureHunter = 3368,
      Global_aBeatTrackingData = 16876,
      Global_fSavedDeadEyePoints = 83815,
      Global_PlayerHouses = 16537,
      Global_PlayerBounties = 26401,
      Global_LawDogs = 26316,
      Global_WeatherManager = 16524,
      Global_WindManager = 16517,
      Global_Deed = 13172,
      Global_PlayerData = 12976,
      Global_MexicanRevolution = 30619,
      Global_eLastMission = 6269,
      Global_bWanted = 3403,
      Global_bCampFireDebug = 3370,
      Global_bIsSpawnMode = 3371,
      Global_bCasualMode = 3413,
      Global_RC_CootsChapel = 6291,
      Global_RC_Armadillo = 6298,
      Global_RC_TwinRocks = 6351,
      Global_RC_RidgewoodFarm = 6364,
      Global_RC_ChollaSprings = 6391,
      Global_RC_RathskellerFork = 6402,
      Global_RC_GaptoothBreach = 6433,
      Global_RC_SolomonsFolly = 6490,
      Global_RC_Tumbleweed = 6501,
      Global_RC_GaptoothRidge = 6532,
      Global_RC_BenedictPoint = 6537,
      Global_RC_HennigansStead = 6550,
      Global_RC_HennigansRanch = 6563,
      Global_RC_ThievesLanding = 6614,
      Global_RC_PikesBasin = 6643,
      Global_RC_Plainview = 6654,
      Global_RC_FortMercer = 6667,
      Global_RC_RioBravo = 6704,
      Global_RC_Escalera = 6709,
      Global_RC_Nosalida = 6764,
      Global_RC_TesoroAzul = 6785,
      Global_RC_PuntaOrgullo = 6810,
      Global_RC_Chuparosa = 6815,
      Global_RC_LasHermanas = 6866,
      Global_RC_Perdido = 6928,
      Global_RC_CasaMadrugada = 6933,
      Global_RC_ElPresidio = 6962,
      Global_RC_Torquemada = 6987,
      Global_RC_ElMataderoTown = 7002,
      Global_RC_DiezCoronas = 7027,
      Global_RC_BeechersHope = 7032,
      Global_RC_Blackwater = 7035,
      Global_RC_GreatPlains = 7108,
      Global_RC_PacificUnionRailroadCamp = 7113,
      Global_RC_ManzanitaPost = 7148,
      Global_RC_Cochinay = 7171,
      Global_RC_TallTrees = 7174,
   };

public:
   static uintptr_t* GetGlobalPtr(int globalId)
   {
      //return &g_GameVariables->pGlobalVars[(globalId >> 18) & 0x3F][globalId & 0x3FFFF];
      //return (g_GameVariables->pGlobalVars[globalId >> 0x12 & 0x3F]) + (globalId & 0x3FFFF);
      return &g_GameVariables->pGlobalVars[globalId / 0x40000][globalId % 0x40000];
   }

   template <typename T>
   static T Get(int globalId)
   {
      uintptr_t* addr = GetGlobalPtr(globalId);

      if (addr == nullptr)
         return 0;

      return *(T*)addr;
   }

   static const char* GetString(int globalId)
   {
      const char* addr = (const char*)GetGlobalPtr(globalId);

      if (addr == nullptr)
         return "";

      return addr;
   }

   template <typename T>
   static void Set(int global, T value)
   {
      uintptr_t* addr = GetGlobalPtr(global);

      if (addr == nullptr)
         return;

      *(T*)addr = value;
   }

   static void SetString(int global, const char* value)
   {
      strncpy((char*)GetGlobalPtr(global), value, strlen(value));
      *(char*)(GetGlobalPtr(global) + strlen(value)) = 0;
   }

   static void SetBit(int globalId, int index)
   {
      *(GetGlobalPtr(globalId)) |= (1 << index);
   }

   static void ClearBit(int globalId, int index)
   {
      *(GetGlobalPtr(globalId)) &= (1 << index);
   }

   static bool IsBitSet(int globalId, int index)
   {
      uintptr_t* addr = GetGlobalPtr(globalId);

      if (addr == nullptr)
         return false;

      uint32_t value = *(uint32_t*)addr;
      return ((value >> index) & 1) != 0;
   }

   static void* GetStructField(int globalId, int index)
   {
      uintptr_t* MemoryAddress = GetGlobalPtr(globalId);
      return (void*)(MemoryAddress + (4 * index));
   }

   static void* GetArray(int globalId, int itemSize)
   {
      uintptr_t count = *(uintptr_t*)GetGlobalPtr(globalId);

      void** result = nullptr;

      for (int i = 0; i < count; i++)
      {
         uintptr_t* MemoryAddress = GetGlobalPtr(globalId);
         result[i] = (void*)(MemoryAddress + 4 + (4 * itemSize * i));
      }

      return result;
   }

   static void* GetArrayItem(int globalId, int index, int itemSize)
   {
      int count = *(uintptr_t*)GetGlobalPtr(globalId);
      uintptr_t* MemoryAddress = GetGlobalPtr(globalId);
      return (void*)(MemoryAddress + 4 + (4 * itemSize * index));
   }

   static void Debug(int globalId)
   {
      uintptr_t* address = GetGlobalPtr(globalId);
      printf("Global Address: 0x%X\n", address);
      printf("Global Value: 0x%X\n", *address);
   }
};