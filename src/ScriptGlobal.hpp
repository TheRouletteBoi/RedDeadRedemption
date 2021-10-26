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
      Global_CurrentRegionLayout = 30616,
      Global_StatsArray1 = 34581, // increase/decrease set
      Global_StatsArray2 = 49205,
      Global_Bounty = 26401,
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